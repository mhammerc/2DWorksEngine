#pragma once

/**
\file Animation.h
\brief File containing definition of Animation class
\author Main developper : Martin H. Alias Imote
\author Graphic artist and main contributor : MrGantz02
\version 0.1
*/

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include "Utility.h"

namespace we
{

	/**
	\class Animation
	\brief Permit you to animate a sprite. Use this class like a normal sprite !

	To use the animation possibilities :
	\li Call loadFromFile(const std::string &path) with the path of the configuration file
	\li The configuration file look like this :
	\code
		#version 1.0
		#name Mario_Animation_Conf_File

		#interval 9

		#texture_link data/player/mario-charset.png
		#texture_width 17
		#texture_height 30

		#animation forward
			#number 3

			#width 8
			#height 79

			#width 49
			#height 79

			#width 87
			#height 79

		#animation jump
			#number 2

			#width 127
			#height 79

			#width 127
			#height 123
	\endcode
	
	\li #interval is the number of frame between changing of picture
	\li #texture_link is the path to the picture who contain animation file
	\li #texture_width is the width of one animation picture
	\li #texture_height is the height of one animation picture
	\li To declare an animation, you juste write #animation [NAME] (exemple : #animation forward. This animation will be launch when the player walk forward)
	\li After the declaration, you must write #number [0-X]. This is the number of picture will contain the animation
	\li Next, you must write X time #width and #height to declare the position of all picture. #width declare the left position of the picture and #height declare the top position of the picture. After, the framework calculates the complete image with #texture_width and #texture_height.
	\li You can declare unlimited animation.
	\li To use display animation, you just need to call turnAnimation(const std::string &name) with the name you precedently declared.
	*/
	class Animation : public sf::Sprite
	{
	public:
		
		/**
		\brief Load a animation from animation file
		\remark If the function return true, you can start the animation !
		\param path The path to the animation file
		\return False if an error occurred
		*/
		bool loadFromFile(const std::string &path);

		/**
		\brief Start or continue animation
		\param name The name of the animation
		\remark If you haven't start this animation before, the function start it
		\remark If we are texture less to display the animation, we got back to get new textures
		\remark You need call this function every frame or start this function in a thread to respect the interval writed in configuration file
		*/
		void turnAnimation(const std::string &name, int type = 0);

		Animation();
		~Animation();

	protected:
		sf::Image _image; //Contain the main image of the animation

		std::map<std::string, sf::Texture> _texture; //Contain all animations texture

		std::map<std::string, std::string> _configuration; //Contain the configuration from the configuration file

		double frame; //Contain the frame for regule the animation
		std::string lastAnimationLaunchedName; //Contain the name of the last animation launched
		int lastAnimationLaunchedKey; //Contain the key of the last texture of the last animation launched
		bool countType; //The count type, internal use
		bool hasAlreadyDoOneTurn; //If the present running animation has already do one cycle
	};

}