#ifndef _MYGRAPH_NET
#define _MYGRAPH_NET

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned short int unsint;
/***************************接连矩阵结构********************************/
typedef struct nearLink{
	int head;
	int weight;
	struct nearLink *next;
}NearLink;

typedef struct headArray{
	char flag;
	NearLink *next;
}HeadArray;

typedef struct Vertex{
	HeadArray *vertexs;
	int length;
}Vertex;

//被选中的弧的结构
typedef struct selectArc{
	int head;
	int tail;
}SelectArc;

//最小花费点
typedef struct closedge{
	int vertexPos;
	int lowcost;
}Closedge;

//构建顶点图列表
void CreateHeadArr(Vertex *header,char *content);

//构建弧列表
void CreateArcArr(Vertex *header,char *content,int type);

//遍历接连表
void visitVerLink(Vertex *header);

//深度优先遍历接连表
void DFSvisitVerLink(Vertex *header,int startPos);

//广度优先遍历接连表
void BFSvisitVerLink(Vertex *header,int startPos);

//普里姆算法
// 构建最小生成树
void MiniSpanTree_PRIM(Vertex *header,int startPos);
/*******************************end*************************************/
#endif
