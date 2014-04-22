#include "TileMap.h"

bool we::TileMap::collision(const sf::Sprite &sprite)
{
	int widthWorld = atoi(_configuration["tileset_width"].c_str()); //Width of the world in number of tiles
	int heightWorld = atoi(_configuration["tileset_height"].c_str()); //Height of the world in number of tiles
	int widthTile = atoi(_configuration["texture_width"].c_str()); //Width of tile texture
	int heightTile = atoi(_configuration["texture_height"].c_str()); //Height of tile texture
	float scaleX = getScale().x;
	float scaleY = getScale().y;



	/* We verify if the sprite is out of the world */
	if (sprite.getPosition().x < 0 || (sprite.getPosition().x + sprite.getGlobalBounds().width - 1) / scaleX >= widthWorld * widthTile
		|| sprite.getPosition().y < 0 || (sprite.getPosition().y + sprite.getGlobalBounds().height - 1) / scaleY >= heightWorld * heightTile)
		return 1;
	
	
	int xMin, xMax; //Will contain all x possibilities values contained in sprite
	int yMin, yMax; //Will contain all y possibilities values contained in sprite
	int indexTile; //Contain the index of the tile who is verifying
	bool typeOfIndexTile; //Contain true if the tile block the sprite

	xMin = sprite.getPosition().x / widthTile / scaleX;
	xMax = (sprite.getPosition().x + sprite.getGlobalBounds().width - 1) / widthTile / scaleX;

	yMin = sprite.getPosition().y / heightTile / scaleY;
	yMax = (sprite.getPosition().y + sprite.getGlobalBounds().height - 1) / heightTile / scaleY;

	for (int i = xMin; i <= xMax; i++)
	{
		for (int j = yMin; j <= yMax; j++)
		{
			indexTile = j * widthWorld;
			indexTile += i;

			typeOfIndexTile = _collision[_mapContents.getArray()[indexTile]];

			if (typeOfIndexTile == true)
				return true;
		}
	}

	return false;

}

bool we::TileMap::loadFromFile(const std::string &path)
{
	std::ifstream flux(path);

	if (!flux)
	{
		std::cerr << "Error A1 : can't open file in TileMap class ('" << path << "')\n";
		return false;
	}

	std::string key;
	std::string value;

	while (flux >> key)
	{
		Utility::eraseFirstSpecialChar(key);

		if (key == "tileset_link") /* The link to the tileset file */
		{
			flux >> _configuration[key];
			if (!_mapContents.loadFromFile(_configuration[key])) //Load the tileset in the array (mapContents)
				return false;
		}
		else if (key == "collision") /* All collisions by type of tile */
		{
			flux >> key;

			while (key != "end")
			{
				int numberKey = atoi(key.c_str()); //Translate the key to integer
				flux >> _collision[numberKey]; //The next flux is 0 (entity can pass across the tile) or 1 (entity can't pass across the tile)

				flux >> key;
				Utility::eraseFirstSpecialChar(key);
			}
		}
		else
			flux >> _configuration[key];
	}

	//std::cout << "Level loaded.\nName : " << _configuration["name"] << "\nVersion : " << _configuration["version"] << "\n\n"; //DEBUG ONLY

	return load();
}

we::MapContents we::TileMap::getMapContents()
{
	return _mapContents;
}

std::map<std::string, std::string> we::TileMap::getConfiguration()
{
	return _configuration;
}

std::map<int, bool> we::TileMap::getCollisions()
{
	return _collision;
}

we::TileMap::TileMap(const std::string &path)
{
	loadFromFile(path);
}

bool we::TileMap::load()
{

	/* Getting the size of the world and the size of texture */
	m_width = atoi(_configuration["tileset_width"].c_str());
	m_height = atoi(_configuration["tileset_height"].c_str());

	sf::Vector2u tileSize;
	tileSize.x = atoi(_configuration["texture_width"].c_str());
	tileSize.y = atoi(_configuration["texture_height"].c_str());

	/* Loading texture of tileset */
	if (!m_tileset.loadFromFile(_configuration["texture_link"]))
		return false;

	/* Resize the vertex array to contain the world */
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(m_width * m_height * 4);

	/* Fill the vertex array */
	for (unsigned int i = 0; i < m_width; ++i)
		for (unsigned int j = 0; j < m_height; ++j)
		{
			/* Getting the actual tile's number */
			int tileNumber = _mapContents.getArray()[i + j * m_width];

			/* Getting texture position */
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			/* Getting pointer to the quad to define */
			sf::Vertex* quad = &m_vertices[(i + j * m_width) * 4];

			/* Place his fourth corners*/
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			/* Place the fourth texture position */
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}

	return true;
}

void we::TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	/* Setting the transformation */
	states.transform *= getTransform();

	/* Setting texture tileset */
	states.texture = &m_tileset;

	/* Finnaly, we draw the vertex array */
	target.draw(m_vertices, states);
}

we::TileMap::TileMap() {}

we::TileMap::~TileMap() {}
