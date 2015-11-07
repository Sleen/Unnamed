#include "ConsoleApplication.hpp"

#include <cstdlib>

namespace unnamed {
    
    static ConsoleApplication* instance = nullptr;
    
    ConsoleApplication::ConsoleApplication() {
        instance = this;
    }
    
    ConsoleApplication::~ConsoleApplication() {}
    
    ConsoleApplication* ConsoleApplication::GetInstance() {
        return instance;
    }
    
    void ConsoleApplication::Exit() {
        OnExit();
        exit(0);
    }
    
    void ConsoleApplication::SetArgs(char const *argv[], int argc) {
        for (int i=0;i<argc;i++) {
            args_.push_back(argv[i]);
        }
    }
    
}
