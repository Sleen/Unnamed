#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <exception>
#include <functional>

#include "Base/Exception.hpp"
#include "Base/StringHelper.hpp"
#include "Base/Log.hpp"
#include "Base/System.hpp"

namespace me {

    namespace unit_test {
    
	class Tests;

	class TestFailed {
	protected:
		std::string what;
		std::string where;

	public:
		TestFailed() {
			what = "unknown error";
			where = "unknown position";
		}

		TestFailed(const std::string& what, const std::string& where) {
			this->what = what;
			this->where = where;
		}

		const std::string& What() const {
			return what;
		}

		const std::string& Where() const {
			return where;
		}
	};

	class Test {
	private:
		std::string name;
		TestFailed err;
		std::function<void()> fun;

	public:
		Test(Tests* tests, const std::string& name, std::function<void()> fun);

		const std::string& GetName() const {
			return name;
		}

		const TestFailed& GetError() const {
			return err;
		}

		bool Run() {
			try {
				fun();
			}
			catch (const TestFailed& err) {
				this->err = err;
				return false;
			}
			catch (const Exception& ex) {
				this->err = TestFailed(ex.What(), ex.Where());
				return false;
			}
			catch (...) {
				return false;
			}

			return true;
		}
	};
        
        class Benchmark {
        private:
            std::string name;
            std::function<void()> fun;
            size_t iterations;
            double time;
        public:
            Benchmark(Tests* tests, const std::string& name, size_t iterations, std::function<void()> fun);
            
            const std::string& GetName() const {
                return name;
            }
            
            void Run() {
                if (iterations <= 0) {
                    iterations = 1;
                }
                
                try {
                    double start = System::GetTime();
                    for (int i=0;i<iterations;i++) {
                        fun();
                    }
                    double end = System::GetTime();
                    time = (end - start) / iterations;
                }
                catch (...) {
                    time = -1;
                }
            }
            
            std::string GetTimeString() const {
                if (time < 0) {
                    return "error";
                }
                
                return StringHelper::Format("%.5f ms", time * 1000);
            }
        };

	class Tests {
	private:
		std::string name;
        std::vector<Test*> tests;
        std::vector<Benchmark*> benchmarks;

	public:
		Tests(const std::string& name) {
			this->name = name;
		}

		bool RunAll() {
			std::vector<Test*> failed;
            const char* passedText = " passed ";
            const char* failedText = "*FAILED*";
//            const size_t minWidth = 20;
//            const size_t maxWidth = 60;
//            size_t width = minWidth;
//            
//            for (auto& test : tests) {
//                width = std::min(maxWidth, std::max(width, test->GetName().length()));
//                if (width == maxWidth) break;
//            }
//            
//            for (auto& benchmark : benchmarks) {
//                width = std::min(maxWidth, std::max(width, benchmark->GetName().length()));
//                if (width == maxWidth) break;
//            }
            size_t width = 60;
            
            Log::V("+%s+", StringHelper::FillLeft("", width + 20, "-").c_str());
            
            Log::V("|%s|", StringHelper::FillCenter(StringHelper::FillCenter(name.length() > width + 16 ? StringHelper::FillLeft(name, width + 16) : name, name.length() + 4), width + 20, "#").c_str());
            if (tests.size() > 0) {
                Log::V("|%s|", StringHelper::FillCenter("", width + 20, "-").c_str());
                for (auto& test : tests) {
                    bool passed = test->Run();
                    if (!passed) {
                        failed.push_back(test);
                    }
                    Log::V("|  %s  %15s |", StringHelper::FillLeft(test->GetName(), width).c_str(), passed ? passedText : failedText);
                }
            }
            if (benchmarks.size() > 0) {
                Log::V("|%s|", StringHelper::FillCenter("", width + 20, "-").c_str());
                for (auto& benchmark : benchmarks) {
                    benchmark->Run();
                    Log::V("|  %s  %14s  |", StringHelper::FillLeft(benchmark->GetName(), width).c_str(), benchmark->GetTimeString().c_str());
                }
            }
            Log::V("|%s|", StringHelper::FillLeft("", width + 20, "-").c_str());

            size_t testsWidth = (width + 6) / 3;
            size_t benchmarksWidth = ((width + 6) - testsWidth) / 2;
            size_t resultWidth = (width + 6) - testsWidth - benchmarksWidth;
            
            std::string testsCount = me::StringHelper::ToString(tests.size()) + " Tests";
            std::string benchmarksCount = me::StringHelper::ToString(benchmarks.size()) + " Benchmarks";
            std::string result = failed.empty() ? "All Passed" : (me::StringHelper::ToString(failed.size()) + " Failed");
            Log::V("|  %s  |  %s  |  %s  |",
                   StringHelper::FillCenter(testsCount, testsWidth).c_str(),
                   StringHelper::FillCenter(benchmarksCount, benchmarksWidth).c_str(),
                   StringHelper::FillCenter(result, resultWidth).c_str());

            for (auto& t : failed) {
                Log::V("|%s|", StringHelper::FillCenter("", width + 20, "-").c_str());
                std::string s = t->GetName() + ": [" + t->GetError().Where() + "] " + t->GetError().What();
                auto lines = StringHelper::LineWrap(s, width + 16);
                for (auto& l : lines) {
                    Log::V("|  %s  |", StringHelper::FillLeft(l, width + 16).c_str());
                }
			}
            
            Log::V("+%s+", StringHelper::FillLeft("", width + 20, "-").c_str());
            Log::V("");
            Log::V("");

			return failed.empty();
		}
        
		void AddTest(Test* test) {
			tests.push_back(test);
        }
        
        void AddBenchmark(Benchmark* benchmark) {
            benchmarks.push_back(benchmark);
        }
	};
        
	Test::Test(Tests* tests, const std::string& name, std::function<void()> fun) {
        this->name = StringHelper::Trim(name, " \"");
		this->fun = fun;
		tests->AddTest(this);
	}
        
    Benchmark::Benchmark(Tests* tests, const std::string& name, size_t iterations, std::function<void()> fun) {
        this->name = StringHelper::Trim(name, " \"");
        this->fun = fun;
        this->iterations = iterations;
        tests->AddBenchmark(this);
    }
        
    }

#define BEGIN_TESTS(name) \
namespace TOKENPASTE2(tests_ns_, __COUNTER__) { \
class Tests : public me::unit_test::Tests{ \
public: \
    Tests() : me::unit_test::Tests(#name){ RunAll(); }
    
#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
    
#define END_TESTS() } test;}

#define TEST(name) TEST_(TOKENPASTE2(test_func_, __COUNTER__), name)
#define TEST_(id, name) \
    me::unit_test::Test TOKENPASTE2(test_, __COUNTER__) = me::unit_test::Test(this, #name, std::bind(&std::remove_pointer<decltype(this)>::type::id, this)); \
void id()

#define BENCHMARK(name, iterations) BENCHMARK_(TOKENPASTE2(benc_func_, __COUNTER__), name, iterations)
#define BENCHMARK_(id, name, iterations) \
me::unit_test::Benchmark TOKENPASTE2(benc_, __COUNTER__) = me::unit_test::Benchmark(this, #name, iterations, std::bind(&std::remove_pointer<decltype(this)>::type::id, this)); \
void id()
    
#define UNIT_TEST_THROW(message) throw me::unit_test::TestFailed(message, std::string(__FILE__) + " (" + me::StringHelper::ToString(__LINE__) + ")")

#define CHECK_EQUAL(a, b) \
try{ \
    if (a == b) {} \
    else { UNIT_TEST_THROW("equal check failed."); } \
} \
catch (const me::unit_test::TestFailed& ex){ \
    throw ex; \
} \
catch (const Exception& ex){ \
    UNIT_TEST_THROW(ex.What()); \
} \
catch (...){ \
    UNIT_TEST_THROW("unhandled exception"); \
}

#define CHECK(exp) \
try{ \
    if (!(exp)) { UNIT_TEST_THROW("check failed."); } \
} \
catch (const me::unit_test::TestFailed& ex){ \
    throw ex; \
} \
catch (const Exception& ex){ \
    UNIT_TEST_THROW(ex.What()); \
} \
catch (...){ \
    UNIT_TEST_THROW("unhandled exception"); \
}

#define CHECK_THROW(code, throwType) \
try{ \
    try{ \
        code; \
    }catch(throwType){ \
        throw "OK"; \
    }catch(const Exception& ex){ \
        UNIT_TEST_THROW(ex.What()); \
    }catch(...){ \
        UNIT_TEST_THROW("throw check failed"); \
    } \
    UNIT_TEST_THROW("throw check failed, no exception thrown."); \
}catch(const me::unit_test::TestFailed& ex){ \
    throw ex; \
}catch(...){ }

#define CHECK_NO_THROW(code) \
try{ \
    code; \
}catch(const Exception& ex){ \
    UNIT_TEST_THROW(ex.What()); \
}catch(...){ \
    UNIT_TEST_THROW("no-throw check failed"); \
}

#define CHECK_NOT_NULL(exp) \
try{ \
    if (exp == nullptr) { UNIT_TEST_THROW("not-null check failed."); } \
} \
catch (const me::unit_test::TestFailed& ex){ \
    throw ex; \
} \
catch (const Exception& ex){ \
    UNIT_TEST_THROW(ex.What()); \
} \
catch (...){ \
    UNIT_TEST_THROW("unhandled exception"); \
}

#define CHECK_NULL(exp) \
try{ \
    if (exp != nullptr) { UNIT_TEST_THROW("null check failed."); } \
} \
catch (const me::unit_test::TestFailed& ex){ \
    throw ex; \
} \
catch (const Exception& ex){ \
    UNIT_TEST_THROW(ex.What()); \
} \
catch (...){ \
    UNIT_TEST_THROW("unhandled exception"); \
}

#define CHECK_COUT(code, text) \
{ \
    auto buf = std::cout.rdbuf(); \
    std::stringstream ss; \
    std::cout.rdbuf(ss.rdbuf()); \
    try{ \
        code; \
    } \
    catch (const Exception& ex){ \
        std::cout.rdbuf(buf); \
        UNIT_TEST_THROW(ex.What()); \
    } \
    catch (...){ \
        std::cout.rdbuf(buf); \
        UNIT_TEST_THROW("unhandled exception"); \
    } \
    std::cout.rdbuf(buf); \
    if (ss.str() != text){ \
        UNIT_TEST_THROW(std::string("cout check failed. expected: '") + text + "', actual: '" + ss.str() + "'"); \
    } \
}

}
