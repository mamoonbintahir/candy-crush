
#include <iostream>
#include <time.h>
#include "header.h"
using namespace std;

const int rows = 8;
const int cols = 8;
int X1 = 10;
int Y1 = 60;
int totalSeconds = 60;



//random jewels before the game starts
void randomJewels(int arr[][cols])
{
	srand(time(NULL));
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			arr[i][j] = rand() % 5;
	
}

//draw the jewels with respect to the number according to the x and y passed
void drawdifferentJewel(int x, int y, int jewelNum, bool combo4, bool combo5)
{
	switch (jewelNum)
	{
	case 0:
		myEllipse(x, y, x + 30, y + 30, 255, 0, 255, 255, 0, 255);
		break;

	case 1:
		myEllipse(x, y, x + 30, y + 30, 255, 0, 0, 0, 0, 0);
		break;

	case 2:
		myRect(x, y, x + 30, y + 30, 0, 0, 255, 0, 0, 255);
		break;

	case 3:
		myTriangle(x, y, x + 30, y + 30, 122, 30, 255);
		break;

	case 4:
		myRect(x, y, x + 30, y + 30, 220, 250, 30, 0, 0, 0);
		break;
	}
	// for combo five shape//
	if (combo5)
		myTriangle(x + 7, y + 7, x + 22, y + 22, 255, 255, 255);

	//for combo 4 shape//
	else if (combo4)
		myEllipse(x + 7, y + 7, x + 22, y + 22, 255, 255, 255, 0, 0, 0);

}

void combo4Explosion(int arr[][cols], bool combo4[][cols], bool combo5[][cols], int x, int y, int& score)
{
	score += 600;
	combo4[y][x] = 0;
	combo5[y][x] = 0;


	int j = x - 1, i = y - 1;
	if (j < 0)
		j = 0;
	if (i < 0)
		i = 0;

	// for combo matrix explosion//
	int i1 = i + 2;
	if (i1 >= rows)
		i1 = rows - 1;

	for (; i1 > 2; i1--)
	{
		arr[i1][j] = arr[i1 - 3][j];
		arr[i1][j + 1] = arr[i1 - 3][j + 1];
		arr[i1][j + 2] = arr[i1 - 3][j + 2];
		// for combo 4//
		combo4[i1][j] = combo4[i1 - 3][j];
		combo4[i1][j + 1] = combo4[i1 - 3][j + 1];
		combo4[i1][j + 2] = combo4[i1 - 3][j + 2];

		combo5[i1][j] = combo5[i1 - 3][j];
		combo5[i1][j + 1] = combo5[i1 - 3][j + 1];
		combo5[i1][j + 2] = combo5[i1 - 3][j + 2];
	}

	int k = x - 1;
	if (k < 0)
		k = 0;
	for (; k < x + 2; k++)
	{
		arr[0][k] = rand() % 5;
		arr[1][k] = rand() % 5;
		arr[2][k] = rand() % 5;

		combo4[0][k] = 0;
		combo4[1][k] = 0;
		combo4[2][k] = 0;

		combo5[0][k] = 0;
		combo5[1][k] = 0;
		combo5[2][k] = 0;
	}
}
// for combo five explosion//
void combo5Explosion(int arr[][cols], bool combo4[][cols], bool combo5[][cols], int x, int y, int& score)
{
	combo4[y][x] = 0;
	combo5[y][x] = 0;

	score += 1000;
	for (int i = 0; i < rows; i++)
	{
		arr[i][x] = rand() % 5;
		combo4[i][x] = 0;
		combo5[i][x] = 0;
	}

	for (int i = y; i > 0; i--)
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = arr[i - 1][j];
			combo4[i][j] = combo4[i - 1][j];
			combo5[i][j] = combo5[i - 1][j];
		}

	for (int j = 0; j < cols; j++)
	{
		arr[0][j] = rand() % 5;
		combo4[0][j] = 0;
		combo5[0][j] = 0;
	}
}

//checks if jewls match in horizontal or combos are being formed or blasted in the process
void checkHorizontalmatch(int arr[][cols], bool combo4[][cols], bool combo5[][cols], int& score)
{

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols - 2; j++)
			if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2])
			{
				//checking some cases of 5-combo
				if (i + 2 < rows)
				{
					if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j])
					{
						for (int i1 = i + 1; i1 > 0; i1--)
						{
							arr[i1][j] = arr[i1 - 1][j];
							combo4[i1][j] = combo4[i1 - 1][j];
							combo5[i1][j] = combo5[i1 - 1][j];
						}
						arr[0][j] = rand() % 5;
						combo4[0][j] = 0;
						combo5[0][j] = 0;
						combo5[i + 2][j] = 1;
					}
					else if (arr[i][j] == arr[i + 1][j + 1] && arr[i][j] == arr[i + 2][j + 1])
					{
						for (int i1 = i + 1; i1 > 0; i1--)
						{
							arr[i1][j + 1] = arr[i1 - 1][j + 1];
							combo4[i1][j + 1] = combo4[i1 - 1][j + 1];
							combo5[i1][j + 1] = combo5[i1 - 1][j + 1];
						}
						arr[0][j + 1] = rand() % 5;
						combo4[0][j + 1] = 0;
						combo5[0][j + 1] = 0;
						combo5[i + 2][j + 1] = 1;
					}
					else if (arr[i][j] == arr[i + 1][j + 2] && arr[i][j] == arr[i + 2][j + 2])
					{
						for (int i1 = i + 1; i1 > 0; i1--)
						{
							arr[i1][j + 2] = arr[i1 - 1][j + 2];
							combo4[i1][j + 2] = combo4[i1 - 1][j + 2];
							combo5[i1][j + 2] = combo5[i1 - 1][j + 2];
						}
						arr[0][j + 2] = rand() % 5;
						combo4[0][j + 2] = 0;
						combo5[0][j + 2] = 0;
						combo5[i + 2][j + 2] = 1;
					}

				}
				else if (i - 2 >= 0)
				{
					if (arr[i][j] == arr[i - 1][j] && arr[i][j] == arr[i - 2][j])
					{
						for (int i1 = i - 1; i1 > 0; i1--)
						{
							arr[i1][j + 1] = arr[i1 - 1][j + 1];
							combo4[i1][j + 1] = combo4[i1 - 1][j + 1];
							combo5[i1][j + 1] = combo5[i1 - 1][j + 1];
						}
						arr[0][j + 1] = rand() % 5;
						combo4[0][j + 1] = 0;
						combo5[0][j + 1] = 0;
						combo5[i - 2][j + 1] = 1;
					}
				}

				//check if 4-combo is formed
				if (arr[i][j + 3] == arr[i][j])
					combo4[i][j + 3] = true;

				//check if any of three matches gems is a bonus gem
				if (combo5[i][j])
					combo5Explosion(arr, combo4, combo5, j, i, score);
				else if (combo5[i][j + 1])
					combo5Explosion(arr, combo4, combo5, j + 1, i, score);
				else if (combo5[i][j + 2])
					combo5Explosion(arr, combo4, combo5, j + 2, i, score);
				else if (combo4[i][j])
					combo4Explosion(arr, combo4, combo5, j, i, score);
				else if (combo4[i][j + 1])
					combo4Explosion(arr, combo4, combo5, j + 1, i, score);
				else if (combo4[i][j + 2])
					combo4Explosion(arr, combo4, combo5, j + 2, i, score);

				//if no combbo found, remove gems normally
				else {
					score += 100;
					for (int i1 = i; i1 > 0; i1--)
					{
						arr[i1][j] = arr[i1 - 1][j];
						arr[i1][j + 1] = arr[i1 - 1][j + 1];
						arr[i1][j + 2] = arr[i1 - 1][j + 2];

						combo4[i1][j] = combo4[i1 - 1][j];
						combo4[i1][j + 1] = combo4[i1 - 1][j + 1];
						combo4[i1][j + 2] = combo4[i1 - 1][j + 2];

						combo5[i1][j] = combo5[i1 - 1][j];
						combo5[i1][j + 1] = combo5[i1 - 1][j + 1];
						combo5[i1][j + 2] = combo5[i1 - 1][j + 2];
					}
					arr[0][j] = rand() % 5;
					arr[0][j + 1] = rand() % 5;
					arr[0][j + 2] = rand() % 5;

					combo4[0][j] = 0;
					combo4[0][j + 1] = 0;
					combo4[0][j + 2] = 0;

					combo5[0][j] = 0;
					combo5[0][j + 1] = 0;
					combo5[0][j + 2] = 0;
				}
			}

}

//checks if jewels match in vertical or combos are being formed or blasted in the process
void checkVerticalmatch(int arr[][cols], bool combo4[][cols], bool combo5[][cols], int& score)
{

	for (int i = 0; i < rows - 2; i++)
		for (int j = 0; j < cols; j++)
			if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j])
			{

				//checking some cases for 5 combo
				if (j + 2 < cols)
				{
					if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2])
					{
						for (int i1 = i; i1 > 0; i1--)
						{
							arr[i1][j + 1] = arr[i1 - 1][j + 1];
							combo4[i1][j + 1] = combo4[i1 - 1][j + 1];
							combo5[i1][j + 1] = combo5[i1 - 1][j + 1];
						}
						arr[0][j + 1] = rand() % 5;
						combo4[0][j + 1] = 0;
						combo5[0][j + 1] = 0;
						combo5[i][j + 2] = 1;
					}
					else if (arr[i][j] == arr[i + 1][j + 1] && arr[i][j] == arr[i + 1][j + 2])
					{
						for (int i1 = i + 1; i1 > 0; i1--)
						{
							arr[i1][j + 1] = arr[i1 - 1][j + 1];
							combo4[i1][j + 1] = combo4[i1 - 1][j + 1];
							combo5[i1][j + 1] = combo5[i1 - 1][j + 1];
						}
						arr[0][j + 1] = rand() % 5;
						combo4[0][j + 1] = 0;
						combo5[0][j + 1] = 0;
						combo5[i + 1][j + 2] = 1;
					}
					else if (arr[i][j] == arr[i + 2][j + 1] && arr[i][j] == arr[i + 2][j + 2])
					{
						for (int i1 = i + 2; i1 > 0; i1--)
						{
							arr[i1][j + 1] = arr[i1 - 1][j + 1];
							combo4[i1][j + 1] = combo4[i1 - 1][j + 1];
							combo5[i1][j + 1] = combo5[i1 - 1][j + 1];
						}
						arr[0][j + 1] = rand() % 5;
						combo4[0][j + 1] = 0;
						combo5[0][j + 1] = 0;
						combo5[i + 2][j + 2] = 1;
					}
				}
				else if (j - 2 >= 0)
				{
					if (arr[i][j] == arr[i + 1][j - 1] && arr[i][j] == arr[i + 1][j - 2])
					{
						for (int i1 = i + 1; i1 > 0; i1--)
						{
							arr[i1][j - 1] = arr[i1 - 1][j - 1];
							combo4[i1][j - 1] = combo4[i1 - 1][j - 1];
							combo5[i1][j - 1] = combo5[i1 - 1][j - 1];
						}
						arr[0][j + 1] = rand() % 5;
						combo4[0][j + 1] = 0;
						combo5[0][j + 1] = 0;
						combo5[i + 1][j - 2] = 1;
					}
				}

				//check if 4 combo is formed
				if (i + 3 < rows && arr[i + 3][j] == arr[i][j])
					combo4[i + 3][j] = true;

				//if any of 3 gems is a combo gem then do the respective explosion
				if (combo5[i][j])
					combo5Explosion(arr, combo4, combo5, j, i, score);
				else if (combo5[i + 1][j])
					combo5Explosion(arr, combo4, combo5, j, i + 1, score);
				else if (combo5[i + 2][j])
					combo5Explosion(arr, combo4, combo5, j, i + 2, score);

				else if (combo4[i][j])
					combo4Explosion(arr, combo4, combo5, j, i, score);
				else if (combo4[i + 1][j])
					combo4Explosion(arr, combo4, combo5, j, i + 1, score);
				else if (combo4[i + 2][j])
					combo4Explosion(arr, combo4, combo5, j, i + 2, score);

				//if no combo explosion is possible remove gems as normal
				else {
					score += 100;
					for (int i1 = i + 2; i1 > 2; i1--)
					{
						arr[i1][j] = arr[i1 - 3][j];
						combo4[i1][j] = combo4[i1 - 3][j];
						combo5[i1][j] = combo5[i1 - 3][j];
					}

					arr[0][j] = rand() % 5;
					arr[1][j] = rand() % 5;
					arr[2][j] = rand() % 5;

					combo4[0][j] = 0;
					combo4[1][j] = 0;
					combo4[2][j] = 0;

					combo5[0][j] = 0;
					combo5[1][j] = 0;
					combo5[2][j] = 0;
				}
			}
}

//printing the score
void printScore(int score, int& startTime)
{
	gotoxy(5, 1);
	cout << "Score: " << score;
	gotoxy(20, 1);
	cout << "Time remaining: " << 60 - ((int)(GetTickCount() - startTime) / 1000) << " seconds                             ";
}

//check if move towards left is possible
bool checkleftSwapp(int arr[][cols], int x, int y)
{
	if (x - 1 >= 0 && y - 1 >= 0 && y + 1 < rows)
		if (arr[y][x] == arr[y - 1][x - 1] && arr[y][x] == arr[y + 1][x - 1])
			return true;
	if (x - 1 >= 0 && y + 2 < rows)
		if (arr[y][x] == arr[y + 1][x - 1] && arr[y][x] == arr[y + 2][x - 1])
			return true;
	if (x - 1 >= 0 && y - 2 >= 0 && y + 1 < rows)
		if (arr[y][x] == arr[y - 1][x - 1] && arr[y][x] == arr[y - 2][x - 1])
			return true;
	if (x - 1 >= 0 && y - 2 >= 0)
		if (arr[y][x - 1] == arr[y - 1][x] && arr[y][x - 1] == arr[y - 2][x])
			return true;
	if (x - 1 >= 0 && y - 1 >= 0 && y + 1 < rows)
		if (arr[y][x - 1] == arr[y - 1][x] && arr[y][x - 1] == arr[y + 1][x])
			return true;
	if (x - 1 >= 0 && y + 2 < rows)
		if (arr[y][x - 1] == arr[y + 1][x] && arr[y][x - 1] == arr[y + 2][x])
			return true;
	if (x - 3 >= 0)
		if (arr[y][x] == arr[y][x - 2] && arr[y][x] == arr[y][x - 3])
			return true;
	if (x + 3 < cols)
		if (arr[y][x - 1] == arr[y][x + 1] && arr[y][x - 1] == arr[y][x + 2])
			return true;
	return false;
}

//check if move toward right is possible
bool checkrightSwapp(int arr[][cols], int x, int y)
{
	if (x + 1 < cols && y - 1 >= 0 && y + 1 < rows)
		if (arr[y][x] == arr[y - 1][x + 1] && arr[y][x] == arr[y + 1][x + 1])
			return true;
	if (x + 1 < cols && y + 2 < rows)
		if (arr[y][x] == arr[y + 1][x + 1] && arr[y][x] == arr[y + 2][x + 1])
			return true;
	if (x + 1 < cols && y - 2 >= 0 && y + 1 < rows)
		if (arr[y][x] == arr[y - 1][x + 1] && arr[y][x] == arr[y - 2][x + 1])
			return true;
	if (x + 1 < cols && y - 2 >= 0)
		if (arr[y][x + 1] == arr[y - 1][x] && arr[y][x + 1] == arr[y - 2][x])
			return true;
	if (x + 1 < cols && y - 1 >= 0 && y + 1 < rows)
		if (arr[y][x + 1] == arr[y - 1][x] && arr[y][x + 1] == arr[y + 1][x])
			return true;
	if (x + 1 < cols && y + 2 < rows)
		if (arr[y][x + 1] == arr[y + 1][x] && arr[y][x + 1] == arr[y + 2][x])
			return true;
	if (x + 3 < cols)
		if (arr[y][x] == arr[y][x + 2] && arr[y][x] == arr[y][x + 3])
			return true;
	if (x - 3 >= 0)
		if (arr[y][x + 1] == arr[y][x - 1] && arr[y][x - 1] == arr[y][x - 2])
			return true;
	return false;
}

//check if move upwards is possible
bool checkupperSwapp(int arr[][cols], int x, int y)
{
	if (y - 1 >= 0 && x + 1 < cols && x - 1 >= 0)
		if (arr[y][x] == arr[y - 1][x - 1] && arr[y][x] == arr[y - 1][x + 1])
			return true;
	if (y - 1 >= 0 && x - 2 >= 0)
		if (arr[y][x] == arr[y - 1][x - 1] && arr[y][x] == arr[y - 1][x - 2])
			return true;
	if (y - 1 >= 0 && x + 2 < cols)
		if (arr[y][x] == arr[y - 1][x + 1] && arr[y][x] == arr[y - 1][x + 2])
			return true;
	if (y - 1 >= 0 && x + 1 < cols && x - 1 >= 0)
		if (arr[y - 1][x] == arr[y][x - 1] && arr[y - 1][x] == arr[y][x + 1])
			return true;
	if (y - 1 >= 0 && x - 2 >= 0)
		if (arr[y - 1][x] == arr[y][x - 1] && arr[y - 1][x] == arr[y][x - 2])
			return true;
	if (y - 1 >= 0 && x + 2 < cols)
		if (arr[y - 1][x] == arr[y][x + 1] && arr[y - 1][x] == arr[y][x + 2])
			return true;
	if (y - 3 >= 0)
		if (arr[y][x] == arr[y - 2][x] && arr[y][x] == arr[y - 3][x])
			return true;
	if (y - 1 >= 0 && y + 2 < rows)
		if (arr[y - 1][x] == arr[y + 1][x] && arr[y - 1][x] == arr[y + 2][x])
			return true;
	return false;
}

//check if move downwards is possible
bool checkdownSwapp(int arr[][cols], int x, int y)
{
	if (y + 1 < rows && x + 1 < cols && x - 1 >= 0)
		if (arr[y][x] == arr[y + 1][x - 1] && arr[y][x] == arr[y + 1][x + 1])
			return true;
	if (y + 1 < rows && x - 2 >= 0)
		if (arr[y][x] == arr[y + 1][x - 1] && arr[y][x] == arr[y + 1][x - 2])
			return true;
	if (y + 1 < rows && x + 2 < cols)
		if (arr[y][x] == arr[y + 1][x + 1] && arr[y][x] == arr[y + 1][x + 2])
			return true;
	if (y + 1 < rows && x + 1 < cols && x - 1 >= 0)
		if (arr[y + 1][x] == arr[y][x - 1] && arr[y + 1][x] == arr[y][x + 1])
			return true;
	if (y + 1 < rows && x - 2 >= 0)
		if (arr[y + 1][x] == arr[y][x - 1] && arr[y + 1][x] == arr[y][x - 2])
			return true;
	if (y + 1 < rows && x + 2 < cols)
		if (arr[y + 1][x] == arr[y][x + 1] && arr[y + 1][x] == arr[y][x + 2])
			return true;
	if (y + 3 < rows)
		if (arr[y][x] == arr[y + 2][x] && arr[y][x] == arr[y + 3][x])
			return true;
	if (y - 2 >= 0 && y + 1 < rows)
		if (arr[y + 1][x] == arr[y - 1][x] && arr[y + 1][x] == arr[y - 2][x])
			return true;
	return false;
}

//check which key is pressed and if the move according to the pressed key is possible, do it
void keysmover(int& x, int& y, bool& selected, int arr[][cols], bool combo4[][cols], bool combo5[][cols])
{
	int keyPressed = 0;
	if (isCursorKeyPressed(keyPressed))
	{
		if (!selected)
		{
			if (keyPressed == 1 && x > 0)
				x--;
			else if (keyPressed == 3 && x < cols - 1)
				x++;
			else if (keyPressed == 2 && y > 0)
				y--;
			else if (keyPressed == 4 && y < rows - 1)
				y++;
			else if (keyPressed == 5)
				selected = true;
		}
		else
		{
			if (keyPressed == 1 && x > 0 && checkleftSwapp(arr, x, y))
			{
				swap(arr[y][x], arr[y][x - 1]);
				swap(combo4[y][x], combo4[y][x - 1]);
				swap(combo5[y][x], combo5[y][x - 1]);
			}
			else if (keyPressed == 3 && x < cols - 1 && checkrightSwapp(arr, x, y))
			{
				swap(arr[y][x], arr[y][x + 1]);
				swap(combo4[y][x], combo4[y][x + 1]);
				swap(combo5[y][x], combo5[y][x + 1]);
			}
			else if (keyPressed == 2 && y > 0 && checkupperSwapp(arr, x, y))
			{
				swap(arr[y][x], arr[y - 1][x]);
				swap(combo4[y][x], combo4[y - 1][x]);
				swap(combo5[y][x], combo5[y - 1][x]);
			}
			else if (keyPressed == 4 && y < rows - 1 && checkdownSwapp(arr, x, y))
			{
				swap(arr[y][x], arr[y + 1][x]);
				swap(combo4[y][x], combo4[y + 1][x]);
				swap(combo5[y][x], combo5[y + 1][x]);
			}
			selected = false;
		}
	}
	if (!selected)
		myRect(X1 + x * 50, Y1 + y * 50, X1 + 50 + (x * 50), Y1 + 50 + (y * 50), 250, 150, 130, 0, 0, 0);
	else
		myRect(X1 + x * 50, Y1 + y * 50, X1 + 50 + (x * 50), Y1 + 50 + (y * 50), 0, 255, 0, 0, 0, 0);
}

int main()
{
	int arr[rows][cols];			     //the main 2D array which stores an int corresponding to the jewel

	int activeX = 0, activeY = 0;	   	//a two size array that stores the indices of the cell active for swapping

	int score = 0;					    //our score variable

	bool combo4[rows][cols] = { 0 };    //an array of same size as main array that tells where we have formed a 4 candy
	bool combo5[rows][cols] = { 0 };
	bool selectedCell = false;
	randomJewels(arr);
	int startTime = GetTickCount();
	int endTime = GetTickCount() + (1000 * totalSeconds);

	while (GetTickCount() < endTime)
	{
		/*system("cls");*/
		myRect(X1 - 5, Y1 - 5, X1 + (50 * cols) + 5, Y1 + (50 * rows) + 5, 20, 230, 230, 0, 0, 0);
		printScore(score, startTime);
		keysmover(activeX, activeY, selectedCell, arr, combo4, combo5);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				int jewellocationX = X1 + (50 * j + 10);
				int jewellocationY = Y1 + (50 * i + 10);
				drawdifferentJewel(jewellocationX, jewellocationY, arr[i][j], combo4[i][j], combo5[i][j]);
			}
			
		}
		Sleep(900);
		checkHorizontalmatch(arr, combo4, combo5, score);
		checkVerticalmatch(arr, combo4, combo5, score);
	}
	/*system("cls");*/
	cout << "  your Time is up" << endl;
	cout << "Total Score is: " << score << endl;
	system("pause");
	return 0;
}
