//
//  main.cpp
//  testHash
//
//  Created by Yuan WangCheng on 1/20/19.
//  Copyright © 2019 WangCheng Yuan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <map>
#include "HashTable.h"
using namespace std;
bool IsPrime(int number)
{
    if (number == 2 || number == 3)
        return true;
    if (number % 2 == 0 || number % 3 == 0)
        return false;
    int divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= number)
    {
        if (number % (divisor - 1) == 0)
            return false;
        if (number % (divisor + 1) == 0)
            return false;
        divisor += 6;
    }
    return true;
}

int NextPrime(int a)
{
    while (!IsPrime(++a))
    {
    }
    return a;
}

int main(int argc, char *argv[]){
    string input;
    int size;
    int prime;
    cin >> size;
    prime = NextPrime(size);
    HashTable ht(prime);
    // int a1 = 162;
    // int a2 = 210;
    // int a3 = 89;
    // int a4 = 10;
    srand(time(0));
    int a1 = rand() % 256;
    int a2 = rand() % 256;
    int a3 = rand() % 256;
    int a4 = rand() % 256;
    while(cin >> input){
        if (input == "insert"){
            cin >> input;
            int index = ht.hash(input,a1,a2,a3,a4);
            ht.insert(input,index);
        }
        else if (input == "lookup"){
            cin >> input;
            int index = ht.hash(input,a1,a2,a3,a4);
            ht.lookup(input,index);
        }
        else if (input == "delete"){
            cin >> input;
            int index = ht.hash(input,a1,a2,a3,a4);
            ht.remove(input,index);
        }
        else if (input == "stat"){
            cout << a4 << " " << a3 << " " << a2 << " " << a1 << endl;
            int x = ht.getInsertNumber();
            cout << x <<endl;
            int y = ht.getDeleteNumeber();
            cout << y <<endl;
            int z = ht.getEmptySlots();
            cout << z <<endl;
            int w = ht.getOneItemSlot();
            cout << w <<endl;
            cout << ht.getCollisionNumber() << " ";
            cout << ht.getCollisionIndex() <<endl;
        }
        else continue;
          ht.getCollisionNumber();
          ht.getCollisionIndex();
    }
            return 0;
}


