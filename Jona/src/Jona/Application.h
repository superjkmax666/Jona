#pragma once

#include "Core.h"

namespace Jona {

	class JONA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in Client
	Application* CreateApplication();

}
