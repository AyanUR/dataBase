#include <stdio.h>
#include <string.h>
#include "simplelist.h"
#include "table.h"
#include "algoritmorelaciones.h"
#ifndef __ALGORITMOENTIDADES_H__
#define __ALGORITMOENTIDADES_H__
char compuestos[anidado][atribute][tamano];
int nb=0,np=0;
void whatIs(list **cab,list **table,char *line);
void showCompuestos(){
	int i,j;
        for(i=0;compuestos[i][0][0]!=0;i++){
		for(j=0;compuestos[i][j][0]!=0;j++)
			printf("|%s",compuestos[i][j]);
		printf("|\n");
	}
}
void listMultivalue(list **table,char *multivaluados,char akey[][tamano]){
	list *aux=NULL;
        char nametablemulti[tamano],attrmulti[tamano];
        int i=1;
        sprintf(nametablemulti,"%s_%s",akey[0],multivaluados);
        sprintf(attrmulti,"%s*",multivaluados);
        addElementLast(&aux,nametablemulti);
        addElementLast(&aux,attrmulti);
	while(akey[i++][0]!=0)
		addElementLast(&aux,akey[i-1]);
        addRowforTable(table,&aux);
}
void saveKey(list *cab,char key[][tamano]){
	int i=0;
	strcpy(key[i++],cab->data);
	while((cab=cab->next)!=NULL){
		if(strchr(cab->data,'*')!=NULL){
			memcpy(key[i++],cab->data,strlen(cab->data));
		}
	}
}
void multivaluados(list **cab,list **table,char *multivaluado){
	char akey[atribute][tamano];//atribute numero maximo de atributos llave
	bzero(akey,atribute*tamano*sizeof(char));
	saveKey(*cab,akey);
	listMultivalue(table,strtok(multivaluado,","),akey);
	while((multivaluado=strtok(NULL,","))!=NULL)
		listMultivalue(table,multivaluado,akey);
}
void putKey(list **cab,char *parofkey){
	list *p;
//	char id[tamano]={0};
//	sprintf(id,"*%d&",idkey++);
	for(p=*cab;p!=NULL&&strcasecmp(p->data,parofkey);p=p->next){;}
	if(p!=NULL)
		strcat(p->data,"*");
}
void serchCompuesto(list **cab,char *parofkey){
        int i,j;
        for(i=0;compuestos[i][0][0]!=0;i++){
                if(!strcasecmp(parofkey,compuestos[i][0])){//lo encontro
                        for(j=1;compuestos[i][j][0]!=0;j++){
                                if(!strcasecmp(compuestos[i][j],"next"))
                                        serchCompuesto(cab,compuestos[i+1][0]);
                                putKey(cab,compuestos[i][j]);
                        }
                        return;
                }
        }
        putKey(cab,parofkey);
}
void key(list **cab,char *llave){
	serchCompuesto(cab,strtok(llave,","));
	while((llave=strtok(NULL,","))!=NULL)
		serchCompuesto(cab,llave);
	bzero(compuestos,anidado*atribute*tamano*sizeof(char));
	nb=np=0;
}
void compuesto(list **cab,list **table,char *compusto){
	char *aux[atribute];
	int i=0;
	if(compuestos[nb][0][0]!=0){
		strcpy(compuestos[nb++][np],"next");
		np=0;
	}
	sscanf(compusto,"%[a-zA-Z0-9_]-%s",compuestos[nb][np++],compusto);
	aux[i++]=strtok(compusto,".");
	while((aux[i++]=strtok(NULL,"."))!=NULL){;}
	for(i=0;aux[i]!=NULL;i++){
		if(aux[i][0]!='c'&&aux[i][0]!='m'){//es derfivado o simple
			addElementLast(cab,strcpy(compuestos[nb][np++],strtok(&aux[i][2],",")));
			while((aux[i]=strtok(NULL,","))!=NULL)
				addElementLast(cab,strcpy(compuestos[nb][np++],aux[i]));
			continue;
		}
		if(aux[i][0]=='m'){
			multivaluados(cab,table,&aux[i][2]);
			continue;
		}
		compuesto(cab,table,&aux[i][2]);
	}
}
void simpleDerivado(list **cab,char *simple){
	addElementLast(cab,strtok(simple,","));	
	while((simple=strtok(NULL,","))!=NULL)
		addElementLast(cab,simple);
}
void whatIs(list **cab,list **table,char *line){
	switch(line[0]){
		case 'E':addElementLast(cab,&line[2]);break;
		case 's':simpleDerivado(cab,&line[2]);break;
		case 'd':simpleDerivado(cab,&line[2]);break;
		case 'k':key(cab,&line[2]);break;
		case 'c':compuesto(cab,table,&line[2]);break;
		case 'm':multivaluados(cab,table,&line[2]);break;
		case 'r':relacion(table,&line[2]);
		case ';':
			addRowforTable(table,cab);
			bzero(compuestos,anidado*atribute*tamano*sizeof(char));
			*cab=NULL;
		break;
	}
}
#endif
