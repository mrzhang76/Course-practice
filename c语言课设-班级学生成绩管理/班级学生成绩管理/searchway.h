#ifndef __SEARCHWAY_H__//��ѯģ�� 
#define __SEARCHWAY_H__
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include"validation.h"

#include"stmanagement.h" 
#include"Linklist.h" 
int search(NodeA **TA,char c[11]); 					//ѧ����ѯ
int searchresult(NodeA **TA,NodeB **TB,char c[11]);	//�ɼ���ѯ 
int searchclass(NodeB **TB,char c[11]);				//�γ̲�ѯ 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
int search(NodeA **TA,char c[11]){					//ѧ����ѯ 
	NodeA *temp;
	temp=(clinkListA *)malloc(sizeof(NodeA));
	temp=*TA;
	temp=temp->next; 
	while(temp->data.tid!=false){
		if(!strcmp(temp->data.id,c)||!strcmp(temp->data.name,c)){
			printf("%s %s %s %s %s\n",temp->data.id,temp->data.name,temp->data.gender,temp->data.dob,temp->data.profession);
			return 1;
		}
		else{
			temp=temp->next;
		}
	}
		printf("���޴���\n");
 		return -1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
int searchresult(NodeA **TA,NodeB **TB,char c[11]){	//�ɼ���ѯ 
	int flag=0;
	flag=search(TA,c);//��ѯ�Ƿ��д�ѧ����Ϣ 
	if(flag!=1){
		printf("���޴��ˣ���˶�\n");
	}
	else{
		NodeB *temp;
		temp=(clinkListB *)malloc(sizeof(NodeB));
		temp=*TB;
		temp=temp->next; 
		while(temp->data.result[0]!=-1){
			if(!strcmp(temp->data.id,c)){
				printf("%s %s %s %s \n",temp->data.id,temp->data.classid.name,temp->data.classid.credit,temp->data.result);
			}
			temp=temp->next;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
int searchclass(NodeB **TB,char c[11]){	//�γ̲�ѯ 
	int flag=0;
	NodeB *temp;
	temp=(clinkListB *)malloc(sizeof(NodeB));
	temp=*TB;
	temp=temp->next; 
	while(temp->data.result[0]!=-1){
			if(!strcmp(temp->data.classid.name,c)||!strcmp(temp->data.classid.cid,c)){
				printf("%s\t%s\t%s\n",temp->data.classid.cid,temp->data.classid.name,temp->data.classid.credit);
				return 1;
			}
			temp=temp->next;
		}
	
}
#endif
