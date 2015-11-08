#pragma once

#include "Base/System.hpp"

namespace unnamed {

    class Time
    {
    public:
        Time() = delete;
        ~Time() = delete;
        static void UpdateTime();
        static double DeltaTime();
        static double TimeSinceStart();
        static float FPS();

    };

}
