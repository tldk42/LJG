#pragma once
#include "../XVertex2D.h"


namespace LJG
{
	/** */
	class XDebugShape2D : public XVertex2D
	{
	public:
		XDebugShape2D();
		~XDebugShape2D() override = default;

		void Render() override;
	};
}
