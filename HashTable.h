#include <list>
#include <string>
#include <vector>
using namespace std;
class HashTable{

public:
    HashTable(int size);
    void insert(string name, int index);
    void remove(string name, int index);
    bool exists(string name, int index);
    void lookup(string name, int index);
    int hash(string name, int coefficients1, int coefficients2, int coefficients3, int coefficients4);      //hash function
    int advanceHash(string name, int exponent, int prime,vector<int> vect); //advanced hash function
    void print();
    int getInsertNumber();
    int getDeleteNumeber();
    int getEmptySlots();
    int getOneItemSlot();
    int getCollisionNumber();
    int getCollisionIndex();

private:
    vector<list<string> > table;
    int size;
    int insertNumebr;
    int deleteNumber;
    int maxCollisionNumber;
    int maxCollisionIndex;
};
