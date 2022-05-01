#include "entities.h"

using namespace std;

//********************//
//Методы класса Entity//
//********************//

Entity::Entity(String initF, float initX, float initY) 
{
	file = initF;
	x = initX;
	y = initY;
	image.loadFromFile(file);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Entity::setPosition(float initX, float initY) 
{
	x = initX;
	y = initY;
	sprite.setPosition(x, y);
}

float Entity::getX() { return x; }
float Entity::getY() { return y; }

//********************//
//Методы класса Rocket//
//********************//

Rocket::Rocket(String initF, float initX, float initY) : Entity(initF, initX, initY) 
{
	image.loadFromFile(file);
	image.createMaskFromColor(Color(255, 255, 255), 0);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 77, 139));
	sprite.setOrigin(w / 2, h - hFire);
}

short Rocket::getHFire() { return hFire; }

void Rocket::control(Vector2u wSize, float frame, float yGround)
{
	float a = 0.05, maxSpeedX = 4;
	float alt = yGround - y;
	cout << alt << endl << y << endl << yGround << endl << a << endl << endl;

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		sprite.setTextureRect(IntRect(w * (int)frame, 0, w, h));
		speedY -= a;
		if (speedY < -maxSpeedX) speedY = -maxSpeedX;
		if (alt > 0)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				speedX -= a;
				if (speedX < -maxSpeedX) speedX = -maxSpeedX;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				speedX += a;
				if (speedX > maxSpeedX) speedX = maxSpeedX;
			}
		}
	}
	else
	{
		speedY += a;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	
	if (alt < 0)
	{
		y = yGround;
		speedY = -speedY / 2;
		speedX = speedX / 2;
		a = 0;
	}

	if (alt > 500)
	{
		y = yGround - 500;
		speedY = 0;
		a = 0;
	}

	if ((x < 0) || (x > wSize.x - w / 2)) {
		if (x < 0) x = 0;
		else x = wSize.x - w / 2;
		speedX = -speedX;
	}

	sprite.setRotation(2 * speedX);

	x += speedX;
	y += speedY;

	sprite.setPosition(x, y);
}
