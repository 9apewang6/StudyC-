#pragma once
#include "GameArray.h"
class Score {
public:
	Score(int maxEntry);
	Score(const Score& sr);
	Score(Score&& sr);
	Score& operator=(const Score& sr);
	~Score();
	void add(const GameArray& ar);  // 按分数进行升序排列,插入排序

	GameArray remove(int index)noexcept;
	void display()const;
	int getSize()const;
private:
	void init(const Score& sr);
private:
	int maxEntries;
	int numEntries;
	GameArray* entry_;

};