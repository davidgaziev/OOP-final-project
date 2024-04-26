#ifndef PATIENT
#define PATIENT
using namespace std;

#include "./person.hh"

class appointment;
class room;
class patient : public person
{
private:
    int height; 
    int weight;
    bool hospitalized;
    bool alive;
    int r;
    friend class appointment;
    friend class room;

public:
    patient();
    void fillMap();
    void saveMap();
    void addPerson();
    void printDetails();
    void printDetailsFromHistory(string extraDetails = "");
    void getDetails(int rec = 0);
    void getDetailsFromHistory();
    void hospitalize();
    void reportADeath();
    void removePerson();
};
#endif // !PATIENT