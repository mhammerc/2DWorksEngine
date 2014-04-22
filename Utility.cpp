#include "Utility.h"


void we::Utility::eraseFirstSpecialChar(std::string &a)
{
	if (a[0] == '#')
		a.erase(0, 1);
}

bool we::Utility::isInteger(double number)
{
	return number == std::floor(number);
}

std::map<std::string, std::string> we::Utility::getConfigurationFromFile(const std::string &path)
{
	std::ifstream flux(path);

	if (!flux)
	{
		std::cerr << "Error A1 : can't open file ('" << path << "')\n";
		throw;
	}

	std::string key;
	std::map<std::string, std::string> _configuration;

	while (flux >> key)
	{
		Utility::eraseFirstSpecialChar(key);
		flux >> _configuration[key];
	}

	return _configuration;


}

we::Utility::Utility()
{
}


we::Utility::~Utility()
{
}
