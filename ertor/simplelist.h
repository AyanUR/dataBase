#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __SIMPLELIST_H__
#define __SIMPLELIST_H__
#define sizeNameEntity 30
#define sizeNameAttribute 30
#define maxAttributesInEntity 17
typedef struct entity{
	int attributeTop;
	char name[sizeNameEntity];
	char attribute[maxAttributesInEntity][sizeNameAttribute];
	struct entity *next,*before;
}entity;
char existEntity(entity **cab,char *entidad){
	entity *p=*cab;
	for(;*cab!=NULL;*cab=(*cab)->before){
		if(!strcasecmp((*cab)->name,entidad))
			return 1;
	}
	*cab=p;
	return 0;
}
char memory(entity **nvo){
	if((*nvo=(entity *)malloc(sizeof(entity)))==NULL)
		return 1;
	(*nvo)->attributeTop=0;
	(*nvo)->next=(*nvo)->before=NULL;
	return 0;
}
void showEntitys(entity *cab){
	int i;
	for(;cab!=NULL;cab=cab->before){
		//printf("\nat=%d\tak=%d",cab->attributeTop,cab->keyTop);
		printf("\n\n%s\n",cab->name);
		for(i=0;i<cab->attributeTop;i++)
			printf("|%s",cab->attribute[i]);
	}
}
char addEntityLast(entity **cab,char *nameEntity){
//	printf("\n%s",nameEntity);
	entity *nvo;
	if(memory(&nvo)){
		printf("\nerror dont have more memory :(");
		return 1;
	}
	strcpy(nvo->name,nameEntity);
	if((*cab)!=NULL){
		(*cab)->next=nvo;
		nvo->before=*cab;
	}
	*cab=nvo;
	return 0;
}
void addAttribute(entity **entity,char *attribute){
//	printf("\n%s",attribute);
	if(*entity!=NULL){
		if((*entity)->attributeTop<maxAttributesInEntity)
			strcpy((*entity)->attribute[(*entity)->attributeTop++],attribute);
		else
			printf("\nthe attributes in this entity is full :S");
	}else{printf("\nthe list is empty");}
}
void freeMemory(entity **cab){
	showEntitys(*cab);
	entity *p=(*cab)->next,*q=(*cab)->before;
	free(*cab);
	*cab=NULL;
	if(p!=NULL){
		p->before=q;
		*cab=p;	
	}
	if(q!=NULL){
		q->next=p;
		*cab=q;
	}
	if(*cab!=NULL)
		for(;(*cab)->next!=NULL;*cab=(*cab)->next);
}
#endif
