// COMPLETED PHYSICS.C CODE BY MOHAMMAD SALEH SAGHARCHI (96110797)  !

#include "physics.h"
#include "game.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

int valideX(int x,int width)
{
    if (x < 0)
    {
        x = width + x;
    }
    if (x >= width)
    {
        x = x % width;
    }
    return x;
}
int valideY(int y,int height)
{
    if (y < 0)
    {
        y = height + y;
    }
    if (y >= height)
    {
        y = y % height;
    }
    return y;
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

int valid(int X, int Y, const Map* map, Ghost * g)
{
    if(g->type == CLYDE)
    {
        if(X >= map->width || X < 0 || Y >= map->height || Y < 0)
            return -1;
    }
    else
    {
        X = valideX(X,map->width);
        Y = valideY(Y,map->height);
    }
    if(map->cells[X][Y] == CELL_BLOCK)
        return -1;
    return getid(X,Y,map->width);
}

int firstqu(int * queu, int max)
{
    for (int i = 0; i<max; ++i)
    {
        if(queu[i] == -1)
            return i;
    }
}

Pacman * pacmang;
Ghost * blinkyg;
int max;



POINT getfirstvalid (const Map* map,int x, int y)
{
    int min = max * max,dis;
    POINT res,tm;
    int X,Y;
    X = valideX(x,map->width);
    Y = valideY(y,map->height);
    res.x = X;
    res.y = Y;

    if(map->cells[X][Y] == CELL_BLOCK)
    {
        for(int i = 0 ; i < max ; i++)
        {
            tm = getxy(i, map->width);
            if (map->cells[tm.x][tm.y] != CELL_BLOCK)
            {
                dis = (X - tm.x) * (X - tm.x) + (Y - tm.y) * (Y - tm.y);
                if (dis < min)
                {
                    min = dis;
                    res.x = tm.x;
                    res.y = tm.y;
                }
            }
        }
    }
    return res;
}

POINT gettarget(const Map* map, Ghost* ghost)
{
    POINT t;

    if(ghost->blue == true)
    {
        t = getfirstvalid(map,ghost->startX,ghost->startY);
        return t;
    }

    if(ghost->type == BLINKY)
    {
        t.x = (int)pacmang->x;
        t.y = (int)pacmang->y;
    }
    if(ghost->type == PINKY)
    {
        int next = 0;
        POINT d;
        int X, Y;
        d = getpoint(pacmang->dir);
        for(int i = 4 ; i >= 0 ; i--)
        {

            int notd = 0;
            for (int j = 1; j <= i; j++)
            {
                X = (int)pacmang->x + d.x * j;
                Y = (int)pacmang->y + d.y * j;
                X = valideX(X,map->width);
                Y = valideY(Y,map->height);
                if(map->cells[X][Y] == CELL_BLOCK)
                {
                    notd++;
                }
            }
            if(notd == 0)
            {
                next = i;
                break;
            }
        }
        X = (int)pacmang->x + d.x * next;
        Y = (int)pacmang->y + d.y * next;
        X = valideX(X,map->width);
        Y = valideY(Y,map->height);
        t.x = X;
        t.y = Y;
    }
    if(ghost->type == INKY)
    {
        int x1,x2,X,y1,y2,Y;
        POINT d;
        d = getpoint(pacmang->dir);
        x1 = (int)pacmang->x + d.x * 2;
        y1 = (int)pacmang->y + d.y * 2;
        x2 = (int)blinkyg->x;
        y2 = (int)blinkyg->y;
        X = x1 + (x1 - x2);
        Y = y1 + (y1 - y2);
        t = getfirstvalid(map,X,Y);
    }
    if(ghost->type == CLYDE)
    {
        int dis =0 ,X,Y,x1,y1;
        X = (int)ghost->x;
        Y = (int)ghost->y;
        x1 = (int)pacmang->x;
        y1 = (int)pacmang->y;
        dis = (X - x1) * (X - x1) + (Y - y1) * (Y - y1);
        if(dis > 64)
        {
            t.x = x1;
            t.y = y1;
        }
        else
        {
            t = getfirstvalid(map,0,map->height-1);
        }
    }


    return t;
}



int * map2;
int * visited;
int * queue;
int * moq;
int firstinit = 0;
int nextvis[4];
int tmx,tmy,tmindx;
int ghx,ghy;


POINT target;

//Direction decideGhost(const Map* map, Ghost* ghost)
Direction decideGhost(const Map *map , Ghost *ghost , Pacman *pacman , Ghost *blinky)
{
    max = map->width * map->height;

    if(ghost->type == BLINKY)
    {
        blinkyg = ghost;
    }

   // if(ghost->type != CLYDE)
    //{
       // return DIR_NONE;
    //}

    if(ghost->x != (double)(int)(ghost->x) || ghost->y != (double)(int)(ghost->y))
        return ghost->dir;

    // START AI



    target = gettarget(map, ghost);


    //ghost->x =target.x;
    //ghost->y = target.y;

    //return DIR_NONE;


    ghx = (int)ghost->x;
    ghy = (int)ghost->y;



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
    int distance = 0;

    if(target.x == ghx && target.y == ghy)
    {
        endwhile = 1;
        int di = -1 , X , Y;
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

    while (!endwhile)
    {
        if(nowq > max)
        {
            printf("\n\n\n\n NOT FINDED!\n\n\n\n");
            printf("\n\n\n\nTARGET : %d %d\n\n\n\n",target.x,target.y);
            endwhile = 1;
        }
        if (visited[queue[nowq]] == 0)
        {
            visited[queue[nowq]] = 1;
            map2[queue[nowq]] = moq[nowq];

            if(getid(target.x,target.y,map->width) == queue[nowq])
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
                    distance++;
                    mo = map2[mo];
                }

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
                if(tmy+1 == map->height)
                    return DIR_UP;
                if(tmy-1 == -map->height)
                    return DIR_DOWN;
                if(tmx+1 ==  map->width)
                    return DIR_LEFT;
                if(tmx-1 == -map->width)
                    return DIR_RIGHT;

                printf("\nDISTANCE :                %d\n",distance);
                printf(" ------------------ %d %d-------------" , tmx,tmy );

                break;
            }


            for (int i = 0; i<4; ++i)
            {
                nextvis[i] = -1;
            }
            POINT np = getxy(queue[nowq],map->width);
            tmx = np.x;
            tmy = np.y;

            nextvis[0] = valid(tmx-1, tmy, map,ghost);
            nextvis[1] = valid(tmx+1, tmy, map,ghost);
            nextvis[2] = valid(tmx, tmy+1, map,ghost);
            nextvis[3] = valid(tmx, tmy-1, map,ghost);


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

}

Direction decidePacman(const Map* map, Pacman* pacman, Action action) {



    pacmang = pacman;

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
