#include<iostream>
#include<conio.h>
#include<iomanip>
using namespace std;

const int Height = 20;
const int Width = 20;
int x, y, foodX, foodY, score;
int TailX[100], TailY[100];
int nTail;
bool gameover;

enum eDirect { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirect dir;

void Setup() {
	gameover = false;
	dir = STOP;
	x = Height / 2;
	y = Width / 2;
	foodX = rand() % Height;
	foodY = rand() % Width;
	score = 0;
};
void Draw() {
	system("cls");
	for (int i = 0; i < Height + 2; i++)
		cout << setw(2) << "#";
	cout << endl;

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			if (j == 0)
				cout << setw(2) << "#";
			if (y == i && x == j) {
				cout << "O";
			}
			else if (foodX == j && foodY == i) {
				cout << "F";
			}
			else
			{
				bool printtail = false;
				for (int k = 0; k < nTail; k++)
				{
					if (TailX[k] == j && TailY[k] == i) {
						cout << "o";
						printtail = true;
					}
				}
				if (!printtail) {
					cout << setw(2) << " ";
				}
			}
			if (j == Width - 1)
				cout << setw(2) << "#";

		}
		cout << endl;
	}

	for (int i = 0; i < Width + 2; i++)
		cout << setw(2) << "#";
	cout << endl;
	cout << "Score : " << score << endl;
};

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameover = true;
			break;
		}
	}
}

void Logic() {
	int prevX, prevY;
	prevX = TailX[0];
	prevY = TailY[0];
	int prev2X,prev2Y;
	TailX[0] = x;
	TailY[0] = y;
	for (int i = 1; i < nTail; i++) 
	{
		prev2X = TailX[i];
		prev2Y = TailY[i];
		TailX[i] = prevX;
		TailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x >= Height) x = 0; else if (x < 0) x = Height - 1;
	if (y >= Width) y = 0; else if (y < 0) y = Width - 1;

	if (x == foodX && y == foodY)
	{
		++nTail;
		foodX = rand() % Height;
		foodY = rand() % Width;
		score += 10;
	}

	for (int i = 0; i < nTail; i++)
		if (TailX[i] == x && TailY[i] == y)
			gameover = true;
}

int main() {
	Setup();
	while (!gameover) {
		Draw();
		Input();
		Logic();
	}
	return 0;
}