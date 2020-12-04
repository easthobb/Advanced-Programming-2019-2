#pragma once
#include "Board.h"
#include "Player.h"

class GameManager
{
public:
	// 게임 초기화
	void init();
	// player 가 실제 게임 플레이 진행
	// -> 플레이어가 이동할 액션을 선택, 그에 따른 반응을 호출.
	// -> 더 이상 움직일 수 없으면 최대 점수를 출력하고 종료.	
	void run(Player* player);

private:
	Board gameBoard;
};