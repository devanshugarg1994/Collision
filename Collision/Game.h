#pragma once
#include<iostream>
#include<ctime>
#include<sstream>
#include "Player.h"
#include "Ball.h"



class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	int points;
	sf::Font font;
	sf::Text text;
	Player player;
	std::vector <Ball> balls;
	float spawnTimerMax;
	float spawnTimer;
	int maxBalls;

	// Function
	void initVariables();
	void initWindow();
	void initFont();
	void initText();
public:

	// constructor and Destructor
	Game();
	~Game();

	// Accessors

	// Modifiers

	// Function
	const bool running() const;
	void pollEvents();
	void spawnBalls();
	int ballType();
	Ball addBall();
	void checkCollision();
	void updateGUI();
	void update();
	void renderGUI(sf::RenderTarget *target);
	void render();
};

