#include "enemyshipbis.h"

const int SIZE = 200; //Taille en pourcentage
const int NBSLICES = 8; //Nombre de slices pour les cylindres.
//COCKPIT
glm::vec4 cockpitColor = glm::vec4(1.0f/256.0f*99.0f, 1.0f/256.0f*99.0f, 1.0f/256.0f*120.0f, 1.0f);
float cockpitWidth = 1.5f * (SIZE/100.0f);
float cockpitHeight = 1.5f * (SIZE/100.0f);
float cockpitDepth = 5.0f * (SIZE/100.0f);

glm::mat4 cockpitShear
{
    1,0,0,0,
    0,1,0,0,
    0,0.5f,1,0,
    0,0,0,1
};

glm::mat4 cockpitMatrix = glm::scale(glm::mat4(), vec3(cockpitWidth, cockpitHeight, cockpitDepth))*cockpitShear;

//WINDOW
glm::vec4 windowColor = glm::vec4(0,0,0.8f,0.8f);
float windowWidth = 1.0f * (SIZE/100.0f);
float windowHeight = 0.7f * (SIZE/100.0f);
float windowDepth = 0.5f * (SIZE/100.0f);
//TODO valeurs -3 et -4.8f en fonction du cockpit.. (et notamment du shearing)
glm::mat4 windowMatrix = glm::translate(glm::mat4(), vec3(0,-0.5f,-4.8f)) * glm::scale(glm::mat4(), vec3(windowWidth, windowHeight, windowDepth));


//WING LEFT
glm::mat4 wingLeftShear
{
    1,0,0,0,
    0,1,0,0,
    0.5f,0,1,0,
    0,0,0,1
};

glm::vec4 wingColor = glm::vec4(1.0f/256.0f*99.0f, 0, 0, 0.7f);
float wingWidth = 3.6f * (SIZE/100.0f);
float wingHeight = 0.5f * (SIZE/100.0f);
float wingDepth = 1.6f * (SIZE/100.0f);
//glm::scale(glm::mat4(), glm::vec3(wingWidth,wingHeight,wingDepth))
glm::mat4 wingLeftMatrix = glm::translate(glm::mat4(), vec3(-5.25f, 0.5f, 1.0f)) * glm::scale(glm::mat4(), glm::vec3(wingWidth,wingHeight,wingDepth)); //* wingLeftShear * glm::rotate(glm::mat4(), glm::pi<float>()/2, vec3(0,1,0));


//WING RIGHT
glm::mat4 wingRightShear
{
    1,0,0,0,
    0,1,0,0,
    0.5,0,1,0,
    0,0,0,1
};
glm::mat4 wingRightMatrix = glm::translate(glm::mat4(), vec3(5.25f, 0.5f, 1.0f)) * glm::scale(glm::mat4(), glm::vec3(wingWidth,wingHeight,wingDepth)); //* wingLeftShear * glm::rotate(glm::mat4(), glm::pi<float>()/2, vec3(0,1,0));

//CANON SUPPORTS
glm::vec4 supportColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

float supportWidth = 0.3f * (SIZE/100.0f);
float supportHeight = 0.125f * (SIZE/100.0f);
float supportDepth = 0.9f * (SIZE/100.0f);

glm::mat4 firstLeftSupportMatrix = glm::translate(glm::mat4(), vec3(-5, -0.0625f, 1.0f)) * glm::scale(glm::mat4(), glm::vec3(supportWidth,supportHeight,supportDepth));
glm::mat4 secondLeftSupportMatrix = glm::translate(glm::mat4(), vec3(-7, -0.0625f, 1.0f)) * glm::scale(glm::mat4(), glm::vec3(supportWidth,supportHeight,supportDepth));

glm::mat4 firstRightSupportMatrix = glm::translate(glm::mat4(), vec3(5, -0.0625f, 1.0f)) * glm::scale(glm::mat4(), glm::vec3(supportWidth,supportHeight,supportDepth));
glm::mat4 secondRightSupportMatrix = glm::translate(glm::mat4(), vec3(7, -0.0625f, 1.0f)) * glm::scale(glm::mat4(), glm::vec3(supportWidth,supportHeight,supportDepth));

//CANONS
glm::vec4 canonColor = glm::vec4(0,0,1.0f,1.0f);
float canonRadius = 0.15f * (SIZE/100.0f);
float canonLength = 2.0f * (SIZE/100.0f);
glm::mat4 firstLeftCanonMatrix = glm::translate(glm::rotate(glm::mat4(),glm::pi<float>()/2,vec3(1,0,0)), vec3(-5, 0, 0.40f));
glm::mat4 secondLeftCanonMatrix = glm::translate(glm::rotate(glm::mat4(),glm::pi<float>()/2,vec3(1,0,0)), vec3(-7, 0, 0.40f));

glm::mat4 firstRightCanonMatrix = glm::translate(glm::rotate(glm::mat4(),glm::pi<float>()/2,vec3(1,0,0)), vec3(5, 0, 0.40f));
glm::mat4 secondRightCanonMatrix = glm::translate(glm::rotate(glm::mat4(),glm::pi<float>()/2,vec3(1,0,0)), vec3(7, 0, 0.40f));

EnemyShipBis::EnemyShipBis() :
    cockpit(cockpitColor, cockpitMatrix),
    window(windowColor, windowMatrix),
    wingLeft(wingColor, wingLeftMatrix),
    wingRight(wingColor, wingRightMatrix),
    firstLeftSupport(supportColor, firstLeftSupportMatrix),
    secondLeftSupport(supportColor, secondLeftSupportMatrix),
    firstRightSupport(supportColor, firstRightSupportMatrix),
    secondRightSupport(supportColor, secondRightSupportMatrix),
    firstLeftCanon(canonColor, 8, canonLength, canonRadius, firstLeftCanonMatrix),
    secondLeftCanon(canonColor, 8, canonLength, canonRadius, secondLeftCanonMatrix),
    firstRightCanon(canonColor, 8, canonLength, canonRadius, firstRightCanonMatrix),
    secondRightCanon(canonColor, 8, canonLength, canonRadius, secondRightCanonMatrix),
    _angle(0),
    _zPosition(( rand()/(double)RAND_MAX ) * (150-100) + 100),
    _xPosition(( rand()/(double)RAND_MAX ) * (20-0) + 0 - 20)
{
    cockpit.AddChild(&window);
    cockpit.AddChild(&wingLeft);
    cockpit.AddChild(&wingRight);

    wingLeft.AddChild(&firstLeftSupport);
    wingLeft.AddChild(&secondLeftSupport);
    wingRight.AddChild(&firstRightSupport);
    wingRight.AddChild(&secondRightSupport);

    firstLeftSupport.AddChild(&firstLeftCanon);
    secondLeftSupport.AddChild(&secondLeftCanon);
    firstRightSupport.AddChild(&firstRightCanon);
    secondRightSupport.AddChild(&secondRightCanon);


    _addShapeToList(&cockpit);
    _addShapeToList(&window);
    _addShapeToList(&wingLeft);
    _addShapeToList(&wingRight);
    _addShapeToList(&firstLeftSupport);
    _addShapeToList(&secondLeftSupport);
    _addShapeToList(&firstRightSupport);
    _addShapeToList(&secondRightSupport);
    _addShapeToList(&firstLeftCanon);
    _addShapeToList(&secondLeftCanon);
    _addShapeToList(&firstRightCanon);
    _addShapeToList(&secondRightCanon);



    _defineBoundingBox();
    _translateBoundingBox(_xPosition, 0, _zPosition);
}

void EnemyShipBis::render(double dt)
{
    float zMove = -0.2f;
    animate();
    goForward(zMove);
    _translateBoundingBox(0, 0, zMove);
    cockpit.Render();
    window.Render();
    wingLeft.Render();
    wingRight.Render();
    firstLeftSupport.Render();
    secondLeftSupport.Render();
    firstRightSupport.Render();
    secondRightSupport.Render();
    firstLeftCanon.Render();
    secondLeftCanon.Render();
    firstRightCanon.Render();
    secondRightCanon.Render();


}

void EnemyShipBis::goForward(float zMove)
{
    if(_zPosition < -20) { alive=false; }
    _zPosition += zMove;
    cockpit.SetTransform(glm::translate(glm::mat4(), vec3(_xPosition,0,_zPosition)));
}

void EnemyShipBis::animate()
{

    if(_angle >= 2*glm::pi<float>()) _angle=0;
    else _angle += glm::pi<float>()/240;
    cockpit.SetTransform(glm::rotate(glm::mat4(), _angle, vec3(1, 1, 0)));
}

void EnemyShipBis::destroyWithExplosion()
{

}

void EnemyShipBis::destroyWithoutExplosion()
{

}
