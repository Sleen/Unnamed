#include "StringHelper.hpp"

#include <cstring>
#include <algorithm>

namespace me {

	bool StringHelper::StartsWith(const std::string & text, const std::string & value)
	{
		if (value.length() > text.length()) return false;
		for (int i = 0; i < value.length(); i++) {
			if (text[i] != value[i])return false;
		}
		return true;
	}

	bool StringHelper::EndsWith(const std::string & text, const std::string & value)
	{
		if (value.length() > text.length()) return false;
		const char* data = text.c_str() + text.length() - value.length();
		for (int i = 0; i < value.length(); i++) {
			if (data[i] != value[i])return false;
		}
		return true;
	}

	std::string StringHelper::Trim(const std::string & text, char c)
	{
		int i = 0, len = text.length(), j = len - 1;
		for (; i < len; i++) {
			if (text[i] != c) break;
		}
		for (; j >= 0; j--) {
			if (text[j] != c) break;
		}
		return text.substr(i, j - i + 1);
	}

	std::string StringHelper::TrimStart(const std::string & text, char c)
	{
		int i = 0, len = text.length();
		for (; i < len; i++) {
			if (text[i] != c) break;
		}
		return text.substr(i);
	}

	std::string StringHelper::TrimEnd(const std::string & text, char c)
	{
		int i = text.length() - 1;
		for (; i >= 0; i--) {
			if (text[i] != c) break;
		}
		return text.substr(0, i + 1);
	}

	std::string StringHelper::Trim(const std::string & text, const std::string & chars)
	{
		int i = 0, len = text.length(), j = len - 1;
		for (; i < len; i++) {
			if (chars.find(text[i]) == std::string::npos) break;
		}
		for (; j >= 0; j--) {
			if (chars.find(text[j]) == std::string::npos) break;
		}
		return text.substr(i, j - i + 1);
	}

	std::string StringHelper::TrimStart(const std::string & text, const std::string & chars)
	{
		int i = 0, len = text.length();
		for (; i < len; i++) {
			if (chars.find(text[i]) == std::string::npos) break;
		}
		return text.substr(i);
	}

	std::string StringHelper::TrimEnd(const std::string & text, const std::string & chars)
	{
		int i = text.length() - 1;
		for (; i >= 0; i--) {
			if (chars.find(text[i]) == std::string::npos) break;
		}
		return text.substr(0, i + 1);
	}

	std::string StringHelper::ToLower(const std::string & text)
	{
		std::string s = text;
		std::transform(s.begin(), s.end(), s.begin(), (int(*)(int))tolower);
		return s;
	}

	std::string StringHelper::ToUpper(const std::string & text)
	{
		std::string s = text;
		std::transform(s.begin(), s.end(), s.begin(), (int(*)(int))toupper);
		return s;
	}

	std::string StringHelper::Replace(const std::string & text, char old, char _new)
	{
		int len = text.length();
		char* s = new char[len + 1];
		strcpy(s, text.c_str());
		for (int i = 0; i < len; i++) {
			if (s[i] == old)
				s[i] = _new;
		}
		std::string str(s);
		delete[] s;
		return str;
	}

	std::string StringHelper::Format(const char *format, ...)
    {
		va_list args;
		va_start(args, format);
		return Formatv(format, args);
	}

	// TODO 
	std::string StringHelper::Formatv(const char * format, va_list args)
	{
		//std::stringstream ss;
		//return ss.str();
		
		static char buf[1024];
		vsprintf(buf, format, args);
		return buf;
	}

	std::vector<std::string> StringHelper::Split(const std::string & str, char c, bool removeEmpty)
	{
		std::vector<std::string> ret;
		int start = 0;
		for (int i = 0, len = str.length(); i < len; i++) {
			if (str[i] == c) {
				if(!removeEmpty || i != start)
					ret.push_back(str.substr(start, i - start));
				start = i + 1;
			}
		}
		if (!removeEmpty || start < str.length())
			ret.push_back(str.substr(start));
		return ret;
	}

	std::vector<std::string> StringHelper::Split(const std::string & str, const std::string & chars, bool removeEmpty)
	{
		std::vector<std::string> ret;
		int start = 0;
		for (int i = 0, len = str.length(); i < len; i++) {
			if (chars.find(str[i]) != std::string::npos) {
				if (!removeEmpty || i != start)
					ret.push_back(str.substr(start, i - start));
				start = i + 1;
			}
		}
		if (!removeEmpty || start < str.length())
			ret.push_back(str.substr(start));
		return ret;
	}
    
    static std::string Fill(const std::string& text, size_t length, const char* fill, const char* ellipsis, int alignment) {
        if (text.length() > length) {
            return StringHelper::Format("%s%s", text.substr(0, length - strlen(ellipsis)).c_str(), ellipsis);
        } else if (text.length() == length) {
            return text;
        }
        
        char* chrs = new char[length+1];
        chrs[length] = 0;
        size_t len = strlen(fill);
        for (int i=0;i<length;i++) {
            chrs[i] = fill[i % len];
        }
        int start = alignment == 0 ? 0 : alignment == 1 ? length-text.length() : (length-text.length())/2;
        memcpy(chrs + start, text.c_str(), text.length());
        std::string ret = chrs;
        delete [] chrs;
        return ret;
    }
    
    std::string StringHelper::FillLeft(const std::string& text, size_t length, const char* fill, const char* ellipsis) {
        return Fill(text, length, fill, ellipsis, 0);
    }
    
    std::string StringHelper::FillRight(const std::string& text, size_t length, const char* fill, const char* ellipsis) {
        return Fill(text, length, fill, ellipsis, 1);
    }
    
    std::string StringHelper::FillCenter(const std::string& text, size_t length, const char* fill, const char* ellipsis) {
        return Fill(text, length, fill, ellipsis, 2);
    }
    
    std::vector<std::string> StringHelper::LineWrap(const std::string& text, size_t length) {
        std::vector<std::string> lines;
        int wordLength = 0;
        int lineLength = 0;
        for (int i=0, len = text.length();i<len;i++) {
            bool newLine = false;
            if (text[i] == '\r') {
                newLine = true;
            } else if (text[i] == '\n') {
                if (i > 0 && text[i-1] == '\r') {
                    continue;
                }
                newLine = true;
            }
            
            if (newLine) {
                lines.push_back(text.substr(i-lineLength, lineLength));
                lineLength = 0;
                wordLength = 0;
                continue;
            }
            
            if (text[i] == ' ') {
                wordLength = 0;
            } else {
                wordLength++;
            }
            lineLength++;
            
            if (lineLength == length) {
                if (wordLength > 0) {
                    if (i == len-1 || text[i+1] == ' ' || text[i+1] == '\n' || text[i+1] == '\r') {
                        lines.push_back(text.substr(i - lineLength+1, lineLength));
                        lineLength = 0;
                        while(i < len && text[i+1] == ' ') i++;
                    } else if (wordLength == lineLength){
                        lines.push_back(text.substr(i-lineLength+1, lineLength));
                        lineLength = 0;
                        wordLength = 0;
                    } else {
                        lines.push_back(text.substr(i-lineLength+1,lineLength - wordLength));
                        lineLength = wordLength;
                    }
                } else {
                    lines.push_back(text.substr(i-lineLength+1, lineLength));
                    lineLength = 0;
                }
            }
        }
        if (lineLength > 0) {
            lines.push_back(text.substr(text.length() - lineLength));
        }
        return lines;
    }

}
