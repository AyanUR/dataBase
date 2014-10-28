#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __SIMPLELIST_H__
#define __SIMPLELIST_H__
#define size 111
typedef struct list{
	char data[size];
	struct list *next,*previous,*up,*down;
}list;
list *exist(list *cab,char *data){
	while(cab!=NULL){
		if(!strcasecmp(cab->data,data))
			return cab;
		cab=cab->next;
	}
	return NULL;
}
int requestMemory(list **nvo){
	if((*nvo=(list*)malloc(sizeof(list)))==NULL){
		printf("\nerror dont have more memory :( ");
		return 1;
	}
	(*nvo)->next=(*nvo)->previous=(*nvo)->up=(*nvo)->down=NULL;
	return 0;
}
void showList(list *cab){
	list *p=cab;
	for(p=cab;p!=NULL;p=p->next)
		printf("|%s",p->data);
	printf("|\n");
}
int addElementLast(list **cab,char *data){
	list *nvo,*p;
	if(requestMemory(&nvo))
		return 1;
	strcpy(nvo->data,data);
	if(*cab==NULL)
		*cab=nvo;
	else{
		for(p=*cab;p->next!=NULL;p=p->next){;}
		p->next=nvo;
		nvo->previous=p;
	}
	return 0;
}
int addElementFirst(list **cab,char *data){
	list *nvo;
	if(requestMemory(&nvo))
		return 1;
	strcpy(nvo->data,data);
	if(*cab!=NULL){
		(*cab)->previous=nvo;
		nvo->next=*cab;
	}
	*cab=nvo;
	return 0;
}
int addElementForIndex(list **cab,char *data,int index){
	int i;
	list *nvo,*p,*q;
	for(i=0,p=*cab;i<index&&p!=NULL;i++,p=p->next){;}
	if(p==NULL){
		printf("\nthe index %d is very long or the list is empty",index);
		return 1;
	}
	if(requestMemory(&nvo))
		return 1;
	strcpy(nvo->data,data);
	if((q=p->previous)!=NULL){
		q->next=nvo;
		nvo->previous=q;
	}
	nvo->next=p;
	p->previous=nvo;	
	return 0;
}
/*int removeElementForData(list **cab,char *data){
	list *p,*q,*r;
	for(p=*cab;p!=NULL&&!strcasecmp(p->data,data);p=p->next){;}
	if(p==NULL){
		printf("\ndata no exist in the list :( or the list is empty");
		return 1;
	}
	q=p->previous;
	r=p->next;
	q->next=r;
	r->previous=q;
	free(p);
	return 0;
}
int removeElementForIndex(list **cab,int index){
	int i;
	list *p,*r,*q;
	for(i=0,p=*cab;i<index&&p!=NULL;i++,p=p->next){;}
	if(p==NULL){
		printf("\nthe index is very long :( the index most big is %d or the list is empty",i);
		return 1;
	}
	q=p->previous;
	r=p->next;
	q->next=r;
	r->previous=q;
	free(p);
	return 0;
}*/
#endif
