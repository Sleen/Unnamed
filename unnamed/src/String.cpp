#include "String.hpp"

#include <sstream>

namespace unnamed {

String::String(const char* str, StringEncoding encoding) {
    if (encoding == StringEncoding::Utf8) {
        byteLength_ = strlen(str);
        data_ = new char[byteLength_ + 1];
        memcpy(data_, str, byteLength_ + 1);
        int n = 0;
        for (int i=0;i<byteLength_;i++) {
            char c = data_[i];
            if (n > 0) {
                if (((c >> 6) & 0x03) != 0x02) { // ! 10xxxxxx
                    // error
                    printf("'%s' is not a valid utf8 string\n", str);
                    return;
                }
                n--;
            } else {
                length_++;
                if (((c >> 7) & 0x01) == 0x00) {		// 0xxxxxxx
                    
                } else if (((c >> 5) & 0x07) == 0x06) {	// 110xxxxx
                    n = 1;
                } else if (((c >> 4) & 0x0F) == 0x0E) {	// 1110xxxx
                    n = 2;
                } else if (((c >> 3) & 0x1F) == 0x1E) {	// 11110xxx
                    n = 3;
                } else if (((c >> 2) & 0x3F) == 0x3E) {	// 111110xx
                    n = 4;
                } else if (((c >> 1) & 0x7F) == 0x7E) {	// 1111110x
                    n = 5;
                } else {
                    // error
                    printf("'%s' is not a valid utf8 string\n", str);
                    return;
                }
            }
        }
        if (n > 0) {
            // error
            printf("'%s' is not a valid utf8 string\n", str);
            return;
        }
    }
}

String::String(const char16_t* str) {
    size_t len = std::char_traits<char16_t>::length(str);
    std::vector<char> vec;
    bool surrogate = false;
    for (int i=0;i<len;i++) {
        char16_t c = str[i];
        if (surrogate) {
            if (((c >> 10) & 0x3F) == 0x37) {		// 110111xxxxxxxxxx
                char32_t chr = (((str[i-1] & 0x03FF) << 10) | (c & 0x03FF)) + 0x10000;
                vec.push_back(((chr >> 18) & 0x07) | 0xF0);	// 11110xxx
                vec.push_back(((chr >> 12) & 0x3F) | 0x80);	// 10xxxxxx
                vec.push_back(((chr >> 6) & 0x3F) | 0x80);	// 10xxxxxx
                vec.push_back((chr & 0x3F) | 0x80);			// 10xxxxxx
                length_++;
            } else {
                // error
                printf("not a valid utf16 string (low surrogate expected)\n");
                return;
            }
            surrogate = false;
        } else {
            if (((c >> 10) & 0x3F) == 0x36) {		// 110110yyyyyyyyyy
                surrogate = true;
            } else if (((c >> 10) & 0x3F) == 0x37) {	// 110111xxxxxxxxxx
                // error
                printf("not a valid utf16 string (high surrogate expected)\n");
                return;
            } else {
                if (c <= 0x7F) {
                    vec.push_back(c);
                } else if (c <= 0x7FF) {
                    vec.push_back(((c >> 6) & 0x1F) | 0xC0);	// 110xxxxx
                    vec.push_back((c & 0x3F) | 0x80);			// 10xxxxxx
                } else {
                    vec.push_back(((c >> 12) & 0x0F) | 0xE0);	// 1110xxxx
                    vec.push_back(((c >> 6) & 0x3F) | 0x80);	// 10xxxxxx
                    vec.push_back((c & 0x3F) | 0x80);			// 10xxxxxx
                }
                length_++;
            }
        }
    }
    if (surrogate) {
        // error
        printf("an incomplete utf16 string, (low surrogate expected)\n");
        return;
    }
    byteLength_ = vec.size();
    vec.push_back(0);
    data_ = new char[byteLength_ + 1];
    memcpy(data_, vec.data(), byteLength_ + 1);
}

String::String(const char32_t* str) {
    length_ = std::char_traits<char32_t>::length(str);
    std::vector<char> vec;
    for (int i=0;i<length_;i++) {
        char32_t c = str[i];
        if (c <= 0x7F) {
            vec.push_back(c);
        } else if (c <= 0x7FF) {
            vec.push_back(((c >> 6) & 0x1F) | 0xC0);	// 110xxxxx
            vec.push_back((c & 0x3F) | 0x80);			// 10xxxxxx
        } else if (c <= 0xFFFF) {
            vec.push_back(((c >> 12) & 0x0F) | 0xE0);	// 1110xxxx
            vec.push_back(((c >> 6) & 0x3F) | 0x80);	// 10xxxxxx
            vec.push_back((c & 0x3F) | 0x80);			// 10xxxxxx
        } else if (c <= 0x1FFFFF) {
            vec.push_back(((c >> 18) & 0x07) | 0xF0);	// 11110xxx
            vec.push_back(((c >> 12) & 0x3F) | 0x80);	// 10xxxxxx
            vec.push_back(((c >> 6) & 0x3F) | 0x80);	// 10xxxxxx
            vec.push_back((c & 0x3F) | 0x80);			// 10xxxxxx
        } else if (c <= 0x3FFFFFF) {
            vec.push_back(((c >> 24) & 0x03) | 0xF8);	// 111110xx
            vec.push_back(((c >> 18) & 0x3F) | 0x80);	// 10xxxxxx
            vec.push_back(((c >> 12) & 0x3F) | 0x80);	// 10xxxxxx
            vec.push_back(((c >> 6) & 0x3F) | 0x80);	// 10xxxxxx
            vec.push_back((c & 0x3F) | 0x80);			// 10xxxxxx
        } else {
            vec.push_back(((c >> 30) & 0x01) | 0xFC);	// 1111110x
            vec.push_back(((c >> 24) & 0x3F) | 0x80);	// 10xxxxxx
            vec.push_back(((c >> 18) & 0x3F) | 0x80);	// 10xxxxxx
            vec.push_back(((c >> 12) & 0x3F) | 0x80);	// 10xxxxxx
            vec.push_back(((c >> 6) & 0x3F) | 0x80);	// 10xxxxxx
            vec.push_back((c & 0x3F) | 0x80);			// 10xxxxxx
        }
    }
    byteLength_ = vec.size();
    vec.push_back(0);
    data_ = new char[byteLength_ + 1];
    memcpy(data_, vec.data(), byteLength_ + 1);
}

String::String(int64_t value) {
    std::stringstream ss;
    ss << value;
    String s(ss.str());
    Swap(s);
}

String::String(uint64_t value) {
    std::stringstream ss;
    ss << value;
    String s(ss.str());
    Swap(s);
}

String::String(int32_t value) {
    std::stringstream ss;
    ss << value;
    String s(ss.str());
    Swap(s);
}

String::String(uint32_t value) {
    std::stringstream ss;
    ss << value;
    String s(ss.str());
    Swap(s);
}

String::String(int16_t value) {
    std::stringstream ss;
    ss << value;
    String s(ss.str());
    Swap(s);
}

String::String(uint16_t value) {
    std::stringstream ss;
    ss << value;
    String s(ss.str());
    Swap(s);
}

String::String(int8_t value) : String((uint16_t)value) {
}

String::String(uint8_t value) : String((uint16_t)value) {
}

String::String(float value) {
    std::stringstream ss;
    ss << value;
    String s(ss.str());
    Swap(s);
}

String::String(double value) {
    std::stringstream ss;
    ss << value;
    String s(ss.str());
    Swap(s);
}

String::String(bool value) {
    String boolString(value ? "true" : "false");
    Swap(boolString);
}

String::String(char c) {
    char s[] = {c, 0};
    String str(s);
    Swap(str);
}

String::String(char16_t c) {
    char16_t s[] = {c, 0};
    String str(s);
    Swap(str);
}

String::String(char32_t c) {
    char32_t s[] = {c, 0};
    String str(s);
    Swap(str);
}
    
String::String(const String& str) {
    if (str.length_ == 0) return;
    length_ = str.length_;
    byteLength_ = str.byteLength_;
    data_ = new char[byteLength_ + 1];
    lastIndex_ = str.lastIndex_;
    lastByteIndex_ = str.lastByteIndex_;
    memcpy(data_, str.data_, byteLength_ + 1);
}

String::~String() {
    if (data_) {
        delete[] data_;
    }
    
    if (next_) {
        delete[] next_;
    }
}

String& String::operator=(String str) {
    Swap(str);
    return *this;
}

int String::GetByteIndex(size_t index) const {
    if (index == 0) {
        return 0;
    } else if (index >= length_) {
        return byteLength_;
    } else if (index == lastIndex_) {
        return lastByteIndex_;
    }
    
    int i;
    int start;
    bool ascend;
    int n;
    if (index < lastIndex_ / 2) {
        start = 1;
        ascend = true;
        n = index;
    } else if (index < lastIndex_) {
        start = lastByteIndex_ - 1;
        ascend = false;
        n = lastIndex_ - index;
    } else if (index < length_ / 2 + lastIndex_ / 2) {
        start = lastByteIndex_ + 1;
        ascend = true;
        n = index - lastIndex_;
    } else {
        start = byteLength_ - 1;
        ascend = false;
        n = length_ - index;
    }
    
    if (ascend) {
        for (i = start; i < byteLength_; i++) {
            if (((data_[i] >> 6) & 0x03) != 0x02) n--;
            if (n == 0) break;
        }
    } else {
        for (i = start; i >= 0; i--) {
            if (((data_[i] >> 6) & 0x03) != 0x02) n--;
            if (n == 0) break;
        }
    }

    lastIndex_ = index;
    lastByteIndex_ = i;
    return i;
}

char32_t String::CharAt(size_t index) const {
    char32_t r = 0;
    if (index >= length_)
        return r;
    
    int i = GetByteIndex(index);
    char c = data_[i];
    if (((c >> 7) & 0x01) == 0x00) {		// 0xxxxxxx
        r |= c;
    } else if (((c >> 5) & 0x07) == 0x06) {	// 110xxxxx
        r |= (c & 0x1F) << 6;
        r |= (data_[i+1] & 0x3F);
    } else if (((c >> 4) & 0x0F) == 0x0E) {	// 1110xxxx
        r |= (c & 0x0F) << 12;
        r |= (data_[i+1] & 0x3F) << 6;
        r |= (data_[i+2] & 0x3F);
    } else if (((c >> 3) & 0x1F) == 0x1E) {	// 11110xxx
        r |= (c & 0x07) << 18;
        r |= (data_[i+1] & 0x3F) << 12;
        r |= (data_[i+2] & 0x3F) << 6;
        r |= (data_[i+3] & 0x3F);
    } else if (((c >> 2) & 0x3F) == 0x3E) {	// 111110xx
        r |= (c & 0x03) << 24;
        r |= (data_[i+1] & 0x3F) << 18;
        r |= (data_[i+2] & 0x3F) << 12;
        r |= (data_[i+3] & 0x3F) << 6;
        r |= (data_[i+4] & 0x3F);
    } else if (((c >> 1) & 0x7F) == 0x7E) {	// 1111110x
        r |= (c & 0x01) << 30;
        r |= (data_[i+1] & 0x3F) << 24;
        r |= (data_[i+2] & 0x3F) << 18;
        r |= (data_[i+3] & 0x3F) << 12;
        r |= (data_[i+4] & 0x3F) << 6;
        r |= (data_[i+5] & 0x3F);
    }
    
    return r;
}

std::string String::Utf8String() const {
    if (length_ == 0) {
        return std::string();
    }
    
    return std::string(data_);
}

std::u16string String::Utf16String() const {
    if (length_ == 0) {
        return std::u16string();
    }
    
    std::vector<char16_t> vec;
    for (int i=0;i<length_;i++) {
        char32_t c = CharAt(i);
        if (c < 0x10000) {
            vec.push_back(c);
        } else {
            c -= 0x10000;
            vec.push_back(((c >> 10) & 0x03FF) | 0xD800);
            vec.push_back((c & 0x03FF) | 0xDC00);
        }
    }
    vec.push_back(0);
    return vec.data();
}

std::u32string String::Utf32String() const {
    if (length_ == 0) {
        return std::u32string();
    }
    
    std::vector<char32_t> vec(length_ + 1);
    for (int i=0;i<length_;i++) {
        vec[i] = CharAt(i);
    }
    vec[length_] = 0;
    return vec.data();
}

void String::Swap(String& str) {
    if (&str == this) return;
    std::swap(data_, str.data_);
    std::swap(length_, str.length_);
    std::swap(byteLength_, str.byteLength_);
    std::swap(lastIndex_, str.lastIndex_);
    std::swap(lastByteIndex_, str.lastByteIndex_);
}

String String::operator+(const String& s) const {
    if (length_ == 0) {
        return s;
    } else if (s.length_ == 0) {
        return *this;
    }
    
    String ret;
    ret.length_ = length_ + s.length_;
    ret.byteLength_ = byteLength_ + s.byteLength_;
    ret.data_ = new char[ret.byteLength_ + 1];
    memcpy(ret.data_, data_, byteLength_);
    memcpy(ret.data_ + byteLength_, s.data_, s.byteLength_ + 1);
    return ret;
}

String String::operator+(const char* s) const {
    return operator+(String(s));
}

String String::operator+(const char16_t* s) const {
    return operator+(String(s));
}

String String::operator+(const char32_t* s) const {
    return operator+(String(s));
}

String String::operator+(const std::string& s) const {
    return operator+(String(s));
}

String String::operator+(const std::u16string& s) const {
    return operator+(String(s));
}

String String::operator+(const std::u32string& s) const {
    return operator+(String(s));
}

String String::operator+(int64_t value) const{
    return operator+(String(value));
}

String String::operator+(uint64_t value) const{
    return operator+(String(value));
}

String String::operator+(int32_t value) const{
    return operator+(String(value));
}

String String::operator+(uint32_t value) const{
    return operator+(String(value));
}

String String::operator+(int16_t value) const{
    return operator+(String(value));
}

String String::operator+(uint16_t value) const{
    return operator+(String(value));
}

String String::operator+(int8_t value) const{
    return operator+(String(value));
}

String String::operator+(uint8_t value) const{
    return operator+(String(value));
}

String String::operator+(float value) const{
    return operator+(String(value));
}

String String::operator+(double value) const{
    return operator+(String(value));
}

String String::operator+(bool value) const{
    return operator+(String(value));
}

String String::operator+(char value) const{
    return operator+(String(value));
}

String String::operator+(char16_t value) const{
    return operator+(String(value));
}

String String::operator+(char32_t value) const{
    return operator+(String(value));
}

String& String::operator+=(const String& s) {
    String str = operator+(s);
    Swap(str);
    return *this;
}

String& String::operator+=(const char* s) {
    return operator+=(String(s));
}

String& String::operator+=(const char16_t* s) {
    return operator+=(String(s));
}

String& String::operator+=(const char32_t* s) {
    return operator+=(String(s));
}

String& String::operator+=(const std::string& s) {
    return operator+=(String(s));
}

String& String::operator+=(const std::u16string& s) {
    return operator+=(String(s));
}

String& String::operator+=(const std::u32string& s) {
    return operator+=(String(s));
}

String& String::operator+=(int64_t value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(uint64_t value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(int32_t value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(uint32_t value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(int16_t value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(uint16_t value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(int8_t value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(uint8_t value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(float value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(double value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(bool value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(char value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(char16_t value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

String& String::operator+=(char32_t value) {
    String str = operator+(value);
    Swap(str);
    return *this;
}

bool String::operator==(const String& s) const {
    if (byteLength_ != s.byteLength_) {
        return false;
    }
    
    return memcmp(data_, s.data_, byteLength_) == 0;
}

bool String::operator!=(const String& s) const {
    return !operator==(s);
}

String operator+(const char* lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(const char16_t* lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(const char32_t* lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(const std::string& lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(const std::u16string& lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(const std::u32string& lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(int64_t lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(uint64_t lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(int32_t lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(uint32_t lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(int16_t lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(uint16_t lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(int8_t lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(uint8_t lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(float lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(double lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(bool lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(char lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(char16_t lh, const String& rh) {
    return String(lh) + rh;
}

String operator+(char32_t lh, const String& rh) {
    return String(lh) + rh;
}
    
const String& String::BlankCharacters() {
    static String chars(" \t\n\r\u3000\v\f\u00A0\u180E\u2000\u2001\u2002\u2003\u2004\u2005\u2006\u2007\u2008\u2009\u200A\u200B\u200C\u200D\u2028\u2029\u202F\u205F\u2060\uFEFF");
    return chars;
}

String String::Substring(size_t start, size_t length) const {
    String ret;
    
    if (start >= length_) {
        return ret;
    }
    
    if (length > length_ - start) {
        length = length_ - start;
    }
    
    if (length == 0) {
        return ret;
    }
    
    int startIndex = GetByteIndex(start);
    int endIndex = GetByteIndex(start + length);
    ret.byteLength_ = endIndex - startIndex;
    ret.length_ = length;
    ret.data_ = new char[byteLength_ + 1];
    memcpy(ret.data_, data_ + startIndex, ret.byteLength_);
    ret.data_[ret.byteLength_] = 0;
    return ret;
}

String String::Substring(size_t start) const {
    String ret;
    
    if (start >= length_) {
        return ret;
    }
    
    int startIndex = GetByteIndex(start);
    ret.byteLength_ = byteLength_ - startIndex;
    ret.length_ = length_ - start;
    ret.data_ = new char[byteLength_ + 1];
    memcpy(ret.data_, data_ + startIndex, ret.byteLength_ + 1);
    return ret;
}

bool String::StartsWith(const String& s) const {
    if (s.length_ > length_) return false;
    for (int i = 0; i < s.length_; i++) {
        if (CharAt(i) != s.CharAt(i)) {
            return false;
        }
    }
    return true;
}

bool String::EndsWith(const String& s) const {
    if (s.length_ > length_) return false;
    for (int i = 0, j = length_ - s.length_; i < s.length_; i++, j++) {
        if (CharAt(j) != s.CharAt(i)) {
            return false;
        }
    }
    return true;
}

String String::ToLower() const {
    String ret = *this;
    for (int i=0;i<byteLength_;i++) {
        char c = data_[i];
        if (c >= 'A' && c <= 'Z') {
            ret.data_[i] = c - 'A' + 'a';
        }
    }
    return ret;
}

String String::ToUpper() const {
    String ret = *this;
    for (int i=0;i<byteLength_;i++) {
        char c = data_[i];
        if (c >= 'a' && c <= 'z') {
            ret.data_[i] = c - 'a' + 'A';
        }
    }
    return ret;
}

String String::TrimStart(const String& chars) const {
    int i = 0;
    for (; i < length_; i++) {
        bool found = false;
        for (int j = 0; j < chars.length_; j++) {
            if (CharAt(i) == chars.CharAt(j)) {
                found = true;
                break;
            }
        }
        if (!found) break;
    }
    return Substring(i);
}

String String::TrimEnd(const String& chars) const {
    int i = length_ - 1;
    for (; i >= 0; i--) {
        bool found = false;
        for (int j = 0; j < chars.length_; j++) {
            if (CharAt(i) == chars.CharAt(j)) {
                found = true;
                break;
            }
        }
        if (!found) break;
    }
    return Substring(0, i + 1);
}

String String::Trim(const String& chars) const {
    int i = 0, k = length_ - 1;
    for (; i < length_; i++) {
        bool found = false;
        for (int j = 0; j < chars.length_; j++) {
            if (CharAt(i) == chars.CharAt(j)) {
                found = true;
                break;
            }
        }
        if (!found) break;
    }
    for (; k > i; k--) {
        bool found = false;
        for (int j = 0; j < chars.length_; j++) {
            if (CharAt(k) == chars.CharAt(j)) {
                found = true;
                break;
            }
        }
        if (!found) break;
    }
    return Substring(i, k - i + 1);
}

int String::IndexOf(char32_t c, size_t startIndex) const {
    for (int i = startIndex; i < length_; i++) {
        if (CharAt(i) == c) {
            return i;
        }
    }
    
    return -1;
}

int String::LastIndexOf(char32_t c) const {
    for (int i = length_ - 1; i >= 0; i--) {
        if (CharAt(i) == c) {
            return i;
        }
    }
    
    return -1;
}

int String::IndexOf(const String& s, size_t startIndex) const {
    if (s.length_ == 0 || s.length_ > length_) {
        return -1;
        
    }
    size_t* next = s.next_;
    if (next == nullptr) {
        next = new size_t[s.length_];
        next[0] = 0;
        int j = 0;
        for (int i = 1; i < s.length_; i++) {
            char32_t c = s.CharAt(i);
            while (j > 0 && c != s.CharAt(j)) {
                j = next[j - 1];
            }
            if (c == s.CharAt(j)) {
                j++;
            }
            next[i]=j;
        }
        s.next_ = next;
    }
    
    int j = 0;
    for (int i = startIndex; i < length_; i++) {
        char32_t c = CharAt(i);
        while (j > 0 && c != s.CharAt(j)) {
            j = next[j - 1];
        }
        if (c == s.CharAt(j)) {
            j++;
        }
        if (j == s.length_) {
            return i - j + 1;
        }
    }
    
    return -1;
}

int String::LastIndexOf(const String& s) const {
    return Reverse().IndexOf(s.Reverse());
}

String String::Replace(char32_t oldChar, char32_t newChar, size_t startIndex) const {
    int i = IndexOf(oldChar, startIndex);
    if (i < 0) {
        return *this;
    }
    return Substring(0, i) + String(newChar) + Substring(i + 1);
}

String String::Replace(const String& oldStr, const String& newStr, size_t startIndex) const {
    int i = IndexOf(oldStr, startIndex);
    if (i < 0) {
        return *this;
    }
    return Substring(0, i) + newStr + Substring(i + 1);
}

String String::ReplaceAll(char32_t oldChar, char32_t newChar, size_t startIndex) const {
    int i;
    String ret = Substring(0, startIndex);
    while ((i = IndexOf(oldChar, startIndex)) >= 0) {
        ret += Substring(startIndex, i - startIndex) + String(newChar);
        startIndex = i + 1;
    }
    ret += Substring(startIndex);
    return ret;
}

String String::ReplaceAll(const String& oldStr, const String& newStr, size_t startIndex) const {
    int i;
    String ret = Substring(0, startIndex);
    while ((i = IndexOf(oldStr, startIndex)) >= 0) {
        ret += Substring(startIndex, i - startIndex) + newStr;
        startIndex = i + oldStr.length();
    }
    ret += Substring(startIndex);
    return ret;
}

std::vector<String> String::Split(char32_t c, bool removeEmpty) const {
    std::vector<String> ret;
    int start = 0;
    for (int i = 0; i < length_; i++) {
        if (CharAt(i) == c) {
            if(!removeEmpty || i != start)
                ret.push_back(Substring(start, i - start));
            start = i + 1;
        }
    }
    if (!removeEmpty || start < length_)
        ret.push_back(Substring(start));
    return ret;
}

std::vector<String> String::Split(const String& chars, bool removeEmpty) const {
    std::vector<String> ret;
    int start = 0;
    for (int i = 0; i < length_; i++) {
        if (chars.IndexOf(CharAt(i)) >= 0) {
            if(!removeEmpty || i != start)
                ret.push_back(Substring(start, i - start));
            start = i + 1;
        }
    }
    if (!removeEmpty || start < length_)
        ret.push_back(Substring(start));
    return ret;
}

String String::Reverse() const {
    std::u32string s = Utf32String();
    std::reverse((char32_t*)s.c_str(), (char32_t*)s.c_str() + s.length());
    return String(s);
}

}
