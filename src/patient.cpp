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
    //Открытие файла для чтения
    f.open("./data/patients.csv", ios::in);
    string temp;
    //Пропуск первой строки заголовка
    getline(f >> ws, temp);

    while (getline(f >> ws, temp))
    {
        patient p;
        //Создание stringstream объекта для чтения из строки 'temp';
        stringstream s(temp);
        string s1, s4, s5, s7, s8, s9, s10, s11, s12;
        //Чтения из stringstream объекта 's' и присвоение значения соответствующему полю;
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
        //Добавление объекта в структуру данных map 
        hospital::patientsList[p.id] = p;
    }
    f.close();
    return;
}
void patient::saveMap()
{
    fstream f;
    //Создание нового CSV файла с актуальными данными
    f.open("./data/temp.csv", ios::out);
    //Первая строка хранящая заголовки 
    f << "patientId,firstName,lastName,gender,age,mobNumber,address,height,weight,wasHospitalized?,stillAlive(ifHospitalized)?,room\n";
    //Запись в файл каждого объекта из структуры данных map patientsList 
    for (auto i : hospital::patientsList)
        f << i.second.id << "," << i.second.firstName << "," << i.second.lastName << "," << i.second.gender
          << "," << i.second.age << "," << i.second.mobNumber << "," << i.second.add.addToStr()
          << "," << i.second.height << "," << i.second.weight << ","
          << (i.second.hospitalized ? 'Y' : 'N') << "," << (i.second.alive ? 'Y' : 'N') << "," << i.second.r << endl;
    f.close();
    //Удаление предыдущего CSV файла хранящего устаревшие данные
    remove("./data/patients.csv");
    //Переименование CSV файла для сохранения смысла содержания 
    rename("./data/temp.csv", "./data/patients.csv");
    return;
}
void patient::addPerson()
{
    //getting the basic details of patient from the user side;
    person::addPerson();
    //getting patient specific details;

    r = -1;
    cout << "\nВведите рост пациента (в см):\n";
    cin >> height;
    cout << "\nВведите вес пациента (в кг):\n";
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
         << firstName << " " << lastName << " успешно зарегистрирован!\n";
    cout << "Его ID: " << id << "\n";

    return;
}
void patient::printDetails()
{
    if (id == -1)
        return;
    person::printDetails();
    cout << "Рост (см)             : " << height << "\n";
    cout << "Вес (кг)              : " << weight << "\n";
    cout << "Был госпитолизирован? : " << ((hospitalized) ? "Д" : "Н") << "\n";
    if (hospitalized) cout << "Лежит в палате : " << r << "\n";
    cout << "Жив?                  : " << ((alive) ? "Д" : "Н") << "\n";
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
    cout << "Рост (см)    : " << height << "\n";
    cout << "Вес (кг) : " << weight << "\n";
    cout << "Был госпитолизирован? " << ((hospitalized) ? "Д" : "Н") << "\n";
    cout << "Жив?          : " << ((alive) ? "Д" : "Н") << "\n";
    cout << "Удален?     : " << s1 << "\n";
    return;
}
void patient::getDetails(int rec)
{
    int opt = 0;
    cout << "\nВарианты поиска:\n[1]: По ID\n[2]: По имени\n\n";
    cin >> opt;
    while (opt != 1 && opt != 2)
        cout << "вариант 1 или 2?\n", cin >> opt;
    //1: Filter by ID;
    if (opt == 1)
    {
        int reqId;
        cout << "\nВведите ID:\n";
        cin >> reqId;
        if (hospital::patientsList.find(reqId) != hospital::patientsList.end())
            *this = hospital::patientsList[reqId];
        else
            cout << "\nНет записей!\n";
    }
    //2: Filter by name;
    else if (opt == 2)
    {
        string reqFName, reqLName;
        cout << "Ввдите имя:\n";
        getline(cin >> ws, reqFName);
        cout << "\nВведите фамилию:\n";
        getline(cin, reqLName);
        vector<patient> matchingRecords;
        for (auto i : hospital::patientsList)
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
                cout << "\nВведите ID нужного пациента: ";
                cin >> reqId;
                if (hospital::patientsList.find(reqId) != hospital::patientsList.end())
                    *this = hospital::patientsList[reqId];
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
    return;
}
void patient::getDetailsFromHistory()
{
    int opt = 0;
    cout << "\nВарианты поиска:\n[1]: По имени\n[2]: По номеру телефона\n\n";
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
        cout << matchingRecords.size() << " подходящих записей найдено!\n";
        for (int i = 0; i < matchingRecords.size(); i++)
            matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
    }
    //2: Filter by mobNumber;
    else if (opt == 2)
    {
        string reqMobNum;
        cout << "Введите номер телефона: \n";
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
        cout << matchingRecords.size() << " подходящий записей найдено!\n";
        for (int i = 0; i < matchingRecords.size(); i++)
            matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
    }
    return;
}
void patient::hospitalize()
{
    cout << "\nПоиск пациента.\n";
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
    cout << firstName << " " << lastName << " госпитолизирован успешно!\n";
    return;
}
void patient::reportADeath()
{
    cout << "\nПоиск пациента.\n";
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
    cout << firstName << " " << lastName << " умер, аминь!\n";
    return;
}
void patient::removePerson()
{
    cout << "\nПоиск пациента для удаления.\n";
    getDetails();
    if (id == -1)
        return;
    if (r > 0)
    {
        cout << "\nПациент лежит в палате! Сначала освободите палату!\n\n";
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
    cout << firstName << " " << lastName << " удален!\n";
    return;
}

// Removing a patient: it's rather "DISCHARGING a HOSPITALIZED patient";
// If a patient wasn't hospitalized, just came to the hospital for an appointment with;
// a doctor then that appointment object will be cleared on the next day automatically;
// and there's no need of removing the patient's record from patients.csv in that case;

// Maybe consider this as a kind of limitation of this system;