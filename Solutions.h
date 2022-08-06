//
// Eylül Badem - 22003079
// HW4 - 14.05.2022
//

#ifndef HW4_SOLUTIONS_H
#define HW4_SOLUTIONS_H
#include <string>
#include "Stack.h"
using namespace std;

void fantabulous(string list, int length);
void subset(string intervals, int length);
string infix2prefix(string expression);
void evaluatePrefix(string expression);
string intToString(int integer);
int getOperatorPrecedence(string opr);
double evaluatePostfix( const string exp );
int stringToInt(string st);
string prefix2postfix( const string exp );

#endif //HW4_SOLUTIONS_H
