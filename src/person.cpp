using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/person.hh"

person::person()
{
    id = -1;
}
void person::addPerson(int16_t minAge, int16_t maxAge)
{
    //getting basic details of the person from the user side;
    cout << "\n������� ���:\n";
    getline(cin >> ws, firstName);
    cout << "\n������� �������:\n";
    getline(cin, lastName);

    cout << "\n������� �������: \n";
    cin >> age;
    while (age <= 0)
        cout << "������ �������� �������\n���������� �����!\n", cin >> age;
    if (category != 2)
    {
        if (age < minAge)
            return void(cout << "��������, ������� �������� ������ ���� ��" << minAge << " ���, ����� ���������������� ��� " << cat << ".\n");
        else if (age > maxAge)
            return void(cout << "��������, ������� �������� ������ ���� �� ������ " << maxAge << " ���, ����� ���������������� ��� " << cat << ".\n");
    }

    cout << "\n��� (M = ������� || F = �������): \n";
    cin >> gender;
    while (gender != 'M' && gender != 'F')
        cout << "M ��� F?\n", cin >> gender;
    cout << "\n������� ����� �������� (� ����� ������): \n";
    getline(cin >> ws, mobNumber);
    add.takeInput();
    return;
}
void person::printDetails()
{
    if (id == -1)
        return;
    cout << "\n��������:\n";
    cout << "ID               : " << id << "\n";
    cout << "������ ���       : " << firstName << " " << lastName << "\n";
    cout << "���              : " << gender << "\n";
    cout << "�������          : " << age << "\n";
    cout << "����� ��������   : " << mobNumber << "\n";
    cout << "�����            :";
    add.print();
    return;
}
void person::printDetailsFromHistory()
{
    if (id == -1)
        return;
    cout << "\n�������� � ������� :\n";
    cout << "������ ���           : " << firstName << " " << lastName << "\n";
    cout << "���                  : " << gender << "\n";
    cout << "�������              : " << age << "\n";
    cout << "����� ��������       : " << mobNumber << "\n";
    cout << "�����                :";
    add.print();
    return;
}