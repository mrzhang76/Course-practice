#ifndef __VALIDATION_H__
#define __VALIDATION_H__
#include<stdio.h>/ 
int validation(int x,int y);//合法性验证
int validation(int x,int y){
	if(0<=x&&x<=y)
		return x;
	else{
		 
		printf("请输入正确的字符\n");
	    getchar();
	    fflush(stdin);
		return x=-1;
	}
	   
}

 #endif
