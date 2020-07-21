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


void Player::Draw_map(RenderWindow& window, Sprite& tile, size_t num_of_strs, Strings* buffer_of_strs)
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

			tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
			window.draw(tile);
		}
	}
}

void Player::Mykeyboard(Sound& sound)
{
	if (Keyboard::isKeyPressed(Keyboard::A))
		dx = -0.1;

	if (Keyboard::isKeyPressed(Keyboard::D))
		dx = 0.1;

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		if (onGround)
		{
			dy = -0.27;
			onGround = false;
			sound.play();
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


//**************************__ENEMY_CLASS_BLOCK*********************************//


void Enemy::Set(Texture& image, int x, int y)
{
	sprite.setTexture(image);
	rect = FloatRect(x, y, 16, 16);

	dx = 0.05;
	currentFrame = 0;
	life = true;
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

void Menu(RenderWindow& window) 
{
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;

	//menuTexture1.loadFromFile("images/111.png");
	//menuTexture2.loadFromFile("images/222.png");
	//menuTexture3.loadFromFile("images/333.png");

	menuTexture1.loadFromFile("111.png");
	menuTexture1.loadFromFile("222.png");
	menuTexture1.loadFromFile("333.png");

	aboutTexture.loadFromFile("about.png");

	menuBackground.loadFromFile("Penguins.jpg");

	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;

	int menuNum = 0;

	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);

	menuBg.setPosition(345, 0);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);

		menuNum = 0;

		window.clear(Color(129, 181, 221));
		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu1.setColor(Color::Blue);
			menuNum = 1;
		}

		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu2.setColor(Color::Blue);
			menuNum = 2;
		}


		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu3.setColor(Color::Blue);
			menuNum = 3;
		}
	
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) 
				isMenu = false;

			if (menuNum == 2)
			{
				window.draw(about);
				window.display(); 
				while (!Keyboard::isKeyPressed(Keyboard::Escape)); 
			}
			if (menuNum == 3)
			{
				window.close();
				isMenu = false;
			}
		}
		window.draw(menuBg);

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}