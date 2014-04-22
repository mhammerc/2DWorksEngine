#pragma once

#include <string>
#include <SFML/System.hpp>
#include <SFML\Graphics.hpp>

namespace we
{
	/**
	\class Game
	\brief This class represent the game loop. Inherit this class to one of your class and let's start !

	Use the Game Loop is easy. Follow this exemple :

	MyGame.h :
	\code{.cpp}
		#pragma once
		#include <SFML/Graphics.hpp>
		#include "WorksEngine.h" //Automatically include all engine's functions


		class MyGame : public we::Game
		{
			public:
			bool draw();
			bool update();

			bool initialize();

			MyGame();
			~MyGame();
		};
	\endcode

	MyGame.cpp :
	\code{.cpp}
		#include "MyGame.h"

		bool MyGame::update()
		{
			//Update your logic game here

			sf::Event event;
			while (_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					exit();
					return false; //Return false to stop the game
				}
			}

		return true; //Return true to continue the game
		}

		bool Mario::draw()
		{
			//Update() is called before draw()
			//Draw your drawable entities here (see SFML)

			//_window.draw(YourEntity);

			return true; //Return true to continue the game
		}

		bool Mario::initialize()
		{
			//Configure your game before start the game loop (update() and draw())

			_window.setFramerateLimit(60); //To get constant framerate

			//Add in your .h file we::TileMap variable and initialize it here for exemple
			// if (!_map.loadFromFile("data/maps/tileset_mario_2_conf.dat"))
			//	return false;

			return true;
		}

		//Load the window here like this (see SFML doc for more informations)
		Mario::Mario() : we::Game(sf::VideoMode(960, 640), "2D Works Engine") {}


		Mario::~Mario()	{}
	\endcode

	main.cpp :
	\code{.cpp}
		#include "MyGame.h"

		int main()
		{
			Mario mario;
			if (mario.initialize())
				return mario.launch();
			return 0;
		}
	\endcode


	*/
	class Game
	{

	public:
		/**\brief Internal function used to start the Game Loop
		\return false if one error occurred*/
		bool launch();

		/**\brief Called every frame to update the game logic
		\return false if one error occurred*/
		virtual bool update() = 0;
		/**\brief Called every frame to draw your entities
		\return false if one error occurred*/
		virtual bool draw() = 0;

		/**\brief Called only one time to intialize your game before enter the game loop (update() and draw())
		\return false if one error occurred*/
		bool initialize();

		/**\brief Used to stop you game */
		void exit();

		/**\brief Same as exit()*/
		void stop();

		/**\brief Constructor
		\param resolution Size of the window you want (see SFML doc)
		\param name Name of the window
		*/
		Game(sf::VideoMode resolution, std::string name);
		virtual ~Game();

	protected:
		sf::RenderWindow _window;
		sf::Clock _ticks;
		bool _canContinueGameLoop;

	};
}

