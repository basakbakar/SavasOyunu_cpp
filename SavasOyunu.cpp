/****************************************************************************
**					SAKARYA ÜNÝVERSÝTESÝ
**			         BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**				    BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**				          PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI…...:PROJE1
**				ÖÐRENCÝ ADI...............:BAÞAK BAKAR
**				ÖÐRENCÝ NUMARASI.:B171210075
**				DERS GRUBU…………:D
****************************************************************************/

#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

int const width = 80;//I defined my arrays, characters counters and const values.
int const height = 20;
char a = 219;
char b = 175;
char c = 215;
char arena[100][100];
char keys[256];
int enemycounter = 0;
int counter1 = 0;
int bulletcounter = 0;
int const bulletnumber = 10000;
int enemynumber = 1000;

struct gun//I defined a struct called gun and I defined coordinates and symbol in it.
{
	int x;
	int y;
	char symbol;
};
gun weaponcraft[5];//I defined my basic structs in the game.
gun bullet[10000];
gun enemy[6];

void gotoxy(int x, int y)//I used the this function for changing the coordinats.
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void readkeyboard(char keys1[])//I used this function for reading keyboard.
{
	for (int i = 0; i < 256; i++)
		keys1[i] = (char)(GetAsyncKeyState(i) >> 8);
}
void hidecursor()//I used this function for not seeing the cursor moves.
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_CURSOR_INFO		cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
void drawarena()//I made this function for making the arena.
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cout << arena[x][y];
		}
		cout << endl;
	}
}
void cleanarena()//I made this function for not seeing the arenas occur again and again.
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			arena[x][y] = ' ';
	}
}
void makelimits()//ý made this function for making limits for the arena.
{
	for (int x = 0; x < width; x++)
	{
		arena[x][0]=a;
		arena[x][height - 1] = a;
	}
	for (int y = 0; y < height; y++)
	{
		arena[0][y] = a;
		arena[width - 1][y] = a;
	}
}
void makegun()//I made this function for creating the gun.
{
	int y1 = 6;
	int x1 = 1;
	for (int i = 0; i < 5; i++)//I created the y coordinates of weaponcraft.
	{
		weaponcraft[i].symbol = a;
		weaponcraft[i].y = y1;
		y1++;
	}
	weaponcraft[0].x = 1;//I created the x coordinates of weaponcraft.
	weaponcraft[1].x = 2;
	weaponcraft[2].x = 3;
	weaponcraft[3].x = 2;
	weaponcraft[4].x = 1;
}
void gunlocation()//I made this function for locating the gun to the arena.
{
	for (int i = 0;i < 5;i++)
	{
		int x = weaponcraft[i].x;
		int y = weaponcraft[i].y;
		arena[x][y] = weaponcraft[i].symbol;
	}
}
void makebullet()//I made this function for creating the bullet and giving its first coordinates.
{
	bullet[bulletcounter].symbol = b;
	bullet[bulletcounter].y = weaponcraft[2].y;
	bullet[bulletcounter].x = weaponcraft[2].x + 1;
	bulletcounter++;	
}
void bulletmoves()// I made this function for making bullets move left to right.
{
	for (int i = 0; i <bulletnumber; i++)
	{
		if (bullet[i].x < 79)
			bullet[i].x++;
		if (bullet[i].x == 78)
			bullet[i].x = 83;
	}

}
void bulletlocation()//I made this function for locating bullets in the arena.
{
	for (int i = 0; i < bulletnumber; i++)
	{
		int x = bullet[i].x;
		int y = bullet[i].y;
		arena[x][y] = bullet[i].symbol;
	}
}
void makeenemy()//I made this function for creating the enemy and giving its first coordinates.
{
	int randomlocation = rand() % 19;//I wanted the x coordinate of enemy to be 79 and y coordinate of the emeny to be random.
	if (enemycounter % 20 == 0)
	{
		enemy[counter1].x = 79;
		enemy[counter1].y = randomlocation;
		enemy[counter1].symbol = c;
		counter1++;
	}	
}
void enemylocation()//I made this function for locating the enemies in the arena.
{
	for (int i = 0; i < counter1; i++)
	{
		int x = enemy[i].x;
		int y = enemy[i].y;
		arena[x][y] = c;
		arena[x][y + 1] = c;
		arena[x][y + 2] = c;
		arena[x + 1][y] = c;
		arena[x + 1][y + 2] = c;
		arena[x + 2][y] = c;
		arena[x + 2][y + 1] = c;
		arena[x + 2][y + 2] = c;
	}
}
void enemybulletmatch()//I made this function for matching bullet and enemy.
{
	for (int i = 1; i < counter1; i++) 
	{
		for (int j = 0; j < enemycounter; j++)
		{
			if (bullet[j].x == enemy[i].x && bullet[j].y == enemy[i].y || //I thought the possibilities of the match of bullet and every coordinates of the enemy.
				bullet[j].x == enemy[i].x && bullet[j].y == enemy[i].y + 1 ||
				bullet[j].x == enemy[i].x && bullet[j].y == enemy[i].y + 2 ||
				bullet[j].x == enemy[i].x + 1 && bullet[j].y == enemy[i].y ||
				bullet[j].x == enemy[i].x + 1 && bullet[j].y == enemy[i].y + 1 ||
				bullet[j].x == enemy[i].x + 1 && bullet[j].y == enemy[i].y + 2) 
			{
				enemy[i].x = 81;//In the cases above I wanted the enemy's x coordinate to be out of the arena. So that we will not see them again.
				bullet[j].x = 82;//In the cases above I wanted the enemy's y coordinate to be out of the arena. So that we will not see them again.
			}

		}
	}

}
void enemymoves()//I made this function for moving enemies right to left.
{
	for (int i = 0;i <enemynumber; i++)//I wanted the enemy's x coordinate to be in arena.
	{
		if (enemy[i].x > 0 && enemy[i].x < 80)
			enemy[i].x--;;
		
		if (enemy[i].x == 0) 
			enemy[i].x = 81;
		
	}
	enemycounter++;
}
void keyboardcontrol()//I made this function for getting commands from the user.
{
	readkeyboard(keys);
	
	if (keys['W'] != 0)//'W' command tells the weaponcraft to go up.
	{
		for (int i = 0; i < 5; i++)
			weaponcraft[i].y--;
	}
	if (keys['S'] != 0)//'S' command tells the weaponcraft to go down.
	{
		for (int i = 0; i < 5; i++)
			weaponcraft[i].y++;
	}
	if (keys[32] != 0)//Space command tells the bullet to appear.
		makebullet();
}
int main()
{
	srand(time(0));
	hidecursor();
	makegun();
	while (true)
	{
		cleanarena();
		makelimits();
		makeenemy();
		enemymoves();
		enemybulletmatch();
		enemylocation();
		
		keyboardcontrol();
		gunlocation();
	
		bulletmoves();
		bulletlocation();
		
		gotoxy(0, 0);
		drawarena();
		Sleep(10);
	}
	
	cin.get();
	system("pause");
	return 0;
}
