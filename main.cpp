/*  Условие:
 *  Реализовать функцию, осуществляющую примитивную распаковку строки, содержащую повторяющиеся символы/руны.
 *  Реализовать поддержку escape-последовательностей.
 *  Примеры:
 *  "a4bc2d5e" => "aaaabccddddde"
 *  "abcd" => "abcd"
 *  "45" => incorrect
 *  "" => ""
 *  qwe\4\5 => qwe45
 *  qwe\45 => qwe44444
 *  qwe\\5 => qwe\\\\\
*/

#include <bits/stdtr1c++.h>

bool isNumber(const char c) { return c - '0' >= 0 && c - '0' <= 9; }
bool isSymbol(const char c) { return !isNumber(c) && c != '\\'; }
bool isEscape(const char c) { return c == '\\'; }

std::string unpackString(const std::string &s, bool &success) {
    enum { BEGIN, NUMBER, SYMBOL, ESCAPE } state = BEGIN;
    std::string answer;
    success = true;

    if ( s.empty() ) { return answer; }

    for ( auto i = 0; i < s.size(); ++i ) {
        if (state == BEGIN && isNumber(s[i])) {
            success = false;
            return answer;
        } else if (state == BEGIN && isSymbol(s[i])) {
            answer.append(1, s[i]);
            state = SYMBOL;
        } else if (state == SYMBOL && isNumber(s[i])) {
            int number = static_cast<int>(s[i] - '0') - 1;
            if (number >= 0) { answer.append(number, s[i - 1]); }
            state = NUMBER;
        } else if (state == SYMBOL && isSymbol(s[i])) {
            answer.append(1, s[i]);
            state = SYMBOL;
        } else if (state == SYMBOL && isEscape(s[i])) {
            state = ESCAPE;
        } else if (state == NUMBER && isNumber(s[i])) {
            success = false;
            return answer;
        } else if (state == NUMBER && isSymbol(s[i])) {
            answer.append(1, s[i]);
            state = SYMBOL;
        } else if (state != ESCAPE && isEscape(s[i])) {
            state = ESCAPE;
        } else if (state == ESCAPE && !isEscape(s[i])) {
            answer.append(1, s[i]);
            state = SYMBOL;
        } else if (state == ESCAPE && isEscape(s[i])) {
            answer.append(1, s[i - 1]);
            state = SYMBOL;
        }
    }
    if ( state == ESCAPE ) { success = false; }
    return answer;
}

void test() {
    {
        std::string s;
        bool flag;
        assert( unpackString(s, flag) == "" && flag );
        std::cout << "TEST1 : SUCCESS!" << std::endl;
    }

    {
        std::string s {"a"};
        bool flag;
        assert( unpackString(s, flag) == "a" && flag );
        std::cout << "TEST2 : SUCCESS!" << std::endl;
    }

    {
        std::string s {"ab"};
        bool flag;
        assert( unpackString(s, flag) == "ab" && flag );
        std::cout << "TEST3 : SUCCESS!" << std::endl;
    }

    {
        std::string s {"abbsdraaa"};
        bool flag;
        assert( unpackString(s, flag) == "abbsdraaa" && flag );
        std::cout << "TEST4 : SUCCESS!" << std::endl;
    }

    {
        std::string s {"a4bc2d5e"};
        bool flag;
        assert( unpackString(s, flag) == "aaaabccddddde" && flag);
        std::cout << "TEST5 : SUCCESS!" << std::endl;
    }

    {
        std::string s {"45"};
        bool flag;
        unpackString(s, flag);
        assert(!flag);
        std::cout << "TEST6 : SUCCESS!" << std::endl;
    }

    {
        std::string s { "a4bcd33" };
        bool flag;
        unpackString(s, flag);
        assert(!flag);
        std::cout << "TEST7 : SUCCESS!" << std::endl;
    }

    {
        std::string s { "a4b21d" };
        bool flag;
        unpackString(s, flag);
        assert(!flag);
        std::cout << "TEST8 : SUCCESS!" << std::endl;
    }

    {
        std::string s { R"(qwe\4\5)" };
        bool flag;
        assert( unpackString(s, flag) == "qwe45" && flag);
        std::cout << "TEST9 : SUCCESS!" << std::endl;
    }

    {
        std::string s { R"(qwe\45)" };
        bool flag;
        assert( unpackString(s, flag) == "qwe44444" && flag);
        std::cout << "TEST10 : SUCCESS!" << std::endl;
    }

    {
        std::string s { R"(qwe\\5)" };
        bool flag;
        assert( unpackString(s, flag) == std::string { R"(qwe\\\\\)" } && flag);
        std::cout << "TEST11 : SUCCESS!" << std::endl;
    }
}

int main() {
    test();
    return 0;
}

