#ifndef __ASTRUCT_H__
#define __ASTRUCT_H__
#include<stdio.h>
#include<string.h>
struct course {
	char cid[20];	//课程代码 
	char name[20];	//课程名称 
	char credit[10];	//课程学分 
	
	
	
};//课程数据体
struct result {
	char id[20];				//学号
	char result[10]; 			//成绩 
	struct course classid;	//课程信息 
	
	
}; //成绩数据体
struct  student {
	bool tid=true;					//存储标识 
	char id[20];						//学号 
	char name[20];				//姓名 
	char gender[20];				//性别 
	char dob[20];					//出生日期 
	char profession[20];		//专业 
 
    
	
	
};//学生数据体 
 #endif
 //储存结构体
