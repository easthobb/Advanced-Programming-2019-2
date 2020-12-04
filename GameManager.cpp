#include "GameManager.h"

// 게임 초기화
void GameManager::init()
{
	// 초기화.
	gameBoard.init();

	// 처음은 2개의 블록
	gameBoard.putRandomBlock();
	gameBoard.putRandomBlock();
}

// player 가 실제 게임 플레이 진행
// -> 플레이어가 이동할 액션을 선택, 그에 따른 반응을 호출.
// -> 최대 점수를 얻으면 게임 클리어
void GameManager::run(Player * player)
{
	// 초기화.
	init();

	// 게임 시작.
	// 게임 판 정보를 복사하여 플레이어에게 보내준다.
	int board[BOARD_SIZE][BOARD_SIZE];
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			board[x][y] = gameBoard.getBoardXY(x, y);
		}
	}
	player->gameStart(board);

	// 10000번 턴을 준다.
	// 10000번 내에 끝나지 않으면 강제 종료.
	int limitTurn = MAX_TURN;
	while (limitTurn--)
	{
		// 게임 판을 화면에 출력
		if (DEBUG)
		{
			std::cout << gameBoard << std::endl;
		}


		// 다음에 이동할 좌표
		Action nextAction = player->nextMove();

		// 게임 판 정보를 복사한다.
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			for (int y = 0; y < BOARD_SIZE; y++)
			{
				board[x][y] = gameBoard.getBoardXY(x, y);
			}
		}

		// 더 이상 움직일 것이 없으면 게임 종료.
		if (gameBoard.isGameOver())
		{
			break;
		}

		// 이동 시도 및 성공
		if (gameBoard.move(nextAction))
		{
			// 랜덤으로 블록 하나 생성.
			if (gameBoard.putRandomBlock())
			{
				// 게임 판 정보를 복사한다.
				for (int x = 0; x < BOARD_SIZE; x++)
				{
					for (int y = 0; y < BOARD_SIZE; y++)
					{
						board[x][y] = gameBoard.getBoardXY(x, y);
					}
				}
				
				player->ableToMove(nextAction, board);
			}
			// 블록 생성 불가능 하면 게임 종료.
			else
			{
				break;
			}
		}
		// 이동 시도 실패
		else
		{
			player->notAbleToMove(nextAction, board);
		}
	}

	// 게임 판을 화면에 출력	
	std::cout << gameBoard << std::endl;

	// 지정된 턴 이전에 끝나면 게임 클리어 및 점수 출력
	if (limitTurn >= 0)
	{
		std::cout << MAX_TURN - limitTurn << "회 만에 게임 종료. >,<\n점수는 " << gameBoard.getTotalScore() << std::endl;
	}
	// 게임 종료 및 점수 출력.
	else
	{
		std::cout << MAX_TURN << "회 안에 게임 종료가 안 되어 강제 종료합니다. T^T\n점수는" << gameBoard.getTotalScore() << std::endl;
	}


	delete player;
}
