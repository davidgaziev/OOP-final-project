using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/nurse.hh"
#include "./../include/hospital.hh"

nurse::nurse()
{
    id = -1;
    type = "";
    cat = "nurse";
    category = 3;
}
void nurse::fillMap()
{
    fstream f;
    f.open("./data/nurses.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        nurse n;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, s4, s5, s7, s8;
        //reading from the string stream object 's';
        getline(s, s1, ',');
        getline(s, n.firstName, ',');
        getline(s, n.lastName, ',');
        getline(s, s4, ',');
        getline(s, s5, ',');
        getline(s, n.mobNumber, ',');
        getline(s, s7, ',');
        getline(s, n.type, ',');
        getline(s, s8, ',');
        n.id = strToNum(s1);    
        n.gender = s4[0];
        n.age = strToNum(s5);
        n.add.strToAdd(s7);
        n.r = strToNum(s8);
        hospital::nursesList[n.id] = n;
    }
    f.close();
    return;
}
void nurse::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "nurseId,firstName,lastName,gender,age,mobNumber,address,type,room\n";
    for (auto i : hospital::nursesList)
        f << i.second.id << "," << i.second.firstName << "," << i.second.lastName << "," << i.second.gender
          << "," << i.second.age << "," << i.second.mobNumber << "," << i.second.add.addToStr()
          << "," << i.second.type << "," << i.second.r << endl;
    f.close();
    remove("./data/nurses.csv");
    rename("./data/temp.csv", "./data/nurses.csv");
    return;
}
void nurse::addPerson()
{
    if (hospital::nursesList.size() == hospital::nursesLimit)
    {
        cout << "\n\nДостигнут лимит медсестер, невозможно добавить нового!\n\n";
        return;
    }
    //18 and 65 are the age limits for registration of a new nurse;
    person::addPerson(18, 65);
    if ((age < 18) || (age > 65))
        return;
    cout << "\nВведите тип медсестры: \n";
    getline(cin >> ws, type);
    if (hospital::nursesList.rbegin() != hospital::nursesList.rend())
        id = ((hospital::nursesList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::nursesList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in nursesHistory.csv;
    f.open("./data/nursesHistory.csv", ios::app);
    f << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr() << "," << type << ",N,NA" << endl;
    f.close();

    cout << "\n"
         << firstName << " " << lastName << " успешно зарегистрирована!\n";
    cout << "ID: " << id << "\n";

    return;
}
void nurse::printDetails()
{
    if (id == -1)
        return;
    person::printDetails();
    cout << "Тип            : " << type << "\n";
    if (r > 0) cout << "Назначена к палате номер: " << r << "\n";
    return;
}
void nurse::printDetailsFromHistory(string extraDetails)
{
    if (id == -1)
        return;
    person::printDetailsFromHistory();
    stringstream k(extraDetails);
    string s1, s2, s8;
    getline(k, s1, ',');
    getline(k, s2, ',');
    if (extraDetails == "")
    {
        fstream f;
        f.open("./data/nursesHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            nurse n;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4, s5, s7;
            //reading from the string stream object 's';
            getline(s, n.firstName, ',');
            getline(s, n.lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, n.mobNumber, ',');

            if (n.firstName == firstName && n.lastName == lastName && n.mobNumber == mobNumber)
            {

                getline(s, s7, ',');
                getline(s, n.type, ',');
                getline(s, s1, ',');
                getline(s, s2, ',');
                getline(s, s8, ',');
            }
        }
        f.close();
    }
    cout << "Тип            : " << type << "\n";
    cout << "Ушел?      : " << s1 << "\n";
    if (s1 == "Y")
        cout << "Причина          : " << s2 << "\n";
    if (strToNum(s8) > 0) cout << "Назначена к палате номер: " << r << "\n";
    return;
}
void nurse::getDetails(int rec)
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
        if (hospital::nursesList.find(reqId) != hospital::nursesList.end())
            *this = hospital::nursesList[reqId];
        else
            cout << "\nНет записей!\n";
    }
    //2: Filter by name;
    else if (opt == 2)
    {
        string reqFName, reqLName;
        cout << "Введите имя:\n";
        getline(cin >> ws, reqFName);
        cout << "\nВведите фамилия:\n";
        getline(cin, reqLName);
        vector<nurse> matchingRecords;
        for (auto i : hospital::nursesList)
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
                cout << "\nВведите ID нужной медсестры: ";
                cin >> reqId;
                if (hospital::nursesList.find(reqId) != hospital::nursesList.end())
                    *this = hospital::nursesList[reqId];
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
        cout << "Введите Тип нужной медсестры:\n";
        getline(cin >> ws, reqType);
        vector<nurse> matchingRecords;
        for (auto i : hospital::nursesList)
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
                cout << "\nВведите ID нужной медсестры: ";
                cin >> reqId;
                if (hospital::nursesList.find(reqId) != hospital::nursesList.end())
                    *this = hospital::nursesList[reqId];
                else
                {
                    cout << "\nНеверный ID!\nПовторить попытку? (Y = Да или N = Нет)\n";
                    cin >> tt;
                    while (tt != 'Y' || tt != 'N')
                        cout << "Y или N?\n", cin >> tt;
                }
            } while (tt == 'Y');
    }
    return;
}
void nurse::getDetailsFromHistory()
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
        cout << "Введите имя\n";
        getline(cin >> ws, reqFName);
        cout << "\nВведите фамилию\n";
        getline(cin, reqLName);
        vector<nurse> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/nursesHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            nurse n;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4, s5, s7, s9, s10;
            //reading from the string stream object 's';
            getline(s, n.firstName, ',');
            getline(s, n.lastName, ',');

            if (n.firstName == reqFName && n.lastName == reqLName)
            {
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, n.mobNumber, ',');
                getline(s, s7, ',');
                getline(s, n.type, ',');
                getline(s, s9);
                getline(s, s10);
                n.id = 0;
                n.gender = s4[0];
                n.age = strToNum(s5);
                n.add.strToAdd(s7);
                n.r = strToNum(s10);
                matchingRecords.push_back(n);
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
        cout << "Введите Тип нужной медсестры:\n";
        getline(cin >> ws, reqType);
        vector<nurse> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/nursesHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            nurse n;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4, s5, s7, s9, s10;
            //reading from the string stream object 's';
            getline(s, n.firstName, ',');
            getline(s, n.lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, n.mobNumber, ',');
            getline(s, s7, ',');
            getline(s, n.type, ',');
            getline(s, s10, ',');
            if (n.type == reqType)
            {
                getline(s, s9);
                n.id = 0;
                n.gender = s4[0];
                n.age = strToNum(s5);
                n.add.strToAdd(s7);
                n.r = strToNum(s10);
                matchingRecords.push_back(n);
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
void nurse::removePerson()
{
    cout << "\nПоиск медсестры для удаления.\n";
    getDetails();
    if (id == -1)
        return;
    if (r > 0) {
        cout << "Медсестра назначена к палате! Сначала освободите палату!\n";
        return;
    }

    hospital::nursesList.erase(id);

    string s, temp;
    stringstream str;
    fstream f, fout;
    string reason;
    cout << "\nПричина?\n";
    getline(cin >> ws, reason);
    str << firstName << "," << lastName << "," << gender << "," << age
        << "," << mobNumber << "," << add.addToStr() << "," << type << ",N,NA\n";
    getline(str, s);
    f.open("./data/nursesHistory.csv", ios::in);
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
    remove("./data/nursesHistory.csv");
    rename("./data/temp.csv", "./data/nursesHistory.csv");
    cout << firstName << " " << lastName << " успешно удален(-а)!\n";
    return;
}