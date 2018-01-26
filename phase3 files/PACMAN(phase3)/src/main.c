#include <stdio.h>
#include "SDL2_gfxPrimitives.h"
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "physics.h"
#include "map.h"
#include "input.h"


int WIDTH = 640;
int HEIGHT = 480;
int R = 20;
int drawlines = 0;
Action keytype = ACTION_IDLE;
int mouseX = 0;
int mouseY = 0;
Uint32 background;
Uint32 lasttime = 0;
Uint32 pausetime = 0;
Uint32 temptime = 0;
Uint32 alltime = 0;
int paclive ;
char filname[] = "res/reality.txt";


SDL_Renderer *renderer;

SDL_Window *window;

Uint32 rgb(Uint32 r, Uint32 g, Uint32 b)
{
    Uint32 s = 16;
    return r + g * s * s + b * s * s * s * s + 255 * s * s * s * s * s * s ;
}
Uint32 rgba(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    Uint32 s = 16;
    return r + g * s * s + b * s * s * s * s + a * s * s * s * s * s * s ;
}


int i = 27;
int add = 0;
void drawLive(int x, int y, Uint32 col)
{
    SDL_RenderSetScale(renderer,0.5, 0.5);
    x = 2 * x;
    y = 2 * y;
    x = x + R;
    y = y + R;
    filledCircleColor(renderer, x, y, R, rgb(255, 172, 20));
    filledCircleColor(renderer, x + 1, y - 12, 4, rgb(255, 255, 255));
    filledCircleColor(renderer, x + 3, y - 10, 2, rgb(68, 66, 63));
    filledPieColor(renderer, x - 4, y, 25, -1 * 27, 27, col);
    SDL_RenderSetScale(renderer,1, 1);
}
void drawPac(int X, int Y, int dir, int anim)
{
    int x,y;

    int num = 1;
    if((X < 0 && X > -40) || (X > WIDTH - 40 && X < WIDTH) || (Y < 0 && Y > -40) || (Y > HEIGHT - 40 && Y < HEIGHT))
    {
        num = 2;
    }
    for (int j = 0; j < num; ++j)
    {
        x = X + R;
        y = Y + R;
        filledCircleColor(renderer, x, y, R, rgb(255, 172, 20));
        if (dir == 1)
        {
            filledCircleColor(renderer, x - 12, y - 1, 4, rgb(255, 255, 255));
            filledCircleColor(renderer, x - 10, y - 3, 2, rgb(68, 66, 63));
            filledPieColor(renderer, x, y + 4, 25, -1 * i - 90, i - 90, background);
        }
        if (dir == 2)
        {
            filledCircleColor(renderer, x + 1, y - 12, 4, rgb(255, 255, 255));
            filledCircleColor(renderer, x + 3, y - 10, 2, rgb(68, 66, 63));
            filledPieColor(renderer, x - 4, y, 25, -1 * i, i, background);
        }
        if (dir == 3)
        {
            filledCircleColor(renderer, x + 12, y + 1, 4, rgb(255, 255, 255));
            filledCircleColor(renderer, x + 10, y + 3, 2, rgb(68, 66, 63));
            filledPieColor(renderer, x, y - 4, 25, -1 * i + 90, i + 90, background);
        }
        if (dir == 4)
        {
            filledCircleColor(renderer, x - 1, y - 12, 4, rgb(255, 255, 255));
            filledCircleColor(renderer, x - 3, y - 10, 2, rgb(68, 66, 63));
            filledPieColor(renderer, x + 4, y, 25, -1 * i + 180, i + 180, background);
        }
        if(X < 0 && X > -40)
        {
            X = WIDTH + X;
        }
        else if(X > WIDTH - 40 && X < WIDTH)
        {
            X = -(WIDTH - X);
        }
        else if(Y < 0 && Y > -40)
        {
            Y = HEIGHT + Y;
        }
        else if(Y > HEIGHT - 40 && Y < HEIGHT)
        {
            Y = -(HEIGHT - Y);
        }
    }
    if(anim == 1)
    {
        if (add == 0)
        {
            i-=PACMAN_DEFAULT_SPEED/2;
        }
        else
        {
            i+=PACMAN_DEFAULT_SPEED/2;
        }
    }
    if(i <= 5 )
    {
        add = 1;
    }
    if(i >= 27)
    {
        add = 0;
    }
}
void drawghost(int x, int y, Ghost gh, int vasat)
{
    x = x + R;
    y = y + R;
    Uint32 backcolor;
    if(gh.blue == true)
    {
        backcolor = rgb(17, 118, 219);
    }
    else
    {
        if(gh.type == BLINKY)
        {
            backcolor = rgb(219, 0, 43);
        }
        if(gh.type == CLYDE)
        {
            backcolor = rgb(255, 139, 51);
        }
        if(gh.type == INKY)
        {
            backcolor = rgb(52, 180, 255);
        }
        if(gh.type == PINKY)
        {
            backcolor = rgb(255, 53, 248);
        }
    }
    filledPieColor(renderer, x,y,R,180,0,backcolor);
    boxColor(renderer,  x - R, y, x + R ,y + 10,backcolor);
    if(gh.blue == true)
    {
        arcColor(renderer, x, y + 15, 15,230,310, rgb(255,255,255));
    }
    else if(vasat)
    {
        arcColor(renderer, x, y + 15 - 25, 15 ,47,133, rgb(255,255,255));
    }
    if(vasat)
    {
        filledCircleColor(renderer,x-7,y-10,4,rgb(255,255,255));
        filledCircleColor(renderer,x+7,y-10,4,rgb(255,255,255));
        filledCircleColor(renderer,x - 7,y-10,2,rgb(0,0,0));
        filledCircleColor(renderer,x + 7,y-10,2,rgb(0,0,0));
    }
    else if(gh.dir == DIR_RIGHT)
    {
        filledCircleColor(renderer,x-7,y-10,4,rgb(255,255,255));
        filledCircleColor(renderer,x+7,y-10,4,rgb(255,255,255));
        filledCircleColor(renderer,x - 5,y-10,2,rgb(0,0,0));
        filledCircleColor(renderer,x + 9,y-10,2,rgb(0,0,0));
    }
    else if(gh.dir == DIR_UP)
    {
        filledCircleColor(renderer,x-7,y-10,4,rgb(255,255,255));
        filledCircleColor(renderer,x+7,y-10,4,rgb(255,255,255));
        filledCircleColor(renderer,x-7,y-12,2,rgb(0,0,0));
        filledCircleColor(renderer,x+7,y-12,2,rgb(0,0,0));
    }
    else if(gh.dir == DIR_DOWN)
    {
        filledCircleColor(renderer,x-7,y-10,4,rgb(255,255,255));
        filledCircleColor(renderer,x+7,y-10,4,rgb(255,255,255));
        filledCircleColor(renderer,x-7,y-8,2,rgb(0,0,0));
        filledCircleColor(renderer,x+7,y-8,2,rgb(0,0,0));
    }
    else if(gh.dir == DIR_LEFT)
    {
        filledCircleColor(renderer,x-7,y-10,4,rgb(255,255,255));
        filledCircleColor(renderer,x+7,y-10,4,rgb(255,255,255));
        filledCircleColor(renderer,x - 9,y-10,2,rgb(0,0,0));
        filledCircleColor(renderer,x + 5,y-10,2,rgb(0,0,0));
    }
    //filledTrigonColor(renderer,x - 20,y + 20,   x - 13,y + 10,  x - 7,y+20,background);
    //filledTrigonColor(renderer,x - 7,y + 20,   x,y + 10,   x+7,y + 20,background);
    //filledTrigonColor(renderer,x + 7,y + 20,   x + 13,y + 10   ,x + 20,y + 20,background);

    filledTrigonColor(renderer,x - 20,y + 10,   x - 20,y + 20,   x - 13,y + 10,backcolor);
    filledTrigonColor(renderer,x - 13,y + 10,   x - 7,y + 20,      x,y + 10,backcolor);
    filledTrigonColor(renderer,x,y + 10,   x+7,y + 20,  x + 13,y + 10,backcolor);
    filledTrigonColor(renderer,x + 13,y + 10   ,x + 20,y + 20,  x + 20,y+10,backcolor);
}
void drawGhost(int X, int Y, Ghost gh, int vasat)
{
    drawghost(X,Y,gh,vasat);

    if(X < 0 && X > -40)
    {
        X = WIDTH + X;
        drawghost(X,Y,gh,vasat);
    }
    else if(X > WIDTH - 40 && X < WIDTH)
    {
        X = -(WIDTH - X);
        drawghost(X,Y,gh,vasat);
    }
    else if(Y < 0 && Y > -40)
    {
        Y = HEIGHT + Y;
        drawghost(X,Y,gh,vasat);
    }
    else if(Y > HEIGHT - 40 && Y < HEIGHT)
    {
        Y = -(HEIGHT - Y);
        drawghost(X,Y,gh,vasat);
    }
}
void drawBlock(int x, int y)
{
    boxColor(renderer, x,y,x+40,y+40, rgb(0, 145, 168));
}
void drawCheese(int x, int y)
{
    filledCircleColor(renderer, x + 20, y + 20, 9, rgb(255, 241, 122));
}
void drawCherry(int x, int y)
{
    arcColor(renderer, x+40,y+30,30,180,252,rgb(0,255,0));
    arcColor(renderer, x+55,y+20,30,170,215,rgb(0,255,0));
    filledCircleColor(renderer, x + 10, y + 30, 8, rgb(255,0,0));
    filledCircleColor(renderer, x + 30, y + 30, 8, rgb(255,0,0));
}
float drawPines(int * xs, int * ys, int ls, float piner, float plus, int anim)
{
    for (int i = 0; i < ls; ++i)
    {
        filledCircleColor(renderer, xs[i] + 20, ys[i] + 20, (int)piner, rgb(52, 249, 124));
    }
    if(anim)
        return piner+plus;
    else
        return piner;
}
void drawMap(Map map, int anim)
{
    int xps[100];
    int yps[100];
    int ps = 0;
    boxColor(renderer, 0, 0, WIDTH, HEIGHT, background);
    for (int i = 0; i < map.width; ++i)
    {
        for (int j = 0; j < map.height; ++j)
        {
            if(map.cells[i][j] == '#')
            {
                drawBlock(i*40, j*40);
            }
            if(map.cells[i][j] == '^')
            {
                drawCherry(i*40, j*40);
            }
            if(map.cells[i][j] == '*')
            {
                drawCheese(i*40, j*40);
            }
            if(map.cells[i][j] == 'O')
            {
                xps[ps] = i*40;
                yps[ps] = j*40;
                ps++;
            }
        }
    }
    static float piner = 15.0;
    static float plusp = 0.5;
    piner = drawPines(xps,yps,ps,piner,plusp,anim);
    if(piner >= 15.0)
    {
        plusp = -0.5;
    }
    if(piner <= 8.0)
    {
        plusp = 0.5;
    }
    if(drawlines)
    {
        for (int i = 0; i < WIDTH; i += (2 * R))
        {
            lineColor(renderer, i, 0, i, HEIGHT, rgb(60, 60, 60));
        }
        for (int j = 0; j < HEIGHT; j += (2 * R))
        {
            lineColor(renderer, 0, j, WIDTH, j, rgb(60, 60, 60));
        }
    }
}
int SDL_INITT()
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf ("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int sW = DM.w;
    int sH = DM.h;
    background = rgb(45,45,45);




    HEIGHT += 100;
    window  = SDL_CreateWindow("MY PACMAN", sW / 2 - WIDTH / 2, sH / 2 - HEIGHT / 2, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    HEIGHT -= 100;

    if (window == NULL)
    {
        printf ("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        printf ("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 3;
    }

    return 0;
}
void drawMenu(Game gm, Pacman pac)
{
    boxColor(renderer, 0,HEIGHT, WIDTH, HEIGHT + 100, rgb(0, 96, 71));
    lineColor(renderer,0,HEIGHT,WIDTH,HEIGHT,rgb(255,255,255));

    SDL_RenderSetScale(renderer,1.2,1.2);

    char scorestr[50];
    char timestr[50];
    sprintf(scorestr,"SCORE : %d", gm.score);
    sprintf(timestr,"TIME : %0.2lf", (double)((lasttime - pausetime) - alltime) / (double)1000);

    stringColor(renderer, 10, HEIGHT / 1.2 + 10, "LIVES : ", rgb(255,255,255));
    for (int j = 0; j < pac.health; ++j)
    {
        drawLive(90 + 22 * j, HEIGHT + 5, rgb(0,96,71));
    }
    SDL_RenderSetScale(renderer,1.2,1.2);

    stringColor(renderer, 10, HEIGHT / 1.2 + 35, scorestr, rgb(255,255,255));
    stringColor(renderer, (WIDTH / 1.2) / 2 - 120, HEIGHT / 1.2 + 35, "P: PAUSE/RESUME , ARROWS: MOVE", rgb(255,255,255));
    stringColor(renderer, WIDTH / 1.2 - 110, HEIGHT / 1.2 + 35, timestr, rgb(255,255,255));

    SDL_RenderSetScale(renderer,1,1);
    boxColor(renderer, WIDTH / 2 - 100, HEIGHT + 60, WIDTH / 2 - 10, HEIGHT + 85, rgb(188, 188, 188));
    boxColor(renderer, WIDTH / 2 + 10, HEIGHT + 60, WIDTH / 2 + 100,  HEIGHT + 85 , rgb(188, 188, 188));

    SDL_RenderSetScale(renderer,1.2,1.2);
    stringColor(renderer, (WIDTH / 2 - 71) / 1.2 , HEIGHT / 1.2 + 58, "EXIT", rgb(255,255,255));
    stringColor(renderer, (WIDTH / 2 + 22) / 1.2 , HEIGHT / 1.2 + 58, "RESTART", rgb(255,255,255));

    SDL_RenderSetScale(renderer,1,1);
    stringColor(renderer, (WIDTH - 180)  , HEIGHT + 85, "BY : M. S. SAGHARCHI!", rgb(66, 255, 116));
}



#ifdef main
# undef main
#endif
int main(int argc, char* argv[])
{

    SDL_Event e;
    int anim = 1;
    int quit = 0;
    int lastdir;
    int pause = 0;

    int xpac = 0;
    int ypac = 0;

    Map myMap;
    Game myGame;
    Pacman myPac;
    Ghost myGhost[4];
    initiateGame(filname, &myMap, &myGame, &myPac, myGhost);
    WIDTH = myMap.width * 40;
    HEIGHT = myMap.height * 40;
    lastdir = myPac.dir;
    if(lastdir == DIR_NONE)
        lastdir = DIR_RIGHT;

    if(SDL_INITT() != 0)
    {
        return 1;
    }

    quit = 0;
    WIDTH = 500;
    HEIGHT = 500;
    SDL_SetWindowSize(window, WIDTH, HEIGHT);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int sW = DM.w;
    int sH = DM.h;
    SDL_SetWindowPosition(window,  sW / 2 - WIDTH / 2, sH / 2 - HEIGHT / 2);
    int exit = 0;
    while (!quit)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                //SDL_ShowSimpleMessageBox(0, "PACMAN", "Thank You !", window);
                quit = 1;
            }
            if (e.type == SDL_MOUSEMOTION)
            {
                mouseX = e.motion.x;
                mouseY = e.motion.y;
            }
            if (e.type == SDL_MOUSEBUTTONUP)
            {
                //boxColor(renderer, WIDTH / 2 - 100, HEIGHT / 2 - 40, WIDTH / 2 + 100, HEIGHT / 2 - 5, rgb(188, 188, 188));
                //boxColor(renderer, WIDTH / 2 - 100, .HEIGHT / 2 + 5, WIDTH / 2 + 100, HEIGHT / 2 + 40, rgb(188, 188,
                if(mouseX > WIDTH / 2 - 100 && mouseY > HEIGHT / 2 - 40 && mouseX <  WIDTH / 2 + 100 && mouseY < HEIGHT / 2 - 5)
                {
                    SDL_ShowSimpleMessageBox(0, "PACMAN", "WELCOME !", window);
                    quit = 1;
                }
                if(mouseX > WIDTH / 2 - 100 && mouseY > HEIGHT / 2 + 5 && mouseX <  WIDTH / 2 + 100 && mouseY < HEIGHT / 2 + 40)
                {
                    exit = 1;
                    quit = 1;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        boxColor(renderer, 0, 0, WIDTH, HEIGHT, rgb(0, 96, 71));

        boxColor(renderer, WIDTH / 2 - 100, HEIGHT / 2 - 40, WIDTH / 2 + 100, HEIGHT / 2 - 5, rgb(188, 188, 188));
        boxColor(renderer, WIDTH / 2 - 100, HEIGHT / 2 + 5, WIDTH / 2 + 100, HEIGHT / 2 + 40, rgb(188, 188, 188));

        SDL_RenderSetScale(renderer, 1.2, 1.2);
        stringColor(renderer, (WIDTH / 2 - 50) / 1.2, (HEIGHT / 2 - 25) / 1.2, "START GAME", rgb(255, 255, 255));
        stringColor(renderer, (WIDTH / 2 - 18) / 1.2, (HEIGHT / 2 + 18) / 1.2, "EXIT", rgb(255, 255, 255));

        SDL_RenderSetScale(renderer, 1, 1);
        stringColor(renderer, (WIDTH - 180), HEIGHT - 15, "BY : M. S. SAGHARCHI!", rgb(66, 255, 116));
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    if(!exit)
    {
        WIDTH = myMap.width * 40;
        HEIGHT = myMap.height * 40;
        HEIGHT += 100;
        SDL_SetWindowSize(window, WIDTH, HEIGHT);
        SDL_SetWindowPosition(window,  sW / 2 - WIDTH / 2, sH / 2 - HEIGHT / 2);
        HEIGHT -= 100;
        quit = 0;
    }
    while (!quit)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                SDL_ShowSimpleMessageBox(0, "PACMAN", "Thank You !", window);
                quit = 1;
            }
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        keytype = ACTION_LEFT;
                        break;
                    case SDLK_RIGHT:
                        keytype = ACTION_RIGHT;
                        break;
                    case SDLK_UP:
                        keytype = ACTION_UP;
                        break;
                    case SDLK_DOWN:

                        keytype = ACTION_DOWN;
                        break;
                    case SDLK_p:
                        if(pause == 0)
                        {
                            temptime = SDL_GetTicks();
                        }
                        else
                        {
                            pausetime += SDL_GetTicks() - temptime;
                        }
                        pause = !pause;
                        break;
                    default:
                        keytype = ACTION_IDLE;
                        break;
                }
            }
            if(e.type == SDL_MOUSEMOTION)
            {
                mouseX = e.motion.x;
                mouseY = e.motion.y;
            }
            if(e.type == SDL_MOUSEBUTTONUP)
            {
                if(e.button.button == SDL_BUTTON_LEFT)
                {
                    //boxColor(renderer, WIDTH / 2 - 100, HEIGHT + 60, WIDTH / 2 - 10, HEIGHT + 85, rgb(188, 188, 188));
                    //boxColor(renderer, WIDTH / 2 + 10, HEIGHT + 60, WIDTH / 2 + 100,  HEIGHT + 85 , rgb(188, 188, 188));
                    if(mouseX > WIDTH / 2 - 100 && mouseX < WIDTH / 2 - 10 && mouseY > HEIGHT + 60 && mouseY < HEIGHT + 85)
                    {
                        SDL_ShowSimpleMessageBox(0, "PACMAN", "Thank You !", window);
                        quit = 1;
                    }
                    if(mouseX > WIDTH / 2 + 10 && mouseX < WIDTH / 2 + 100 && mouseY > HEIGHT + 60 && mouseY < HEIGHT + 85)
                    {
                        SDL_ShowSimpleMessageBox(0, "PACMAN", "Restart !", window);
                        if(pause)
                        {
                            pausetime += SDL_GetTicks() - temptime;
                        }
                        anim = 1;
                        quit = 0;
                        lastdir;
                        pause = 0;
                        xpac = 0;
                        ypac = 0;
                        R = 20;
                        keytype = ACTION_IDLE;
                        mouseX = 0;
                        mouseY = 0;
                        temptime = 0;
                        initiateGame(filname, &myMap, &myGame, &myPac, myGhost);
                        WIDTH = myMap.width * 40;
                        HEIGHT = myMap.height * 40;
                        lastdir = myPac.dir;
                        if(lastdir == DIR_NONE)
                            lastdir = DIR_RIGHT;
                        lasttime = SDL_GetTicks();
                        alltime += (lasttime - pausetime - alltime);


                    }
                }
            }
        }
        bool igf = isGameFinished(&myGame, &myPac);
        if(igf == true)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            drawMap(myMap,0);
            for (int g = 0; g < 4; ++g)
            {
                xpac = (int) (myGhost[g].x * 40.0);
                ypac = (int) (myGhost[g].y * 40.0);
                drawGhost(xpac, ypac, myGhost[g], 0);
            }
            xpac = (int)(myPac.x * 40.0);
            ypac = (int)(myPac.y * 40.0);
            drawPac(xpac, ypac, lastdir, 0 );
            drawMenu(myGame, myPac);




            if(myPac.health <= 0)
            {
                boxColor(renderer, 0, 0, WIDTH ,HEIGHT, rgba(255,0,0,80));
                SDL_RenderSetScale(renderer,3,3);
                stringColor(renderer, WIDTH / 6 - 40, HEIGHT / 6 - 3, "GAMEOVER :(", rgb(255,255,255));
                //stringColor(renderer, WIDTH / 6 - 25, HEIGHT / 6 - 3, "WON :)", rgb(255,255,255));
            }
            else
            {
                boxColor(renderer, 0, 0, WIDTH ,HEIGHT, rgba(0,255,0,80));
                SDL_RenderSetScale(renderer,3,3);
                //stringColor(renderer, WIDTH / 6 - 40, HEIGHT / 6 - 3, "GAMEOVER :(", rgb(255,255,255));
                stringColor(renderer, WIDTH / 6 - 25, HEIGHT / 6 - 3, "WON :)", rgb(255,255,255));
            }
            SDL_RenderSetScale(renderer,1,1);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000 / CYCLES_PER_SEC);
            continue;
        }
        if(pause)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            drawMap(myMap,0);
            for (int g = 0; g < 4; ++g)
            {
                xpac = (int) (myGhost[g].x * 40.0);
                ypac = (int) (myGhost[g].y * 40.0);
                drawGhost(xpac, ypac, myGhost[g], 0);
            }
            xpac = (int)(myPac.x * 40.0);
            ypac = (int)(myPac.y * 40.0);
            drawPac(xpac, ypac, lastdir, 0 );
            drawMenu(myGame, myPac);
            boxColor(renderer, 0, 0, WIDTH ,HEIGHT, rgba(0,0,0,120));
            SDL_RenderSetScale(renderer,3,3);
            stringColor(renderer, WIDTH / 6 - 20, HEIGHT / 6 - 3, "PAUSE", rgb(255,255,255));
            SDL_RenderSetScale(renderer,1,1);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000 / CYCLES_PER_SEC);
            continue;
        }
        lasttime = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        drawMap(myMap,1);


        //filledCircleColor(renderer, 20,20,20,rgb(255,0,0));
        for (int g = 0; g < 4; ++g)
        {

            if((double)(int)myGhost[g].x == myGhost[g].x)
            {
                if((int)myGhost[g].x == myMap.width)
                {
                    myGhost[g].x = 0.0;
                }
            }
            if((double)(int)myGhost[g].y == myGhost[g].y)
            {
                if((int)myGhost[g].y == myMap.height)
                {
                    myGhost[g].y = 0.0;
                }
            }

            Direction x = decideGhost(&myMap, &myGhost[g], &myPac, &myGhost[0]);
            myGhost[g].dir = x;

            paclive = myPac.health;
            checkGhostCollision(&myPac ,&myGhost[g]);

            xpac = (int)(myGhost[g].x * 40.0);
            ypac = (int)(myGhost[g].y * 40.0);
            drawGhost(xpac, ypac, myGhost[g], 0);



            if(myPac.health < paclive)
            {
                paclive = myPac.health;
                boxColor(renderer, 0, 0, WIDTH ,HEIGHT + 80, rgba(0,0,0,180));
                //SDL_RenderSetScale(renderer,3,3);
                //stringColor(renderer, WIDTH / 6 - 40, (HEIGHT ) / 6 - 3, "Please Wait!", rgb(255,255,255));
                //SDL_RenderSetScale(renderer,1,1);

                drawGhost(xpac, ypac, myGhost[g], 1);
                drawMenu(myGame,myPac);
                Map temp;
                Game gtemp;
                initiateGame(filname, &temp, &gtemp, &myPac, myGhost);
                WIDTH = myMap.width * 40;
                HEIGHT = myMap.height * 40;
                lastdir = myPac.dir;
                if(lastdir == DIR_NONE)
                    lastdir = DIR_RIGHT;
                myPac.health = paclive;
                SDL_RenderPresent(renderer);
                SDL_Delay(1200);
                SDL_RenderSetScale(renderer,1,1);
                continue;
            }
            if(x == DIR_UP)
            {
                ypac-=GHOST_DEFAULT_SPEED/2;
                if(ypac < 0)
                    ypac = HEIGHT + ypac;
            }
            if(x == DIR_DOWN)
            {
                ypac+=GHOST_DEFAULT_SPEED/2;
                if(ypac >= HEIGHT)
                    ypac = ypac % HEIGHT;
            }
            if(x == DIR_LEFT)
            {
                xpac-=GHOST_DEFAULT_SPEED/2;
                if(xpac < 0)
                    xpac = WIDTH + xpac;
            }
            if(x == DIR_RIGHT)
            {
                xpac+=GHOST_DEFAULT_SPEED/2;
                if(xpac >= WIDTH)
                    xpac = xpac % WIDTH;
            }
            myGhost[g].x = (double)xpac / (double)(40);
            myGhost[g].y = (double)ypac / (double)(40);

            if((double)(int)myGhost[g].x == myGhost[g].x)
            {
                if((int)myGhost[g].x == myMap.width)
                {
                    myGhost[g].x = 0.0;
                }
            }
            if((double)(int)myGhost[g].y == myGhost[g].y)
            {
                if((int)myGhost[g].y == myMap.height)
                {
                    myGhost[g].y = 0.0;
                }
            }
            checkGhostState(&myGhost[g]);
        }


        Direction x = decidePacman(&myMap,&myPac,keytype);
        if(x != DIR_NONE)
        {
            lastdir = x;
        }
        myPac.dir = x;

        xpac = (int)(myPac.x * 40.0);
        ypac = (int)(myPac.y * 40.0);
        drawPac(xpac, ypac, lastdir, x == DIR_NONE ? 0 : 1);
        if(x == DIR_UP)
        {
            ypac-=PACMAN_DEFAULT_SPEED/2;
            if(ypac < 0)
                ypac = HEIGHT + ypac;
        }
        if(x == DIR_DOWN)
        {
            ypac+=PACMAN_DEFAULT_SPEED/2;
            if(ypac >= HEIGHT)
                ypac = ypac % HEIGHT;
        }
        if(x == DIR_LEFT)
        {
            xpac-=PACMAN_DEFAULT_SPEED/2;
            if(xpac < 0)
                xpac = WIDTH + xpac;
        }
        if(x == DIR_RIGHT)
        {
            xpac+=PACMAN_DEFAULT_SPEED/2;
            if(xpac >= WIDTH)
                xpac = xpac % WIDTH;
        }
        myPac.x = (double)xpac / (double)(40);
        myPac.y = (double)ypac / (double)(40);
        if((double)(int)myPac.x == myPac.x)
        {
            if((int)myPac.x == myMap.width)
            {
                myPac.x = 0.0;
            }
        }
        if((double)(int)myPac.y == myPac.y)
        {
            if((int)myPac.y == myMap.height)
            {
                myPac.y = 0.0;
            }
        }
        checkEatables(&myMap, &myGame, &myPac, myGhost);


        drawMenu(myGame, myPac);



        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / CYCLES_PER_SEC);
    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}