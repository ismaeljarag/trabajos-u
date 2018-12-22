#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <dos.h>
#define tam_map 19
/**Matriz de 10x10, donde hay agua y tierra.
hay 3 clases:
	Mago: 		10HP - 5ATK
	Guerrero: 	25HP - 3ATK
	???		50HP - 7ATK
Hay 3 Enemigos:
	I)	20HP - 5ATK	80% Flee
	II)	50HP - 30ATK	50% Flee
	III)	100HP - 50ATK	5% Flee*/
typedef char mapa[tam_map][tam_map];
struct enemigos
{
    char nombre[30];
    int y,x;
    int vida;
    int ataque;
    int escape;
    int cantidad_enemigos;

} enemigo1;
struct jugadores
{
    char nombre[30];
    int x;
    int y;
    int vida;
    int ataque;
    int huir;
    int aspirado;

} player1;
void song_loss(){
    Beep( 	293.66,500);
    Beep(  277.18, 500);
    Beep(  261.63,500);
    Beep(246.94, 650);


}
int huida(){   int escape=0;
                escape=rand() %100;
                if(escape <= enemigo1.escape){
                    printf("Has logrado escapar con exito\n\n");
                    system("pause\n");
                    return 1;
                }
                else{
                    printf("Oh,oh. No has logrado escapar\n");
                    system("pause");
                    return 0;
                }
}
void song_win()
{
    Beep(440.00,250);
    Beep(440.00,250);
    Beep(392.00,250);
    Beep(440.00,500);
    Beep(349.23,500);
    Beep(392.00,500);
    Beep(440.00,200);
    Beep(392.00,200);
    Beep(440.00,800);
}
void tabla_puntaje()
{
    SetColor(19);
    printf("******************************************\n");
    printf("            TABLA DE ESTADISTICAS.      \n  %s:                  %s      \n",player1.nombre,enemigo1.nombre);
    printf("       Vida:%d                Vida:%d    \n       Ataque:%d               Ataque:%d  \n",player1.vida,enemigo1.vida,player1.ataque,enemigo1.ataque);
    printf("******************************************\n");
}
void fin_juego_creditos(int n)
{
    if(n==1)
    {
        tabla_puntaje();

        printf("Mataste a todos los enemigos. Gracias por jugar");
        printf("\n");
        song_win();
    }
    else
    {
        printf("Te han matado, intentalo otra vez");
        printf("\n");
        song_loss();
    }

}
void aparicion_enemigos(mapa map,int player1y,int player1x,int *win)
{

    int y,x;
    int enemy;
    enemy=rand() % (1+3);
    y=rand() % 11;
    x=rand() % 11;
    if(x>7 && y>7 && map[player1y][player1x+1]!= 'O')
    {

        map[player1y][player1x+1]= 'X';
        system("@cls");
        switch(enemy)
        {
        case 0:
            enemigo1.vida=20;
            enemigo1.ataque=5;
            enemigo1.escape=80;
            strcpy(enemigo1.nombre, "Demonio");

            break;
        case 1:
            enemigo1.vida=50;
            enemigo1.ataque=30;
            enemigo1.escape=50;
            strcpy(enemigo1.nombre, "Assasin");
            break;
        case 2:
            enemigo1.vida=100;
            enemigo1.ataque=50;
            enemigo1.escape=5;
            strcpy(enemigo1.nombre, "Carabinero");
            break;
        }
        while(player1.vida >0 && enemigo1.vida > 0)
        {
            mostrar_mapa(map,player1x,player1y);
            int opc;
            mostrar_mapa(map);
            Beep(500,300);
            printf("!Oh¡ rayos, un enemigo de tipo %s\n",enemigo1.nombre);
            printf("1.¿Enfrentar? 2.Intentar huir\n");
            scanf("%d",&opc);
            if(opc==1) //ENFRENTAMIENTO
            {
                printf("Tu ataque es de %d\n\a",player1.ataque);
                enemigo1.vida-=player1.ataque;
                printf("El enemigo ataca con %d puntos atakk, quedas con %d\n\a",enemigo1.ataque,player1.vida-enemigo1.ataque);
                player1.vida-=enemigo1.ataque;
                system("pause\n");
            }
            else{
                if(huida()==1) break;

            }



        }

        if(enemigo1.vida<=0){
            enemigo1.cantidad_enemigos--;
            *win=1;
        }
        else *win=2;

    }
}
void SetColor(int ForgC)
{
    WORD wColor;
    //This handle is needed to get the current background attribute

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //csbi is used for wAttributes word

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //To mask out all but the background attribute, and to add the color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
void eleccion_pj()
{
    int clase;
    printf("1.Mago\n");
    printf("2.Guerrero\n");
    printf("3.Chuck Norris\n");
    printf("Escoga una clase: ");
    scanf("%d",&clase);
    if(clase==1)
    {
        player1.vida=10;
        player1.ataque=5;
        strcpy(player1.nombre, "Mago");
        player1.aspirado=1;
    }
    if(clase==2)
    {
        player1.vida=25;
        player1.ataque=3;
        strcpy(player1.nombre, "Guerrero");
        player1.aspirado=2;
    }
    if(clase==3)
    {
        player1.vida=50;
        player1.ataque=7;
        strcpy(player1.nombre, "Chuck Norris");
        player1.aspirado=4;

    }

}
void mover_pj(int direccion,mapa map)
{
    direccion=getch();
    if(direccion == 'w')
        if(player1.y > 0 && map[player1.y-1][player1.x] != 'O')
            player1.y--;
    if(direccion == 's')
        if(player1.y < tam_map-1 && map[player1.y+1][player1.x] != 'O')
            player1.y++;
    if(direccion == 'a')
        if(player1.x > 0 && map[player1.y][player1.x-1] !='O')
            player1.x--;
    if(direccion == 'd')
        if(player1.x < tam_map-1 && map[player1.y][player1.x+1] != 'O')
            player1.x++;
    if(direccion == 'm')  //ASPIRADORA AGUA
    {
        map[player1.y][player1.x+1]='#';
        map[player1.y+1][player1.x]='#';
    }
}
void llenar_mapa(mapa map)
{
    srand(time(NULL));
    int i,x,direccion;
    for(i=0; i<tam_map; i++)
    {
        for(x=0; x<tam_map; x++)
        {
            if(rand()%100 < 70 )
            {
                map[i][x] = '#';

            }
            else
            {
                map[i][x] = 'O';

            }


        }

    }
    map[0][0]='#';
    player1.x=rand() % 1;
    player1.y=rand() % 1;

}
void mostrar_mapa(mapa map,int x,int y)
{
    int i,u;
    tabla_puntaje();

    for(i=0; i<tam_map; i++)
    {
        for(u=0; u<tam_map; u++)
        {
            if(i==y&&u==x)
            {
                SetColor(250);
                printf("J");

            }
            else
            {
                if(map[i][u]=='#')
                    SetColor(232);
                if (map[i][u] == 'O')
                    SetColor(30); //100 ROJO
                if(map[i][u]== 'X')
                {
                    SetColor(100);
                }

                printf("%c",map[i][u]);
            }


        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    strcpy(enemigo1.nombre,"Sin enemigo");
    int direccion;
    int win=0;
    mapa map_dib;
    enemigo1.cantidad_enemigos=1;
    enemigo1.vida=-1;
    enemigo1.ataque=-1;
    eleccion_pj();
    llenar_mapa(map_dib);
    while(enemigo1.cantidad_enemigos!=0 && player1.vida > 0)
    {
        mostrar_mapa(map_dib,player1.x,player1.y);
        mover_pj(direccion,map_dib);
        aparicion_enemigos(map_dib,player1.y,player1.x,&win);
        system("cls");
        mostrar_mapa(map_dib,player1.x,player1.y);
        system("@cls");
    }
    fin_juego_creditos(win);





}
