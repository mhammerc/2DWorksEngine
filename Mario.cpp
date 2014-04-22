#include "Mario.h"



bool Mario::update()
{
	//Update your logic game here

		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				exit();
				return false;
			}
		}

		_player.update(_map);

		return true;
}

bool Mario::draw()
{
	_window.draw(_map);
	_window.draw(_player);

	return true;
}

bool Mario::initialize()
{
	_window.setFramerateLimit(60);

	_map.setScale(2, 2);

	if (!_map.loadFromFile("data/maps/tileset_mario_2_conf.dat"))
		return false;
	
	_player.scale(2, 2);
	
	
	return true;
}


Mario::Mario() : we::Game(sf::VideoMode(960, 640), "2D Works Engine")
{}


Mario::~Mario()
{
}
