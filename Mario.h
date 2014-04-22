#pragma once
#include "WorksEngine.h"
#include "Player.h"
#include <SFML/Graphics.hpp>


	class Mario : public we::Game
	{
	public:
		bool draw();
		bool update();

		bool initialize();

		Mario();
		~Mario();

	protected:
		we::TileMap _map;
		Player _player;
	};