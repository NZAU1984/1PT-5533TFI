#pragma once

#include <main.h>

#include "scene.h"
#include "enemyship.h"
#include "ThreeDObject.h"

class EnemyShipBis : public ThreeDObject
{
 public:
  EnemyShipBis();

  void render(double dt);

  void goForward(float zMove);
  void animate();

  void destroyWithExplosion();
  void destroyWithoutExplosion();

  bool isAlive() { return alive;}
  void setNotAlive() { alive = false; }

 protected:
  Box cockpit;
  Box window;
  Box wingLeft, wingRight;
  Box firstLeftSupport, secondLeftSupport, firstRightSupport, secondRightSupport;
  Cylinder firstLeftCanon, secondLeftCanon, firstRightCanon, secondRightCanon;

  float _angle;
  float _zPosition;
  float _xPosition;

  bool alive = true;

  double _minPositionZ = 0;
  const double _maxPositionZ = 75;

  const double _minPositionX = -15;
  const double _maxPositionX = 15;
};
