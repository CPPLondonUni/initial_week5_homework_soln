
#include <cassert>
#include <cctype>
#include <cstddef>
#include <string>
#include <iostream>

void lower_case(std::string& str)
{
    for (char& c : str) {
        c = std::tolower(c);
    }
}

void headline_case(std::string& str)
{
    // Do nothing for an empty string
    if (str.empty()) {
        return;
    }

    // Capitalise the first character of the string
    str[0] = std::toupper(str[0]);

    // For every other character of the string, capitalise if the preceding
    // character was a space
    for (std::size_t i = 1; i < str.size(); i++) {
        if (str[i - 1] == ' ') {
            str[i] = std::toupper(str[i]);
        }
    }
}

void sentence_case(std::string& str)
{
    // Do nothing for an empty string
    if (str.empty()) {
        return;
    }

    // Capitalise the first character
    str[0] = std::toupper(str[0]);

    // Iterate through the string starting from position 2, testing the
    // preceding two characters
    for (std::size_t i = 2; i < str.size(); i++) {
        if (str[i - 2] == '.' && str[i - 1] == ' ') {
            str[i] = std::toupper(str[i]);
        }
    }
}

void sentence_case2(std::string& str)
{
    // Do nothing for an empty string
    if (str.empty()) {
        return;
    }

    // Capitalise the first character
    str[0] = std::toupper(str[0]);

    for (std::size_t i = 0; i < str.size(); i++) {
        // if we find a full stop...
        if (str[i] == '.') {
            // ...advance through the string until we find the next non-
            // whitespace character, or reach the end
            do {
                ++i;
            } while (i < str.size() && std::isspace(str[i]));

            // If we have *not* reached the end of the string, change the
            // character to uppercase
            if (i != str.size()) {
                str[i] = std::toupper(str[i]);
            }
        }
    }
}

void sentence_case3(std::string& str)
{
    // Do nothing for an empty string
    if (str.empty()) {
        return;
    }

    // Record whether we need to capitalise the next character
    bool capitalise_next = true;

    for (std::size_t i = 0; i < str.size(); i++) {
        if (capitalise_next) {
            str[i] = std::toupper(str[i]);
            capitalise_next = false;
        }

        // If we find a full stop...
        if (str[i] == '.') {
            // Update i to inspect the next character
            ++i;
            // If i now points to the end of the string, we're done
            if (i == str.size()) {
                return;
            }

            // Now count the number of space characters until the next non-
            // whitespace
            std::size_t space_count = 0;
            for (std::size_t j = i; j < str.size(); ++j) {
                if (!std::isspace(str[j])) {
                    break;
                }
                ++space_count;
            }

            // Replace the characters in positions i to i + space_count with
            // a single space
            str.replace(i, space_count, " ");

            //
            capitalise_next = true;
        }

    }
}

int main()
{
    // Test lower_case()
    {
        std::string mixed = "MiXeD";
        lower_case(mixed);
        assert(mixed == "mixed");
    }

    // Test headline_case()
    {
        std::string str = "this is a headline";
        headline_case(str);
        assert(str == "This Is A Headline");
    }

    // Test sentence_case()
    {
        std::string str = "this is sentence 1. this is sentence 2.";
        sentence_case(str);
        assert(str == "This is sentence 1. This is sentence 2.");
    }

    // Test sentence_case2()
    {
        std::string str = "this is sentence 1.  \t\n \r this is sentence 2.";
        const std::string expected = "This is sentence 1.  \t\n \r This is sentence 2.";
        sentence_case2(str);
        assert(str == expected);
    }

    // Test sentence_case3()
    {
        std::string str = "this is sentence 1.  \t\n \r this is sentence 2.";
        const std::string expected = "This is sentence 1. This is sentence 2.";
        sentence_case3(str);
        std::cout << str << std::endl;
        assert(str == expected);
    }
}