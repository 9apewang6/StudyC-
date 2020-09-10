#include "Score.h"
Score::Score(int maxEntry):maxEntries(maxEntry),numEntries(0)
{
	entry_ = new GameArray[maxEntry];
}
void Score::init(const Score& sr)
{
	maxEntries = sr.maxEntries;
	numEntries = sr.numEntries;
	entry_ = new GameArray[maxEntries];
	for (int i = 0; i < maxEntries; i++)
	{
		entry_[i] = sr.entry_[i];
	}
}
Score::Score(const Score& sr)
{
	init(sr);
}

Score::Score(Score&& sr)
{
	maxEntries = sr.maxEntries;
	numEntries = sr.maxEntries;
	entry_ = sr.entry_;
	sr.entry_ = nullptr;  
}

Score& Score::operator=(const Score& sr)
{
	if (&sr == this)
		return *this;
	if (entry_ != nullptr)
	{
		delete[] entry_;
	}
	init(sr);
	return *this;
}
Score::~Score()
{
	if (entry_ != nullptr)
	{
		delete[] entry_;
		entry_ = nullptr;
	}
}

void Score::add(const GameArray& ar)
{
	int newscore = ar.getScore();
	if (numEntries == maxEntries)
	{
		if (newscore <= entry_[maxEntries - 1].getScore())
			return;
	}
	else
	{
		++numEntries;
	}

	//  插入排序  ,, 升序 
	// key =  newsore ; 
	// j =  numentries -1
	int j = numEntries - 2;

	while (j>=0&&newscore <= entry_[j].getScore())
	{
		entry_[j + 1] = entry_[j];
		j--;
	}
	entry_[j + 1] = ar;
}
GameArray Score::remove(int index)noexcept
{
	// 当index >= numentries  时， 移除最后一个元素 
	if ((index<0)||(index>=numEntries))
	{
		throw std::logic_error("invalid index");
	}
	
	GameArray ans = entry_[index];
	for (int i = index; i < (numEntries - 1); i++)
	{
		entry_[i] = entry_[i + 1];
	}
	numEntries--;
	return ans;
}

void Score::display()const
{
	int i = 0;
	for (i = 0; i < numEntries; i++)
	{
		cout << i + 1 << "." << "name:    " << entry_[i].getName() << "    score:    " << entry_[i].getScore() << endl;
	}
	std::cout << std::endl;

}
int Score::getSize()const
{
	return numEntries;
}
