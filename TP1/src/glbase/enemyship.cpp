#include "enemyship.h"

const int SIZE = 50; //Taille en pourcentage
const int NBSLICES = 8; //Nombre de slices pour les cylindres.

//BODY
glm::vec4 mainBodyEnemyColor = vec4(1.0f, 0, 0, 0.5f);
float mainBodyEnemyRadius = 2 * (SIZE/100.0f);

//BACK CONNECTORS AND MOTORS
glm::vec4 backConnectorColor = vec4(1.0f, 1, 0, 0.5f);
glm::vec4 mainBackMotorsConnectorColor = vec4(1.0f, 0, 1, 0.5f);
glm::vec4 motorsColor = vec4(1.0f, 0, 0, 0.5f);

float mainBackConnectorHeight = mainBodyEnemyRadius;
float mainBackConnectorRadius = mainBodyEnemyRadius/5; //ok
glm::mat4 mainBackConnectorMatrix = glm::translate(glm::mat4(),vec3(0,0,mainBodyEnemyRadius+mainBackConnectorHeight/2)) * glm::rotate(glm::mat4(), glm::pi<float>()/2, vec3(1,0,0));

float mainBackMotorRadius = mainBodyEnemyRadius/5; //ok
glm::mat4 mainBackMotorConnectorMatrix = glm::translate(glm::mat4(),vec3(0,0,mainBodyEnemyRadius+mainBackConnectorHeight+mainBackMotorRadius/2));

float backConnectorHeight = mainBodyEnemyRadius*3/2;
float backConnectorRadius = mainBodyEnemyRadius/5; //ok
glm::mat4 firstBackConnectorMatrix = glm::translate(glm::mat4(),vec3(-(backConnectorHeight/2),0,0)) * glm::translate(glm::mat4(),vec3(0,0,(mainBodyEnemyRadius+mainBackConnectorHeight+mainBackMotorRadius/2))) * glm::rotate(glm::mat4(), glm::pi<float>()/2, vec3(0,0,1));
glm::mat4 secondBackConnectorMatrix = glm::translate(glm::mat4(),vec3(backConnectorHeight/2,0,0)) * glm::translate(glm::mat4(),vec3(0,0,(mainBodyEnemyRadius+mainBackConnectorHeight+mainBackMotorRadius/2))) * glm::rotate(glm::mat4(), glm::pi<float>()/2, vec3(0,0,1));

float motorsHeight = mainBodyEnemyRadius/5*4;
float motorsRadius = mainBodyEnemyRadius/3;
glm::mat4 firstMotorMatrix = glm::translate(glm::mat4(),vec3(-backConnectorHeight,0,0)) * glm::translate(glm::mat4(),vec3(0,0,mainBodyEnemyRadius+mainBackConnectorHeight+mainBackMotorRadius/2)) * glm::rotate(glm::mat4(), glm::pi<float>()/2, vec3(1,0,0));
glm::mat4 secondMotorMatrix = glm::translate(glm::mat4(),vec3(backConnectorHeight,0,0)) * glm::translate(glm::mat4(),vec3(0,0,mainBodyEnemyRadius+mainBackConnectorHeight+mainBackMotorRadius/2)) * glm::rotate(glm::mat4(), glm::pi<float>()/2, vec3(1,0,0));

//MAIN CANON
glm::vec4 mainCanonEnemyColor = vec4(0, 1.0f, 0, 1.0f);
float mainCanonEnemyHeight  = 1 * (SIZE/100.0f);
float mainCanonEnemyRadius = 0.5f * (SIZE/100.0f);
glm::mat4 mainCanonMatrix = glm::translate(glm::rotate(glm::mat4(), glm::pi<float>()/2, vec3(1,0,0)), vec3(0,-(mainCanonEnemyHeight/2+mainBodyEnemyRadius),0));

//CONNECTORS
glm::vec4 connectorEnemyColor = vec4(1.0f,0,0,1.0f);
float frontConnectorHeight  = 10 * (SIZE/100.0f);
float frontConnectorRadius = 0.5f * (SIZE/100.0f);
glm::mat4 leftFrontConnectorMatrix = glm::translate(glm::rotate(glm::mat4(), -glm::pi<float>()/3, vec3(0,0,1)), vec3(0, -(frontConnectorHeight/2 + mainBodyEnemyRadius), 0));
glm::mat4 rightFrontConnectorMatrix = glm::translate(glm::rotate(glm::mat4(), glm::pi<float>()/3, vec3(0,0,1)), vec3(0, -(frontConnectorHeight/2 + mainBodyEnemyRadius), 0));

//EXTREMES CANONS
glm::vec4 extremCanonColor = vec4(1.0f, 0, 0, 1.0f);
float extremCanonHeight = 3 * (SIZE/100.0f);
float extremCanonRadius = 0.5f * (SIZE/100.0f);
glm::mat4 leftLeftCanonMatrix = glm::translate(glm::rotate(glm::rotate(glm::mat4(), -glm::pi<float>()/6, vec3(0,0,1)), glm::pi<float>()/2, vec3(1,0,0)), vec3(mainBodyEnemyRadius+frontConnectorHeight, 0, 0));
glm::mat4 rightRightCanonMatrix = glm::translate(glm::rotate(glm::rotate(glm::mat4(), glm::pi<float>()/6, vec3(0,0,1)), glm::pi<float>()/2, vec3(1,0,0)), vec3(-(mainBodyEnemyRadius+frontConnectorHeight), 0, 0));

//SUPPORTS
glm::vec4 canonSupportColor = vec4(0, 0, 1.0f, 1.0f);
float canonSupportHeight  = 2 * (SIZE/100.0f);
float canonSupportWidth  = 1 * (SIZE/100.0f);
float canonSupportDepth  = 2 * (SIZE/100.0f);
float alpha = asin((frontConnectorRadius+canonSupportWidth/2)/mainBodyEnemyRadius);
glm::mat4 supportLeftMatrix = glm::rotate(glm::mat4(), glm::pi<float>()/3 -alpha, vec3(0,0,1)) * glm::translate(glm::mat4(), vec3(-(frontConnectorHeight/2 + mainBodyEnemyRadius),0, 0)) * glm::rotate(glm::mat4(), glm::pi<float>()/2, glm::vec3(0,0,1)) * glm::scale(glm::mat4(), glm::vec3(canonSupportWidth,canonSupportHeight,canonSupportDepth));
glm::mat4 supportRightMatrix = glm::rotate(glm::mat4(), -(glm::pi<float>()/3 -alpha), vec3(0,0,1)) * glm::translate(glm::mat4(), vec3((frontConnectorHeight/2 + mainBodyEnemyRadius),0, 0)) * glm::rotate(glm::mat4(), glm::pi<float>()/2, glm::vec3(0,0,1)) * glm::scale(glm::mat4(), glm::vec3(canonSupportWidth,canonSupportHeight,canonSupportDepth));

//MIDDLE CANONS
float middleCanonHeight = 3 * (SIZE/100.0f);
float middleCanonRadius = 0.5f * (SIZE/100.0f);
float alphabis = asin((frontConnectorRadius+canonSupportWidth/2)/mainBodyEnemyRadius);
glm::mat4 middleCanonLeftMatrix = glm::rotate(glm::mat4(), glm::pi<float>()/3 -alpha, vec3(0,0,1)) * glm::translate(glm::mat4(), vec3(-(frontConnectorHeight/2 + mainBodyEnemyRadius),0, 0)) * glm::rotate(glm::mat4(), glm::pi<float>()/2, glm::vec3(1,0,0));
glm::mat4 middleCanontRightMatrix = glm::rotate(glm::mat4(), -(glm::pi<float>()/3 -alpha), vec3(0,0,1)) * glm::translate(glm::mat4(), vec3((frontConnectorHeight/2 + mainBodyEnemyRadius),0, 0)) * glm::rotate(glm::mat4(), glm::pi<float>()/2, glm::vec3(1,0,0));


EnemyShip::EnemyShip() :

    mainBody(mainBodyEnemyColor, 4, 16, mainBodyEnemyRadius),

    mainBackConnector(connectorEnemyColor, NBSLICES, mainBackConnectorHeight, mainBackConnectorRadius, mainBackConnectorMatrix),
    mainBackMotorsConnector(canonSupportColor, 4, 16, mainBackMotorRadius,mainBackMotorConnectorMatrix),
    firstBackConnector(connectorEnemyColor, NBSLICES, backConnectorHeight, backConnectorRadius, firstBackConnectorMatrix),
    secondBackConnector(connectorEnemyColor, NBSLICES, backConnectorHeight, backConnectorRadius, secondBackConnectorMatrix),
    firstMotor(connectorEnemyColor, NBSLICES, motorsHeight, motorsRadius, firstMotorMatrix),
    secondMotor(connectorEnemyColor, NBSLICES, motorsHeight, motorsRadius, secondMotorMatrix),
    mainCanon(mainCanonEnemyColor, NBSLICES, mainCanonEnemyHeight, mainCanonEnemyRadius, mainCanonMatrix),
    leftFrontConnector(connectorEnemyColor, NBSLICES, frontConnectorHeight, frontConnectorRadius, leftFrontConnectorMatrix),
    rightFrontConnector(connectorEnemyColor, NBSLICES, frontConnectorHeight, frontConnectorRadius, rightFrontConnectorMatrix),
    supportLeft(canonSupportColor, supportLeftMatrix),
    supportRight(canonSupportColor, supportRightMatrix),
    leftCanon(connectorEnemyColor, NBSLICES, middleCanonHeight, middleCanonRadius, middleCanonLeftMatrix),
    rightCanon(connectorEnemyColor, NBSLICES, middleCanonHeight, middleCanonRadius, middleCanontRightMatrix),
    rightRightCanon(connectorEnemyColor, NBSLICES, extremCanonHeight, extremCanonRadius, rightRightCanonMatrix),
    leftLeftCanon(connectorEnemyColor, NBSLICES, extremCanonHeight, extremCanonRadius, leftLeftCanonMatrix),


    _angle(0),
    _zPosition(( rand()/(double)RAND_MAX ) * (150-100) + 100),
    _xPosition(( rand()/(double)RAND_MAX ) * (20-0) + 0 - 20)
{

mainBody.AddChild(&mainBackConnector);
mainBody.AddChild(&leftFrontConnector);
mainBody.AddChild(&rightFrontConnector);
mainBody.AddChild(&mainCanon);

mainBackConnector.AddChild(&mainBackMotorsConnector);
mainBackMotorsConnector.AddChild(&firstBackConnector);
mainBackMotorsConnector.AddChild(&secondBackConnector);
firstBackConnector.AddChild(&firstMotor);
secondBackConnector.AddChild(&secondMotor);

leftFrontConnector.AddChild(&supportLeft);
leftFrontConnector.AddChild(&leftLeftCanon);
rightFrontConnector.AddChild(&supportRight);
rightFrontConnector.AddChild(&rightRightCanon);
supportLeft.AddChild(&leftCanon);
supportRight.AddChild(&rightCanon);


_addShapeToList(&mainBody);
_addShapeToList(&firstBackConnector);

_addShapeToList(&secondBackConnector);


_defineBoundingBox();

_translateBoundingBox(_xPosition, 0, _zPosition);

}

EnemyShip::~EnemyShip()
{

}

void EnemyShip::render(double dt)
{
    goForward();
    animate();
//    _translateBoundingBox(0, 0, _zPosition);
    mainBody.Render();

    mainBackConnector.Render();
    mainBackMotorsConnector.Render();
    firstBackConnector.Render();
    secondBackConnector.Render();
    firstMotor.Render();
    secondMotor.Render();
    //front
    mainCanon.Render();
    leftFrontConnector.Render();
    rightFrontConnector.Render();
    supportLeft.Render();
    supportRight.Render();
    leftLeftCanon.Render();
    rightRightCanon.Render();
    leftCanon.Render();
    rightCanon.Render();


}
void EnemyShip::goForward(){
    if(_zPosition < -20) { alive=false; }
    _zPosition -= 0.1f;
    mainBody.SetTransform(glm::translate(glm::mat4(), vec3(_xPosition,0,_zPosition)));
}
void EnemyShip::animate(){
    if(_angle >= 2*glm::pi<float>()) _angle=0;
    else _angle += glm::pi<float>()/240;
    glm::mat4 connectorMotorMatrix = glm::rotate(glm::mat4(), _angle, vec3(0, 0, 1));
    mainBackMotorsConnector.SetTransform(connectorMotorMatrix);


}
std::vector<glm::vec3> EnemyShip::getPosition()
{
    std::vector<glm::vec3> theVector;

    theVector.push_back(vec3(0, 0, 0));
    theVector.push_back(vec3(1, 1, 1));
    theVector.push_back(vec3(2, 2, 2));
    theVector.push_back(vec3(3, 3, 3));

    return theVector;
}
void EnemyShip::destroyWithExplosion(){}
void EnemyShip::destroyWithoutExplosion(){}
