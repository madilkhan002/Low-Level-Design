#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;

class Jump {
public:
	int start;
	int end;
};

class Cell
{
public:
	Jump jump;
};


class Player
{
public:
	static int _unique_id;
	int id = 0;
	int currentPos;
	Player()
	{
		_unique_id++;
		id = _unique_id;
		currentPos = 0;
	}
};

int Player::_unique_id = 0;

class Board
{
public:
	Cell** cell;

	Board(int boardSize, int snakes, int ladders)
	{
		cell = new Cell *[boardSize];
		for (int i = 0; i < boardSize; i++)
		{
			cell[i] = new Cell[boardSize];
		}
		//set default -1 for jump
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				cell[i][j].jump.start = -1;
				cell[i][j].jump.end = -1;
			}
		}
		initializeBoard(snakes, ladders, boardSize);
	}
	void initializeBoard(int snakes, int ladders, int boardSize)
	{
		srand(time(0));
		unordered_set<int>ust;
		while (snakes > 0)
		{
			int startPoint = rand() % (boardSize * boardSize);
			int endPoint = rand() % (boardSize * boardSize);
			if (startPoint <= endPoint) continue;
			if (ust.find(startPoint) != ust.end()) continue;
			int sx = startPoint / boardSize;
			int sy = startPoint % boardSize;
			int ex = endPoint / boardSize;
			int ey = endPoint % boardSize;

			cell[sx][sy].jump.start = ex;
			cell[sx][sy].jump.end = ey;
			ust.insert(startPoint);
			snakes--;
		}

		while (ladders > 0)
		{
			int startPoint = rand() % (boardSize * boardSize);
			int endPoint = rand() % (boardSize * boardSize);
			if (startPoint >= endPoint) continue;
			if (ust.find(startPoint) != ust.end()) continue;
			if (ust.find(endPoint) != ust.end()) continue;
			int sx = startPoint / boardSize;
			int sy = startPoint % boardSize;
			int ex = endPoint / boardSize;
			int ey = endPoint % boardSize;

			cell[sx][sy].jump.start = ex;
			cell[sx][sy].jump.end = ey;
			ust.insert(startPoint);
			ladders--;
		}
	}
};


class Dice
{
	int diceCount;
public:
	Dice(int diceCount)
	{
		this->diceCount = diceCount;
	}
	int rollDice()
	{
		int total_score = 0;
		srand(time(0));
		for (int i = 0; i < diceCount; i++)
		{
			int score = (rand() % 6) + 1;
			total_score += score;
		}
		return total_score;
	}
};

class Game
{
	Board* board;
	Dice* dice;
	deque<Player*>dq;
	Player *Winner = nullptr;
	int lastPos;
	int boardSize;
public:
	Game(int total_dice, int boardSize, int sankes, int ladders, int players)
	{
		board = new Board(boardSize, sankes, ladders);
		dice = new Dice(total_dice);
		for (int i = 0; i < players; i++)
		{
			Player * player = new Player();
			dq.push_back(player);
		}
		this->lastPos = boardSize * boardSize;
		this->boardSize = boardSize;
	}

	void playGame()
	{
		while (Winner == nullptr)
		{
			Player * currentPlayer = findCurrentPlayerMove();
			int currentPosition = currentPlayer->currentPos;
			currentPosition += dice->rollDice();
			if (currentPosition > lastPos)
			{
				Winner = currentPlayer;
				break;
			}
			currentPosition = checkJump(currentPosition);
			currentPlayer->currentPos = currentPosition;
			/*cout << "Current Player : " << currentPlayer->id << endl;
			cout << "Current Position : " << currentPlayer->currentPos << endl;
			cout << "|.......................|\n";*/

		}
		cout << "Player ID : " << Winner->id << " Won!....\n";
	}




private:
	Player * findCurrentPlayerMove()
	{
		auto currentPlayer = dq.front();
		dq.pop_front();
		dq.push_back(currentPlayer);
		return currentPlayer;
	}

	int checkJump(int position)
	{
		int i = position / boardSize;
		int j = position % boardSize;
		int x = board->cell[i][j].jump.start;
		int y = board->cell[i][j].jump.end;
		if (x == -1) return (i * boardSize) + j;
		return (x * boardSize) + y;
	}
};


int main()
{
	int total_dice = 1;
	int boardSize = 10;
	int sankes = 2;
	int ladders = 2;
	int players = 2;

	Game game(total_dice, boardSize, sankes, ladders, players);
	game.playGame();
	


	return 0;
}