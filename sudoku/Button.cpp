#include "Button.h"
#include "Sudoku.h"



Button::Button()
{

}

Button::~Button()
{
}

void Button::initvariables(std::string s, sf::Font& font, sf::Vector2f position) 
{
	this->content = s;
	*this->font = font;
	*this->position = position;
	this->initilazeButton();
}

bool Button::isClicked(sf::Event e, sf::Vector2f mousePos)
{
	if (this->shape->getGlobalBounds().contains(mousePos) && e.mouseButton.button == sf::Mouse::Left)
	{
		return true;
	}
	return false;
}



void Button::render(sf::RenderWindow& window)
{
	window.draw(*this->shape);
	window.draw(*this->text);

}

void Button::initilazeButton()
{

	this->text->setFont(*this->font);
	this->text->setString(this->content);
	this->text->setCharacterSize(24);
	this->text->setPosition(*this->position);
	this->text->setFillColor(sf::Color::Black);
	this->shape->setSize(sf::Vector2f(120,50));
	this->shape->setPosition(this->position->x - static_cast<int>( this->text->getGlobalBounds().width/9 ) , this->position->y  - static_cast<int>(this->text->getGlobalBounds().height / 2));
	this->shape->setFillColor(sf::Color::White);
	this->shape->setOutlineThickness(2);
	this->shape->setOutlineColor(sf::Color::Black);
}

void Button::Hover(sf::Vector2f mousePos)
{
	if(this->shape->getGlobalBounds().contains(mousePos))
	{
		this->shape->setFillColor(sf::Color::Black);
		this->shape->setOutlineColor(sf::Color::White);
		this->text->setFillColor(sf::Color::White);
		
	}
	else {
		this->shape->setFillColor(sf::Color::White);
		this->shape->setOutlineColor(sf::Color::Black);
		this->text->setFillColor(sf::Color::Black);

	}

}





