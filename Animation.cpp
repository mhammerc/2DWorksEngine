#include "Animation.h"

void we::Animation::turnAnimation(const std::string &name, int type)
{
	/* Convert into integer the number of picture contain the actual animation */
	int numberOfPictures = atoi(_configuration[name + "_" + "number"].c_str());


	if (name != lastAnimationLaunchedName) /* Else, the animation is not already launched and we launch it */
	{
		frame = 0;
		setTexture(_texture[name + "_" + std::to_string(0)]);
		lastAnimationLaunchedName = name;
		lastAnimationLaunchedKey = 0;
		countType = true;
		hasAlreadyDoOneTurn = false;
	}


	/* If animation is already launched, we just set the next texture*/
	if (name == lastAnimationLaunchedName)
	{
		/* We set the next texture if the present frame number is a key frame */
		if (Utility::isInteger(frame / atoi(_configuration["interval"].c_str())))
		{
			/* Inverse the count type if we are on the last texture (to get the previous or the following) */
			if (lastAnimationLaunchedKey == numberOfPictures-1 || hasAlreadyDoOneTurn && lastAnimationLaunchedKey == 0)
			{
				if (type == 0) /* It the display method allow to rewind*/
				{
					hasAlreadyDoOneTurn = true;

					if (countType)
						countType = false;
					else
						countType = true;
				}
				else if (type == 1) /* If the display method want restart to 0 when last picture was drawed */
				{
					lastAnimationLaunchedKey = -1;
				}
			}

			if (countType)
				++lastAnimationLaunchedKey;
			else
				--lastAnimationLaunchedKey;

			/* And finally, set the texture to entity */
				setTexture(_texture[name + "_" + std::to_string(lastAnimationLaunchedKey)]);			
		}
	}

	++frame;

}

bool we::Animation::loadFromFile(const std::string &path)
{
	std::ifstream flux(path);

	if (!flux)
	{
		std::cerr << "Error A1 : can't open file in Animation class ('" << path << "')\n";
		return false;
	}

	std::string key;
	std::string value;

	while (flux >> key)
	{
		Utility::eraseFirstSpecialChar(key);

		if (key == "texture_link")
		{
			flux >> _configuration[key];
			if (!_image.loadFromFile(_configuration[key]))
				return false;
		}

		else if (key == "animation") /* If the keyword set the start of new animation */
		{
			std::string animationName;
			flux >> animationName; /* First, we have the name */
			
			flux >> key;
			Utility::eraseFirstSpecialChar(key);

			flux >> _configuration[animationName + "_" + key]; /* The number of texture */
			
			/* And we save all origin point of all texture */
			for (int i = 0; i < atoi(_configuration[animationName + "_number"].c_str()); ++i)
			{
				int width;
				flux >> key; /* Will contain #width */
				flux >> width;


				int height;
				flux >> key; /* Will contain #height */
				flux >> height;

				/* Get the size of this textures */
				int texture_width = atoi(_configuration["texture_width"].c_str());
				int texture_height = atoi(_configuration["texture_height"].c_str());

				/* Set the name of this texture */
				std::string name = animationName + "_" + std::to_string(i);

				/* And save the texture */
				_texture[name] = sf::Texture();
				_texture[name].loadFromImage(_image, sf::IntRect(sf::Vector2i(width, height), sf::Vector2i(texture_width, texture_height)));

			}
		}
		else /* This is a lambda information key */
			flux >> _configuration[key];
	}

	//std::cout << "Animation loaded.\nName : " << _configuration["name"] << "\nVersion : " << _configuration["version"] << "\n\n"; //DEBUG ONLY

	return true;
}

we::Animation::Animation() : frame(-1), lastAnimationLaunchedKey(0), countType(false)
{
	Sprite::Sprite();
}


we::Animation::~Animation()
{
}
