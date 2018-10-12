#include <stdio.h>
#include <string.h>
#define filas 9
#define columnas 10
void mostrar_asientos(char * butacas[filas][columnas],int cantidad_asientos){
    system("cls");
        //PANTALLA PRINCIPAL
        printf("  ------------------------------------------");
         printf("\n                  PANTALLA\n");
        printf("  ------------------------------------------\n");
            for(int i=0;i<columnas;i++){
                printf("  %d ",i+1); //Columnas contador
                if(i==1) printf("  ");
                if(i==7) printf("  ");

            }
          printf("\n");
          for(int i=0;i<filas;i++){
                printf("%d ",i+1);  //Contador filas
          for(int x=0;x<columnas;x++){
            printf("%c   ",butacas[i][x]);
          if(x==1)printf("  ");
          if(x==7) printf("  ");

        }
        printf("\n");
            }
            printf("\n");


    }
int buscar_numero(char *fila){
    for(int x=0;x<strlen(fila);x++){
        if(fila [x] >= '0' && fila [x] <= '9'){
            return fila[x];
        }

        }
}
int main(){
    char *butacas[filas][columnas]; //Declaración variables
    int fila_pedida; int columna_pedida;
    int opcion; int break_menu=1; int asientos_libres=filas*columnas; int asientos_usados=0;
    int precio_entrada=0; int cantidad_asientos=0; int c_asientos_copy=0; int asientos_a_eliminar=0; int asientos_a_eliminar_copy;
    //Fin declaración variables

    for(int i=0;i<filas;i++){ //Rellenado de asientos 'O' libre 'X' ocupado.
        for(int x=0;x<columnas;x++){
            butacas[i][x]='O';
        }
    }
    do{
        printf("\n                                 CINE ISMAPOLIS\n\n");
        printf("1. Mostrar asientos\n");
        printf("2. Solicitar asiento\n");
        printf("3. Eliminar asiento\n");
        printf("Eliga una opcion: ");scanf("%d",&opcion);

    switch(opcion){ //Menú

    case 1: mostrar_asientos(&butacas,cantidad_asientos);  break;
    case 2:
            printf("Cantidad de asientos: "); scanf("%d",&cantidad_asientos);
            //MOSTRAR ASIENTOS
            mostrar_asientos(&butacas,cantidad_asientos);
            c_asientos_copy=cantidad_asientos;
            for(int x=0;x<cantidad_asientos;x++){
            printf("Asientos por elegir: %d\n",c_asientos_copy);
            printf("Ingrese la fila de la butaca: ");
            scanf("%d",&fila_pedida);
            printf("Ingrese la columna de la batuca: ");
            scanf("%d",&columna_pedida);
                if(butacas[fila_pedida-1][columna_pedida-1]=='O'){
                butacas[fila_pedida-1][columna_pedida-1]='X';
                asientos_libres--;
                asientos_usados++;
                precio_entrada=precio_entrada+2500;
                c_asientos_copy--;
                mostrar_asientos(&butacas,cantidad_asientos);



            }
             }

             printf("Asientos disponibles: %d\n",asientos_libres);
            printf("Asientos usados: %d\n",asientos_usados);
            printf("Precio de entradas: $%d\n",precio_entrada);
            break;
    case 3: printf("Cantidad a eliminar: "); scanf("%d",&asientos_a_eliminar);
            asientos_a_eliminar_copy=asientos_a_eliminar;
            mostrar_asientos(&butacas,cantidad_asientos);
            for(int x=0;x<asientos_a_eliminar;x++){
            printf("Asientos por eliminar: %d\n",asientos_a_eliminar_copy);
            printf("\nIngrese la fila de la butaca: ");
            scanf("%d",&fila_pedida);
            printf("Ingrese la columna de la batuca: ");
            scanf("%d",&columna_pedida);
            if(butacas[fila_pedida-1][columna_pedida-1]=='X'){
            butacas[fila_pedida-1][columna_pedida-1]='O';
            asientos_libres++;
            asientos_usados--;
            precio_entrada=precio_entrada-2500;
            }
            mostrar_asientos(&butacas,cantidad_asientos);// mostrar asientos
            printf("Asientos disponibles: %d\n",asientos_libres);
            printf("Asientos usados: %d\n",asientos_usados);
            printf("Precio de entradas: $%d\n",precio_entrada);
            asientos_a_eliminar_copy--;
            }
            break;
    case 4: break_menu++;

    }
    }while(break_menu<2);
}
