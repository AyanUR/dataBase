#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef __BASIC_H__
#define __BASIC_H__
#define size 70
typedef struct base{
	char attrval[size];
	struct base *sig,*ant,*up,*down;
}base;
int k=0;
void openFile(FILE **file,char *name,char *mode){
	if((*file=fopen(name,mode))==NULL){
		printf("\nerror al abrir el archivo %s",name);
		exit(-1);
	}
}
void createList(base **cab,char *value){
	base *nvo,*p;
	nvo=(base *)malloc(sizeof(base));
	strcpy(nvo->attrval,value);
	nvo->ant=nvo->sig=nvo->up=nvo->down=NULL;
	if(*cab==NULL)
		*cab=nvo;
	else{
		for(p=*cab;p->sig!=NULL;p=p->sig){;}
		p->sig=nvo;
		nvo->ant=p;
	}
}
void createTable(base **cab,base *aux){
	base *p;
	for(p=(*cab)->sig;p->down!=NULL;p=p->down){;}
	for(;p!=NULL;p=p->sig,aux=aux->sig){
		p->down=aux;
		aux->up=p;
	}
}
int readFile(FILE **file,base **cab,char *whatfile){
	char lector[size];
	base *aux=NULL,*p;
	k=0;
	while(!feof(*file)){
		fscanf(*file,"%s\n",lector);
		if(!strcmp(lector,";")){
			createTable(cab,aux);
			aux=NULL;
			continue;
		}
		k++;
		createList(&aux,lector);
	}
	if(!strcmp(whatfile,"atributes.dat"))
		*cab=aux;//para los atributos
	if(!strcmp(whatfile,"key.dat")){
		for(p=aux;p->sig!=NULL;p=p->sig){;}//para yaves
		p->sig=*cab;
		(*cab)->ant=p;
	}
	return k;
}
void printaux(char *cad){
	int i;
	printf("%s",cad);
	for(i=strlen(cad);i<15;i++)
		printf(" ");
}
void printTable(base **cab){
	base *p,*q;
	for(p=(*cab)->sig;p!=NULL;p=p->down){
		for(q=p;q!=NULL;q=q->sig){
			printaux(q->attrval);
		}
		printf("\n");
	}
}
#endif
