#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM 20	//最大顶点个数
#define VertexType int	 	//顶点数据类型
#define InfoType int 		//图中弧或边包含信息类型
VertexType ve[MAX_VERTEX_NUM];//全局变量，保存边的最早开始时间
VertexType vl[MAX_VERTEX_NUM];//全局变量，保存边的最晚开始时间
typedef struct ArcNode{
	int adjvex;				//邻接点在数组中的位置下标
	struct ArcNode *nextarc;//指向下一个邻接点的指针 
	VertexType dut; 		//信息域 
}ArcNode;
typedef struct VNode{
	VertexType data;		//顶点的数据域
	ArcNode * firstarc;		//指向邻接点的指针 
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;		//图中顶点及各邻接点数组
	int vexnum,arcnum;		//记录图中顶点数和边或弧数 
	int kind; 				//记录图的种类 
}ALGraph;
typedef struct stack{		//结构体定义栈结构
    VertexType data;
    struct stack * next;
}stack;
stack *T;
void CreateAOE(ALGraph **G);		  			//创建AOE网，构建邻接表 
int LocateVex(ALGraph G,VertexType u); 			//返回顶点对应邻接表数组中位置下标
void FindInDegree(ALGraph G,int indegree[]);    //统计各顶点的入度
bool TopologicalOrder(ALGraph G);
void CriticalPath(ALGraph G);					//求各顶点的最晚发生时间并计算出各边的最早和最晚开始时间	
void initStack(stack* *S);						//初始化栈结构
bool StackEmpty(stack S);						//判断栈是否为空
void push(stack *S,VertexType u);				//进栈操作
void pop(stack *S,VertexType *i);				//弹出栈顶元素	
//////////////////////////////////////////////////////////////////////////////////////////////
int main(){
	ALGraph *G;
    CreateAOE(&G);//创建AOE网
    initStack(&T);
    TopologicalOrder(*G);
    CriticalPath(*G);
	return 0;
}			
////////////////////////////////////////////////////////////////////////////////////////////// 
void CreateAOE(ALGraph **G){					//创建AOE网，构建邻接表 
    *G=(ALGraph*)malloc(sizeof(ALGraph));
   	printf("输入活动数和活动间路径个数<x,y>\n");
    scanf("%d,%d",&((*G)->vexnum),&((*G)->arcnum));//记录定顶点数和边数 
    int i=0,k=(*G)->arcnum;
    for (i=0; i<(*G)->vexnum; i++) {			//创建邻接表表头结点 
        (*G)->vertices[i].data=i+1; 			//顶点数据域存储顶点编号 
        (*G)->vertices[i].firstarc=NULL;		//将指向邻接点的指针设置为空 
    }
    VertexType initial,end,dut;
    for (int j=0; j<(*G)->arcnum; j++) {		//创建顶点对应邻接表 
    	printf("输入结点依赖关系以及路径权值<x,y,z>(剩余%d对)\n",k--);
        scanf("%d,%d,%d",&initial,&end,&dut);
        ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=LocateVex(*(*G), end);		//找到路径结束点对应在邻接表数组中的位置下标
        p->nextarc=NULL;						//将指向下一个邻接点的指针设置为空 
        p->dut=dut;
       
        int locate=LocateVex(*(*G), initial);	//找到路径起始结点在邻接表数组中的位置下标 
        p->nextarc=(*G)->vertices[locate].firstarc;//将指向下一个邻接点的指针指向路径起始点 
        (*G)->vertices[locate].firstarc=p;		//将路径起始点的下一个邻接点指针指向路径终止点 
    }
} 
//////////////////////////////////////////////////////////////////////////////////////////////
int LocateVex(ALGraph G,VertexType u){			//找到顶点对应在邻接表数组中的位置下标
    for (int i=0; i<G.vexnum; i++) {
        if (G.vertices[i].data==u) {
            return i;
        }
    }
    return -1;
} 
////////////////////////////////////////////////////////////////////////////////////////////// 
void FindInDegree(ALGraph G,int indegree[]){	//统计各顶点的入度
    for (int i=0; i<G.vexnum; i++) {			//初始化数组，默认初始值全部为0
        indegree[i]=0;
    }
    for (int i=0; i<G.vexnum; i++) {			//遍历邻接表，根据各链表中结点的数据域存储的各顶点位置下标，在indegree数组相应位置+1
        ArcNode *p=G.vertices[i].firstarc;
        while (p) {
            indegree[p->adjvex]++;
            p=p->nextarc;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
bool TopologicalOrder(ALGraph G){				//检查图中是否存在回路并统计最早时间(拓扑排序)	 
    int indegree[G.vexnum];						//创建记录各顶点入度的数组
    FindInDegree(G,indegree);					//统计各顶点的入度
 	stack *S;
   	initStack(&S);
    for (int i=0; i<G.vexnum; i++) {			//保存边的最早开始时间的数组初始化 
        ve[i]=0;
    }
    for (int i=0; i<G.vexnum; i++) {			//将入度为零的结点入栈（初始源点） 
        if (!indegree[i]) {
            push(S, i);
        }
    }
    int count=0;
     while (!StackEmpty(*S)) {					//如果栈不为空 
        int index;
        pop(S,&index);							//弹栈，并记录栈中保存的顶点所在邻接表数组中的位置
        push(T, index);							//入栈T，为求各边的最晚开始时间做准备
        ++count;
        for (ArcNode *p=G.vertices[index].firstarc; p ; p=p->nextarc) {
           VertexType k=p->adjvex;				//依次查找跟该顶点相链接的顶点，如果初始入度为1，当删除前一个顶点后，该顶点入度为0 
           if (!(--indegree[k])) {				//如果此邻接顶点入度为0，此结点入栈 （去除前顶点） 
               push(S, k);
            }
           if (ve[index]+p->dut>ve[k]) {		 //如果边的源点的最长路径长度加上边的权值比汇点的最长路径长度还长，就覆盖ve数组中对应位置的值，最终结束时，ve数组中存储的就是各顶点的最长路径长度
                ve[k]=ve[index]+p->dut;
            }
        }
    }
     
    if (count<G.vexnum) {						
        printf("该图有回路");
        return false;
    }
    return true;
} 
//////////////////////////////////////////////////////////////////////////////////////////////
void CriticalPath(ALGraph G){					//求各顶点的最晚发生时间并计算出各边的最早和最晚开始时间
    if (!TopologicalOrder(G)) {					//检查图中是否存在回路并统计最早时间(拓扑排序) 
        return ;
    }
    for (int i=0 ; i<G.vexnum ; i++) {
        vl[i]=ve[G.vexnum-1];
    }
    int j,k,flag=0,a;
    while (!StackEmpty(*T)) {
        pop(T, &j);								//出栈 
        for (ArcNode* p=G.vertices[j].firstarc ; p ; p=p->nextarc) {
            k=p->adjvex;
           	if (vl[k]-p->dut<vl[j]) {			 //构建Vl数组，如果每个边的汇点-边的权值比源点值小，就保存更小的
                vl[j] = vl[k]-p->dut;
            }
        }
    }
    printf("路径起始点\t\t路径终止点\t\t路径权值\t\t最早开始时间\t最晚开始时间\t是否为关键活动\t\n");
    for (j = 0; j < G.vexnum; j++) {		 
        for (ArcNode*p = G.vertices[j].firstarc; p ;p = p->nextarc) {
        	flag=0;
            k = p->adjvex;
            int ee = ve[j];						//求各边的最早开始时间e[i],等于ve数组中相应源点存储的值
            int el = vl[k]-p->dut;				//求各边的最晚开始时间l[i]，等于汇点在vl数组中存储的值减边的权值 
			if(ee==el){
            	flag=1;
            	
			}
       		printf("%3d\t\t\t%3d\t\t\t%3d\t\t\t%3d\t\t\t%3d\t\t\t%d\n",j+1,k+1,p->dut,ee,el,flag);
       		if(ee==el&&k+1==G.vexnum){
       			a=el+p->dut;
			   } 
        }
    }
    printf("所需时间为：%d",a);
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

