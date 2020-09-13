#ifndef __STMANAGEMENT_H__//学生信息管理
#define __STMANAGEMENT_H__
#include"astruct.h" 
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include"Linklist.h"
#include"searchway.h" 

void newstudent(NodeB **TB,NodeA **TA);//学生信息添加
void changestudent(NodeB **TB,NodeA **TA);//学生信息修改 
void delstudent(NodeB &TB,NodeA &TA);//学生信息删除
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void newstudent(NodeB **TB,NodeA **TA){//学生信息添加 
	int flag1=0,flag2=0; 
	char i=0;
	char temp[100],temp1[10],temp2[10],temp3[10],temp4[10],temp5[10];
	printf("请输入需要添加学生的学号：\n");
	scanf("%s",temp1);
	printf("请输入需要添加学生的姓名：\n");
	scanf("%s",temp2);
	printf("请输入需要添加学生的性别：\n");
	scanf("%s",temp3);
	printf("请输入需要添加学生的出生日期：\n");
	scanf("%s",temp4);
	printf("请输入需要添加学生的专业：\n");
	scanf("%s",temp5);
	printf("将要添加的学生信息为：\n");
	printf("%s\n",temp1);
	printf("%s\n",temp2);
	printf("%s\n",temp3);
	printf("%s\n",temp4);
	printf("%s\n",temp5);
	printf("是否确认（y or n）\n");
	scanf("%s",&i);
	if(i=='y'){
		printf("正在添加\n");
		flag1=search(TA,temp1);//检查是否重复
 
		flag2=search(TA,temp2);//检查是否重复 
		if(flag1==1||flag2==0){
			printf("学号/姓名信息重复，请检查\n");
			sleep(3);
			system("cls");
		}else{
			sprintf(temp, "%s %s %s %s %s ",temp1,temp2,temp3,temp4,temp5);
			puts(temp);
			NodeA *T,*pre,*tempA;
			T=(clinkListA *)malloc(sizeof(NodeA));
			tempA=*TA;
			tempA=tempA->next;
			strcpy(T->data.id,temp1);
			strcpy(T->data.name,temp2);
			strcpy(T->data.gender,temp3);
			strcpy(T->data.dob,temp4);
			strcpy(T->data.profession,temp5);
			tempA=*TA;
			pre=tempA->next;
			tempA->next=T;
			T->next=pre;
			printf("添加成功\n");
			sleep(3);
			system("cls");
		}
	}
	else{
		printf("已放弃添加，回到上一级菜单\n");
		sleep(3);
		system("cls");
	}
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void changestudent(NodeB **TB,NodeA **TA){//学生信息修改 
		system("cls");
		printf("学生信息修改\n");
		printf("请输入学号或者姓名\n"); 
		char c[11];
		int flag = 0;
		int i=0;
		scanf("%s",c);
		system("cls");
		flag=search(TA,c);//检查是否存在 
		if(flag!=-1){
			char temp[100],temp1[10],temp2[10],temp3[10],temp4[10],temp5[20];
			printf("将学号修改为：（无需修改请输入原值）\n");
			scanf("%s",temp1);
			printf("将姓名修改为：（无需修改请输入原值）\n");
			scanf("%s",temp2);
			printf("将性别修改为：（无需修改请输入原值）\n");
			scanf("%s",temp3);
			printf("将出生日期修改为：（无需修改请输入原值）\n");
			scanf("%s",temp4);
			printf("将专业修改为：（无需修改请输入原值）\n");
			scanf("%s",temp5);
			printf("将要修改的学生信息为：（无需修改请输入原值）\n");
			sprintf(temp, "%s %s %s %s %s ",temp1,temp2,temp3,temp4,temp5);
			puts(temp);
			printf("是否确认（1 or 0）\n");//一个神奇的bug,需要研究 
			scanf("%d",&i);
			if(i==1){
				printf("正在修改\n");
				NodeA *tempA;
				tempA=(clinkListA *)malloc(sizeof(NodeA));
				tempA=*TA;
				tempA=tempA->next;
				while(tempA->data.tid!=false){
 					if(!strcmp(tempA->data.id,c)||!strcmp(tempA->data.name,c)){
 						strcpy(tempA->data.id,temp1);
						strcpy(tempA->data.name,temp2);
						strcpy(tempA->data.gender,temp3);
						strcpy(tempA->data.dob,temp4);
						strcpy(tempA->data.profession,temp5);
						printf("修改成功\n");
						break;
					}
					else{
						tempA=tempA->next; 
						}
				}
				sleep(3);
				system("cls");
			}
			else{
				printf("已放弃修改，回到上一级菜单\n");
				sleep(3);
				system("cls");
			}
	}
	sleep(1);
	system("cls");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void delstudent(NodeB **TB,NodeA **TA){//学生信息删除 
		system("cls");
		int flag=-1;
		printf("学生信息删除\n");
		printf("请输入学号或者姓名\n"); 
		char c[11];
		scanf("%s",c);
		system("cls");
		flag=search(TA,c);//检查是否存在 
		int i=0;
		if(flag==1){
			printf("将要删除的学生信息为：\n");
			search(TA,c);//显示信息 
			puts(c); 
			printf("是否确认（1 or 0）\n");
			scanf("%d",&i);
			puts(c); 
			if(i==1){
				printf("正在删除\n");
				NodeA *tempA,*pre;
				tempA=(clinkListA *)malloc(sizeof(NodeA));
				tempA=*TA;
				do{
					if(!strcmp(tempA->next->data.id,c)||!strcmp(tempA->next->data.name,c)){
						pre=tempA->next->next;
						tempA->next=pre;
						printf("删除成功\n"); 	
					}
					else{
						tempA=tempA->next; 
					}
				}while(tempA->data.tid!=false);
				sleep(3);
				system("cls");
			}
			else{
				printf("已放弃修改，回到上一级菜单\n");
				sleep(3);
				system("cls");
			}
		} 

}
 #endif
