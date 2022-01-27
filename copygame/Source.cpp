// Header Files
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <fstream>

// Global Constants
const int Width = 70;
const int Height = 26;

/* HANDLE is a handle to an object. This type is declared in Windows.h
GETStdHandle() retrieves a handle to the specified standard device here:
STD_OUTPUT_HANDLE The standard output device. Initially, this is the active console screen buffer
*/

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

// Global Variables & Arrays
int EnemyVertical[2];
int EnemyHorizontal[2];
int EnemyFlag[2];
char SpaceShip = 202;
char Enemy = 254;
int ShipPosition = -1 + Width / 2;
int score = 0;
int life = 3;
int level = 1;
int Bullets[20][2];
int BulletsIndex = 0;

using namespace std;


// Function Prototypes
void SetCursorPosition(int x, int y);
void Cursor(bool visible, DWORD size);
void GameWindow();
void GenerateEnemy1(int ind);
void GenerateEnemy2(int ind);
void SpawnEnemies(int ind);
void RemoveEnemies(int ind);
void ResetEnemies(int ind);
void GenerateBullets();
void NavigateBullets();
void SpawnBullets();
void RemoveBullets();
void SpawnShip();
void RemoveShip();
int CollisionWithEnemy();
int HitEnemy();
void GameOver();
void GameScore();
void GameWin();
void UpdateLife();
void UpdateLevel();
void GameInstructions();
void play();
void GameReset();


//-------------------------------------------- Huzan (in) --------------------------------------------------------------------------

// Main Function
int main()
{
	Cursor(0, 1);
	srand(time(0));

	do {
		SetConsoleTextAttribute(console, 7);
		system("cls");
		cout << endl;
		cout << "   ������������������������������������������������������������������������������������������������������" << endl;
		cout << "   ��                                                                    ��" << "                            ��" << endl;
		cout << "   ��                                                                    ��" << "                            ��" << endl;
		cout << "   ��                                                                    ��" << "                            ��" << endl;
		cout << "   ��                                                          " << char(254) << "         ��                            ��" << endl;
		cout << "   ��     ____  ___   ___   ___  ___                                     ��" << "                            ��" << endl;
		cout << "   ��    |     |   | |   | |    |                              " << char(15) << "         ��                            ��" << endl;
		cout << "   ��    |___  |___| |___| |    |___                                     ��" << "                            ��" << endl;
		cout << "   ��        | |     |   | |    |                                        ��" << "                            ��" << endl;
		cout << "   ��    ____| |     |   | |___ |___                                     ��" << "                            ��" << endl;
		cout << "   ��  ________________________________                                  ��" << "      SELECT OPTIONS        ��" << endl;
		cout << "   ��                                                                    ��" << "    ------------------      ��" << endl;
		cout << "   ��              _____        ____   ____  _____ _____ ______          ��" << "  PRESS 1 TO PLAY           ��" << endl;
		cout << "   ��              |     |   | |    | |    |   |   |     |    |          ��" << "  PRESS 2 FOR INSTRCUTIONS  ��" << endl;
		cout << "   ��              |___  |___| |    | |    |   |   |____ |____|          ��" << "  PRESS 3 TO EXIT           ��" << endl;
		cout << "   ��                  | |   | |    | |    |   |   |     |  \\            ��" << "                            ��" << endl;
		cout << "   ��              ____| |   | |____| |____|   |   |____ |   \\           ��" << "                            ��" << endl;
		cout << "   ��           _________________________________________________        ��" << "                            ��" << endl;
		cout << "   ��                                                                    ��" << "                            ��" << endl;
		cout << "   ��                                                                    ��" << "                            ��" << endl;
		cout << "   ��                                                                    ��" << "                            ��" << endl;
		cout << "   ��                                                                    ��" << "                            ��" << endl;
		cout << "   ��                                                          " << char(202) << "         ��                            ��" << endl;
		cout << "   ��                                                                    ��" << "                            ��" << endl;
		cout << "   ��                                                                    ��" << "                            ��" << endl;
		cout << "   ������������������������������������������������������������������������������������������������������" << endl;
		Sleep(100);

		/*
		_getche() function waits for any character
		input from keyboard and it will also echo
		the input character on to the output screen.
		*/

		char operation = _getche();

		if (operation == '1')
			play();
		else if (operation == '2')
			GameInstructions();
		else if (operation == '3')
			exit(0);

	} while (1);

	return 0;
}

// Function for making game's border screen.
void GameWindow() {
	//the following function allows to change color.
	SetConsoleTextAttribute(console, 7);
	system("cls");
	cout << endl;
	cout << "   ������������������������������������������������������������������������������������������������������" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "       SPACE SHOOTER        ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "������������������������������" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "         SCORE:             ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "������������������������������" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "         LIFE:              ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "������������������������������" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "         Level:             ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "������������������������������" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "         CONTROLS           ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << " PRESS SPACEBAER - TO SHOOT ��" << endl;
	cout << "   ��                                                                    ��" << " PRESS A - TO MOVE LEFT     ��" << endl;
	cout << "   ��                                                                    ��" << " PRESS D - TO MOVE RIGHT    ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ������������������������������������������������������������������������������������������������������" << endl;
}

// Function for game instructions.
void GameInstructions() {

	SetConsoleTextAttribute(console, 7);
	system("cls");
	cout << endl;
	cout << "   ������������������������������������������������������������������������������������������������������" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "      SELECT OPTIONS        ��" << endl;
	cout << "   ��                                                                    ��" << "    ------------------      ��" << endl;
	cout << "   ��                                                          " << char(254) << "         ��                            ��" << endl;
	cout << "   ��                                                                    ��" << "  PRESS ANY KEY             ��" << endl;
	cout << "   ��                                                          " << char(15) << "         ��  TO HEAD BACK              ��" << endl;
	cout << "   ��                          Game Instructions                         ��" << "                            ��" << endl;
	cout << "   ��                         -------------------                        ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                PRESS SPACEBAR TO MAKE YOUR SHIP SHOOT              ��" << "                            ��" << endl;
	cout << "   ��                PRESS A/LEFT TO MOVE LEFT                           ��" << "                            ��" << endl;
	cout << "   ��                PRESS D/RIGHT TO MOVE RIGHT                         ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                          " << char(202) << "         ��                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ��                                                                    ��" << "                            ��" << endl;
	cout << "   ������������������������������������������������������������������������������������������������������" << endl;
	_getch();
}

// Function for displaying game over.
void GameOver() {

	SetConsoleTextAttribute(console, 4);
	system("cls");
	cout << endl;
	cout << "   ������������������������������������������������������������������������������������������������������" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                   _____________   _____________   ______________  _____________                  ��" << endl;
	cout << "   ��                  |  ___________| |  _________  | |  ___    ___  | |  __________|                 ��" << endl;
	cout << "   ��                  | |             | |         | | | |   |  |   | | | |                            ��" << endl;
	cout << "   ��                  | |       ____  | |_________| | | |   |  |   | | | |__________                  ��" << endl;
	cout << "   ��                  | |      |__  | |  _________  | | |   |  |   | | |  __________|                 ��" << endl;
	cout << "   ��                  | |         | | | |         | | | |   |  |   | | | |                            ��" << endl;
	cout << "   ��                  | |_________| | | |         | | | |   |  |   | | | |__________                  ��" << endl;
	cout << "   ��                  |_____________| |_|         |_| |_|   |__|   |_| |____________|                 ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                   _____________   _           _  ______________  ______________                  ��" << endl;
	cout << "   ��                  |  _________  | | |         | | |  ___________| | ___________ |                 ��" << endl;
	cout << "   ��                  | |         | |  | |       | |  |  |            | |         | |                 ��" << endl;
	cout << "   ��                  | |         | |   | |     | |   |  |__________  | |_________| |                 ��" << endl;
	cout << "   ��                  | |         | |    | |   | |    |   __________| |  _______   |                  ��" << endl;
	cout << "   ��                  | |         | |     | |_| |     |  |            | |       | |                   ��" << endl;
	cout << "   ��                  | |_________| |      |   |      |  |__________  | |        | |                  ��" << endl;
	cout << "   ��                  |_____________|       |_|       |_____________| |_|         |_|                 ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                                     Press any key to continue!!                                  ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ������������������������������������������������������������������������������������������������������" << endl;
	Sleep(2000);
	GameReset();
	_getch();
}

// Function that displays win 
void GameWin() {

	SetConsoleTextAttribute(console, 2);
	system("cls");
	cout << endl;
	cout << "   ������������������������������������������������������������������������������������������������������" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                                  _      _    __________   _       _                              ��" << endl;
	cout << "   ��                                 | |     | | |  ______  | | |     | |                             ��" << endl;
	cout << "   ��                                  | |   | |  |  |    |  | | |     | |                             ��" << endl;
	cout << "   ��                                   | | | |   |  |    |  | | |     | |                             ��" << endl;
	cout << "   ��                                    |   |    |  |    |  | | |     | |                             ��" << endl;
	cout << "   ��                                     | |     |  |    |  | | |     | |                             ��" << endl;
	cout << "   ��                                     | |     |  |____|  | | |_____| |                             ��" << endl;
	cout << "   ��                                     |_|     |__________| |_________|                             ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                                   _       _   _________   ___       _                            ��" << endl;
	cout << "   ��                                  | |  _  | | |  _____  | |   |     | |                           ��" << endl;
	cout << "   ��                                  | | | | | | | |     | | | | |     | |                           ��" << endl;
	cout << "   ��                                  | | | | | | | |     | | | | | |   | |                           ��" << endl;
	cout << "   ��                                  | | | | | | | |     | | | |  | |  | |                           ��" << endl;
	cout << "   ��                                  | | | | | | | |     | | | |   | | | |                           ��" << endl;
	cout << "   ��                                  | |_| |_| | | |_____| | | |    | |  |                           ��" << endl;
	cout << "   ��                                  |_________| |_________| | |     |___|                           ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                                     Press any key to continue!!                                  ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ��                                                                                                  ��" << endl;
	cout << "   ������������������������������������������������������������������������������������������������������" << endl;
	Sleep(1000);
	GameReset();
	_getch();
}

// Function to reset Game
void GameReset()
{
	score = 0;
	life = 3;
	level = 1;
}

//-------------------------------------------- Huzan (out) --------------------------------------------------------------------------


//-------------------------------------------- Ahmad (in) --------------------------------------------------------------------------

/*
Here SetCursorPosition is a user-defined function that can move the cursor to a different location on the screen

Purpose :

--> Positions cursor in text window .
--> Moves Cursor to Position Specified i.e at (x,y)
--> If the coordinates are invalid, the call to SetCursorPosition is simply ignored by Compiler
--> The origin is located at (1,1) the upper-left corner of the window
--> Maximum x Co-ordinate in Text Mode = 80.
--> Maximum y Co-ordinate in Text Mode = 25.
*/

void SetCursorPosition(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

/*
The typedef in C++ is a keyword used to assign alternative names to the existing datatypes.
DWORD is a typedef for 'double word' sized integers.
It's a way of sizing them, rather than giving bit numbers.
In general:
16 bit = WORD
32 bit = DWORD

*/
void Cursor(bool visible, DWORD size) {

	// CONSOLE_CURSOR_INFO gives information about the cursor
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.bVisible = visible;
	CursorInfo.dwSize = size;
	SetConsoleCursorInfo(console, &CursorInfo);
}

// Function to display score.
void GameScore()
{
	SetCursorPosition(Width + 21, 7);
	cout << score << endl;
}

// Function to update life
void UpdateLife()
{
	SetCursorPosition(Width + 20, 11);
	cout << life << endl;
}

// Function to update level
void UpdateLevel()
{
	SetCursorPosition(Width + 21, 15);
	cout << level << endl;
}

// Function that involves collision of the ship with enemy
int CollisionWithEnemy() {
	if (EnemyVertical[0] >= 24) {
		if (EnemyHorizontal[0] - ShipPosition >= 0 && EnemyHorizontal[0] - ShipPosition < 8) {
			life--;
			UpdateLife();
			if (life == 0)
				return 1;
		}

	}
	return 0;
}

// Function to display spaceship
void SpawnShip()
{
	SetConsoleTextAttribute(console, 14);
	SetCursorPosition(ShipPosition, 24);
	cout << SpaceShip;
}

// Function to remove spaceship
void RemoveShip() {
	SetCursorPosition(ShipPosition, 24);
	cout << " ";
}

//-------------------------------------------- Ahmad (out) --------------------------------------------------------------------------


//-------------------------------------------- Haris (in) --------------------------------------------------------------------------


// Function to generate first enemy at random coordinates
void GenerateEnemy1(int ind) {
	EnemyHorizontal[ind] = rand() % 60 + 7;
}

// Function to generate second enemy at random coordinates
void GenerateEnemy2(int ind) {
	EnemyHorizontal[ind] = rand() % 60 + 8;
}

// Function that displays emnemies
void SpawnEnemies(int ind) {
	SetConsoleTextAttribute(console, 4);
	if (EnemyFlag[ind] == true) {
		SetCursorPosition(EnemyHorizontal[ind], EnemyVertical[ind]);
		cout << Enemy;
	}
}

// Funtion to remove enemies
void RemoveEnemies(int ind) {
	if (EnemyFlag[ind] == true) {
		SetCursorPosition(EnemyHorizontal[ind], EnemyVertical[ind]);
		cout << " ";
	}
}

// Function to reset enemies
void ResetEnemies(int ind) {
	RemoveEnemies(ind);
	EnemyVertical[ind] = 7;
	GenerateEnemy2(ind);
	GenerateEnemy1(ind);
}

// Function to generate bulltes fired from the spaceship
void GenerateBullets() {
	Bullets[BulletsIndex][0] = 23; // firing y position
	Bullets[BulletsIndex][1] = ShipPosition; // firing x position
	BulletsIndex++;
	// The below if statement reset bullets value wheen all 10 are fired
	if (BulletsIndex == 10)
		BulletsIndex = 0;
}

// Function to navigate bullets
void NavigateBullets() {
	for (int i = 0; i < 10; i++) {
		if (Bullets[i][0] > 2)
			Bullets[i][0]--; // to give a borderline to the bullets
		else
			Bullets[i][0] = 0; // to let bullet remove, once it reaches the top
	}
}

// Function to display bullets
void SpawnBullets() {
	SetConsoleTextAttribute(console, 7);
	for (int i = 0; i < 20; i++) {
		if (Bullets[i][0] > 1) {
			SetCursorPosition(Bullets[i][1], Bullets[i][0]);
			cout << char(15);
		}
	}
}

// Function to remove bullets
void RemoveBullets() {
	for (int i = 0; i < 10; i++) {
		if (Bullets[i][0] >= 1) {
			SetCursorPosition(Bullets[i][1], Bullets[i][0]);
			cout << " ";
		}
	}
}

// Function to remove bullets after they hit the enemies
void RemoveBulletsAfterHit(int i) {
	SetCursorPosition(Bullets[i][1], Bullets[i][0]);
	cout << " ";
}

//-------------------------------------------- Haris (out) --------------------------------------------------------------------------

//-------------------------------------------- Wasiq (in) --------------------------------------------------------------------------

// Function that deletes enemies when hit with the bullets fired via spaceship
int HitEnemy() {

	for (int i = 0; i < 10; i++) // bullets navigating loop - row
	{
		for (int j = 0; j < 2; j += 2) // bullets navigating loop - coloumn
		{
			if (Bullets[i][j] != 0)
			{
				if (Bullets[i][j] >= EnemyVertical[0] && Bullets[i][j] <= EnemyVertical[0] + 1)  // vertical position hit
				{
					if (Bullets[i][j + 1] >= EnemyHorizontal[0] && Bullets[i][j + 1] <= EnemyHorizontal[0] + 1) // horizontal position hit
					{
						RemoveBulletsAfterHit(i);
						Bullets[i][j] = 0;
						ResetEnemies(0);
						return 1;

					}
				}
				if (Bullets[i][j] >= EnemyVertical[1] && Bullets[i][j] <= EnemyVertical[1] + 1) {
					if (Bullets[i][j + 1] >= EnemyHorizontal[1] && Bullets[i][j + 1] <= EnemyHorizontal[1] + 1) {
						RemoveBulletsAfterHit(i);
						Bullets[i][j] = 0;
						ResetEnemies(1);
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

// Function to play the game
void play() {

	EnemyFlag[0] = 1;
	EnemyFlag[1] = 1;
	ShipPosition = -1 + Width / 2;
	EnemyVertical[0] = EnemyVertical[1] = 4; // enemy starting point

	for (int i = 0; i < 20; i++) {
		Bullets[i][0] = Bullets[i][1] = 0; // bullets reset
	}

	system("cls");
	GameWindow();
	GenerateEnemy1(0);
	GenerateEnemy2(1);
	GameScore();
	UpdateLife();
	UpdateLevel();

	SetCursorPosition(27, 8); 
	cout << "PRESS ANY KEY TO START";
	_getch();
	SetCursorPosition(27, 8); 
	cout << "                      ";

	while (1) {
		if (_kbhit()) {
			char key = _getch();
			// 68 is Arrow Left
			if (key == 'a' || key == 'A') {
				if (ShipPosition > 6) // left border limit
					ShipPosition -= 1;
			}
			//67 is Arrow Right
			if (key == 'd' || key == 'D') {
				if (ShipPosition < Width) // right border limit
					ShipPosition += 1;
			}
			// 32 is space character
			if (key == 32) {
				Beep(7, 10);
				GenerateBullets();
			}
			// 27 is escape character
			if (key == 27) {
				break;
			}
		}

		SpawnShip();
		SpawnEnemies(0);
		SpawnEnemies(1);
		SpawnBullets();

		if (CollisionWithEnemy() == 1) {
			GameOver();
			ofstream out;
			out.open("score.txt");
			out << score;
			out.close();
			return;
		} 
		if (HitEnemy() ==1) {
			score++;
			GameScore();
			if (score == level * 10)
			{
				level++;
				UpdateLevel();
			}
			if (level == 6)
			{
				GameWin();
				return;
			}

		}
		Sleep(200); // game speed
		RemoveShip();
		RemoveEnemies(0);
		RemoveEnemies(1);
		RemoveBullets();
		NavigateBullets();

		if (EnemyFlag[0] == 1)
			EnemyVertical[0] += 1;

		if (EnemyFlag[1] == 1)
			EnemyVertical[1] += 1;

		if (EnemyVertical[0] > Height - 2) {
			ResetEnemies(0); // enemy 
		}
		if (EnemyVertical[1] > Height - 2) {
			ResetEnemies(1);
		}
	}
}

//-------------------------------------------- Wasiq (out) --------------------------------------------------------------------------