#include "jnpch.h"
#include "Application.h"

#include "Jona/Events/ApplicationEvent.h"
#include "Jona/Log.h"

namespace Jona {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			JN_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{

			JN_TRACE(e);
		}

		while (true);
	}

}