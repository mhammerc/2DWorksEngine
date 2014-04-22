#include "Player.h"



void Player::update(we::TileMap &map)
{
	verifyKeyboard(map);
}

void Player::verifyKeyboard(we::TileMap &map)
{
	sf::Vector2f oldPosition = getPosition();
	bool isOneEventDone(false);

	/* TOP */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		isOneEventDone = true;
		move(sf::Vector2f(0, -2 * getScale().y)); //Move the player in consequences
		turnAnimation("walk_forward"); //Launch the animation
	}

	/* RIGHT */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		isOneEventDone = true;
		move(sf::Vector2f(2 * getScale().x, 0));
		turnAnimation("walk_right");
	}
	

	/* DOWN */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{	
		isOneEventDone = true;
		move(sf::Vector2f(0, 2 * getScale().y));
		turnAnimation("walk_left");
	}
	


	/* LEFT */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		isOneEventDone = true;
		move(sf::Vector2f(-2 * getScale().x, 0));
		turnAnimation("walk_down");
	}

	

	/* JUMP */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		isOneEventDone = true;
		turnAnimation("jump", 1);
	}


	if (isOneEventDone && map.collision(*this))
		setPosition(oldPosition);
	else if (!isOneEventDone)
		turnAnimation("no_event",1);
}


Player::Player()
{
	loadFromFile("data/player/player_animation.dat");
	setTexture(_texture["walk_forward_0"]);
	setColor(sf::Color(255, 255, 255, 250));
	setPosition(50, 50);
}


Player::~Player(){}
