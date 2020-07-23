#include "platformer.h"


Player::Player(Texture& image) : dx(0.1),
								 dy(0.1),
								 currentFrame(0),
								 offsetX(0),
								 offsetY(0),
								 onGround(true)
{
	sprite.setTexture(image);
	rect = FloatRect(100, 180, 16, 16);
}


void Player::Update(float time, Strings* buffer_of_strs)
{
	rect.left += dx * time;
	Collision(GORIZONTAL, buffer_of_strs);

	if (!onGround)
		dy = dy + 0.0005 * time;

	rect.top += dy * time;
	onGround = false;

	Collision(VERTICAL, buffer_of_strs);

	currentFrame += time * 0.005;

	if (currentFrame > 3)
		currentFrame -= 3;

	if (dx > 0)
		sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame), 144, 16, 16));

	if (dx < 0)
		sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame) + 16, 144, -16, 16));


	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	dx = 0;
}


void Player::Collision(int dir, Strings* buffer_of_strs)
{

	for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
	{
		for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
		{
			if ((buffer_of_strs[i].line_ptr[j] == 'P') || (buffer_of_strs[i].line_ptr[j] == 'k') || (buffer_of_strs[i].line_ptr[j] == '0') || (buffer_of_strs[i].line_ptr[j] == 'r') || (buffer_of_strs[i].line_ptr[j] == 't'))
			{
				if (dy > 0 && dir == VERTICAL)
				{
					rect.top = i * 16 - rect.height;
					dy = 0;
					onGround = true;
				}
				if (dy < 0 && dir == VERTICAL)
				{
					rect.top = i * 16 + 16;
					dy = 0;
				}
				if (dx > 0 && dir == GORIZONTAL)
				{
					rect.left = j * 16 - rect.width;
				}
				if (dx < 0 && dir == GORIZONTAL)
				{
					rect.left = j * 16 + 16;
				}
			}

			if (buffer_of_strs[i].line_ptr[j] == 'c')
			{
				buffer_of_strs[i].line_ptr[j] = ' ';
			}
		}
	}

}

void Player::Map_scrolling()
{
	if (rect.left > WIDTH_OF_SCREEN / 2)
		offsetX = rect.left - WIDTH_OF_SCREEN / 2;

	if (rect.top > HEIGHT_OF_SCREEN / 2)
		offsetY = rect.top - HEIGHT_OF_SCREEN / 2;
}

//**************************__ENEMY_CLASS_BLOCK*********************************//


Enemy::Enemy(Texture& image, int x, int y) : dx(0.05),
											 currentFrame(0),
											 life(true)
{
	sprite.setTexture(image);
	rect = FloatRect(x, y, 16, 16);
}

void Enemy::Update(float time, Player& plr, Strings* buffer_of_strs)
{
	rect.left += dx * time;

	Collision(buffer_of_strs);


	currentFrame += time * 0.005;
	if (currentFrame > 2)
		currentFrame -= 2;

	sprite.setTextureRect(IntRect(18 * int(currentFrame), 0, 16, 16));

	if (!life)
		sprite.setTextureRect(IntRect(58, 0, 16, 16));


	sprite.setPosition(rect.left - plr.offsetX, rect.top - plr.offsetY);

}


void Enemy::Collision(Strings* buffer_of_strs)
{

	for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
	{
		for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
		{
			if ((buffer_of_strs[i].line_ptr[j] == 'P') || (buffer_of_strs[i].line_ptr[j] == '0'))
			{
				if (dx > 0)
				{
					rect.left = j * 16 - rect.width; dx *= -1;
				}
				else if (dx < 0)
				{
					rect.left = j * 16 + 16;  dx *= -1;
				}

			}
		}
	}
}




/**********************__COMMON_FUNC*******************************/


const char* Map_selection(RenderWindow& window)
{
	Texture mapTexture1, mapTexture2, mapTexture3;

	mapTexture1.loadFromFile("images/map1.png");
	mapTexture2.loadFromFile("images/map2.png");
	mapTexture3.loadFromFile("images/map3.png");

	Sprite map1(mapTexture1), map2(mapTexture2), map3(mapTexture3);

	bool isMenu = 1;
	int map_num = 0;

	map1.setPosition(3 * WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10);
	map2.setPosition(3 * WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10 + 1 * 120);
	map3.setPosition(3 * WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10 + 2 * 120);

	while (isMenu)
	{
		map1.setColor(Color::White);
		map2.setColor(Color::White);
		map3.setColor(Color::White);

		map_num = 0;

		window.clear(Color(0, 5, 0));

		if (IntRect(2 * WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10, 220, 40).contains(Mouse::getPosition(window)))
		{
			map1.setColor(Color::Red);
			map_num = 1;
		}
	
		if (IntRect(2 * WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10 + 1*120, 220, 40).contains(Mouse::getPosition(window)))
		{
			map2.setColor(Color::Red);
			map_num = 2; 
		}

		if (IntRect(2 * WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10 + 2*120, 220, 40).contains(Mouse::getPosition(window)))
		{
			map3.setColor(Color::Red);
			map_num = 3;
		}
	
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (map_num == 1)
			{
				isMenu = false; 
				return "map1.txt";
			}
			if (map_num == 2)
			{
				isMenu = false;
				return "map2.txt";
			}
			if (map_num == 3)
			{
				isMenu = false;
				return "map3.txt";
			}

		}

		window.draw(map1);
		window.draw(map2);
		window.draw(map3);

		window.display();
	}
}

struct Res_of_menu_t Menu(RenderWindow& window) 
{
	const char sel_map[MAX_FILE_NAME] = { 0 };
	Res_of_menu_t res;

	Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, aboutTexture; //menuBackground;

	menuTexture1.loadFromFile("images/start_new_game.png");
	menuTexture2.loadFromFile("images/about_this_game.png");
	menuTexture3.loadFromFile("images/select_map.png");
	menuTexture4.loadFromFile("images/exit.png");


	aboutTexture.loadFromFile("images/about.png");

	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menu4(menuTexture4), about(aboutTexture); //menuBg(menuBackground);

	bool isMenu = 1;

	int menuNum = 0;

	menu1.setPosition(2*WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN/10);
	menu2.setPosition(2*WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10  + 80);
	menu3.setPosition(2*WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10  + 80*2);
	menu4.setPosition(2 * WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10 + 80 * 3);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menu4.setColor(Color::White);

		menuNum = 0;

		window.clear(Color(0, 5, 0));

		if (IntRect(2 * WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10, 350, 80).contains(Mouse::getPosition(window)))
		{
			menu1.setColor(Color::Red);
			menuNum = 1;
		}

		if (IntRect(2 * WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10 + 80, 350, 80).contains(Mouse::getPosition(window)))
		{
			menu2.setColor(Color::Red);
			menuNum = 2;
		}

		if (IntRect(2 * WIDTH_OF_SCREEN / 9, HEIGHT_OF_SCREEN / 10 + 80*2, 350, 80).contains(Mouse::getPosition(window)))
		{
			menu3.setColor(Color::Red);
			menuNum = 3;
		}

		if (IntRect(2 * WIDTH_OF_MAP / 9, HEIGHT_OF_SCREEN / 10 + 80 * 3, 350, 80).contains(Mouse::getPosition(window)))
		{
			menu4.setColor(Color::Red);
			menuNum = 4;
		}
	
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				//start new game from the first map;
				isMenu = false;
				res.res = START_NEW_GAME;

				return res;
			}

			if (menuNum == 2)
			{
				window.draw(about);
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}
			if (menuNum == 3)
			{
				while (!Keyboard::isKeyPressed(Keyboard::Escape))
				{
					const char* sel_map = Map_selection(window);
				}
		

				res.name_of_file = sel_map;
				res.res = SELECT_MAP;

				return res;
			}
			if (menuNum == 4)
			{
				window.close();
				isMenu = false;
				res.res = EXIT;

				return res;
			}
		}
	//	window.draw(menuBg);

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);

		window.display();
	}
}

void Mykeyboard(Sound& sound, Player& plr)
{
	if (Keyboard::isKeyPressed(Keyboard::A))
		plr.dx = -0.1;

	if (Keyboard::isKeyPressed(Keyboard::D))
		plr.dx = 0.1;

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		if (plr.onGround)
		{
			plr.dy = -0.27;
			plr.onGround = false;
			//sound.play();
		}
	}
}


void Intersection(Enemy& enemy, Player& player)
{
	if (player.rect.intersects(enemy.rect))
	{
		if (enemy.life == true)
		{
			if (player.dy > 0)
			{
				enemy.dx = 0;
				player.dy = -0.2;
				enemy.life = false;
			}
			else
				player.sprite.setColor(Color::Red);
		}
	}
}



void Draw_map(RenderWindow& window, Sprite& tile, size_t num_of_strs, Strings* buffer_of_strs, Player& plr)
{
	int  i = 0, j = 0;

	for (i = 0; i < num_of_strs; ++i)
	{
		for (j = 0; j < buffer_of_strs[i].len; j++)
		{
			if (buffer_of_strs[i].line_ptr[j] == 'P')
				tile.setTextureRect(IntRect(143 - 16 * 3, 112, 16, 16));

			if (buffer_of_strs[i].line_ptr[j] == 'k')
				tile.setTextureRect(IntRect(143, 112, 16, 16));

			if (buffer_of_strs[i].line_ptr[j] == 'c')
				tile.setTextureRect(IntRect(143 - 16, 112, 16, 16));

			if (buffer_of_strs[i].line_ptr[j] == 't')
				tile.setTextureRect(IntRect(0, 47, 32, 95 - 47));

			if (buffer_of_strs[i].line_ptr[j] == 'g')
				tile.setTextureRect(IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));

			if (buffer_of_strs[i].line_ptr[j] == 'G')
				tile.setTextureRect(IntRect(145, 222, 222 - 145, 255 - 222));

			if (buffer_of_strs[i].line_ptr[j] == 'd')
				tile.setTextureRect(IntRect(0, 106, 74, 127 - 106));

			if (buffer_of_strs[i].line_ptr[j] == 'w')
				tile.setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));

			if (buffer_of_strs[i].line_ptr[j] == 'r')
				tile.setTextureRect(IntRect(143 - 32, 112, 16, 16));

			if (buffer_of_strs[i].line_ptr[j] == 'Y')
				tile.setTextureRect(IntRect(95, 5, 108, 107));

			if ((buffer_of_strs[i].line_ptr[j] == ' ') || (buffer_of_strs[i].line_ptr[j] == '0'))
				continue;

			tile.setPosition(j * 16 - plr.offsetX, i * 16 - plr.offsetY);
			window.draw(tile);
		}
	}
}


Strings* Start_game(size_t* num_of_str, const char* name_of_file)
{
	//char name_of_file[MAX_FILE_NAME] = "map.txt";
	char source[MAX_FILE_NAME] = "maps/";

	size_t byte_file_size = 0;
	Strings* buffer_of_strs = nullptr;

	strcat(source, name_of_file);

	char* text_buffer = Create_Buffer(source, &byte_file_size);

	if (text_buffer == NULL)
	{
		printf("Error with creating buffer\n");
		abort();
	}

	buffer_of_strs = Create_Ptr_Buf(text_buffer, byte_file_size, num_of_str, '\n');
	assert(buffer_of_strs != NULL);

	return buffer_of_strs;
}
