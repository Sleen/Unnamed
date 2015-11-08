#include "Time.hpp"

#include "Base/System.hpp"

namespace unnamed {
    static double lastTime_ = 0;
    static double deltaTime_ = 0;
    static double startTime_ = 0;

    static int frames_ = 0;
    static double times_ = 0;
    static float fps_ = 0;

    void Time::UpdateTime() {
        double time = me::System::GetTime();

        if (startTime_ == 0) {
            startTime_ = time;
            lastTime_ = time;
            return;
        }

        deltaTime_ = time - lastTime_;
        lastTime_ = time;

        frames_++;
		if ((times_ += deltaTime_) > 0.2f){
			fps_ = frames_ / times_;
			times_ = 0.0f;
			frames_ = 0;
		}
    }
    
    double Time::DeltaTime() {
        return deltaTime_;
    }
    
    double Time::TimeSinceStart() {
        return me::System::GetTime() - startTime_;
    }

    float Time::FPS() {
        return fps_;
    }

}
