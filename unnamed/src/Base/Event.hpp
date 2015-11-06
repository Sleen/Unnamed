#pragma once

#include <functional>
#include <map>

namespace me {

	template<typename... Args>
	class Action {
	protected:
		using FUN = std::function<void(Args...)>;
		int handlerID;
		std::map<int, FUN> m;
	public:
		int operator+=(FUN f) {
			m.insert(std::pair<int, FUN>(++handlerID, f));
			return handlerID;
		}

		template<class Sender>
		int add(Sender *s, void (Sender::*f)(Args...)) {
			m.insert(std::pair<int, FUN>(++handlerID, [s, f](Args... args) {(*s.*f)(args...); }));//forward<Args>(args)...);}));
			return handlerID;
		}

		bool empty() const {
			return m.empty();
		}

		void operator-=(int id) {
			m.erase(id);
		}

		void clear() {
			m.clear();
		}

		void operator()(Args... args) {
			for (auto& f : m)
				f.second(args...);//forward<Args>(args)...);
		}
	};

	template<typename Sender, typename... Args>
	class Event : public Action<Sender&, Args...> {
	protected:
		using FUN = std::function<void(Sender&, Args...)>;
		using Action<Sender&, Args...>::m;
		using Action<Sender&, Args...>::handlerID;
	public:
		int add(Sender *s, void (Sender::*f)(Sender&, Args...)) {
			m.insert(std::pair<int, FUN>(++handlerID, [s, f](Sender& ss, Args... args) {(*s.*f)(ss, args...); }));//forward<Sender&>(ss), forward<Args>(args)...);}));
			return handlerID;
		}
	};

}
