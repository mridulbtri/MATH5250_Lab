#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Where is the grand prize?
    srand( time(NULL) );
    char prize = (char)(65 + rand() % 3); // 'A', 'B', or 'C'
    char notprize1 = (char)(((prize - 'A') + 1) % 3 + 'A');
    char notprize2 = (char)(((prize - 'A') + 2) % 3 + 'A');

    // Ask contestant to pick a door
    printf("\n");
    printf(" =-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf(" ** Monty Hall Simulator **\n");
    printf(" =-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("\n");

    char pick = ' ';
    while (pick != 'A' && pick != 'B' && pick != 'C')
    {
        printf(" Pick a door (A, B, or C): ");
        scanf(" %c", &pick);  
    }

    printf("\n You entered : %c\n", pick);

    // Tell contestant about another door
    char other;
    char other_other;
    printf("\n Interesting choice ...\n");

    if (pick == prize)
    {
        int ss = rand() % 2;
        if (ss == 0)
        {
            other = notprize1;
            other_other = notprize2;
        }
        else
        {
            other = notprize2;
            other_other = notprize1;
        }
    }
    else
    {
        other_other = prize;
        if (pick == notprize1)
        {
            other = notprize2;
        }
        else
        {
            other = notprize1;
        }
    }

    printf("\n I can tell you for sure that the prize is not behind door: %c\n", other);

    // Ask if they want to change
    int change = -1;
    while (change != 0 && change != 1)
    {
        printf("\n Stay with Door %c (press 0) or switch to Door %c (press 1): ",
               pick, other_other);
        scanf("%d", &change);
    }

    char final_pick;
    if (change == 0)
    {
        final_pick = pick;
        printf("\n You stayed with Door %c\n", final_pick);
    }
    else
    {
        final_pick = other_other;
        printf("\n You switched to Door %c\n", final_pick);
    }

    // Check answer
    if (final_pick == prize)
    {
        printf("\n *** WINNER ***\n\n");
    }
    else
    {
        printf("\n --- LOSER ---\n\n");
    }
    printf(" The prize was behind Door %c\n\n", prize);

    return 0;
}