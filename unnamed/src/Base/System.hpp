#pragma once

#include <cstdint>
#include <string>

namespace me{

	enum class Unit {
		Px,		// pixels
		Dp,		// device independent pixels, 1dp = 1/160in
		Mm,		// millimeters
		Cm,		// centimeters
		In,		// inches, 1in = 25.4mm
		Pt		// points, 1pt = 1/72in
	};

class System{
private:
	static float ratios[6];

public:
	static std::string GetSystemVersion();
	static int64_t GetMicroSecond();
    static double GetTime();
	static inline int64_t GetMilliSecond() { return GetMicroSecond() / 1000; }
	static float GetScreenDpi() { return 100; } // TODO
	static float ToPixel(float value, Unit unit) {
		return value*ratios[(int)unit];
	}
};

}
