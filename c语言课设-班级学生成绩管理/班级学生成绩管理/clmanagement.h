#ifndef __CLMANAGEMENT_H__
#define __CLMANAGEMENT_H__
//�γ���Ϣ���� 
#include"astruct.h"
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include"Linklist.h"
#include"searchway.h" 

void classadd(NodeB **L);		//��ӿγ�
void classchange(NodeB **L);	//�޸Ŀγ�
void classdel(NodeB **L);		//ɾ���γ�
 /////////////////////////////////////////////////////////////////////////////////////////////////////
void classadd(NodeB **L){		//��ӿγ�
	printf("��������Ҫ��ӵĿγ���Ϣ\n");
	char temp[100],temp1[20],temp2[20],temp3[10],y;
	printf("�γ̴��룺\n");
	scanf("%s",temp1);
	printf("�γ�����\n");
	scanf("%s",temp2);
	printf("�γ�ѧ�֣�\n");
	scanf("%s",temp3);
	sprintf(temp,"%s %s %s ",temp1,temp2,temp3);
	puts(temp);
	int i,flag=0;
	flag=searchclass(L,temp1);//���γ���Ϣ�Ƿ��ظ� 
	flag=searchclass(L,temp2);
	if(flag==1){
		printf("�γ���Ϣ�ظ�������\n");
		sleep(2);
		system("cls"); 
		classadd(L); 
	}
	printf("�Ƿ�ȷ�ϣ�y or n��\n");
	scanf("%s",&i);
	if(i=='y'){
		printf("�������\n");
		puts(temp); 
		InsertNodeB(L,temp);
		sleep(3);
		system("cls");
	}
	else{
		printf("�ѷ�����ӣ��ص���һ���˵�\n");
		sleep(3);
		system("cls");
		
	}
} 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void classchange(NodeB **L){			//�γ���Ϣ�޸� 
		system("cls");
		printf("�γ���Ϣ�޸�\n");
		printf("������γ����ƻ����\n"); 
		char c[11];
		int flag = 0;
		scanf("%s",c);
		system("cls");
		flag=searchclass(L,c);
		if(flag!=0){
			int i=0;
			char temp[100],temp1[20],temp2[20],temp3[10];
			printf("���γ̴����޸�Ϊ���������޸�������ԭֵ��\n");
			scanf("%s",temp1);
			printf("���γ������޸�Ϊ���������޸�������ԭֵ��\n");
			scanf("%s",temp2);
			printf("���γ�ѧ���޸�Ϊ���������޸�������ԭֵ��\n");
			scanf("%s",temp3);
			sprintf(temp, "%s %s %s  ",temp1,temp2,temp3);
			puts(temp);
			printf("�Ƿ�ȷ�ϣ�1 or 0��\n");
			scanf("%d",&i);
			if(i==1){
				printf("�����޸�\n");
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
				printf("�޸ĳɹ�\n");
				sleep(3);
				system("cls");
			}
			else{
				printf("�ѷ����޸ģ��ص���һ���˵�\n");
				sleep(3);
				system("cls");
			}		
	}
	else{
		printf("���޴˿γ�\n"); 
	}
	sleep(1);
	system("cls");
}
////////////////////////////////////////////////////////////////////////////////////////////////
void classdel(NodeB **L){//�γ���Ϣɾ�� 
		system("cls");
		printf("�γ���Ϣɾ��\n");
		printf("������γ����ƻ����\n"); 
		char c[11];
		scanf("%s",c);
		system("cls");
		int flag=0;
		flag=searchclass(L,c);//���γ��Ƿ���� 
		int i=0;
		if(flag==1){
			printf("�Ƿ�ȷ�ϣ�1 or 0��\n");
			scanf("%d",&i);
			if(i==1){
				printf("����ɾ��\n");
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
				printf("ɾ���ɹ�\n");
			}
		} 
		else{
			printf("�ѷ����޸ģ��ص���һ���˵�\n");
			sleep(3);
			system("cls");
		}
		system("cls");
	}
 


#endif
