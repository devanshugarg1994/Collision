#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

enum BallType {DEFAULT =0, DAMAGING, HEALING, NROFTYPE};
class Ball
{
private:
	sf::CircleShape shape;
	unsigned int balltimer;
	int type;
	void initShape(const sf::RenderTarget* target);

public:
	static const unsigned int time = 250;

	Ball(const sf::RenderTarget * target, int type);
	virtual ~Ball();
	const sf::CircleShape getShape() const;
	const int& getType() const;
	const unsigned int getBallTimer() const;
	void setBallPosition(const sf::RenderTarget* target);

	void updateBallTimer();
	void update();
	void render(sf::RenderTarget* target);

};

