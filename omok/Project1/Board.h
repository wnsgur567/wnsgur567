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

//	\0	\100	\200	\300	\400	\\		\1900
//-------------------------------------------
//	\1
//	\2
//	\3
//	\4
//	\5
//	\6
//	\7
//	\8
//  \
//  \
//	\19

class Board {
private:
	int board[20][20] = { 0 };
	int offense = WHITE_Player;

	//�¸��� true   (6������ / ��Ȯ�� 5�� ��츸)
	bool isWin(int x, int y) {
		int sum = 1;
		//Hor
		int i = 1;
		while (true) {	//right			
			if (x + i < 20 && board[x + i][y] == offense) {
				sum++;	i++;
			}
			else break;
		}
		i = 1;
		while (true) {	//left			
			if (x - i > 0 && board[x - i][y] == offense) {
				sum++;	i++;
			}
			else break;
		}
		if (sum == 5) return true;


		sum = 1;
		//Ver
		i = 1;
		while (true) {	//down				
			if (y + i < 20 && board[x][y + i] == offense) {
				sum++;	i++;
			}
			else break;
		}
		i = 1;
		while (true) {	//up		
			if (y - i > 0 && board[x][y - i] == offense) {
				sum++;	i++;
			}
			else break;
		}
		if (sum == 5) return true;


		sum = 1;
		//�밢 1
		i = 1;
		while (true) {
			if (x + i < 20 && y + i < 20 && board[x + i][y + i] == offense) {
				sum++;	i++;
			}
			else break;
		}
		i = 1;
		while (true) {
			if (x - i > 0 && y - i > 0 && board[x - i][y - i] == offense) {
				sum++;	i++;
			}
			else break;
		}
		if (sum == 5) return true;

		sum = 1;
		//�밢 2
		i = 1;
		while (true) {
			if (x + i < 20 && y - i > 0 && board[x + i][y - i] == offense) {
				sum++;	i++;
			}
			else break;
		}
		i = 1;
		while (true) {
			if (x - i > 0 && y + i < 20 && board[x - i][y + i] == offense) {
				sum++;	i++;
			}
			else break;
		}
		if (sum == 5) return true;
		return false;
	}



	//3*3 check
	void check3By3(int x, int y) {

	}
	//4*4 check
	void check4By4(int x, int y) {

	}

public:
	Board() {

	}
	//�ٵϵ��� �Ѽ� �ִ��� üũ
	int putOn(int mx, int my) {
		int x = mx / 50 - 1;	int y = my / 50 - 1;

		if (board[x][y] == 0) {
			//TODO : is Win?
			if (isWin(x, y))	return offense;
			//TODO : 3by3,4by4 check

			board[x][y] = offense;
			offense *= -1; //�÷��̾� ��ȯ
		}
	}
	int getOffense() { return offense; }
	int(*ReturnArray())[20]{ return board; }	//2���� �迭 ��ȯ
};