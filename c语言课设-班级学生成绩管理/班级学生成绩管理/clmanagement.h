#ifndef __CLMANAGEMENT_H__
#define __CLMANAGEMENT_H__
//课程信息管理 
#include"astruct.h"
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include"Linklist.h"
#include"searchway.h" 

void classadd(NodeB **L);		//添加课程
void classchange(NodeB **L);	//修改课程
void classdel(NodeB **L);		//删除课程
 /////////////////////////////////////////////////////////////////////////////////////////////////////
void classadd(NodeB **L){		//添加课程
	printf("请输入想要添加的课程信息\n");
	char temp[100],temp1[20],temp2[20],temp3[10],y;
	printf("课程代码：\n");
	scanf("%s",temp1);
	printf("课程名称\n");
	scanf("%s",temp2);
	printf("课程学分：\n");
	scanf("%s",temp3);
	sprintf(temp,"%s %s %s ",temp1,temp2,temp3);
	puts(temp);
	int i,flag=0;
	flag=searchclass(L,temp1);//检查课程信息是否重复 
	flag=searchclass(L,temp2);
	if(flag==1){
		printf("课程信息重复，请检查\n");
		sleep(2);
		system("cls"); 
		classadd(L); 
	}
	printf("是否确认（y or n）\n");
	scanf("%s",&i);
	if(i=='y'){
		printf("正在添加\n");
		puts(temp); 
		InsertNodeB(L,temp);
		sleep(3);
		system("cls");
	}
	else{
		printf("已放弃添加，回到上一级菜单\n");
		sleep(3);
		system("cls");
		
	}
} 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void classchange(NodeB **L){			//课程信息修改 
		system("cls");
		printf("课程信息修改\n");
		printf("请输入课程名称或代码\n"); 
		char c[11];
		int flag = 0;
		scanf("%s",c);
		system("cls");
		flag=searchclass(L,c);
		if(flag!=0){
			int i=0;
			char temp[100],temp1[20],temp2[20],temp3[10];
			printf("将课程代码修改为：（无需修改请输入原值）\n");
			scanf("%s",temp1);
			printf("将课程名称修改为：（无需修改请输入原值）\n");
			scanf("%s",temp2);
			printf("将课程学分修改为：（无需修改请输入原值）\n");
			scanf("%s",temp3);
			sprintf(temp, "%s %s %s  ",temp1,temp2,temp3);
			puts(temp);
			printf("是否确认（1 or 0）\n");
			scanf("%d",&i);
			if(i==1){
				printf("正在修改\n");
				NodeB *tempA;
				tempA=(clinkListB *)malloc(sizeof(NodeB));
				tempA=*L;
				sscanf(temp, "%s %s %s  ",temp1,temp2,temp3);
				tempA=tempA->next;
				while(tempA->data.result[0]!=-1){
 					if(!strcmp(tempA->data.classid.cid,c)||!strcmp(tempA->data.classid.name,c)){
						strcpy(tempA->data.classid.cid,temp1);
						strcpy(tempA->data.classid.name,temp2);
						strcpy(tempA->data.classid.credit,temp3);
					}
					tempA=tempA->next;
				}
				printf("修改成功\n");
				sleep(3);
				system("cls");
			}
			else{
				printf("已放弃修改，回到上一级菜单\n");
				sleep(3);
				system("cls");
			}		
	}
	else{
		printf("并无此课程\n"); 
	}
	sleep(1);
	system("cls");
}
////////////////////////////////////////////////////////////////////////////////////////////////
void classdel(NodeB **L){//课程信息删除 
		system("cls");
		printf("课程信息删除\n");
		printf("请输入课程名称或代码\n"); 
		char c[11];
		scanf("%s",c);
		system("cls");
		int flag=0;
		flag=searchclass(L,c);//检查课程是否存在 
		int i=0;
		if(flag==1){
			printf("是否确认（1 or 0）\n");
			scanf("%d",&i);
			if(i==1){
				printf("正在删除\n");
				NodeB *tempA,*pre;
				tempA=(clinkListB*)malloc(sizeof(NodeB));
				tempA=*L;
				do{
					if(!strcmp(tempA->next->data.classid.cid,c)||!strcmp(tempA->next->data.classid.name,c)){
						pre=tempA->next->next;
						tempA->next=pre;	
						}
						tempA=tempA->next; 
					}while(tempA->data.result[0]!=-1);
				printf("删除成功\n");
			}
		} 
		else{
			printf("已放弃修改，回到上一级菜单\n");
			sleep(3);
			system("cls");
		}
		system("cls");
	}
 


#endif
