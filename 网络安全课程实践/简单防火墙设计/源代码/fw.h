#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/vmalloc.h>
#include <linux/skbuff.h>
#include <linux/sched.h>
#include <linux/netfilter.h>
#include <linux/uaccess.h>	
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <linux/netfilter_ipv4.h>		

#define INBOUND         0
#define OUTBOUND        1

#define SRC_IPADDR      2
#define DEST_IPADDR     3
#define SRC_NET_MASK    4
#define DEST_NET_MASK   5
#define SRC_PORT        6
#define DEST_PORT       7
#define PROTOCOL        8

#define ACTION          9
#define BLOCK           10
#define UNBLOCK         11

#define DELETE          12
#define PRINT           13

#define PERMIT          14
#define ALLOW_ACCESS    15
#define REMOVE_ACCESS   16

#define MAX_NUM_OF_RULES        256               
#define IS_LAST_RULE            0x80              

#define UID_MAX                 256

#ifndef IP_ADDR_LEN
#define IP_ADDR_LEN             4                       
#endif

#ifndef IP_PROTOCOL 
#define IP_PROTOCOL     0x800                             
#endif

#ifndef TCP_PROTOCOL
#define TCP_PROTOCOL    0x06                                
#endif

#ifndef UDP_PROTOCOL
#define UDP_PROTOCOL    0x11                                 
#endif

#ifndef ICMP_PROTOCOL
#define ICMP_PROTOCOL   0x01                                 
#endif

#define ALL_PROTOCOLS   0xFF
#define IP_TYPE_PACKET  0x04

typedef struct port_rule{
        unsigned char  bitmask;
        unsigned short sport;
        unsigned short dport;
#define IS_SPORT 0x01
#define IS_DPORT 0x02
}my_port_rule;

typedef struct ip_rule{
        unsigned char  bitmask;
        unsigned char  sip[IP_ADDR_LEN];
        unsigned char  smask[IP_ADDR_LEN];
        unsigned char  dip[IP_ADDR_LEN];
        unsigned char  dmask[IP_ADDR_LEN];
        unsigned char  proto;                   
#define IS_SIP 0x01
#define IS_DIP 0x02
#define IS_SMASK 0x10
#define IS_DMASK 0x20
}my_ip_rule;

typedef struct my_ipt{        
        my_port_rule    port_rule;
        my_ip_rule      ip_rule;        
        unsigned char   hook_entry;
        unsigned char   rule_index;
        unsigned char   action;
        unsigned long   packet_count;
        unsigned int    uid;    
        unsigned short  dummy_byte;           
}my_iptable;                           

#define MAX_RULE_LENGTH 	PAGE_SIZE
#define MAX_RULES 			100
#define RULE_DOES_NOT_MATCH 1
#define RULE_MATCHES      	0
#define UID_MAX        		256

static struct 			proc_dir_entry *proc_entry;
static my_iptable 		fw_rules_table[MAX_RULES];
static my_iptable 		*my_ipt;
static struct 			nf_hook_ops nfho_in;
static struct 			nf_hook_ops nfho_out;
static unsigned char 	allowed_users[MAX_RULES];

static unsigned char	num_of_rules;
static unsigned int 	rule_index;
static unsigned int 	next_rule_ctr;

unsigned int fw_inbound_filter(void *priv,struct sk_buff *skb,const struct nf_hook_state *state);
unsigned int fw_outbound_filter(void *priv,struct sk_buff *skb,const struct nf_hook_state *state);
ssize_t fw_write(struct file *filp, const char __user *buff, size_t count, loff_t *ppos);
int Check_Rule(struct sk_buff *skb, my_iptable *my_ipt);
int Check_IP(const unsigned char *ip_addr1, const unsigned char *ip_addr2, const char *net_mask, const unsigned char bmask);
int Check_Protocol(const unsigned short protocol1, const unsigned short protocol2,	const unsigned char bmask);
int Check_Port(const unsigned short port1, const unsigned short port2, const unsigned char bmask);
int Delete_Rule(const my_iptable *my_ipt);

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.write = fw_write
};
