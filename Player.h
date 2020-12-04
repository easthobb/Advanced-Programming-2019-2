#pragma once
#include "Action.h"
#include "Constants.h"
#include "Point.h"

class Player
{
public:

	Player() {}

	// 게임 처음 시작 시 호출됩니다.
	// 현재 게임 판의 상태가 2차원 배열로 주어집니다.
	virtual void gameStart(int board[BOARD_SIZE][BOARD_SIZE]) = 0;

	// 다음에 "움직일 방향"을 반환하세요. 
	// 해당 방향으로 이동 시도 후 아래 ableToMove, notAbleToMove 함수 중 하나가 호출됩니다.
	//
	// Action enum안에는 { MOVE_UP, MOVE_LEFT, MOVE_RIGHT, MOVE_DOWN } 가 들어 있습니다.
	// ex) return Action::MOVE_LEFT; // 왼쪽으로 이동
	virtual Action nextMove() = 0;

	// 블럭들이 움직였다면 이 함수가 호출됩니다.
	// prevAction: 움직임을 시도한 방향
	// board: 현재 게임 판의 상태. 랜덤으로 한 블록이 생성된 상태입니다.
	virtual void ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]) = 0;

	// 블럭들이 움직이지 못했다면 이 함수가 호출됩니다.
	// prevAction: 움직임을 시도한 방향
	// board: 현재 게임 판의 상태. 새로운 블록은 생성되지 않습니다.
	virtual void notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]) = 0;
};