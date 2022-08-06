//
// Eylül Badem - 22003079
// HW4 - 14.05.2022
//

#include "Solutions.h"
#include <sstream>

string infix2prefix( const string exp ){

    Stack expr;
    expr.push( "(");

    string s1;
    string s2;

    int i = 0;

    while ( i < exp.length() ){

        s1 = exp[i];

        if ( i == exp.length() - 1){
            expr.push ( s1);
            break;
        }

        int j = i + 1;
        s2 = exp[j];

        while( s2 != " " ){
            if ( j == exp.length() - 1){
                s1 = s1 + s2;
                s2 = " ";
            }
            else {
                s1 = s1 + s2;
                j++;
                s2 = exp[j];
            }
        }

        expr.push ( s1);
        i = j + 1;

    }

    Stack final;
    Stack operators;

    string cur;
    string popped;


    while ( ! expr.isEmpty()) {
        expr.pop(cur);
        if (cur != "*" && cur != "+" && cur != "-" && cur != "/" && cur != " " && cur != ")" && cur != "(") {
            final.push(cur);
        } else if (cur == ")") {
            operators.push(cur);
        } else if (cur == "(") {
            string opr;
            operators.pop(opr);
            while (opr != ")" && !(operators.isEmpty())) {
                final.push(opr);
                operators.pop(opr);
            }
        }
        else if (  cur == "*" || cur == "+" || cur == "-" || cur == "/"){
            if ( operators.getSize() != 0) {
                operators.pop(popped);
                //operands.getTop(popped);

                while (!operators.isEmpty() && (popped == "+" || popped == "-" || popped == "*" || popped == "/")
                       && (getOperatorPrecedence(cur) <= getOperatorPrecedence(popped))) {
                    final.push(popped);
                    operators.pop(popped);
                }

                // push it back just in case it is "("
                operators.push(popped);
                operators.push(cur);
            }
            else {
                operators.push(popped);
                operators.push( cur);
            }
        }
    }

    string prefix = "";
    string character;

    while( ! final.isEmpty()){
        final.pop( character);
        prefix = prefix + character + " ";
    }

    return prefix.substr(0, prefix.length() - 1);

}

string infix2postfix( const string exp ){

    Stack expr;

    string s1;
    string s2;

    int i = 0;

    while ( i < exp.length() ){

        s1 = exp[i];

        if ( i == exp.length() - 1){
            expr.push ( s1);
            break;
        }

        int j = i + 1;
        s2 = exp[j];

        while( s2 != " " ){
            if ( j == exp.length() - 1){
                s1 = s1 + s2;
                s2 = " ";
            }
            else {
                s1 = s1 + s2;
                j++;
                s2 = exp[j];
            }
        }

        expr.push ( s1);
        i = j + 1;

    }

    expr.push( ")");

    Stack reversed;
    string rev;

    while ( ! expr.isEmpty()){
        expr.pop( rev);
        reversed.push( rev);
    }

    Stack operands;
    Stack final;

    string cur;
    string popped;

    string closedExp;


    while ( ! reversed.isEmpty()){
        reversed.pop( cur);
        if ( cur == "*" || cur == "+" || cur == "-" || cur == "/"){
            if ( operands.getSize() != 0) {
                operands.pop(popped);
                //operands.getTop(popped);

                while (!operands.isEmpty() && (popped == "+" || popped == "-" || popped == "*" || popped == "/")
                       && (getOperatorPrecedence(cur) <= getOperatorPrecedence(popped))) {
                    final.push(popped);
                    operands.pop(popped);
                }

                // push it back just in case it is "("
                operands.push(popped);
                operands.push(cur);
            }
            else {
                operands.push(popped);
                operands.push( cur);
            }

        }
        else if ( cur == ")"){
            string operand;
            operands.pop( operand);
            while ( !(operand == "(") && !(operands.isEmpty())) {
                final.push(operand);
                operands.pop( operand);
            }
        }
        else if ( cur != "*" && cur != "+" && cur != "-" && cur != "/" && cur != " " && cur != ")" && cur != "("){
            final.push( cur);
        }
        else if ( cur == "("){
            operands.push( cur);
        }
    }

    string postfix = "";
    string character;
    Stack finalReversed;

    while ( !final.isEmpty()){
        final.pop( character);
        finalReversed.push( character);
    }

    while( !finalReversed.isEmpty()){
        finalReversed.pop(character);
        postfix = postfix + character + " ";
    }

    return postfix.substr(0, postfix.length() - 1);


}

string prefix2infix( const string exp ){


    // by checking empty spaces add the values to the stack
    Stack expr;

    string s1;
    string s2;

    int i = 0;

    while ( i < exp.length() ){

        s1 = exp[i];

        if ( i == exp.length() - 1){
            expr.push ( s1);
            break;
        }

        int j = i + 1;
        s2 = exp[j];

        while( s2 != " " ){
            if ( j == exp.length() - 1){
                s1 = s1 + s2;
                s2 = " ";
            }
            else {
                s1 = s1 + s2;
                j++;
                s2 = exp[j];
            }
        }

        expr.push ( s1);
        i = j + 1;

    }

    // begin to convert to infix
    Stack final;

    string cur;
    string first;
    string second;
    string formed;
    string infix = "";

    while ( ! expr.isEmpty()){
        expr.pop( cur);

        if ( cur != "*" && cur != "+" && cur != "-" && cur != "/" && cur != " " && cur != ")" && cur != "(" ){
            final.push( cur);
        }
        else if ( cur == "*" || cur == "+" || cur == "-" || cur == "/"){
            final.pop( first);
            final.pop( second);
            formed = "( " + first + " " + cur + " " + second + " )";
            final.push( formed);
        }
    }

    if ( final.getSize() == 1){
        final.pop(infix);
    }

    return infix.substr(2, infix.length() - 3);

}

void evaluatePrefix( const string exp ){
    string st;
    st = prefix2postfix( exp);
    cout << evaluatePostfix( st) << endl;
    return;

}

string prefix2postfix( const string exp ){

    string tempExp;
    string finalExp;

    tempExp = prefix2infix( exp);
    finalExp = infix2postfix( tempExp);

    return finalExp;

}

double evaluatePostfix( const string exp ){
    Stack expr;

    string s1;
    string s2;

    int i = 0;

    while ( i < exp.length() ){

        s1 = exp[i];

        if ( i == exp.length() - 1){
            expr.push ( s1);
            break;
        }

        int j = i + 1;
        s2 = exp[j];

        while( s2 != " " ){
            if ( j == exp.length() - 1){
                s1 = s1 + s2;
                s2 = " ";
            }
            else {
                s1 = s1 + s2;
                j++;
                s2 = exp[j];
            }
        }

        expr.push ( s1);
        i = j + 1;

    }

    Stack reversed;
    string rev;

    while ( ! expr.isEmpty()){
        expr.pop( rev);
        reversed.push( rev);
    }


    Stack calculator;

    string cur;
    string rslt;
    string first;
    string second;
    string final;
    int finalResult;

    int f;
    int s;
    int result;

    while ( ! reversed.isEmpty()){
        reversed.pop( cur);

        if( cur != "*" && cur != "+" && cur != "-" && cur != "/" && cur != " " ){
            calculator.push( cur);
        }
        else if ( cur == "*" || cur == "+" || cur == "-" || cur == "/" ){
            calculator.pop( first);
            calculator.pop( second);

            f = stringToInt( first);
            s = stringToInt( second);

            if ( cur == "*"){
                result = s * f;
            }
            else if ( cur == "+"){
                result = f + s;
            }
            else if ( cur == "-"){
                result = s - f;
            }
            else if ( cur == "/"){
                result = s / f;
            }

            rslt = intToString( result);

            calculator.push( rslt);

        }
    }

    calculator.pop( final);

    finalResult = stringToInt( final);

    return finalResult;
}

int getOperatorPrecedence(string opr) {
    int precedence;

    if( opr == "*" || opr == "/"){
        precedence = 2;
    }
    else if ( opr == "+" || opr == "-"){
        precedence = 1;
    }
    else {
        precedence = 0;
    }

    return precedence;
}

int stringToInt(string st) {
   stringstream degree(st);
   int x = 0;
   degree >> x;
   return x;
}

string intToString(int integer) {
    return to_string(integer);
}


