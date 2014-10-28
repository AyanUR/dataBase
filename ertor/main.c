#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "algoritmoentidades.h"
#include "simplelist.h"
#define tamanoLine 4000
int main(int ari,char **arc){
	FILE *pf;
	char line[tamanoLine];
	entity *entitys=NULL;
	if(ari<2){
		fprintf(stderr,"\nejecute como $%s archivoEntidadRelacion",arc[0]);
		puts("");return 1;
	}
	if((pf=fopen(arc[1],"r"))==NULL){
		printf("\nerror al abrir %s",arc[1]);
		puts("");return 1;
	}
	while((fscanf(pf,"%s",line))!=EOF)
		whatIs(&entitys,line);
	showEntitys(entitys);
	fclose(pf);
	puts("");return 0;
}
