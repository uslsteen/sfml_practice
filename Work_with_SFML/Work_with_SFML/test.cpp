#include "Mario/platformer.h"



int main()
{
	Strings* buffer_of_strs = nullptr;
	size_t num_of_str = 0;

	RenderWindow window(VideoMode(WIDTH_OF_SCREEN, HEIGHT_OF_SCREEN), "TRY_TO_CREATE_MARIO");

	Res_of_menu_t res = Menu(window);

	if (res.res == EXIT)
		return 0;

	else if (res.res == START_NEW_GAME)
	{
		buffer_of_strs = Start_game(&num_of_str, "map1.txt");
	}
	else if (res.res == SELECT_MAP)
	{
		buffer_of_strs = Start_game(&num_of_str, res.name_of_file);
	}



	/*Start block for working with SFML*/

	Texture TileSet;
	TileSet.loadFromFile("images/Mario_Tileset.png");

	Player plr(TileSet);
	//Enemy enemy(TileSet, 48 * 16, 13 * 16);
	//Enemy enemy_1(TileSet, 68 * 16, 13 * 16);
	Enemy enemy[NUM_OF_ENEMY] =
	{
		Enemy(TileSet, 48 * 16, 13 * 16),
		Enemy(TileSet, 68 * 16, 13 * 16)
	};

	Sprite tile(TileSet);

	SoundBuffer sound_buffer;
	sound_buffer.loadFromFile("sounds/Jump.ogg");
	Sound sound(sound_buffer);

	Music music;
	music.openFromFile("sounds/Mario_Theme.ogg");
	//music.play();

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 500; 

		if (time > 20)
			time = 20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		Mykeyboard(sound, plr);

		plr.Update(time, buffer_of_strs);

		for (size_t i = 0; i < NUM_OF_ENEMY; ++i)
		{
			enemy[i].Update(time, plr, buffer_of_strs);
		}

		//enemy.Update(time, plr, buffer_of_strs);
		//enemy_1.Update(time, plr, buffer_of_strs);


		for (size_t i = 0; i < NUM_OF_ENEMY; ++i)
			Intersection(enemy[i], plr);
	
		//Intersection(enemy, plr);
		//Intersection(enemy_1, plr);

		plr.Map_scrolling();

		window.clear(Color(107, 140, 255));
		Draw_map(window, tile, num_of_str, buffer_of_strs, plr);

		window.draw(plr.sprite);

		for (size_t i = 0; i < NUM_OF_ENEMY; ++i)
			window.draw(enemy[i].sprite);
	
		//window.draw(enemy.sprite);
		//window.draw(enemy_1.sprite);

		window.display();
	}

	return 0;
}



