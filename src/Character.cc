#include "Character.hh"
#include "InputsSystem.hh"
#include "Animation.hh"

Animation* idleAnimation{new Animation()};
Animation* runAnimation{new Animation()};

Character::Character(const char* textureUrl, int col, int row, float width, float height, float scale, float moveSpeed,
sf::Vector2f* position, sf::RenderWindow*& window, b2World*& world)
{
  this->window = window;
  this->world = world;
  this->scale = scale;
  this->moveSpeed = moveSpeed;

  texture = new sf::Texture();
  sprite = new sf::Sprite();
  pivotPoint = new sf::CircleShape();

  texture->loadFromFile("assets/sprites.png");
  texture->setSmooth(false);

  sprite->setTexture(*texture);
  sprite->setTextureRect(sf::IntRect(col * width, row * height, width, height));
  sprite->setColor(sf::Color::White);
  sprite->setPosition(*position);
  sprite->setScale(scale, scale);

  pivotPoint->setRadius(1);
  pivotPoint->setFillColor(sf::Color::Green);
  pivotPoint->setOutlineColor(sf::Color::Green);
  pivotPoint->setOutlineThickness(2);

  rigidbody = new Rigidbody(world, b2BodyType::b2_dynamicBody, 
  new b2Vec2(sprite->getPosition().x, sprite->getPosition().y), 
  width * scale / 2, height * scale / 2, 1, 0, 0, 
  b2Vec2(sprite->getOrigin().x , sprite->getOrigin().y), 0.f);

  sprite->setOrigin(width / 2, height / 2);

  idleAnimation = new Animation(0, 5, sprite, 0.05f, 5);
  runAnimation = new Animation(0, 5, sprite, 0.08f, 6);
}

Character::~Character()
{
}

void Character::Draw()
{
  window->draw(*sprite);
  window->draw(*pivotPoint);
}

void Character::Update(float& deltaTime)
{
  sprite->setPosition(rigidbody->GetPositionSFML());
  pivotPoint->setPosition(rigidbody->GetPositionSFML());
  FlipSprite();
  Move();

  if(std::abs(InputsSystem::GetAxis().x) || std::abs(InputsSystem::GetAxis().y))
  {
    runAnimation->Play(deltaTime);
  }
  else
  {
    idleAnimation->Play(deltaTime);
  }
}

void Character::FlipSprite()
{
    sprite->setScale(InputsSystem::GetAxis().x > 0 ? scale :
    InputsSystem::GetAxis().x < 0 ? -scale :
    sprite->getScale().x, sprite->getScale().y);
}

void Character::Move()
{
  rigidbody->Move(b2Vec2(InputsSystem::GetAxis().x * moveSpeed, InputsSystem::GetAxis().y * moveSpeed));
}

sf::Sprite* Character::GetSprite() const
{
  return sprite;
}
