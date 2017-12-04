#include "game.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <physics.h>

void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    // fill me
    int lines = 0;
    int Xs,Ys;
    printf("%s\n",filename);
    char buf[100][1000];
    FILE *fp;
    fp = fopen(filename,"r");

    while(!feof(fp))
    {
        fgets(buf[lines],1000,fp);
        for(int i = 0 ; i < 1000 ; i++)
        {
            if(buf[lines][i] == '\n')
                buf[lines][i] = '\0';
        }
        if(lines == 0)
        {
            sscanf(buf[lines],"%d %d",&Ys,&Xs);
        }
        printf("%s\n",buf[lines]);
        lines++;
    }
    lines--;

    outMap->height = Ys;
    outMap->width = Xs;

    for(int j = 0 ; j < Ys ; j++)
    {
        for(int i = 0 ; i < Xs ; i++)
        {
            outMap->cells[i][j] = buf[1 + j][i];
            if(buf[1 + j][i] == CELL_CHEESE)
                (outGame->cheeses)++;
            if(buf[1 + j][i] == CELL_CHERRY)
                (outGame->cherries)++;
            if(buf[1 + j][i] == CELL_PINEAPPLE)
                (outGame->pineapples)++;
        }
    }
    sscanf(buf[Ys + 1],"%d",&outGame->score);
    outGame->ghosts = 4;

    int local[5];

    sscanf(buf[Ys + 2],"pacman: %d %d (%d,%d) (%d,%d)",&outPacman->dir,&outPacman->health,
           &local[0],&local[1],&local[2],&local[3]);

    outPacman->speed = PACMAN_DEFAULT_SPEED;
    outPacman->startX = local[1];
    outPacman->startY = local[0];
    outPacman->x = (double)(local[3]);
    outPacman->y = (double)(local[2]);



    outGhosts[0].type = BLINKY;
    outGhosts[0].speed = GHOST_DEFAULT_SPEED;
    sscanf(buf[Ys + 3],"blinky: %d %d",&outGhosts[0].dir,&outGhosts[0].blue);
    outGhosts[0].blue = !outGhosts[0].blue;
    if(outGhosts[0].blue == false)
    {
        sscanf(buf[Ys + 3],"blinky: %d %d (%d,%d) (%d,%d)",&outGhosts[0].dir,&outGhosts[0].blue,
               &local[0],&local[1],&local[2],&local[3]);
        outGhosts[0].blueCounterDown = 0;
    }
    else
    {
        sscanf(buf[Ys + 3],"blinky: %d %d %d (%d,%d) (%d,%d)",&outGhosts[0].dir,&outGhosts[0].blue,
               &local[4],&local[0],&local[1],&local[2],&local[3]);
        outGhosts[0].blueCounterDown = (double)(local[4]) * CYCLES_PER_SEC;
    }
    outGhosts[0].startX = local[1];
    outGhosts[0].startX = local[0];
    outGhosts[0].x = (double)local[3];
    outGhosts[0].y = (double)local[2];




    outGhosts[1].type = PINKY;
    outGhosts[1].speed = GHOST_DEFAULT_SPEED;
    sscanf(buf[Ys + 4],"pinky: %d %d",&outGhosts[1].dir,&outGhosts[1].blue);
    outGhosts[1].blue = !outGhosts[1].blue;
    if(outGhosts[1].blue == false)
    {
        sscanf(buf[Ys + 4],"pinky: %d %d (%d,%d) (%d,%d)",&outGhosts[1].dir,&outGhosts[1].blue,
               &local[0],&local[1],&local[2],&local[3]);
        outGhosts[1].blueCounterDown = 0;
    }
    else
    {
        sscanf(buf[Ys + 4],"pinky: %d %d %d (%d,%d) (%d,%d)",&outGhosts[1].dir,&outGhosts[1].blue,
               &local[4],&local[0],&local[1],&local[2],&local[3]);
        outGhosts[1].blueCounterDown = (double)(local[4]) * CYCLES_PER_SEC;
    }
    outGhosts[1].startX = local[1];
    outGhosts[1].startX = local[0];
    outGhosts[1].x = (double)local[3];
    outGhosts[1].y = (double)local[2];




    outGhosts[2].type = CLYDE;
    outGhosts[2].speed = GHOST_DEFAULT_SPEED;
    sscanf(buf[Ys + 5],"clyde: %d %d",&outGhosts[2].dir,&outGhosts[2].blue);
    outGhosts[2].blue = !outGhosts[2].blue;
    if(outGhosts[2].blue == false)
    {
        sscanf(buf[Ys + 5],"clyde: %d %d (%d,%d) (%d,%d)",&outGhosts[2].dir,&outGhosts[2].blue,
               &local[0],&local[1],&local[2],&local[3]);
        outGhosts[2].blueCounterDown = 0;
    }
    else
    {
        sscanf(buf[Ys + 5],"clyde: %d %d %d (%d,%d) (%d,%d)",&outGhosts[2].dir,&outGhosts[2].blue,
               &local[4],&local[0],&local[1],&local[2],&local[3]);
        outGhosts[2].blueCounterDown = (double)(local[4]) * CYCLES_PER_SEC;
    }
    outGhosts[2].startX = local[1];
    outGhosts[2].startX = local[0];
    outGhosts[2].x = (double)local[3];
    outGhosts[2].y = (double)local[2];

    outGhosts[3].type = INKY;
    outGhosts[3].speed = GHOST_DEFAULT_SPEED;
    sscanf(buf[Ys + 6],"inky: %d %d",&outGhosts[3].dir,&outGhosts[3].blue);
    outGhosts[3].blue = !outGhosts[3].blue;
    if(outGhosts[3].blue == false)
    {
        sscanf(buf[Ys + 6],"inky: %d %d (%d,%d) (%d,%d)",&outGhosts[3].dir,&outGhosts[3].blue,
               &local[0],&local[1],&local[2],&local[3]);
        outGhosts[3].blueCounterDown = 0;
    }
    else
    {
        sscanf(buf[Ys + 6],"inky: %d %d %d (%d,%d) (%d,%d)",&outGhosts[3].dir,&outGhosts[3].blue,
               &local[4],&local[0],&local[1],&local[2],&local[3]);
        outGhosts[3].blueCounterDown = (double)(local[4]) * CYCLES_PER_SEC;
    }
    outGhosts[3].startX = local[1];
    outGhosts[3].startX = local[0];
    outGhosts[3].x = (double)local[3];
    outGhosts[3].y = (double)local[2];
    
}

void checkEatables(Map* map, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    // fill me
}

void checkGhostCollision(Pacman* outPacman, Ghost* outGhost) {
    // fill me
}

bool isGameFinished(Game* game, Pacman* pacman) {
    // fill me
   // return true;
}

void checkGhostState(Ghost* ghost) {
    // fill me
}