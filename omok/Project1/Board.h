#pragma once

#define MAP_W 1200
#define MAP_H 1200
#define WHITE_Player 1
#define BLACK_Player -1


//������ ������  100 , 100
//������ ����   1000 ,1000

// 0: �ٵϵ� ����
// 1: ��
//-1: ��

class Board {
private:
	int board[20][20] = { 0 };
	int offense = WHITE_Player;
public:
	//�ٵϵ��� �Ѽ� �ִ��� üũ
	void putOn(int mx, int my) {
		int x = mx / 50 - 1;	int y = my / 50 - 1;

		if (board[x][y] == 0) {
			board[x][y] = offense;
			offense *= -1; //�÷��̾� ��ȯ
		}
	}
	int getOffense() { return offense; }
	int(*ReturnArray())[20] { return board; }	//2���� �迭 ��ȯ
};