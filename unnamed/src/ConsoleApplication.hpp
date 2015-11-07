#pragma once
#include <vector>
#include <string>

namespace unnamed {
    class ConsoleApplication {
    public:
        ConsoleApplication();
        virtual ~ConsoleApplication();
        static ConsoleApplication* GetInstance();
        //virtual AppOptions* Options();
        virtual void OnStart() {}
        virtual void OnExit() {}
        virtual void Exit();
        virtual void Run() {}
        const std::vector<std::string>& Args() { return args_; }
        void SetArgs(char const *argv[], int argc);
        
    private:
        std::vector<std::string> args_;
    };
}
