#include "Board.h"

Board::Board()
{
	// 랜덤 시드 설정.
	srand((int)board);
}

void Board::init()
{
	// 초기화
	score = 0;

	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			board[x][y] = 0;
		}
	}
}

// 랜덤 블럭 생성. 실패 시 false 리턴
bool Board::putRandomBlock()
{
	std::vector<Point> emptyCells = getEmptyCells();

	// 꽉 차 있으면 더 이상 불가능.
	if (emptyCells.size() == 0)
	{
		return false;
	}

	// 빈 칸 중에서 랜덤으로 블럭 삽입.
	int insertIndex = rand() % emptyCells.size(); //2 or 4

	// 4 블럭은 약 10퍼센트의 확률.
	// https://www.linkedin.com/pulse/20140613201532-7790303-probability-of-4-in-a-new-tile-in-2048
	int insertBlock = rand() % 10 < 9 ? 2 : 4; // 2 or 4 

	board[emptyCells[insertIndex].getX()][emptyCells[insertIndex].getY()] = insertBlock;

	return true;
}

// 이동. (상 하 좌 우). 실패 시 false 리턴
bool Board::move(Action action)
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
		results[i] = shift(cellsToMove);

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

bool Board::isGameOver()
{
	// 원래 게임 판, 점수 복사
	int originalScore = score;
	int originalBoard[BOARD_SIZE][BOARD_SIZE];
	memcpy(originalBoard, board, sizeof(board));

	// 네 군데 이동 시도
	for (int i = 0; i < 4; i++)
	{
		// 이동 가능 -> 게임 오버 아님
		if (move((Action)i))
		{
			// 원래 게임 판, 점수로 복구
			score = originalScore;
			memcpy(board, originalBoard, sizeof(board));
			return false;
		}

		// 원래 게임 판, 점수로 복구
		score = originalScore;
		memcpy(board, originalBoard, sizeof(board));
	}

	// 아무 것도 이동할 수 없으면 게임 오버.
	return true;
}

int Board::getTotalScore()
{
	return score;
}

// 대입연산자
Board & Board::operator=(const Board & b)
{
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			this->board[x][y] = b.board[x][y];
		}
	}
	return *this;
}

// getter
int Board::getBoardXY(int x, int y)
{
	return board[x][y];
}

// 비어있는 칸을 리턴.
std::vector<Point> Board::getEmptyCells()
{
	std::vector<Point> emptyCells;

	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (board[x][y] == 0)
			{
				emptyCells.push_back(Point(x, y));
			}
		}
	}

	return emptyCells;
}

// 실제 shift하는 함수.
std::vector<int> Board::shift(std::vector<int> cells)
{
	std::vector<int> result;

	for (int i = 0; i < cells.size(); i++)
	{
		// 같으면 블럭을 합침.
		if (i < cells.size() - 1 && cells[i] == cells[i + 1] && cells[i] != 0)
		{
			cells[i] *= 2;
			score += cells[i];

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

// 출력
std::ostream & operator<<(std::ostream & os, const Board & b)
{
	
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			os << std::setw(8) << std::left << b.board[x][y];
		}
		os << '\n';
	}
	os << std::endl;

	return os;
}
