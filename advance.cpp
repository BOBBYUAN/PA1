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

int getExponent(int input)
{
    int exponent = 0;
    while (input % 2 != 1) {
        input = input /2;
        exponent ++;
    }
    return exponent;
}

int main(int argc, char *argv[]){
    string input;
    int size;
    int prime;
    int exponent;
    cin >> size;
    exponent = getExponent(size);
    prime = NextPrime(size);
    vector<int> random;
    int reminder = 32 % exponent;
    int totalParts = 0;
    int firstPartLength = 0;
    if ((32 % exponent) == 0) {
        totalParts = 32 / exponent;
        firstPartLength = exponent;
    } else {
        totalParts = 1 + ((32 - reminder) / exponent) ;
        firstPartLength = reminder;
    }
    srand(time(0));
    for (int i = 0; i<totalParts; i++) {
        int randomNumber = rand() % (prime-1);
        random.push_back(randomNumber);
    }
    HashTable ht(prime);
    while(cin >> input){
        if (input == "insert"){
            cin >> input;
            int index = ht.advanceHash(input,exponent,prime,random);
            ht.insert(input,index);
        }
        else if (input == "lookup"){
            cin >> input;
            int index =  ht.advanceHash(input,exponent,prime,random);
            ht.lookup(input,index);
        }
        else if (input == "delete"){
            cin >> input;
            int index =  ht.advanceHash(input,exponent,prime,random);
            ht.remove(input,index);
        }
        else if (input == "stat"){
             for (int i = 0; i < random.size(); i++)
           {
            cout << random[i] << " ";
           }
            cout << endl;
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


