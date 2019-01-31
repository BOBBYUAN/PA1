#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include <cmath>
#include "HashTable.h"
using namespace std;
string DecimalToBinaryString(int a)
{
    uint b = (uint)a;
    string binary = "";
    uint mask = 0x80000000u;
    while (mask > 0)
    {
        binary += ((b & mask) == 0) ? '0' : '1';
        mask >>= 1;
    }
    cout<<binary<<endl;
    return binary;
}
//https://stackoverflow.com/questions/3061721/concatenate-boostdynamic-bitset-or-stdbitset
template <size_t N1, size_t N2, size_t N3, size_t N4>
bitset <N1 + N2 + N3 + N4> concat( const bitset <N1> & b1, const bitset <N2> & b2, const bitset <N3> & b3, const bitset <N4> & b4 ) {
    string s1 = b1.to_string();
    string s2 = b2.to_string();
    string s3 = b3.to_string();
    string s4 = b4.to_string();
    return bitset <N1 + N2 + N3 + N4>( s1 + s2 + s3 + s4);
}
//https://www.programiz.com/cpp-programming/examples/binary-decimal-convert
int convertBinaryToDecimal(long long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder * pow(2,i);
        ++i;
    }
    return decimalNumber;
}

HashTable::HashTable(int size){
    this->size = size;
    table.resize(size);
    this->insertNumebr = 0;
    this->deleteNumber = 0;
    this->maxCollisionNumber = 0;
    this->maxCollisionIndex = 0;
}

// here is my hash function
int HashTable::hash(string name, int coefficients1, int coefficients2, int coefficients3, int coefficients4){
    int byte1, byte2, byte3, byte4;
    char dot;
    istringstream s(name);
    s >> byte1 >> dot >> byte2 >> dot >> byte3 >> dot >> byte4 >> dot;
    int sum = ( byte1 * coefficients1 + byte2 * coefficients2 + byte3 * coefficients3 + byte4 * coefficients4);
    int index = sum % 257;  // need to change
    return index;
}

int HashTable::advanceHash(string name, int exponent, int prime,vector<int> vect)
{
    int byte1, byte2, byte3, byte4;
    char dot;
    istringstream s(name);
    s >> byte1 >> dot >> byte2 >> dot >> byte3 >> dot >> byte4 >> dot;
    bitset<8> bin_x1(byte1);
    bitset<8> bin_x2(byte2);
    bitset<8> bin_x3(byte3);
    bitset<8> bin_x4(byte4);
    string mystring =
    concat(bin_x1, bin_x2,bin_x3,bin_x4).to_string<char,std::string::traits_type,std::string::allocator_type>();
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
    vector<int> groupKeys;
    string firstPartString = mystring.substr (0,firstPartLength);

    int firstKey = stoi(firstPartString);
    int firstKeyInDecimal = convertBinaryToDecimal(firstKey);
    groupKeys.push_back(firstKeyInDecimal);

    for (int i = 0; i<(totalParts-1); i++) {
        string keyString = mystring.substr(firstPartLength + i * exponent,exponent);
        int key = stoi(keyString);
        int keyInDecimal = convertBinaryToDecimal(key);
        groupKeys.push_back(keyInDecimal);
    }
    int sum = 0;
    int a [8] = { 10, 11, 5, 14, 3, 8, 2, 13 };  //test hardcode
    int b [4] = {96, 910, 643, 104};  //test case No.2
    int c [4] = {136,124,159,127};
    int d [6] = {58,20,9,55,24,9};
        for (int i = 0; i<groupKeys.size(); i++) {
            groupKeys[i] = groupKeys[i] * vect[i];
            sum = sum + groupKeys[i];
        }
    int index = sum % prime;
    return index;
}

bool HashTable::exists(string name, int index){
    list<string>::iterator it;
    for(it = table[index].begin(); it != table[index].end(); it++){
        if(name.compare(*it) == 0){
            return true;
        }
    }
    return false;
}

void HashTable::lookup(string name, int index){
    if (exists(name, index)) {
        cout << name << ": found." << endl;
    } else {
        cout << name << ": not found." << endl;
    }
}

void HashTable::insert(string name, int index){
    if(exists(name, index)){
        cout << name << " already exists" << endl;
        return;
    }
    table[index].push_back(name);
    insertNumebr += 1;
    return;
}

void HashTable::remove(string name, int index){
    list<string>::iterator it;
    for(it = table[index].begin(); it != table[index].end(); it++){
        if(name.compare(*it) == 0){
            table[index].erase(it);
            deleteNumber += 1;
            return;
        }
    }
    cout << "Error : could not delete " <<name << " because it does not exist." << endl;
    return;
}

void HashTable::print(){
    for(int i = 0; i < size; i++){
        list<std::string>::iterator it;
        cout << i << ": ";
        for(it = table[i].begin(); it != table[i].end(); it++){
            cout << *it << ' ';
        }
        cout << endl;
    }
}

int HashTable::getDeleteNumeber()
{
    return this->deleteNumber;
}

int HashTable::getInsertNumber()
{
    return this->insertNumebr;
}

int HashTable::getEmptySlots()
{
     int emptySlots = 0;
    for(int i = 0; i < size; i++){
        list<std::string>::iterator it;
        if (table[i].empty()) {
            emptySlots += 1;
        }
    }
    return emptySlots;
}

int HashTable::getOneItemSlot()
{
    int oneItemSlot = 0;
    for(int i = 0; i < size; i++){
        list<std::string>::iterator it;
        if (table[i].size() == 1) {
            oneItemSlot += 1;
        }
    }
    return oneItemSlot;
}

int HashTable::getCollisionIndex()
{
    for(int i = 0; i < size; i++){
        list<std::string>::iterator it;
        if (table[i].size() > maxCollisionNumber) {
            maxCollisionIndex = i;
            maxCollisionNumber = table[i].size();
        } else if (table[i].size() == maxCollisionNumber) {
            if (i > maxCollisionIndex) {
                maxCollisionIndex = i;
            }
        }
    }
    return maxCollisionIndex;
}

int HashTable::getCollisionNumber()
{
    return this->maxCollisionNumber;
}
