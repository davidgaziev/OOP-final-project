using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/patient.hh"
#include "./../include/hospital.hh"
#include "./../include/room.hh"

patient::patient()
{
    id = -1;
    hospitalized = 0;
    alive = 1;
    cat = "patient";
    category = 2;
}
void patient::fillMap()
{
    fstream f;
    //�������� ����� ��� ������
    f.open("./data/patients.csv", ios::in);
    string temp;
    //������� ������ ������ ���������
    getline(f >> ws, temp);

    while (getline(f >> ws, temp))
    {
        patient p;
        //�������� stringstream ������� ��� ������ �� ������ 'temp';
        stringstream s(temp);
        string s1, s4, s5, s7, s8, s9, s10, s11, s12;
        //������ �� stringstream ������� 's' � ���������� �������� ���������������� ����;
        getline(s, s1, ',');
        getline(s, p.firstName, ',');
        getline(s, p.lastName, ',');
        getline(s, s4, ',');
        getline(s, s5, ',');
        getline(s, p.mobNumber, ',');
        getline(s, s7, ',');
        getline(s, s8, ',');
        getline(s, s9, ',');
        getline(s, s10, ',');
        getline(s, s11, ',');
        getline(s, s12, ',');
        p.id = strToNum(s1);
        p.gender = s4[0];
        p.age = strToNum(s5);
        p.add.strToAdd(s7);
        p.height = strToNum(s8);
        p.weight = strToNum(s9);
        p.hospitalized = (s10 == "Y");
        p.alive = (s11 == "Y");
        p.r = strToNum(s12);
        //���������� ������� � ��������� ������ map 
        hospital::patientsList[p.id] = p;
    }
    f.close();
    return;
}
void patient::saveMap()
{
    fstream f;
    //�������� ������ CSV ����� � ����������� �������
    f.open("./data/temp.csv", ios::out);
    //������ ������ �������� ��������� 
    f << "patientId,firstName,lastName,gender,age,mobNumber,address,height,weight,wasHospitalized?,stillAlive(ifHospitalized)?,room\n";
    //������ � ���� ������� ������� �� ��������� ������ map patientsList 
    for (auto i : hospital::patientsList)
        f << i.second.id << "," << i.second.firstName << "," << i.second.lastName << "," << i.second.gender
          << "," << i.second.age << "," << i.second.mobNumber << "," << i.second.add.addToStr()
          << "," << i.second.height << "," << i.second.weight << ","
          << (i.second.hospitalized ? 'Y' : 'N') << "," << (i.second.alive ? 'Y' : 'N') << "," << i.second.r << endl;
    f.close();
    //�������� ����������� CSV ����� ��������� ���������� ������
    remove("./data/patients.csv");
    //�������������� CSV ����� ��� ���������� ������ ���������� 
    rename("./data/temp.csv", "./data/patients.csv");
    return;
}
void patient::addPerson()
{
    //getting the basic details of patient from the user side;
    person::addPerson();
    //getting patient specific details;

    r = -1;
    cout << "\n������� ���� �������� (� ��):\n";
    cin >> height;
    cout << "\n������� ��� �������� (� ��):\n";
    cin >> weight;
    hospitalized = false;
    if (hospital::patientsList.rbegin() != hospital::patientsList.rend())
        id = ((hospital::patientsList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::patientsList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in patientsHistory.csv;
    f.open("./data/patientsHistory.csv", ios::app);
    f << firstName << "," << lastName << "," << gender << "," << age
      << "," << mobNumber << "," << add.addToStr() << "," << height << ","
      << weight << "," << ((hospitalized) ? "Y" : "N") << "," << r
      << ","
      << "Y"
      << ","
      << "N"
      << "\n";
    f.close();

    cout << "\n"
         << firstName << " " << lastName << " ������� ���������������!\n";
    cout << "��� ID: " << id << "\n";

    return;
}
void patient::printDetails()
{
    if (id == -1)
        return;
    person::printDetails();
    cout << "���� (��)             : " << height << "\n";
    cout << "��� (��)              : " << weight << "\n";
    cout << "��� ����������������? : " << ((hospitalized) ? "�" : "�") << "\n";
    if (hospitalized) cout << "����� � ������ : " << r << "\n";
    cout << "���?                  : " << ((alive) ? "�" : "�") << "\n";
    return;
}
void patient::printDetailsFromHistory(string extraDetails)
{
    if (id == -1)
        return;
    person::printDetailsFromHistory();
    stringstream k(extraDetails);
    string s1;
    getline(k, s1, ',');
    if (extraDetails == "")
    {
        fstream f;
        f.open("./data/patientsHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            patient p;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s3, s4, s6, s7, s8, s9, s10;
            //reading from the string stream object 's';
            getline(s, p.firstName, ',');
            getline(s, p.lastName, ',');
            getline(s, s3, ',');
            getline(s, s4, ',');
            getline(s, p.mobNumber, ',');

            if (p.firstName == firstName && p.lastName == lastName && p.mobNumber == mobNumber)
            {

                getline(s, s6, ',');
                getline(s, s7, ',');
                getline(s, s8, ',');
                getline(s, s9, ',');
                getline(s, s10, ',');
                getline(s, s1, ',');
            }
        }
        f.close();
    }
    cout << "���� (��)    : " << height << "\n";
    cout << "��� (��) : " << weight << "\n";
    cout << "��� ����������������? " << ((hospitalized) ? "�" : "�") << "\n";
    cout << "���?          : " << ((alive) ? "�" : "�") << "\n";
    cout << "������?     : " << s1 << "\n";
    return;
}
void patient::getDetails(int rec)
{
    int opt = 0;
    cout << "\n�������� ������:\n[1]: �� ID\n[2]: �� �����\n\n";
    cin >> opt;
    while (opt != 1 && opt != 2)
        cout << "������� 1 ��� 2?\n", cin >> opt;
    //1: Filter by ID;
    if (opt == 1)
    {
        int reqId;
        cout << "\n������� ID:\n";
        cin >> reqId;
        if (hospital::patientsList.find(reqId) != hospital::patientsList.end())
            *this = hospital::patientsList[reqId];
        else
            cout << "\n��� �������!\n";
    }
    //2: Filter by name;
    else if (opt == 2)
    {
        string reqFName, reqLName;
        cout << "������ ���:\n";
        getline(cin >> ws, reqFName);
        cout << "\n������� �������:\n";
        getline(cin, reqLName);
        vector<patient> matchingRecords;
        for (auto i : hospital::patientsList)
        {
            if (i.second.firstName == reqFName && i.second.lastName == reqLName)
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
                cout << "\n������� ID ������� ��������: ";
                cin >> reqId;
                if (hospital::patientsList.find(reqId) != hospital::patientsList.end())
                    *this = hospital::patientsList[reqId];
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
    return;
}
void patient::getDetailsFromHistory()
{
    int opt = 0;
    cout << "\n�������� ������:\n[1]: �� �����\n[2]: �� ������ ��������\n\n";
    cin >> opt;
    while (opt != 1 && opt != 2)
        cout << "������� 1 ��� 2?\n", cin >> opt;
    //1: Filter by name;
    if (opt == 1)
    {
        string reqFName, reqLName;
        cout << "������� ���:\n";
        getline(cin >> ws, reqFName);
        cout << "\n������� �������:\n";
        getline(cin, reqLName);
        vector<patient> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/patientsHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            patient p;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s3, s4, s6, s7, s8, s9, s10, s12;
            //reading from the string stream object 's';
            getline(s, p.firstName, ',');
            getline(s, p.lastName, ',');

            if (p.firstName == reqFName && p.lastName == reqLName)
            {
                getline(s, s3, ',');
                getline(s, s4, ',');
                getline(s, p.mobNumber, ',');
                getline(s, s6, ',');
                getline(s, s7, ',');
                getline(s, s8, ',');
                getline(s, s9, ',');
                getline(s, s10, ',');
                getline(s, s10, ',');
                getline(s, s12);
                p.id = 0;
                p.gender = s3[0];
                p.age = strToNum(s4);
                add.strToAdd(s6);
                p.height = strToNum(s7);
                p.weight = strToNum(s8);
                p.hospitalized = (s9 == "Y");
                p.alive = (s10 == "Y");
                matchingRecords.push_back(p);
                extraDetails.push_back(s12);
            }
        }
        f.close();
        cout << "\n";
        cout << matchingRecords.size() << " ���������� ������� �������!\n";
        for (int i = 0; i < matchingRecords.size(); i++)
            matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
    }
    //2: Filter by mobNumber;
    else if (opt == 2)
    {
        string reqMobNum;
        cout << "������� ����� ��������: \n";
        cin >> reqMobNum;
        vector<patient> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/patientsHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            patient p;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s3, s4, s6, s7, s8, s9, s10, s12;
            //reading from the string stream object 's';
            getline(s, p.firstName, ',');
            getline(s, p.lastName, ',');
            getline(s, s3, ',');
            getline(s, s4, ',');
            getline(s, p.mobNumber, ',');

            if (reqMobNum == p.mobNumber)
            {
                getline(s, s6, ',');
                getline(s, s7, ',');
                getline(s, s8, ',');
                getline(s, s9, ',');
                getline(s, s10, ',');
                getline(s, s12);
                p.id = 0;
                p.gender = s3[0];
                p.age = strToNum(s4);
                add.strToAdd(s6);
                p.height = strToNum(s7);
                p.weight = strToNum(s8);
                p.hospitalized = (s9 == "Y");
                p.alive = (s10 == "Y");
                matchingRecords.push_back(p);
                extraDetails.push_back(s12);
            }
        }
        f.close();
        cout << "\n";
        cout << matchingRecords.size() << " ���������� ������� �������!\n";
        for (int i = 0; i < matchingRecords.size(); i++)
            matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
    }
    return;
}
void patient::hospitalize()
{
    cout << "\n����� ��������.\n";
    getDetails();
    if (id == -1)
        return;
    hospital::patientsList[id].hospitalized = 1;
    string s, temp, corrected;
    stringstream str;
    fstream f, fout;
    str << firstName << "," << lastName
        << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
        << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
        << ","
        << ((alive) ? "Y" : "N")
        << ",N"
        << "\n";
    getline(str >> ws, s);
    str << firstName << "," << lastName
        << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
        << "," << height << "," << weight << ","
        << "Y,"
        << ((alive) ? "Y,N\n" : "N,N\n");
    getline(str >> ws, corrected);

    room r; 
    int result = r.addRoom(*this);
    
    if (result == -1) return;
    
    f.open("./data/patientsHistory.csv", ios::in);
    fout.open("./data/temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
            fout << corrected << "\n";
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("./data/patientsHistory.csv");
    rename("./data/temp.csv", "./data/patientsHistory.csv");
    cout << firstName << " " << lastName << " ���������������� �������!\n";
    return;
}
void patient::reportADeath()
{
    cout << "\n����� ��������.\n";
    getDetails();
    if (id == -1)
        return;
    hospital::patientsList[id].alive = 0;
    if (!hospital::patientsList[id].hospitalized)
        hospital::patientsList.erase(id);
    string s, temp, corrected;
    stringstream str;
    fstream f, fout;
    str << firstName << "," << lastName
        << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
        << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
        << ","
        << ((alive) ? "Y" : "N")
        << ",N"
        << "\n";
    getline(str, s);
    f.open("./data/patientsHistory.csv", ios::in);
    fout.open("./data/temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << firstName << "," << lastName
                 << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
                 << "," << height << "," << weight << "," << ((hospitalized) ? "Y,N,N\n" : "N,N,N\n");
        }
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("./data/patientsHistory.csv");
    rename("./data/temp.csv", "./data/patientsHistory.csv");
    cout << firstName << " " << lastName << " ����, �����!\n";
    return;
}
void patient::removePerson()
{
    cout << "\n����� �������� ��� ��������.\n";
    getDetails();
    if (id == -1)
        return;
    if (r > 0)
    {
        cout << "\n������� ����� � ������! ������� ���������� ������!\n\n";
        return;
    }

    hospital::patientsList.erase(id);
    string s, temp;
    stringstream str;
    fstream f, fout;
    str << firstName << "," << lastName
        << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
        << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
        << ","
        << ((alive) ? "Y" : "N")
        << ",N" 
        << ","
        << r
        << "\n";
    getline(str, s);
    f.open("./data/patientsHistory.csv", ios::in);
    fout.open("./data/temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << firstName << "," << lastName
                 << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
                 << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
                 << ","
                 << ((alive) ? "Y" : "N")
                 << ",Y"
                 << ","
                 << r
                 << "\n";
        }
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("./data/patientsHistory.csv");
    rename("./data/temp.csv", "./data/patientsHistory.csv");
    cout << firstName << " " << lastName << " ������!\n";
    return;
}

// Removing a patient: it's rather "DISCHARGING a HOSPITALIZED patient";
// If a patient wasn't hospitalized, just came to the hospital for an appointment with;
// a doctor then that appointment object will be cleared on the next day automatically;
// and there's no need of removing the patient's record from patients.csv in that case;

// Maybe consider this as a kind of limitation of this system;