// Update: 6:35pm 9 Mar, 2020
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// UTILITY FUNCTIONS
void StringSpaceRemove(string &);
string StringSplit(string, unsigned short, unsigned short);
string Num2Str(int);
int ParseInt(string);
float ParseFloat(string);
bool IsNumber(char);

// Khem's Functiions
void ReadExpr(string, unsigned short);
string Diff(string, char);

// Leng's Functions
void PrintResult(vector<string>, unsigned short);
string ImplicitFunc(string);
float cal(string, float);
float implicit_cal(string, float, float);

// Dan's Functions
//graph

// Mhee's Functions

int main() {
    string expr, blank;
    unsigned short option;
    
    do {
        cout << "Enter f(x) = ";
        getline(cin, expr);
        
        cout << "Press: \t[1] to evaluate the function.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();
        
        cout << "The result is...\n\n";
        
        switch (option) {
            case 1: ReadExpr(expr, 1); break;
            case 2: ReadExpr(expr, 2); break;
            case 3: ReadExpr(expr, 3); break;
        }
        
        cout << "Press 'enter' to continue...";
        getline(cin, blank);
        cout << endl;
        
        cout << "Press: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n\t";
        cout << "[4] to try a new expression.\n\t[5] to end the program.\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();
        
    } while (option != 5);

    return 0;
}

void ReadExpr(string expr, unsigned short option) {
    vector<string> term;
    string signs = "";
    
    unsigned short leftPar = 0, rightPar = 0;
    
    // pre-reading process
    StringSpaceRemove(expr);
    
    // reading equation process
    unsigned short splitIndex = 0;
    for (unsigned short i = 0; i < expr.size(); i++) {
        if (expr[i] == '(') leftPar++;
        else if (expr[i] == ')') rightPar++;
        
        if ((expr[i] == '+' || expr[i] == '-') && expr[i-1] != '^' && leftPar == rightPar) {
            term.push_back(StringSplit(expr, splitIndex, i));
            signs += expr[i];
            splitIndex = i + 1;
        }
        
        if (i >= expr.size() - 1) {
            term.push_back(StringSplit(expr, splitIndex, expr.size()));
        }
    }

    // check for errors
    if (leftPar != rightPar) throw "Bad arithmetic expression: no complete pair of parentheses ['()'].";

    PrintResult(term, option);
}

void PrintResult(vector<string> term, unsigned short option) {

    // ++ simplify each term

    string result = "";
    float cal_equation = 0;

    switch (option) {
        case 1: { // Eval
            float x;

            cout<<"Please enter x value : ";
            cin>>x;
            cout<<"f(x) = "<<cal(term,x);
            
        } break;
        case 2: { // Diff
            result = "f'(x) = ";
            for (unsigned short i = 0; i < term.size(); i++) {
                result += Diff(term[i], 'x') + signs[i];
            }
        } break;
        case 3: { // Impl
            result = "dy/dx = ";
            for (unsigned short i = 0; i < term.size(); i++) {      //not yet
                result += Diff(term[i], 'x') + signs[i];
            }
        } break;
        case 4:{

            result = "dx/dy = ";
            for
        }
        case 5:{

            float x,y;

            cout<<"Please enter x and y values : ";
            cin>>x>>y;
            cout<<"f(x) = "<<implicit_cal(term,x,y);
        }
    }

    // ++ re-arrange the result; cleaner result

    cout << result << "\n\n";
}


// main derivative function
string Diff(string term, char var) {
    vector<string> u, trigon;
    vector<unsigned short> trigonIndex, varIndex;
    
    for (unsigned short i = 0; i < term.size(); i++) {
        // find (type): position and #of x
        if (term[i] == var) {
            varIndex.push_back(i);
        }
        
        // find (type): trigonometric function.
        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i+4<term.size()) {
            string tfunc = StringSplit(term, i, i+3);
            
            if (tfunc == "sin" || tfunc == "cos" || tfunc == "tan" || tfunc == "csc" || tfunc == "sec" || tfunc == "cot") {
                
                unsigned short leftPar = 0, rightPar  = 0;
                trigonIndex.push_back(i);
                string tempU = "";
                
                if (term[i+3] == '^') { // find: a*sin^n(u)
                    i+=4; // skip 'sin^'
                    while (IsNumber(term[i])) i++;
                    
                    leftPar++;
                    tempU = term[i++];
                    while (i < term.size() && leftPar != rightPar) {
                        if (term[i] == '(') leftPar++;
                        else if (term[i] == ')') rightPar++;
                        
                        tempU += term[i++];
                    }
                    
                    u.push_back(tfunc + tempU);
                }
                else { // find: a*sin(u) or a*sin^1(u)
                    trigon.push_back(tfunc);
                    
                    i+=4; // skip 'sin('
                    while (i < term.size() && (term[i] != ')' || leftPar != rightPar)) {
                        if (term[i] == '(') leftPar++;
                        else if (term[i] == ')') rightPar++;
                        
                        tempU += term[i++];
                    }
                    u.push_back(tempU);
                }
            }
        }
        
        // find (type): logarithm function
        else if (term[i] == 'l' && i+2<term.size()) {
            string l;
            if (StringSplit(term, i, i+3) == "lon") {
                l = "lon";
            }
            else if (StringSplit(term, i, i+2) == "ln") {
                l = "ln";
            }
        }
    }
    
    if (varIndex.size() == 0 && u.size() == 0) return "";
    if (term.size() == 1 && term[0] == var) return "1";
    
    string result = "";
    int n, a;
    
    // main diff function in many cases below...
    if (u.size() == 0) {
        switch (term[varIndex[0] + 1]) {
            case '^': { // case: ax^n
                unsigned short tpos = varIndex[0] + (term[varIndex[0] + 2] == '(' ? 3 : 2);
                
                a = varIndex[0] == 0 ? 1 : ParseInt(StringSplit(term, 0, varIndex[0]));
                n = ParseInt(StringSplit(term, tpos, term.size()));
                
                string strN = "";
                for (unsigned short i = tpos; i < term.size() && IsNumber(term[i]); i++) {
                    strN += term[i];
                }
                
                if (n - 1 == 0)
                    result = Num2Str(a*n);
                else if (n - 1 == 1)
                    result = Num2Str(a*n) + "x";
                else
                    result = Num2Str(a*n) + "x^" + to_string(n-1);
            } break;
            case '(': { // case: ax^(n)
                
            } break;
            case '*': { // case: ax*(n) or ax*(u)
                
            } break;
            default: { // case ax or ax^1
                result = StringSplit(term, 0, varIndex[0]);
            }
        }
    }
    else {
        if (trigon.size() > 0) { // case: a*sin(u) or a*sin^1(u)
           if (trigon[0] == "sin") trigon[0] = "cos";
            else if (trigon[0] == "cos") trigon[0] = "-sin";
            else if (trigon[0] == "tan") trigon[0] = "sec^2";
            else if (trigon[0] == "csc") trigon[0] = "-csc()*cot()";
            else if (trigon[0] == "sec") trigon[0] = "sec()*tan()";
            else if (trigon[0] == "cot") trigon[0] = "-csc^2";
            
            a = trigonIndex[0] == 0 ? 1 : ParseInt(term);
            
            string chainDiff = Diff(u[0], var);
            bool hasSign = false;
            bool hasXorU = false;
            
            for (unsigned short i = 0; i < chainDiff.size(); i++) {
                if (chainDiff[i] == '+' || chainDiff[i] == '-') {
                    hasSign = true;
                }
                else if (chainDiff[i] == var) {
                    hasXorU = true;
                }
            }
            
            if (hasSign)
                result = Num2Str(a) + trigon[0] + "(" + u[0]  + ")*(" + chainDiff + ")"; 
            else if (hasXorU)
                result = Num2Str(a) + trigon[0] + "(" + u[0]  + ")*" + chainDiff;
            else
                result = Num2Str(a*ParseInt(chainDiff)) + trigon[0] + "(" + u[0]  + ")";
        }
        else if (trigonIndex.size() > 0) { // case: a*sin^n(u)
            a = trigonIndex[0] == 0 ? 1 : ParseInt(term);
            n = ParseInt(StringSplit(term, trigonIndex[0] + 4, term.size()));
            string chainDiff = Diff(u[0], var);
            
            unsigned short fisrtParPos = 0;
            for (unsigned short i = 0; i < u[0].size() && u[0][i] != '('; i++) { // find fisrt '(' pos
                fisrtParPos++;
            }
            
            if (n-1 == 1)
                result = Num2Str(a*n) + u[0] + "*" + chainDiff;
            else {
                string tempBlock = StringSplit(u[0], fisrtParPos, u[0].size());
                result = Num2Str(a*n) + StringSplit(u[0], 0, 3) + "^" + to_string(n-1) + tempBlock + "*" + chainDiff; 
            }
        }
    }
    
    return result;
}

float cal(string t, float x){

    float cal_result = 0;

    for(int i=0; i<t.size(); i++){

        if(t[i] = "x") 
            t[i] = x;

        cal_result += ;
    }
    
    return cal_result;
}

float implicit_cal(string t, float x, float y){

    float cal_result = 0;

    for(int i=0; i<t.size(); i++)
        if(t[i] = "x")
            t[i] = x;
        if(t[i] = "y")
            t[i] = y;
    
    cal_result +=   ;
    
}

// UTILITY FUNCTIONS
void StringSpaceRemove(string &t) {
    string result = "";
    for (unsigned short i = 0; i < t.size(); i++) {
        if (t[i] != ' ')
            result += t[i];
    }
    
    t = result;
}

string StringSplit(string t, unsigned short from, unsigned short to) {
    string result = "";
    for (unsigned short i = from; i < to; i++) {
        result += t[i];
    }
    
    return result;
}

string Num2Str(int n) {
    if (n == 1) {
        return "";
    }
    else {
        return to_string(n);
    }
}

int ParseInt(string t) {
    return atoi(t.c_str());
}

float ParseFloat(string t) {
    return atof(t.c_str());
}

bool IsNumber(char t) {
    return (t >= 46 && t <= 57);
}

string ImplicitFunc(string t){

    int choice;
    
    cout<<"Press: \t[1] to evaluate dy/dx\n\t[2] to evaluate dx/dy\n";
    cout << "=>\t";
    cin>>choice;
    cin.ignore();
    
    if(choice == 1){    // dy/dx
        string result;

        ReadExpr(t, 3);

        result = "";
        
        
        return result;
    }
    
    else if (choice == 2){      //dx/dy
        
        string result;
        
        result = "";
        
        
        
        return result;
    }
    
    else    return "Please enter 1 or 2";
}