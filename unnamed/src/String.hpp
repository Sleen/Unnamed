#pragma once

#include <string>
#include <vector>

namespace unnamed {

class String {
public:
    String() {}
    explicit String(const char* str);
    explicit String(const std::string& str) : String(str.c_str()) {}
    explicit String(const char16_t* str);
    explicit String(const std::u16string& str) : String(str.c_str()) {}
    explicit String(const char32_t* str);
    explicit String(const std::u32string& str) : String(str.c_str()) {}
    explicit String(int64_t value);
    explicit String(uint64_t value);
    explicit String(int32_t value);
    explicit String(uint32_t value);
    explicit String(int16_t value);
    explicit String(uint16_t value);
    explicit String(int8_t value);
    explicit String(uint8_t value);
    explicit String(float value);
    explicit String(double value);
    explicit String(bool value);
    explicit String(char c);
    explicit String(char16_t c);
    explicit String(char32_t c);
    String(const String& str);
    String& operator=(String str);
    ~String();
    size_t length() const { return length_; }
    char32_t CharAt(size_t index) const;
    std::string Utf8String() const;
    std::u16string Utf16String() const;
    std::u32string Utf32String() const;
    void Swap(String& str);
    String operator+(const String& s) const;
    String operator+(const char* s) const;
    String operator+(const char16_t* s) const;
    String operator+(const char32_t* s) const;
    String operator+(const std::string& s) const;
    String operator+(const std::u16string& s) const;
    String operator+(const std::u32string& s) const;
    String operator+(int64_t value) const;
    String operator+(uint64_t value) const;
    String operator+(int32_t value) const;
    String operator+(uint32_t value) const;
    String operator+(int16_t value) const;
    String operator+(uint16_t value) const;
    String operator+(int8_t value) const;
    String operator+(uint8_t value) const;
    String operator+(float value) const;
    String operator+(double value) const;
    String operator+(bool value) const;
    String operator+(char value) const;
    String operator+(char16_t value) const;
    String operator+(char32_t value) const;
    String& operator+=(const String& s);
    String& operator+=(const char* s);
    String& operator+=(const char16_t* s);
    String& operator+=(const char32_t* s);
    String& operator+=(const std::string& s);
    String& operator+=(const std::u16string& s);
    String& operator+=(const std::u32string& s);
    String& operator+=(int64_t value);
    String& operator+=(uint64_t value);
    String& operator+=(int32_t value);
    String& operator+=(uint32_t value);
    String& operator+=(int16_t value);
    String& operator+=(uint16_t value);
    String& operator+=(int8_t value);
    String& operator+=(uint8_t value);
    String& operator+=(float value);
    String& operator+=(double value);
    String& operator+=(bool value);
    String& operator+=(char value);
    String& operator+=(char16_t value);
    String& operator+=(char32_t value);
    bool operator==(const String& s) const;
    bool operator!=(const String& s) const;
    String Substring(size_t start, size_t length) const;
    String Substring(size_t start) const;
    bool StartsWith(const String& s) const;
    bool EndsWith(const String& s) const;
    String ToLower() const;
    String ToUpper() const;
    String TrimStart(const String& chars) const;
    String TrimEnd(const String& chars) const;
    String Trim(const String& chars) const;
    String TrimStart() const { return TrimStart(BlankCharacters()); }
    String TrimEnd() const { return TrimEnd(BlankCharacters()); }
    String Trim() const { return Trim(BlankCharacters()); }
    int IndexOf(char32_t c, size_t startIndex = 0) const;
    int IndexOf(const String& s, size_t startIndex = 0) const;
    int LastIndexOf(char32_t c) const;
    int LastIndexOf(const String& s) const;
    String Replace(char32_t oldChar, char32_t newChar, size_t startIndex = 0) const;
    String Replace(const String& oldStr, const String& newStr, size_t startIndex = 0) const;
    String ReplaceAll(char32_t oldChar, char32_t newChar, size_t startIndex = 0) const;
    String ReplaceAll(const String& oldStr, const String& newStr, size_t startIndex = 0) const;
    std::vector<String> Split(char32_t c, bool removeEmpty = false) const;
    std::vector<String> Split(const String& chars, bool removeEmpty = false) const;
    String Reverse() const;
    
private:
    static const String& BlankCharacters();
    
    int GetByteIndex(size_t index) const;
    
    char* data_ = nullptr;
    size_t length_ = 0;
    size_t byteLength_ = 0;
    mutable size_t lastIndex_ = 0;      // used to make CharAt() faster
    mutable int lastByteIndex_ = 0;     // used to make CharAt() faster
    mutable size_t* next_ = nullptr;    // used to make IndexOf() faster with KMP algorithm
};
    
    String operator+(const char* lh, const String& rh);
    String operator+(const char16_t* lh, const String& rh);
    String operator+(const char32_t* lh, const String& rh);
    String operator+(const std::string& lh, const String& rh);
    String operator+(const std::u16string& lh, const String& rh);
    String operator+(const std::u32string& lh, const String& rh);
    String operator+(int64_t lh, const String& rh);
    String operator+(uint64_t lh, const String& rh);
    String operator+(int32_t lh, const String& rh);
    String operator+(uint32_t lh, const String& rh);
    String operator+(int16_t lh, const String& rh);
    String operator+(uint16_t lh, const String& rh);
    String operator+(int8_t lh, const String& rh);
    String operator+(uint8_t lh, const String& rh);
    String operator+(float lh, const String& rh);
    String operator+(double lh, const String& rh);
    String operator+(bool lh, const String& rh);
    String operator+(char lh, const String& rh);
    String operator+(char16_t lh, const String& rh);
    String operator+(char32_t lh, const String& rh);
    
}
