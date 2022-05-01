#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;

//Класс общий
class Entity 
{
protected:
	float  x, y;
	String file;
	Image image;
	Texture texture;

public:
	Sprite sprite;

	Entity(String initF, float initX, float initY);

	float getX();
	float getY();

	void setPosition(float initX, float initY);
};

//Класс ракеты
class Rocket : public Entity 
{
protected:
	float speedX = 0, speedY = 0;
	short hFire = 38, w = 77, h = 139;
	bool onGround = 1, onMaxHeight = 0;

public:
	Rocket(String initF, float initX, float initY);

	short getHFire();

	void control(Vector2u wSize, float frame, float yGround);
};