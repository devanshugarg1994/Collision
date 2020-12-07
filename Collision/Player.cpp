#include "Player.h"

void Player::initVariables()
{
	this->speed = 5.f;
	this->hpMax = 10;
	this->hp = this->hpMax;

}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}



Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);
	this->initVariables();
	this->initShape();
}

Player::~Player()
{
}

const sf::RectangleShape Player::getShape() const
{
	return this->shape;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;

	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
		this->hp += health;
}

void Player::update(sf::RenderTarget* target)
{

	// According to keyboard Input player is updated.
	this->updateInput();
	// Windows bounds collision.
	this->updateWindowBoundsCollision(target);

}

void Player::updateInput()
{
	/*
		KeyboradInput
	*/

	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->shape.move(-this->speed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->shape.move(this->speed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->shape.move( 0.f, -this->speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->shape.move( 0.f, this->speed);
	}
}

void Player::updateWindowBoundsCollision(sf::RenderTarget* target)
{
	sf::FloatRect playerBounds = this->shape.getGlobalBounds();

	float x = playerBounds.left, y = playerBounds.top;
	//Left
	if (playerBounds.left <= 0.f)
	{
		x = 0.f;
	}
	if (playerBounds.left + playerBounds.width >= target->getSize().x)
	{
		x = target->getSize().x - playerBounds.width;
	}
	if (playerBounds.top <= 0.f) {
		y = 0.f;
	}
	if (playerBounds.height + playerBounds.top >= target->getSize().y) {
		y = target->getSize().y - playerBounds.height;
	}
	this->shape.setPosition(x, y);

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

