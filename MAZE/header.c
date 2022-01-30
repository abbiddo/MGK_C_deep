#include "header.h"

void LoadMaze(char num) {
	char path[20] = "./maze/Maze";
	char str_tmp[50] = { 0, };
	char* ptr;
	int i, j;

	if (num == '1') strcat(path, "1");
	else if (num == '2') strcat(path, "2");
	else strcat(path, "3");

	strcat(path, ".txt");
	FILE* f = fopen(path, "r");

	for (i = 0; i < SIZE; i++) {
		fgets(str_tmp, 50, f);
		ptr = strtok(str_tmp, "\t");

		for (j = 0; j < SIZE; j++) {
			maze[i][j] = *ptr;
			ptr = strtok(NULL, "\t");

		}
	}
	fclose(f);
}

void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void PrintMazeGame() {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		GotoXY(XP, YP + i);
		for (j = 0; j < SIZE; j++) {
			if (maze[i][j] == '1') printf("■");
			else if (maze[i][j] == 'y') printf("★");
			else if (maze[i][j] == '0') printf("□");
			else printf("●");
		}
		printf("\n");
	}
}

void CursorView(char show) {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

int MoveMaze(int *row, int *col) {
	int nkey,a=1;

	if (_kbhit()) {
		nkey = _getch();
		if (nkey == ARROW) {
			nkey = _getch();
			switch (nkey) {
			case UP:
				if (!(IsBlock(*row - 1, *col))) {
					maze[*row][*col] = '0';
					maze[*row - 1][*col] = '*';
					*row -= 1;
				}
				else if (IsFinish(*row - 1, *col)) a=Complete();
				break;
			case DOWN:
				if (!(IsBlock(*row + 1, *col))) {
					maze[*row][*col] = '0';
					maze[*row + 1][*col] = '*';
					*row += 1;
				}
				else if (IsFinish(*row + 1, *col)) a=Complete();
				break;
			case LEFT:
				if (!(IsBlock(*row, *col-1))) {
					maze[*row][*col] = '0';
					maze[*row][*col-1] = '*';
					*col -= 1;
				}
				else if (IsFinish(*row, *col-1)) a=Complete();
				break;
			case RIGHT:
				if (!(IsBlock(*row, *col + 1))) {
					maze[*row][*col] = '0';
					maze[*row][*col+1] = '*';
					*col += 1;
				}
				else if (IsFinish(*row, *col + 1)) a=Complete();
				break;
			}
			if (a == 10) return 10;
		}
	}
}

int IsBlock(int i, int j) {
	if (maze[i][j] == '1' || maze[i][j] == 'y') return 1;
	else return 0;
}

int IsFinish(int i, int j) {
	if (maze[i][j] == 'y') return 1;
	else return 0;
}

int Complete() {
	end = clock();
	res = (float)(end - start) / CLOCKS_PER_SEC;

	GotoXY(XP, YP + SIZE);
	printf("Complete!\n");
	GotoXY(XP, YP + SIZE + 1);
	printf("경과시간 : %.2f초\n", res);
	return 10;
}