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
    cout << "\nВВедите имя:\n";
    getline(cin >> ws, firstName);
    cout << "\nВведите фамилию:\n";
    getline(cin, lastName);

    cout << "\nВведите возраст: \n";
    cin >> age;
    while (age <= 0)
        cout << "Введен неверный возраст\nПопробуйте снова!\n", cin >> age;
    if (category != 2)
    {
        if (age < minAge)
            return void(cout << "Извините, возраст человека должен быть от" << minAge << " лет, чтобы зарегистрировать как " << cat << ".\n");
        else if (age > maxAge)
            return void(cout << "Извините, возраст человека должен быть не больше " << maxAge << " лет, чтобы зарегистрировать как " << cat << ".\n");
    }

    cout << "\nПол (M = Мужской || F = Женский): \n";
    cin >> gender;
    while (gender != 'M' && gender != 'F')
        cout << "M или F?\n", cin >> gender;
    cout << "\nВведите номер телефона (с кодом страны): \n";
    getline(cin >> ws, mobNumber);
    add.takeInput();
    return;
}
void person::printDetails()
{
    if (id == -1)
        return;
    cout << "\nСведения:\n";
    cout << "ID               : " << id << "\n";
    cout << "Полное имя       : " << firstName << " " << lastName << "\n";
    cout << "Пол              : " << gender << "\n";
    cout << "Возраст          : " << age << "\n";
    cout << "Номер телефона   : " << mobNumber << "\n";
    cout << "Адрес            :";
    add.print();
    return;
}
void person::printDetailsFromHistory()
{
    if (id == -1)
        return;
    cout << "\nСведения с истории :\n";
    cout << "Полное имя           : " << firstName << " " << lastName << "\n";
    cout << "Пол                  : " << gender << "\n";
    cout << "Возраст              : " << age << "\n";
    cout << "Номер телефона       : " << mobNumber << "\n";
    cout << "Адрес                :";
    add.print();
    return;
}