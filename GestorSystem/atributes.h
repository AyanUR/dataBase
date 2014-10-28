#include "basic.h"
#ifndef __ATRIBUTES_H__
#define __ATRIBUTES_H__
int checkDuplicate(base **cab,base *aux,int numkey,unsigned char clear);
void load(base **cab,char *whatfile){
	FILE *file;
	openFile(&file,whatfile,"a+");
	readFile(&file,cab,whatfile);
	fclose(file);
}
void saveChanges(base **cab){
	FILE *file[3];
	char whatfile[3][30]={{"key.dat"},{"atributes.dat"},{"values.dat"}};
	int i;
	base *p,*q;
	for(i=0;i<3;i++){
		openFile(&file[i],whatfile[i],"w");
	}
	i=0;
	for(p=*cab;p->ant!=NULL;p=p->ant){;}
	for(;p!=NULL;p=p->down){
		for(q=p;q!=NULL;q=q->sig){
			if(q==*cab){
				p=q->sig;
				fclose(file[i]);//cierro key.dat
				i++;
			}
			fprintf(file[i],"%s\n",q->attrval);
		}
		if(p->ant==*cab){
			fclose(file[i]);//cierro atributes.dat
			i++;
		}else{
			fprintf(file[i],";\n");
		}
	}
	fclose(file[i]);
}
void removeList(base **cab){
	base *p,*q,*r,*c;
	for(p=*cab;p->ant!=NULL;p=p->ant){;}
	while(p!=NULL){
		r=p->up;
		q=p->down;
		r->down=q;
		if(q!=NULL)
			q->up=r;
		c=p;
		p=p->sig;
		free(c);
	}
}
void changeList(base **cab,base **aux){
	base *p,*q,*r,*s,*copy=NULL;
	char campo[size];
	for(p=*aux;p->ant!=NULL;p=p->ant){;}
	printf("\ncampo\t\tvalor");
	for(q=(*cab)->sig,r=p;q!=NULL;q=q->sig,r=r->sig)
		printf("\n%s\t\t%s",q->attrval,r->attrval);
	printf("\n\ningrese el nombre del campo a modificar\n\t\to\nescriba todos para modificar todo\n");
	scanf("%s",campo);
	for(*aux=p;(*aux)!=NULL;(*aux)=(*aux)->sig)
		createList(&copy,(*aux)->attrval);
	for(*aux=p;p!=NULL;p=p->sig){
		q=p->up;
		r=p->down;
		if(q!=NULL)
			q->down=r;
		if(r!=NULL)
			r->up=q;
		p->up=p->down=NULL;
	}
	if(!strcmp(campo,"todos")){
		for(q=(*cab)->sig,r=copy;q!=NULL;q=q->sig,r=r->sig){
			printf("\n%s:   ",q->attrval);
			scanf("%s",r->attrval);
		}
	}else{
		for(q=(*cab)->sig,r=copy;q!=NULL&&strcmp(q->attrval,campo);q=q->sig,r=r->sig){;}
		if(q!=NULL){
			printf("\n%s:    ",q->attrval);
			scanf("%s",r->attrval);
		}
	}
	for(s=(*cab)->sig;s->down!=NULL;s=s->down){;}
	if(!checkDuplicate(cab,copy,k,7)){
		printf("Sus cambios interfieren con la llave");
		for(;s!=NULL;s=s->sig,(*aux)=(*aux)->sig){
			s->down=(*aux);
			(*aux)->up=s;
		}
		while(copy!=NULL){
			*aux=copy;
			copy=copy->sig;
			free(*aux);
		}
	}
	else{
		for(;s!=NULL;s=s->sig,copy=copy->sig){
			s->down=copy;
			copy->up=s;
		}
		while(*aux!=NULL){
			copy=*aux;
			*aux=(*aux)->sig;
			free(copy);
		}
	}
}
int checkDuplicate(base **cab,base *aux,int numkey,unsigned char clear){
	char value[numkey][size];
	base *k[numkey],*p,*q,*c;
	int i,flat=0;
	for(i=0,p=(*cab)->ant;p!=NULL;p=p->ant,i++){//dejas punteros puestos en la key
		for(k[i]=(*cab)->sig,q=aux;strcmp(k[i]->attrval,p->attrval);k[i]=k[i]->sig,q=q->sig){;}
		strcpy(value[i],q->attrval);
	}
	while(k[0]!=NULL){
		c=k[0];
		for(i=0;i<numkey;i++){
			if(!strcmp(k[i]->attrval,value[i]))
				flat++;
			k[i]=k[i]->down;
		}
		if(flat==numkey){
			if(clear==1)//boy a borrar
				removeList(&c);
			if(clear==2)
				changeList(cab,&c);
			return 0;
		}
		flat=0;
	}
	return 1;
}
void removeRegister(base **cab,int numkey,unsigned char coc){
	unsigned char flat=1;
	char value[size];
	base *s,*p,*q,*aux=NULL;
	for(s=*cab;s->ant!=NULL;s=s->ant){;}
	for(p=(*cab)->sig;p!=NULL;p=p->sig,flat=1){
		for(q=s;q!=*cab;q=q->sig){
			if(!strcmp(p->attrval,q->attrval)){
				printf("\n%s:   ",p->attrval);
				scanf("%s",value);
				createList(&aux,value);
				flat=0;
				break;
			}
		}
		if(flat)
			createList(&aux,"nulo");
	}
	if(coc)//boy a borrar
		checkDuplicate(cab,aux,numkey,1);
	else
		checkDuplicate(cab,aux,numkey,2);
}
void addRegister(base **cab,int numkey){
	base *aux=NULL,*p;
	char value[size];
	for(p=(*cab)->sig;p!=NULL;p=p->sig){
		printf("\n%s:   ",p->attrval);
		scanf("%s",value);
		createList(&aux,value);
	}
	if(checkDuplicate(cab,aux,numkey,0)){//debuelve 1 si no esta duplicado
		createTable(cab,aux);
		return ;
	}
	printf("\nse repitio :(");
	while(aux!=NULL){
		p=aux;
		aux=aux->sig;
		free(p)	;
	}
}
void addAtribute(base **cab){
	char atribute[size];
	base *p,*aux=NULL,*nvo,*q;
	int opc=0;
	printf("\nporfavor introdusca un nombre para en nuevo atributo   ");
	scanf("%s",atribute);
	for(p=(*cab);p->sig!=NULL;p=p->sig){
		if(!strcmp(p->attrval,atribute)){
			printf("\nerror el atributo que intentas ingresar ya esta ");
			return;
		}
	}
	printf("\npresione\n\t1 si quiere que el atributo forme parte de la llave\n\t0 en caso contrario\n");
	scanf("%d",&opc);
	if(opc){
		k++;
		q=(*cab)->ant;
		nvo=(base *)malloc(sizeof(base));
		strcpy(nvo->attrval,atribute);
		nvo->sig=nvo->ant=nvo->up=nvo->down=NULL;
		nvo->ant=q;
		nvo->sig=*cab;
		q->sig=nvo;
		(*cab)->ant=nvo;
	}
	for(;p!=NULL;p=p->down){
		nvo=(base *)malloc(sizeof(base));
		strcpy(nvo->attrval,"nulo");
		nvo->ant=nvo->sig=nvo->up=nvo->down=NULL;
		if(aux==NULL){
			strcpy(nvo->attrval,atribute);
			aux=nvo;
		}
		else{
			for(q=aux;q->down!=NULL;q=q->down){;}
			q->down=nvo;
			nvo->up=q;
		}
		nvo->ant=p;
		p->sig=nvo;
	}
}
void removeAtribute(base **cab){
	char atribute[size];
	base *p,*q,*r,*s,*nvo;
	printf("\nporfavor ingrese el nombre del atributo a eliminar   ");
        scanf("%s",atribute);
	for(p=(*cab)->ant;p->ant!=NULL;p=p->ant){;}
	for(;p!=(*cab)&&p!=NULL;p=p->sig){
		if(!strcmp(p->attrval,atribute)){
			k--;
			r=p->ant;
			q=p->sig;
			if(r!=NULL)
				r->sig=q;
			q->ant=r;
			free(p);
		}
	}
	for(;p!=NULL&&strcmp(p->attrval,atribute);p=p->sig){;}
	s=p;
	p=p->sig;
	while(s!=NULL){
		r=s->ant;
		q=s->sig;
	     	if(r!=NULL)
        		r->sig=q;
	       	if(q!=NULL)
        		q->ant=r;
		nvo=s;
	        s=s->down;
        	free(nvo);
	}
}
#endif
