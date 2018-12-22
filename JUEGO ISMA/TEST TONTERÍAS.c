#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
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
int main(){
    srand(time(NULL));
    int a; int x=5;
    a=rand() % (1+2);
    SetColor(95);
    printf("%d",a);
}
