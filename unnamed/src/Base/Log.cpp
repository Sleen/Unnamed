#include "Log.hpp"

#include <ctime>
#include <iostream>

#ifdef __ANDROID__
#	include <android/log.h>
#endif

namespace me {

	static std::string rankNames[] = { "       ", "[Debug]", "[Info] ", "[Warn] ", "[Error]", "[Fatal]" };

	void Log::log(LogPriority priority, const std::string & text)
	{
		time_t t;
		time(&t);
		tm* pt = localtime(&t);
		static time_t last_time = 0;
		std::string time_str = t == last_time ? "        " : StringHelper::Format("%02d:%02d:%02d", pt->tm_hour, pt->tm_min, pt->tm_sec);
		last_time = t;
#ifdef __ANDROID__
		__android_log_write(rank + ANDROID_LOG_VERBOSE, "me", text.c_str());
#else
		std::cout << time_str << " " << rankNames[priority] << " " << text << std::endl;
#endif
	}

}
