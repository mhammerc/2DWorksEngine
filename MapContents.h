#pragma once

/**
\file MapContents.h
\brief File containing definition of MapContents class
\author Main developper : Martin H. Alias Imote
\author Graphic artist and main contributor : MrGantz02
\version 0.1
*/


#include <vector>
#include <fstream>
#include <string>
#include <iostream>

namespace we
{
	/**
	\class MapContents
	\brief This class contain the content of a map (it's the map cut in tiles)
	*/
	class MapContents
	{
	public:

		/**
		\brief Instanciate with a already existant array
		\param tiles The array to copy to instanciate the class
		*/
		MapContents(std::vector<int> &tiles);

		/**
		\brief Instanciate the class with a tile file
		\param path The path to file
		*/
		MapContents(std::string &path);

		/**
		\brief Default constructor
		\remark Use loadFromFile function to load tiles from file
		\remark Use setArray function to set tiles from existing array
		*/
		MapContents();

		/**
		\brief To load the tile from file
		\param path Path to file
		\return False if error occurred
		*/
		bool loadFromFile(std::string path);

		/**
		\brief To manually set the tile array
		\param tiles The array to set
		*/
		void setArray(std::vector<int> &tiles);

		/**
		\brief To get the map content array
		\return The map content array
		*/
		std::vector<int> getArray();

		~MapContents();

	protected:
		std::vector<int> _tiles;
	};
}