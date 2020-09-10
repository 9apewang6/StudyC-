#ifndef _T_SCORES_H_
#define _T_SCORES_H_
#include "T-Array.h"

class T_Scores
{
public:
	T_Scores(int maxEnt =10);
	T_Scores(const T_Scores& s);
	T_Scores(T_Scores&& s);
	T_Scores& operator=(const T_Scores& other);
	~T_Scores();
	void add(const GameEntry& e);
	GameEntry remove(int i)noexcept(false);
	void display()const;

private:
	void initscores(const T_Scores& T);
private:
	int maxEntries;
	int numEntries;
	GameEntry* entry_;
};



#endif  //_T_SCORES_H_

