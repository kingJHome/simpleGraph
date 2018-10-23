#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void replaceNewLine(char *chars);

int main(int argc,char *argv[]){
	FILE *fp = fopen("graph.txt","r");

	if( fp ){
		int type = 0;
		char *content = NULL;
		size_t rlen = 0;
		Vertex aver = {NULL,0};
		
		//读文件内容
		while( getline(&content, &rlen, fp) != -1 ){
			rlen = 0;
			
			replaceNewLine(content);
			char *target = strchr(content,':') + 1;
			if( strstr(content,"type") == content ){
				type = atoi(target);
			}else if( strstr(content,"Vertex") == content ){
				CreateHeadArr(&aver,target);
			}else if( strstr(content,"Arc") == content ){
				CreateArcArr(&aver,target,type);
			}
		}

		fclose(fp);
		visitVerLink(&aver);
	}

	return 0;
}

void replaceNewLine(char *chars){
	size_t clen = strlen(chars);

	chars[clen-1] = '\0';
}
