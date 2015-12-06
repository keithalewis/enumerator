// timer.t - timer
#pragma once
#include <chrono>

namespace timer {

	template<class T = std::chrono::high_resolution_clock>
	class clock {
		typename T::time_point t0, t1;
	public:
		void start()
		{
			t0 = T::now();
		}
		void stop()
		{
			t1 = T::now();
		}
		template<class D = std::chrono::duration<unsigned long long, std::milli>>
		auto count()
		{
			return std::chrono::duration_cast<D>(t1 - t0).count();
		}
	};
	template<class F, class T = std::chrono::high_resolution_clock,
		class D = std::chrono::duration<unsigned long long, std::milli>>
	inline auto time(const F& f, size_t n = 1)
	{
		clock<T> c;

		c.start();
		while (n--)
			f();
		c.stop();

		return c.count<D>();
	}

} // timer