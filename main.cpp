
#include<bits/stdc++.h>
#include "bigInt.h"
using namespace std;
int main(){

    
    BigInt num1, num2;

    cout << "Enter two large numbers:" << endl;
    cin >> num1 >> num2;

    cout << "You entered:" << endl;
    cout << "Number 1: " << num1 << endl;
    cout << "Number 2: " << num2-num1 << endl;


    return 0;
}