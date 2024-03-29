#ifndef KLIB_STRING_H
#define KLIB_STRING_H

#include <cstring>
#include <string> // for iostream

typedef class String {
    friend String operator+ (const char *, String &);
    friend std::ostream& operator<< (std::ostream &, const String &);
    friend std::istream& operator>> (std::istream &, String &);
    friend std::istream& getline(std::istream &, String &);
    /* The method converts numbers to arithmetic string. */
    template <class number>
    friend String toCalStr(number);
    /* The method converts Unicode values into characters. */
    friend char fromCharCode(const unsigned);
    private:
        char *_proto_; // c-string data
        void assign(const char *);
    public:
        /* The length property returns the length of a string (number of characters). */
        unsigned length;
        
        String();
        String(const char *str);
        String(const char);
        String(const String &str);
        ~String();
        
        operator char*();
        operator const char*();

        char& operator[] (const int);
        String operator+ (const char *);
        String operator+ (const String &);
        String operator+= (const char *);
        String operator+= (const char);
        String operator+= (const String &);
        String operator= (const char *);
        String operator= (const String &);
        bool operator== (const char *);
        bool operator== (const String &);
        bool operator!= (const char *);
        bool operator!= (const String &);
        String operator* (const unsigned);
        
        /* The method returns the character at the specified index in a string. */
        char charAt(const unsigned);
        /* The method returns the Unicode of the character at the specified index in a string. */
        int charCodeAt(const unsigned);
        /* The method returns a non-negative integer that is the Unicode code point value. */
        unsigned codePointAt(const unsigned);
        /* The method is used to join two or more strings. */
        template<class _type_string>
        String concat(const _type_string);
        /* The method retunrs the value of c-string. */
        char * cstring();
        /* The method determines whether a string ends with the characters of a specified string. */
        template<class _type_string>
        bool endsWith(const _type_string, unsigned=-1);
        /* The method determines whether a string contains the characters of a specified string. */
        template<class _type_string>
        bool includes(const _type_string, const unsigned=0);
        /* The method returns the position of the first occurrence of a specified value in a string. */
        template<class _type_string>
        int indexOf(const _type_string, const unsigned=0);
        /* The method returns the position of the last occurrence of a specified value in a string. */
        template<class _type_string>
        int lastIndexOf(const _type_string, unsigned=-1);
        /* The method compares two strings in the current locale. */
        template<class _type_string>
        int localeCompare(const _type_string);
        /* The method searches a string for a match against a regular expression, and returns the matches, as an Array object. */
        String match();
        /* method pads the current string with a given string (repeated, if needed) so that the resulting string reaches a given length. */
        String matchAll();
        /* The method returns the Unicode Normalization Form of the string. */
        template<class _type_string>
        String normalize(const _type_string);
        /* The method pads the current string with another string (multiple times, if needed) until the resulting string reaches the given length */
        template<class _type_string>
        String padEnd(const unsigned, const _type_string);
        /* The method pads the current string with another string (multiple times, if needed) until the resulting string reaches the given length */
        template<class _type_string>
        String padStart(const unsigned, const _type_string);
        /* The method returns a new string with a specified number of copies of the string it was called on. */
        String repeat(const unsigned);
        /* The method searches a string for a specified value, or a regular expression, and returns a new string where the specified values are replaced. */
        template<class _type_string1, class _type_string2>
        String replace(const _type_string1, const _type_string2);
        /* The  method searches a string for a specified value, and returns the position of the match. */
        template<class _type_string>
        int search(const _type_string);
        /* The method extracts parts of a string and returns the extracted parts in a new string. */
        String slice(const unsigned, unsigned=-1);
        /* The method is used to split a string into an array of substrings, and returns the new array. */
        template<class _type_string>
        Array<String> split(const _type_string);
        /* The method determines whether a string begins with the characters of a specified string. */
        template<class _type_string>
        bool startsWith(const _type_string, const unsigned=0);
        /* The method extracts parts of a string, beginning at the character at the specified position, and returns the specified number of characters. */
        String substr(const unsigned, unsigned=-1);
        /* The method extracts the characters from a string, between two specified indices, and returns the new sub string. */
        String substring(unsigned, unsigned=-1);
        /* The method converts a string to lowercase letters. */
        String toLowerCase();
        /* The method returns the value of a String object. */
        String toString();
        /* The method converts a string to uppercase letters. */
        String toUpperCase();
        /* The method removes whitespace from both sides of a string. */
        String trim();
        /* The method removes whitespace from the beginning of the string. */
        String trimStart();
        /* The method removes whitespace from the beginning of the string. */
        String trimLeft();
        /* The method removes whitespace from the end of the string. */
        String trimEnd();
        /* The method removes whitespace from the end of the string. */
        String trimRight();
        /* The method returns the primitive value of a String object. */
        String valueOf();
} string;

/* constructor */
String::String() {
    _proto_ = NULL;
    length = 0;
}

String::String(const char *str) {
    this->assign(str);
}

String::String(const char c) {
    length = 1;

    _proto_ = new char[2];

    _proto_[0] = c;
    _proto_[1] = '\0';
}

String::String(const String &str) {
    this->assign(str._proto_);
}

String::~String() {
    delete[] _proto_;
}

/* call operators */
String::operator char*() {return _proto_;}
String::operator const char*() {return _proto_;}
char& String::operator[] (const int index) {return _proto_[index];}

/* processing operators: FRIEND */
std::ostream& operator<< (std::ostream &out, const String &str) {
    out << str._proto_;
    return out;
}

std::istream& operator>> (std::istream &in, String &str) {
    std::string t;
    in >> t;
    
    str.assign(t.c_str());
    
    return in;
}

std::istream& getline(std::istream &in, String &str) {
    std::string t;
    std::getline(std::cin, t);
    
    str.assign(t.c_str());
    
    return in;
}

/* processing operators: OVERLOAD */
String operator+ (const char *lstr, String &rstr) {
    unsigned llength = strlen(lstr);

    char result[llength+rstr.length+1];
    result[llength+rstr.length] = '\0';

    for (unsigned i = 0; i < llength; i++)
        result[i] = lstr[i];
    for (unsigned i = 0; i < rstr.length; i++)
        result[rstr.length+i] = rstr._proto_[i];

    rstr._proto_ = result;
    rstr.length += llength;

    return result;
}

String String::operator+ (const char *str) {
    unsigned inlength = strlen(str);

    char *old = _proto_;
    _proto_ = new char[length+inlength+1];
    _proto_[length+inlength] = '\0';

    for (unsigned i = 0; i < length; i++)
        _proto_[i] = old[i];
    for (unsigned i = 0; i < inlength; i++)
        _proto_[length+i] = str[i];

    delete[] old;
    length += inlength;
    
    return _proto_;
}

String String::operator+ (const String &str) {
    char *old = _proto_;
    _proto_ = new char[length+str.length+1];
    _proto_[length+str.length] = '\0';

    for (unsigned i = 0; i < length; i++)
        _proto_[i] = old[i];
    for (unsigned i = 0; i < str.length; i++)
        _proto_[length+i] = str._proto_[i];

    delete[] old;
    length += str.length;
    
    return _proto_;
}

/* ### */

String String::operator+= (const char *str) {
    unsigned inlength = strlen(str);

    char *old = _proto_;
    _proto_ = new char[length+inlength+1];
    _proto_[length+inlength] = '\0';

    for (unsigned i = 0; i < length; i++)
        _proto_[i] = old[i];
    for (unsigned i = 0; i < inlength; i++)
        _proto_[length+i] = str[i];

    delete[] old;
    length += inlength;
    
    return _proto_;
}

String String::operator+= (const char chr) {
    char *old = _proto_;
    _proto_ = new char[(++length)+1];
    _proto_[length-1] = chr;
    _proto_[length] = '\0';
    
    for (unsigned i = 0; i < length-1; i++)
        _proto_[i] = old[i];
    
    delete[] old;

    return _proto_;
}

String String::operator+= (const String &str) {
    char *old = _proto_;
    _proto_ = new char[length+str.length+1];
    _proto_[length+str.length] = '\0';

    for (unsigned i = 0; i < length; i++)
        _proto_[i] = old[i];
    for (unsigned i = 0; i < str.length; i++)
        _proto_[length+i] = str._proto_[i];

    delete[] old;
    length += str.length;
    
    return _proto_;
}

/* ### */

String String::operator= (const char *str) {
    this->assign(str);
    return *this;
}

String String::operator= (const String &str) {
    this->assign(str._proto_);
    return *this;
}

/* ### */

bool String::operator== (const String &str) {
    if (length != str.length) return false;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str._proto_[i]) return false;
    }
    
    return true;
}

bool String::operator== (const char *str) {
    if (length != strlen(str)) return false;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str[i]) return false;
    }
    
    return true;
}

bool String::operator!= (const String &str) {
    if (length != str.length) return true;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str._proto_[i]) return true;
    }
    
    return false;
}

bool String::operator!= (const char *str) {
    if (length != strlen(str)) return true;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str[i]) return true;
    }
    
    return false;
}

/* ### */

String String::operator* (const unsigned mul) {
    
}

/* class methods: PRIVATE */
void String::assign(const char *str) {
    //delete[] _proto_;

    length = strlen(str);

    _proto_ = new char[length+1];
        
    for (unsigned i = 0; i < length+1; i++) {
        _proto_[i] = str[i];
    }

    _proto_[length] = '\0';
}

/* class methods: FRIEND */
template <class number>
String toCalStr(number n) {
    if (n == 1) return "";
    if (n == -1) return "-";

    return std::to_string(int(n)).c_str();
}

/* class methods: BUILT-IN */
char String::charAt(const unsigned index) {
    return _proto_[index];
}

int String::charCodeAt(const unsigned index) {
    return _proto_[index];
}

template <class _type_string>
String String::concat(const _type_string string1) {
    string str(string1);

    char result[length+str.length+1];
    result[length+str.length] = '\0';
    
    for (unsigned i = 0; i < length; i++)
        result[i] = _proto_[i];
    for (unsigned i = 0; i < str.length; i++)
        result[length + i] = str._proto_[i];

    return result;
}

template <class _type_string>
bool String::endsWith(const _type_string searchvalue, unsigned atlength) {
    if (atlength == -1) atlength = length;
    string t(searchvalue);

    unsigned j = length-1;
    for (unsigned i = j; i >= 0; i--) {
        if (t[j] == _proto_[i]) {
            if (++j == t.length)
                return true;
        }
        return false;
    }

    return false;
}

template<class _type_string>
bool String::includes(const _type_string searchvalue, const unsigned start) {
    string t(searchvalue);

    unsigned j = 0;
    for (unsigned i = start; i < length; i++) {
        if (_proto_[i] == t[j]) {
            if (++j == t.length)
                return true;
        }
        else {
            j = 0;
        }
    }

    return false;
}

template<class _type_string>
int String::indexOf(const _type_string searchvalue, const unsigned start) {
    string t(searchvalue);

    unsigned j = 0, fisrtFindIndex = 0;
    for (unsigned i = start; i < length; i++) {
        if (_proto_[i] == t[j]) {
            if (j == 0) fisrtFindIndex = i;
            if (++j == t.length)
                return true;
        }
        else {
            j = 0;
        }
    }

    return -1;
}

template <class _type_string>
int String::lastIndexOf(const _type_string searchvalue, unsigned start) {
    if (start == -1) start = length;
    string t(searchvalue);

    unsigned j = length-1;
    for (unsigned i = j; i >= 0; i--) {
        if (t[j] == _proto_[i]) {
            if (++j == t.length)
                return i;
        }
        else {
            j = 0;
        }
    }

    return -1;
}

template<class _type_string1, class _type_string2>
String String::replace(const _type_string1 searchvalue, const _type_string2 newvalue) {
    string searchVal(searchvalue), newVal(newvalue);

    if (searchVal == "") return *this;

    string result = "";
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] == searchVal[0]) {
            if (newVal == "") continue;
            result += newVal;
        }
        else {
            result += _proto_[i];
        }
    }

    return result;
}

template<class _type_string>
int String::search(const _type_string searchvalue) {
    string t(searchvalue);

    unsigned j = 0, fisrtFindIndex = 0;
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] == t[j]) {
            if (i == 0) fisrtFindIndex = i;
            if (i == t.length)
                return fisrtFindIndex;
        }
        else {
            j = 0;
        }
    }

    return -1;
}

String String::slice(const unsigned start, unsigned end) {
    if (end == -1) end = length;
    if (end-start <= 0) return "";

    char result[end-start+1];
    result[end-start] = '\0';

    unsigned j = 0;
    for (unsigned i = start; i < end; i++) {
        result[j++] = _proto_[i];
    }

    return result;
}

template<class _type_string>
Array<String> String::split(const _type_string separator) {
    string sep(separator);
    Array<String> splited;

    unsigned splitIndex = 0;
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] == sep[0]) {
            splited.push(this->slice(splitIndex,i));
            splitIndex = i+sep.length;
        }
    }

    splited.push(this->slice(splitIndex));

    return splited;
}

template<class _type_string>
bool String::startsWith(const _type_string searchvalue, const unsigned start) {
    string t(searchvalue);
    
    unsigned i = start;
    while (i < length) {
        if (_proto_[i] == t[i]) {
            if (++i == t.length)
                return true;
        }
        false;
    }

    return false;
}

String String::substr(const unsigned start, unsigned atlength) {
    if (atlength == -1) atlength = length;
    if (atlength-start <= 0) return "";

    char result[atlength-start+1];
    result[atlength-start] = '\0';

    unsigned j = 0;
    for (unsigned i = start; i < atlength; i++) {
        result[j++] = _proto_[i];
    }

    return result;
}

String String::substring(unsigned start, unsigned end) {
    if (end == -1) end = length;
    if (end-start <= 0) return "";
    else if (start > end) {
        unsigned temp = start;
        start = end;
        end = start;
    }

    char result[end-start+1];
    result[end-start] = '\0';

    unsigned j = 0;
    for (unsigned i = start; i < end; i++) {
        result[j++] = _proto_[i];
    }

    return result;
}

String String::toLowerCase() {
    char str[length+1];
    str[length] = '\0';

    for (unsigned i = 0; i < length; i++) {
        str[i] = _proto_[i];
        if (str[i] >= 65 && str[i] <= 90) {
            str[i] += 32;
        }
    }

    return str;
}

String String::toString() {
    return *this;
}

String String::toUpperCase() {
    char str[length+1];
    str[length] = '\0';

    for (unsigned i = 0; i < length; i++) {
        str[i] = _proto_[i];
        if (str[i] >= 97 && str[i] <= 122) {
            str[i] -= 32;
        }
    }

    return str;
}

String String::trim() {
    unsigned indexLeft = 0, indexRight = 0;
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != ' ') {
            indexLeft = i;
            break;
        }
    }

    for (unsigned i = length-1; i >= 0; i--) {
        if (_proto_[i] != ' ') {
            indexRight = i+1;
            break;
        }
    }

    return this->slice(indexLeft, indexRight);
}

String String::valueOf() {
    return *this;
}

#endif