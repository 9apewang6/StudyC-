#include "Score.h"
int main()
{
	Score s(10);
	s.add(GameArray("wang", 80));
	s.add(GameArray("wane", 81));
	s.add(GameArray("want", 82));
	s.add(GameArray("wany", 83));
	s.add(GameArray("wanu", 79));
	s.add(GameArray("wani", 85));
	s.add(GameArray("wano", 86));


	s.display();

	GameArray rev = s.remove(4);

	cout << "now the size is " << s.getSize() << endl;
	s.display();
	system("pause");
}