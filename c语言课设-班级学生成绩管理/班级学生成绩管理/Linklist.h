#ifndef __LINKLIST_H__		//����ṹ���� 
#define __LINKLIST_H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include"astruct.h"
#include"validation.h"
typedef struct NodeA *ElemTypeA;
typedef struct NodeA{
    struct student data;
    struct NodeA *next;
}NodeA,clinkListA;
														//ѧ����Ϣ�� 
typedef struct NodeB *ElemTypeB;
typedef struct NodeB{
    struct result data;
    struct NodeB *next;
}NodeB,clinkListB;
														//�γ̳ɼ���
													
ElemTypeA initializeA(void);					    	//���ļ�StudentInfo.txt����ѧ������
ElemTypeB initializeB(void);							//���ļ�"StudentScore.txt����ѧ���ɼ�
ElemTypeA CreateNodeA(NodeA *L,char temp[100]); 		//����ѧ����Ϣ�� 
ElemTypeB CreateNodeB(NodeB *T,char temp[100]); 		//�����γ̳ɼ��� 
void changest(char temp[100],NodeA **TA,char c[11]);	//ѧ����Ϣ�޸� 
bool TraverseNodeA(NodeA *L);				    		//����ѧ����Ϣ�� 
void newst(char temp[100],NodeA **L);        	    	//�½�ѧ����Ϣ 
void InsertNodeA(NodeA **TA,char temp[100]);			//�½ڵ����ѧ���� 
bool stdatewritten(NodeA T);							//ѧ����Ϣд���ļ� 
bool TraverseNodeB(NodeB *L);							//�����ɼ���Ϣ��
bool Traverse_NodeB(NodeB *L);							//�����γ���Ϣ��
void InsertNodeB(NodeB **TB,char temp[100]);			//�½ڵ����γ���
void changecl(char temp[100],NodeB **TA,char c[11]);	//�γ���Ϣ�޸�
bool cldatewritten(NodeB **T);							//�γ���Ϣд���ļ� 
//////////////////////////////////////////////////////////////////////////////////////////////////////
ElemTypeA initializeA(void){							//���ļ�StudentInfo.txt����ѧ������ 
	FILE *fp;
	NodeA *A=NULL;
	if((fp=fopen("StudentInfo.txt","r"))!=NULL){
		rewind(fp);		
		while((fgetc(fp))!=EOF){
			char temp[100];
			fgets(temp,100,fp);	
			A=CreateNodeA(A,temp);
		}
		fclose(fp);
		}
		else{
			printf("ȱ��studentInfo.txt\n");
			printf("��ʼ��ʧ��\n");
			sleep(3);
			exit(1); 
		}
		return A;
}
ElemTypeB initializeB(void){							//���ļ�"StudentScore.txt����ѧ���ɼ�
	FILE *fp;
	NodeB *B=NULL;
	if((fp=fopen("StudentScore.txt","r"))!=NULL){
		rewind(fp);
		while((fgetc(fp))!=EOF){
			
			char temp[100];
			fgets(temp,100,fp);	
			B=CreateNodeB(B,temp);
		
		}
		fclose(fp);
		}
		else{
			printf("ȱ��StudentScore.txt\n");
			printf("��ʼ��ʧ��\n");
			sleep(3);
			exit(1); 
			
		}
		return B;
}
ElemTypeA CreateNodeA(NodeA *L,char temp[100]){			//����ѧ����Ϣ��
	char tempa1[10],temp2[10],temp3[10],temp4[10],temp5[10];
	sscanf(temp, "%s %s %s %s %s ",tempa1,temp2,temp3,temp4,temp5);
	if(L==NULL){
   			L=(clinkListA *)malloc(sizeof(NodeA));
    		L->data.tid=false;
    		L->next=L;
    		NodeA *K;
    		K=(clinkListA *)malloc(sizeof(NodeA));
    		L->next=K;
    		K->next=L;
			strcpy(K->data.id,tempa1);
			strcpy(K->data.name,temp2);
			strcpy(K->data.gender,temp3);
			strcpy(K->data.dob,temp4);
			strcpy(K->data.profession,temp5);
			}
	else{
			clinkListA *pre;                     
      		pre = L; 
      		while(pre->next->data.tid!=NULL)
         		 pre = pre->next;               
         	clinkListA *p;                      
          	p = (clinkListA *)malloc(sizeof(NodeA));  
         	strcpy(p->data.id,tempa1);
			strcpy(p->data.name,temp2);
			strcpy(p->data.gender,temp3);
			strcpy(p->data.dob,temp4);
			strcpy(p->data.profession,temp5);
         	p->next = pre->next;
         	pre->next = p;
    
	}
	return L;
}
ElemTypeB CreateNodeB(NodeB *L,char temp[100]){		//�����γ̳ɼ���
	char temp1[20],temp2[20],temp3[20],temp4[20],temp5[20];
	sscanf(temp, "%s %s %s %s %s ",temp1,temp2,temp3,temp4,temp5);
	if(L==NULL){
			L=(clinkListB *)malloc(sizeof(NodeB));
    		L->data.result[0]=-1;
    		L->next=L;
    		NodeB *K;
    		K=(clinkListB *)malloc(sizeof(NodeB));
    		L->next=K;
    		K->next=L;
			strcpy(K->data.id,temp1);
			strcpy(K->data.classid.cid,temp2);
			strcpy(K->data.classid.name,temp3);
			strcpy(K->data.classid.credit,temp4);
			strcpy(K->data.result,temp5);
		}
	else{
			clinkListB *pre;                     
      		pre = L;
     		while(pre->next->data.result[0]!=-1)
         		 pre = pre->next;               
         	clinkListB *p;                      
          	p = (clinkListB *)malloc(sizeof(NodeB));  
         	strcpy(p->data.id,temp1);
			strcpy(p->data.classid.cid,temp2);
			strcpy(p->data.classid.name,temp3);
			strcpy(p->data.classid.credit,temp4);
			strcpy(p->data.result,temp5);
         	p->next = pre->next;
         	pre->next = p;
	}
return L;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TraverseNodeA(NodeA *L){									//����ѧ����Ϣ��
	if(L==NULL) return 0;
	L=L->next; 
	while(L->data.tid!=false){
			printf("%s %s %s %s %s\n",L->data.id,L->data.name,L->data.gender,L->data.dob,L->data.profession);
			L=L->next;
	} 
	return 1;
}
void newst(char temp[100],NodeA **L){							//�½�ѧ����Ϣ
	char temp1[10],temp2[10],temp3[10],temp4[10],temp5[10];
	sscanf(temp, "%s %s %s %s %s",temp1,temp2,temp3,temp4,temp5);
	puts(temp);
	InsertNodeA(L,temp);
}
void changest(char temp[100],NodeA **TA,char c[11]){			//ѧ����Ϣ�޸� 
	char temp1[10],temp2[10],temp3[10],temp4[10],temp5[20];
	sscanf(temp, "%s %s %s %s %s ",temp1,temp2,temp3,temp4,temp5);
	NodeA *tempA;
	tempA=(clinkListA *)malloc(sizeof(NodeA));
	tempA=*TA;
 	while(tempA->data.tid!=false){
		if(!strcmp(tempA->data.id,c)||!strcmp(tempA->data.name,c)){
			strcpy(tempA->data.id,temp1);
			strcpy(tempA->data.name,temp2);
			strcpy(tempA->data.gender,temp3);
			strcpy(tempA->data.dob,temp4);
			strcpy(tempA->data.profession,temp5);		}
		else{
			tempA=tempA->next; 
		}
		
	}

}
void InsertNodeA(NodeA **TA,char temp[100]){					//�½ڵ����ѧ����
	NodeA *T,*pre,*tempA;
	T=(clinkListA *)malloc(sizeof(NodeA));
	tempA=*TA;
	char temp1[10],temp2[10],temp3[10],temp4[10],temp5[10];
	sscanf(temp, "%s %s %s %s %s ",temp1,temp2,temp3,temp4,temp5);
	strcpy(T->data.id,temp1);
	strcpy(T->data.name,temp2);
	strcpy(T->data.gender,temp3);
	strcpy(T->data.dob,temp4);
	strcpy(T->data.profession,temp5);
	tempA=*TA;
	pre=tempA->next;
	tempA->next=T;
	T->next=pre;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TraverseNodeB(NodeB *L){	//�����ɼ���Ϣ��
	if(L==NULL) return 0;
	L=L->next; 
	char flag[20];
	while(L->next->data.result[0]!=-1){
			printf("%s\t %s\t %s\t%s\t%s\n",L->data.id,L->data.classid.cid,L->data.classid.name,L->data.classid.credit,L->data.result);
			L=L->next;
	} 
	int i=-1;
	while(i==-1){
		printf("����0�Խ������\n"); 
		scanf("%d",&i);
		i=validation(i,0);
    	if(i==0){
			system("cls");
			return 1;
			}
		else 
			i=-1;
	}
	return 1;
	 
}
bool TraverseNode_B(NodeB *L){	//�����γ���Ϣ
	if(L==NULL) return 0;
	L=L->next; 
	char flag[20];
	if(L->next->data.result[0]!=-1)
		strcpy(flag,L->data.id); 
		printf("�γ̱��\t�γ�����\tѧ��\t\n");
	while(L->next->data.result[0]!=-1&&!strcmp(flag,L->data.id)||!strcmp("000",L->data.id)){
			printf("%s\t %s\t %s\t\n",L->data.classid.cid,L->data.classid.name,L->data.classid.credit);
			L=L->next;
	} 
	while(!strcmp("000",L->data.id)){
			printf("%s\t %s\t %s\t\n",L->data.classid.cid,L->data.classid.name,L->data.classid.credit);
			L=L->next;
	} 
	int i=-1;
	while(i==-1){
		printf("����0�Խ������\n"); 
		scanf("%d",&i);
		i=validation(i,0);
    	if(i==0){
			system("cls");
			return 1;
			}
		else 
			i=-1;
	}
	return 1;
	 
}
void changecl(char temp[100],NodeB **TB,char c[11]){			//�γ���Ϣ�޸� 
	char temp1[20],temp2[20],temp3[20];
	puts(temp);
	NodeB *tempA;
	tempA=(clinkListB *)malloc(sizeof(NodeB));
	tempA=*TB;
	sscanf(temp, "%s %s %s  ",temp1,temp2,temp3);
	
	while(tempA->next->data.result[0]!=-1){
 
		if(!strcmp(tempA->data.classid.cid,c)||!strcmp(tempA->data.classid.name,c)){
			strcpy(tempA->data.classid.cid,temp1);
			strcpy(tempA->data.classid.name,temp2);
			strcpy(tempA->data.classid.credit,temp3);

		}
		
			tempA=tempA->next;
		
		
	}
}
void InsertNodeB(NodeB **TB,char temp[100]){	//�½ڵ����γ���
	NodeB *T,*pre,*tempA;
	T=(clinkListB *)malloc(sizeof(NodeB));
	tempA=*TB;
	char temp1[20],temp2[20],temp3[20],temp4[20]="newclass";
	sscanf(temp, "%s %s %s  ",temp1,temp2,temp3);
	strcpy(T->data.result,temp4);
	strcpy(T->data.classid.cid,temp1);
	strcpy(T->data.classid.name,temp2);
	strcpy(T->data.classid.credit,temp3);
	strcpy(T->data.result,"000");
	strcpy(T->data.id,"000");
	tempA=*TB;
	pre=tempA->next;
	tempA->next=T;
	T->next=pre;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
bool stdatewritten(NodeA **TA){									//ѧ����Ϣд���ļ� 
			if (TA == NULL)return 0;
			NodeA *T;
			T=*TA;
			T=T->next;
			FILE *fp;
			fp=fopen("StudentInfo.txt","w");
			while(T->data.tid!=false){
				char temp1[10],temp2[10],temp3[10],temp4[10],temp5[10],temp[100];
				strcpy(temp1,T->data.id);
				strcpy(temp2,T->data.name);
				strcpy(temp3,T->data.gender);
				strcpy(temp4,T->data.dob);
				strcpy(temp5,T->data.profession);
				sprintf(temp, "%s %s %s %s %s ",temp1,temp2,temp3,temp4,temp5);
				fprintf(fp,"\t");
				fputs(temp,fp);
				fprintf(fp,"\n");
				T=T->next;
			}
			fclose(fp);
	
}
bool cldatewritten(NodeB **TB){								//ѧ�γ���Ϣд���ļ� 
			if (TB == NULL)return 0;
			NodeB *T;
			T=*TB;
			T=T->next;
			FILE *fp;
			fp=fopen("StudentScore.txt","w");
			while(T->data.result[0]!=-1){
				char temp1[20],temp2[20],temp3[20],temp4[20],temp5[20],temp[100];
				strcpy(temp1,T->data.id);
				strcpy(temp2,T->data.classid.cid);
				strcpy(temp3,T->data.classid.name);
				strcpy(temp4,T->data.classid.credit);
				strcpy(temp5,T->data.result);

				sprintf(temp, "%s %s %s %s  %s",temp1,temp2,temp3,temp4,temp5);
				fprintf(fp,"\t");
				fputs(temp,fp);
				fprintf(fp,"\n");
				T=T->next;
			}
			fclose(fp);
	
} 
#endif
