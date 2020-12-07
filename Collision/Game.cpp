#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxBalls = 10;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(1280, 720);
	this->window = new sf::RenderWindow(this->videoMode, "Collision", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/Dosis_Light.ttf")) {
		std::cout << "ERROR!::GAME::INITFONTS:: FONT IS NOT LOADED" << std::endl;
	}
}

void Game::initText()
{
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(30);
	this->text.setString("test");
}

// constructor and Destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}


const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while ((this->window->pollEvent(this->sfmlEvent)))
	{
		switch (this->sfmlEvent.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape) 
				this->window->close();
			break;

		}

	}
}

void Game::spawnBalls()
{
	// Timer
	if (this->spawnTimer < this->spawnTimerMax) {
		this->spawnTimer += 1.f;
	} else{
		if (this->balls.size() < this->maxBalls) {
			// Here we are calling constructor directly without suing new
			// which create a object on stack memory and call constructor
			this->balls.push_back(Ball(this->window, this->ballType()));
		}
	}
}

int Game::ballType()
{
	const int randValue = rand() % 100 + 1;
	int type;
	if (randValue > 60 && randValue < 80) {
		return type = BallType::DAMAGING;
	}
	else if (randValue > 80 && randValue < 100) {
		return type = BallType::HEALING;
	}

	return (type = BallType::DEFAULT);
}

Ball Game::addBall()
{
	const Ball ball = Ball(this->window, rand() % BallType::NROFTYPE);

	for (size_t i = 0; i < this->balls.size() - 1; i++) {
		for (size_t y = i + 1; y < this->balls.size(); y++) {
			ball.getShape().getGlobalBounds().contains(balls[i].getShape().getPosition());
			this->addBall();
		}
	}

	return ball;
}



void Game::checkCollision()
{
	for (size_t i = 0; i < this->balls.size(); i++) {
		if (this->player.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds())) {
			
			switch (this->balls[i].getType())
			{
			case BallType::DEFAULT :
				this->points++;
				break;
			case BallType::DAMAGING:
				this->player.takeDamage(1);
				break;

			case BallType::HEALING:
				this->player.gainHealth(1);
				break;
			}
			this->balls.erase(this->balls.begin() + i);
		}else {
			this->balls[i].updateBallTimer();
			const int ref = this->balls[i].getBallTimer();
			std::cout << ref << std::endl;
			if (this->balls[i].getBallTimer() > Ball::time) {
				this->balls.erase(this->balls.begin() + i);
			}

		}
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << this->points << std::endl << "HP: " << this->player.getHp() << " / " << this->player.getHpMax();
	this->text.setString(ss.str());
}

// Function
void Game::update()
{
	// The order in which we check the collision and update the collider is important 
	this->pollEvents();
	this->spawnBalls();
	this->player.update(this->window);
	this->checkCollision();
	this->updateGUI();
}

void Game::renderGUI(sf::RenderTarget* target)
{
	target->draw(this->text);
}



void Game::render()
{
	this->window->clear();

	this->player.render(this->window);

	for (auto& ball : this->balls) {
		ball.render(this->window);
	}

	this->renderGUI(this->window);
	this->window->display();
}
