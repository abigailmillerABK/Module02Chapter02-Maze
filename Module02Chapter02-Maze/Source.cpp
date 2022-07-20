/*
Challenge:
Create your maze game as demonstrated in the videos
*/

#include <iostream>
#include <conio.h>

constexpr char kPlayerSymbol = '@';

int GetIndexFromCoordinates(int x, int y, int width);
void DrawLevel(char level[], int width, int height, int playerX, int playerY);
bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& hasKey);

void main() {

	constexpr int kWidth = 12;
	constexpr int kHeight = 12;

	char levelArray[]{
		'+','-','-','-','-','-','-','-','-','-','-','+',
		'|',' ',' ','-','-','-','-',' ',' ',' ',' ','|',
		'|',' ',' ','-','-','-','-',' ',' ',' ',' ','|',
		'|',' ',' ','-','-','-','-',' ',' ',' ',' ','|',
		'|',' ',' ','-','-','-','-',' ',' ',' ',' ','|',
		'|',' ',' ','-','-','-','-',' ',' ',' ','*','|',
		'|',' ',' ','-','-','-','-',' ',' ',' ',' ','|',
		'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
		'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
		'|',' ',' ',' ',' ',' ',' ','+','_','_','_','|',
		'|',' ',' ',' ',' ',' ',' ','D',' ',' ','X','|',
		'+','-','-','-','-','-','-','+','-','-','-','+',
	};
	int playerX = 1;
	int playerY = 1;
	bool hasKey = false;
	bool gameOver = false;

	while (!gameOver) {
		system("cls");
		DrawLevel(levelArray, kWidth, kHeight,playerX, playerY);
		gameOver = UpdatePlayerPosition(levelArray, playerX, playerY, kWidth, hasKey);
	}
	system("cls");
	DrawLevel(levelArray, kWidth, kHeight, playerX, playerY);
	std::cout << "You Won" << "\n";

}
	

int GetIndexFromCoordinates(int x, int y, int width)
{
	return x + y * width;
}

void DrawLevel(char level[], int width, int height, int playerX, int playerY)
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (playerX == x && playerY == y) {
				std::cout << kPlayerSymbol;
			}
			else {
				int index = GetIndexFromCoordinates(x, y, width);
				std::cout << level[index];
			}
		}
		std::cout << "\n";
	}
}

bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& hasKey) {
	char input = _getch();

	int newPlayerX = playerX;
	int newPlayerY = playerY;

	switch (input) {
	case 'w':
		newPlayerY--;
		break;
	case 'a':
		newPlayerX--;
		break;
	case 's':
		newPlayerY++;
		break;
	case 'd':
		newPlayerX++;
		break;
	default:
		break;
	}

	int index = GetIndexFromCoordinates(newPlayerX, newPlayerY, width);
	if (level[index] == ' '){
		playerX = newPlayerX;
		playerY = newPlayerY;
	}
	else if (level[index] == '*') {
		hasKey = true;
		level[index] = ' ';
		playerX = newPlayerX;
		playerY = newPlayerY;
	}
	else if (level[index] == 'D' && hasKey == true) {
		level[index] = ' ';
		hasKey = false;
		playerX = newPlayerX;
		playerY = newPlayerY;
	}
	else if (level[index] == 'X') {
		level[index] = ' ';
		playerX = newPlayerX;
		playerY = newPlayerY;
		return true;
	}
	return false;
}
