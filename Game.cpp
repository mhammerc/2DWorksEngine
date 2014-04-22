#include "Game.h"


bool we::Game::launch()
{
	while (_canContinueGameLoop)
	{
		if (!update())
			return false;
		
		_window.clear();

		if (!draw())
			return false;

		_window.display();

	}

	return false;
}

void we::Game::exit()
{
	this->_canContinueGameLoop = false;
}

void we::Game::stop()
{
	exit();
}

we::Game::Game(sf::VideoMode resolution, std::string name) : _canContinueGameLoop(true), _window(resolution, name)
{
}


we::Game::~Game()
{
}
