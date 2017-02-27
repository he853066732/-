#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <windows.h>
#include<time.h>
using namespace std;
class Part
{
public:
	int X;
	int Y;
	char dir;
	void dis_X(int x);
	void dis_Y(int x);
	void dis_dir(char x);
	void dayin();
};
void Part::dis_X(int x)
{
	X=x;
}
void Part::dis_Y(int x)
{
	Y=x;
}
void Part::dis_dir(char x)
{
	if(dir=='w'&&x!='s')
	{
		dir=x;
	}
	if(dir=='s'&&x!='w')
	{
		dir=x;
	}
	if(dir=='a'&&x!='d')
	{
		dir=x;
	}
	if(dir=='d'&&x!='a')
	{
		dir=x;
	}
}
void Part::dayin()
{
	HANDLE hout;
	COORD coord;
	coord.X=X;
	coord.Y=Y;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,coord);	
	printf("⊙");
	if(dir=='w')
	{
		Y=Y-1;
	}
	else if(dir=='a')
	{
		X=X-1;
	}
	else if(dir=='s')
	{
		Y=Y+1;
	}
	else if(dir=='d')
	{
		X=X+1;
	}
}
class PART
{
public:
	int X;
	int Y;
	int IF;
	void dayin();
};
void PART::dayin()
{
	if(IF==1)
	{
		HANDLE hout;
	    COORD coord;
	    coord.X=X;
	    coord.Y=Y;
	    hout=GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleCursorPosition(hout,coord);
		printf("%c",3);
	}
	else if(IF==2)
	{
		HANDLE hout;
	    COORD coord;
	    coord.X=X;
	    coord.Y=Y;
	    hout=GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleCursorPosition(hout,coord);
		printf(" ");
	}
}
class Snake
{	
public:
	PART part[1000];
	int Snake_speed;
	int Snake_long;
	Part Head;
	void dis_dir();
	void dis_speed();
	void Snake_new();
	void Snake_add();
	void Snake_dayin();
	void dis_score();
};
class Food
{
public:
	int X;
	int Y;
	void Food_new();
	void dayin();
	Snake snake;
};
void Food::Food_new()
{
	int i;
	srand(time(NULL));
	X=rand()%49+1;
	Y=rand()%19+1;
	for(i=0;snake.part[i].IF==1;i++)
	{
		if(X==snake.part[i].X&&Y==snake.part[i].Y)
		{
			Food_new();
		}
	}
}
void Food::dayin()
{
	HANDLE hout;
	COORD coord;
	coord.X=X;
	coord.Y=Y;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,coord);
	printf("%c",33);
}
void Snake::dis_dir()
{
	char point;
	point=getch();
	if(point=='w'||point=='a'||point=='s'||point=='d')
	{
		Head.dis_dir(point);  
	}
}
void Snake::dis_score()
{
	HANDLE hout;
	COORD coord;
	coord.X=60;
	coord.Y=10;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,coord);
	printf("您的分数是：%d",Snake_long-5);
}
void Snake::dis_speed()
{
	int x;
	while(1)
	{
	cin>>x;
	if(x>=1&&x<=10)
	{
		Snake_speed=(11-x)*100;
		break;
	}
	else
	{
		cout<<"对不起，您输入的等级不正确，请重新输入："<<endl;
	}
	}
}
void Snake::Snake_dayin()
{
	int i;
	Head.dayin();
	for(i=0;i<50;i++)
	{
		part[i].dayin();
	}
	for(i=49;i>=0;i--)
	{
		part[i].X=part[i-1].X;
		part[i].Y=part[i-1].Y;
	}
	part[0].X=Head.X;
	part[0].Y=Head.Y;
}
void Snake::Snake_new()
{
	int i;
	Snake_speed=100;
	Head.dis_X(5);
	Head.dis_Y(1);
	Head.dir='d';
	Snake_long=0;
	for(i=0;i<1000;i++)
	{
		part[i].IF=0;
	}
	for(i=0;i<5;i++)
	{
		Snake_add();
	}
}
void Snake::Snake_add()
{
	int i;
	for(i=0;i<50;i++)
	{
		if(part[i].IF!=1)
		{
			part[i].IF=1;
			part[i+1].IF=2;
			break;
		}
	}
	Snake_long++;
}
class File
{
public:
	int fen;
	FILE *fp;
	void new_file();
	void dis_fen();
};
class Game
{
	Snake snake;
	Food food;
	File file;
public:
	void Game_bianjie();
	void Game_begin();
	void Game_eat();
	int Game_end();
	void Game_play();
	void Game_sleep();
	void Game_Fen();
};
void Game::Game_sleep()
{
	_sleep(snake.Snake_speed);
}
void Game::Game_play()
{
	snake.Snake_dayin();
	food.dayin();
	snake.dis_score();
	Game_eat();
	if(kbhit())
	{
		snake.dis_dir();
	}
}
int Game::Game_end()
{
	int i;
	if(snake.Head.X==0||snake.Head.X==50||snake.Head.Y==0||snake.Head.Y==20)
	{
		system("cls");
		cout<<"对不起，游戏结束。"<<endl;
		printf("您的分数是：%d\n",snake.Snake_long-5);
		printf("最高分是：");
		Game_Fen();
		printf("\n");
		system("pause");
		getch();
		return 1;
	}
	for(i=1;snake.part[i].IF==1;i++)
	{
		if(snake.Head.X==snake.part[i].X&&snake.Head.Y==snake.part[i].Y)
		{
			system("cls");
		    cout<<"对不起，游戏结束。"<<endl;
			printf("您的分数是：%d\n",snake.Snake_long-5);
			printf("最高分是：");
			Game_Fen();
			printf("\n");
			system("pause");
			getch();
		    return 1;
		}
	}
	return 0;
}
void Game::Game_eat()
{
	if(snake.Head.X==food.X&&snake.Head.Y==food.Y)
	{
		snake.Snake_add();
		food.Food_new();
	}
}
void Game::Game_bianjie()
{
	int X;
	int Y;
	HANDLE hout;
	COORD coord;	
	Y=0;
	for(X=0;X<=50;X++)
	{
		coord.X=X;
	    coord.Y=Y;
	    hout=GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleCursorPosition(hout,coord);
		printf("%c",3);
	}
	Y=20;
	for(X=0;X<=50;X++)
	{
		coord.X=X;
	    coord.Y=Y;
	    hout=GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleCursorPosition(hout,coord);
		printf("%c",3);
	}
	X=0;
	for(Y=1;Y<=19;Y++)
	{
		coord.X=X;
	    coord.Y=Y;
	    hout=GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleCursorPosition(hout,coord);
		printf("%c",3);
	}
	X=50;
	for(Y=1;Y<=19;Y++)
	{
		coord.X=X;
	    coord.Y=Y;
	    hout=GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleCursorPosition(hout,coord);
		printf("%c",3);
	}
}
void Game::Game_begin()
{
	snake.Snake_new();
	food.Food_new();
	cout<<"欢迎来到贪吃蛇世界！本游戏按“w”向上，按“s”向下，按“a”向左，按“d”向右。"<<endl;
	cout<<"下面请输入游戏等级，为1-10级："<<endl;
	snake.dis_speed();
}
void File::dis_fen()
{
	if((fp=fopen("d;\snake.txt","r"))==NULL)
	{
		new_file();
	}
	fp=fopen("d:\snake.txt","w");
	fprintf(fp,"%d",fen);
}
void File::new_file()
{
	fp=fopen("d;\snake.txt","a");
	fclose(fp);
}
void Game::Game_Fen()
{
	file.fp=NULL;
    file.fen=0;
	freopen("d:\snake.txt","r",stdin);
	scanf("%d",&file.fen);
	if(file.fen<snake.Snake_long-5)
	{
		file.fen=snake.Snake_long-5;
		file.dis_fen();
	}
	printf("%d",file.fen);
}
int main()
{
	Game game;
	game.Game_begin();
	system("cls");
	while(1)
	{
	    game.Game_bianjie();
		game.Game_play();
		if(game.Game_end())
		{
			break;
		}
		game.Game_sleep();
	}
	return 0;
}