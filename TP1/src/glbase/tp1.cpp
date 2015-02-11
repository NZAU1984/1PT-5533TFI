#include "tp1.h"

#include "glm/gtx/transform2.hpp"

#include <sstream>
#include <string>
#include <time.h>

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
	Core(),
	dummyEnemy(0, 0, 50, 0, 0, 0),
	projectile(0, 0, 0, 0, 0, 5)
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

	_timerTick();

	/*srand(time(NULL));

	uint randm = (rand() % 1001);

	_LOG_INFO() << randm;

	if (randm < 500)
	{
		_addEnemy1();
	}
	else
	{
		_addEnemy2();
	}*/
}

void CoreTP1::Render(double dt)
{
	spaceship.render(dt);
//	dummyEnemy.render(dt);
//	projectile.render(dt);

	_timerHasExpired = (glfwGetTime() > (_timerStart + _delay));

	if (_dead)
	{
		DrawText("YOU DIED :(", glm::vec2(0.5f, 0.5f), glm::vec4(1, 0, 0, 1), 32, ALIGN_CENTER);

		_invincibleMode = false;
	}
	else
	{
		if (_invincibleMode)
		{
			DrawText("INVINCIBLE MODE", glm::vec2(0.5f, 0.0f), glm::vec4(1, 0, 0, 1), 32, ALIGN_CENTER);
		}
		else if (_timerHasExpired)
		{
			// check with every enemy. ONE positive collision = do stuff AND return to exit function to avoid checking
			// any other collision !
			
			// BEGIN loop : enemies
			// change 'dummyEnemy' with iterator...
			if (spaceship.checkCollisionWith(dummyEnemy))
			{
				_hitPlayer();

				// remove all enemies
				// remove all player's projectiles
				// remove all enemies' projectiles

				// return; <= IMPORTANT !!
			}
				// BEGIN loop : player's projectiles
				/*
				if(dummyEnemy.checkCollisionWithProjectile(projectile))
				{
					dummyEnemy.kill(); // whatever...

					// give points to player...
				}
				*/
				// END loop : player's projectiles
			// END loop : enemies

			// BEGIN loop : enemies' projectiles
			/*
			if(spaceship.checkCollisionWithProjectile(projectile))
			{
				_hitPlayer();

				// remove all enemies
				// remove all player's projectiles
				// remove all enemies' projectiles

				// return; <= IMPORTANT
			}

			*/
			// END loop : enemies' projectiles

		}
		else
		{
			DrawText("GET READY!", glm::vec2(0.5f, 0.5f), glm::vec4(1, 0, 0, 1), 32, ALIGN_CENTER);
		}
	}

/*	bool coll = dummyEnemy.checkCollisionWithProjectile(projectile);

	if (coll)
	{
		_LOG_INFO() << "=== Projectile collision ===";
	}*/
	//_LOG_INFO() << rand() % 1001;
	/*if ((_timerEnemy1 + _delayEnemy1 < glfwGetTime()) && ((rand() % 1001) <= 10) && enemies.size() < 5)
	{
		_addEnemy1();
		//_LOG_INFO() << "added EnemyShip";
		//enemies.push_back(std::unique_ptr<EnemyShip>(new EnemyShip()));
	}
	else if ((_timerEnemy2 + _delayEnemy2 < glfwGetTime()) && ((rand() % 1001) <= 10) && enemiesBis.size() < 5)
	{
		_addEnemy2();
	}

	for (auto it = enemies.begin(), itEnd = enemies.end(); it != itEnd; ++it)
	{
		(*it)->render(dt);
	}

	for (auto it = enemiesBis.begin(), itEnd = enemiesBis.end(); it != itEnd; ++it)
	{
		(*it)->render(dt);
	}*/

	std::stringstream ss;
	std::stringstream ss1;

	ss << "LIVES: " << _nLives;
	ss1 << "POINTS: " << _points;

	DrawText((ss.str()).c_str(), glm::vec2(0.01f, 0.92f), glm::vec4(1, 0, 0, 1), 32, ALIGN_LEFT);
	DrawText((ss1.str()).c_str(), glm::vec2(0.99f, 0.92f), glm::vec4(1, 0, 0, 1), 32, ALIGN_RIGHT);
}

void CoreTP1::_addEnemy1()
{
	_LOG_INFO() << "added EnemyShip";
	enemies.push_back(std::unique_ptr<EnemyShip>(new EnemyShip()));

	_timerEnemy1 = glfwGetTime();
}

void CoreTP1::_addEnemy2()
{
	_LOG_INFO() << "added EnemyShipBis";
	//enemies.push_back(std::unique_ptr<EnemyShip>(new EnemyShip()));
	_timerEnemy2 = glfwGetTime();
}

CoreTP1::~CoreTP1()
{
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
	if (!_timerHasExpired || _dead)
	{
		return;
	}

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
	if (!_timerHasExpired || _dead)
	{
		return;
	}

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
	if (!_timerHasExpired || _dead)
	{
		return;
	}

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
	if (!_timerHasExpired || _dead)
	{
		return;
	}

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
		return;
	}

	if (_dead)
	{
		_dead   = false;
		_nLives = 5;
		_points = 0;
		_timerTick();
	}

	if (down)
	{
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


