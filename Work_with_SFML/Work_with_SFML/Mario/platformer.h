#ifndef __PLATFORMER_H__
#define __PLATFORMER_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "..\strings\strings.h"
#include "strings/strings.h"

#include <iostream>
#include <string>

using namespace sf;


enum Params_of_the_game
{
	GROUND = 300,
	HEIGTH_OF_MAP = 17,
	WIDTH_OF_MAP = 150,
	WIDTH_OF_SCREEN = 640,
	HEIGHT_OF_SCREEN = 400,
	GORIZONTAL = 0,
	VERTICAL = 1,
	NUM_OF_ENEMY = 2
};


enum Menu
{
	EXIT = 0,
	START_NEW_GAME = 1,
	SELECT_MAP = 2
};

struct Res_of_menu_t
{
	const char* name_of_file;
	enum Menu res;
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
	
	Enemy(Texture& texture, int x, int y);

	void Update(float time, Player& plr, Strings* buffer_of_strs);

	void Collision(Strings* buffer_of_strs);
};

/******************__COMMON_FUNC_FOR WORKING*************************/

void Mykeyboard(Sound& sound, Player& plr);

struct Res_of_menu_t Menu(RenderWindow& window);

void Intersection(Enemy& enemy, Player& player);

void Draw_map(RenderWindow& window, Sprite& tile, size_t num_of_strs, Strings* buffer_of_strs, Player& plr);

Strings* Start_game(size_t* num_of_str, const char* name_of_file);

const char* Map_selection(RenderWindow& window);


#endif // __PLATFORMER_H__