#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ios>    //used to get stream size
#include <limits> //used to get numeric limits
#include <windows.h>
using namespace std;

#include "./include/global.hh"
#include "./include/hospital.hh"
#include "./include/address.hh"
#include "./include/person.hh"
#include "./include/appointment.hh"
#include "./include/patient.hh"
#include "./include/doctor.hh"
#include "./include/nurse.hh"
#include "./include/driver.hh"
#include "./include/ambulance.hh"

void appointmentsMenu();
void patientsMenu();
void doctorsMenu();
void nursesMenu();
void driversMenu();
void ambulancesMenu();

void appointmentsMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\n�������� �����:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./�������/������\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : ��������� �����\n";
        cout << "[02] : �������� �������� � ������\n";
        cout << "[03] : �������� ��� ������\n\n";
        cout << "[-1] : �����\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "��� �����: ";
        cin >> purpose;

        appointment a;

        switch (purpose) {
            case(1):
                a.book();
                break;
            case(2):
                a.getDetails();
                a.printDetails();
                break;
            case(3):
                hospital::printAppointments();
                break;
            case(-1):
                exit = true;
                break;
            default:
                cout << "�������� �����!\n";
                break;
        }


        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\n������� ENTER ��� �����������...\n";
        cout << endl;

        getchar();
    }
    return;
}

void patientsMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\n�������� �����:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./�������/��������\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : ���������������� ������ ��������\n";
        cout << "[02] : �������� �������� � ��������\n";
        cout << "[03] : ����������������� ������������������� ��������\n";
        cout << "[04] : �������� � ������ ��������\n";
        cout << "[05] : ������� ��������\n";
        cout << "[06] : �������� �������� � �������� � �������\n";
        cout << "[07] : �������� �������� ���� ���������\n\n";
        cout << "[-1] : �����\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "��� �����: ";
        cin >> purpose;

        patient p;

        switch (purpose) {
            case(1):
                p.addPerson();
                break;
            case(2):
                p.getDetails(1);
                p.printDetails();
                break;
            case(3):
                p.hospitalize();
                break;
            case(4):
                p.reportADeath();
                break;
            case(5):
                p.removePerson();
                break;
            case(6):
                p.getDetailsFromHistory();
                break;
            case(7):
                hospital::printPatients();
                break;
            case(-1):
                exit = true;
                break;
            default:
                cout << "�������� �����!\n";
                break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\n������� ENTER ��� �����������...\n";
        cout << endl;

        getchar();
    }
    return;
}

void doctorsMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\n�������� �����:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./�������/�����\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : ���������������� ������ �����\n";
        cout << "[02] : �������� �������� � �����\n";
        cout << "[03] : ������� �����\n";
        cout << "[04] : �������� ������� � ����� � �������\n";
        cout << "[05] : �������� ������� ���� ������\n\n";
        cout << "[-1] : �����\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "��� �����: ";
        cin >> purpose;

        if (purpose == 1)
        {
            doctor d;
            d.addPerson();
        }
        else if (purpose == 2)
        {
            doctor d;
            d.getDetails(1);
            d.printDetails();
        }
        else if (purpose == 3)
        {
            doctor d;
            d.removePerson();
        }
        else if (purpose == 4)
        {
            doctor d;
            d.getDetailsFromHistory();
        }
        else if (purpose == 5)
        {
            hospital::printDoctors();
        }
        else if (purpose == -1)
        {
            exit = true;
            break;
        }
        else
        {
            cout << "�������� �����!\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\n������� ENTER ��� �����������...\n";
        cout << endl;

        getchar();
    }
    return;
}

void nursesMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\n�������� �����:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./�������/���������\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : ���������������� ����� ���������\n";
        cout << "[02] : �������� �������� � ���������\n";
        cout << "[03] : ������� ���������\n";
        cout << "[04] : �������� �������� � ��������� � �������\n";
        cout << "[05] : �������� �������� ���� ���������\n\n";
        cout << "[-1] : �����\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "��� �����: ";
        cin >> purpose;

        if (purpose == 1)
        {
            nurse n;
            n.addPerson();
        }
        else if (purpose == 2)
        {
            nurse n;
            n.getDetails(1);
            n.printDetails();
        }
        else if (purpose == 3)
        {
            nurse n;
            n.removePerson();
        }
        else if (purpose == 4)
        {
            nurse n;
            n.getDetailsFromHistory();
        }
        else if (purpose == 5)
        {
            hospital::printNurses();
        }
        else if (purpose == -1)
        {
            exit = true;
            break;
        }
        else
        {
            cout << "�������� �����!\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\n������� ENTER ��� �����������...\n";
        cout << endl;

        getchar();
    }
    return;
}

void driversMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\n�������� �����:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./�������/��������\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : ���������������� ������ ��������\n";
        cout << "[02] : �������� �������� � ��������\n";
        cout << "[03] : ������� ��������\n";
        cout << "[04] : �������� �������� � �������� � �������\n";
        cout << "[05] : �������� �������� ���� ���������\n\n";
        cout << "[-1] : �����\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "��� �����: ";
        cin >> purpose;

        if (purpose == 1)
        {
            driver d;
            d.addPerson();
        }
        else if (purpose == 2)
        {
            driver d;
            d.getDetails(1);
            d.printDetails();
        }
        else if (purpose == 3)
        {
            driver d;
            d.removePerson();
        }
        else if (purpose == 4)
        {
            driver d;
            d.getDetailsFromHistory();
        }
        else if (purpose == 5)
        {
            hospital::printDrivers();
        }
        else if (purpose == -1)
        {
            exit = true;
            break;
        }
        else
        {
            cout << "�������� �����!\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\n������� ENTER ��� �����������...\n";
        cout << endl;

        getchar();
    }
    return;
}

void ambulancesMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\n�������� �����:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./�������/������ ������\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : �������� ������ ������\n";
        cout << "[02] : ��������� ������ ������\n";
        cout << "[03] : �������� �������� � ������ ������\n";
        cout << "[04] : �������� � �������� ������ ������\n";
        cout << "[05] : ������� ������ ������\n";
        cout << "[06] : �������� �������� � ������ ������ � �������\n";
        cout << "[07] : �������� �������� ���� ������ ������\n\n";
        cout << "[-1] : �����\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "��� �����: ";
        cin >> purpose;

        if (purpose == 1)
        {
            ambulance a;
            a.addAmbulance();
        }
        else if (purpose == 2)
        {
            ambulance a;
            a.send();
        }
        else if (purpose == 3)
        {
            ambulance a;
            a.getDetails(1);
            a.printDetails();
        }
        else if (purpose == 4)
        {
            ambulance a;
            a.reportArrival();
        }
        else if (purpose == 5)
        {
            ambulance a;
            a.removeAmbulance();
        }
        else if (purpose == 6)
        {
            ambulance a;
            a.getDetailsFromHistory();
        }
        else if (purpose == 7)
        {
            hospital::printAmbulances();
        }
        else if (purpose == -1)
        {
            exit = true;
            break;
        }
        else
        {
            cout << "�������� �����!\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\n������� ENTER ��� �����������...\n";
        cout << endl;

        getchar();
    }
    return;
}


void roomsMenu()
{
    bool exit = false;
    room r;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\n�������� �����:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./�������/������\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : �������� �������� � ������\n";
        cout << "[02] : ���������� ������\n";
        cout << "[-1] : �����\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "��� �����: ";
        cin >> purpose;

        switch (purpose)
        {
        case 1:
            r.getDetails();
            r.printDetails();
            break;
        case 2:
            r.freeRoom();
            break;
        case -1:
            exit = true;
            break;
        default:
            cout << "�������� �����!\n";
            break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\n������� ENTER ��� �����������...\n";
        cout << endl;

        getchar();
    }



    return;
}



int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    fstream f;
    f.open("./data/appointments.csv", ios::in);
    string temp, s, header;
    getline(f, header);
    getline(f, temp);
    f.close();
    stringstream str(temp);
    getline(str, s, ',');
    getline(str, s, ',');
    int dd, mm, yyyy;
    if (s != "")
        cout << "\n\n\n��������� �������������� ���� (��-��-����) : " << s.substr(6, 2) + "-" + s.substr(4, 2) + "-" + s.substr(0, 4) + "\n";
    cout << "\n���������� ������� ����������� ���� (��-��-����) :\n\n������� ����: ";
    cin >> dd;
    while (dd < 1 || dd > 31)
    {
        cout << "�������� ����! ���������� ������� ���������� ����: ";
        cin >> dd;
    }
    cout << "������� �����: ";
    cin >> mm;
    while (mm < 1 || mm > 12)
    {
        cout << "�������� �����! ���������� ������� ���������� �����: ";
        cin >> mm;
    }
    cout << "������� ��� (����): ";
    cin >> yyyy;
    yyyymmdd = yyyy * 10000 + mm * 100 + dd;
    if (stoi(((s == "") ? ("0") : (s))) < yyyymmdd)
    {
        f.open("./data/temp.csv", ios::out);
        f << header << "\n";
        f.close();
        remove("./data/appointments.csv");
        rename("./data/temp.csv", "./data/appointments.csv");
        fstream fout("./data/temp.csv", ios::out);
        f.open("./data/doctors.csv", ios::in);
        getline(f, temp);
        fout << temp << endl;
        while (getline(f, temp))
        {
            if (temp.size())
                temp[temp.size() - 1] = '0';
            fout << temp << endl;
        }
        f.close();
        fout.close();
        remove("./data/doctors.csv");
        rename("./data/temp.csv", "./data/doctors.csv");
    }
    else if (stoi(s) > yyyymmdd && s != "")
    {
        cout << "\n�������� ���� �������!\n����������� ���� �� ����� ���� ������ ��� ����������, �������: "
             << s.substr(6, 2) + "-" + s.substr(4, 2) + "-" + s.substr(0, 4) + "\n";
        return 0;
    }

    {
        doctor d1;
        patient p;
        nurse n;
        driver d2;
        ambulance a1;
        appointment a2;
        room  r;
        d1.fillMap();
        p.fillMap();
        n.fillMap();
        d2.fillMap();
        a1.fillMap();
        a2.fillMap();
        r.fillMap();
    }
    while (1)
    {
        int category = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\n�������� ���������:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./�������\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : ������\n";
        cout << "[02] : ��������\n";
        cout << "[03] : �������\n";
        cout << "[04] : ���������\n";
        cout << "[05] : ��������\n";
        cout << "[06] : ������ ������\n";
        cout << "[07] : ������\n\n";
        cout << "[-1] : �����\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "��� �����: ";
        cin >> category;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\n";

        if (category == -1) {
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "\n���������� �������...\n";
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            break;
        }

        switch (category) {
            case(1):
                appointmentsMenu();
                break;
            case(2):
                patientsMenu();
                break;
            case(3):
                doctorsMenu();
                break;
            case(4):
                nursesMenu();
                break;
            case(5):
                driversMenu();
                break;
            case(6):
                ambulancesMenu();
                break;
            case(7):
                roomsMenu();
                break;
            default:
                cout << "\n�������� �����!\n";
                break;
        }
       
        cout << endl;
    }
    // saving data inside maps by overwriting it on the files
    {
        doctor d1;
        patient p;
        nurse n;
        driver d2;
        ambulance a1;
        appointment a2;
        room r;
        d1.saveMap();
        p.saveMap();
        n.saveMap();
        d2.saveMap();
        a1.saveMap();
        a2.saveMap();
        r.saveMap();
    }

    return 0;
}
