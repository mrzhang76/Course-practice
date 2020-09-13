#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM 20	//��󶥵����
#define VertexType int	 	//������������
#define InfoType int 		//ͼ�л���߰�����Ϣ����
VertexType ve[MAX_VERTEX_NUM];//ȫ�ֱ���������ߵ����翪ʼʱ��
VertexType vl[MAX_VERTEX_NUM];//ȫ�ֱ���������ߵ�����ʼʱ��
typedef struct ArcNode{
	int adjvex;				//�ڽӵ��������е�λ���±�
	struct ArcNode *nextarc;//ָ����һ���ڽӵ��ָ�� 
	VertexType dut; 		//��Ϣ�� 
}ArcNode;
typedef struct VNode{
	VertexType data;		//�����������
	ArcNode * firstarc;		//ָ���ڽӵ��ָ�� 
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;		//ͼ�ж��㼰���ڽӵ�����
	int vexnum,arcnum;		//��¼ͼ�ж������ͱ߻��� 
	int kind; 				//��¼ͼ������ 
}ALGraph;
typedef struct stack{		//�ṹ�嶨��ջ�ṹ
    VertexType data;
    struct stack * next;
}stack;
stack *T;
void CreateAOE(ALGraph **G);		  			//����AOE���������ڽӱ� 
int LocateVex(ALGraph G,VertexType u); 			//���ض����Ӧ�ڽӱ�������λ���±�
void FindInDegree(ALGraph G,int indegree[]);    //ͳ�Ƹ���������
bool TopologicalOrder(ALGraph G);
void CriticalPath(ALGraph G);					//��������������ʱ�䲢��������ߵ����������ʼʱ��	
void initStack(stack* *S);						//��ʼ��ջ�ṹ
bool StackEmpty(stack S);						//�ж�ջ�Ƿ�Ϊ��
void push(stack *S,VertexType u);				//��ջ����
void pop(stack *S,VertexType *i);				//����ջ��Ԫ��	
//////////////////////////////////////////////////////////////////////////////////////////////
int main(){
	ALGraph *G;
    CreateAOE(&G);//����AOE��
    initStack(&T);
    TopologicalOrder(*G);
    CriticalPath(*G);
	return 0;
}			
////////////////////////////////////////////////////////////////////////////////////////////// 
void CreateAOE(ALGraph **G){					//����AOE���������ڽӱ� 
    *G=(ALGraph*)malloc(sizeof(ALGraph));
   	printf("�������ͻ��·������<x,y>\n");
    scanf("%d,%d",&((*G)->vexnum),&((*G)->arcnum));//��¼���������ͱ��� 
    int i=0,k=(*G)->arcnum;
    for (i=0; i<(*G)->vexnum; i++) {			//�����ڽӱ��ͷ��� 
        (*G)->vertices[i].data=i+1; 			//����������洢������ 
        (*G)->vertices[i].firstarc=NULL;		//��ָ���ڽӵ��ָ������Ϊ�� 
    }
    VertexType initial,end,dut;
    for (int j=0; j<(*G)->arcnum; j++) {		//���������Ӧ�ڽӱ� 
    	printf("������������ϵ�Լ�·��Ȩֵ<x,y,z>(ʣ��%d��)\n",k--);
        scanf("%d,%d,%d",&initial,&end,&dut);
        ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=LocateVex(*(*G), end);		//�ҵ�·���������Ӧ���ڽӱ������е�λ���±�
        p->nextarc=NULL;						//��ָ����һ���ڽӵ��ָ������Ϊ�� 
        p->dut=dut;
       
        int locate=LocateVex(*(*G), initial);	//�ҵ�·����ʼ������ڽӱ������е�λ���±� 
        p->nextarc=(*G)->vertices[locate].firstarc;//��ָ����һ���ڽӵ��ָ��ָ��·����ʼ�� 
        (*G)->vertices[locate].firstarc=p;		//��·����ʼ�����һ���ڽӵ�ָ��ָ��·����ֹ�� 
    }
} 
//////////////////////////////////////////////////////////////////////////////////////////////
int LocateVex(ALGraph G,VertexType u){			//�ҵ������Ӧ���ڽӱ������е�λ���±�
    for (int i=0; i<G.vexnum; i++) {
        if (G.vertices[i].data==u) {
            return i;
        }
    }
    return -1;
} 
////////////////////////////////////////////////////////////////////////////////////////////// 
void FindInDegree(ALGraph G,int indegree[]){	//ͳ�Ƹ���������
    for (int i=0; i<G.vexnum; i++) {			//��ʼ�����飬Ĭ�ϳ�ʼֵȫ��Ϊ0
        indegree[i]=0;
    }
    for (int i=0; i<G.vexnum; i++) {			//�����ڽӱ����ݸ������н���������洢�ĸ�����λ���±꣬��indegree������Ӧλ��+1
        ArcNode *p=G.vertices[i].firstarc;
        while (p) {
            indegree[p->adjvex]++;
            p=p->nextarc;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
bool TopologicalOrder(ALGraph G){				//���ͼ���Ƿ���ڻ�·��ͳ������ʱ��(��������)	 
    int indegree[G.vexnum];						//������¼��������ȵ�����
    FindInDegree(G,indegree);					//ͳ�Ƹ���������
 	stack *S;
   	initStack(&S);
    for (int i=0; i<G.vexnum; i++) {			//����ߵ����翪ʼʱ��������ʼ�� 
        ve[i]=0;
    }
    for (int i=0; i<G.vexnum; i++) {			//�����Ϊ��Ľ����ջ����ʼԴ�㣩 
        if (!indegree[i]) {
            push(S, i);
        }
    }
    int count=0;
     while (!StackEmpty(*S)) {					//���ջ��Ϊ�� 
        int index;
        pop(S,&index);							//��ջ������¼ջ�б���Ķ��������ڽӱ������е�λ��
        push(T, index);							//��ջT��Ϊ����ߵ�����ʼʱ����׼��
        ++count;
        for (ArcNode *p=G.vertices[index].firstarc; p ; p=p->nextarc) {
           VertexType k=p->adjvex;				//���β��Ҹ��ö��������ӵĶ��㣬�����ʼ���Ϊ1����ɾ��ǰһ������󣬸ö������Ϊ0 
           if (!(--indegree[k])) {				//������ڽӶ������Ϊ0���˽����ջ ��ȥ��ǰ���㣩 
               push(S, k);
            }
           if (ve[index]+p->dut>ve[k]) {		 //����ߵ�Դ����·�����ȼ��ϱߵ�Ȩֵ�Ȼ����·�����Ȼ������͸���ve�����ж�Ӧλ�õ�ֵ�����ս���ʱ��ve�����д洢�ľ��Ǹ�������·������
                ve[k]=ve[index]+p->dut;
            }
        }
    }
     
    if (count<G.vexnum) {						
        printf("��ͼ�л�·");
        return false;
    }
    return true;
} 
//////////////////////////////////////////////////////////////////////////////////////////////
void CriticalPath(ALGraph G){					//��������������ʱ�䲢��������ߵ����������ʼʱ��
    if (!TopologicalOrder(G)) {					//���ͼ���Ƿ���ڻ�·��ͳ������ʱ��(��������) 
        return ;
    }
    for (int i=0 ; i<G.vexnum ; i++) {
        vl[i]=ve[G.vexnum-1];
    }
    int j,k,flag=0,a;
    while (!StackEmpty(*T)) {
        pop(T, &j);								//��ջ 
        for (ArcNode* p=G.vertices[j].firstarc ; p ; p=p->nextarc) {
            k=p->adjvex;
           	if (vl[k]-p->dut<vl[j]) {			 //����Vl���飬���ÿ���ߵĻ��-�ߵ�Ȩֵ��Դ��ֵС���ͱ����С��
                vl[j] = vl[k]-p->dut;
            }
        }
    }
    printf("·����ʼ��\t\t·����ֹ��\t\t·��Ȩֵ\t\t���翪ʼʱ��\t����ʼʱ��\t�Ƿ�Ϊ�ؼ��\t\n");
    for (j = 0; j < G.vexnum; j++) {		 
        for (ArcNode*p = G.vertices[j].firstarc; p ;p = p->nextarc) {
        	flag=0;
            k = p->adjvex;
            int ee = ve[j];						//����ߵ����翪ʼʱ��e[i],����ve��������ӦԴ��洢��ֵ
            int el = vl[k]-p->dut;				//����ߵ�����ʼʱ��l[i]�����ڻ����vl�����д洢��ֵ���ߵ�Ȩֵ 
			if(ee==el){
            	flag=1;
            	
			}
       		printf("%3d\t\t\t%3d\t\t\t%3d\t\t\t%3d\t\t\t%3d\t\t\t%d\n",j+1,k+1,p->dut,ee,el,flag);
       		if(ee==el&&k+1==G.vexnum){
       			a=el+p->dut;
			   } 
        }
    }
    printf("����ʱ��Ϊ��%d",a);
}
///////////////////////////////////////////////////////////////////////////////////////////// 
void initStack(stack* *S){
    (*S)=(stack*)malloc(sizeof(stack));
    (*S)->next=NULL;
}
bool StackEmpty(stack S){
    if (S.next==NULL) {
        return true;
    }
    return false;
}
void push(stack *S,VertexType u){
    stack *p=(stack*)malloc(sizeof(stack));
    p->data=u;
    p->next=NULL;
    p->next=S->next;
    S->next=p;
}
void pop(stack *S,VertexType *i){
    stack *p=S->next;
    *i=p->data;
    S->next=S->next->next;
    free(p);
}
//////////////////////////////////////////////////////////////////////////////////////////// 

