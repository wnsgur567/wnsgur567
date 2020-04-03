#pragma once

#define MAP_W 1200
#define MAP_H 1200
#define WHITE_Player 1
#define BLACK_Player -1


//보드판 시작점  100 , 100
//보드판 끝점   1000 ,1000

// 0: 바둑돌 없음
// 1: 백
//-1: 흑

class Board {
private:
	int board[20][20] = { 0 };
	int offense = WHITE_Player;
public:
	//바둑돌을 둘수 있는지 체크
	void putOn(int mx, int my) {
		int x = mx / 50 - 1;	int y = my / 50 - 1;

		if (board[x][y] == 0) {
			board[x][y] = offense;
			offense *= -1; //플레이어 전환
		}
	}
	int getOffense() { return offense; }
	int(*ReturnArray())[20] { return board; }	//2차원 배열 반환
};