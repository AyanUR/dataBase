#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define nameSize 70
typedef struct attrVal{
	char name[nameSize];
	struct attrVal *sig,*ant,*up,*down;
}attrVal;
attrVal *nvo,*p,*q,*r,*cabaux=NULL;
int k;
FILE *atributes,*values;
char temp[nameSize];
void addValue(attrVal **cab,char *temp){
	nvo=(attrVal*)malloc(sizeof(attrVal));
	strcpy(nvo->name,temp);
	nvo->sig=nvo->down=NULL;
	if(cabaux==NULL){
		cabaux=nvo;
		cabaux->ant=NULL;
	}else{
		for(q=cabaux;q->sig!=NULL;q=q->sig){;}
		q->sig=nvo;
		nvo->ant=q;	
	}
	nvo->up=p;
	p->down=nvo;
	p=p->sig;	
}
void addKey(attrVal **cab,char *temp){
	nvo=(attrVal*)malloc(sizeof(attrVal));
	strcpy(nvo->name,temp);
	nvo->up=nvo->down=NULL;
	for(q=(*cab);q->ant!=NULL;q=q->ant){;}
	nvo->sig=q;
	q->ant=nvo;
	
}
void loadKey(attrVal **cab){
	FILE *key;
	char temp[nameSize];
	openFile(&key,"key.dat","a+");
	k=0;
	while(!feof(key)){
		fscanf(key,"%s\n",temp);
		addKey(cab,temp);
		k++;
	}
	fclose(key);
}
void loadValues(attrVal **cab){
	FILE *values;
	char temp[nameSize];
	openFile(&values,"values.dat","a+");
	while(!feof(values)){
		fscanf(values,"%s\n",temp);
		if(feof(values))
			break;
		if(!strcmp(temp,";")){
			for(p=(*cab)->sig;p->down!=NULL;p=p->down){;}
			cabaux=NULL;
		}
		else
			addValue(cab,temp);
	}
	fclose(values);
}
void loadAtributes(attrVal **cab){
	FILE *atributes;
	char temp[nameSize];
	openFile(&atributes,"atributes.dat","a+");
	while(!feof(atributes)){
		fscanf(atributes,"%s\n",temp);
		if(feof(atributes))
			break;
		addAtribute(cab,temp);
	}
	fclose(atributes);
}
void addUpdateTable(attrVal **cab){
	printTable(cab);
	cabaux=NULL;
	char attrnew[nameSize];
	printf("\nporfavor ingrese el nombre del nuevo atributo\n");
	scanf("%s",attrnew);
	for(p=(*cab)->sig;p->sig!=NULL&&!strcmp(p->name,attrnew);p=p->sig){;}
	if(p->sig!=NULL){
		printf("\nerror el atributo que intentas ingresar ya esta ");
		return ;
	}
	while(p!=NULL){
		nvo=(attrVal*)malloc(sizeof(attrVal));
		strcpy(nvo->name,"nulo");
		nvo->sig=nvo->down=NULL;
		if(cabaux==NULL){
			strcpy(nvo->name,attrnew);
			cabaux=nvo;
			cabaux->up=NULL;
		}else{
			for(q=cabaux;q->down!=NULL;q=q->down){;}
			q->down=nvo;
			nvo->up=q;
		}
		p->sig=nvo;
		nvo->ant=p;
		p=p->down;
	}
}
void removeUpdateTable(attrVal **cab){
	printTable(cab);
	char attrremove[nameSize];
	printf("\nporfavor ingrese el nombre del nuevo atributo a eliminar\n");
	scanf("%s",attrremove);
	for(p=(*cab)->sig;p!=NULL&&strcmp(p->name,attrremove);p=p->sig){;}
	printf("%s",p->name);
	if(p==NULL){
		printf("\nel atributo que intenta eliminar no existe \n");
		return ;
	}
	while(p!=NULL){
		r=p->ant;
		q=p->sig;
		if(r!=NULL)
			r->sig=q;
		if(q!=NULL)
			q->ant=r;
		nvo=p;
		p=p->down;
		free(nvo);
	}
}
void addRegister(attrVal **cab){
	cabaux=NULL;
	for(p=(*cab)->sig;p->down!=NULL;p=p->down){;}
	for(q=(*cab)->sig;q!=NULL;q=q->sig){
		nvo=(attrVal*)malloc(sizeof(attrVal));
		printf("\ningrese %s   ",q->name);
		scanf("%s",nvo->name);
		nvo->sig=nvo->down=NULL;
		if(cabaux==NULL){
			nvo->ant=NULL;
			cabaux=nvo;
		}else{
			for(r=cabaux;r->sig!=NULL;r=r->sig){;}
			r->sig=nvo;
			nvo->ant=r;
		}
		nvo->up=p;
		p->down=nvo;
		p=p->sig;
	}
}
int main(){
	int menu;
	attrVal *cab=NULL;
	loadAtributes(&cab);
	loadValues(&cab);
//	loadKey(&cab);
	do{
		system("clear");
		printf("\nprecione\n\t1 nuevo registro\n\t2 añadir atributo\n\t3 eliminar atributo\n\t5 mostrar\n");
		scanf("%d",&menu);
		switch(menu){
			case 1:addRegister(&cab);break;
			case 2:addUpdateTable(&cab);break;
			case 3:removeUpdateTable(&cab);break;
			case 4:break;
			case 5:printTable(&cab);break;
			case 6:printf("\n\n\t\tgracias astra pronto :D");break;
		}
	}while(menu!=6);
	printf("\n");return 0;
}
