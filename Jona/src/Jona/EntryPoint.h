#pragma once

#ifdef JN_PLATFORM_WINDOWS

extern Jona::Application* Jona::CreateApplication();

int main(int argc, char** argv) 
{
	auto app = Jona::CreateApplication();
	app->Run();
	delete app;
}

#endif