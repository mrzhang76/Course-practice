#ifndef __SEARCHWAY_H__//查询模块 
#define __SEARCHWAY_H__
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include"validation.h"

#include"stmanagement.h" 
#include"Linklist.h" 
int search(NodeA **TA,char c[11]); 					//学生查询
int searchresult(NodeA **TA,NodeB **TB,char c[11]);	//成绩查询 
int searchclass(NodeB **TB,char c[11]);				//课程查询 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
int search(NodeA **TA,char c[11]){					//学生查询 
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
		printf("查无此人\n");
 		return -1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
int searchresult(NodeA **TA,NodeB **TB,char c[11]){	//成绩查询 
	int flag=0;
	flag=search(TA,c);//查询是否有此学生信息 
	if(flag!=1){
		printf("查无此人，请核对\n");
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
int searchclass(NodeB **TB,char c[11]){	//课程查询 
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
