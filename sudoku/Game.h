#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include "Sudoku.h"
#include "Button.h"
//We have 3 section, one is sudoku area. Second one is Solve button. Third is Quit button.
//Background will be initilaze
//Game have 3 level at least. 




class Game
{

	public:
		Game();
		~Game();

		sf::RenderWindow* window;
		sf::Event event;
		sf::VideoMode videoMode;
		int height;
		int width;
		//Game State
		enum STATE { GAME = 0, SOLVE, RESULT, END };
		STATE state;
		sf::Font font;
		sf::Text number;

		sf::RectangleShape Smallcell;
		sf::RectangleShape MediumCell;
		sf::RectangleShape LargeCell;
		
		std::vector<int> Coords[2] = {};
		std::vector<std::vector<int>> Board;
		std::vector<sf::RectangleShape> V_SmallCellsRow[9] = {};
		std::vector<std::vector<sf::RectangleShape>> V_SmallCells[9] = {};
		
		std::unique_ptr<Sudoku> sudoku = std::make_unique<Sudoku>();
		std::unique_ptr<Button> generateButton = std::make_unique<Button>();
		std::unique_ptr<Button> solveButton = std::make_unique<Button>();
		int cellSize = 45; //SmallCell Size 
		int xCoord[9] = { 0 };  // Dinamik memory kullan burada
		int yCoord[9] = { 0 };

		int input;

		//MousePositions
		//sf::Vector2i MousePos
		sf::Vector2i MousePos;
		sf::Vector2f mousePosView;
		
		//We should select smallCell with mouse and change number in it if this is changable. 
		//Selected cell will be yellow and we have to select one at same time.
		//Taken input with keyboard. 


		void Update();
		void Render();
		void pollEvent();
		void fillTable();

		bool isGameFinished();//Array of solution == Board array
		
		void updateMousePos();
		void uptadeBoard();
		void changeNumber(std::vector<int> coords);

		void fillColorCells(sf::Color color, int r, int c);

		void printBoard();
	


		//Accessor
		bool running();
	

	private:
		void initVariables();
		void initWindow();
		void initBoard();
		bool loadFont();
		void setupTexts();


};

