#include <stdio.h>

#include "debugmalloc.h"
#include "views/game.h"

int main(void)
{
    int input = 0;

    while(input != 3)
    {
        system("clear || cls");
        printf("[1] Uj jatek kezdese\n[2] Jatek betoltse\n[3] Kilepes\nValasztasa: ");
        scanf("%d", &input);
        
        if(input == 1 || input == 2) 
            game(input == 2);
        else
            break;
    } 

    printf("\nA program leáll.");
    return 0;
}