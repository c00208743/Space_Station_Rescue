#include "Player.h"
#include <iostream>
#include "math.h"

#define M_PI   3.14159265358979323846264338327950288

Player::Player() :
	m_position(300, 300),
	m_velocity(0, 0),
	size(50),
	speed(0)
{

	if (!m_texture.loadFromFile("assets/player/body_02.png"))
	{
		// error...
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(64, 32);
	m_sprite.setPosition(m_position);

	if (!m_font.loadFromFile("ALBA.TTF")) {
		//error
	}
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(30);
	m_text.setString("Shield: Not Ready");

	m_textScore.setFont(m_font);
	m_textScore.setFillColor(sf::Color::White);
	m_textScore.setCharacterSize(30);
	m_textScore.setString("Score: ");

	scoreNu.setFont(m_font);
	scoreNu.setFillColor(sf::Color::White);
	scoreNu.setCharacterSize(30);
	scoreNu.setString("");

	m_gameOver.setFont(m_font);
	m_gameOver.setFillColor(sf::Color::Red);
	m_gameOver.setCharacterSize(30);
	m_gameOver.setString("Game Over!");

	m_health.setFont(m_font);
	m_health.setFillColor(sf::Color::White);
	m_health.setCharacterSize(30);
	m_health.setString("Health : ");

	if (!m_textureShield.loadFromFile("assets/rotating_shield/shieldAnim.png"))
	{
		// error...
	}
	;
	m_spriteShield.setTexture(m_textureShield);
	m_spriteShield.setOrigin(160, 160);
	m_spriteShield.setPosition(m_position);
	m_spriteShield.setTextureRect(sf::IntRect(0, 0, 320, 320));

	previousTile = sf::Vector2i(m_sprite.getPosition().x / 32, m_sprite.getPosition().y / 32);

	m_bullet = new Bullet(true);

}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
Player::~Player()
{
}

void Player::update(double dt, Level * cLevel)
{
	if (health > 0) {

		//increase velocity
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (speed < 3)
			{
				speed = speed + 0.02;
			}
		}
		else
		{
			if (speed > 0)
			{
				speed = speed - 0.02;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (speed > -3)
			{
				speed = speed - 0.02;
			}
		}
		else
		{
			if (speed < 0)
			{
				speed = speed + 0.02;
			}
		}
		//change rotation 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_sprite.rotate(-1.0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_sprite.rotate(1.0);
		}

		float radians = m_sprite.getRotation()* M_PI / 180;
		direction.x = (cos(radians));
		direction.y = (sin(radians));
		m_sprite.setPosition(m_sprite.getPosition().x + (direction.x * speed), m_sprite.getPosition().y + (direction.y * speed));


		//fire bullet
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			health = 100000;
		}
		

		//fire bullet
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_bullet->fire(direction, m_sprite.getPosition(), m_sprite.getRotation());
		}
		m_bullet->update();


		//shield
		m_spriteShield.setPosition(m_sprite.getPosition());
		m_spriteShield.setRotation(m_sprite.getRotation());
		m_text.setPosition(m_sprite.getPosition().x - 900, m_sprite.getPosition().y + 900);
		m_textScore.setPosition(m_sprite.getPosition().x - 900, m_sprite.getPosition().y - 900);
		scoreNu.setPosition(m_sprite.getPosition().x - 800, m_sprite.getPosition().y - 900);
		m_gameOver.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);
		m_health.setPosition(m_sprite.getPosition().x - 900, m_sprite.getPosition().y - 860);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && shieldReady == true)
		{
			shield = true;
			shieldTimer++;
		}
		else {
			shield = false;
		}

		if (shield) {
			timer++;
			if (timer % 10 == 0)
			{
				animate++;
			}
			//animate++;
			m_spriteShield.setTextureRect(sf::IntRect(320 * animate, 0, 320, 320));
			if (animate > 11) {
				animate = 0;
			}
		}

		shieldCoolDown++;
		if (shieldCoolDown > 1000) {
			shieldReady = true;
			m_text.setString("Shield : READY!!!");

		}
		if (shieldTimer > 1000) {
			shieldReady = false;
			m_text.setString("Shield : Not Ready");
			shieldCoolDown = 0;
			shieldTimer = 0;
		}



		currentTile(cLevel);
	}
}

void Player::hit(int d)
{
		health -= d;
}

void Player::render(sf::RenderWindow & window)
{
	m_bullet->render(window);
	window.draw(m_text);
	window.draw(m_textScore);
	window.draw(scoreNu);

	if (health > 0) {
		window.draw(m_sprite);
		window.draw(m_health);
	}
	else {
		window.draw(m_gameOver);
	}
	
	if (shield) {
		window.draw(m_spriteShield);
	}

	
}


sf::Vector2f Player::getPosition()
{
	return m_sprite.getPosition();
}

sf::Vector2f Player::getVelocity()
{
	direction.x * speed;
	direction.y * speed;
	return direction;
}

bool Player::checkBulletCollision(sf::Vector2f pos, int width, int height)
{
	return m_bullet->checkCollision(pos, width, height);
}

bool Player::checkWorkerCollision(sf::Vector2f pos, int width, int height, bool alive)
{
	//box collsion formula 
	if (alive == false) {
		if (m_sprite.getPosition().x < pos.x + width
			&& m_sprite.getPosition().x + 128> pos.x
			&&  m_sprite.getPosition().y + 64 > pos.y
			&&  m_sprite.getPosition().y < pos.y + height)
		{
			collison = true;
			score = score + 10;
			//std::cout << score << std::endl;
			std::string s = std::to_string(score);
			scoreNu.setString(s);
		}
		else {
			collison = false;
		}
	}
		
	
	return collison;
}

void Player::setScore(int enemyS) {
	score += enemyS;
	std::string s = std::to_string(score);
	scoreNu.setString(s);
}

void Player::setHealth(int dam) {
	if (shield == false) {
		health = health - dam;
		std::string s = std::to_string(health);
		m_health.setString("Health : "+ s);
	}
	
}

void Player::currentTile(Level * cLevel)
{
	// Get the square in front
	float posX = m_sprite.getPosition().x + 64;
	float posXB = m_sprite.getPosition().x - 64;
	float posY = m_sprite.getPosition().y;

	sf::Vector2f tileAhead = rotate(sf::Vector2f(posX, posY), m_sprite.getPosition(), m_sprite.getRotation());
	sf::Vector2f tileBehind = rotate(sf::Vector2f(posXB, posY), m_sprite.getPosition(), m_sprite.getRotation());

	int x = floor(tileAhead.x / 32);
	int y = floor(tileAhead.y / 32);

	int xb = floor(tileBehind.x / 32);
	int yb = floor(tileBehind.y / 32);

	if (cLevel->collide(sf::Vector2i(x, y)) || cLevel->collide(sf::Vector2i(xb, yb)))
	{
		speed = 0;
	}

	int gridPosX = m_sprite.getPosition().x / 32;
	int gridPosY = m_sprite.getPosition().y / 32;

	if (previousTile.x != gridPosX || previousTile.y != gridPosY)
	{
		previousTile = sf::Vector2i(m_sprite.getPosition().x / 32, m_sprite.getPosition().y / 32);
		cLevel->updateWeights(previousTile);
	}

	m_bullet->checkWall(cLevel);
}

sf::Vector2f Player::rotate(sf::Vector2f P, sf::Vector2f O, float theta)
{
	sf::Transform rotTran;
	rotTran.rotate(theta, O.x, O.y);
	return rotTran.transformPoint(P);
}

int Player::joinFormation()
{
	numInForm.push_back(true);
	return numInForm.size() - 1;
}

void Player::leaveFormation(int i)
{
	numInForm.pop_back();
	freeFormPos.push_back(i);
}

int Player::getNumInForm()
{
	return numInForm.size();
}

int Player::getFreePosition()
{
	numInForm.push_back(true);
	int i = freeFormPos[freeFormPos.size() - 1];
	freeFormPos.pop_back();
	return i;
}