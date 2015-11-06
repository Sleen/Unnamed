#include <iostream>
#include <iomanip>
#include <cmath>

#include "Unnamed.hpp"
#include "String.hpp"
#include "Base/System.hpp"

using namespace unnamed;

void dump(const String& str) {
    std::cout<<str.Utf8String()<<" {"<<str.length()<<"}  ";
    for (int i=0;i<str.length();i++) {
        std::cout<<std::hex<<std::uppercase<<std::setw((int)ceil(log2(str.CharAt(i))/8)*2)<<std::setfill('0')<<str.CharAt(i)<<" ";
    }
    std::cout<<std::dec<<std::nouppercase<<std::endl;
}

class TestApp : Application
{
public:
	TestApp() {}
	~TestApp() {}
	void OnStart() {
		std::cout<<"OnStart"<<std::endl;
        
        dump(String(1));
        dump(String((int8_t)1));
        dump(String((uint8_t)1));
        dump(String('1'));
        dump(String(String("123")==String("12")+"3"));
        dump(String(String("123")==String("1234")));
        dump(String(String("12345").StartsWith(String("1234"))));
        dump(String(String("12345") == String(1123456).Substring(1, 5)));
        dump(String("   ").Trim());
        std::cout<<String("abcdef").IndexOf('c')<<std::endl;
        std::cout<<String("123测试文字").IndexOf(U'文')<<std::endl;
        std::cout<<String("aabbababaaababbba").IndexOf(String("aab"), 1)<<std::endl;
	}
	void OnExit() { std::cout<<"OnExit"<<std::endl; }
};

TestApp app;
