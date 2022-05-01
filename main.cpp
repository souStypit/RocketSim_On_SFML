#include <iostream>
#include <SFML/Graphics.hpp>
#include "entities.h"

using namespace std;
using namespace sf;

int main() 
{
	RenderWindow window(VideoMode(1280, 720), "RocketSim", Style::Default); //Создает окно размером 1280 х 720
	window.setFramerateLimit(60); //Фиксирует fps на 60
	Vector2u wSize = window.getSize(); //Переменная, хранящая размер экрана
	Texture backTexture;
	backTexture.loadFromFile("Adds/Background.png");
	Sprite back;
	back.setTexture(backTexture);

	Clock clock;
	float frame = 1; //Отвечает за текущее положение анимации
	float yGround = wSize.y - 100;

	Entity ground("Adds/groundTexture.png", 0, yGround);
	ground.sprite.setColor(Color(100, 100, 130, 255));
	Rocket rocket("Adds/Entities/rocketTexture.png", 0, 0);
	rocket.setPosition(wSize.x / 2, yGround);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMilliseconds(); //Получает текущее время
		clock.restart();

		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();		//Проверяет открыто ли окно

		if (frame > 4.9) frame = 1;
		else frame += 0.005 * time;
		rocket.control(wSize, frame, yGround);

		window.clear(); // Очищает экран

		window.draw(back);
		window.draw(rocket.sprite);
		window.draw(ground.sprite);

		window.display();	//Рисует объекты на экране
	}
}