#include "P2015112167.h"

void P2015112167::gameStart(int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	std::cout << "����" << std::endl;
}

/*ableToMove, notAbleToMove�� ���� ������� nextDirection�� ���� ��ȯ 0:�� 1:�� 2:�� 3:�Ʒ� */
Action P2015112167::nextMove()
{
	return (Action) (this->nextDirection); //Action type���� ����ȯ
}

/*�Է¹��� Action�� Movable�� ��� ����Ǵ� �Լ� : ���⼭�� ��ü������ ������ bestchoice�� ����� nextDirection�� �����մϴ�.*/
void P2015112167::ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	this->nextDirection = bestChoice(prevAction, board); // bestChoice �Լ� ȣ�� board�� ������ �������� ������ �Է���.
	std::cout << Action_Debug[prevAction] << "����" << std::endl;
}

/*�Է¹��� Action�� Not Movable�� ��� ����Ǵ� �Լ� : ���⼭�� ��ü������ ������ bestchoice�� ����� nextDirection�� �����մϴ�. ������ bestChoice�� ����� ��ȿ���� �ʴٸ� random ������.*/
void P2015112167::notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	this->nextDirection = bestChoice(prevAction, board);
	if (prevAction == this->nextDirection) //prevAction�� bestchoice�� ����� �������(�������� ���ϴ� ���) 
		this->nextDirection = rand() % 4; //������ ������ ������ ����.

	std::cout << Action_Debug[prevAction] << "����" << std::endl;
}

/*Player class���� �Է¹��� board ������ ���� Simulation�ϱ� ���� ����ϴ� �Լ�. Board class�� �Լ��� ��ӹ��� �ʰ� ���� / class Board::move()*/
bool P2015112167::moving(Action action, int board[BOARD_SIZE][BOARD_SIZE])
{
	bool isAbleToMove = false;
	// Ž���� ����
	const int dir[][2] = { 1, 0, 0, 1, 0, -1, -1, 0 };
	int dx = dir[action][0], dy = dir[action][1];

	std::vector<int> results[BOARD_SIZE];

	// ���� ���� �����δ�...2048 ���� ����.
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::vector<int> cellsToMove, originalCells;

		int x = dx < 0 ? BOARD_SIZE - 1 : i * abs(dy), y = dy < 0 ? BOARD_SIZE - 1 : i * abs(dx);
		int zeroCount = 0;

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int nx = (x + dx * j + BOARD_SIZE) % BOARD_SIZE;
			int ny = (y + dy * j + BOARD_SIZE) % BOARD_SIZE;

			// �տ� �ִ� 0�� ����.
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

		// �̵�.
		results[i] = shifting(cellsToMove);

		// �����̱� ����, ���� ���� �ǰ� �޶���.
		if (originalCells != results[i])
		{
			isAbleToMove = true;
		}
	}

	// �̵� �Ұ����ϸ� false.
	if (isAbleToMove == false)
	{
		return false;
	}

	// ���� �̵�
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

/*Player class���� �Է¹��� board ������ ���� Simulation�ϱ� ���� ����ϴ� �Լ�. Board class�� �Լ��� ��ӹ��� �ʰ� ���� /class Board::shift()*/
std::vector<int> P2015112167::shifting(std::vector<int> cells)
{
	std::vector<int> result;

	for (int i = 0; i < cells.size(); i++)
	{
		// ������ ���� ��ħ.
		if (i < cells.size() - 1 && cells[i] == cells[i + 1] && cells[i] != 0)
		{
			cells[i] *= 2;
			//score += cells[i]; score�� simulation �ܰ迡�� ī��Ʈ�� �ʿ� ����.

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

/* �����Լ� : �Է¹��� Board�� entrophy ���� ���ϴ� �Լ��Դϴ�.*/
// �ǵ� : board�� ���¿� ���� � �������� Ÿ���� �̵���Ű�� ���� �������� ���ϴ� ���� �ʿ��ϴٰ� �����ߴ�.
//		 ���������� ����ϸ� �翬�� ��������, ���������� �����ϰ� ������ board ������ �������� ���¸� ���ϱ� ���� entrophy ������ �����ߴ�.
//		 board���� 0�� �� ���� ��ȿ Ÿ���� ������ �������� ordered �ϴ�.(���� all 0�� �����̴�)
int P2015112167::countEntrophy(int board[BOARD_SIZE][BOARD_SIZE]) { // �� ���� �Ͻ������� �̷��� �����ϰ� �ۼ������� ���� ��������

	int entrophy = 10000; // default entrophy - 0���� ä���� board: 9983
	int countBlankCell = 0; // board�� 0�� ���� ����
	int sumValue = 0; // board�� value�� ���� ���� 

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 0)
				countBlankCell++; // �Է¹��� board�� ���Ұ� 0�̶�� 0�� ���� ����++; 
			else
				sumValue += board[i][j];
		}
	}
	/*�������� DATA�� ���� �����ڰ� �ٲپ �Ǵ� value  */ 
	//sumvalue�� ũ�� ��ȿ������ �ʴ�. : ������ ���� �������� ��� ��ΰ� ���� value�� ����ϱ� ���� ������ �ٸ� ������ entrophy�� ���ϱ� ���ؼ� �ʿ�(���ı���)
	entrophy = entrophy - ((countBlankCell + 1) * (sumValue + 1)); // 10000���� count �Ǵ°� �����ϱ� ���ؼ� upper bound lower bound set
	return entrophy;

}

/* �����Լ� : �Է¹��� Board�� entrophy ���� ���� ������ board���� ��� �������� �̵��ϴ� ���� �� ���� entrophy�� ���� �� �ִ��� �Ǵ��ϴ� �Լ��Դϴ�.*/
// �ǵ� : ������ ���¿� action�� ���� board�� �̵��� �� �ִ� ���°� �ִµ� ������ ������ entrophy �� ���ؼ� �� ���� entrophy�� ���� ���°� �� �����ϴٰ� �Ǵ��ϸ�
//       �̵��ϱ� ���ؼ� �� �Լ��� �����Ͽ���. ������ ����� ������ ���� �ʾҴ�. deep�ϰ� �Ÿ��� 1 ������ Node �Ӹ� �ƴ϶� �� ���� Ž���� �ؾ��ϴµ� ������� �־�
//       1 layer Ž���� �����߱� �����̴�. ������ �̸� �����ϱ� ���� ADVANCED -A, B �� ������ ����Ģ���� ����� general�ϰ� unspecific�� rule���� entrophy
//		 ��꿡 �����������ν� Algorithm�� ���⼺�� �����־���. ���� ������ algorithm�� ���� entrophy�� ������ ������, ���� ��� �̵��� �� �ִ� ��Ȳ�̸�
//       ���������� �̵��ϴ� ������� ���⼺�� �����ߴ�. ���� ���� ū ���� Corner�� ��� ������ �Ѵ�.
Action P2015112167::bestChoice(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	int currentEnt = countEntrophy(board); // �Է¹��� board�� entrophy �Է� 
	int entArray[4] = { 10000 }; // entrophy array, 10000���� �ʱ�ȭ�մϴ�.
	int tempBoard[BOARD_SIZE][BOARD_SIZE]; // board���� �̵��� �� �ִ� 4���� ������ ���ϱ� ���ؼ� �ʿ��� �ӽú��� tempBoard
	int topIndex; // �ֻ��� ���� indexing�ϴ� ����
	int temp = 10000; // �ӽú���
	int elementValue = 0; //board�� ���� ���Ҹ� �����ϴ� �ӽú���

	for (int k = 0; k < 4; k++) // �� �� �Ʒ� ���� 4���⿡ ���ؼ� entrophy value calculating �����ϴ� for ��
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				tempBoard[i][j] = board[i][j];  // �ӽú����� �Է¹��� board ���� �Ҵ�.
			}
		}

		if (moving((Action)k, tempBoard)) //tempBoard�� k �������� ������ �� �ִ� ��쿡�� ����.
		{
			entArray[k] = countEntrophy(tempBoard);

			/*ADVANCED-A weight : �Ʒ� ���� �̵��� ������ ���� �̵��� �����ϴٸ� �߰����� weight�� �ο��մϴ�.*/
			if (k == 2 || k == 3)
			{
				entArray[k] -= 500; // ���������� corner�� Ÿ�ϵ��� ���� �ִ� ���� �� ���� ������ ���� �� �ִٰ� �Ǵ��Ͽ� ����ġ�� �ο��߽��ϴ�.
			}
			/*ADVANCED-B weight : �� ������ �Ʒ� corner�� ���� ū ���� ����ȴٸ� �߰����� weight�� �ο��մϴ�.*/
			for (int x = 0; x < 4; x++) {
				for (int y = 0; y < 4; y++)
				{
					if (elementValue <= tempBoard[x][y])
						elementValue = tempBoard[x][y]; // element �߿� ���� ū �� indexing
				}
			}
			if (elementValue == tempBoard[3][3])
				entArray[k] -= 100;// ���������� �� ������ �Ʒ� corner�� ���� ���� ���� Ÿ���� �ִ� ���� �� ���� ������ �ִٰ� �Ǵ��Ͽ� ����ġ�� �ο��߽��ϴ�.
		}
		else { // k �������� ������ �� ���ٸ� � �����̵� �ִ��� �������� �ο�. 
			entArray[k] = 10000;
		}
	}

	for (int i = 0; i < 4; i++) //����� ���� �� ���� ���� ���� entrophy ���� �����ϱ� ���� for��
	{
		if (temp >= entArray[i])
		{
			temp = entArray[i];
			topIndex = i;
		}
	}

	return (Action)topIndex; // ���� ���� entrophy ���� ���� return
	
}

/*���� �Լ�: ���� �̿ϼ��Դϴ�. �̹� ����������Ʈ������ ������� �ʽ��ϴ�.*/
std::map<int,int> P2015112167::deepChoice(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	
	// recursive �� ������� deep�ϰ� search�� �����ϴ� Algorithm ������ ������ �ð� ���� 
	// ���� �Ⱓ ���� ���� ���� ��ǥ. �� �̻� ������ �� ���ų�, ��� �����̴� entrophy�� ���� case�� ��� ��� Ż��
	// �ٷ� ���� Node�� entrophy�� �ƴ϶� ������ Node �� entrophy ���� ���� ���� ���� �������� �̵�, ���� ����Ǹ鼭 ��������� update �ȴ�.
	std::map<int, int>nextPath;
	return nextPath;
}
 
/*
1. ���� ��Ȳ�� �������� �ʰ� move��shift�� player Ŭ�������� ���� �� �õ� -> score�� �� �� score �� ū ���� ����
2. ���� ��Ȳ�� �������� �ʰ� move shift ���� �� ���� �̵� ����� entrophy �� �����ϴ� �������� ����
3. ���� ��Ȳ �����ϰ� �Ұ����� ��Ȳ����.
4. ��Ʈ���� �� ���� ��� ����� ��ġ�� �� �����ִ°�? �̰ſ� ���� �򰡸� �ؾ���.

��Ʈ���� �򰡸� -> score�� �� ĭ�� ������ ����
*/