#include "T-Scores.h"
#include <iostream>
using namespace std;
T_Scores::T_Scores(int maxEnt /* =10 */) :maxEntries(maxEnt)
{
	entry_ = new GameEntry[maxEntries];
	numEntries = 0;
}

void T_Scores::initscores(const T_Scores& T)
{
	maxEntries = T.maxEntries;
	numEntries = T.numEntries;
	entry_ = new GameEntry[maxEntries];
	for (int i = 0; i < maxEntries; i++)
	{
		entry_[i] = T.entry_[i];
	}
}

T_Scores::T_Scores(const T_Scores& t)
{
	initscores(t);
}

T_Scores::T_Scores(T_Scores&& S)
{
	maxEntries = S.maxEntries;
	numEntries = S.numEntries;
	entry_ = S.entry_;
	S.entry_ = nullptr;
}

T_Scores& T_Scores::operator=(const T_Scores& t)
{
	if (this == &t)
		return *this;
	if (entry_ != nullptr)
		delete[] entry_;
	initscores(t);
	return *this;
}

T_Scores::~T_Scores()
{
	if (entry_!=nullptr)
	{
		delete[] entry_;
	}
}

void T_Scores::add(const GameEntry& e)
{
	int newScore = e.getScore();
	if (numEntries == maxEntries)
	{
		if (newScore <= entry_[maxEntries - 1].getScore())
		{
			return;
		}
	}
	else
	{
		++numEntries;

	}
	int i = numEntries - 2;
	while (i >= 0 && newScore > entry_[i].getScore())
	{
		entry_[i + 1] = entry_[i];
		--i;
	}
	entry_[i + 1] = e;
}

GameEntry T_Scores::remove(int i) noexcept(false)
{
	if ((i < 0) || (i >= numEntries))
	{
		throw std::logic_error("invalid index");
	}
	GameEntry  e = entry_[i];
	for (int j = i + 1; j < numEntries; j++)
	{
		entry_[j - 1] = entry_[j];
	}
	--numEntries;
	return e;
}

void T_Scores::display()const
{
	for (int i = 0; i < numEntries; i++)
	{
		std::cout << "(" << entry_[i].getName() << "," << entry_[i].getScore() << ")";
	}
	std::cout << std::endl;
}