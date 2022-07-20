/*
Transcribed code from CG Spectrum Module 02 Chapter 02
*/

#include <iostream>
#include <conio.h>

constexpr char kCursor = '_';

constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;

constexpr int kEsc = 27;

void GetLevelDimensions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);
int GetIndexFromXY(int x, int y, int width);
void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int levelWidth, int levelHeight);

void main() {
	int levelWidth;
	int levelHeight;

	GetLevelDimensions(levelWidth, levelHeight);

	char* pLevel = new char[levelWidth * levelHeight];

	for (int i = 0; i < levelWidth * levelHeight; i++) {
		pLevel[i] = ' ';
	}

	int cursorX = 0;
	int cursorY = 0;
	bool doneEditing = false;
	while(!doneEditing){
		system("CLS");
		DisplayLevel(pLevel, levelWidth, levelHeight,cursorX,cursorY);
		doneEditing = EditLevel(pLevel,cursorX,cursorY,levelWidth,levelHeight);
	}	
	system("cls");
	DisplayLevel(pLevel, levelWidth, levelHeight, -1, -1);

	delete[] pLevel;
	pLevel = nullptr;
}

bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int levelWidth, int levelHeight) {
	int newCursorX = cursorX;
	int newCursorY = cursorY;

	int intInput = _getch();

	if (intInput == kArrowInput) {
		int arrowInput = _getch();
		switch (arrowInput) {
		case kLeftArrow:
			newCursorX--;
			break;
		case kRightArrow:
			newCursorX++;
			break;
		case kUpArrow:
			newCursorY--;
			break;
		case kDownArrow:
			newCursorY++;
			break;
		}
		if (newCursorX < 0) {
			newCursorX = 0;
		}
		else if (newCursorX >= levelWidth) {
			newCursorX = levelWidth - 1;
		}
		if (newCursorY < 0) {
			newCursorY = 0;
		}
		else if (newCursorY >= levelHeight) {
			newCursorY = levelHeight - 1;
		}

		cursorX = newCursorX;
		cursorY = newCursorY;
	}
	else {
		if (intInput == kEsc) {
			return true;
		}
		else {
			int index = GetIndexFromXY(newCursorX, newCursorY, levelWidth);
			pLevel[index] = (char)intInput;
		}
	}
	return false;

}

void GetLevelDimensions(int& width, int& height)
{
	std::cout << "Enter the width of your level: ";
	std::cin >> width;

	std::cout << "\nEnter the height of your level: ";
	std::cin >> height;
}

void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY) {
	DisplayTopBorder(width);

	for (int y = 0; y < height; y++) {
		DisplayLeftBorder();
		for (int x = 0; x < width; x++) {
			if (cursorX == x && cursorY == y) {
				std::cout << kCursor;
			}
			else {
				int index = GetIndexFromXY(x, y, width);
				std::cout << pLevel[index];
			}
		}
		DisplayRightBorder();
	}

	DisplayBottomBorder(width);
}

void DisplayTopBorder(int width) {
	std::cout << kTopLeftBorder;
	for (int i = 0; i < width; i++) {
		std::cout << kHorizontalBorder;
	}
	std::cout << kTopRightBorder << "\n";
}
void DisplayBottomBorder(int width) {
	std::cout << kBottomLeftBorder;
	for (int i = 0; i < width; i++) {
		std::cout << kHorizontalBorder;
	}
	std::cout << kBottomRightBorder << "\n";
}
void DisplayLeftBorder() {
	std::cout << kVerticalBorder;
}
void DisplayRightBorder() {
	std::cout << kVerticalBorder << "\n";
}


int GetIndexFromXY(int x, int y, int width) {
	return (x + y * width);
}