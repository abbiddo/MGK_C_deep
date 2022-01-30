#include "header.h"

int main() {
	char level;
	int i, j, nkey, row=2, col=1,k;

	CursorView(0);

	GotoXY(XP, YP - 3);
	printf("미로 찾기 게임\n");
	GotoXY(XP, YP - 2);
	printf("난이도를 선택하세요. (1,2,3) ");
	scanf("%c", &level);

	LoadMaze(level);

	start = clock();

	while (1) {
		PrintMazeGame();
		k=MoveMaze(&row,&col);
		if (k == 10) break;
	}
	system("pause");
}