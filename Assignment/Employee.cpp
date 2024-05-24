#include "Employee.h"

#include <cassert>
#include <cmath>
#include <iostream>

namespace Assignment1
{
	Employee::Employee(const FEmployeeInfo& Info, const EEmployeeType EmployeeRole)
		: EmployeeInfo(Info),
		  RoleType(EmployeeRole)
	{
		CalculateSalary();
	}

	void Employee::PrintInfo() const
	{
		std::wcout << L"�̸�: " << EmployeeInfo.Name << '\n'
			<< L"����: " << GetRoleName() << '\n'
			<< L"�޿�: " << mSalary << L"����" << '\n'
			<< "--------------------------------------\n";
	}

	void Employee::CalculateSalary()
	{
		assert(RoleType != EEmployeeType::None, L"��� ���� ����");

		switch (EmployeeInfo.SalaryType)
		{
		case ESalaryType::Hour:
			mSalary = EmployeeInfo.WorkHour * pow(2, static_cast<int>(RoleType));
			break;
		case ESalaryType::Month:
			mSalary = (200 + ((static_cast<int>(RoleType) - 1) * 20) + EmployeeInfo.Year * 5);
			break;
		case ESalaryType::Year:
			mSalary = (2000 + ((static_cast<int>(RoleType) - 1) * 1000) + EmployeeInfo.Grade * 500) / 12;
			break;
		case ESalaryType::None:
			break;
		}
	}

	// �ڽ� �����ڴ� �θ� ������ ȣ�� ����Ÿ�� ����

	Staff::Staff(const FEmployeeInfo& Info)
		: Employee(Info, EEmployeeType::Staff)
	{
	}

	AssignmentManager::AssignmentManager(const FEmployeeInfo& Info)
		: Employee(Info, EEmployeeType::AssignmentManager)
	{
	}

	Manager::Manager(const FEmployeeInfo& Info)
		: Employee(Info, EEmployeeType::Manager)
	{
	}

	GeneralManager::GeneralManager(const FEmployeeInfo& Info)
		: Employee(Info, EEmployeeType::GeneralManager)
	{
	}

	Director::Director(const FEmployeeInfo& Info)
		: Employee(Info, EEmployeeType::Director)
	{
	}
}
