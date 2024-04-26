using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/address.hh"

address::address()
{
    line1 = "";
    line2 = "";
    city = "";
    state = "";
    pinCode = "";
    country = "";
}
void address::takeInput()
{
    cout << "\nВведите адрес:\n";
    cout << "\n1-й адрес:\n";
    getline(cin >> ws, line1);
    cout << "\n2-й адрес (опционально):\n";
    getline(cin, line2);
    cout << "\nГород:\n";
    getline(cin >> ws, city);
    cout << "\nОбласть:\n";
    getline(cin >> ws, state);
    cout << "\nПочтовый индекс:\n";
    getline(cin >> ws, pinCode);
    cout << "\nСтрана:\n";
    getline(cin >> ws, country);
    return;
}
void address::print()
{
    cout << "1-й адрес: " << line1 << "\n";
    if (line2 != "")
        cout << "                  "
             << "2-й адрес: " << line2 << "\n";
    cout << "                  ";
    cout << "Город: " << city << "\n";
    cout << "                  ";
    cout << "Область: " << state << "\n";
    cout << "                  ";
    cout << "Почтовый индекс: " << pinCode << "\n";
    cout << "                  ";
    cout << "Страна: " << country << "\n";
    return;
}
string address::addToStr()
{
    stringstream s;
    s << line1 << "`" << line2 << "`" << city << "`" << state << "`" << pinCode << "`" << country;
    string add;
    getline(s, add);
    for (auto &i : add)
        if (i == ',')
            i = '^';
    return add;
}
void address::strToAdd(string str)
{
    stringstream s(str);
    
    getline(s, line1, '`');
    for (auto &i : line1)
        if (i == '^')
            i = ',';

    getline(s, line2, '`');
    for (auto &i : line2)
        if (i == '^')
            i = ',';

    getline(s, city, '`');
    getline(s, state, '`');
    getline(s, pinCode, '`');
    getline(s, country, '`');
    return;
}