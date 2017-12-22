// COMPLETED PHYSICS.C CODE BY MOHAMMAD SALEH SAGHARCHI (96110797)  !

#include "physics.h"
#include "game.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>



char key;



char gettype(GhostType a)
{
    if(a == INKY)
        return 'I';
    if(a == PINKY)
        return 'P';
    if(a == BLINKY)
        return 'B';
    if(a == CLYDE)
        return 'C';
}

char GetKey(Action a)
{
    if(a == ACTION_RIGHT)
        return 'R';
    if(a == ACTION_LEFT)
        return 'L';
    if(a == ACTION_UP)
        return 'U';
    if(a == ACTION_DOWN)
        return 'D';
    if(a == ACTION_EXIT)
        return 'X';
    if(a == ACTION_IDLE)
        return 'I';
    if(a == ACTION_PAUSE)
        return 'P';
    return 'e';
}

POINT getpoint(Direction dir)
{
    int hx = 0, hy = 0;
    POINT res;
    if(dir == DIR_RIGHT)
    {
        hx = 1;
        hy = 0;
    }
    if(dir == DIR_LEFT)
    {
        hx = -1;
        hy = 0;
    }
    if(dir == DIR_UP)
    {
        hx = 0;
        hy = -1;
    }
    if(dir == DIR_DOWN)
    {
        hx = 0;
        hy = 1;
    }
    if(dir == DIR_NONE)
    {
        hx = 0;
        hy = 0;
    }
    res.x = hx;
    res.y = hy;
    return res;
}


int getid(int x, int y, int width)
{
    int id = 0;
    id += y * width;
    id += x;
    return id;
}

POINT getxy(int id, int width)
{
    POINT res;
    res.y = id / width;
    res.x = id - (res.y * width);
    return res;
}

int isvalid(int x, int y, const Map* map)
{
    if(map->cells[x][y] == CELL_BLOCK)
        return 0;
    if(x >= map->width || x < 0 || y >= map->height || y < 0)
        return 0;
    return 1;
}

int firstqu(int * queu, int max)
{
    for (int i = 0; i<max; ++i)
    {
        if(queu[i] == -1)
            return i;
    }
}

int pacx , pacy;

int * map2;
int * visited;
int * queue;
int * moq;
int firstinit = 0;
int nextvis[4];
int tmx,tmy,tmindx;


Direction decideGhost(const Map* map, Ghost* ghost)
//Direction decideGhost(const Map *map , Ghost *ghost , Pacman *pacman , Ghost *blinky)
{


    if(ghost->type != BLINKY)
    {
        return DIR_NONE;
    }


    // START AI



    int ghx,ghy;
    ghx = (int)ghost->x;
    ghy = (int)ghost->y;

    int max = map->width * map->height;

    //int map2[max] = {0};
    //int visited[max] = {0};
    //int queue[max] = {-1};
    //int moq[max] = {0};
    if(firstinit == 0)
    {
        firstinit = 1;
        map2 = (int *)malloc(sizeof(int) * max);
        visited = (int *)malloc(sizeof(int) * max);
        queue = (int *)malloc(sizeof(int) * max);
        moq = (int *)malloc(sizeof(int) * max);
    }
    for(int i = 0 ; i < max ; i++)
        map2[i] = -2;
    for(int i = 0 ; i < max ; i++)
        visited[i] = 0;
    for(int i = 0 ; i < max ; i++)
        queue[i] = -1;
    for(int i = 0 ; i < max ; i++)
        moq[i] = -2;


    int nowq = 0;
    int nowid = 0;



    nowq = firstqu(queue,max);
    nowid = getid(ghx,ghy,map->width);
    queue[nowq] = nowid;
    moq[nowq] = -1;

    int endwhile = 0;

    while (!endwhile)
    {
        if(nowq > max)
        {
            printf("\n\n\n\n NOT FINDED!\n\n\n\n");
            endwhile = 1;
        }
        if (visited[queue[nowq]] == 0)
        {
            visited[queue[nowq]] = 1;
            map2[queue[nowq]] = moq[nowq];

            if(getid(pacx,pacy,map->width) == queue[nowq])
            {
                printf("\n\n\n\nFINDED!\n\n\n\n");
                endwhile = 1;

                int mo = queue[nowq];
                POINT gil;
                printf("\n\n\n\n");


                while (map2[mo] != -1)
                {
                    //printf("\n\n\n\nFINDing!\n%d\n\n\n",mo);
                    gil = getxy(mo, map->width);
                    //map->cells[gil.x][gil.y] = CELL_CHERRY;

                    mo = map2[mo];
                }
                printf(" ------------------ %d %d %d %d -------------" , (int)ghost->x ,(int)ghost->y,gil.x,gil.y );
                tmx = gil.x - (int)ghost->x;
                tmy = gil.y - (int)ghost->y;

                if(tmx == 1 && tmy == 0)
                    return DIR_RIGHT;
                if(tmx == 0 && tmy == 1)
                    return DIR_DOWN;
                if(tmx == 0 && tmy == -1)
                    return DIR_UP;
                if(tmx == -1 && tmy == 0)
                    return DIR_LEFT;
                //ghost->x = gil.x;
                //ghost->y = gil.y;
                //printf(" -------------  %d %d %d %d\n\n\n\n" , (int)ghost->x ,(int)ghost->y,gil.x,gil.y );
                break;
            }


            for (int i = 0; i<4; ++i)
            {
                nextvis[i] = -1;
            }
            POINT np = getxy(queue[nowq],map->width);
            tmx = np.x;
            tmy = np.y;
            if (isvalid(tmx-1, tmy, map))
            {
                nextvis[0] = getid(tmx-1, tmy, map->width);
            }
            if (isvalid(tmx+1, tmy, map))
            {
                nextvis[1] = getid(tmx+1, tmy, map->width);
            }
            if (isvalid(tmx, tmy+1, map))
            {
                nextvis[2] = getid(tmx, tmy+1, map->width);
            }
            if (isvalid(tmx, tmy-1, map))
            {
                nextvis[3] = getid(tmx, tmy-1, map->width);
            }

            for (int i = 0; i<4; ++i)
            {
                if(nextvis[i] != -1)
                {
                    if(visited[nextvis[i]] == 0)
                    {
                        tmindx = firstqu(queue,max);
                        queue[tmindx] = nextvis[i];
                        moq[tmindx] = queue[nowq];
                    }
                }
            }


        }

        nowq++;
    }







    return DIR_NONE;

    int di = -1;
    int X, Y;

    if(ghost->x == (double)(int)(ghost->x) && ghost->y == (double)(int)(ghost->y))
    {
        while (di == -1)
        {
            di = (int)(rand() % 4) + 1;
            POINT dirr;
            dirr = getpoint(di);
            X = (int)ghost->x + dirr.x;
            Y = (int)ghost->y + dirr.y;
            if(X < 0)
            {
                X = map->width - 1;
            }
            if(X >= map->width)
            {
                X = 0;
            }
            if(Y < 0)
            {
                Y = map->height - 1;
            }
            if(Y >= map->height)
            {
                Y = 0;
            }

            if(map->cells[X][Y] == '#')
            {
                di = -1;
            }
            else
            {
                return di;
            }
        }
    }

}

Direction decidePacman(const Map* map, Pacman* pacman, Action action) {

    pacx = (int) pacman->x;
    pacy = (int) pacman->y;

    printf("%d\n\n",getid(pacx,pacy,map->width));

    int X, Y;

    Direction lastdir;
    lastdir = pacman->dir;
    POINT dirr;
    dirr = getpoint(lastdir);




    char now = GetKey(action);

    if(now == 'R')
    {
        key = 'R';
    }
    if(now == 'L')
    {
        key = 'L';
    }
    if(now == 'U')
    {
        key = 'U';
    }
    if(now == 'D')
    {
        key = 'D';
    }

    if(pacman->x == (double)(int)(pacman->x) && pacman->y == (double)(int)(pacman->y))
    {
        if(key == 'D')
        {
            lastdir = DIR_DOWN;
        }
        if(key == 'U')
        {
            lastdir = DIR_UP;
        }
        if(key == 'L')
        {
            lastdir = DIR_LEFT;
        }
        if(key == 'R')
        {
            lastdir = DIR_RIGHT;
        }

        dirr = getpoint(lastdir);

        X = (int)pacman->x + dirr.x;
        Y = (int)pacman->y + dirr.y;
        if(X < 0)
        {
            X = map->width - 1;
        }
        if(X >= map->width)
        {
            X = 0;
        }
        if(Y < 0)
        {
            Y = map->height - 1;
        }
        if(Y >= map->height)
        {
            Y = 0;
        }

        if(map->cells[X][Y] == '#')
        {

            key = 'e';
            lastdir = pacman->dir;
            dirr = getpoint(lastdir);

            X = (int)pacman->x + dirr.x;
            Y = (int)pacman->y + dirr.y;
            if(X < 0)
            {
                X = map->width - 1;
            }
            if(X >= map->width)
            {
                X = 0;
            }
            if(Y < 0)
            {
                Y = map->height - 1;
            }
            if(Y >= map->height)
            {
                Y = 0;
            }

            if(map->cells[X][Y] == '#')
            {
                return DIR_NONE;
            }
            else
            {
                return lastdir;
            }
        }
        else
        {
            key = 'e';
            return lastdir;
        }
    }
    return pacman->dir;
}
