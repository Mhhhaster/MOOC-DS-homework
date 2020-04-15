#define MaxVertexNum 10    /* 最大顶点数设为10 */
#define Infinity 65535        /* ∞设为双字节无符号整数的最大值65535*/
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<queue>
#define WeightType int
#define Vertex int
#define Datatype char //等同typedef char Datatype
bool BFSVisited[MaxVertexNum] = { false };//一开始所有的顶点都是未被访问过的
bool DFSVisited[MaxVertexNum] = { false };//分别用于BFS和DFS中指示结点是否被访问过
using namespace std;
//一个图类型GNode,指针类型MGraph,一个边类型ENode(方便插入),指针类型Edge
typedef struct GNode* PtrToGNode;
struct GNode {
	int Nv;//顶点数
	int Ne;//边数
	WeightType G[MaxVertexNum][MaxVertexNum];//不为零则代表有边
	//DataType Data[MaxVertexNum];//存顶点的数据，名字等
};
typedef PtrToGNode MGraph;
MGraph CreateGraph(int VertexNum)//初始化一个有VertexNum个顶点无边的图
{
	Vertex V, W;//边的序号从0开始
	MGraph Graph;
	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = Infinity;//初始化所有顶点间无边
	return Graph;
}
typedef struct ENode* PtrToENode;//边的结构
struct ENode {
	Vertex V1, V2;//一条边两个顶点
	WeightType Weight;//一个权重
};
typedef PtrToENode Edge;//Edge为边类型指针
void InsertEdge(MGraph Graph, Edge E)
{
	Graph->G[E->V1][E->V2] = E->Weight;//行指示出度
	Graph->G[E->V2][E->V1] = E->Weight;//此为无向图插入方式(i到j,j到i)，有向图则略去
}
MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	int Nv;
	scanf("%d", &Nv);
	Graph = CreateGraph(Nv);//Graph为一个有Nv个顶点无边的图
	scanf("%d", &(Graph->Ne));//输入图的边数
	if (Graph->Ne != 0)
	{
		E = (Edge)malloc(sizeof(struct ENode));
		for (int i = 0; i <Graph->Ne; i++)//从边0一直到Ne-1
		{
			scanf("%d%d", &E->V1, &E->V2);
			E->Weight = 1;
			InsertEdge(Graph, E);
		}
	}
	//Vertex V;
	//for (V = 0; V < Graph->Nv; V++)
	//scanf(" %c", &(Graph->Data[V]));
	return Graph;
}
void Visit(Vertex V)
{
	printf(" %d", V);
}
/* IsEdge(Graph, V, W)检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。  */
/* 此函数根据图的不同类型要做不同的实现，关键取决于对不存在的边的表示方法。*/
/* 例如对有权图, 如果不存在的边被初始化为INFINITY, 则函数实现如下:         */
void bFS(MGraph Graph, Vertex S, void (*Visit)(Vertex))//先进先出,参数：图指针，顶点S，
{   /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
	Vertex V, W;
	queue<Vertex>Q;//Queue Q;Q = CreateQueue(MaxSize); /* 创建空队列, MaxSize为外部定义的常数 */
	/* 访问顶点S：此处可根据具体访问需要改写 */
	Q.push(S);//AddQ(Q, S); /* S入队列 */
	while (!Q.empty()) //由于每一个顶点可能连多条边，所以不能这样入队
	{
		V = Q.front();  /* 弹出V */
		Q.pop();
		Visit(V);
		BFSVisited[V] = true; 
		for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
			/* 若W是V的邻接点并且未访问过 */
			if (!BFSVisited[W] && Graph->G[V][W] < Infinity) 
			{
				Q.push(W); /* W入队列 */
			}
	} /* while结束*/
}
void BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex))//先进先出,参数：图指针，顶点S，
{   
	Vertex V, W;
	queue<Vertex>Q;//Queue Q;Q = CreateQueue(MaxSize); /* 创建空队列, MaxSize为外部定义的常数 */
	/* 访问顶点S：此处可根据具体访问需要改写 */
	Visit(S);
	BFSVisited[S] = true;
	Q.push(S);//AddQ(Q, S); /* S入队列 */
	while (!Q.empty()) //在push的时候访问并标记，防止二次push（区别于树层序遍历中的pop后标记）
	{
		V = Q.front();  /* 弹出V */
		Q.pop();
		for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
			/* 若W是V的邻接点并且未访问过 */
			if (!BFSVisited[W] && Graph->G[V][W] < Infinity)
			{
				Q.push(W); /* W入队列 */
				Visit(W);
				BFSVisited[W] = true;
			}
	} /* while结束*/
}
void ListComponents_BFS(MGraph Graph)//遍历所有顶点，访问过则跳过
{
	Vertex i;
	for (i = 0; i < Graph->Nv; i++)//顶点从0到Nv-1
	{
		if (!BFSVisited[i])
		{
			printf("{");
			BFS(Graph, i, Visit);
			printf(" }");
			printf("\n");
		}
	}
}
void DFS(MGraph Graph, Vertex S, void (*Visit)(Vertex))//类似于树的先序遍历
{   /* 以S为出发点对邻接矩阵存储的图Graph进行DFS搜索 */
	Vertex W;
	/* 访问顶点S：此处可根据具体访问需要改写 */
	Visit(S);
	DFSVisited[S] = true;
	for (W = 0; W < Graph->Nv; W++)
		if (Graph->G[S][W] < Infinity && DFSVisited[W] == false)//
			DFS(Graph, W, Visit);
	return;
}
void ListComponents_DFS(MGraph Graph)
{
	for (Vertex i = 0; i < Graph->Nv; i++)
	{
		if (DFSVisited[i] == false)
		{
			printf("{");
			DFS(Graph, i, Visit);
			printf(" }");
			printf("\n");
		}
	}
}
int main()
{
	MGraph G = BuildGraph();
	ListComponents_DFS(G);
	ListComponents_BFS(G);
	return 0;
}