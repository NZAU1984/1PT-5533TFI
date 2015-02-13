#pragma once
#include <main.h>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include "core.h"
#include "scene.h"
#include "spaceship.h"
#include "DummyEnemy.h"
#include "Projectile.h"
#include "enemyship.h"
#include "enemyshipbis.h"

class CoreTP1 : public Core
{
public:
	CoreTP1();
	virtual ~CoreTP1() override;

protected:
	virtual void Render(double dt) override;
	virtual void OnKeyW(bool down) override;
	virtual void OnKeyA(bool down) override;
	virtual void OnKeyS(bool down) override;
	virtual void OnKeyD(bool down) override;
	virtual void OnKeySPACE(bool down) override;
	virtual void OnKeyTAB(bool down) override;

protected:
	Spaceship spaceship;
	DummyEnemy dummyEnemy;
	Projectile projectile;

	std::list<std::unique_ptr<EnemyShip>> enemies;
	std::list<std::unique_ptr<EnemyShipBis>> enemiesBis;

	bool _invincibleMode = false;

	uint _nLives = 5;

	int _points = 0;

	double _delay = 2.5;

	double _timerStart = 0;

	bool _timerHasExpired = false;

	bool _dead = false;

	void _timerTick();

	void _hitPlayer();

	void _addEnemy1();

	void _addEnemy2();

	double _timerEnemy1 = 0;
	double _timerEnemy2 = 0;

	double _delayEnemy1 = 3;
	double _delayEnemy2 = 3;
};