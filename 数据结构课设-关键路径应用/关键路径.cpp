#include <stdio.h>
#include <stdlib.h>
#define  MAX_VERTEX_NUM 20//��󶥵����
#define  VertexType int//�������ݵ�����
//typedef enum{false,true} bool;
//����ȫ�ֱ���������ߵ����翪ʼʱ��
VertexType ve[MAX_VERTEX_NUM];
//����ȫ�ֱ���������ߵ�����ʼʱ��
VertexType vl[MAX_VERTEX_NUM];
typedef struct ArcNode{
    int adjvex;						//�ڽӵ��������е�λ���±�
    struct ArcNode * nextarc;		//ָ����һ���ڽӵ��ָ��
    VertexType dut;
}ArcNode;

typedef struct VNode{
    VertexType data;				//�����������
    ArcNode * firstarc;				//ָ���ڽӵ��ָ��
}VNode,AdjList[MAX_VERTEX_NUM];		//�洢������ͷ��������

typedef struct {
    AdjList vertices;				//ͼ�ж��㼰���ڽӵ�����
    int vexnum,arcnum;				//��¼ͼ�ж������ͱ߻���
}ALGraph;
//�ҵ������Ӧ���ڽӱ������е�λ���±�
int LocateVex(ALGraph G,VertexType u){
    for (int i=0; i<G.vexnum; i++) {
        if (G.vertices[i].data==u) {
            return i;
        }
    }
    return -1;
}
//����AOE���������ڽӱ�
void CreateAOE(ALGraph **G){
    *G=(ALGraph*)malloc(sizeof(ALGraph));
   	printf("�������ͻ��·������<x,y>\n");
    scanf("%d,%d",&((*G)->vexnum),&((*G)->arcnum));
    int i=0,k=(*G)->arcnum;
    for (i=0; i<(*G)->vexnum; i++) {
        (*G)->vertices[i].data=i+1; //����������洢������ 
        (*G)->vertices[i].firstarc=NULL;//��ָ���ڽӵ��ָ������Ϊ�� 
    }
    
    VertexType initial,end,dut;
    for (int j=0; j<(*G)->arcnum; j++) {
    	printf("������������ϵ�Լ�·��Ȩֵ<x,y,z>(ʣ��%d��)\n",k--);
        scanf("%d,%d,%d",&initial,&end,&dut);
       
        ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=LocateVex(*(*G), end);//�ҵ������Ӧ���ڽӱ������е�λ���±�
        p->nextarc=NULL;//��ָ����һ���ڽӵ��ָ������Ϊ�� 
        p->dut=dut;
       
        int locate=LocateVex(*(*G), initial);
        p->nextarc=(*G)->vertices[locate].firstarc;
        (*G)->vertices[locate].firstarc=p;
    }
}
//�ṹ�嶨��ջ�ṹ
typedef struct stack{
    VertexType data;
    struct stack * next;
}stack;

stack *T;

//��ʼ��ջ�ṹ
void initStack(stack* *S){
    (*S)=(stack*)malloc(sizeof(stack));
    (*S)->next=NULL;
}
//�ж�ջ�Ƿ�Ϊ��
bool StackEmpty(stack S){
    if (S.next==NULL) {
        return true;
    }
    return false;
}
//��ջ����ͷ�巨���½����뵽������
void push(stack *S,VertexType u){
    stack *p=(stack*)malloc(sizeof(stack));
    p->data=u;
    p->next=NULL;
    p->next=S->next;
    S->next=p;
}
//��ջ������ɾ��������Ԫ����ͬʱ���ͷŸÿռ䣬�����ý���е�������ͨ����ַ��ֵ������i;
void pop(stack *S,VertexType *i){
    stack *p=S->next;
    *i=p->data;
    S->next=S->next->next;
    free(p);
}
//ͳ�Ƹ���������
void FindInDegree(ALGraph G,int indegree[]){
    //��ʼ�����飬Ĭ�ϳ�ʼֵȫ��Ϊ0
    for (int i=0; i<G.vexnum; i++) {
        indegree[i]=0;
    }
    //�����ڽӱ����ݸ������н���������洢�ĸ�����λ���±꣬��indegree������Ӧλ��+1
    for (int i=0; i<G.vexnum; i++) {
        ArcNode *p=G.vertices[i].firstarc;
        while (p) {
            indegree[p->adjvex]++;
            p=p->nextarc;
        }
    }
}

bool TopologicalOrder(ALGraph G){
    int indegree[G.vexnum];//������¼��������ȵ�����
    FindInDegree(G,indegree);//ͳ�Ƹ���������
    //����ջ�ṹ��������ʹ�õ�������
    stack *S;
    //��ʼ��ջ
    initStack(&S);
    for (int i=0; i<G.vexnum; i++) {
        ve[i]=0;
    }
    //���Ҷ�Ϊ0�Ķ��㣬��Ϊ��ʼ��
    for (int i=0; i<G.vexnum; i++) {
        if (!indegree[i]) {
            push(S, i);
        }
    }
    int count=0;
    //ջΪ��Ϊ������־
    while (!StackEmpty(*S)) {
        int index;
        //��ջ������¼ջ�б���Ķ��������ڽӱ������е�λ��
        pop(S,&index);
        //ѹջ��Ϊ����ߵ�����ʼʱ����׼��
        push(T, index);
        ++count;
        //���β��Ҹ��ö��������ӵĶ��㣬�����ʼ���Ϊ1����ɾ��ǰһ������󣬸ö������Ϊ0
        for (ArcNode *p=G.vertices[index].firstarc; p ; p=p->nextarc) {
           
            VertexType k=p->adjvex;
           
            if (!(--indegree[k])) {
                //�������Ϊ0����ջ
                push(S, k);
            }
            //����ߵ�Դ����·�����ȼ��ϱߵ�Ȩֵ�Ȼ����·�����Ȼ������͸���ve�����ж�Ӧλ�õ�ֵ�����ս���ʱ��ve�����д洢�ľ��Ǹ�������·�����ȡ�
            if (ve[index]+p->dut>ve[k]) {
                ve[k]=ve[index]+p->dut;
            }
        }
    }
    //���countֵС�ڶ�����������������ͼ�л�
    if (count<G.vexnum) {
        printf("��ͼ�л�·");
        return false;
    }
    return true;
}
//��������������ʱ�䲢��������ߵ����������ʼʱ��
void CriticalPath(ALGraph G){
    if (!TopologicalOrder(G)) {
        return ;
    }
    for (int i=0 ; i<G.vexnum ; i++) {
        vl[i]=ve[G.vexnum-1];
    }
    int j,k;
    while (!StackEmpty(*T)) {
        pop(T, &j);
        for (ArcNode* p=G.vertices[j].firstarc ; p ; p=p->nextarc) {
            k=p->adjvex;
            //����Vl���飬�ڳ�ʼ��ʱ��Vl������ÿ����Ԫ����18�����ÿ���ߵĻ��-�ߵ�Ȩֵ��Դ��ֵС���ͱ����С�ġ�
            if (vl[k]-p->dut<vl[j]) {
                vl[j] = vl[k]-p->dut;
            }
        }
    }
    for (j = 0; j < G.vexnum; j++) {
        for (ArcNode*p = G.vertices[j].firstarc; p ;p = p->nextarc) {
            k = p->adjvex;
            //����ߵ����翪ʼʱ��e[i],����ve��������ӦԴ��洢��ֵ
            int ee = ve[j];
            //����ߵ�����ʼʱ��l[i]�����ڻ����vl�����д洢��ֵ���ıߵ�Ȩֵ
            int el = vl[k]-p->dut;
            //�ж�e[i]��l[i]�Ƿ���ȣ������ȣ��ñ߾��ǹؼ������Ӧ����*��ǣ���֮���ߺ��û���
            char tag = (ee==el)?'*':' ';
           // printf(""); 
            printf("%3d%3d%3d���翪ʼʱ��%3d����ʼʱ��%3d�Ƿ�Ϊ�ؼ�·��%2c\n",j,k,p->dut,ee,el,tag);
        }
    }
}
int main(){
    ALGraph *G;
    CreateAOE(&G);//����AOE��
    initStack(&T);
    TopologicalOrder(*G);
    CriticalPath(*G);
    return  0;
}
