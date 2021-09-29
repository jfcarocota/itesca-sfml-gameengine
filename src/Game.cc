#include "Game.hh"
#include "Constants.hh"
#include "Collider.hh"
#include "InputsSystem.hh"
#include "Animation.hh"
#include "Rigidbody.hh"
#include<iostream>

Collider* collider{new Collider(100, 100, 100, 100, sf::Color::Green, 5.f)};

sf::Texture* texture1{new sf::Texture()};
sf::Sprite* sprite1{new sf::Sprite()};

sf::Clock* timer{new sf::Clock()};
float deltaTime{};
const float playerSpeed{200.f};
const float playerScale{4.f};

sf::CircleShape* pivotPoint{new sf::CircleShape()};

Animation* idleAnimation{new Animation()};
Animation* runAnimation{new Animation()};

Rigidbody* rigidbody1{new Rigidbody()};

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

}

void Game::Draw()
{
  window->draw(*sprite1);
  window->draw(*pivotPoint);
}

void Game::Render()
{
  window->clear(sf::Color(0, 0, 0, 255));
  Draw();
  window->display();
}
void Game::Init()
{
  //gravity = new b2Vec2(0.f, -50.8f);
  gravity = new b2Vec2(0.f, 0.f);
  world = new b2World(*gravity);

  texture1->loadFromFile("assets/sprites.png");
  texture1->setSmooth(false);
  sprite1->setTexture(*texture1);
  sprite1->setTextureRect(sf::IntRect(0 * 16, 5 * 16, 16, 16));
  sprite1->setColor(sf::Color::White);
  sprite1->setPosition(100, 0);
  sprite1->setScale(sf::Vector2f(playerScale, playerScale));
  sprite1->setOrigin(sprite1->getLocalBounds().width / 2, sprite1->getLocalBounds().height / 2);

  pivotPoint->setRadius(1);
  pivotPoint->setFillColor(sf::Color::Green);
  pivotPoint->setOutlineColor(sf::Color::Green);
  pivotPoint->setOutlineThickness(2);

  idleAnimation = new Animation(0, 5, sprite1, 0.05f, 5);
  runAnimation = new Animation(0, 5, sprite1, 0.08f, 6);

  rigidbody1 = new Rigidbody(world, b2BodyType::b2_dynamicBody, 
  new b2Vec2(sprite1->getPosition().x, sprite1->getPosition().y), 
  16 * playerScale, 16 * playerScale, 1, 0, 0, 
  b2Vec2(sprite1->getOrigin().x, sprite1->getOrigin().y), 0.f);

  Update();
}

void Game::UpdatePhysics()
{
  world->ClearForces();
  world->Step(deltaTime, 8, 8);
  std::cout << deltaTime << std::endl;

  sprite1->setPosition(rigidbody1->GetBody()->GetPosition().x, 
  -rigidbody1->GetBody()->GetPosition().y);
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
    deltaTime = timer->getElapsedTime().asSeconds();
    timer->restart();

    UpdatePhysics();

    Inputs();
    pivotPoint->setPosition(sprite1->getPosition() + sprite1->getOrigin());

    if(std::abs(InputsSystem::GetAxis().x) || std::abs(InputsSystem::GetAxis().y))
    {
      runAnimation->Play(deltaTime);
    }
    else
    {
      idleAnimation->Play(deltaTime);
    }

    //flip sprite
    sprite1->setScale(InputsSystem::GetAxis().x > 0 ? playerScale : 
    InputsSystem::GetAxis().x < 0 ? -playerScale : 
    sprite1->getScale().x, sprite1->getScale().y);
    rigidbody1->GetBody()->SetLinearVelocity(b2Vec2(
      InputsSystem::GetAxis().x * playerSpeed, 
      -InputsSystem::GetAxis().y * playerSpeed));
    Render();
  }

  delete window;
  delete event;
}