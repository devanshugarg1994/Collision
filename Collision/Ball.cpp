#include "Ball.h"

void Ball::initShape(const sf::RenderTarget* target)
{
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
	this->balltimer = rand() % 100;
	sf::Color color;
	switch (this->type)
	{
	case DEFAULT:
		color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		break;
	case DAMAGING:
		color = sf::Color::Red;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	case HEALING:
		color = sf::Color::Green;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;

	}
	this->shape.setFillColor(color);

	this->setBallPosition(target);

}

void Ball::setBallPosition(const sf::RenderTarget* target)
{
	this->shape.setPosition(
		static_cast<float>(rand() % target->getSize().x - this->shape.getGlobalBounds().width),
		static_cast<float>(rand() % target->getSize().y - this->shape.getGlobalBounds().height));
	// Checking if ball is not going out of window bounds
	if (this->shape.getPosition().x < 0 ||
		this->shape.getPosition().x + this->shape.getRadius() > target->getSize().x ||
		this->shape.getPosition().y < 0 ||
		this->shape.getPosition().y + this->shape.getRadius() > target->getSize().y) 
	{
		this->setBallPosition(target);
	}

}


Ball::Ball(const sf::RenderTarget* target, int type)
	:type(type)
{
	this->initShape(target);
}

Ball::~Ball()
{
}

const sf::CircleShape Ball::getShape() const
{
	return this->shape;
}

const int& Ball::getType() const
{
	return this->type;
}

const unsigned int Ball::getBallTimer() const
{
	return this->balltimer;
}



void Ball::updateBallTimer()
{
	this->balltimer++;
}

void Ball::update()
{
}

void Ball::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
