using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/doctor.hh"
#include "./../include/hospital.hh"

doctor::doctor()
{
    id = -1;
    type = "";
    appointmentsBooked = 0;
    cat = "doctor";
    category = 1;
}
void doctor::fillMap()
{
    fstream f;
    f.open("./data/doctors.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        doctor d;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, s4, s5, s7, s9;
        //reading from the string stream object 's';
        getline(s, s1, ',');
        getline(s, d.firstName, ',');
        getline(s, d.lastName, ',');
        getline(s, s4, ',');
        getline(s, s5, ',');
        getline(s, d.mobNumber, ',');
        getline(s, s7, ',');
        getline(s, d.type, ',');
        getline(s, s9, ',');
        d.id = strToNum(s1);
        d.gender = s4[0];
        d.age = strToNum(s5);
        d.add.strToAdd(s7);
        d.appointmentsBooked = strToNum(s9);
        hospital::doctorsList[d.id] = d;
    }
    f.close();
    return;
}
void doctor::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "doctorId,firstName,lastName,gender,age,mobNumber,address,type,appointmentsBooked\n";
    for (auto i : hospital::doctorsList)
        f << i.second.id << "," << i.second.firstName << "," << i.second.lastName << "," << i.second.gender
          << "," << i.second.age << "," << i.second.mobNumber << "," << i.second.add.addToStr()
          << "," << i.second.type << "," << i.second.appointmentsBooked << endl;
    f.close();
    remove("./data/doctors.csv");
    rename("./data/temp.csv", "./data/doctors.csv");
    return;
}
void doctor::addPerson()
{
    if (hospital::doctorsList.size() == hospital::doctorsLimit)
    {
        cout << "\n\nДостигнут лимит врачей, невозможно добавить нового!\n\n";
        return;
    }
    //18 and 65 are the age limits for registration of a new doctor;
    person::addPerson(18, 65);
    if ((age < 18) || (age > 65))
        return;
    cout << "\nВведите тип врача: \n";
    getline(cin >> ws, type);
    if (hospital::doctorsList.rbegin() != hospital::doctorsList.rend())
        id = ((hospital::doctorsList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::doctorsList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in doctorsHistory.csv;
    f.open("./data/doctorsHistory.csv", ios::app);
    f << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr() << "," << type << ",N,NA" << endl;
    f.close();

    cout << "\n"
         << firstName << " " << lastName << " успешно зарегистрирован!\n";
    cout << "Его ID: " << id << "\n";

    return;
}
void doctor::printDetails()
{
    if (id == -1)
        return;
    person::printDetails();
    cout << "Тип            : " << type << "\n";
    cout << "Приемов        : " << appointmentsBooked << "/8 (назначено приемов на сегодня)\n";
    return;
}
void doctor::printDetailsFromHistory(string extraDetails)
{
    if (id == -1)
        return;
    person::printDetailsFromHistory();
    stringstream k(extraDetails);
    string s1, s2;
    getline(k, s1, ',');
    getline(k, s2, ',');
    if (extraDetails == "")
    {
        fstream f;
        f.open("./data/doctorsHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            doctor d;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4, s5, s7;
            //reading from the string stream object 's';
            getline(s, d.firstName, ',');
            getline(s, d.lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, d.mobNumber, ',');

            if (d.firstName == firstName && d.lastName == lastName && d.mobNumber == mobNumber)
            {

                getline(s, s7, ',');
                getline(s, d.type, ',');
                getline(s, s1, ',');
                getline(s, s2, ',');
            }
        }
        f.close();
    }
    cout << "Тип            : " << type << "\n";
    cout << "Ушел?      : " << s1 << "\n";
    if (s1 == "Y")
        cout << "Причина          : " << s2 << "\n";
    return;
}
void doctor::getDetails(int rec)
{
    int opt = 0;
    cout << "\nВарианты поиска:\n[1]: По ID\n[2]: По имени\n[3]: По типу\n\n";
    cin >> opt;
    while (opt != 1 && opt != 2 && opt != 3)
        cout << "Вариант 1, 2 или 3?\n", cin >> opt;
    //1: Filter by ID;
    if (opt == 1)
    {
        int reqId;
        cout << "\nВведите ID:\n";
        cin >> reqId;
        if (hospital::doctorsList.find(reqId) != hospital::doctorsList.end())
            *this = hospital::doctorsList[reqId];
        else
            cout << "\nНет записей!\n";
    }
    //2: Filter by name;
    else if (opt == 2)
    {
        string reqFName, reqLName;
        cout << "Введите имя:\n";
        getline(cin >> ws, reqFName);
        cout << "\nВведите фамилию:\n";
        getline(cin, reqLName);
        vector<doctor> matchingRecords;
        for (auto i : hospital::doctorsList)
        {
            if (i.second.firstName == reqFName && i.second.lastName == reqLName)
                matchingRecords.push_back(i.second);
        }
        cout << "\n";
        cout << matchingRecords.size() << " подходящих записей найдено!\n";
        for (auto i : matchingRecords)
            i.printDetails();
        char tt = 'N';
        if (matchingRecords.size() > rec)
        {
            do
            {
                int reqId;
                cout << "\nВведите ID нужного врача: ";
                cin >> reqId;
                if (hospital::doctorsList.find(reqId) != hospital::doctorsList.end())
                    *this = hospital::doctorsList[reqId];
                else
                {
                    cout << "\nНеверный ID!\nПовторить попытку? (Y = Да или N = Нет)\n";
                    cin >> tt;
                    while (tt != 'Y' || tt != 'N')
                        cout << "Y или N?\n", cin >> tt;
                }
            } while (tt == 'Y');
        }
    }
    //3: Filter by type;
    else if (opt == 3)
    {
        string reqType;
        cout << "Введите Тип нужного врача:\n";
        getline(cin >> ws, reqType);
        vector<doctor> matchingRecords;
        for (auto i : hospital::doctorsList)
        {
            if (i.second.type == reqType)
                matchingRecords.push_back(i.second);
        }
        cout << "\n";
        cout << matchingRecords.size() << " подходящих записей найдено!\n";
        for (auto i : matchingRecords)
            i.printDetails();
        char tt = 'N';
        if (matchingRecords.size() > 0)
            do
            {
                int reqId;
                cout << "\nВведите ID нужного врача: ";
                cin >> reqId;
                if (hospital::doctorsList.find(reqId) != hospital::doctorsList.end())
                    *this = hospital::doctorsList[reqId];
                else
                {
                    cout << "\nНеверный ID!\nПовторить попытку? (Y = Да или N = Нет)\n";
                    cin >> tt;
                    while (tt != 'Y' || tt != 'N')
                        cout << "Y or N?\n", cin >> tt;
                }
            } while (tt == 'Y');
    }
    return;
}
void doctor::getDetailsFromHistory()
{
    int opt = 0;
    cout << "\nВарианты поиска:\n[1]: По ФИО\n[2]: По типу\n\n";
    cin >> opt;
    while (opt != 1 && opt != 2)
        cout << "вариант 1 или 2?\n", cin >> opt;

    //1: Filter by name;
    if (opt == 1)
    {
        string reqFName, reqLName;
        cout << "Введите имя:\n";
        getline(cin >> ws, reqFName);
        cout << "\nВведите фамилию:\n";
        getline(cin, reqLName);
        vector<doctor> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/doctorsHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            doctor d;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4, s5, s7, s9;
            //reading from the string stream object 's';
            getline(s, d.firstName, ',');
            getline(s, d.lastName, ',');

            if (d.firstName == reqFName && d.lastName == reqLName)
            {
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, d.mobNumber, ',');
                getline(s, s7, ',');
                getline(s, d.type, ',');
                getline(s, s9);
                d.id = 0;
                d.gender = s4[0];
                d.age = strToNum(s5);
                d.add.strToAdd(s7);
                matchingRecords.push_back(d);
                extraDetails.push_back(s9);
            }
        }
        f.close();
        cout << "\n";
        cout << matchingRecords.size() << " подходящих записей найдено!\n";
        for (int i = 0; i < matchingRecords.size(); i++)
            matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
    }
    //2: Filter by type;
    else if (opt == 2)
    {
        string reqType;
        cout << "Введите Тип нужного врача:\n";
        getline(cin >> ws, reqType);
        vector<doctor> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/doctorsHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            doctor d;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4, s5, s7, s9;
            //reading from the string stream object 's';
            getline(s, d.firstName, ',');
            getline(s, d.lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, d.mobNumber, ',');
            getline(s, s7, ',');
            getline(s, d.type, ',');
            if (d.type == reqType)
            {
                getline(s, s9);
                d.id = 0;
                d.gender = s4[0];
                d.age = strToNum(s5);
                d.add.strToAdd(s7);
                matchingRecords.push_back(d);
                extraDetails.push_back(s9);
            }
        }
        f.close();
        cout << "\n";
        cout << matchingRecords.size() << " подходящих записей найдено!\n";
        for (int i = 0; i < matchingRecords.size(); i++)
            matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
    }
    return;
}
void doctor::removePerson()
{
    cout << "\nПоиск врача для удаления.\n";
    getDetails();
    if (id == -1)
        return;
    if (appointmentsBooked > 0)
    {
        cout << "\nУ выбранного врача есть прием на сегодня, невозможно удалить.\n\n";
        return;
    }
    hospital::doctorsList.erase(id);

    string s, temp;
    stringstream str;
    fstream f, fout;
    string reason;
    cout << "\nПричина?\n";
    getline(cin >> ws, reason);
    str << firstName << "," << lastName << "," << gender << "," << age
        << "," << mobNumber << "," << add.addToStr() << "," << type << ",N,NA\n";
    getline(str, s);
    f.open("./data/doctorsHistory.csv", ios::in);
    fout.open("./data/temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << firstName << "," << lastName << "," << gender << "," << age
                 << "," << mobNumber << "," << add.addToStr() << "," << type << ",Y," << reason << "\n";
        }
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("./data/doctorsHistory.csv");
    rename("./data/temp.csv", "./data/doctorsHistory.csv");
    cout << firstName << " " << lastName << " успешно удален(-а)!\n";
    return;
}