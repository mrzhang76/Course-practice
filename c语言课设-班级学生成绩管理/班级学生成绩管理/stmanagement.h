#ifndef __STMANAGEMENT_H__//ѧ����Ϣ����
#define __STMANAGEMENT_H__
#include"astruct.h" 
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include"Linklist.h"
#include"searchway.h" 

void newstudent(NodeB **TB,NodeA **TA);//ѧ����Ϣ���
void changestudent(NodeB **TB,NodeA **TA);//ѧ����Ϣ�޸� 
void delstudent(NodeB &TB,NodeA &TA);//ѧ����Ϣɾ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void newstudent(NodeB **TB,NodeA **TA){//ѧ����Ϣ��� 
	int flag1=0,flag2=0; 
	char i=0;
	char temp[100],temp1[10],temp2[10],temp3[10],temp4[10],temp5[10];
	printf("��������Ҫ���ѧ����ѧ�ţ�\n");
	scanf("%s",temp1);
	printf("��������Ҫ���ѧ����������\n");
	scanf("%s",temp2);
	printf("��������Ҫ���ѧ�����Ա�\n");
	scanf("%s",temp3);
	printf("��������Ҫ���ѧ���ĳ������ڣ�\n");
	scanf("%s",temp4);
	printf("��������Ҫ���ѧ����רҵ��\n");
	scanf("%s",temp5);
	printf("��Ҫ��ӵ�ѧ����ϢΪ��\n");
	printf("%s\n",temp1);
	printf("%s\n",temp2);
	printf("%s\n",temp3);
	printf("%s\n",temp4);
	printf("%s\n",temp5);
	printf("�Ƿ�ȷ�ϣ�y or n��\n");
	scanf("%s",&i);
	if(i=='y'){
		printf("�������\n");
		flag1=search(TA,temp1);//����Ƿ��ظ�
 
		flag2=search(TA,temp2);//����Ƿ��ظ� 
		if(flag1==1||flag2==0){
			printf("ѧ��/������Ϣ�ظ�������\n");
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
			printf("��ӳɹ�\n");
			sleep(3);
			system("cls");
		}
	}
	else{
		printf("�ѷ�����ӣ��ص���һ���˵�\n");
		sleep(3);
		system("cls");
	}
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void changestudent(NodeB **TB,NodeA **TA){//ѧ����Ϣ�޸� 
		system("cls");
		printf("ѧ����Ϣ�޸�\n");
		printf("������ѧ�Ż�������\n"); 
		char c[11];
		int flag = 0;
		int i=0;
		scanf("%s",c);
		system("cls");
		flag=search(TA,c);//����Ƿ���� 
		if(flag!=-1){
			char temp[100],temp1[10],temp2[10],temp3[10],temp4[10],temp5[20];
			printf("��ѧ���޸�Ϊ���������޸�������ԭֵ��\n");
			scanf("%s",temp1);
			printf("�������޸�Ϊ���������޸�������ԭֵ��\n");
			scanf("%s",temp2);
			printf("���Ա��޸�Ϊ���������޸�������ԭֵ��\n");
			scanf("%s",temp3);
			printf("�����������޸�Ϊ���������޸�������ԭֵ��\n");
			scanf("%s",temp4);
			printf("��רҵ�޸�Ϊ���������޸�������ԭֵ��\n");
			scanf("%s",temp5);
			printf("��Ҫ�޸ĵ�ѧ����ϢΪ���������޸�������ԭֵ��\n");
			sprintf(temp, "%s %s %s %s %s ",temp1,temp2,temp3,temp4,temp5);
			puts(temp);
			printf("�Ƿ�ȷ�ϣ�1 or 0��\n");//һ�������bug,��Ҫ�о� 
			scanf("%d",&i);
			if(i==1){
				printf("�����޸�\n");
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
						printf("�޸ĳɹ�\n");
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
				printf("�ѷ����޸ģ��ص���һ���˵�\n");
				sleep(3);
				system("cls");
			}
	}
	sleep(1);
	system("cls");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void delstudent(NodeB **TB,NodeA **TA){//ѧ����Ϣɾ�� 
		system("cls");
		int flag=-1;
		printf("ѧ����Ϣɾ��\n");
		printf("������ѧ�Ż�������\n"); 
		char c[11];
		scanf("%s",c);
		system("cls");
		flag=search(TA,c);//����Ƿ���� 
		int i=0;
		if(flag==1){
			printf("��Ҫɾ����ѧ����ϢΪ��\n");
			search(TA,c);//��ʾ��Ϣ 
			puts(c); 
			printf("�Ƿ�ȷ�ϣ�1 or 0��\n");
			scanf("%d",&i);
			puts(c); 
			if(i==1){
				printf("����ɾ��\n");
				NodeA *tempA,*pre;
				tempA=(clinkListA *)malloc(sizeof(NodeA));
				tempA=*TA;
				do{
					if(!strcmp(tempA->next->data.id,c)||!strcmp(tempA->next->data.name,c)){
						pre=tempA->next->next;
						tempA->next=pre;
						printf("ɾ���ɹ�\n"); 	
					}
					else{
						tempA=tempA->next; 
					}
				}while(tempA->data.tid!=false);
				sleep(3);
				system("cls");
			}
			else{
				printf("�ѷ����޸ģ��ص���һ���˵�\n");
				sleep(3);
				system("cls");
			}
		} 

}
 #endif
