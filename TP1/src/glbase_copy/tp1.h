#pragma once
#include <main.h>
#include "core.h"
#include "scene.h"
#include "spaceship.h"
#include "DummyEnemy.h"
#include "Projectile.h"
#include "enemyship.h"
#include "enemyshipbis.h"
#include <list>
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

protected:
	Spaceship spaceship;
    std::list<std::unique_ptr<EnemyShip>> enemies;
    std::list<std::unique_ptr<EnemyShipBis>> enemiesBis;
    std::list<std::unique_ptr<Projectile>> listMissiles;
};
