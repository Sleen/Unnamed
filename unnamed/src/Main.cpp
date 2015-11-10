#include "ConsoleApplication.hpp"
#include <iostream>
#include <locale>

int main(int argc, char const *argv[])
{
	setlocale(LC_ALL, "");
    
	unnamed::ConsoleApplication* instance = unnamed::ConsoleApplication::GetInstance();
	
	if (!instance) {
		std::cerr<<"there's no instance of Application"<<std::endl;
	}

    instance->SetArgs(argv, argc);
	instance->OnStart();
	instance->Run();
	instance->OnExit();

	return 0;
}