#ifndef __PLATFORMER_H__
#define __PLATFORMER_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "strings.h"

#include <iostream>
#include <string>

using namespace sf;


enum Params_of_the_game
{
	GROUND = 300,
	HEIGTH_OF_MAP = 17,
	WIDTH_OF_MAP = 150,
	WIDTH_OF_SCREEN = 600,
	HEIGHT_OF_SCREEN = 400,
	GORIZONTAL = 0,
	VERTICAL = 1
};


class Player
{
public:

	float dx, dy;
	float currentFrame;
	float offsetX, offsetY;

	FloatRect rect;
	Sprite sprite;

	bool onGround;

	
public:

	Player(Texture& image);

	void Update(float time, Strings* buffer_of_strs);

	void Collision(int dir, Strings* buffer_of_strs);

	void Draw_map(RenderWindow& window, Sprite& tile, size_t num_of_strs, Strings* buffer_of_strs);

	void Mykeyboard(Sound& sound);

	void Map_scrolling();

};



class Enemy
{
public:

	float dx;
	float currentFrame;

	FloatRect rect;
	Sprite sprite;

	bool life;

public:

	//Enemy();
	
	void Set(Texture& texture, int x, int y);

	void Update(float time, Player& plr, Strings* buffer_of_strs);

	void Collision(Strings* buffer_of_strs);
};

void Menu(RenderWindow& window);

void Intersection(Enemy& enemy, Player& player);


#endif // __PLATFORMER_H__