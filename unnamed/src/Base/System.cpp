#include "System.hpp"

#ifdef _WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	undef WIN32_LEAN_AND_MEAN
#else
extern "C" {
#	define __lint__
#	include <sys/time.h>
}

#endif

namespace me {
    
    double System::GetTime() {
#ifdef _WIN32
        static int64_t freq = 0;
        if (freq == 0) {
            LARGE_INTEGER f;
            QueryPerformanceFrequency(&f);
            freq = f.QuadPart;
        }
        LARGE_INTEGER perf;
        QueryPerformanceCounter(&perf);
        return (double)perf.QuadPart / freq;
#else
        struct timeval tv = { 0 };
        gettimeofday(&tv, NULL);
        return tv.tv_sec + (double)tv.tv_usec / 1000000.0;
#endif
    }
    
	int64_t System::GetMicroSecond()
	{
#ifdef _WIN32
		static int64_t freq = 0;
		if (freq == 0) {
			LARGE_INTEGER f;
			QueryPerformanceFrequency(&f);
			freq = f.QuadPart;
		}
		LARGE_INTEGER perf;
		QueryPerformanceCounter(&perf);
		return perf.QuadPart * 1000000 / freq;
#else
		struct timeval tv = { 0 };
		gettimeofday(&tv, NULL);
		return tv.tv_sec * 1000000 + tv.tv_usec;
#endif
	}

}
