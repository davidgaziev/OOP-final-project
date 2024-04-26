using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/room.hh"
#include "./../include/hospital.hh"

room::room()
{
    id = -1;
    P.id = -1;
    N.id = -1;
    free = false;
}
void room::fillMap()
{
    fstream f;
    f.open("./data/rooms.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        room a;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, s2, s3, s4;
        //reading from the string stream object 's';
        getline(s, s1, ',');
        getline(s, s2, ','); 
        getline(s, s3, ',');
        getline(s, s4, ',');
        a.id = strToNum(s1);
        a.P = hospital::patientsList[strToNum(s2)];
        a.N = hospital::nursesList[strToNum(s3)];
        a.free = (s4 == "Y");
        hospital::roomsList[a.id] = a;
    }
    f.close();
    return;
}
void room::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "roomId,patientId,nurseId,free\n";
    for (auto i : hospital::roomsList)
        f << i.second.id << "," << i.second.P.id << "," << i.second.N.id
        << "," << i.second.free << endl;
    f.close();
    remove("./data/rooms.csv");
    rename("./data/temp.csv", "./data/rooms.csv");
    return;
}
void room::printDetails()
{
    if (id == -1)
        return;
    cout << "\n\n\nДетали палаты:\nНомер                 : " << id << "\n"
        << "Имя пациента     : " + P.firstName + " " + P.lastName + "(ID = " << P.id << ")\n"
        << "Имя медсестры      : " + N.firstName + " " + N.lastName + "(ID = " << N.id << ")\n";
    return;
}
int room::addRoom(patient& p)
{
    P = p;
   
    char ans;
    cout << "\n\nНазначьте медсестру к палате:\n";

    ans = 'Y';
    while (ans == 'Y') {
        N.getDetails();
        ans = 'K';
        if (N.id == -1)
        {
            cout << "Повторите попытку (Y : Да || N : Нет)?\n";
            cin >> ans;
            while (ans != 'Y' && ans != 'N')
            {
                cout << "Y или N?\n";
                cin >> ans;
            }
        }
        else if (N.r > 0)
        {
            cout << "Извините, эта медсестра назначена к другой палате\n";
            cout << "Выбрать другую медсестру (Y : Да || N : Нет)?\n";
            cin >> ans;
            while (ans != 'Y' && ans != 'N')
            {
                cout << "Y или N?\n";
                cin >> ans;
            }
        }
       /* if (hospital::nursesList.find(reqId) != hospital::nursesList.end())
            if (hospital::nursesList[reqId].r >= 1) {

            }
        cout << hospital::nursesList[reqId].firstName;
            else
                cout << "\nНет медсестры с таким ID!\n";*/
        
    }

    if (ans == 'N') {
        return -1;
    }

    cout << "\nВведите номер комнаты: ";
    cin >> id;

    if (hospital::roomsList.find(id) != hospital::roomsList.end()) {
        do {
            if (!hospital::roomsList[id].free) {
                cout << "Эта палата уже занята! Введите другую!\n";
            }

            cout << "\nВведите номер комнаты: ";
            cin >> id;

        } while (!hospital::roomsList[id].free);
    }

    hospital::roomsList[id] = *this;

    hospital::patientsList[P.id].r = id;
    hospital::nursesList[N.id].r = id;
    
    return 1;
}
void room::getDetails()
{
    cout << "\nВведите номер палаты:\n";
    cin >> id;
    if (hospital::roomsList.find(id) == hospital::roomsList.end())
    {
        cout << "\nНеверный номер палаты!\n";
        id = -1;
        return;
    }
    *this = hospital::roomsList[id];
    return;
}

void room::freeRoom() 
{
    cout << "\nПоиск палаты для удаления.\n";
    getDetails();
    if (id == -1)
        return;
    hospital::roomsList.erase(id);
    hospital::patientsList[P.id].r = -1;
    hospital::patientsList[P.id].hospitalized = false;
    hospital::nursesList[N.id].r = -1;
  
    cout << "Палата #" << id << " освобождена!\n";
    return;
}