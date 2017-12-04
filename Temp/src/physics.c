#include "physics.h"
#include "game.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct POINT{
    int x;
    int y;
};

typedef struct POINT POINT;

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

Direction decideGhost(const Map* map, Ghost* ghost) {

    int di = -1;
    int X,Y;

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

    int X,Y;

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
