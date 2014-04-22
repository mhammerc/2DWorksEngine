#pragma once

/**
\file TileMap.h
\brief File containing definition of TileMap class
\author Main developper : Martin H. Alias Imote
\author Graphic artist and main contributor : MrGantz02
\version 0.1
*/

#include "Utility.h"
#include "MapContents.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>


namespace we
{

	/**
	\class TileMap
	\brief This class contain the world (tile map) and permit you to draw it. 

	Follow this exemple code :

	\code{.cpp}
	#include <SFML/Graphics.hpp>
	#include "WorksEngine.h"

	int main()
	{
		sf::RenderWindow window(sf::VideoMode(360, 208), "2D Works Engine"); //The windows to draw elements
		window.setVerticalSyncEnabled(true); //To get constant 60 FPS

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

	#texture_link data/maps/mario.bmp
	#texture_width 24
	#texture_height 16

	#tileset_link data/maps/mario_tiles.dat
	#tileset_width 15
	#tileset_height 13

	#collision
		0 0
		1 1
		2 1
		3 1
		4 1
		5 1
		6 1
		7 1
	#end
	\endcode

	The tileset file look like this :

	\code
	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	1 0 0 0 0 0 0 0 0 1 1 1 1 1 0
	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	0 0 3 4 0 0 0 2 2 2 2 0 0 2 2
	0 0 5 6 0 0 0 0 0 0 0 0 0 0 0
	0 0 5 6 0 0 0 0 0 0 0 0 0 0 0
	0 0 5 6 0 0 0 0 0 0 0 0 0 0 0
	7 7 7 7 7 7 7 7 7 7 7 7 7 7 7
	\endcode

	Just link all this to a tileset picture and you map is drawed !
	\li #texture_link is the path to the picture
	\li #texture_width is the width of one tile
	\li #texture_height is the height of one tile
	\li #tileset_link is the path to the file containing the organisation of the world
	\li #tileset_width is the width of the world
	\li #tileset_height is the height of the world
	\li To explain the collision of the world to the applicaiton, you must write it between #collision and #end. First, you write the number of the tile (ex : 0) and choose if the tile block any entities (1) or let pass any entities (0). Follow the exemple !
	\li In the tileset file, simply write the world. In the exemple, 7 is the floor, 0 is air and the rest are objects.  
	*/

	class TileMap : public sf::Drawable, public sf::Transformable
	{

	public:
		/**
		 \brief Constructor
		 \param path Instanciate the class and autoload a map with configuration file
		*/
		TileMap(const std::string &path);

		/**
		\brief Constructor
		\remark Use we::TileMap::loadFromFile function to load a map with configuration file
		*/
		TileMap();
		~TileMap();

		/**
		\brief Load the file to load the map.
		\param path Instanciate the class and autoload a map with configuration file
		\return Return false if a problem occurred when loading file
		*/
		bool loadFromFile(const std::string &path);

		/**
		\brief To test if sprite touch a blocked tile
		\param sprite Sprite to apply the test
		\return Return true if collision detected
		*/
		bool collision(const sf::Sprite &sprite);

		/**
		\brief To get the contents of this map
		\remark The content of a map is the map cut in tiles 
		\return Return true if collision detected
		*/
		MapContents getMapContents();

		/**
		\brief To get the map of collisions
		\remark The key is an integer : the type of tile
		\remark the value is a boolean : true if the tile block any entities
		\return Return the map of collisions
		*/
		std::map<int, bool> getCollisions();

		/**
		\brief To get the configuration from the file
		\remark Exemple : #name, #version or any non-specialized #<keyword> go in this map
		\remark The key to get the value of #name (keyword in the file) is name and not #name. The # was deleted
		\return Return the configuration map
		*/
		std::map<std::string, std::string> getConfiguration();

		/**
		\brief If changement was done, recalculate the map
		\return Return false if any errors occurred
		*/
		bool load();

	protected:
		/**
		\brief Contain configurations information from the configuration file
		*/
		std::map<std::string, std::string> _configuration;

		/**
		\brief Contain collisions information from the configuration file
		*/
		std::map<int, bool> _collision;

		/**
		\brief Contain std::we::MapContents information from the configuration file
		*/
		MapContents _mapContents;

		sf::VertexArray m_vertices;
		sf::Texture m_tileset;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		unsigned int m_width;
		unsigned int m_height;
		
	};
}

