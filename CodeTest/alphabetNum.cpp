#include <string>
#include <iostream>
using namespace std;

bool solution(string s)
{
	bool answer = true;

	int pNum = 0;
	int yNum = 0;

	for (const char c : s)
	{
		if (c == 'p' || c == 'P')
			pNum++;
		if (c == 'y' || c == 'Y')
			yNum++;
	}

	return pNum == yNum;
}
