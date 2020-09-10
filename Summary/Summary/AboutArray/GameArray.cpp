#include "GameArray.h"
GameArray::GameArray(string name /* = "" */, int score /* = 0 */) :name_(name), score_(score)
{

}

std::string  GameArray::getName()const
{
	return name_;
}

int GameArray::getScore()const
{
	return score_;
}