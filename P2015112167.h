#pragma once
#include "Player.h"
#include "Board.h"
#include <map>

class P2015112167 : public Player
{
	int nextDirection; // player ������ �������� �̵��� ������ �����ϴ� ����(0,1,2,3)�� ���� ����.

public:
	void gameStart(int board[BOARD_SIZE][BOARD_SIZE]);
	Action nextMove();
	void ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]);
	void notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]);

	/*���� �Լ�*/
	bool moving(Action action, int board[BOARD_SIZE][BOARD_SIZE]); // �� Ŭ���� �ܰ迡�� board�� ������ Simualtion �ϱ� ���� ����ϴ� �Լ�
	std::vector<int> shifting(std::vector<int> cells);// �� Ŭ���� �ܰ迡�� board�� ������ Simualtion �ϱ� ���� ����ϴ� �Լ�
	int countEntrophy(int board[BOARD_SIZE][BOARD_SIZE]); //board�� ���·� entrophy ���� ���ϱ� ���� ����� ���� �޼ҵ�
	Action bestChoice(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]); // entrophy ���� ����� ���� node���� �Ǵܰ����� �ּ��� value ���
	

	/*�������� ���� �Լ� : ���� �бⰡ ���� �� ���������� ������ �� �����Դϴ�.*/
	std::map<int,int> deepChoice(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]);

private:
	char* Action_Debug[4] = { "MOVE_UP, ���� �̵�", "MOVE_LEFT, �������� �̵�" , "MOVE_RIGHT, ���������� �̵�" , "MOVE_DOWN, �Ʒ��� �̵�" };
};