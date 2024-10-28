#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <unordered_map>

using namespace std;

enum class Type
{
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    DIGIT,
    SEMICOLON,
    UNKNOWN
};

bool isKeyword(string word)
{
    static unordered_map<string, Type> keywords = {
        {"int", Type::KEYWORD},
    };
    if (keywords.find(word) != keywords.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

Type categoriz(string str)
{
    if (isKeyword(str))
    {
        return Type::KEYWORD;
    }
    else if (isdigit(str[0]))
    {
        return Type::DIGIT;
    }
    else if (str == "=")
    {
        return Type::OPERATOR;
    }
    else if (str == ";")
    {
        return Type::SEMICOLON;
    }
    else if (isalpha(str[0]))
    {
        return Type::IDENTIFIER;
    }
    return Type::UNKNOWN;
}

void output(string str, Type type)
{
    cout << "\"" << str << "\" \t| Type => ";
    switch (type)
    {
    case Type::KEYWORD:
        cout << "Keyword";
        break;
    case Type::IDENTIFIER:
        cout << "Identifier";
        break;
    case Type::OPERATOR:
        cout << "Operator";
        break;
    case Type::DIGIT:
        cout << "DIGIT";
        break;
    case Type::SEMICOLON:
        cout << "Semicolon";
        break;
    case Type::UNKNOWN:
        cout << "Unknown";
        break;
    }
    cout << endl;
}

void lexicalAnalyzer(string input)
{
    stack<string> parts;
    string currentPart;

    for (char ch : input)
    {
        if (isspace(ch))
        {
            if (!currentPart.empty())
            {
                parts.push(currentPart);
                currentPart.clear();
            }
        }
        else if (ch == '=' || ch == ';')
        {
            if (!currentPart.empty())
            {
                parts.push(currentPart);
                currentPart.clear();
            }
            currentPart += ch;
            parts.push(currentPart);
            currentPart.clear();
        }
        else
        {
            currentPart += ch;
        }
    }

    if (!currentPart.empty())
    {
        parts.push(currentPart);
    }

    while (!parts.empty())
    {
        string str = parts.top();
        parts.pop();
        Type type = categoriz(str);
        output(str, type);
    }
}

int main()
{
    cout << "******************************\n";
    string statement = "int age = 25;";
    lexicalAnalyzer(statement);
    cout << "******************************\n";
    return 0;
}
