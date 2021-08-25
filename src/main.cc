#include<iostream>
#include<SFML/Graphics.hpp>
#include "Constants.hh"

int main()
{
  sf::RenderWindow* window{new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My game")};
  sf::Event event;

  while (window->isOpen())
  {
    while (window->pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
      {
        window->close();
      }
    }
  }
  delete window;
  return 0;
}