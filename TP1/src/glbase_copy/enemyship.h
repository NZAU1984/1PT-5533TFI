#pragma once

#include <main.h>
#include <math.h>
#include "scene.h"
#include "ThreeDObject.h"
#include <vector>

class EnemyShip : public ThreeDObject
{
 public:
  EnemyShip();
  bool canShoot();
  void updateLastShot();

  void render(double dt);

  std::vector<glm::vec3> getPosition();

  void goForward(float zMove);
  void animate();

  void destroyWithExplosion();
  void destroyWithoutExplosion();

  bool isAlive(){return alive; }
  void setNotAlive() { alive = false; }
 protected:
  double _delay = 5.0; // 5s
  double _lastShot = 0;

  Sphere mainBody;
  //back
  Cylinder mainBackConnector;
  Sphere mainBackMotorsConnector;
  Cylinder firstBackConnector;
  Cylinder secondBackConnector;
  Cylinder firstMotor;
  Cylinder secondMotor;
  //front
  Cylinder mainCanon;
  Cylinder leftFrontConnector;
  Cylinder rightFrontConnector;
  Box supportLeft;
  Box supportRight;
  Cylinder leftCanon;
  Cylinder rightCanon;
  Cylinder rightRightCanon;
  Cylinder leftLeftCanon;

  float _angle;
  float _zPosition;
  float _xPosition;
  bool alive= true;

  const double _minPositionZ = 0;
  const double _maxPositionZ = 75;

  const double _minPositionX = -15;
  const double _maxPositionX = 15;
};
