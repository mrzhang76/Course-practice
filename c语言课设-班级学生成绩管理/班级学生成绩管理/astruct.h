#ifndef __ASTRUCT_H__
#define __ASTRUCT_H__
#include<stdio.h>
#include<string.h>
struct course {
	char cid[20];	//�γ̴��� 
	char name[20];	//�γ����� 
	char credit[10];	//�γ�ѧ�� 
	
	
	
};//�γ�������
struct result {
	char id[20];				//ѧ��
	char result[10]; 			//�ɼ� 
	struct course classid;	//�γ���Ϣ 
	
	
}; //�ɼ�������
struct  student {
	bool tid=true;					//�洢��ʶ 
	char id[20];						//ѧ�� 
	char name[20];				//���� 
	char gender[20];				//�Ա� 
	char dob[20];					//�������� 
	char profession[20];		//רҵ 
 
    
	
	
};//ѧ�������� 
 #endif
 //����ṹ��
