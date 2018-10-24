#include "graph.h"

//字符串中字母的数目
int letterLen(char *content){
	int nums = 0;
	size_t clen = strlen(content);
	
	for(size_t i = 0; i < clen; ++i){
		if( isalpha(content[i]) ){
			++nums;
		}
	}

	return nums;
}

//搜索符号在顶点列表中的位置
int searchFlagPos(HeadArray *vers,char flag,int len){
	int result = -1;
	
	for(int i = 0; i < len; ++i){
		if(vers[i].flag==flag){
			result = i;
			break;
		}
	}

	return result;
}

//插入边集
void InsertToLink(HeadArray *vers,int pos,NearLink *tar,int len){
	if( pos < len ){
		NearLink *curLink = vers[pos].next;

		for( ; curLink && curLink->next; curLink = curLink->next);
		if( !curLink ){
			vers[pos].next = tar;
		}else{
			curLink->next = tar;
		}
	}
}

//是否在数组中
int isInArray(int key,int *arrs,int len){
	int init = 0;

	for(int i = 0; i < len; ++i){
		if( arrs[i] == key ){
			init = 1;
			break;
		}
	}

	return init;
}

//获取新查找位置
int getHeadPos(HeadArray *vers,int curPos,int len){
	int rpos = -1,spos = 0;

	for( ; spos < len; ++spos){
		NearLink *curLink = vers[spos].next;

		for( ; curLink; curLink = curLink->next){
			if( curLink->head == curPos ){
				rpos = spos;
				break;
			}
		}

		if( rpos != -1 ){
			break;
		}
	}

	return rpos;
}

//获取下一个访问点位置
int getNextNodePos(HeadArray *vers,int curPos,int len,int *vted,int curlen){
	int pos = -1;
	NearLink *curLink = vers[curPos].next;

	if( !curLink ){
		if(	curlen >= 2 ){
			curLink = vers[vted[curlen-2]].next;
		}else{
			curPos = getHeadPos(vers,curPos,len);
			curLink = vers[curPos].next;
		}
	}

	for( ; curLink; curLink = curLink->next){
		if( !isInArray(curLink->head,vted,curlen) ){
			pos = curLink->head;
			break;
		}
	}

	if( pos == -1 ){
		curPos = getHeadPos(vers,curPos,len);
		pos = getNextNodePos(vers,curPos,len,vted,curlen);
	}

	return pos;
}

//未访问顶点入栈
void enStackGraph(HeadArray *vers,int curPos,int len,int *vted,int *curlen){
	NearLink *curLink = vers[curPos].next;

	for( ; curLink; curLink = curLink->next){
		if( !isInArray(curLink->head,vted,*curlen) ){
			vted[*curlen] = curLink->head;
			*curlen += 1;
		}
	}
}

//判断弧是不存在
int arcNotExist(HeadArray *vers,int tail,int head){
	int arcnot = 1;
	NearLink *curLink = vers[tail].next;
	
	for( ; curLink && curLink->next; curLink = curLink->next){
		if( curLink->head == head ){
			arcnot = 0;
			break;
		}
	}
	return arcnot;
}

//构建顶点图列表
void CreateHeadArr(Vertex *header,char *content){
	if( strlen(content) ){
		size_t clen = strlen(content),
			   start = 0;
		int curPos = 0,
			alphaLen = letterLen(content);
		
		header->vertexs = (HeadArray*)malloc(alphaLen * sizeof(HeadArray));
		if( header->vertexs ){
			header->length = alphaLen;
			for( ; start < clen; ++start){
				if( isalpha(content[start]) ){
					header->vertexs[curPos].flag = content[start];
					header->vertexs[curPos].next = NULL;
					++curPos;
				}
			}
		}
	}
}

//构建弧列表
void CreateArcArr(Vertex *header,char *content,int type){
	if( strlen(content) ){
		size_t clen = strlen(content),
			   start = 0;
		char fir = content[0],
			 sec = *(strchr(content,' ')+1);
		int weight = atoi((strchr(content,sec) + 1)),
			firPos = searchFlagPos(header->vertexs, fir, header->length),
			secPos = searchFlagPos(header->vertexs, sec, header->length);
		NearLink *firLink = (NearLink*)malloc(sizeof(NearLink)),
				 *secLink = (NearLink*)malloc(sizeof(NearLink));
		
		if( firLink && secLink ){
			firLink->head = firPos;
			secLink->head = secPos;
			firLink->next = secLink->next = NULL;
			firLink->weight = secLink->weight = 0;

			if( type >= 2 ){
				firLink->weight = secLink->weight = weight;
			}
			if( arcNotExist(header->vertexs,firPos,secPos) ){
				InsertToLink(header->vertexs, firPos, secLink, header->length);
			}
			if( (type==1||type==3)&&arcNotExist(header->vertexs,secPos,firPos) ){
				InsertToLink(header->vertexs, secPos, firLink, header->length);
			}
		}
	}
}

//遍历接连表
void visitVerLink(Vertex *header){
	for(int i = 0; i < header->length; ++i){
		NearLink *curLink = header->vertexs[i].next;

		printf("%c", header->vertexs[i].flag);
		for( ; curLink; curLink = curLink->next){
			printf("-->%d(%d)", curLink->head, curLink->weight);
		}
		printf("\n");
	}
}

//深度优先遍历接连表
void DFSvisitVerLink(Vertex *header,int startPos){
	int visited[header->length],
		curPos = 0;
	HeadArray *arrs = header->vertexs;

	visited[curPos++] = startPos;
	while( curPos < header->length ){
		if( curPos != header->length - 1){
			startPos = getNextNodePos(arrs,startPos,header->length,visited,curPos);
			visited[curPos++] = startPos;
		}else{
			for(int i = 0; i < header->length; ++i){
				if( !isInArray(i,visited,curPos) ){
					visited[curPos++] = i;
				}
			}
		}
	}

	for( int i = 0; i < header->length; ++i){
		if(i == 0){
			printf("%c", arrs[visited[i]].flag);
		}else{
			printf("-->%c", arrs[visited[i]].flag);
		}
	}
	printf("\n");
}

//广度优先遍历接连表
void BFSvisitVerLink(Vertex *header,int startPos){
	int visited[header->length],
        curPos = 0,
		prevPos = 0;
    HeadArray *arrs = header->vertexs;
	
	visited[curPos++] = startPos;
	while( curPos < header->length ){
		enStackGraph(arrs,visited[prevPos],header->length,visited,&curPos);
		++prevPos;
	}

	for( int i = 0; i < header->length; ++i){
		if(i == 0){
			printf("%c", arrs[visited[i]].flag);
		}else{
			printf("-->%c", arrs[visited[i]].flag);
		}
	}
	printf("\n");
}

int selectMin(Closedge *arrs,int len){
	int st = 0,rt = 0,mins;
	
	for( ; st < len; ++st){
		if(arrs[st].lowcost > 0){
			rt = st;
			mins = arrs[st].lowcost;
			break;
		}
	}

	for(st += 1; st < len; ++st){
		if( arrs[st].lowcost>0 && arrs[st].lowcost<mins ){
			rt = st;
			mins = arrs[st].lowcost;
		}
	}

	return rt;
}

void MiniSpanTree_PRIM(Vertex *header,int startPos){
	if( header && header->length ){
		int milen = header->length,
			curPos = 0,
			selectArr[milen];
		SelectArc *sas = (SelectArc*)malloc((milen-1) * sizeof(SelectArc));
		Closedge *cdge = (Closedge*)malloc(milen * sizeof(Closedge));

		if( sas && cdge ){
			selectArr[curPos] = startPos;
			for(int i = 0; i < milen; ++i){
				cdge[i].lowcost = -1;
			}
			
			for(NearLink *curLink = header->vertexs[startPos].next; curLink; curLink = curLink->next){
				cdge[curLink->head].vertexPos = startPos;
				cdge[curLink->head].lowcost = curLink->weight;
			}

			for(int i = 1; i < milen; ++i){
				int k = selectMin(cdge, milen);
				sas[curPos].head = startPos;
				sas[curPos].tail = k;
				selectArr[++curPos] = k;
				cdge[k].lowcost = 0;
				startPos = k;
				for(NearLink *curLink = header->vertexs[k].next; curLink; curLink = curLink->next){
					if( (!isInArray(curLink->head,selectArr,curPos+1) && cdge[curLink->head].lowcost==-1 ||  cdge[curLink->head].lowcost>0 && cdge[curLink->head].lowcost>curLink->weight) ){
						cdge[curLink->head].vertexPos = k;
						cdge[curLink->head].lowcost = curLink->weight;
					}
				}
			}

			//输出弧
			for(int i = 0; i < milen - 1; ++i){
				printf("%c-->%c\n", header->vertexs[sas[i].head].flag, header->vertexs[sas[i].tail].flag);
			}
		}
	}
}

//克鲁斯卡尔算法
void MiniSpanTree_Kruskal(Vertex *header){
}
