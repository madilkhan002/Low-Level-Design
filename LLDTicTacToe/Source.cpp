#include<bits/stdc++.h>
using namespace std;

// Enum of cell type
enum CellType {
	X = 1,
	O = 2
};

// class of cells
class Cell
{
public:
	CellType celltype;
	Cell(CellType celltype)
	{
		this->celltype = celltype;
	}
};

class CellX : public Cell
{
public:
	CellX() :Cell(X){}
};



class CellO : public Cell
{
public:
	CellO() :Cell(O) {}
};



// Player Class
class Player
{
public:
	CellType celltype;
	string name;
	Player(CellType celltype, string name)
	{
		this->name = name;
		this->celltype = celltype;
	}
};


// board class
class Board
{
public:
	vector<vector<Cell*>>board;
	int size;
	Board(int size)
	{
		this->size = size;
		board.resize(size, vector<Cell*>(size));
		initializeBoard();
	}

	void initializeBoard()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				board[i][j] = nullptr;
			}
		}
	}
	
	bool addCell(int i, int j, CellType celltype)
	{
		if (board[i][j] != nullptr) return false;
		board[i][j] = new Cell(celltype);
		return 1;
	}

	void printBoard()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (board[i][j] == nullptr) cout << "|   ";
				else if (board[i][j]->celltype == X) cout << "| X ";
				else cout << "| O ";
			}
			cout << endl;
		}
	}
};

// Game

class Game
{
public:
	Board *boardObj = nullptr;
	deque<Player>player;
	int size;
	Game(int size)
	{
		this->size = size;
	}
	void initializeGame()
	{
		CellX cellx;
		CellO cello;
		Player player1(cellx.celltype, "Player1");
		Player player2(cello.celltype, "Player2");

		player.push_back(player1);
		player.push_back(player2);
		boardObj = new Board(size);
	}

	void playGame()
	{
		bool noWinner = true;
		while (noWinner==true)
		{
			boardObj->printBoard();
			auto currentPlayer = player.front();
			player.pop_front();

			int i, j;
			cout << "Player Name : " << currentPlayer.name << " MOVE...\n";
			cout << "Enter Co-ordinates : ";
			cin >> i >> j;
			if (i < 0 || i >= size || j < 0 || j >= size)
			{
				printf("%s", "Invalid Corrdinates\n");
				player.push_front(currentPlayer);
				continue;
			}

			bool isAdded = boardObj->addCell(i, j, currentPlayer.celltype);
			if (isAdded == false)
			{
				printf("%s", "Already Occupied Cell\n");
				player.push_front(currentPlayer);
				continue;
			}
			
			int result = checkWinner();
			if (result == 1)
			{
				cout << currentPlayer.name << " Wins......";
				return;
			}
			else if (result == 2)
			{
				noWinner = false;
			}

			player.push_back(currentPlayer);

		}
		cout << "Game Tied\nBesT OF LUCK NExT TiME\n";
	}

	int checkWinner()
	{
		// rows
		for (int i = 0; i < size; i++)
		{
			bool isWinner = true;
			for (int j = 0; j < size; j++)
			{
				if (boardObj->board[i][j] == nullptr)
				{
					isWinner = false;
					break;
				}
				if (j > 0 && (boardObj->board[i][j]->celltype != boardObj->board[i][j - 1]->celltype))
				{
					isWinner = false;
				}
			}
			if (isWinner == true) return 1;
		}
		// cols
		for (int j = 0; j < size; j++)
		{
			bool isWinner = true;
			for (int i = 0; i < size; i++)
			{
				if (boardObj->board[i][j] == nullptr)
				{
					isWinner = false;
					break;
				}
				if (i > 0 && (boardObj->board[i][j]->celltype != boardObj->board[i-1][j]->celltype))
				{
					isWinner = false;
				}
			}
			if (isWinner == true) return 1;
		}

		// check for draw

		int count = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (boardObj->board[i][j] != nullptr) count++;
			}
		}

		return count == (size * size) ? 2 : 0;
	}

};


int main()
{
	Game game(3);
	game.initializeGame();
	game.playGame();


	return 0;
}