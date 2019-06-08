#pragma once

#ifdef JN_PLATFORM_WINDOWS

extern Jona::Application* Jona::CreateApplication();

int main(int argc, char** argv) 
{
	Jona::Log::Init();
	JN_CORE_WARN("Initialized Log!");
	int a = 5;
	JN_INFO("Hello! Var={0}", a);

	auto app = Jona::CreateApplication();
	app->Run();
	delete app;
}

#endif