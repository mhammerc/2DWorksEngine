#pragma once
#include "Animation.h"
#include "TileMap.h"
#include <iostream>


	class Player :
		public we::Animation
	{
	public:
		void update(we::TileMap &map);
		void verifyKeyboard(we::TileMap &map);

		Player();
		~Player();

	protected:
		bool jump, top, right, left, down;
	};


