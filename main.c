#include <stdio.h>
#include <stdlib.h>

int n, m, min, sec, x, y;

struct PAC {
	int dir;
	int score;
	int lives;
	int firstx;
	int firsty;
	int nowx;
	int nowy;
};

struct ROOH {
	char name[10];
	int dir;
	int state;
	int time;
	int firstx;
	int firsty;
	int nowx;
	int nowy;
};

int ischeeseremain(char all[100][100] , int m , int n)
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
	sscanf(inputr[x], "(%d,%d)", &rooh.firstx , &rooh.firsty);
	sscanf(inputr[x + 1], "(%d,%d)", &rooh.nowx , &rooh.nowy);
	*rohadd  = rooh;
}

void checkscore(struct PAC *pacman,int all[100][100],struct ROOH rooh[4])
{
	int local = 0;
	if (all[pacman->nowx][pacman->nowy] == 'O')
		local += 50;
	if (all[pacman->nowx][pacman->nowy] == '*')
		local++;
	if (all[pacman->nowx][pacman->nowy] == '^')
		local += 20;
		
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

int main(int argc, char *argv[]) {

	scanf("%d %d", &n, &m);

	char all[m][n];
	char temp[300];
	fflush(stdin);
	for(y = 0 ; y < n ; y++)
	{
		gets(temp);
		x = 0;
		for(int i = 0 ; i < 300 && temp[i] != '\0'; i++)
		{
			if(temp[i] != ' ')
			{
				all[x][y] = temp[i];
				x++;
			}
			
		}
	}
	
//	for(int y = 0 ; y < n ; y++)
//	{
//		for(int x = 0 ; x < m ; x++)
//		{
//			printf("%c ", all[x][y]);
//		}
//	}
	
	

	
	
	struct PAC pacman;
	
	scanf("%d:%d",&min,&sec);
	scanf("%d", &pacman.score);
	
	fflush(stdin);
	scanf("pacman: %d %d (%d,%d) (%d,%d)", 
	&pacman.dir, &pacman.lives , &pacman.firstx , &pacman.firsty , &pacman.nowx, &pacman.nowy);
	
	struct ROOH rooh[4];
	
	inputstoarrays(&rooh[0]);
	inputstoarrays(&rooh[1]);
	inputstoarrays(&rooh[2]);
	inputstoarrays(&rooh[3]);

	if(pacman.dir == 1)
		pacman.nowy--;
	if(pacman.dir == 2)
		pacman.nowx++;
	if(pacman.dir == 3)
		pacman.nowy++;
	if(pacman.dir == 4)
		pacman.nowx--;
		
	checkscore(&pacman,all,rooh);				
	
	return 0;
}
