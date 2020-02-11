#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

string SpaceRemover (string infix)
{
    string fixedUpInfix;
    for (int i = 0; i < infix.size(); i++)
    {
        char ch = infix[i];
        if (isOperator(ch) || islower(ch) || ch == '(' || ch == ')')
            fixedUpInfix += ch;
        else if (ch == 32) //GOD ALMIGHTY, PUTTING "ch == ' '" DID NOT WORK HOOO BOY DID I ALMOST HAVE AN ANEURYSM OVER THIS
            continue;
    }
    return fixedUpInfix;
}

bool precedence(char firstOperator, char secondOperator)
{
    return (!((firstOperator == '*' || firstOperator == '/') && (secondOperator == '+' || secondOperator == '-')));
}

bool syntaxCheck (string infix)
{
    string fixedUpInfix = SpaceRemover(infix);
    if (fixedUpInfix.size() == 0)
        return false;
    if (fixedUpInfix.size() == 1 && !(islower(fixedUpInfix[0]))) {
        return false;
    }
    int openParenthesesCount = 0;
    int closedParenthesesCount = 0;
    int operatorCount = 0;
    int operandCount = 0;
    for (int i = 0; i < fixedUpInfix.size(); i++) {
        char ch = fixedUpInfix[i];
        if (!(islower(ch)) && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '(' && ch != ')')
            return false;
        if (isalpha(ch))
        {
            operandCount++;
        }
        if (ch == '(')
        {
            openParenthesesCount++;
        }
        if (ch == ')')
        {
            closedParenthesesCount++;
        }
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            operatorCount++;
        }
    }
    if (openParenthesesCount != closedParenthesesCount || operandCount == 0 || operatorCount != (operandCount-1))
        return false;
    for (int i = 0; i < fixedUpInfix.size(); i++)
    {
        char current = fixedUpInfix[i];
        char next = fixedUpInfix[i+1];
        if (isalpha(current) && isalpha(next))
            return false;
        if (current == '(' && next == ')')
            return false;
        if (current == '(' && isOperator(next)) {
            return false;
        }
        if (isOperator(current) && isOperator(next))
            return false;
    }
    string parenthesesOrder;
    for (int i = 0; i < fixedUpInfix.size(); i++)
    {
        char ch = fixedUpInfix[i];
        if (ch == '(' || ch == ')') {
            parenthesesOrder += ch;
        }
    }
    if (parenthesesOrder.size() != 0 && (parenthesesOrder[0] != '(' || parenthesesOrder[parenthesesOrder.size()-1] != ')'))
        return false;
    return true;
}

void infixToPostfix (string infix, string& postfix)
{
    string fixedUpInfix = SpaceRemover(infix);
    postfix = "";
    stack <char> operators;
    for (int i = 0; i < fixedUpInfix.size(); i++)
    {
        char ch = fixedUpInfix[i];
        switch (ch) {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                postfix += ch;
                break;
            case '(':
                operators.push(ch);
                break;
            case ')':
                while (operators.top() != '(')
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.pop();
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while (!operators.empty() && operators.top() != '(' && precedence(ch, operators.top()))
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(ch);
                break;
        }
    }
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }
}

bool mappedValuesExist (string infix, const Map& values)
{
    for (int i = 0; i < infix.size(); i++)
    {
        char ch = infix[i];
        if (isalpha(ch) && !values.contains(ch))
            return false;
    }
    return true;
}

int evaluate(string infix, const Map& values, string& postfix, int& result) {
    if (!syntaxCheck(infix))
        return 1;
    else {
        infixToPostfix(infix, postfix);
        if (!mappedValuesExist(infix, values))
            return 2;
        else
        {
            stack <int> operands;
            for (int i = 0; i < postfix.size(); i++)
            {
                char ch = postfix[i];
                if (islower(ch))
                {
                    int valueGetter;
                    values.get(ch, valueGetter);
                    operands.push(valueGetter);
                }
                else
                {
                    int secondOperand = operands.top();
                    operands.pop();
                    int firstOperand = operands.top();
                    operands.pop();
                    int answer;
                    switch(ch)
                    {
                        case '+':
                            answer = firstOperand + secondOperand;
                            break;
                        case '-':
                            answer = firstOperand - secondOperand;
                            break;
                        case '*':
                            answer = firstOperand * secondOperand;
                            break;
                        case '/':
                            if (secondOperand == 0)
                                return 3;
                            else
                            {
                                answer = firstOperand/secondOperand;
                                break;
                            }
                    }
                    operands.push(answer);
                }
            }
            result = operands.top();
            return 0;
        }
    }
}

//int main()
//{
//    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
//    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
//    Map m;
//    for (int k = 0; vars[k] != '#'; k++)
//        m.insert(vars[k], vals[k]);
//    string pf;
//    int answer;
//    assert(evaluate("a+ e", m, pf, answer) == 0  &&
//                            pf == "ae+"  &&  answer == -6);
//    answer = 999;
//    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
//      // unary operators not allowed:
//    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a*b", m, pf, answer) == 2  &&
//                            pf == "ab*"  &&  answer == 999);
//    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
//                            pf == "yoau-*+"  &&  answer == -1);
//    answer = 999;
//    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
//                            pf == "oyy-/"  &&  answer == 999);
//    assert(evaluate(" a  ", m, pf, answer) == 0  &&
//                            pf == "a"  &&  answer == 3);
//    assert(evaluate("((a))", m, pf, answer) == 0  &&
//                            pf == "a"  &&  answer == 3);
//    cout << "Passed all tests" << endl;
//}
