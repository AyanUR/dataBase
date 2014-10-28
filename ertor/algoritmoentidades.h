#include <stdio.h>
#include <string.h>
#include "simplelist.h"
#ifndef __ALGORITMOENTIDADES_H__
#define __ALGORITMOENTIDADES_H__
#define maxMultivaluados 7
#define maxAnidacionesforCompuestos 7
entity *compuestos=NULL;
char multivaluados[maxMultivaluados][sizeNameAttribute];
int im=0;
void whatIs(entity **cab,char *line);
void passAttributesCompuestosForEntity(entity **entitys,char flag){
	int i;
	for(i=0;i<compuestos->attributeTop;i++){
		if(flag)
			strcat(compuestos->attribute[i],"*");
		addAttribute(entitys,compuestos->attribute[i]);
	}
	freeMemory(&compuestos);
}
void copyKey(entity **destino,entity *origen,char flag){//flat != 0 copia como llave else como atributeSimple
	int i;
	char temp[sizeNameAttribute];
	for(i=0;i<origen->attributeTop;i++){
		if(strchr(origen->attribute[i],'*')!=NULL){
			if(flag)
				addAttribute(destino,origen->attribute[i]);
			else{
				memcpy(temp,origen->attribute[i],(strlen(origen->attribute[i])-1)*sizeof(char));
				addAttribute(destino,temp);
			}
		}
	}
}
void putKey(entity **entitys,char *key){//entitys puede ser *entitys o *compuestos
	int i;
	if(existEntity(&compuestos,key)){
		passAttributesCompuestosForEntity(entitys,1);
	}else{
		for(i=0;i<(*entitys)->attributeTop;i++){
			if(!strcasecmp((*entitys)->attribute[i],key))
				strcat((*entitys)->attribute[i],"*");
		}
	}
}
void key(entity **entitys,char *key){
	putKey(entitys,strtok(key,","));
	while((key=strtok(NULL,","))!=NULL)
		putKey(entitys,key);
}
void compuesto(entity **cab,char *compuesto){//c-nombreAtriC-s-nombre,ap,am.k-boleta.c-nombrec-m-at))
	char nameAttributeCompuesto[sizeNameEntity],*aux[maxAnidacionesforCompuestos];
	int i=0;
	sscanf(compuesto,"%[a-zA-Z0-9_]-%s",nameAttributeCompuesto,compuesto);
	addEntityLast(&compuestos,nameAttributeCompuesto);
	aux[i++]=strtok(compuesto,".");
	while(i<maxAnidacionesforCompuestos&&(aux[i++]=strtok(NULL,"."))!=NULL){;}
	if(strtok(NULL,".")!=NULL)printf("\nanidationes for compuestos is full :( only accept %d",maxAnidacionesforCompuestos);
	for(i=0;aux[i]!=NULL;i++){
		whatIs(&compuestos,aux[i]);		
	}
}
void simpleDerivado(entity **entitys,char *simple){//s-atsod1,atsod2,...,atsodn
	addAttribute(entitys,strtok(simple,","));
	while((simple=strtok(NULL,","))!=NULL)
		addAttribute(entitys,simple);
}
void addAndFinish(entity **entitys,char *nameEntity){//add entity and attributes of compuestos and multivalue
	int i;
	entity *p=*entitys;
	char nameMultivaluados[2*sizeNameEntity]={0};
	while(compuestos!=NULL){
		passAttributesCompuestosForEntity(entitys,0);
	}
	for(i=0;i<im;i++){
		sprintf(nameMultivaluados,"%s of %s",p->name,multivaluados[i]);
		addEntityLast(entitys,nameMultivaluados);
		copyKey(entitys,p,1);
		addAttribute(entitys,strcat(multivaluados[i],"*"));
	}
	addEntityLast(entitys,nameEntity);
	im=0;	bzero(multivaluados,maxMultivaluados*sizeNameAttribute*sizeof(char));
}
void whatIs(entity **entitys,char *line){
	switch(line[0]){
		case 'E':addAndFinish(entitys,&line[2]);break;
		case 's':simpleDerivado(entitys,&line[2]);break;
		case 'd':simpleDerivado(entitys,&line[2]);break;
		case 'k':key(entitys,&line[2]);break;
		case 'c':compuesto(entitys,&line[2]);break;
		case 'm':		
				strcpy(multivaluados[im++],strtok(&line[2],",")); 
				while((line=strtok(NULL,","))!=NULL&&im<maxMultivaluados){strcpy(multivaluados[im++],line);}
				if(strtok(NULL,",")!=NULL)printf("\nthe multivaluados full only accept %d",maxMultivaluados);
		break;
		case 'r':relacion(table,&line[2]);
	}
}
#endif
