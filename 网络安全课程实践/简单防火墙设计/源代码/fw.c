#include "fw.h"     

int init_fw_read_write_module(void) {	
	int ret = 0;
	my_ipt = (my_iptable *)vmalloc(sizeof(my_iptable));

	if(!my_ipt)														
		ret = -ENOMEM;
	else {
		memset((char *)my_ipt, 0, sizeof(my_iptable));
		proc_entry = proc_create("fw", 0646, NULL,&fops);		//创建规则文件存放在虚拟文件系统/proc	

		if(proc_entry == NULL) {
			ret = -ENOMEM;
			vfree(my_ipt);
			printk(KERN_INFO "fw: couldn't create proc entry\n");
		}		
		else {
			printk(KERN_INFO "fw: fw proc entry succesfully registered\n");
			rule_index = 0;
			next_rule_ctr = 0;
			num_of_rules = 0;
			printk(KERN_INFO "fw: fw read_write module loaded successfully\n");	
		}		
	}
	return 0;
}

int init_rule_match_module(void) {
	nfho_in.hook		= fw_inbound_filter;		
	nfho_in.hooknum 	= NF_INET_LOCAL_IN;			
	nfho_in.pf			= PF_INET;						
	nfho_in.priority 	= NF_IP_PRI_FIRST;			
	nf_register_net_hook(&init_net,&nfho_in);
	
	nfho_out.hook		= fw_outbound_filter;	
	nfho_out.hooknum	= NF_INET_LOCAL_OUT;
	nfho_out.pf			= PF_INET;
	nfho_out.priority	= NF_IP_PRI_FIRST;
	nf_register_net_hook(&init_net,&nfho_out);

	printk(KERN_INFO "fw: rule match module loaded\n");
	return 0;
}	

int my_init_module(void) {
	init_fw_read_write_module();
	init_rule_match_module();
	return 0;
}

ssize_t fw_write(struct file *filp, const char __user *buff, size_t count, loff_t *ppos) {
	int rules_remaining = MAX_RULES - rule_index + 1;		
	int num = count / sizeof(my_iptable);						
	memset(my_ipt, 0, sizeof(my_iptable));					

	if (num > rules_remaining) {
		printk(KERN_INFO "fw: fw_table is out of memory. Will exit now..\n");
		return -ENOSPC;
	} 
	
	if (copy_from_user(my_ipt, buff, count)) {	
		printk(KERN_INFO "Sorry, reading the user-data from /proc failed");
		return -EFAULT;
	}					
	printk(KERN_INFO "\ncopied the rule from user \nrules_remaining: %d, num: %d, len: %ld\n", rules_remaining, num,  count);
	
	if(my_ipt->action == DELETE) {
		if (!Delete_Rule(my_ipt))
			printk(KERN_INFO "fw: fw has deleted the rule %u\n", my_ipt->rule_index);		
		else
			printk(KERN_INFO "fw: fw couldn't find your rule to delete\n");		
		return 0;
	}

	printk(KERN_INFO "my_ipt hook number: %u \n", my_ipt->hook_entry);
	memcpy(fw_rules_table + rule_index, my_ipt, sizeof(my_iptable));
	printk(KERN_INFO "rule written. rule_index: %d, num_of_rules: %d", rule_index+1, num_of_rules+1);
	rule_index ++;
	num_of_rules ++;
	
	return count;	
}


unsigned int fw_inbound_filter(void *priv,struct sk_buff *skb,const struct nf_hook_state *state){
	int index = 0;
	int action = 0;	
	for(index = 0; index < num_of_rules; index ++) {
		if(fw_rules_table[index].hook_entry == NF_INET_LOCAL_IN) 
		{
			action = Check_Rule(skb, &fw_rules_table[index]);
			if(!action)	{				
				if (fw_rules_table[index].action == BLOCK)
					return NF_DROP;
				else
					return NF_ACCEPT;
			}			
		}	
	}
	return NF_ACCEPT;
}


unsigned int fw_outbound_filter(void *priv,struct sk_buff *skb,const struct nf_hook_state *state)
{
	int index = 0;
	int action = 0;	
	for(index = 0; index < num_of_rules; index ++) {
		if(fw_rules_table[index].hook_entry == NF_INET_LOCAL_OUT) {
			action = Check_Rule(skb, &fw_rules_table[index]);
			if(!action) {				
				if (fw_rules_table[index].action == BLOCK)
					return NF_DROP;
				else
					return NF_ACCEPT;
			}
		}	
	}
	return NF_ACCEPT;
}

int Delete_Rule(const my_iptable *my_ipt) {
	unsigned int index = my_ipt->rule_index - 1;
	if (index + 1 > num_of_rules) {
		printk(KERN_INFO "fw: The index for the given rule is out of bounds, Delete operation unsuccessful\n");
		return 1;
	}
	memset(&(fw_rules_table[index]), 0 , sizeof(my_iptable));	
		
	if (index == num_of_rules - 1) { 								
		--num_of_rules;												
		--rule_index;	
	}	
	else {															
		for(; index < num_of_rules-1; index++)						
			fw_rules_table[index] = fw_rules_table[index + 1];		
		num_of_rules --;
		rule_index --;
	}
	return 0;
}

int Check_Rule(struct sk_buff *skb, my_iptable *my_ipt) {
	struct iphdr *ip_header 		= 	ipip_hdr(skb);		
	struct tcphdr *tcp_header 		=	tcp_hdr(skb);		
	struct udphdr *udp_header 		=	udp_hdr(skb);		
	
	if((my_ipt->ip_rule.bitmask & IS_SIP) == IS_SIP) {
		if(!Check_IP((unsigned char *)(&ip_header->saddr), my_ipt->ip_rule.sip, my_ipt->ip_rule.smask, IS_SIP))
		{}
		else
			return RULE_DOES_NOT_MATCH;
	}
	if ((my_ipt->ip_rule.bitmask & IS_DIP ) == IS_DIP) {
		if(!Check_IP((unsigned char *)(&ip_header->daddr), my_ipt->ip_rule.dip, my_ipt->ip_rule.dmask, IS_DIP))
		{}
		else
			return RULE_DOES_NOT_MATCH;
	}	

	if ((my_ipt->ip_rule.bitmask & IP_TYPE_PACKET ) == IP_TYPE_PACKET)		
	{		
		if (!Check_Protocol(ip_header->protocol, my_ipt->ip_rule.proto, IP_TYPE_PACKET))	
		{}
		else
			return RULE_DOES_NOT_MATCH;
	}
	

	if ((my_ipt->port_rule.bitmask & IS_SPORT) == IS_SPORT)	{
		if (!Check_Port(tcp_header->source, my_ipt->port_rule.sport, IS_SPORT))
		{}
		else if (!Check_Port(udp_header->source, my_ipt->port_rule.sport, IS_SPORT))
		{}
		else
			return RULE_DOES_NOT_MATCH;  
	}
	if ((my_ipt->port_rule.bitmask & IS_DPORT) == IS_DPORT) {
		if (!Check_Port(tcp_header->dest, my_ipt->port_rule.dport, IS_DPORT))
		{printk(KERN_INFO "Destination port checking\n");}
		else if (!Check_Port(udp_header->dest, my_ipt->port_rule.dport, IS_DPORT))
		{}
		else
			return RULE_DOES_NOT_MATCH;  
	}

	my_ipt->packet_count++;			
	return RULE_MATCHES;
}

int Check_IP(const unsigned char *ip_addr1, const unsigned char *ip_addr2, const char *net_mask, const unsigned char bmask) {
	int action = RULE_DOES_NOT_MATCH;
	unsigned char accept_all_ip[] = {0x00,0x00,0x00,0x00};
	int *ip1, *ip2, *netmask;
	ip1 = (int *)ip_addr1,
	ip2 = (int *)ip_addr2;
	netmask = (int *)net_mask;
	
	do {
		if (!memcmp(ip1, ip2, IP_ADDR_LEN))	{					
			action = RULE_MATCHES;	
			break;
		}
		else {
			if(!memcmp(accept_all_ip, net_mask, IP_ADDR_LEN)) { 	
				action = RULE_MATCHES;
				break;
			}												
			else {				
				if(((*ip1)&(*netmask)) == ((*ip2)&(*netmask))) {   
					action = RULE_MATCHES;								
					break;
				}
				else {
					action = RULE_DOES_NOT_MATCH;							
					break;
				}
			}
		}
	}
	while(0);
	return action;
}			

int Check_Protocol(const unsigned short protocol1, const unsigned short protocol2, const unsigned char bmask) {
	int action = RULE_DOES_NOT_MATCH;
	do {		
		if(protocol2 == ALL_PROTOCOLS) {
			action = RULE_MATCHES;		
			break;
		}			
		else if(protocol1 == protocol2) {
			action = RULE_MATCHES;		
			break;
		}			
		else {
			action = RULE_DOES_NOT_MATCH;	
			break;
		}
	}
	while(0);
 	return action;				
}

int Check_Port(const unsigned short port1, const unsigned short port2, const unsigned char bmask) {
	int action = RULE_DOES_NOT_MATCH;	
	do {
		if(port1 == port2) {
			printk(KERN_INFO "Destination port matches\n");
			action = RULE_MATCHES;					
			break;
		}
	else { 
		action = RULE_DOES_NOT_MATCH;			
		break;
		}
	}
	while(0);
	return action;
}

void cleanup_fw_read_write_module(void) {
	remove_proc_entry("fw", NULL);
	vfree(my_ipt);
	printk(KERN_INFO "fw: fw read_write module unloaded successfully\n");
}

void cleanup_rule_match_module(void) {
	nf_register_net_hook(&init_net,&nfho_in);
	nf_register_net_hook(&init_net,&nfho_out);
	printk(KERN_INFO "fw: fw rule match module unloaded\n");
}

void my_cleanup_module(void) {
	cleanup_fw_read_write_module();
	cleanup_rule_match_module();
}

module_init(my_init_module);
module_exit(my_cleanup_module);
