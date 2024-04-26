using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/ambulance.hh"
#include "./../include/hospital.hh"

ambulance::ambulance()
{
    id = -1;
    add.strToAdd("`````");
    D.id = -1;
}
void ambulance::fillMap()
{
    fstream f;
    f.open("./data/ambulances.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        ambulance a;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, s5, s6, s7;
        //reading from the string stream object 's';
        getline(s, s1, ',');
        getline(s, a.model, ',');
        getline(s, a.manufacturer, ',');
        getline(s, a.vrn, ',');
        getline(s, s5, ',');
        getline(s, s6, ',');
        getline(s, s7, ',');
        a.id = strToNum(s1);
        a.idle = (s5 == "Y");
        if (!a.idle)
        {
            a.add.strToAdd(s6);
            a.D = hospital::driversList[strToNum(s7)];
        }
        hospital::ambulancesList[a.id] = a;
    }
    f.close();
    return;
}
void ambulance::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "ambulanceId,model,manufacturer,vrn,idle?,headedTowards(ifNotIdle),driverID(ifNotIdle)\n";
    for (auto i : hospital::ambulancesList)
    {
        f << i.second.id << "," << i.second.model << "," << i.second.manufacturer << "," << i.second.vrn
          << "," << (i.second.idle ? ("Y,NA,NA\n") : ("N," + i.second.add.addToStr() + ","));
        if (!(i.second.idle))
        {
            f << i.second.D.id << endl;
        }
    }
    f.close();
    remove("./data/ambulances.csv");
    rename("./data/temp.csv", "./data/ambulances.csv");
    return;
}
void ambulance::addAmbulance()
{
    if (hospital::ambulancesList.size() == hospital::ambulancesLimit)
    {
        cout<<"\n\n��������� ����� ������ ������, ���������� �������� ������!\n\n";
        return;
    }
    //getting the basic details of the ambulance from the user side;
    cout << "\n������� ������ ������ ������:\n";
    getline(cin >> ws, model);
    cout << "\n������� ����� ������ ������:\n";
    getline(cin >> ws, manufacturer);
    cout << "\n������� ����� ���� ������ ������:\n";
    getline(cin >> ws, vrn);
    if (hospital::ambulancesList.rbegin() != hospital::ambulancesList.rend())
        id = ((hospital::ambulancesList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::ambulancesList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in ambulancesHistory.csv;
    f.open("./data/ambulancesHistory.csv", ios::app);
    f << model << "," << manufacturer << "," << vrn << ",Y" << endl;
    f.close();

    cout << "\n"
         << model << " �� " << manufacturer << " ������� ���������!\n";
    cout << "ID: " << id << "\n";
}
void ambulance::printDetails()
{
    if (id == -1)
        return;
    cout << "������:\n";
    cout << "ID                  : " << id << "\n";
    cout << "�����               : " << manufacturer << "\n";
    cout << "������              : " << model << "\n";
    cout << "�����               : " << vrn << "\n";
    cout << "��������?           : " << ((idle) ? "�" : "�") << "\n";
    if (!idle)
    {
        cout << "���� � ������: ";
        add.print();
        cout << "ID ��������       : " << D.id << "\n";
    }
    return;
}
void ambulance::printDetailsFromHistory(string extraDetails)
{
    if (id == -1)
        return;
    if (extraDetails == "")
    {
        fstream f;
        f.open("./data/driversHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            ambulance a;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4;
            //reading from the string stream object 's';
            getline(s, a.model, ',');
            getline(s, a.manufacturer, ',');
            getline(s, s4, ',');

            if (vrn == s4)
            {
                getline(s, extraDetails, ',');
            }
        }
        f.close();
    }
    cout << "������         : " << model << "\n";
    cout << "�����          : " << manufacturer << "\n";
    cout << "����� ����     : " << vrn << "\n";
    cout << "�������?       : " << extraDetails << "\n";
    return;
}
void ambulance::getDetails(int rec)
{
    int opt = 0;
    cout << "\n�������� ������:\n[1]: �� ID\n[2]: �� ������\n[3]: �� ������ ����\n\n";
    cin >> opt;
    while (opt != 1 && opt != 2 && opt != 3)
        cout << "������� 1, 2 ��� 3?\n", cin >> opt;
    //1: Filter by ID;
    if (opt == 1)
    {
        int reqId;
        cout << "\n������� ID:\n";
        cin >> reqId;
        if (hospital::ambulancesList.find(reqId) != hospital::ambulancesList.end())
            *this = hospital::ambulancesList[reqId];
        else
            cout << "\n��� �������!\n";
    }
    //2: Filter by model;
    else if (opt == 2)
    {
        string reqModel;
        cout << "������:\n";
        getline(cin >> ws, reqModel);
        vector<ambulance> matchingRecords;
        for (auto i : hospital::ambulancesList)
        {
            if (i.second.model == reqModel)
                matchingRecords.push_back(i.second);
        }
        cout << "\n";
        cout << matchingRecords.size() << " ���������� ������� �������!\n";
        for (auto i : matchingRecords)
            i.printDetails();
        char tt = 'N';
        if (matchingRecords.size() > rec)
        {
            do
            {
                int reqId;
                cout << "\n������� ID ������ ������ ������: ";
                cin >> reqId;
                if (hospital::ambulancesList.find(reqId) != hospital::ambulancesList.end())
                    *this = hospital::ambulancesList[reqId];
                else
                {
                    cout << "\n�������� ID!\n��������� �������? (Y = �� ��� N = ���)\n";
                    cin >> tt;
                    while (tt != 'Y' || tt != 'N')
                        cout << "Y ��� N?\n", cin >> tt;
                }
            } while (tt == 'Y');
        }
    }
    //3: Filter by vehicle reg. number;
    else if (opt == 3)
    {
        string reqVRN;
        cout << "������� ����� ���� ������ ������ ������:\n";
        getline(cin >> ws, reqVRN);
        for (auto i : hospital::ambulancesList)
        {
            if (i.second.vrn == reqVRN)
            {
                *this = i.second;
                return;
            }
        }
        //if a record is found, it's details will be stored in the driver class object that called this function,
        //and the control is returned;
        //else:
        cout << "\n��� �������!\n";
    }
    return;
}
void ambulance::getDetailsFromHistory()
{
    int opt = 0;
    cout << "\n�������� ������:\n[1]: �� ������\n[2]: �� ������ ����\n\n";
    cin >> opt;
    while (opt != 1 && opt != 2)
        cout << "������� 1 ��� 2?\n", cin >> opt;

    //1: Filter by model;
    if (opt == 1)
    {
        string reqModel;
        cout << "������:\n";
        getline(cin >> ws, reqModel);
        vector<ambulance> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/ambulancesHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            ambulance a;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4;
            bool owned;
            //reading from the string stream object 's';
            getline(s, a.model, ',');

            if (a.model == reqModel)
            {

                getline(s, a.manufacturer, ',');
                getline(s, a.vrn, ',');
                getline(s, s4, ',');
                a.id = 0;
                matchingRecords.push_back(a);
                extraDetails.push_back(s4);
            }
        }
        f.close();
        cout << "\n";
        cout << matchingRecords.size() << " ���������� ������� �������!\n";
        for (int i = 0; i < matchingRecords.size(); i++)
            matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
    }
    //2: Filter by vrn;
    else if (opt == 2)
    {
        string reqVRN;
        cout << "������� ����� ���� ������ ������ ������:\n";
        getline(cin >> ws, reqVRN);
        vector<ambulance> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/ambulancesHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4;
            //reading from the string stream object 's';
            getline(s, model, ',');
            getline(s, manufacturer, ',');
            getline(s, vrn, ',');
            if (vrn == reqVRN)
            {
                getline(s, s4, ',');
                id = 0;
                printDetailsFromHistory(s4);
                return;
            }
        }
        f.close();
        //if a record is found, it's details will be stored in the ambulance class object that called this function,
        //and the control is returned;
        //else:
        cout << "\n��� �������!\n";
    }
    return;
}
void ambulance::send()
{

    //*************picking an idle ambulance*************;

    bool gotOne = 0;
    for (auto i : hospital::ambulancesList)
    {
        if (i.second.idle)
        {
            *this = i.second;
            gotOne = 1;
            break;
        }
    }
    if (!gotOne)
    {
        cout << "��� ��������� ������ ������!"
             << "\n";
        return;
    }
    //*************  picking a free driver  *************;

    gotOne = 0;
    for (auto i : hospital::driversList)
    {
        if (i.second.idle)
        {
            D = i.second;
            gotOne = 1;
            break;
        }
    }
    if (!gotOne)
    {
        cout << "��� ��������� ���������!"
             << "\n";
        return;
    }

    idle = 0;

    cout << "������� �����:\n";
    add.takeInput();

    //updating status of ambulance;
    hospital::ambulancesList[id] = *this;

    //updating status of driver;
    hospital::driversList[D.id].idle = 0;

    cout << model << " �� " << manufacturer << " ���������� � ��������� " << D.firstName << " " << D.lastName << " (ID = " << D.id << ") �������!\n";
    return;
}
void ambulance::reportArrival()
{
    getDetails();

    //updating status of driver;
    //note that if we first update the status of ambulance we will lose the identity of it's driver;
    //and then there will be no way to update the status of the driver;
    hospital::driversList[D.id].idle = 1;

    //updating status of ambulance;
    hospital::ambulancesList[id].idle = 1;
    hospital::ambulancesList[id].add.strToAdd("`````");
    driver d;
    hospital::ambulancesList[id].D = d;

    cout << "\n������ ������� ��������!\n\n";
    return;
}
void ambulance::removeAmbulance()
{
    cout << "\n����� ������ ������ ��� ��������.\n";
    getDetails();
    if (id == -1)
        return;
    if (!idle)
    {
        cout << "\n��������� ������ ������ �� ��������.\n������ ��������� ����� ���� �������.\n\n";
        return;
    }
    hospital::doctorsList.erase(id);

    string s, temp;
    stringstream str;
    fstream f, fout;
    str << model << "," << manufacturer << "," << vrn << ",Y\n";
    getline(str, s);
    f.open("./data/ambulancesHistory.csv", ios::in);
    fout.open("./data/temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << model << "," << manufacturer << "," << vrn << ",N"
                 << "\n";
        }
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("./data/ambulancesHistory.csv");
    rename("./data/temp.csv", "./data/ambulancesHistory.csv");
    cout << model << " �� " << manufacturer << " (��� = " << vrn << ") ������� ������!\n";
    return;
}