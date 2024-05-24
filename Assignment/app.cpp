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

	// �����Ҵ� ������ ����
	Employee* myeonkun = new Director({L"����", ESalaryType::Year, 20, 10, 100});

	Company.push_back(myeonkun);;
	Company.push_back(new Staff({L"�輺��", ESalaryType::Year, 3, 2, 100}));
	Company.push_back(new AssignmentManager({L"�����", ESalaryType::Hour, 7, 3, 100}));
	Company.push_back(new Staff({L"������", ESalaryType::Hour, 3, 1, 100}));
	Company.push_back(new Staff({L"������", ESalaryType::Month, 1, 1, 400}));
	Company.push_back(new Manager({L"���Ѻ�", ESalaryType::Month, 6, 5, 300}));

	std::wcout << L"*------------- ������� -------------*\n";
	for (const Employee* employee : Company)
	{
		if (employee)
		{
			employee->PrintInfo();
		}
	}


	// �޸� ����
	delete myeonkun;

	return 0;
}
