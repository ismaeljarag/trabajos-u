#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int buscar_numero(char *fila){
    for(int x=0;x<strlen(fila);x++){
        if(fila [x] >= '0' && fila [x] <= '9'){
            return fila[x];
        }

        }
}
int main(){
    char asiento_a[5]={'X','X','X','X','X'};
    char asiento_b[5]={'X','X','X','X','X'};
    char asiento_c[5]={'X','X','X','X','X'};
    int a_escogido;
    int posicion_asiento; char fila[3]="";
    printf("\n      CINE ISMOPOLIS\n ");
    printf("\n    1  2  3  4  5");
    printf("\nA.  %c  %c  %c  %c  %c",asiento_a[0],asiento_a[1],asiento_a[2],asiento_a[3],asiento_a[4]);
    printf("\nB.  %c  %c  %c  %c  %c",asiento_b[0],asiento_b[1],asiento_b[2],asiento_b[3],asiento_b[4]);
    printf("\nC.  %c  %c  %c  %c  %c\n",asiento_c[0],asiento_c[1],asiento_c[2],asiento_c[3],asiento_c[4]);
    printf("Escoga la fila[Ej: 2A]: ");
    scanf("%s",&fila);
    if(strcmp(fila,"1A")==0||strcmp(fila,"2A")==0||strcmp(fila,"3A")==0||strcmp(fila,"4A")==0||strcmp(fila,"5A")==0){
            a_escogido=buscar_numero(fila)-48;
            for(int i=1;i<=5;i++){
                if(a_escogido==i){
                    asiento_a[i-1]='O';
                }
            }           }
    if(strcmp(fila,"1B")==0||strcmp(fila,"2B")==0||strcmp(fila,"3B")==0||strcmp(fila,"4B")==0||strcmp(fila,"5B")==0){
            a_escogido=buscar_numero(fila)-48;
            for(int i=1;i<=5;i++){
                if(a_escogido==i){
                    asiento_b[i-1]='O';
                }
            }

    }
    if(strcmp(fila,"1C")==0||strcmp(fila,"2C")==0||strcmp(fila,"3C")==0||strcmp(fila,"4C")==0||strcmp(fila,"5C")==0){
            a_escogido=buscar_numero(fila)-48;
            for(int i=1;i<=5;i++){
                if(a_escogido==i){
                    asiento_c[i-1]='O';
                }
            }

    }
    printf("\n    1  2  3  4  5");
    printf("\nA.  %c  %c  %c  %c  %c",asiento_a[0],asiento_a[1],asiento_a[2],asiento_a[3],asiento_a[4]);
    printf("\nB.  %c  %c  %c  %c  %c",asiento_b[0],asiento_b[1],asiento_b[2],asiento_b[3],asiento_b[4]);
    printf("\nC.  %c  %c  %c  %c  %c",asiento_c[0],asiento_c[1],asiento_c[2],asiento_c[3],asiento_c[4]);


}
