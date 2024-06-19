#pragma once
#include "TGUI_Base.h"
#include "Component/Manager/Manager.h"

namespace LJG
{
	
	class TGUI_Docking : public TGUI_Base, public TSingleton<TGUI_Docking>
	{

	public:

	private:
		friend class TSingleton<TGUI_Docking>;
		TGUI_Docking();
	};
}
