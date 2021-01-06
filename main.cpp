#include<iostream>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<fstream>
#include<sstream>
#include<string.h>


#define MAXSNAKESIZE 100
int height = 25;
int width = 50;
bool gameover;
bool print =false;
int score = 0;
char c;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

using namespace std;

void gotoxy (int x, int y)
    {
         COORD coordinates;
         coordinates.X = x;
         coordinates.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
    }


class Sc
{
	private:
		string name;
		int SCORE;
		string scorecard;
	public:
		void setName(string s)
		{
			name = s;
		}
		void setScore(int s)
		{
			SCORE = s;
		}
		void setScorecard()
		{
		    stringstream ss;
		    ss<<SCORE;
		    string score;
		    ss>>score;

		    scorecard = name + " - " + score;
		}
		string getScorecard()
		{
			return scorecard;
		}
		string getName()
		{
			return name;
		}
		int getScore()
		{
			return SCORE;
		}
};


class Point
{
	private:
		int x;
		int y;
	public:
		Point()
		{
			x = y = 0;
		}
		Point(int x,int y)
		{
			this->x = x;
			this->y = y;
		}
		void SetPoint(int x,int y)
		{
			this->x = x;
			this->y = y;
		}
		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}
		void setX(int i)
		{
			this->x = i;
		}
		void setY(int i)
		{
			this->y = i;
		}
		void MoveUp()
		{
			y--;
		}
		void MoveDown()
		{
			y++;
		}
		void MoveLeft()
		{
			x--;
		}
		void MoveRight()
		{
			x++;
		}
		void isEqual(Point *p)
		{
			p->x = this->x;
			p->y = this->y;
		}
		void Debug()
		{
			cout<<"("<<x<<","<<y<<")";
		}
};

class Snake
{
	private:
		Point *cell[MAXSNAKESIZE];
		int size;
		char dir;
		Point fruit;
	public:
		Snake()
		{
			size = 1;
			dir = STOP;
			cell[0] = new Point(width/2,height/2);
			for(int i = 1;i<MAXSNAKESIZE;i++)
			{
				cell[i] = NULL;
			}
			fruit.SetPoint(rand()%40,rand()%30);
		}
		void AddCell(int x,int y)
		{
			cell[size] = new Point(x,y);
			size = size +1;
		}
		void TurnUp()
		{
			cell[0]->MoveUp();
		}
		void TurnDown()
		{
			cell[0]->MoveDown();
		}
		void TurnLeft()
		{
			cell[0]->MoveLeft();
		}
		void TurnRight()
		{
			cell[0]->MoveRight();
		}
		void Head(int x,int y)
		{
			cell[0]->SetPoint(x,y);
		}

		void check()
		{
			for(int i=1;i<size;i++)
			{
				if(cell[i]->GetX() == cell[0]->GetX() && cell[i]->GetY() == cell[0]->GetY())
				{
					for (int j = i;j<size;j++)
					{
						cell[j] = NULL;
						score-=50;
					}
					size = i;
				}
			}
		}

		void Move()
		{
			for(int i = size-1;i>0;i--)
			{
				int x = cell[i-1]->GetX();
				int y = cell[i-1]->GetY();
				cell[i]->setX(x);
				cell[i]->setY(y);
			}
		}

		void Randomfruit()
		{
			fruit:
			fruit.SetPoint(rand()%(width-2),rand()%(height-2));
			if(fruit.GetX() == 0 || fruit.GetY() == 0)
			{
				goto fruit;
			}

		}
		void EatFruit()
		{
			if(cell[0]->GetX() == fruit.GetX() && cell[0]->GetY() == fruit.GetY())
			{
				AddCell(0,0);
				score+= 100;
				Randomfruit();
			}
		}
		int snakesize()
		{
			return size;
		}
		int getpositionX(int i=0)
		{
			return cell[i]->GetX();
		}
		int getpositionY(int i=0)
		{
			return cell[i]->GetY();
		}

		int getfruitX()
		{
			return fruit.GetX();
		}
		int getfruitY()
		{
			return fruit.GetY();
		}


		void Debug()
		{
			for(int i=0;i<size;i++)
			{
				cell[i]->Debug();
			}
		}
};

void Layout()
{
	system("cls");
	bool print = false;
	for(int i=0;i<width+2;i++)
	{
		cout<<"#";
	}
	cout<<endl;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			bool print = false;
			if(i == 10)
			{
				if(j==12)
				{
					cout<<"1.Start game";
				}
				if(j>=12 && j<24)
				{
					print = true;
				}

			}

			if(i == 12)
			{
				if(j==12)
				{
					cout<<"2.Game Instructions";
				}
				if(j>=12 && j<31)
				{
					print = true;
				}

			}

			if(i == 14)
			{
				if(j==12)
				{
					cout<<"3.Our Scorers";
				}
				if(j>=12 && j<25)
				{
					print = true;
				}

			}

			if(j==0)
			{
				cout<<"#";
			}
			if(!print)
			{
				cout<<" ";
			}
			if(j==width-1)
			{
				cout<<"#";
			}
		}
		cout<<endl;
	}
	for(int i=0;i<width+2;i++)
	{
		cout<<"#";
	}
	cout<<endl;
	cout<<"Enter your choice :- ";
}

void Draw(Snake &s)
{
	int k = 1;
	for(int i=0;i<height;i++)
	{
	    gotoxy(1,k++);
		for(int j=0;j<width;j++)
		{
			if(i== s.getpositionY(0) && j== s.getpositionX(0))
			{
				cout<<"O";
			}
			else if(i==s.getfruitY() && j== s.getfruitX())
			{
				cout<<"F";
			}
			else
			{
				bool print = false;
				for(int k= 0;k< s.snakesize();k++)
				{
					if(s.getpositionX(k) == j && s.getpositionY(k) == i)
					{
						cout<<"o";
						print = true;
					}
				}
				if(!print)
				{
					cout<<" ";
				}
			}
		}
		cout<<endl;
	}

	gotoxy(0,height+2);
	cout<<"                      ";
	gotoxy(0,height+2);
	cout<<" SCORE :- "<<score;

}

int Input(Snake &s)
{
	if(_kbhit())
	{
		c = getch();
	}
	if(dir == UP && (c == 's' || c == 'S'))
	{
		return 1;
	}
	if(dir == DOWN && (c == 'w' || c == 'W'))
	{
		return 1;
	}
	if(dir == LEFT && (c == 'd' || c == 'D'))
	{
		return 1;
	}
	if(dir == RIGHT && (c == 'a' || c == 'A'))
	{
		return 1;
	}
	switch(c)
	{
		case 'w':
		case 'W':
			dir = UP;
			break;
		case 's':
		case 'S':
			dir = DOWN;
			break;
		case 'a':
		case 'A':
			dir = LEFT;
			break;
		case 'd':
		case 'D':
			dir = RIGHT;
			break;
	}
	return 0;
}

void Logic(Snake &s)
{

	s.Move();

	switch(dir)
	{
		case LEFT: s.TurnLeft();
		          break;
		case RIGHT: s.TurnRight();
		          break;
		case UP: s.TurnUp();
		          break;
		case DOWN: s.TurnDown();
		          break;
	}

	s.EatFruit();

	s.check();

	if(s.getpositionX() <0 || s.getpositionX() >= width)
	{
		gameover = true;
	}
	if(s.getpositionY() < 0 || s.getpositionY() >= height)
	{
		gameover = true;
	}
}

int Score()
{
	system("cls");
	for(int i=0;i<width+2;i++)
	{
		cout<<"#";
	}
	cout<<endl;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			bool print = false;
			if(i == (height/2) - 1)
			{
				if(j==16)
				{
				 	cout<<"Your Score is "<<score;
				}
				if(score < 100)
				{
					if(j>=16 && j<31)
					{
						print = true;
					}
				}
				else if(score > 900)
				{
					if(j>=16 && j<34)
					{
						print = true;
					}
				}
				else
				{
					if(j>=16 && j<33)
					{
						print = true;
					}
				}
			}
			if(j==0)
			{
				cout<<"#";
			}
			if(!print)
			{
				cout<<" ";
			}
			if(j==width-1)
			{
				cout<<"#";
			}
		}
		cout<<endl;
	}
	for(int i=0;i<width+2;i++)
	{
		cout<<"#";
	}
	cout<<endl;
	cout<<"Do you want to save your score(Y/N)? ";



}

int main()
{
	srand((unsigned)time(NULL));

	int x;
	char ch;
	char c;
	Sc sc;
	label:
	Snake snake;
	snake.Randomfruit();
	gameover = false;
	score = 0;
	Layout();
	cin>>x;
	if(x == 1)
		{

			while(!gameover)
			{
				Draw(snake);
				Input(snake);
				Logic(snake);
			//	Sleep(10);
			}
			Score();
			cin>>ch;
			if(ch == 'y')
			{
                string scorecard;
				char *s = new char[20];
				cout<<"Enter your Name : ";
				cin>>s;
				sc.setName(s);
				sc.setScore(score);
				sc.setScorecard();
				scorecard = sc.getScorecard();
				cout<<scorecard;
				ofstream ofs("Scores.txt",ios::app);
				ofs<<scorecard<<endl;
				ofs.close();
			}
			cout<<endl;
			cout<<endl;
			cout<<"Do you want to start again(Y/N)?";
			cin>>c;
			if(c == 'y')
			{
				goto label;
			}
			else if(c == 'n')
			{
				gameover = true;
			}

		}
	if(x == 2)
	{
			Draw(snake);
			cout<<endl;
			cout<<"GAME INSTRUCTIONS :-"<<endl;
			cout<<"1. Snake has to eat the fruit to get bigger."<<endl;
			cout<<"2. If Snake enters the wall from one side, then it'll come out from the opposite side."<<endl;
			cout<<"3. If the game bites itself, Game is over."<<endl;
			cout<<"Do you want to start the game(Y/N)?";
			cin>>ch;
			if(ch == 'y')
			{
				while(!gameover)
				{
					Draw(snake);
					Input(snake);
					Logic(snake);
				//	Sleep(10);
				}
				Score();
				cin>>ch;
			if(ch == 'y')
			{

				char *s = new char[20];
				cout<<"Enter your Name : ";
				cin>>s;
				cout<<s;
				sc.setName(s);
				sc.setScore(score);
				sc.setScorecard();
				ofstream ofs("Scores.txt",ios::app);
				string scorecard = sc.getScorecard();
				ofs<<scorecard<<endl;
				ofs.close();
			}
				cout<<"Do you want to start again(Y/N)?";
				cin>>c;
				if(c == 'y')
				{
					goto label;
				}
				else if(c == 'n')
				{
					gameover = true;
				}
			}
			else if(ch =='n')
			{
				gameover = true;
			}
	}
	if(x == 3)
	{
		Draw(snake);
		cout<<endl<<endl;
		cout<<"Our Scorers : ";
        cout<<endl<<"--------------------------------------------------"<<endl;
		string scorecard;
		ifstream ifs("Scores.txt");
		int k = 1;
		while(ifs)
        {
            getline(ifs,scorecard);
            if(scorecard.empty())
                break;
            cout<<k++<<". "<<scorecard;
            cout<<endl<<"--------------------------------------------------"<<endl;
        }
		ifs.close();
		cout<<endl;
		while(!(_kbhit()))
        {
            gotoxy(0,height+4+(2*k));
		    cout<<"Press any key";
		    Sleep(200);
		    gotoxy(0,height+4+(2*k));
		    cout<<"             ";
		    Sleep(200);

        }
		if(_getch())
		{
			goto label;
		}
	}

	return 0;
}
