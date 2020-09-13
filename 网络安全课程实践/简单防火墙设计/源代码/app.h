#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> 	
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <sys/socket.h>
#include <netinet/in.h>
//规则预定义
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
#define HELP           13

#define MAX_NUM_OF_RULES        256            
#define IS_LAST_RULE            0x80          
//钩子预定义
#define NF_IP_PRE_ROUTING       0
#define NF_IP_LOCAL_IN          1
#define NF_IP_FORWARD           2
#define NF_IP_LOCAL_OUT         3
#define NF_IP_POST_ROUTING      4

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

//规则结构体
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
        unsigned short  dummy_byte;
}my_iptable;
//参数
char option_string[] = {
        PROTOCOL,    	':', 	
	SRC_IPADDR,  	':',
	DEST_IPADDR,  	':', 
	SRC_PORT, 	':', 
	DEST_PORT, 	':',
	SRC_NET_MASK, 	':',
	DEST_NET_MASK, 	':', 		    			
	ACTION,       	':',
	DELETE,		':',
        HELP,           '\0'		    				            				    			
}; 

int in_out_flag = INT_MAX;	
char inbound[] = "in";
char outbound[] = "out";		    		

void Convert_To_Lower_Case(const char *argv, char *str);
void Set_Hook_Entry(my_iptable* my_ipt, char* optarg);
void Set_IP(const char* optarg, unsigned char is_source, my_iptable* my_ipt);
void Set_Net_Mask(const char *optarg, unsigned char is_source, my_iptable *my_ipt);
void Set_Port(const char *optarg, unsigned char is_source, my_iptable *my_ipt);
void Set_Protocol(const char *optarg, my_iptable *my_ipt);
void Set_Action(const char *optarg, my_iptable *my_ipt);
void Delete_Rule(const int *fd, const char *optarg, my_iptable *my_ipt);
void help(void);



