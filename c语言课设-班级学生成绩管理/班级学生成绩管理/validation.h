#ifndef __VALIDATION_H__
#define __VALIDATION_H__
#include<stdio.h>/ 
int validation(int x,int y);//�Ϸ�����֤
int validation(int x,int y){
	if(0<=x&&x<=y)
		return x;
	else{
		 
		printf("��������ȷ���ַ�\n");
	    getchar();
	    fflush(stdin);
		return x=-1;
	}
	   
}

 #endif
