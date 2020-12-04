#include "GameManager.h"
#include "P2015112167.h"
//솔루션 작업 검토
int main()
{
	// 게임 선언
	GameManager game;

	// 게임 시작
	game.run(new P2015112167());
	int temp;
	std::cin >> temp;

	return 0;
}
