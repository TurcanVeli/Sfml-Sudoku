#include "Game.h"

Game::Game()
{
	this->initVariables();
	this->loadFont();
	this->initWindow();
	this->initBoard();
	this->setupTexts();
	this->generateButton->initvariables("Generate", this->font, sf::Vector2f(230, 40));
	this->solveButton->initvariables("Solve", this->font, sf::Vector2f(450, 40));
	this->state = GAME;
}

Game::~Game()
{
	delete this->window;
	this->window = { nullptr };
	

}


void Game::initVariables()
{

	this->height	= 800;
	this->width		= 800;
	this->xCoord[0] = (this->width / 2) -  static_cast<int>(this->cellSize*9 /  2 );
	this->yCoord[0] = (this->width / 2) - static_cast<int>(this->cellSize * 9 / 2 );
	this->videoMode = sf::VideoMode(this->height, this->width);
	this->window	= { nullptr };
	this->input = 0;
	this->sudoku->generateSudoku();
	this->printBoard();
}







void Game::initWindow()
{
	
	this->window = new sf::RenderWindow(this->videoMode, "Sudoku" );
	this->window->setFramerateLimit(60);

}

void Game::initBoard()
{

	for (int i = 1; i < 9; i++)
	{
		this->xCoord[i] = this->xCoord[i - 1] + this->cellSize;
		this->yCoord[i] = this->yCoord[i - 1] + this->cellSize;
	}

}

bool Game::loadFont()
{
	
	if (!this->font.loadFromFile("Assets/arial.ttf"))
	{
		std::cout << "Font couldn't loaded!" << std::endl;
		return false;
	}
	return true;

}


//Set numbers to text value
//Fonksion ismi değişecek
void Game::setupTexts()
{
	this->number.setFont(this->font);
	this->number.setCharacterSize(20);
	this->number.setFillColor(sf::Color::Black);

	this->Smallcell.setSize(sf::Vector2f(this->cellSize, this->cellSize));
	this->Smallcell.setOutlineThickness(0.7f);
	this->Smallcell.setOutlineColor(sf::Color::Black);
	this->Smallcell.setFillColor(sf::Color::Transparent);

	for (int i = 0; i < 9; i++) 
	{		
		this->V_SmallCellsRow->push_back(this->Smallcell);
	}
	for (int j = 0; j < 9; j++)
	{
		this->V_SmallCells->push_back(*this->V_SmallCellsRow);
		

	}

	this->MediumCell.setSize(sf::Vector2f(this->cellSize * 3.f, this->cellSize * 3.f ));
	this->MediumCell.setOutlineThickness(3.5f);
	this->MediumCell.setOutlineColor(sf::Color::Black);
	this->LargeCell.setSize(sf::Vector2f(this->cellSize * 9.f, this->cellSize * 9.f));
	this->LargeCell.setOutlineThickness(5.f);
	this->LargeCell.setOutlineColor(sf::Color::Black);
	this->LargeCell.setPosition(sf::Vector2f(this->xCoord[0], this->yCoord[0]));

	this->MediumCell.setFillColor(sf::Color::Transparent);
	this->LargeCell.setFillColor(sf::Color::White);

}


bool Game::running()
{
	return this->window->isOpen();
}




void Game::Update()
{
	this->pollEvent();
	this->updateMousePos();
	this->generateButton->Hover(this->mousePosView);
	this->solveButton->Hover(this->mousePosView);
}

void Game::Render()
{

	this->window->clear(sf::Color::Magenta);
	this->fillTable();
	this->generateButton->render(*this->window);
	this->solveButton->render(*this->window);
	this->window->display();

}

void Game::pollEvent()
{
	if(this->state == GAME)
	{
	
	
	
	
		while (this->window->pollEvent(this->event)) {

			switch (this->event.type)
			{
			case(sf::Event::Closed()):
				this->window->close();
				break;

			case sf::Event::KeyPressed:
				if (this->Coords->size() == 2)
				{
			
			
					if (this->event.key.code == sf::Keyboard::Num1)
						this->input = 1;
					else if (this->event.key.code == sf::Keyboard::Num2)
						this->input = 2;
					else if (this->event.key.code == sf::Keyboard::Num3)
						this->input = 3;
					else if (this->event.key.code == sf::Keyboard::Num4)
						this->input = 4;
					else if (this->event.key.code == sf::Keyboard::Num5)
						this->input = 5;
					else if (this->event.key.code == sf::Keyboard::Num6)
						this->input = 6;
					else if (this->event.key.code == sf::Keyboard::Num7)
						this->input = 7;
					else if (this->event.key.code == sf::Keyboard::Num8)
						this->input = 8;
					else if (this->event.key.code == sf::Keyboard::Num9)
						this->input = 9;

				this->changeNumber(*this->Coords);
			
				}

				break;
			case sf::Event::MouseButtonPressed:
			
				if(this->generateButton->isClicked(this->event,this->mousePosView))
				{
					this->sudoku->generateSudoku();
		
				}
				if (this->solveButton->isClicked(this->event, this->mousePosView))
				{
					this->state = SOLVE;
					if(this->sudoku->solveSudo(0, 0))
					{
						this->sudoku->fillTruthBoard();

					
					}
					else {
						std::cout << "Sudoku is invalid" << std::endl;
					}
					this->state = GAME;

				}
				if (this->event.mouseButton.button == sf::Mouse::Left)
				{
				
					this->uptadeBoard();
				}
			default:
				break;
			}
		}
	}
}

void Game::fillTable()
{
	this->window->draw(this->LargeCell);

	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 9; j++) {

			if (i % 3  == 0 && j % 3 == 0) {
				this->MediumCell.setPosition(sf::Vector2f(this->xCoord[j], this->yCoord[i]));
				this->window->draw(this->MediumCell);
			}
			this->V_SmallCells->at(i).at(j).setPosition(sf::Vector2f(this->xCoord[j], this->yCoord[i]));
			this->window->draw(this->V_SmallCells->at(i).at(j));
			this->number.setString(std::to_string(this->sudoku->board->at(i).at(j)));
			this->number.setPosition(this->xCoord[j] + static_cast<int>(this->cellSize / 2.f) - 10, this->yCoord[i] + static_cast<int>(this->cellSize / 2.f) - 10);
			this->window->draw(this->number);
		}

	}
}


void Game::printBoard()
{
	for (int i =0; i<9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << this->sudoku->board->at(i).at(j)<< " ";

		}
		std::cout<< std::endl;
	}
	std::cout << "            " << std::endl;

}

bool Game::isGameFinished()
{	
	return false;
}







void Game::updateMousePos()
{
	this->MousePos = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->MousePos);

}



void Game::uptadeBoard()
{
	
		for (int row = 0; row < 9; row++) 
		{
			for(int column = 0; column <9; column++ )
			{
				if (this->V_SmallCells->at(row).at(column).getGlobalBounds().contains(this->mousePosView) && this->sudoku->Truthboard->at(row).at(column) == true)
			
				{
					if (this->Coords->size() == 2) 
					{
						this->fillColorCells(sf::Color::Transparent, this->Coords->at(0), this->Coords->at(1));
					}
					this->fillColorCells(sf::Color::Red, row, column);
	
				}
			}
		}
}

void Game::changeNumber(std::vector<int> coords)
{
	if (this->input != 0) {
		this->sudoku->board->at(coords.at(0)).at(coords.at(1)) = this->input;
		this->input = 0;
	}
}

void Game::fillColorCells(sf::Color color, int r, int c)
{
	int startingRow = r - r % 3;
	int startingColumn = c - c % 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			this->V_SmallCells->at(startingRow + i).at(startingColumn + j).setFillColor(color);
		}
	}

	for (int i = 0; i < 9; i++)
	{
		this->V_SmallCells->at(i).at(c).setFillColor(color);
		this->V_SmallCells->at(r).at(i).setFillColor(color);



	}

	this->Coords->clear();
	this->Coords->insert(this->Coords->begin(), r);
	this->Coords->insert(this->Coords->begin() + 1, c);


}
