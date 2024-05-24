#include <iostream>
#include <locale>
#include <vector>

#include "Employee.h"


int main()
{
	using namespace Assignment1;

	std::locale::global(std::locale("kor"));

	std::vector<Employee*> Company;
	Company.reserve(18);

	// µ¿ÀûÇÒ´ç Æ÷ÀÎÅÍ ¼ÒÀ¯
	Employee* myeonkun = new Director({L"±è¸í±Õ", ESalaryType::Year, 20, 10, 100});

	Company.push_back(myeonkun);;
	Company.push_back(new Staff({L"±è¼º¹Î", ESalaryType::Year, 3, 2, 100}));
	Company.push_back(new AssignmentManager({L"±è±âÇö", ESalaryType::Hour, 7, 3, 100}));
	Company.push_back(new Staff({L"°ø´ÙÈò", ESalaryType::Hour, 3, 1, 100}));
	Company.push_back(new Staff({L"±èÀçÈñ", ESalaryType::Month, 1, 1, 400}));
	Company.push_back(new Manager({L"±èÇÑºû", ESalaryType::Month, 6, 5, 300}));

	std::wcout << L"*------------- Á÷¿ø¸ñ·Ï -------------*\n";
	for (const Employee* employee : Company)
	{
		if (employee)
		{
			employee->PrintInfo();
		}
	}


	// ¸Ş¸ğ¸® ÇØÁ¦
	delete myeonkun;

	return 0;
}
