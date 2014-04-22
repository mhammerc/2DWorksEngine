#pragma once

/**
	 \file Utility.h
	 \brief Contain we::Utility class
	 \author Main developper : Martin H. Alias Imote
	 \author Graphic artist and main contributor : MrGantz02
	 \version 0.1
*/

#include <string>
#include <cmath>
#include <map>
#include <fstream>
#include <iostream>

namespace we
{

	/**
		 \class Utility
		 \brief This class contain tools to do some classic action
		 \remark Don't instantiate this class, all functions are static !
	*/
	class Utility
	{
	public:

		/**
		 \brief In configuration files, you can start keyword with #. This function delete it
		 \param a The text you want apply the function
		*/
		static void eraseFirstSpecialChar(std::string &a);

		/**
		\brief This function test if a double number is integer
		\param number The number to apply the test
		\return Return true if the double is integer (x.0) (ex : 3.0, 4.0, 99.0)
		*/
		static bool isInteger(double number);

		/**
		\brief This function read a file and put in a map the key and the value
		\param path Path to the file
		\return the map contain all informations
		*/
		static std::map<std::string, std::string> getConfigurationFromFile(const std::string &path);

		Utility();
		~Utility();
	};
}

