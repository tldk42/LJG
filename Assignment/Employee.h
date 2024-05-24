#pragma once
#include <string>

namespace Assignment1
{
	enum class EEmployeeType
	{
		None,
		Staff,             // ���
		AssignmentManager, // �븮
		Manager,           // ����
		GeneralManager,    // ����
		Director           //�̻�
	};


	enum class ESalaryType
	{
		None,
		Hour,  // �ñ�
		Month, //����
		Year   // ����
	};

	struct FEmployeeInfo
	{
		std::wstring Name;
		ESalaryType  SalaryType = ESalaryType::None; // �޿� ���� ���
		int          Year       = 0;                 // ����
		int          Grade      = 0;                 // �ɷ� ���
		int          WorkHour   = 0;                 // �� �ٹ� �ð�
	};

	// Base class (���� ���� Ŭ����)
	class Employee
	{
	public:
		Employee() = delete;

		Employee(const FEmployeeInfo& Info, const EEmployeeType EmployeeRole);
		virtual ~Employee() = default;

	public:
#pragma region Getter
		inline int GetSalaryPerHour() const { return mSalary / 12; }
		inline int GetSalaryPerMonth() const { return mSalary; }
		inline int GetSalaryPerYear() const { return mSalary * 12; }

		inline std::wstring GetName() const { return EmployeeInfo.Name; }

		inline ESalaryType   GetSalaryType() const { return EmployeeInfo.SalaryType; }
		inline EEmployeeType GetRole() const { return RoleType; }

		virtual inline std::wstring GetRoleName() const = 0;
#pragma endregion

		void PrintInfo() const;

	private:
		void CalculateSalary();

	protected:
		FEmployeeInfo EmployeeInfo;
		EEmployeeType RoleType = EEmployeeType::None;
		int           mSalary; // ���� ���� �޿�  (���� ����)
	};


	//-----------------------  ���  ------------------------------
	class Staff : public Employee
	{
	public:
		Staff(const FEmployeeInfo& Info);
		~Staff() override = default;

		inline std::wstring GetRoleName() const override { return L"���"; }
	};

	//-----------------------  �븮  ------------------------------
	class AssignmentManager : public Employee
	{
	public:
		AssignmentManager(const FEmployeeInfo& Info);
		~AssignmentManager() override = default;

		inline std::wstring GetRoleName() const override { return L"�븮"; }
	};

	class Manager : public Employee
	{
	public:
		Manager(const FEmployeeInfo& Info);
		~Manager() override = default;

		inline std::wstring GetRoleName() const override { return L"����"; }
	};

	class GeneralManager : public Employee
	{
	public:
		GeneralManager(const FEmployeeInfo& Info);
		~GeneralManager() override = default;

		inline std::wstring GetRoleName() const override { return L"����"; }
	};

	class Director : public Employee
	{
	public:
		Director(const FEmployeeInfo& Info);
		~Director() override = default;

		inline std::wstring GetRoleName() const override { return L"�̻�"; }
	};
}
