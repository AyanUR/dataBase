#include "basic.h"
#include "atributes.h"
int main(){
	base *cab=NULL;
	int menu;
	load(&cab,"atributes.dat");
	load(&cab,"values.dat");
	load(&cab,"key.dat");
	do{
		system("clear");
		printf("\npresione\n\t1 agragar registro\n\t2 anadir atributo\n\t3 eliminar atributo\n\t4 eliminar registro\n\t5 modificar registro\n\t6 mostrar\n\t7 salir\n");
		scanf("%d",&menu);
		switch(menu){
			case 1:addRegister(&cab,k);break;
			case 2:addAtribute(&cab);break;
			case 3:printTable(&cab);removeAtribute(&cab);break;
			case 4:printTable(&cab);removeRegister(&cab,k,1);break;
			case 5:printTable(&cab);removeRegister(&cab,k,0);break;
			case 6:printTable(&cab);break;
			case 7:printf("\n\n\t\tasta pronto :D");break;								
		}
		getchar();getchar();
	}while(menu!=7);
	saveChanges(&cab);
	printf("\n");return 0;
}
