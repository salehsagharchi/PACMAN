// COMPLETED GAME.C CODE BY MOHAMMAD SALEH SAGHARCHI (96110797)  !

#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <physics.h>
#include <math.h>
#include <time.h>

void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    srand(time(NULL));

    int lines = 0;
    int Xs, Ys;
    char buf[100][1000];

    // COPY FILE INFOS TO "buf" ARRAY !

    FILE *fp;
    fp = fopen("res/map.txt", "r");

    while(!feof(fp))
    {
        fgets(buf[lines], 1000, fp);
        for(int i = 0; i < 1000; i++)
        {
            if(buf[lines][i] == '\n')
                buf[lines][i] = '\0';
        }
        if(lines == 0)
        {
            sscanf(buf[lines], "%d %d", &Ys, &Xs);
        }
        printf("%s\n", buf[lines]);
        lines++;
    }
    lines--;

    //INIT OUTMAP & OUTGAME !

    outMap->height = Ys;
    outMap->width = Xs;


    for(int j = 0; j < Ys; j++)
    {
        for(int i = 0; i < Xs; i++)
        {
            if(buf[1 + j][i] == CELL_BLOCK || buf[1 + j][i] == CELL_EMPTY || buf[1 + j][i] == CELL_PINEAPPLE)
                outMap->cells[i][j] = buf[1 + j][i];

            if(buf[1 + j][i] == CELL_CHEESE)
                (outGame->cheeses)++;

            if(buf[1 + j][i] == CELL_CHERRY)
                (outGame->cherries)++;

            if(buf[1 + j][i] == CELL_PINEAPPLE)
                (outGame->pineapples)++;
        }
    }

    sscanf(buf[Ys + 1], "%d", &outGame->score);


    outGame->ghosts = 4;

    int local[5];

    //INIT PACMAN INFOS !

    sscanf(buf[Ys + 2], "pacman: %d %d (%d, %d) (%d, %d)", &outPacman->dir, &outPacman->health,
           &local[0], &local[1], &local[2], &local[3]);

    outPacman->speed = PACMAN_DEFAULT_SPEED;
    outPacman->startX = local[1];
    outPacman->startY = local[0];
    outPacman->x = (double)(local[3]);
    outPacman->y = (double)(local[2]);

    //INIT BLINKY INFOS ! -- red

    outGhosts[0].type = BLINKY;
    outGhosts[0].speed = GHOST_DEFAULT_SPEED;
    sscanf(buf[Ys + 3], "blinky: %d %d", &outGhosts[0].dir, &outGhosts[0].blue);
    outGhosts[0].blue = !outGhosts[0].blue;
    if(outGhosts[0].blue == false)
    {
        sscanf(buf[Ys + 3], "blinky: %d %d (%d, %d) (%d, %d)", &outGhosts[0].dir, &outGhosts[0].blue, 
               &local[0], &local[1], &local[2], &local[3]);
        outGhosts[0].blueCounterDown = 0;
    }
    else
    {
        sscanf(buf[Ys + 3], "blinky: %d %d %d (%d, %d) (%d, %d)", &outGhosts[0].dir, &outGhosts[0].blue, 
               &local[4], &local[0], &local[1], &local[2], &local[3]);
        outGhosts[0].blueCounterDown = (double)(local[4]) * CYCLES_PER_SEC;
    }
    outGhosts[0].startX = local[1];
    outGhosts[0].startY = local[0];
    outGhosts[0].x = (double)local[3];
    outGhosts[0].y = (double)local[2];

    // INIT PINKY INFOS ! -- pink


    outGhosts[1].type = PINKY;
    outGhosts[1].speed = GHOST_DEFAULT_SPEED;
    sscanf(buf[Ys + 4], "pinky: %d %d", &outGhosts[1].dir, &outGhosts[1].blue);
    outGhosts[1].blue = !outGhosts[1].blue;
    if(outGhosts[1].blue == false)
    {
        sscanf(buf[Ys + 4], "pinky: %d %d (%d, %d) (%d, %d)", &outGhosts[1].dir, &outGhosts[1].blue, 
               &local[0], &local[1], &local[2], &local[3]);
        outGhosts[1].blueCounterDown = 0;
    }
    else
    {
        sscanf(buf[Ys + 4], "pinky: %d %d %d (%d, %d) (%d, %d)", &outGhosts[1].dir, &outGhosts[1].blue, 
               &local[4], &local[0], &local[1], &local[2], &local[3]);
        outGhosts[1].blueCounterDown = (double)(local[4]) * CYCLES_PER_SEC;
    }
    outGhosts[1].startX = local[1];
    outGhosts[1].startY = local[0];
    outGhosts[1].x = (double)local[3];
    outGhosts[1].y = (double)local[2];

    // INIT CLYDE INFOS ! -- yellow


    outGhosts[2].type = CLYDE;
    outGhosts[2].speed = GHOST_DEFAULT_SPEED;
    sscanf(buf[Ys + 5], "clyde: %d %d", &outGhosts[2].dir, &outGhosts[2].blue);
    outGhosts[2].blue = !outGhosts[2].blue;
    if(outGhosts[2].blue == false)
    {
        sscanf(buf[Ys + 5], "clyde: %d %d (%d, %d) (%d, %d)", &outGhosts[2].dir, &outGhosts[2].blue, 
               &local[0], &local[1], &local[2], &local[3]);
        outGhosts[2].blueCounterDown = 0;
    }
    else
    {
        sscanf(buf[Ys + 5], "clyde: %d %d %d (%d, %d) (%d, %d)", &outGhosts[2].dir, &outGhosts[2].blue, 
               &local[4], &local[0], &local[1], &local[2], &local[3]);
        outGhosts[2].blueCounterDown = (double)(local[4]) * CYCLES_PER_SEC;
    }
    outGhosts[2].startX = local[1];
    outGhosts[2].startY = local[0];
    outGhosts[2].x = (double)local[3];
    outGhosts[2].y = (double)local[2];


    // INIT INKY INFOS ! -- blue


    outGhosts[3].type = INKY;
    outGhosts[3].speed = GHOST_DEFAULT_SPEED;
    sscanf(buf[Ys + 6], "inky: %d %d", &outGhosts[3].dir, &outGhosts[3].blue);
    outGhosts[3].blue = !outGhosts[3].blue;
    if(outGhosts[3].blue == false)
    {
        sscanf(buf[Ys + 6], "inky: %d %d (%d, %d) (%d, %d)", &outGhosts[3].dir, &outGhosts[3].blue, 
               &local[0], &local[1], &local[2], &local[3]);
        outGhosts[3].blueCounterDown = 0;
    }
    else
    {
        sscanf(buf[Ys + 6], "inky: %d %d %d (%d, %d) (%d, %d)", &outGhosts[3].dir, &outGhosts[3].blue, 
               &local[4], &local[0], &local[1], &local[2], &local[3]);
        outGhosts[3].blueCounterDown = (double)(local[4]) * CYCLES_PER_SEC;
    }
    outGhosts[3].startX = local[1];
    outGhosts[3].startY = local[0];
    outGhosts[3].x = (double)local[3];
    outGhosts[3].y = (double)local[2];

}

void checkEatables(Map* map, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {

    int lx[5], ly[5];

    lx[0] = (int)(outPacman->x);
    ly[0] = (int)(outPacman->y);

    lx[1] = lx[0] + 1;
    ly[1] = ly[0];

    lx[2] = lx[0] - 1;
    ly[2] = ly[0];

    lx[3] = lx[0];
    ly[3] = ly[0] + 1;

    lx[4] = lx[0];
    ly[4] = ly[0] - 1;

    // CHECKING EATABLE CELLS BY DISTANCE < 0.5 !

    double dis;

    for(int i = 0; i < 5; i++)
    {
        char nwmap = map->cells[lx[i]][ly[i]];

        dis = ((double)lx[i] - outPacman->x) * ((double)lx[i] - outPacman->x);
        dis += ((double)ly[i] - outPacman->y) * ((double)ly[i] - outPacman->y);
        dis = sqrt(dis);

        if(nwmap == '*' && (dis <= 0.5))
        {
            (outGame->score) += CHEESE_SCORE;
            map->cells[lx[i]][ly[i]] = '_';
            (outGame->cheeses) -= 1;
        }
        if(nwmap == '^' && (dis <= 0.5))
        {
            (outGame->score) += CHERRY_SCORE;
            map->cells[lx[i]][ly[i]] = '_';
            (outGame->cherries) -= 1;
        }
        if(nwmap == 'O' && (dis <= 0.5))
        {
            (outGame->score) += PINEAPPLE_SCORE;
            map->cells[lx[i]][ly[i]] = '_';
            (outGame->pineapples) -= 1;
            (outGame->pineapples) -= 1;
            for(int i = 0; i < 4; i ++)
            {
                outGhosts[i].blue = true;
                outGhosts[i].blueCounterDown = BLUE_DURATION;
            }
        }
    }

}

void checkGhostCollision(Pacman* outPacman, Ghost* outGhost) {

    return;
    int nwx, nwy, mx, my;

    nwx = (int)(outPacman->x);
    nwy = (int)(outPacman->y);
    mx = (int)(outGhost->x);
    my = (int)(outGhost->y);

    if(nwx == mx && nwy == my)
    {
        if(outGhost->blue)
        {
            outGhost->blue = false;
            outGhost->x = outGhost->startX;
            outGhost->y = outGhost->startY;
        }
        else
        {
            (outPacman->health) --;
            outPacman->x = outPacman->startX;
            outPacman->y = outPacman->startY;
        }
    }
}

bool isGameFinished(Game* game, Pacman* pacman) {

    if((game->cheeses <= 0 && game->pineapples <= 0) || (pacman->health <= 0))
    {
        return true;
    }
    return false;
}

void checkGhostState(Ghost* ghost) {

    if(ghost->blueCounterDown <= 0)
    {
        ghost->blue = false;
    }
    if(ghost->blue == true)
    {
        (ghost->blueCounterDown)--;
    }

}
