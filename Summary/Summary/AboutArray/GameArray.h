#pragma once
#include <iostream>
#include <string>
using namespace std;
class  GameArray
{
public:
	GameArray(string name = "", int score = 0);
	std::string getName()const;
	int getScore()const;
private:
	string name_;
	int score_;

};