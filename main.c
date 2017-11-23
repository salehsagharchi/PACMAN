#include <stdio.h>
#include <stdlib.h>

int n, m, min, sec, x, y;
int all[100][100];

struct PAC
{
    int dir;
    int score;
    int lives;
    int firstx;
    int firsty;
    int nowx;
    int nowy;
};

struct ROOH
{
    char name[10];
    int dir;
    int state;
    int time;
    int firstx;
    int firsty;
    int nowx;
    int nowy;
};

int ischeeseremain(int m, int n)
{
    int cheeseN = 0;
    int pinappN = 0;
    int cheryN = 0;
    for(int y = 0 ; y < n ; y++)
    {
        for(int x = 0 ; x < m ; x++)
        {
            if (all[x][y] == 'O')
                pinappN++;
            if (all[x][y] == '*')
                cheeseN++;
            if (all[x][y] == '^')
                cheryN++;
        }
    }
    if(pinappN == 0 && cheeseN == 0)
        return 0;
    return 1;
}

void inputstoarrays(struct ROOH *rohadd)
{
    struct ROOH rooh;
    rooh = *rohadd;
    char inputr[6][10];
    char temp[300];
    for(int i = 0 ; i < 300; i++)
    {
        temp[i] = '\0';
    }


    fflush(stdin);
    gets(temp);


    x = 0;
    int inhead = 0;
    for(int i = 0; i < 300 && temp[i] != '\0'; i++)
    {
        if(temp[i] == ' ')
        {
            inputr[x][inhead] = '\0';
            x++;
            inhead = 0;
        }
        else
        {
            inputr[x][inhead] = temp[i];
            inhead ++;
        }

    }
    for(int i = 0; i < 10; i++)
    {
        rooh.name[i] = inputr[0][i];
    }

    rooh.dir = inputr[1][0] - 48;
    rooh.state = inputr[2][0] - 48;
    if(rooh.state == 0)
    {
        sscanf(inputr[3], "%d", &rooh.time);
        x = 4;
    }
    else
    {
        x = 3;
        rooh.time = 0;
    }
    sscanf(inputr[x], "(%d,%d)", &rooh.firsty, &rooh.firstx);
    sscanf(inputr[x + 1], "(%d,%d)", &rooh.nowy, &rooh.nowx);
    *rohadd  = rooh;
}

void checkscore(struct PAC *pacman,int m,int n,struct ROOH rooh[4])
{
    //printf("%d %d\n",pacman->nowx,pacman->nowy);
    //printf("%c",all[pacman->nowx][pacman->nowy]);
    for(int y = 0 ; y < n ; y++)
    {
        for(int x = 0 ; x < m ; x++)
        {
            //printf("%c ", all[x][y]);
        }
    }
    //printf("$$$$$$$$$$$");
    int local = 0;
    if (all[pacman->nowx][pacman->nowy] == 'O')
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            if(rooh[i].state == 1)
            {
                rooh[i].state = 0;
                rooh[i].time = 10;
            }

        }
    }
    if (all[pacman->nowx][pacman->nowy] == '*')
        local++;
    if (all[pacman->nowx][pacman->nowy] == '^')
        local += 20;

    if (all[pacman->nowx][pacman->nowy] == 'O' || all[pacman->nowx][pacman->nowy] == '*' || all[pacman->nowx][pacman->nowy] == '^')
        all[pacman->nowx][pacman->nowy] = "_";

    for(int i = 0 ; i < 4 ; i++)
    {
        if(rooh[i].state == 0)
        {
            if(rooh[i].nowx == pacman->nowx && rooh[i].nowy == pacman->nowy)
            {
                local += 50;
            }
        }
    }

    pacman->score += local;
}


int checkwin(struct PAC pacman, int m, int n)
{
    if(pacman.lives <= 0)
    {
        return 0;
    }
    if(ischeeseremain(m,n) == 1)
    {
        return 0;
    }
    return 1;
}
int main(int argc, char *argv[])
{

    scanf("%d %d", &n, &m);

    char temp[300];
    fflush(stdin);
    for(y = 0 ; y < n ; y++)
    {
        gets(temp);
        for(int x = 0 ; x < m; x++)
        {
            all[x][y] = temp[x];
        }
    }

    for(int y = 0 ; y < n ; y++)
    {
        for(int x = 0 ; x < m ; x++)
        {
            //printf("%c ", all[x][y]);
        }
    }





    struct PAC pacman;

    scanf("%d:%d",&min,&sec);
    scanf("%d", &pacman.score);

    fflush(stdin);
    scanf("pacman: %d %d (%d,%d) (%d,%d)",
          &pacman.dir, &pacman.lives, &pacman.firsty, &pacman.firstx, &pacman.nowy, &pacman.nowx);

    struct ROOH rooh[4];

    inputstoarrays(&rooh[0]);
    inputstoarrays(&rooh[1]);
    inputstoarrays(&rooh[2]);
    inputstoarrays(&rooh[3]);
//	int dir;
//	int state;
//	int time;
//	int firstx;
//	int firsty;
//	int nowx;
//	int nowy;
    //for(int i = 0 ; i < 4 ; i++)
        //printf("%d %d %d %d %d %d %d\n",rooh[i].dir,rooh[i].state,rooh[i].time,rooh[i].firstx,rooh[i].firsty,rooh[i].nowx,rooh[i].nowy);

    x = 0;
    y = 0;

    int tempx,tempy;
    tempx = pacman.nowx;
    tempy = pacman.nowy;

    if(pacman.dir == 1)
        y--;
    if(pacman.dir == 2)
        x++;
    if(pacman.dir == 3)
        y++;
    if(pacman.dir == 4)
        x--;

    x = pacman.nowx + x;
    y = pacman.nowy + y;

    if(y < 0)
        y = n - 1;
    if(y == n)
        y = 0;
    if(x < 0)
        x = m-1;
    if(x == m)
        x = 0;


    if(all[x][y] == '#')
    {
        pacman.nowx = tempx;
        pacman.nowy = tempy;
    }
    else
    {
        pacman.nowx = x;
        pacman.nowy = y;
    }



    checkscore(&pacman,m,n,rooh);
    //printf("\ncheckscore\n");

    for(int i = 0 ; i < 4 ; i++)
    {
        //printf("%d %d %d\n",rooh[i].state,rooh[i].nowx,rooh[i].nowy);
        if(rooh[i].state == 1)
        {
            if(rooh[i].nowx == pacman.nowx && rooh[i].nowy == pacman.nowy)
            {
                //printf("%d %d %d\n",rooh[i].state,rooh[i].nowx,rooh[i].nowy);
                x = pacman.firstx;
                pacman.nowx = x;
                y = pacman.firsty;
                pacman.nowy = y ;

                pacman.lives--;
                break;
            }
        }
    }


    printf("(%d,%d)\n",pacman.nowy,pacman.nowx);
//	printf("%d", pacman.nowx);
    printf("%d\n",pacman.score);
//	return 0;
    if(checkwin(pacman,m,n) == 1)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }

    return 0;
}
