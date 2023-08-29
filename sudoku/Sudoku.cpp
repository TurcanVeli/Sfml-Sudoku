#include "Sudoku.h"
#include <random>
#include <iostream>

Sudoku::Sudoku()
{
	this->initVariables();
}

Sudoku::~Sudoku()
{

	this->board.release();
}


void Sudoku::initVariables()
{
	this->level = EASY;
	this->fillBoard_withZeros();
}


//---------------------
std::unique_ptr<std::vector<std::vector<int>>> Sudoku::getBoard()
{
	return std::unique_ptr<std::vector<std::vector<int>>>();
}

std::unique_ptr<std::vector<std::vector<bool>>> Sudoku::getTruthBoard()
{
	return std::unique_ptr<std::vector<std::vector<bool>>>();
}
//------------------------

void Sudoku::fillBoard_withZeros()
{
	std::vector<int> temp;
	this->board->clear();
	for(int j = 0; j < 9; j++)
	{
		temp.push_back(0);

	}
	for(int i = 0; i<9; i++)
	{
		this->board->push_back(temp);
	}
	temp.clear();
}



bool Sudoku::findZero()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if(this->board->at(i).at(j) == UNASSIGNED)
			{
				return true;
			}
		}
	}
	return false;
}


void Sudoku::genSudo()
{
	int s = 0, v = 0, num = 0;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(1, 9);//produce random int between 1-9, 1 and 9 is include
	std::uniform_int_distribution<int> pos(0, 8);
	for (int k = 0; k < 26; k++)
	{
	label:	s = pos(generator);
			v = pos(generator);
			num = distribution(generator);
		if (this->isSafe(num, s, v))
		{
			this->board->at(s).at(v) = num;
		}
		else
		{
			goto label;
		}
	}

}

void Sudoku::generateSudoku()
{
	this->fillBoard_withZeros();
	this->genSudo();
	this->fillTruthBoard();
	//this->EraseNumber(EASY);
}



void Sudoku::EraseNumber(Level level)
{
	int s = 0, v = 0, num = 0;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> pos(0, 8);
	if (level == EASY)
	{
		for (int i = 0; i < 20; i++)
		{
			s = pos(generator);
			v = pos(generator);
			this->board->at(s).at(v) == UNASSIGNED;
		}

	}
}


bool Sudoku::solveSudo(int r ,int c)
{
	
	if(c  == 9 && r == 8)
	{
		return true;
	}


	if (c == 9)
	{
		r++;
		c = 0;
	}
	
	if(this->board->at(r).at(c) != UNASSIGNED)
	{
		return this->solveSudo(r, c + 1);
	}
	for(int num = 1; num <10; num++)
	{
		if (this->isSafe(num,r, c))
		{
			this->board->at(r).at(c) = num;

			if(this->solveSudo(r,c+1))
			{
				return true;
			}
		}
		this->board->at(r).at(c) = UNASSIGNED;
	}
	return false;
}


bool Sudoku::isSafe(int num, int r, int c)
{
	return this->checkRow(num, r) && this->checkCol(num, c) && this->checkGrid(num, r, c);
}

bool Sudoku::checkRow(int num, int r)
{
	for (int i = 0; i < 9; i++)
	{
		if (this->board->at(r).at(i) == num)
		{
			return false;
		}
	}

	return true;
}

bool Sudoku::checkCol(int num, int c)
{
	for (int i = 0; i < 9; i++)
	{

		if (this->board->at(i).at(c) == num)
		{
			return false;

		}

	}
	return true;
}

bool Sudoku::checkGrid(int num, int r, int c)
{
	int sR = r - r % 3;
	int sC = c - c % 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			if (this->board->at(sR + i).at(sC + j) == num)

			{
				return false;

			}
		}

	}
	return true;
}


void Sudoku::fillTruthBoard()
{
	std::unique_ptr<std::vector<bool>> temp = std::make_unique<std::vector<bool>>();
	this->Truthboard->clear();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (this->board->at(i).at(j) == UNASSIGNED) {
				temp->push_back(true);

			}
			else {
				temp->push_back(false);
			}
		}
		this->Truthboard->push_back(*temp);
		temp->clear();

	}
	temp.release();

}
