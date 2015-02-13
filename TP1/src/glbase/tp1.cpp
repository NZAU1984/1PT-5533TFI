#include "tp1.h"

#include "glm/gtx/transform2.hpp"

#include <sstream>
#include <string>

std::string printVec3(glm::vec3 vec)
{
	std::stringstream ss;
	ss << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";

	return ss.str();
}

/*
 * 'CoreTP1' is a super class of 'Core' (CoreTP1 extends Core)
 *
 * Initialization, between 'CoreTP1::CoreTP1() :' and '{'
 *     - Calling the base class constructor (calling 'Core' constructor)
 *     - Initializing protected member 'b' (of type Box) with a new 'vec4'
 *     - Initializing protected member 'b2' (of type Box) with a new 'vec4'
 *     - Initializing protecter member 'f' (of type float) with '0'
 *
 * 'Box' class defined in 'scene' (.h/.ccp)
 * 'vec4' is part of GLM
 */
CoreTP1::CoreTP1() :
    Core()
{
	/* '_viewMatrix' defined in 'core.h' with type 'glm::mat4'
	 * It is a protected property of 'Core' (the superclass of the current class)
	 *
	 * More info about 'glm::lookAt' @ http://stackoverflow.com/questions/21830340/understanding-glmlookat
	 * Arguments are "eye", "center", "up"
	 *
	 * +x is pointing towards left
	 * +y is pointing towards top
	 * +z is pointing towards background
	 * */
	// default = 0, 3, -6 ... 0,0,0 .. 0,1,0
	_viewMatrix = glm::lookAt(glm::vec3(0, 45, -25), glm::vec3(0, 0, 20), glm::vec3(0, 1, 0));
}

void CoreTP1::Render(double dt)
{
	spaceship.render(dt);

	//Popper éventuellement un nouvel ennemi
	if (((rand() / (double)RAND_MAX) * (1000 - 0) + 0) <= 5 && enemies.size() < 5)
	{
		enemies.push_back(std::unique_ptr<EnemyShip>(new EnemyShip()));
	}

	if (((rand() / (double)RAND_MAX) * (1000 - 0) + 0) <= 5 && enemiesBis.size() < 5)
	{
		enemiesBis.push_back(std::unique_ptr<EnemyShipBis>(new EnemyShipBis()));
	}

	{
		auto enemyIterator = enemies.begin();

		while (enemyIterator != enemies.end())
		{
			/* Checking for killed enemies. */
			if (!(*enemyIterator)->isAlive())
			{
				_LOG_INFO() << "DESTROY EnemyShip";

				enemyIterator = enemies.erase(enemyIterator);

				continue;
			}

			if ((*enemyIterator)->checkCollisionWith(spaceship))
			{
				_LOG_INFO() << "DEAD: YOU WERE HIT BY 'EnemyShip'.";

				return;
			}

			/* Not dead: render. */
			(*enemyIterator)->render(dt);

			if ((*enemyIterator)->canShoot())
			{
				std::vector<glm::vec3> listTmp = (*enemyIterator)->getPosition();

				for (std::vector<glm::vec3>::iterator itbis = listTmp.begin(); itbis != listTmp.end(); ++itbis)
				{
					enemyProjectiles.push_back(std::unique_ptr<Projectile>(
						new Projectile((*itbis).x, (*itbis).y, (*itbis).z, 0, 0, -12)));
				}
			}

			auto playersProjectileIterator = playersProjectiles.begin();

			while (playersProjectileIterator != playersProjectiles.end())
			{
				if ((*enemyIterator)->checkCollisionWithProjectile((*playersProjectileIterator)->getPosition()))
				{
					_LOG_INFO() << "YOU KILLED 'EnemyShip'.";

					enemyIterator = enemies.erase(enemyIterator);

					goto END_OF_LOOP;
				}

				//(*playersProjectileIterator)->render(dt);

				++playersProjectileIterator;
			}

			++enemyIterator;

		END_OF_LOOP:;
		}
	}

	{
		auto enemyIterator = enemiesBis.begin();

		while (enemyIterator != enemiesBis.end())
		{
			/* Checking for killed enemies. */
			if (!(*enemyIterator)->isAlive())
			{
				_LOG_INFO() << "DESTROY EnemyShip";

				enemyIterator = enemiesBis.erase(enemyIterator);

				continue;
			}

			if ((*enemyIterator)->checkCollisionWith(spaceship))
			{
				_LOG_INFO() << "DEAD: YOU WERE HIT BY 'EnemyShip'.";

				return;
			}

			/* Not dead: render. */
			(*enemyIterator)->render(dt);

			if ((*enemyIterator)->canShoot())
			{
				std::vector<glm::vec3> listTmp = (*enemyIterator)->getPosition();

				for (std::vector<glm::vec3>::iterator itbis = listTmp.begin(); itbis != listTmp.end(); ++itbis)
				{
					enemyProjectiles.push_back(std::unique_ptr<Projectile>(
						new Projectile((*itbis).x, (*itbis).y, (*itbis).z, 0, 0, -12)));
				}
			}

			auto playersProjectileIterator = playersProjectiles.begin();

			while (playersProjectileIterator != playersProjectiles.end())
			{
				if ((*enemyIterator)->checkCollisionWithProjectile((*playersProjectileIterator)->getPosition()))
				{
					_LOG_INFO() << "YOU KILLED 'EnemyShipBis'.";

					enemyIterator = enemiesBis.erase(enemyIterator);

					goto END_OF_LOOP1;
				}

				//(*playersProjectileIterator)->render(dt);

				++playersProjectileIterator;
			}

			++enemyIterator;

		END_OF_LOOP1:;
		}
	}

		auto it2 = enemyProjectiles.begin();

		while(it2 != enemyProjectiles.end())
		{
			if ((*it2)->isOutsideScreen())
			{
				it2 = enemyProjectiles.erase(it2);

				continue;
			}

			(*it2)->render(dt);

			if (spaceship.checkCollisionWithProjectile((*it2)->getPosition()))
			{
				_LOG_INFO() << "DEAD BY PROJECTILE!";

				return;
			}

			++it2;
		}

		auto it3 = playersProjectiles.begin();

		while (it3 != playersProjectiles.end())
		{
			if ((*it3)->isOutsideScreen())
			{
				it3 = playersProjectiles.erase(it3);

				continue;
			}

			(*it3)->render(dt);

			++it3;
		}
}

CoreTP1::~CoreTP1()
{
}

void CoreTP1::_shootProjectile()
{
	glm::vec3 spaceshipPosition = spaceship.getPosition();

	playersProjectiles.push_back(std::unique_ptr<Projectile>(
		new Projectile(spaceshipPosition.x, spaceshipPosition.y, spaceshipPosition.z, 0, 0, 16)));
}

void CoreTP1::_timerTick()
{
	_timerStart = glfwGetTime();
}

void CoreTP1::_hitPlayer()
{
	--_nLives;

	DrawText("BANG!", glm::vec2(0.5f, 0.5f), glm::vec4(1, 0, 0, 1), 32, ALIGN_CENTER);

	if (_nLives == 0)
	{
		_dead = true;
	}

	spaceship.resetPosition();

	_timerTick();
}

void CoreTP1::OnKeyW(bool down)
{
	if (down)
	{
		spaceship.goForward();
	}
	else
	{
		spaceship.stopGoingForward();
	}
}

void CoreTP1::OnKeyA(bool down)
{
	if (down)
	{
		spaceship.goLeft();
	}
	else
	{
		spaceship.stopGoingLeft();
	}
}

void CoreTP1::OnKeyS(bool down)
{
	if (down)
	{
		spaceship.goBackward();
	}
	else
	{
		spaceship.stopGoingBackward();
	}
}

void CoreTP1::OnKeyD(bool down)
{
	if (down)
	{
		spaceship.goRight();
	}
	else
	{
		spaceship.stopGoingRight();
	}
}

void CoreTP1::OnKeySPACE(bool down)
{
	if (!_timerHasExpired)
	{
		//return;
	}

	if (_dead)
	{
		_dead = false;
		_nLives = 5;
		_points = 0;
		_timerTick();
	}

	if (down)
	{
		_shootProjectile();

		_LOG_INFO() << "SPACE";
	}
}

void CoreTP1::OnKeyTAB(bool down)
{
	if (down)
	{
		_invincibleMode = !_invincibleMode;

		_LOG_INFO() << "TAB " << _invincibleMode;
	}
}