#include "T-Array.h"
GameEntry::GameEntry(const std::string& str /* = "" */, int s /* = 0 */) :name_(str), score_(s)
{

}
std::string GameEntry::getName()const
{
	return name_;
}

int GameEntry::getScore()const
{
	return score_;
}