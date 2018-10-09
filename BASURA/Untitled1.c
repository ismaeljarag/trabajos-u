#include <stdio.h>
#include <string.h>
char fila[1]="1A";
int buscar_numero(char *fila){
    for(int x=0;x<strlen(fila);x++){
        if(fila [x] >= '0' && fila [x] <= '9'){
            return fila[x];
        }

        }
}
int main(){
    int a=buscar_numero(fila);
    printf("%c",a);
}
