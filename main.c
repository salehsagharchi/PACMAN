#include <stdio.h>
#include <stdlib.h>

int n, m, score, min, sec, x, y;

struct PAC {
	int dir;
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
	
	
	scanf("%d:%d",&min,&sec);
	scanf("%d",&score);
	
	struct PAC pacman;
	
	fflush(stdin);
	scanf("pacman: %d %d (%d,%d) (%d,%d)", 
	&pacman.dir, &pacman.lives , &pacman.firstx , &pacman.firsty , &pacman.nowx, &pacman.nowy);
	
	struct ROOH rooh[4];
	
	inputstoarrays(&rooh[0]);
	inputstoarrays(&rooh[1]);
	inputstoarrays(&rooh[2]);
	inputstoarrays(&rooh[3]);


	
	return 0;
}
