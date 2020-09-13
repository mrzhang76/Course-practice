#include "app.h"
int main(int argc, char **argv) {
	const char* errstr;
	int opt;
	my_iptable *my_ipt = NULL;
	my_ipt = (my_iptable *)malloc(sizeof(my_iptable));
	memset(my_ipt, '\0', sizeof(my_iptable));	

	//在PROC虚拟文件系统下创建用于与防火墙内核程序通信规则的文件
	int fd = open("/proc/fw", O_WRONLY | O_APPEND );
	if (fd < 0) {
		fprintf(stderr, "%s\n", "Error: in opening /proc/fw file. Please check if it is registered in /proc\n");
		return 1;
	}
	else	
		printf("/proc/fw successfully opened for writing\n");

	//循环读取防火墙控制程序的启动参数并进行处理
	while(1) {
		//设置可以接受的参数
		static struct option long_options[] =	{							
			{"out",			no_argument,		&in_out_flag, 1},
			{"in",			no_argument,		&in_out_flag, 0},				
			{"proto",		required_argument,	0,  PROTOCOL},	
			{"srcip",		required_argument,	0, 	SRC_IPADDR},
			{"destip",		required_argument, 	0,  DEST_IPADDR},
			{"srcport",		required_argument, 	0, 	SRC_PORT},
			{"destport",    required_argument, 	0, 	DEST_PORT},
			{"srcnetmask",	required_argument, 	0, 	SRC_NET_MASK},
			{"destnetmask",	required_argument, 	0, 	DEST_NET_MASK},	
			{"delete",		required_argument,	0, 	DELETE},	
			{"action",		required_argument, 	0, 	ACTION},		
			{"help",		no_argument,		0,  HELP},			
			{0, 0, 0, 0}			
		};		

		int option_index = 0;

		//解析命令行参数
		if((opt = getopt_long(argc, argv, option_string, long_options, &option_index)) == -1)		
			break;

		//根据读取到的参数进行处理
		switch(opt) {
			//设定规则出入站
			case 0:
				if(long_options[option_index].flag != 0)		
					break;
			case SRC_IPADDR:                            	
			//设定规则源IP
				Set_IP(optarg, IS_SIP, my_ipt);				
				printf("Source IP address set\n");
				break;
			case DEST_IPADDR:
			//设定规则目的IP
				Set_IP(optarg, IS_DIP, my_ipt);				
				printf("Destination IP address set\n");
				break;
			case SRC_NET_MASK:
			//设定规则源网络掩码
				Set_Net_Mask(optarg, IS_SMASK, my_ipt);		
				printf("Source net mask set\n");
				break;
			case DEST_NET_MASK:
			//设定规则目的网络掩码
				Set_Net_Mask(optarg, IS_DMASK, my_ipt);		
				printf("Destination net mask set\n");
				break;
			case SRC_PORT:
			//设定规则源端口
				Set_Port(optarg, IS_SPORT, my_ipt);			
				printf("Source port set\n");
				break;
			case DEST_PORT:	
			//设定规则目的端口
				Set_Port(optarg, IS_DPORT, my_ipt);			
				printf("Destination port set\n");
				break;
			case PROTOCOL:
			//设定规则协议
				Set_Protocol(optarg, my_ipt);				
				printf("Protocol set\n");
				break;
			case ACTION:
			//设定规则活动性
				Set_Action(optarg, my_ipt);					
				printf("Action set\n");
				break;
			case DELETE:
			//删除已经设定的规则
				Delete_Rule(&fd, optarg, my_ipt);			
				printf("Delete option set\n");				
				write(fd, my_ipt, sizeof(my_iptable));
				return 0;     
			case HELP:
				help();
				return 0;
        	default:
				help();
        		break;        		
		}		
	}

	if(in_out_flag == 0) {
		Set_Hook_Entry(my_ipt, inbound);		
	}
	else if(in_out_flag == 1) {
		Set_Hook_Entry(my_ipt, outbound);		
	}	
	else {
		printf("Error: direction(whether inbound or outbound) not specified\nSyntax: --in for inbound, --out for outbound\n");		
	}
	
	write(fd, my_ipt, sizeof(my_iptable));	//将规则写入虚拟文件系统/proc/fw 
	close(fd);
	free(my_ipt);
	return 0;
} 	

void Set_Hook_Entry(my_iptable* my_ipt, char* optarg) {		//设定出入站规则
	char* str = optarg;	

	if(!strcmp(str, inbound)) {
		my_ipt->hook_entry = NF_IP_LOCAL_IN;
	}
	else if(!strcmp(str, outbound)) {
		my_ipt->hook_entry = NF_IP_LOCAL_OUT;
	}
	else {
		fprintf(stderr, "Bad Argument: should be either --in or --out\n");		
	}
	printf("Hook entry set for this rule: %d\n", my_ipt->hook_entry);	
}

void Set_IP(const char* optarg, unsigned char is_source, my_iptable* my_ipt) {	//设定规则IP
	struct in_addr *ip_addr = (struct in_addr *)malloc(sizeof(struct in_addr));	
	char* str = (char *)malloc(100 * sizeof(char));		
	Convert_To_Lower_Case(optarg, str);		//将参数转换为小写

	if (!inet_aton(str, ip_addr)) {		//将字符串IP地址转换为32位的网络序列IP地址
		fprintf(stderr, "Bad argument: Couldn't parse IP address\n");
	}	
	
	if (is_source == IS_SIP) {		
		memcpy(my_ipt->ip_rule.sip, (unsigned char *)ip_addr, IP_ADDR_LEN);
		my_ipt->ip_rule.bitmask |= IS_SIP; 		

	}
	else if (is_source == IS_DIP) {
		memcpy(my_ipt->ip_rule.dip, (unsigned char *)ip_addr, IP_ADDR_LEN);
		my_ipt->ip_rule.bitmask |= IS_DIP;			
	}
	else {
		fprintf(stderr, "Bad argument: in IP address\n");
	}	

	free(str);
	free(ip_addr);
}

void Set_Net_Mask(const char *optarg, unsigned char is_source, my_iptable *my_ipt) {	//设定规则掩码
	struct in_addr *netmask = (struct in_addr *)malloc(sizeof(struct in_addr));
	char* str1 = NULL;
	str1 = (char *)malloc(100 * sizeof(char));		
	Convert_To_Lower_Case(optarg, str1);
	printf("netmask is: %s\n", str1);
	if(!inet_aton(str1, netmask)) {
		fprintf(stderr, "Bad argument: Couldn't parse net mask\n");
	}
	
	if(is_source == IS_SIP) {
		memcpy(my_ipt->ip_rule.smask, (unsigned char *)netmask, IP_ADDR_LEN);
		my_ipt->ip_rule.bitmask |= IS_SIP;
	}
	else if(is_source == IS_DIP) {
		memcpy(my_ipt->ip_rule.dmask, (unsigned char *)netmask, IP_ADDR_LEN);
		my_ipt->ip_rule.bitmask |= IS_DIP;
	}
	else {
		fprintf(stderr, "Bad argument: in net mask\n");
	}
}

void Set_Port(const char *optarg, unsigned char is_source, my_iptable *my_ipt) {		//设定规则端口	
	unsigned short port = 0;	
	port = atoi(optarg);
	printf("port number: %u\n", port);
		
	if (is_source == IS_SPORT) {
		my_ipt->port_rule.sport = port; 
		my_ipt->port_rule.bitmask |= IS_SPORT;		
	}
	else if (is_source == IS_DPORT) {
		my_ipt->port_rule.dport = port; 
		my_ipt->port_rule.bitmask |= IS_DPORT;
	}
	else {
		fprintf(stderr, "Bad argument: in port number\n");
	}	
}

void Set_Protocol(const char *optarg, my_iptable *my_ipt) {		//设定规则协议
	unsigned char protocol = 0;
	char *str = (char *)malloc(100);	
	Convert_To_Lower_Case(optarg, str);		//将参数转换为小写	
		
	if (!strcmp("tcp", str)) {
		my_ipt->ip_rule.proto = TCP_PROTOCOL;
		my_ipt->ip_rule.bitmask |= IP_TYPE_PACKET;
	}
	else if (!strcmp("udp", str)) {
		my_ipt->ip_rule.proto = UDP_PROTOCOL;
		my_ipt->ip_rule.bitmask |= IP_TYPE_PACKET;
	}
	else if (!strcmp("icmp", str)) {
		my_ipt->ip_rule.proto = ICMP_PROTOCOL;
		my_ipt->ip_rule.bitmask |= IP_TYPE_PACKET;
	}
	else if (!strcmp("all", str)) {
		my_ipt->ip_rule.proto = ALL_PROTOCOLS;
		my_ipt->ip_rule.bitmask |= IP_TYPE_PACKET;
	}		
	else {
		fprintf(stderr, "Bad argument: in protocol\n");	
	}	
	free(str);
}

void Set_Action(const char *optarg, my_iptable *my_ipt) {		//设定规则活动性
	char* str = NULL;
	str = (char *)malloc(strlen(optarg)+1);
	Convert_To_Lower_Case(optarg, str);		//将参数转换为小写

	if(my_ipt->action != 0)
		my_ipt->action = 0;
	if(!strcmp("block", str))	
		my_ipt->action = my_ipt->action + BLOCK;
	else if (!strcmp("unblock", str)) 
		my_ipt->action = my_ipt->action + UNBLOCK;	
	else {
		fprintf(stderr, "Bad argument: in --action, should be BLOCK or UNBLOCK\n");
	}
	free(str);
}

void Delete_Rule(const int *fd, const char *optarg, my_iptable *my_ipt) {		//删除规则
	int index = atoi(optarg);
	if (index < 0) {
		fprintf(stderr, "minifirewall: rule number must be greater than 0\n");
		return ;
	} 
	my_ipt->rule_index = index;
	my_ipt->action = DELETE;	
}

void Convert_To_Lower_Case(const char *argv, char *str) {		// 将参数转换为小写
	int length = strlen(argv);
	strncpy(str, argv, length);
	str[length] = '\0';
	while(*str != '\0') {
		*str = tolower(*str);
		str ++;
	}
	return;
}

void help(void){
	printf("Set hook entry: --in --out \n");
	printf("Set protol: --protol ALL/TCP/UDP/ICMP\n");				
	printf("Set ip: --srcip --destip\n");
	printf("Set port: --destport --srcport\n");
	printf("Set netmask: --srcnetmask --destnetmask\n");
	printf("Set action: --action UNBLOCK/BLOCK \n");
	printf("Delete rule: --delete \n"); 		
	printf("Print rule: --print \n");
	printf("help: --help \n");			

}

