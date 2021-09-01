#include "Game.hh"
#include "Constants.hh"
#include "Collider.hh"
#include "InputsSystem.hh"
#include<iostream>
//#include "Rectangle.hh"

//Rectangle* rectangle{new Rectangle(100, 100, 100, 100, sf::Color(255, 0, 0, 255))};
//Rectangle* rectangle2{new Rectangle(100, 100, 100, 100)};
Collider* collider{new Collider(100, 100, 100, 100, sf::Color::Green, 5.f)};

Game::Game()
{
  window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
  event = new sf::Event();
}

Game::~Game()
{
}

void Game::Inputs()
{
  std::cout << "Axis x: " << InputsSystem::GetAxis().x << " Axis Y: " << InputsSystem::GetAxis().y << std::endl;
}

void Game::Draw()
{
  window->draw(*collider->GetShape());
}

void Game::Render()
{
  window->clear(sf::Color(0, 0, 0, 255));
  Draw();
  window->display();
}
void Game::Init()
{

  Update();
}

void Game::Update()
{
  while (window->isOpen())
  {
    while (window->pollEvent(*event))
    {
      if(event->type == sf::Event::Closed)
      {
        window->close();
      }
    }

    Inputs();
    collider->GetShape()->move(InputsSystem::GetAxis());
    Render();
  }

  delete window;
  delete event;
}