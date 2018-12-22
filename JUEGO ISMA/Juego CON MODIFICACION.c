#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <dos.h>
#define tam_map 10
#define niveles_totales 5

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
    int probabilidad_aparicion;

} enemigo1;
struct jugadores
{
    char nombre[30];
    int x;
    int y;
    int vida;
    int ataque;
    int huir;
    int drenaragua;
    int nivel_mapa;

} player1;

void siguiente_nivel(mapa map)
{


    printf("%cSUPERADO!\n",173);
    printf("Prob. Aparicion enemigos sgte. mapa: %c%d\n",37,enemigo1.probabilidad_aparicion);
    printf("Niveles restantes: %d\n",(niveles_totales-1)-player1.nivel_mapa);
    printf("Presiona una tecla para el siguiente mapa...");
    system("PAUSE >>NULL");
    player1.nivel_mapa++;

    llenar_mapa(map);


}
void song_loss()
{
    Beep( 	293.66,500);
    Beep(  277.18, 500);
    Beep(  261.63,500);
    Beep(246.94, 650);


}
int huida()
{
    int escape=0;
    escape=rand() %100;
    if(escape <= enemigo1.escape)
    {
        printf("Has logrado escapar con exito\n\n");
        system("pause\n");
        return 1;
    }
    else
    {
        printf("Oh,oh. No has logrado escapar\n");
        printf("El enemigo te dio con %d de atakk, quedas con %d\n",enemigo1.ataque,player1.vida-enemigo1.ataque);
        player1.vida-=enemigo1.ataque;
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


    SetColor(6);
    printf("*********************************************************************************\n");
    printf("                                TABLA DE ESTADISTICAS\n\n  %-12s%20s%24s    POSICION PJ\n",player1.nombre,enemigo1.nombre,"Nivel mapa");
    printf("       Vida:%3d                  Vida:%3d         %3d           Y:%3d   \n       Ataque:%3d                Ataque:%3d                     X:%3d ",player1.vida,enemigo1.vida,player1.nivel_mapa,player1.y+1,player1.ataque,enemigo1.ataque,player1.x+1);
    printf("                                         \n       Drenar agua:%3d           Escape:%c%3d  \n ",player1.drenaragua,'%',enemigo1.escape);
    printf("********************************************************************************\n");
}
void fin_juego_creditos(int n,mapa map)
{
    player1.vida=0;
    enemigo1.vida=-1;
    enemigo1.ataque=-1;
    strcpy(enemigo1.nombre,"Sin enemigo");
    enemigo1.escape=0;
    player1.nivel_mapa=0;
    llenar_mapa(map);
    if(n==1)
    {
        tabla_puntaje();
        SetColor(95);
        printf("Has ganado. Gracias por jugar");
        printf("\n");
        song_win();
    }
    else
    {
        tabla_puntaje();
        SetColor(95);
        printf("Te han matado, intentalo otra vez");
        printf("\n");
        song_loss();
    }

}
void rand_enemigo(int enemy)
{
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
}
void aparicion_enemigos(mapa map,int player1y,int player1x,int *win)
{


    int y,x;
    int enemy;
    enemy=rand() % (1+2);
    y=rand() % 100;
    x=rand() % 100;
    if(enemigo1.probabilidad_aparicion > x && map[player1y][player1x+1]!= 'O')
    {

        map[player1y][player1x+1]= 'X';

        rand_enemigo(enemy);
        while(player1.vida >0 && enemigo1.vida > 0)
        {
            mostrar_mapa(map,player1x,player1y);
            char opc;
            mostrar_mapa(map);
            Beep(500,300);
            SetColor(95);
            while(opc < '1' || opc > '2')
            {
                printf("%cOh! rayos, un enemigo de tipo %s\n",173,enemigo1.nombre);
                printf("-----------------------------------\n");
                printf("|  1.%cEnfrentar? |2.Intentar huir |\n",168);
                printf("-----------------------------------\n");
                fflush(stdin);
                scanf("%c",&opc);
            }
            if(opc=='1') /*ENFRENTAMIENTO*/
            {
                /*while(enemigo1.vida >=0 && player1.vida >= 0) SACAR COMENTARIO PARA DESACTIVAR ENFRENTAMIENTO POR TURNOS
                {*/
                    printf("Tu ataque es de %d, el enemigo queda con %d\n\a",player1.ataque,enemigo1.vida-player1.ataque);
                    enemigo1.vida-=player1.ataque;
                    printf("El enemigo ataca con %d puntos atakk, quedas con %d\n\n",enemigo1.ataque,player1.vida-enemigo1.ataque);
                    player1.vida-=enemigo1.ataque;
                    if(enemigo1.vida<=0){
                        printf("Has matado al enemigo\n");
                        printf("Has ganado 20HP + 2PTOS AD+ 4ATK\n");
                        player1.vida+=20;
                        player1.drenaragua+=2;
                        player1.ataque+=4;
                        strcpy(enemigo1.nombre,"Sin enemigo");
                        enemigo1.vida=-1;
                        enemigo1.ataque=-1;
                        enemigo1.escape=0;

                    }
                    system("pause\n"); opc=5;
               /*}*/
            }
           if(opc=='2')
            {
                if(huida()==1){
                    break;
                }
                opc=5;

            }
        }

        if(player1.vida<=0)  /** FIN JUEGO POR BAJA VIDA PLAYER*/
        {
            *win=2;
        }
        /**     if(enemigo1.vida<=0)
             {
                 enemigo1.cantidad_enemigos--;
                 *win=1;
             }
             else *win=2; FIN JUEGO POR BAJA DE ENEMIGOS*/

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
    char clase;
    while(clase < '1' || clase > '3' )
    {
        printf("1.Mago\n   10HP - 5ATK - 4DA  \n");
        printf("2.Guerrero\n   25HP - 3ATK - 3DA\n");
        printf("3.Chuck Norris\n   50HP - 7ATK - 2DA\n\n");
        printf("Escoja una clase: \n");
        fflush(stdin);
        scanf("%c",&clase);
        system("cls");
        if(clase < '1' || clase > '3')
            printf("Digite una opcion correcta\n\n\a");
    }

    if(clase== '1')
    {
        player1.vida=10;
        player1.ataque=5;
        strcpy(player1.nombre, "Mago");
        player1.drenaragua=4;
    }
    if(clase== '2')
    {
        player1.vida=25;
        player1.ataque=3;
        strcpy(player1.nombre, "Guerrero");
        player1.drenaragua=3;
    }
    if(clase== '3')
    {
        player1.vida=50;
        player1.ataque=7;
        strcpy(player1.nombre, "Chuck Norris");
        player1.drenaragua=2;

    }

}
void mover_pj(int direccion,mapa map)
{
    direccion=getch();
    if(direccion == 'w')
    {
        Beep(500,150);
        if(player1.y > 0 && map[player1.y-1][player1.x] != 'O')
            player1.y--;
    }
    if(direccion == 's')
    {
        Beep(500,150);
        if(player1.y < tam_map-1 && map[player1.y+1][player1.x] != 'O')
            player1.y++;
    }
    if(direccion == 'a')
    {
        Beep(500,150);
        if(player1.x > 0 && map[player1.y][player1.x-1] !='O')
            player1.x--;
    }
    if(direccion == 'd')
    {
        Beep(500,150);
        if(player1.x < tam_map-1 && map[player1.y][player1.x+1] != 'O')
            player1.x++;
    }
    if(direccion == 'm')  //ASPIRADORA AGUA
    {
        if(player1.drenaragua!=0)
        {
            player1.drenaragua--;
            Beep(500,150);
            map[player1.y][player1.x+1]='#';
            map[player1.y+1][player1.x]='#';
        }

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
    map[tam_map-1][tam_map-1]='F';
    map[0][0]='#';
    map[0][1]='#'; // LIMPIEZA AREA RODEA J
    map[1][0]='#';

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
                    SetColor(3); //100 ROJO
                if(map[i][u]== 'X')
                {
                    SetColor(100);
                }
                if(map[i][u]=='F')
                {
                    SetColor(45);
                }

                printf("%c",map[i][u]);
            }


        }
        printf("\n");
    }
    printf("\n");

    if(x==tam_map-1 && y==tam_map-1)
    {
        if(player1.nivel_mapa<2){
            enemigo1.probabilidad_aparicion++;
        }
        else{
            enemigo1.probabilidad_aparicion+=3;
        }

        siguiente_nivel(map);
    }
}

int main() // 48 y 57
{
    char opc_menu;
    int a=0;
    int win=1;
    int direccion;
    strcpy(enemigo1.nombre,"Sin enemigo");
    enemigo1.cantidad_enemigos=1;
    enemigo1.vida=-1;
    enemigo1.ataque=-1;
    mapa map_dib;
    player1.nivel_mapa=0;
    enemigo1.probabilidad_aparicion=0;
    llenar_mapa(map_dib);


    while(opc_menu < '1' || opc_menu > '3' || a==0 )
    {
        printf("\n\n");
        printf("1.Iniciar Juego.\n2.Instrucciones.\n3.Creditos\n%cQue desea hacer?\n",168);
        fflush( stdin );
        scanf("%c",&opc_menu);
        if(opc_menu < '1' || opc_menu > '3')
            printf("Digite una opcion correcta\a");
        if(opc_menu=='1')
        {
            system("cls");
            eleccion_pj();

            while(enemigo1.cantidad_enemigos!=0 && player1.vida > 0 && player1.nivel_mapa<niveles_totales)
            {
                mostrar_mapa(map_dib,player1.x,player1.y);
                mover_pj(direccion,map_dib);
                aparicion_enemigos(map_dib,player1.y,player1.x,&win);
                system("@cls");
                mostrar_mapa(map_dib,player1.x,player1.y);
                system("@cls");
            }
            fin_juego_creditos(win,map_dib);

        }
        if(opc_menu=='2')
        {
            printf("Estas encerrado en un laberinto donde no puedes pasar por el agua(circulos). Debes llegar al punto final(F)\n");
            printf("mientras vas sorteando a diferentes enemigos, los cuales aumentan sus posibilidades de aparecer mientras avanzas\n");
            printf("niveles. Al matar un enemigo ganaras diferentes puntos de estadisticas. GANAS SI LLEGAS AL NIVEL %d, SUERTE.\n",niveles_totales);
            printf("\nW - Mover hacia arriba\nA - Mover a la izquierda\nD - Mover a la derecha\nS - Mover hacia abajo\n");
            printf("M - Drenar Agua(DA)");

        }
        if(opc_menu=='3')
        {
            printf("Ismael Jara G\nMatias Alarcon");
        }




    }






}
