// LinkedList.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "List.h"


int main()
{
	using namespace JSTL;


	List<int> TestList;

	TestList.Insert(0);
	TestList.Insert(2);
	TestList.Insert(3);
	TestList.Insert(1);

	TestList.PrintAll();
}
