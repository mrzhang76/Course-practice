#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include"validation.h"

#include"stmanagement.h" 
#include"clmanagement.h" 
#include"Linklist.h" 
#include"searchway.h" 
int validation(int,int); 						//合法性验证 
void classmenu(NodeB **TB,NodeA **TA);			//课程信息管理菜单 
void studentmenu(NodeB **TB,NodeA **TA);		//学生信息管理菜单 
void classqeury(NodeB **TB,NodeA **TA);			//课程信息显示  
void classmanagement(NodeB **TB,NodeA **TA);	//课程信息管理
void studentquery(NodeB **TB,NodeA **TA);		//学生信息查询 
void studentmanagement(NodeB **TB,NodeA **TA);	//学生信息管理 
void stresult(NodeB **TB,NodeA **TA);			//学生成绩查询 
void themenu(NodeB **TB,NodeA **TA);			//主菜单 


int main(void){
		NodeA *TA=NULL;//学生信息 
		NodeB *TB=NULL;//学生成绩 
		TA=initializeA();//学生信息初始化
		TB=initializeB();//学生成绩初始化 
		themenu(&TB,&TA);//主菜单 
		return 0; 
}
void themenu(NodeB **TB,NodeA **TA){
		int x=-1,y=2;
		printf("**************************************欢迎使用班级学生成绩管理系统**************************************\n");
		printf("*                                         请选择需要使用的功能                                         *\n");
		printf("*                                          1.课程信息管理                                              *\n");
		printf("*                                          2.学生信息管理                                              *\n");
		printf("*                                          3.学生成绩查询                                              *\n");
		printf("*                                          0.退  出                                                    *\n");
		printf("********************************************************************************************************\n");
		
	while(x==-1){
		 
		scanf("%d",&x);
		x=validation(x,3);//合法性验证 
		switch(x){
			case 1:system("cls"); classmenu(TB,TA);							break;//课程信息管理 
			case 2:system("cls"); studentmenu(TB,TA);						break;//学生信息管理 
			case 3:system("cls"); stresult(TB,TA);							break;//成绩查询 
			case 0: printf("再见");stdatewritten(TA);cldatewritten(TB);	exit(1);  //数据写入文件并退出 
			case -1:														break; 
		
		} 
	}

	 
} 
void classmenu(NodeB **TB,NodeA **TA){
		int x=-1; 
		printf("**********************************************课程信息管理**********************************************\n");
		printf("*                                         请选择需要使用的功能                                         *\n");
		printf("*                                          1.课程信息查询                                              *\n");
		printf("*                                          2.课程信息管理                                              *\n");
		printf("*                                          3.返回上一级                                                *\n");
		printf("*                                          0.退出                                                      *\n");
		printf("********************************************************************************************************\n");
		while(x==-1){
		 	scanf("%d",&x);
			x=validation(x,3);//合法性验证
			switch(x){
				case 1:system("cls");TraverseNodeB(*TB); themenu(TB,TA);		break; 
				case 2:system("cls"); classmanagement(TB,TA); themenu(TB,TA);	break;//课程查询 
				case 3:system("cls"); themenu(TB,TA);							break;//课程管理 
				case 0: printf("再见");stdatewritten(TA);cldatewritten(TB);	exit(1);  //数据写入文件并退出
				
		
		} 
	}
}
void studentmenu(NodeB **TB,NodeA **TA){
		int x=-1; 
		printf("**********************************************学生信息管理**********************************************\n");
		printf("*                                         请选择需要使用的功能                                         *\n");
		printf("*                                           1.学生信息查询                                             *\n");
		printf("*                                           2.学生信息管理                                             *\n");
		printf("*                                           3.返回上一级                                               *\n");
		printf("*                                           0.退出                                                     *\n");
		printf("********************************************************************************************************\n");
		while(x==-1){
		 	scanf("%d",&x);
			x=validation(x,3);//合法性验证 
			switch(x){
				case 1:system("cls");studentquery(TB,TA);					  	break;//学生信息查询 
				case 2:system("cls");studentmanagement(TB,TA);   			 	break;//学生信息管理 
				case 3:system("cls");themenu(TB,TA);						 	break;//主菜单 
				case 0:printf("再见");stdatewritten(TA);cldatewritten(TB);	exit(1);  //数据写入文件并退出 
				case -1:														break;
		
		} 
	}

}
void classmanagement(NodeB **TB,NodeA **TA){//课程信息管理 
	printf("**********************************************课程信息管理**********************************************\n");
	printf("*                                         请选择需要使用的功能                                         *\n");
	printf("*                                          1.课程信息添加                                              *\n");
	printf("*                                          2.课程信息修改                                              *\n");
	printf("*                                          3.课程信息删除                                              *\n");
	printf("*                                          4.返回上一级                                                *\n");
	printf("*                                          0.退出                                                      *\n");
	printf("********************************************************************************************************\n");
	int x=-1;
	while(x==-1){
	 	scanf("%d",&x);
			x=validation(x,4);//合法性验证 
			switch(x){
				case 1:system("cls"); classadd(TB);								break;//课程信息添加 
				case 2:system("cls"); classchange(TB);							break;//课程信息修改 
				case 3:system("cls"); classdel(TB);								break;//课程信息删除 
				case 4:system("cls"); classmenu(TB,TA);							break;//课程菜单 
				case 0: printf("再见");stdatewritten(TA);cldatewritten(TB);	exit(1);  //数据写入文件并退出
				case -1:														break;
		
}
}
}
void studentquery(NodeB **TB,NodeA **TA){//学生信息查询
	printf("**********************************************学生信息查询**********************************************\n");
	printf("*                                            1.加载全部信息                                            *\n");
	printf("*                                            2.按学号/姓名查询                                         *\n");
	printf("********************************************************************************************************\n");
	int i=0;
	scanf("%d",&i);
	if(i==1){
		system("cls");
		bool x=1;
		i=-1;
		
		printf("*******************************************正在加载学生信息*********************************************\n");
		x=TraverseNodeA(*TA);//学生信息加载 
		printf("********************************************************************************************************\n");
		while(i==-1){
			printf("键入0以结束浏览\n"); 
			scanf("%d",&i);
			i=validation(i,0);//合法性验证 
    		if(i==0){
				system("cls");
				themenu(TB,TA); //返回主菜单 
			}else i=-1;
		}
		
	} 
	else{
		system("cls");
		printf("*******************************************请输入学号或者姓名*******************************************\n"); 
		char a[11],c[11];
		scanf("%s",c);
		system("cls");
		printf("********************************************************************************************************\n");
		search(TA,c);//查询并显示 
		printf("********************************************************************************************************\n");
		int i=-1;
		while(i==-1){
			printf("键入0以结束浏览\n"); 
			scanf("%d",&i);
			i=validation(i,0);//进行合法性验证 
    		if(i==0){
				system("cls");
				themenu(TB,TA); //返回主菜单 
			}
			else 
				i=-1;
		}
	}
	studentmenu(TB,TA); //返回上一级菜单 
}
void studentmanagement(NodeB **TB,NodeA **TA){//学生信息管理 
	printf("*****************************************学生信息管理***************************************************\n");
	printf("*                                     请选择需要使用的功能                                             *\n");
	printf("*                                       1.学生信息添加                                                 *\n");
	printf("*                                       2.学生信息修改                                                 *\n");
	printf("*                                       3.学生信息删除                                                 *\n");
	printf("*                                       4.返回上一级                                                   *\n");
	printf("*                                       0.退出                                                         *\n");
	printf("********************************************************************************************************\n");
	int x=-1;
	while(x==-1){
	 	scanf("%d",&x);
			x=validation(x,4);//合法性验证 
			switch(x){
				case 1:system("cls"); newstudent(TB,TA);studentmanagement(TB,TA);	break;//学生信息添加 
				case 2:system("cls"); changestudent(TB,TA);studentmanagement(TB,TA);break;//学生信息修改 
				case 3:system("cls"); delstudent(TB,TA);studentmanagement(TB,TA);	break;//学生信息删除 
				case 4:system("cls"); studentmenu(TB,TA);							break;//学生管理菜单 
				case 0: printf("再见");stdatewritten(TA);cldatewritten(TB);		exit(1);  //将内存中的数据写入文件并关闭程序 
				case -1:break;
			}
		}
		
}

void stresult(NodeB **TB,NodeA **TA){//学生成绩查询 
	printf("*******************************************请输入学号或者姓名*******************************************\n"); 
	char c[11];
	scanf("%s",c);
	system("cls");
	printf("********************************************************************************************************\n");
	searchresult(TA,TB,c);	//调用成绩查找函数 
	printf("********************************************************************************************************\n");
	int i=-1;
	while(i==-1){
		printf("键入0以结束浏览\n"); 
		scanf("%d",&i);
		i=validation(i,0);
    	if(i==0){
			system("cls");
			themenu(TB,TA); //返回主菜单 
			}
		else 
			i=-1;
	}

}
