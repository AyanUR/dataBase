#include <stdio.h>
#include <string.h>
#ifndef __ALGORITMORELACIONES_H__
#define __ALGORITMORELACIONES_H__
#define tamano 70//tamaño de las cadenas
#define anidado 11//numero maximo de anidaciones de una tributo compuesto numero de bloques
#define atribute 11//numero maximo de atributos del atributo compuesto numero de palabras
list *integridad=NULL,*strong=NULL;
void putPunterosinEntity(char *entityone,char *entitytwo,list **eone,list **etwo){//eone and etwo no nulos
	while(strcasecmp(entityone,(*eone)->data)&&(*eone=(*eone)->down)!=NULL);
	while(strcasecmp(entitytwo,(*etwo)->data)&&(*etwo=(*etwo)->down)!=NULL);
}
void passKey(list **dest,list *orig,unsigned char flat,char *simple){
	char aux[tamano],origen[tamano]={0};
	strcpy(aux,orig->data);
	for(;orig!=NULL;orig=orig->next){
		if(strchr(orig->data,'*')!=NULL){
			strcpy(origen,orig->data);
			if(flat)//solo pasas atributo
				origen[strlen(orig->data)-1]='\0';
			if(exist(*dest,orig->data)==NULL)
				addElementLast(dest,origen);	
		}
	}
	if(simple[0]!=0){
		addElementLast(dest,strtok(simple,","));
		while((simple=strtok(NULL,","))!=NULL)
			addElementLast(dest,simple);
	}
	sprintf(aux,"%s paso su llave a %s",aux,(*dest)->data);
	addElementLast(&integridad,aux);
}
void createTable(list **table,char *relacion,list *eone,list *etwo,char *simple){
	list *aux=NULL;
	char nametable[tamano*2]={0};
	strcat(strcat(strcat(nametable,eone->data),relacion),etwo->data);
	addElementLast(&aux,nametable);
	for(;eone!=NULL;eone=eone->next){
			if(strchr(eone->data,'*'))
				addElementLast(&aux,eone->data);
	}
	for(;etwo!=NULL;etwo=etwo->next){
			if(strchr(etwo->data,'*'))
				addElementLast(&aux,etwo->data);
	}
	if(simple[0]!=0){
        	addElementLast(&aux,strtok(simple,","));
       		 while((simple=strtok(NULL,","))!=NULL)
                	addElementLast(&aux,simple);
	}
	addRowforTable(table,&aux);
}
void Strong(list **table,list **eone,list **etwo,char info[][tamano],unsigned char flat){
	if(info[3][0]=='1'&&(info[4][0]=='n'||(info[4][0]=='1'&&(info[5][0]==info[6][0]||(info[5][0]=='p'&&info[6][0]=='t')))))//1:n,1t:1t,1p:1p,1p:1t
		passKey(etwo,*eone,flat,&info[7][2]);
	if((info[3][0]=='n'&&info[4][0]=='1')||(info[3][0]=='1'&&info[5][0]=='t'&&info[4][0]=='1'&&info[6][0]=='p'))//n:1,1t:1p
		passKey(eone,*etwo,flat,&info[7][2]);
	if((info[3][0]=='m'&&info[4][0]=='n')||(info[3][0]=='n'&&info[4][0]=='m'))//m:n
		createTable(table,info[0],*eone,*etwo,&info[7][2]);
}
void strongDevil(list **table,list **eone,list **etwo,char info[][tamano]){//por default tienes que pasarle la llave del fuerte al devil
	if(info[1][0]=='<'&&info[2][0]=='>'){//eone fuerte , etwo devil
		if(exist(strong,&info[2][1])==NULL)
			addElementLast(&strong,&info[2][1]);
		passKey(etwo,*eone,0,&info[7][2]);
	}
	else{//eone devil etwo fuerte
		if(exist(strong,&info[1][1])==NULL)
			addElementLast(&strong,&info[1][1]);
		passKey(eone,*etwo,0,&info[7][2]);
	}
	if((info[3][0]=='m'&&info[4][0]=='n')||(info[3][0]=='n'&&info[4][0]=='m'))
		createTable(table,info[0],*eone,*etwo,&info[7][2]);	
}
void devil(list **table,list **eone,list **etwo,char info[][tamano]){
	if(exist(strong,&info[1][1])!=NULL){	
		if(exist(strong,&info[2][1])!=NULL)
			Strong(table,eone,etwo,info,0);
		else{
			info[1][0]='<';
			strongDevil(table,eone,etwo,info);
		}
		return;
	}
	info[2][0]='<';
	strongDevil(table,eone,etwo,info);
}
void relacion(list **table,char *relacion){	//cursa-Alumno,Materia|m:n|t-p|s-attrsimples
	char info[8][tamano];
	list *entityone=*table,*entitytwo=*table;
	bzero(info,8*tamano*sizeof(char));
	sscanf(relacion,"%[a-zA-Z0-9_]-%[a-zA-Z0-9_><],%[a-zA-Z0-9_><]|%c:%c|%c:%c|%s",info[0],info[1],info[2],&info[3][0],&info[4][0],&info[5][0],&info[6][0],info[7]);
	putPunterosinEntity(&info[1][1],&info[2][1],&entityone,&entitytwo);
	if(info[1][0]=='<'&&info[2][0]=='<'){//son fuertes
		Strong(table,&entityone,&entitytwo,info,1);return;}
	if(info[1][0]=='>'&&info[2][0]=='>'){//son deviles
		devil(table,&entityone,&entitytwo,info);return ;}
	//una es devil y la otra fuerte
	strongDevil(table,&entityone,&entitytwo,info);
}
#endif
