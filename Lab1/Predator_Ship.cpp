#include "Predator_Ship.h"

#define M_PI   3.14159265358979323846264338327950288

Predator_Ship::Predator_Ship() :
	m_position(5000, 5000),
	m_velocity(0, 0),
	m_maxSpeed(1.0f),
	m_maxRotation(20.0f),
	m_timeToTarget(100.0f),
	radius(200.0f),
	m_threshold(30.0f)
{


	if (!m_texture.loadFromFile("assets/predator_ship/body_01.png")) {
		//error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);

	m_sprite.setOrigin(32, 64);

	if (!m_textureExplosion.loadFromFile("assets/explosion/explosion1.png"))
	{
		// error...
	}

	m_spriteExplosion.setTexture(m_textureExplosion);
	m_spriteExplosion.setOrigin(160, 160);
	m_spriteExplosion.setPosition(m_position);
	m_timerCount = 0;

	m_wallCount = m_wallCountLimit;
	health = 0;

	// Missile
	m_missile = new Missile();
	m_missile->setSpeed(2.0f);

	// Bullet
	m_bullet = new Bullet(false);
	m_fireCooldownCounter = 0;
	m_fireBullet = true;

}


Predator_Ship::~Predator_Ship()
{

}

void Predator_Ship::spawn(sf::Vector2f pos)
{
	m_position = pos;
	health = 50;
	timer = 0;
	animate = 0;
	finishAnimate = false;
	
	m_sprite.setPosition(m_position);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);

	m_timerCount = 0;

	m_wallCount = m_wallCountLimit;
		
	m_fireCooldownCounter = 0;
	m_fireBullet = true;
}

void Predator_Ship::setPos(sf::Vector2f newPos)
{
	m_position = newPos;
}


float Predator_Ship::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}

void Predator_Ship::boundary(float x, float y)
{
	if (x > 6100)
	{
		m_position.x = -100;
	}
	if (x < -100)
	{
		m_position.x = 6100;
	}
	if (y < -100)
	{
		m_position.y = 6100;
	}
	if (y > 6100)
	{
		m_position.y = -100;
	}

}

float Predator_Ship::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;
}

void Predator_Ship::kinematicSeek(sf::Vector2f playerPosition)
{
	m_velocity = playerPosition - m_position;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * m_maxSpeed;
	m_velocity.y = m_velocity.y * m_maxSpeed;

	m_orientation = getNewOrientation(m_orientation, m_velocityF);
	m_orientation = m_orientation + 180;

}
void Predator_Ship::kinematicArrive(sf::Vector2f playerPosition)
{
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	m_velocity = playerPosition - m_position;

	if (m_velocityF >= 0)
	{
		m_velocity = m_velocity / m_timeToTarget;

		if (m_velocityF > m_maxSpeed) {

			//Normalize vector
			m_velocity.x = m_velocity.x / m_velocityF;
			m_velocity.y = m_velocity.y / m_velocityF;
			m_velocity = m_velocity * m_maxSpeed;

		}

		m_orientation = getNewOrientation(m_orientation, m_velocityF);
		m_orientation = m_orientation + 180;
	}

}


void Predator_Ship::collison(std::vector<Enemy*> enemies)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		n_direction = enemies[i]->getPosition() - m_position;
		n_distance = std::sqrt(n_direction.x*n_direction.x + n_direction.y* n_direction.y);

		if (n_distance <= radius)
		{
			float dot = (m_velocity.x * n_direction.x) + (m_velocity.y * n_direction.y);
			float det = (m_velocity.x * n_direction.y) - (m_velocity.y * n_direction.x);

			float angle = atan2(det, dot);
			angle = (180 / 3.14) * angle;


			if (angle >= -m_threshold && angle <= m_threshold)
			{
				crash = true;
				m_velocity = -m_velocity;
				m_orientation = -m_orientation;
				//std::cout << "Collided Arrive" << std::endl;

			}

		}
		if (crash == true && n_distance > radius)
		{
			crash = false;
		}
	}
}


sf::Vector2f Predator_Ship::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Predator_Ship::getVelocity()
{
	return m_velocity;
}


void Predator_Ship::update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies, Level * cLevel)
{
	//collison(enemies);
	if (crash == false)
	{
		int gridX = std::floor(m_position.x / 32);
		int gridY = std::floor(m_position.y / 32);
		if (cLevel->getWeight(sf::Vector2i(gridX, gridY)) != INT_MAX) // Current tile isn't max it
		{
			kinematicSeek(nextTile(cLevel));
		}
		else
		{
			if (m_timerCount >= m_timerCountLimit)
			{
				m_timerCount = 0;
				newTarget();
			}
			else
			{
				m_timerCount++;
			}

			kinematicSeek(target);
			checkWall(cLevel);
		}
		
	}

	if (health > 0) {
		m_position = m_position + m_velocity;

		m_missile->update(cLevel);
		if (m_missile->getStatus() == true)
		{
			m_missile->kinematicSeek(playerPosition);
		}

		m_bullet->update();

		m_bullet->checkWall(cLevel);
	}

	//m_position = m_position + m_velocity;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);

	if (m_bullet->checkCollision(playerPosition, 64, 128))
	{
		player->hit(10);
	}

	boundary(m_sprite.getPosition().x, m_sprite.getPosition().y);

	if (health <= 0) {
		timer++;
		if (timer % 10 == 0)
		{
			animate++;
		}
		//animate++;
		m_spriteExplosion.setTextureRect(sf::IntRect(310 * animate, 0, 320, 320));
		if (animate>15) {
			animate = 0;
			finishAnimate = true;
		}
	}
}

bool Predator_Ship::checkBulletCollision(sf::Vector2f pos, int width, int height)
{
	return m_bullet->checkCollision(pos, width, height);
}

sf::Vector2f Predator_Ship::nextTile(Level * cLevel)
{
	int gridPosX = std::floor(m_position.x / 32);
	int gridPosY = std::floor(m_position.y / 32);

	
 	std::vector<int> neighbourWeights;
	std::vector<sf::Vector2f> neighbourPos;

	neighbourWeights.push_back(cLevel->getWeight(sf::Vector2i(gridPosX, gridPosY - 1))); // Above
	neighbourPos.push_back(sf::Vector2f(gridPosX * 32 + 16, ((gridPosY - 1) * 32) + 16)); // Above
	neighbourWeights.push_back(cLevel->getWeight(sf::Vector2i(gridPosX, gridPosY + 1))); // Below
	neighbourPos.push_back(sf::Vector2f(gridPosX * 32 + 16, ((gridPosY + 1) * 32) + 16)); // Below
	neighbourWeights.push_back(cLevel->getWeight(sf::Vector2i(gridPosX - 1, gridPosY))); // Left
	neighbourPos.push_back(sf::Vector2f(((gridPosX - 1) * 32) + 16, gridPosY * 32 + 16)); // Left
	neighbourWeights.push_back(cLevel->getWeight(sf::Vector2i(gridPosX + 1, gridPosY))); // Right
	neighbourPos.push_back(sf::Vector2f(((gridPosX + 1) * 32) + 16 , gridPosY * 32 + 16)); // Right

	int smallest = INT_MAX;
	int smallestIndexPos = 0;
	for (int i = 0; i < neighbourWeights.size(); i++)
	{
		if (neighbourWeights[i] < smallest)
		{
			smallest = neighbourWeights[i];
			smallestIndexPos = i;
		}
	}

	//std::cout << "Weight: " << cLevel->getWeight(sf::Vector2i(gridPosX, gridPosY)) << std::endl;
	
	return neighbourPos[smallestIndexPos];

}

void Predator_Ship::render(sf::RenderWindow & window)
{
	if (health <= 0) {
		if (finishAnimate == false) {
			window.draw(m_spriteExplosion);
		}
	}
	else {
		window.draw(m_sprite);
		m_missile->render(window);
		m_bullet->render(window);
	}
}

int Predator_Ship::getWidth()
{
	return  128; 
}
int Predator_Ship::getHeight()
{
	return  256;
}

void Predator_Ship::kinematicWander(sf::Vector2f targetPosition)
{
	m_velocity = targetPosition - m_position;
	m_velocity = normalize(m_velocity);
	float orientation = getNewOrientation(m_sprite.getRotation(), length(m_velocity));
	orientation = orientation + m_maxRotation * ((rand() % 2) - 1);
	m_sprite.setRotation(orientation);
	m_velocity = sf::Vector2f(-sin(orientation), cos(orientation)) * m_maxSpeed;

}

void Predator_Ship::hit(int damage)
{
	//std::cout << health << std::endl;
	health = health - damage;
	m_explosion.x = m_position.x;
	m_explosion.y = m_position.y;
	m_spriteExplosion.setPosition(m_explosion);
}

int Predator_Ship::getHealth()
{
	return health;
}

bool Predator_Ship::radar(sf::Vector2f pos) {
	radarDistance = sqrt((pos.x - m_sprite.getPosition().x)*(pos.x - m_sprite.getPosition().x)
		+ (pos.y - m_sprite.getPosition().y)*(pos.y - m_sprite.getPosition().y));

	if (radarDistance < 750 && m_fireCooldownCounter > m_fireCooldownLimit && m_fireBullet)
	{
		//std::cout << "Bullet fired " << std::endl;
		float radians = (m_sprite.getRotation() - 90 )* M_PI / 180;
		sf::Vector2f direction;
		direction.x = (cos(radians));
		direction.y = (sin(radians));
		m_bullet->fire(direction, m_sprite.getPosition(), m_sprite.getRotation());
		m_fireCooldownCounter = 0; 
		m_fireBullet = false;
		return true;
	}
	else if (radarDistance < 750 && !m_missile->getStatus() && m_fireCooldownCounter > m_fireCooldownLimit && !m_fireBullet) {
		//std::cout << "Missile fired " << std::endl;
		m_missile->fire(m_sprite.getPosition());
		m_fireCooldownCounter = 0;
		m_fireBullet = true;
		return true;
	}
	else {
		//std::cout << "not in range " << std::endl;
		m_fireCooldownCounter++;
		return false;
	}


}
bool Predator_Ship::workerRadar(sf::Vector2f pos) {
	return 0;
}
int Predator_Ship::getId()
{
	return 2;
}
int Predator_Ship::getScore()
{
	return 0;
}
void Predator_Ship::setScore()
{
	//do nothing 
}
bool Predator_Ship::checkWorkerCollision(sf::Vector2f pos, int width, int height, bool alive)
{
	//do nothing
	return 0;
}
int Predator_Ship::getDamageToPlayer()
{
	//how much damage has been inflicted to the player
	return m_missile->damagedPlayer();
}

float Predator_Ship::length(sf::Vector2f vel)
{
	return (sqrt((vel.x * vel.x) + (vel.y * vel.y)));
}

sf::Vector2f Predator_Ship::normalize(sf::Vector2f vel)
{
	if (length(vel) != 0)
		return sf::Vector2f(vel.x / length(vel), vel.y / length(vel));
	else
		return vel;
}

void Predator_Ship::checkWall(Level * cLevel)
{
	// Get the square in front
	float posX = m_position.x + 64;
	float posY = m_position.y;

	sf::Vector2f tileAhead = rotate(sf::Vector2f(posX, posY), m_sprite.getPosition(), m_sprite.getRotation());

	int x = floor(tileAhead.x / 32);
	int y = floor(tileAhead.y / 32);
	if (m_wallCount > m_wallCountLimit)
	{
		if (cLevel->collide(sf::Vector2i(x, y)))
		{
			//std::cout << "Wall" << std::endl;
			target.x = -target.x;
			target.y = -target.y;
			m_wallCount = 0;
		}
	}
	else
	{
		m_wallCount++;
	}
}


void Predator_Ship::newTarget()
{
	target = sf::Vector2f(rand() % 6000, rand() % 6000);
}

sf::Vector2f Predator_Ship::rotate(sf::Vector2f P, sf::Vector2f O, float theta)
{
	sf::Transform rotTran;
	rotTran.rotate(theta, O.x, O.y);
	return rotTran.transformPoint(P);
}