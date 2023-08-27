#pragma once

#include <memory>
#include <vector>
#include <limits>
#include <chrono>
#define UNASSIGNED 0

class Sudoku
{

	public:
		Sudoku();
		~Sudoku();
		enum Level
		{
			EASY = 0, MEDIUM, HARD
		};
		Level level;
	
	
		void genSudo();
		void generateSudoku();
		void fillTruthBoard();
		bool solveSudo(int r, int c);
		std::unique_ptr<std::vector<std::vector<int>>> board = std::make_unique<std::vector<std::vector<int>>>();
		std::unique_ptr<std::vector<std::vector<bool>>> Truthboard = std::make_unique<std::vector<std::vector<bool>>>();
		
	private:
		std::unique_ptr<std::vector<std::vector<int>>> getBoard();
		std::unique_ptr<std::vector<std::vector<bool>>> getTruthBoard();
		void initVariables();
		void fillBoard_withZeros();
		bool findZero();
		void EraseNumber(Level level);
		bool isSafe(int num, int r, int c);
		bool checkRow(int num, int r);
		bool checkCol(int num, int c);
		bool checkGrid(int num, int r, int c);


};

