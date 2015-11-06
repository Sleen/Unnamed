#pragma once

namespace me {

	class Math {
	public:
		static const double PI;
		
		template<typename T>
		inline static T Max(T a, T b) {
			return a > b ? a : b;
		}

		template<typename T>
		inline static T Min(T a, T b) {
			return a < b ? a : b;
		}
	};

}
