#ifndef _MYGRAPH_NET
#define _MYGRAPH_NET

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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

//构建顶点图列表
void CreateHeadArr(Vertex *header,char *content);

//构建弧列表
void CreateArcArr(Vertex *header,char *content,int type);

//遍历接连表
void visitVerLink(Vertex *header);
/*******************************end*************************************/

/***************************十字链表结构********************************/
/*******************************end*************************************/
#endif
