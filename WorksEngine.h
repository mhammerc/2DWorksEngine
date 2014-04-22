
/**
	\file WorksEngine.h
	\brief Core file include other file of 2D Works Engine
	\author Main developper : Martin H. Alias Imote
	\author Graphic artist and main contributor : MrGantz02
	\version 0.1
*/

/* GameLoop */
	#include "Game.h"

/* Graphics Engine */
	#include "Animation.h"
	/* TileMap Engine */
		#include "TileMap.h"
		#include "MapContents.h"



/* Utility Tools */
	#include "Utility.h"



/**
* \namespace we
* \brief This namespace regroup all elements refered to 2D Works Engine
*/


/**
\mainpage 2D Works Engine

Simply create 2D application with tile map and animations !
This framework allow you to create a tile map and to animate sf::Sprite elements.

\section how_to_use_it How to use it ?

Follow this exemple code :

\code{.cpp}
	#include <SFML/Graphics.hpp>
	#include "WorksEngine.h"

	int main()
	{
		sf::RenderWindow window(sf::VideoMode(360, 208), "2D Works Engine"); //The windows to draw elements
		window.setVerticalSyncEnabled(true); //To get constant 60 FPS (or more if your screen is better)

		we::TileMap map; //The tile map
		if (!map.loadFromFile("data/maps/mario_conf.dat")) //Link to you conf file (see below)
		{
			//Error occured
		}

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(); //Clear the screen
			window.draw(map); //Draw the map
			window.display(); //Display all drawed elements
		}

		return 0;
	}
\endcode

The mario_conf.dat look like this :
\code
	#version 1.1
	#name Mario_Conf_Tile_File

	#texture_link data/maps/tileset_mario_2.bmp
	#texture_width 32
	#texture_height 32

	#tileset_link data/maps/tileset_mario_2_world.dat
	#tileset_width 15
	#tileset_height 10

	#collision
		6 0
		8 1
		0 1
		59 0
		62 0
		60 0
	#end
\endcode

The tileset file look like this :

\code
	6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
	6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
	6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
	6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
	6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
	6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
	6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
	6 59 6 6 6 62 6 6 6 60 6 6 6 6 6
	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	8 8 8 8 8 8 8 8 8 8 8 8 8 8 8
\endcode

Just link all this to a tileset picture and you map is drawed !

*/