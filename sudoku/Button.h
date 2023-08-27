#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "memory"

class Button 
{
	public:
		Button();
		~Button();
		void initvariables(std::string s, sf::Font& font, sf::Vector2f position);
		bool isClicked(sf::Event e, sf::Vector2f mousePos);
		void render(sf::RenderWindow& window);
		void Hover(sf::Vector2f mousePos);
	private:
		void initilazeButton();
		std::unique_ptr<sf::RectangleShape> shape = std::make_unique<sf::RectangleShape>();
		std::unique_ptr<sf::Text> text = std::make_unique<sf::Text>();
		std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
		std::unique_ptr<sf::Vector2f> position = std::make_unique<sf::Vector2f>();
		std::string content;
		
};

