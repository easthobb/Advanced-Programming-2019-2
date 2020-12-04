#pragma once
#include "Player.h"
#include "Board.h"
#include <map>

class P2015112167 : public Player
{
	int nextDirection; // player 내에서 다음으로 이동할 방향을 지정하는 변수(0,1,2,3)의 값을 가짐.

public:
	void gameStart(int board[BOARD_SIZE][BOARD_SIZE]);
	Action nextMove();
	void ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]);
	void notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]);

	/*구현 함수*/
	bool moving(Action action, int board[BOARD_SIZE][BOARD_SIZE]); // 이 클래스 단계에서 board의 정보로 Simualtion 하기 위해 사용하는 함수
	std::vector<int> shifting(std::vector<int> cells);// 이 클래스 단계에서 board의 정보로 Simualtion 하기 위해 사용하는 함수
	int countEntrophy(int board[BOARD_SIZE][BOARD_SIZE]); //board의 상태로 entrophy 값을 평가하기 위한 사용자 정의 메소드
	Action bestChoice(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]); // entrophy 값을 사용해 현재 node에서 판단가능한 최선의 value 출력
	

	/*구현하지 않은 함수 : 추후 학기가 끝난 후 개인적으로 구현해 볼 예정입니다.*/
	std::map<int,int> deepChoice(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]);

private:
	char* Action_Debug[4] = { "MOVE_UP, 위로 이동", "MOVE_LEFT, 왼쪽으로 이동" , "MOVE_RIGHT, 오른쪽으로 이동" , "MOVE_DOWN, 아래로 이동" };
};