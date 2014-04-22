#include "MapContents.h"


bool we::MapContents::loadFromFile(std::string path)
{
	/* Load file will contain tile contents */
	std::ifstream flux(path);

	if (!flux)
	{
		std::cerr << "Error A1 : can't open file in MapContents class ('" << path << "')\n";
		return false;
	}

	/* Save in array */
	int number;
	while (flux >> number)
		_tiles.push_back(number);

	return true;
}

void we::MapContents::setArray(std::vector<int> &tiles)
{
	_tiles = tiles;
}

std::vector<int> we::MapContents::getArray()
{
	return _tiles;
}

we::MapContents::MapContents(std::string &path)
{
	loadFromFile(path);
}

we::MapContents::MapContents(std::vector<int> &tiles)
{
	_tiles = tiles;
}

we::MapContents::MapContents(){}


we::MapContents::~MapContents(){}
