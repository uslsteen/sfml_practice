#include "platformer.h"



int main()
{
 /*Start block for downloading maps of the game*/

    char name_of_file[MAX_FILE_NAME] = { 0 };
	char source[MAX_FILE_NAME] = "maps/";
	char* res = nullptr;

	size_t byte_file_size = 0, num_of_str = 0;
	Strings* buffer_of_strs = nullptr;

	int check_input = Input("%s", name_of_file);

	if (check_input == NULL)
	{
		printf("Error with reading name of file.\n");
		return 0;
	}

	strcat(source, name_of_file);

	char* text_buffer = Create_Buffer(source, &byte_file_size);

	if (text_buffer == NULL)
	{
		printf("Error with creating buffer\n");
		return 0;
	}

	buffer_of_strs = Create_Ptr_Buf(text_buffer, byte_file_size, &num_of_str, '\n');
	assert(buffer_of_strs != NULL);

	/*End of maps block*/


	/***********************************************************************/


	/*Start block for working with SFML*/

	RenderWindow window(VideoMode(WIDTH_OF_SCREEN, HEIGHT_OF_SCREEN), "TRY_TO_CREATE_MARIO");

	//Menu(window);

	Texture TileSet;
	TileSet.loadFromFile("images/Mario_Tileset.png");

	Player plr(TileSet);
	Enemy enemy;

	enemy.Set(TileSet, 48 * 16, 13 * 16);

	Sprite tile(TileSet);

	SoundBuffer sound_buffer;
	sound_buffer.loadFromFile("sounds/Jump.ogg");
	Sound sound(sound_buffer);

	Music music;
	music.openFromFile("sounds/Mario_Theme.ogg");
	music.play();

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 500; 

		if (time > 20) time = 20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		plr.Mykeyboard(sound);

		plr.Update(time, buffer_of_strs);
		enemy.Update(time, plr, buffer_of_strs);

		Intersection(enemy, plr);

		plr.Map_scrolling();

		window.clear(Color(107, 140, 255));
		plr.Draw_map(window, tile, num_of_str, buffer_of_strs);

		window.draw(plr.sprite);
		window.draw(enemy.sprite);

		window.display();
	}

	return 0;
}



