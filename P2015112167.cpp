#include "P2015112167.h"

void P2015112167::gameStart(int board[BOARD_SIZE][BOARD_SIZE])
{
	// 시작
	std::cout << "시작" << std::endl;
}

/*ableToMove, notAbleToMove를 통해 만들어진 nextDirection의 값을 반환 0:위 1:왼 2:오 3:아래 */
Action P2015112167::nextMove()
{
	return (Action) (this->nextDirection); //Action type으로 형변환
}

/*입력받은 Action이 Movable할 경우 실행되는 함수 : 여기서는 자체적으로 정의한 bestchoice의 결과를 nextDirection에 저장합니다.*/
void P2015112167::ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	this->nextDirection = bestChoice(prevAction, board); // bestChoice 함수 호출 board와 이전의 움직임의 정보를 입력함.
	std::cout << Action_Debug[prevAction] << "성공" << std::endl;
}

/*입력받은 Action이 Not Movable할 경우 실행되는 함수 : 여기서는 자체적으로 정의한 bestchoice의 결과를 nextDirection에 저장합니다. 하지만 bestChoice의 결과가 유효하지 않다면 random 움직임.*/
void P2015112167::notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	this->nextDirection = bestChoice(prevAction, board);
	if (prevAction == this->nextDirection) //prevAction과 bestchoice의 결과가 같을경우(움직이지 못하는 경우) 
		this->nextDirection = rand() % 4; //랜덤한 값으로 움직임 실행.

	std::cout << Action_Debug[prevAction] << "실패" << std::endl;
}

/*Player class에서 입력받은 board 정보에 대해 Simulation하기 위해 사용하는 함수. Board class의 함수를 상속받지 않고 구현 / class Board::move()*/
bool P2015112167::moving(Action action, int board[BOARD_SIZE][BOARD_SIZE])
{
	bool isAbleToMove = false;
	// 탐색할 방향
	const int dir[][2] = { 1, 0, 0, 1, 0, -1, -1, 0 };
	int dx = dir[action][0], dy = dir[action][1];

	std::vector<int> results[BOARD_SIZE];

	// 게임 판을 움직인다...2048 게임 참고.
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::vector<int> cellsToMove, originalCells;

		int x = dx < 0 ? BOARD_SIZE - 1 : i * abs(dy), y = dy < 0 ? BOARD_SIZE - 1 : i * abs(dx);
		int zeroCount = 0;

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int nx = (x + dx * j + BOARD_SIZE) % BOARD_SIZE;
			int ny = (y + dy * j + BOARD_SIZE) % BOARD_SIZE;

			// 앞에 있는 0은 제거.
			if (board[nx][ny] == 0)
			{
				zeroCount++;
			}
			else
			{
				cellsToMove.push_back(board[nx][ny]);
			}

			originalCells.push_back(board[nx][ny]);
		}

		for (int z = 0; z < zeroCount; z++)
		{
			cellsToMove.push_back(0);
		}

		// 이동.
		results[i] = shifting(cellsToMove);

		// 움직이기 가능, 원래 게임 판과 달라짐.
		if (originalCells != results[i])
		{
			isAbleToMove = true;
		}
	}

	// 이동 불가능하면 false.
	if (isAbleToMove == false)
	{
		return false;
	}

	// 실제 이동
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		int x = dx < 0 ? BOARD_SIZE - 1 : i * abs(dy), y = dy < 0 ? BOARD_SIZE - 1 : i * abs(dx);

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int nx = (x + dx * j + BOARD_SIZE) % BOARD_SIZE;
			int ny = (y + dy * j + BOARD_SIZE) % BOARD_SIZE;

			board[nx][ny] = results[i][j];
		}
	}

	return isAbleToMove;
}

/*Player class에서 입력받은 board 정보에 대해 Simulation하기 위해 사용하는 함수. Board class의 함수를 상속받지 않고 구현 /class Board::shift()*/
std::vector<int> P2015112167::shifting(std::vector<int> cells)
{
	std::vector<int> result;

	for (int i = 0; i < cells.size(); i++)
	{
		// 같으면 블럭을 합침.
		if (i < cells.size() - 1 && cells[i] == cells[i + 1] && cells[i] != 0)
		{
			cells[i] *= 2;
			//score += cells[i]; score을 simulation 단계에선 카운트할 필요 없음.

			result.push_back(cells[i]);
			cells.push_back(0);
			i++;
		}
		else
		{
			result.push_back(cells[i]);
		}
	}

	return result;
}

/* 구현함수 : 입력받은 Board의 entrophy 값을 평가하는 함수입니다.*/
// 의도 : board의 상태에 따라 어떤 방향으로 타일을 이동시키는 것이 좋은지를 평가하는 모델이 필요하다고 생각했다.
//		 무작위성을 고려하면 당연히 좋겠지만, 무작위성을 배제하고 현재의 board 상태의 객관적인 상태를 평가하기 위해 entrophy 개념을 차용했다.
//		 board에서 0이 더 많고 유효 타일의 갯수가 적을수록 ordered 하다.(물론 all 0는 예외이다)
int P2015112167::countEntrophy(int board[BOARD_SIZE][BOARD_SIZE]) { // 이 모델은 일시적으로 이렇게 간단하게 작성했지만 추후 수정가능

	int entrophy = 10000; // default entrophy - 0으로 채워진 board: 9983
	int countBlankCell = 0; // board의 0을 세는 변수
	int sumValue = 0; // board의 value를 세는 변수 

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 0)
				countBlankCell++; // 입력받은 board의 원소가 0이라면 0을 세는 변수++; 
			else
				sumValue += board[i][j];
		}
	}
	/*실험적인 DATA에 따라서 실험자가 바꾸어도 되는 value  */ 
	//sumvalue는 크게 유효하지는 않다. : 어차피 같은 시점에서 모든 경로가 같은 value를 사용하기 때문 하지만 다른 시점의 entrophy와 비교하기 위해서 필요(추후구현)
	entrophy = entrophy - ((countBlankCell + 1) * (sumValue + 1)); // 10000으로 count 되는걸 방지하기 위해서 upper bound lower bound set
	return entrophy;

}

/* 구현함수 : 입력받은 Board의 entrophy 값을 통해 현재의 board에서 어떠한 방향으로 이동하는 것이 더 낮은 entrophy를 만들 수 있는지 판단하는 함수입니다.*/
// 의도 : 현재의 상태와 action을 통해 board를 이동할 수 있는 상태가 있는데 위에서 정의한 entrophy 를 통해서 더 낮은 entrophy를 가진 상태가 더 적합하다고 판단하면
//       이동하기 위해서 이 함수를 구현하였다. 하지만 충분히 성능이 좋지 않았다. deep하게 거리가 1 떨어진 Node 뿐만 아니라 더 깊이 탐색을 해야하는데 어려움이 있어
//       1 layer 탐색만 구현했기 때문이다. 하지만 이를 보완하기 위해 ADVANCED -A, B 를 도입해 경험칙으로 얻어진 general하고 unspecific한 rule들을 entrophy
//		 계산에 가감해줌으로써 Algorithm에 경향성을 더해주었다. 따라서 구현한 algorithm은 같은 entrophy를 가졌고 오른쪽, 왼쪽 모두 이동할 수 있는 상황이면
//       오른쪽으로 이동하는 방식으로 경향성을 보유했다. 또한 가장 큰 값을 Corner에 모는 선택을 한다.
Action P2015112167::bestChoice(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	int currentEnt = countEntrophy(board); // 입력받은 board의 entrophy 입력 
	int entArray[4] = { 10000 }; // entrophy array, 10000으로 초기화합니다.
	int tempBoard[BOARD_SIZE][BOARD_SIZE]; // board에서 이동할 수 있는 4가지 방향을 평가하기 위해서 필요한 임시변수 tempBoard
	int topIndex; // 최상위 값을 indexing하는 변수
	int temp = 10000; // 임시변수
	int elementValue = 0; //board의 개별 원소를 지정하는 임시변수

	for (int k = 0; k < 4; k++) // 위 왼 아래 오른 4방향에 대해서 entrophy value calculating 수행하는 for 문
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				tempBoard[i][j] = board[i][j];  // 임시변수에 입력받은 board 정보 할당.
			}
		}

		if (moving((Action)k, tempBoard)) //tempBoard를 k 방향으로 움직일 수 있는 경우에만 수행.
		{
			entArray[k] = countEntrophy(tempBoard);

			/*ADVANCED-A weight : 아래 방향 이동과 오른쪽 방향 이동이 가능하다면 추가적인 weight를 부여합니다.*/
			if (k == 2 || k == 3)
			{
				entArray[k] -= 500; // 경험적으로 corner로 타일들을 몰아 넣는 것이 더 높은 점수를 얻을 수 있다고 판단하여 가중치를 부여했습니다.
			}
			/*ADVANCED-B weight : 맨 오른쪽 아래 corner에 가장 큰 값이 저장된다면 추가적인 weight를 부여합니다.*/
			for (int x = 0; x < 4; x++) {
				for (int y = 0; y < 4; y++)
				{
					if (elementValue <= tempBoard[x][y])
						elementValue = tempBoard[x][y]; // element 중에 가장 큰 값 indexing
				}
			}
			if (elementValue == tempBoard[3][3])
				entArray[k] -= 100;// 경험적으로 맨 오른쪽 아래 corner에 가장 높은 값의 타일을 넣는 것이 더 높은 점수를 있다고 판단하여 가중치를 부여했습니다.
		}
		else { // k 방향으로 움직일 수 없다면 어떤 상태이든 최대의 무질서도 부여. 
			entArray[k] = 10000;
		}
	}

	for (int i = 0; i < 4; i++) //저장된 방향 중 가장 적은 값의 entrophy 값을 추출하기 위한 for문
	{
		if (temp >= entArray[i])
		{
			temp = entArray[i];
			topIndex = i;
		}
	}

	return (Action)topIndex; // 가장 작은 entrophy 값을 추출 return
	
}

/*구현 함수: 현재 미완성입니다. 이번 심프프로젝트에서는 사용하지 않습니다.*/
std::map<int,int> P2015112167::deepChoice(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	
	// recursive 한 방법으로 deep하게 search를 진행하는 Algorithm 구상을 했으나 시간 부족 
	// 시험 기간 끝난 이후 구현 목표. 더 이상 움직일 수 없거나, 어떻게 움직이던 entrophy가 같은 case일 경우 재귀 탈출
	// 바로 하위 Node의 entrophy가 아니라 최하위 Node 의 entrophy 들을 평가해 가장 낮은 방향으로 이동, 턴이 진행되면서 계속적으로 update 된다.
	std::map<int, int>nextPath;
	return nextPath;
}
 
/*
1. 랜덤 상황을 가정하지 않고 move와shift를 player 클래스에서 구현 후 시도 -> score를 얻어서 더 score 가 큰 방향 선택
2. 랜던 상황을 가정하지 않고 move shift 구현 후 개별 이동 방식의 entrophy 가 감소하는 방향으로 선택
3. 랜덤 상황 배제하고 불가능한 상황까지.
4. 엔트로피 모델 생성 어떠한 모양의 배치가 더 질서있는가? 이거에 대한 평가를 해야함.

엔트로피 평가모델 -> score와 빈 칸의 갯수로 만듦
*/