#pragma once

#include<SFML/Graphics.hpp>
#include "Rigidbody.hh"

class Character
{
private:
  sf::Texture* texture{};
  sf::Sprite* sprite{};
  Rigidbody* rigidbody{};
  sf::CircleShape* pivotPoint{};
  sf::RenderWindow* window{};
  b2World* world{};
  float scale{};
  float moveSpeed{};

  void Move();
  void FlipSprite();
public:
  Character(const char* textureUrl, int col, int row, float width, float height, float scale, float moveSpeed,
  sf::Vector2f* position, sf::RenderWindow*& window, b2World*& world);
  ~Character();

  void Update(float& deltaTime);
  void Draw();

  sf::Sprite* GetSprite() const;
};