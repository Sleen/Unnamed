#include "Application.hpp"
#include <iostream>
#include <locale>

int main(int argc, char const *argv[])
{
	setlocale(LC_ALL, "");
	
	unnamed::Application* instance = unnamed::Application::GetInstance();
	
	if (!instance) {
		std::cerr<<"there's no instance of Application"<<std::endl;
	}

	instance->OnStart();
	instance->Run();
	instance->OnExit();

	return 0;
}