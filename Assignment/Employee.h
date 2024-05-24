#pragma once
#include <string>

namespace Assignment1
{
	enum class EEmployeeType
	{
		None,
		Staff,             // 사원
		AssignmentManager, // 대리
		Manager,           // 과장
		GeneralManager,    // 부장
		Director           //이사
	};


	enum class ESalaryType
	{
		None,
		Hour,  // 시급
		Month, //월급
		Year   // 연봉
	};

	struct FEmployeeInfo
	{
		std::wstring Name;
		ESalaryType  SalaryType = ESalaryType::None; // 급여 지급 방식
		int          Year       = 0;                 // 년차
		int          Grade      = 0;                 // 능력 등급
		int          WorkHour   = 0;                 // 월 근무 시간
	};

	// Base class (순수 가상 클래스)
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
		int           mSalary; // 월급 기준 급여  (만원 단위)
	};


	//-----------------------  사원  ------------------------------
	class Staff : public Employee
	{
	public:
		Staff(const FEmployeeInfo& Info);
		~Staff() override = default;

		inline std::wstring GetRoleName() const override { return L"사원"; }
	};

	//-----------------------  대리  ------------------------------
	class AssignmentManager : public Employee
	{
	public:
		AssignmentManager(const FEmployeeInfo& Info);
		~AssignmentManager() override = default;

		inline std::wstring GetRoleName() const override { return L"대리"; }
	};

	class Manager : public Employee
	{
	public:
		Manager(const FEmployeeInfo& Info);
		~Manager() override = default;

		inline std::wstring GetRoleName() const override { return L"과장"; }
	};

	class GeneralManager : public Employee
	{
	public:
		GeneralManager(const FEmployeeInfo& Info);
		~GeneralManager() override = default;

		inline std::wstring GetRoleName() const override { return L"부장"; }
	};

	class Director : public Employee
	{
	public:
		Director(const FEmployeeInfo& Info);
		~Director() override = default;

		inline std::wstring GetRoleName() const override { return L"이사"; }
	};
}
