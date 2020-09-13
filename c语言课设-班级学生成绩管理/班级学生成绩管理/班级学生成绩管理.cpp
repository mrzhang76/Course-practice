#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include"validation.h"

#include"stmanagement.h" 
#include"clmanagement.h" 
#include"Linklist.h" 
#include"searchway.h" 
int validation(int,int); 						//�Ϸ�����֤ 
void classmenu(NodeB **TB,NodeA **TA);			//�γ���Ϣ����˵� 
void studentmenu(NodeB **TB,NodeA **TA);		//ѧ����Ϣ����˵� 
void classqeury(NodeB **TB,NodeA **TA);			//�γ���Ϣ��ʾ  
void classmanagement(NodeB **TB,NodeA **TA);	//�γ���Ϣ����
void studentquery(NodeB **TB,NodeA **TA);		//ѧ����Ϣ��ѯ 
void studentmanagement(NodeB **TB,NodeA **TA);	//ѧ����Ϣ���� 
void stresult(NodeB **TB,NodeA **TA);			//ѧ���ɼ���ѯ 
void themenu(NodeB **TB,NodeA **TA);			//���˵� 


int main(void){
		NodeA *TA=NULL;//ѧ����Ϣ 
		NodeB *TB=NULL;//ѧ���ɼ� 
		TA=initializeA();//ѧ����Ϣ��ʼ��
		TB=initializeB();//ѧ���ɼ���ʼ�� 
		themenu(&TB,&TA);//���˵� 
		return 0; 
}
void themenu(NodeB **TB,NodeA **TA){
		int x=-1,y=2;
		printf("**************************************��ӭʹ�ð༶ѧ���ɼ�����ϵͳ**************************************\n");
		printf("*                                         ��ѡ����Ҫʹ�õĹ���                                         *\n");
		printf("*                                          1.�γ���Ϣ����                                              *\n");
		printf("*                                          2.ѧ����Ϣ����                                              *\n");
		printf("*                                          3.ѧ���ɼ���ѯ                                              *\n");
		printf("*                                          0.��  ��                                                    *\n");
		printf("********************************************************************************************************\n");
		
	while(x==-1){
		 
		scanf("%d",&x);
		x=validation(x,3);//�Ϸ�����֤ 
		switch(x){
			case 1:system("cls"); classmenu(TB,TA);							break;//�γ���Ϣ���� 
			case 2:system("cls"); studentmenu(TB,TA);						break;//ѧ����Ϣ���� 
			case 3:system("cls"); stresult(TB,TA);							break;//�ɼ���ѯ 
			case 0: printf("�ټ�");stdatewritten(TA);cldatewritten(TB);	exit(1);  //����д���ļ����˳� 
			case -1:														break; 
		
		} 
	}

	 
} 
void classmenu(NodeB **TB,NodeA **TA){
		int x=-1; 
		printf("**********************************************�γ���Ϣ����**********************************************\n");
		printf("*                                         ��ѡ����Ҫʹ�õĹ���                                         *\n");
		printf("*                                          1.�γ���Ϣ��ѯ                                              *\n");
		printf("*                                          2.�γ���Ϣ����                                              *\n");
		printf("*                                          3.������һ��                                                *\n");
		printf("*                                          0.�˳�                                                      *\n");
		printf("********************************************************************************************************\n");
		while(x==-1){
		 	scanf("%d",&x);
			x=validation(x,3);//�Ϸ�����֤
			switch(x){
				case 1:system("cls");TraverseNodeB(*TB); themenu(TB,TA);		break; 
				case 2:system("cls"); classmanagement(TB,TA); themenu(TB,TA);	break;//�γ̲�ѯ 
				case 3:system("cls"); themenu(TB,TA);							break;//�γ̹��� 
				case 0: printf("�ټ�");stdatewritten(TA);cldatewritten(TB);	exit(1);  //����д���ļ����˳�
				
		
		} 
	}
}
void studentmenu(NodeB **TB,NodeA **TA){
		int x=-1; 
		printf("**********************************************ѧ����Ϣ����**********************************************\n");
		printf("*                                         ��ѡ����Ҫʹ�õĹ���                                         *\n");
		printf("*                                           1.ѧ����Ϣ��ѯ                                             *\n");
		printf("*                                           2.ѧ����Ϣ����                                             *\n");
		printf("*                                           3.������һ��                                               *\n");
		printf("*                                           0.�˳�                                                     *\n");
		printf("********************************************************************************************************\n");
		while(x==-1){
		 	scanf("%d",&x);
			x=validation(x,3);//�Ϸ�����֤ 
			switch(x){
				case 1:system("cls");studentquery(TB,TA);					  	break;//ѧ����Ϣ��ѯ 
				case 2:system("cls");studentmanagement(TB,TA);   			 	break;//ѧ����Ϣ���� 
				case 3:system("cls");themenu(TB,TA);						 	break;//���˵� 
				case 0:printf("�ټ�");stdatewritten(TA);cldatewritten(TB);	exit(1);  //����д���ļ����˳� 
				case -1:														break;
		
		} 
	}

}
void classmanagement(NodeB **TB,NodeA **TA){//�γ���Ϣ���� 
	printf("**********************************************�γ���Ϣ����**********************************************\n");
	printf("*                                         ��ѡ����Ҫʹ�õĹ���                                         *\n");
	printf("*                                          1.�γ���Ϣ���                                              *\n");
	printf("*                                          2.�γ���Ϣ�޸�                                              *\n");
	printf("*                                          3.�γ���Ϣɾ��                                              *\n");
	printf("*                                          4.������һ��                                                *\n");
	printf("*                                          0.�˳�                                                      *\n");
	printf("********************************************************************************************************\n");
	int x=-1;
	while(x==-1){
	 	scanf("%d",&x);
			x=validation(x,4);//�Ϸ�����֤ 
			switch(x){
				case 1:system("cls"); classadd(TB);								break;//�γ���Ϣ��� 
				case 2:system("cls"); classchange(TB);							break;//�γ���Ϣ�޸� 
				case 3:system("cls"); classdel(TB);								break;//�γ���Ϣɾ�� 
				case 4:system("cls"); classmenu(TB,TA);							break;//�γ̲˵� 
				case 0: printf("�ټ�");stdatewritten(TA);cldatewritten(TB);	exit(1);  //����д���ļ����˳�
				case -1:														break;
		
}
}
}
void studentquery(NodeB **TB,NodeA **TA){//ѧ����Ϣ��ѯ
	printf("**********************************************ѧ����Ϣ��ѯ**********************************************\n");
	printf("*                                            1.����ȫ����Ϣ                                            *\n");
	printf("*                                            2.��ѧ��/������ѯ                                         *\n");
	printf("********************************************************************************************************\n");
	int i=0;
	scanf("%d",&i);
	if(i==1){
		system("cls");
		bool x=1;
		i=-1;
		
		printf("*******************************************���ڼ���ѧ����Ϣ*********************************************\n");
		x=TraverseNodeA(*TA);//ѧ����Ϣ���� 
		printf("********************************************************************************************************\n");
		while(i==-1){
			printf("����0�Խ������\n"); 
			scanf("%d",&i);
			i=validation(i,0);//�Ϸ�����֤ 
    		if(i==0){
				system("cls");
				themenu(TB,TA); //�������˵� 
			}else i=-1;
		}
		
	} 
	else{
		system("cls");
		printf("*******************************************������ѧ�Ż�������*******************************************\n"); 
		char a[11],c[11];
		scanf("%s",c);
		system("cls");
		printf("********************************************************************************************************\n");
		search(TA,c);//��ѯ����ʾ 
		printf("********************************************************************************************************\n");
		int i=-1;
		while(i==-1){
			printf("����0�Խ������\n"); 
			scanf("%d",&i);
			i=validation(i,0);//���кϷ�����֤ 
    		if(i==0){
				system("cls");
				themenu(TB,TA); //�������˵� 
			}
			else 
				i=-1;
		}
	}
	studentmenu(TB,TA); //������һ���˵� 
}
void studentmanagement(NodeB **TB,NodeA **TA){//ѧ����Ϣ���� 
	printf("*****************************************ѧ����Ϣ����***************************************************\n");
	printf("*                                     ��ѡ����Ҫʹ�õĹ���                                             *\n");
	printf("*                                       1.ѧ����Ϣ���                                                 *\n");
	printf("*                                       2.ѧ����Ϣ�޸�                                                 *\n");
	printf("*                                       3.ѧ����Ϣɾ��                                                 *\n");
	printf("*                                       4.������һ��                                                   *\n");
	printf("*                                       0.�˳�                                                         *\n");
	printf("********************************************************************************************************\n");
	int x=-1;
	while(x==-1){
	 	scanf("%d",&x);
			x=validation(x,4);//�Ϸ�����֤ 
			switch(x){
				case 1:system("cls"); newstudent(TB,TA);studentmanagement(TB,TA);	break;//ѧ����Ϣ��� 
				case 2:system("cls"); changestudent(TB,TA);studentmanagement(TB,TA);break;//ѧ����Ϣ�޸� 
				case 3:system("cls"); delstudent(TB,TA);studentmanagement(TB,TA);	break;//ѧ����Ϣɾ�� 
				case 4:system("cls"); studentmenu(TB,TA);							break;//ѧ������˵� 
				case 0: printf("�ټ�");stdatewritten(TA);cldatewritten(TB);		exit(1);  //���ڴ��е�����д���ļ����رճ��� 
				case -1:break;
			}
		}
		
}

void stresult(NodeB **TB,NodeA **TA){//ѧ���ɼ���ѯ 
	printf("*******************************************������ѧ�Ż�������*******************************************\n"); 
	char c[11];
	scanf("%s",c);
	system("cls");
	printf("********************************************************************************************************\n");
	searchresult(TA,TB,c);	//���óɼ����Һ��� 
	printf("********************************************************************************************************\n");
	int i=-1;
	while(i==-1){
		printf("����0�Խ������\n"); 
		scanf("%d",&i);
		i=validation(i,0);
    	if(i==0){
			system("cls");
			themenu(TB,TA); //�������˵� 
			}
		else 
			i=-1;
	}

}
