using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/driver.hh"
#include "./../include/hospital.hh"

driver::driver()
{
    id = -1;
    licenseNumber = "";
    idle = 1;
    cat = "driver";
    category = 4;
}
void driver::fillMap()
{
    fstream f;
    f.open("./data/drivers.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        driver d;
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
        getline(s, d.licenseNumber, ',');
        getline(s, s9, ',');
        d.id = strToNum(s1);
        d.gender = s4[0];
        d.age = strToNum(s5);
        d.add.strToAdd(s7);
        d.idle = (s9 == "Y");
        hospital::driversList[d.id] = d;
    }
    f.close();
    return;
}
void driver::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "driverId,firstName,lastName,gender,age,mobNumber,address,licenseNumber,idle?\n";
    for (auto i : hospital::driversList)
        f << i.second.id << "," << i.second.firstName << "," << i.second.lastName << "," << i.second.gender
          << "," << i.second.age << "," << i.second.mobNumber << "," << i.second.add.addToStr()
          << "," << i.second.licenseNumber << "," << (i.second.idle ? 'Y' : 'N') << endl;
    f.close();
    remove("./data/drivers.csv");
    rename("./data/temp.csv", "./data/drivers.csv");
    return;
}
void driver::addPerson()
{
    if (hospital::driversList.size() == hospital::driversLimit)
    {
        cout << "\n\nДостигнут лимит водителей, невозможно добавить нового!\n\n";
        return;
    }
    //18 and 65 are the age limits for registration of a new driver;
    person::addPerson(18, 65);
    if ((age < 18) || (age > 65))
        return;
    cout << "\nВведите номер прав водителя: \n";
    getline(cin >> ws, licenseNumber);
    if (hospital::driversList.rbegin() != hospital::driversList.rend())
        id = ((hospital::driversList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::driversList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in driversHistory.csv;
    f.open("./data/driversHistory.csv", ios::app);
    f << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr() << "," << licenseNumber << ",N,NA" << endl;
    f.close();

    cout << "\n"
         << firstName << " " << lastName << " успешно зарегистрирован!\n";
    cout << "Его ID: " << id << "\n";

    return;
}
void driver::printDetails()
{
    if (id == -1)
        return;
    person::printDetails();
    cout << "Номер прав          : " << licenseNumber << "\n";
    cout << "Свободен?           : " << (idle ? "Д\n" : "Н\n");
    return;
}
void driver::printDetailsFromHistory(string extraDetails)
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
        f.open("./data/driversHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            driver d;
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
                getline(s, d.licenseNumber, ',');
                getline(s, s1, ',');
                getline(s, s2, ',');
            }
        }
        f.close();
    }
    cout << "Номер прав  : " << licenseNumber << "\n";
    cout << "Ушел?      : " << s1 << "\n";
    if (s1 == "Y")
        cout << "Причина          : " << s2 << "\n";
    return;
}
void driver::getDetails(int rec)
{
    int opt = 0;
    cout << "\nВарианты поиска:\n[1]: По ID\n[2]: По имени\n[3]: По номеру прав\n\n";
    cin >> opt;
    while (opt != 1 && opt != 2 && opt != 3)
        cout << "вариант 1, 2 или 3?\n", cin >> opt;
    //1: Filter by ID;
    if (opt == 1)
    {
        int reqId;
        cout << "\nВведите ID:\n";
        cin >> reqId;
        if (hospital::driversList.find(reqId) != hospital::driversList.end())
            *this = hospital::driversList[reqId];
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
        vector<driver> matchingRecords;
        for (auto i : hospital::driversList)
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
                cout << "\nВведите ID нужного водителя: ";
                cin >> reqId;
                if (hospital::driversList.find(reqId) != hospital::driversList.end())
                    *this = hospital::driversList[reqId];
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
    //3: Filter by licenseNumber;
    else if (opt == 3)
    {
        string reqlicenseNumber;
        cout << "Введите Номер прав нужного водителя:\n";
        getline(cin >> ws, reqlicenseNumber);
        for (auto i : hospital::driversList)
        {
            if (i.second.licenseNumber == reqlicenseNumber)
            {
                *this = i.second;
                return;
            }
        }
        //if a record is found, it's details will be stored in the driver class object that called this function,
        //and the control is returned;
        //else:
        cout << "\nНет записей!\n";
    }
    return;
}
void driver::getDetailsFromHistory()
{
    int opt = 0;
    cout << "\nВарианты поиска:\n[1]: По ID\n[2]: По номеру прав\n\n";
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
        vector<driver> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/driversHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            driver d;
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
                getline(s, d.licenseNumber, ',');
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
    //2: Filter by licenseNumber;
    else if (opt == 2)
    {
        string reqlicenseNumber;
        cout << "Введите Номер прав нужного водителя:\n";
        getline(cin >> ws, reqlicenseNumber);
        vector<driver> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/driversHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4, s5, s7, s9;
            //reading from the string stream object 's';
            getline(s, firstName, ',');
            getline(s, lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, mobNumber, ',');
            getline(s, s7, ',');
            getline(s, licenseNumber, ',');
            if (licenseNumber == reqlicenseNumber)
            {
                getline(s, s9);
                id = 0;
                gender = s4[0];
                age = strToNum(s5);
                add.strToAdd(s7);
                printDetailsFromHistory(s9);
                return;
            }
        }
        f.close();
        //if a record is found, it's details will be stored in the driver class object that called this function,
        //and the control is returned;
        //else:
        cout << "\nНет записей!\n";
    }
    return;
}
void driver::removePerson()
{
    cout << "\nПоиск водителя для удаления.\n";
    getDetails();
    if (id == -1)
        return;
    if (!idle)
    {
        cout << "\nВыбранный водитель занят, невозможно удалить\nТолько свободные могут быть удалены.\n\n";
        return;
    }
    hospital::driversList.erase(id);

    string s, temp;
    stringstream str;
    fstream f, fout;
    string reason;
    cout << "\nПричина?\n";
    getline(cin >> ws, reason);
    str << firstName << "," << lastName << "," << gender << "," << age
        << "," << mobNumber << "," << add.addToStr() << "," << licenseNumber << ",N,NA\n";
    getline(str, s);
    f.open("./data/driversHistory.csv", ios::in);
    fout.open("./data/temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << firstName << "," << lastName << "," << gender << "," << age
                 << "," << mobNumber << "," << add.addToStr() << "," << licenseNumber << ",Y," << reason << "\n";
        }
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("./data/driversHistory.csv");
    rename("./data/temp.csv", "./data/driversHistory.csv");
    cout << firstName << " " << lastName << " успешно удален!\n";
    return;
}