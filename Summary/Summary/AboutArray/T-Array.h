#ifndef _TARRAY_H_
#define _TARRAY_H_
#include <string>
class GameEntry
{
public:
	GameEntry(const std::string& str = "", int s = 0);
	std::string getName()const;
	int getScore()const;
private:
	std::string name_;
	int score_;
};



#endif //_TARRAY_H_