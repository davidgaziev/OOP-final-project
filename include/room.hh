#ifndef ROOM
#define ROOM
using namespace std;

#include "./patient.hh"
#include "./nurse.hh"

class room 
{
private:
    int id;
    patient P;
    nurse N;
    bool free;
public:
    room();
    void fillMap();
    void saveMap();
    void printDetails();
    int addRoom(patient& p);
    void getDetails();
    void freeRoom();
};
#endif // !ROOM
