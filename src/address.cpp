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
    cout << "\n������� �����:\n";
    cout << "\n1-� �����:\n";
    getline(cin >> ws, line1);
    cout << "\n2-� ����� (�����������):\n";
    getline(cin, line2);
    cout << "\n�����:\n";
    getline(cin >> ws, city);
    cout << "\n�������:\n";
    getline(cin >> ws, state);
    cout << "\n�������� ������:\n";
    getline(cin >> ws, pinCode);
    cout << "\n������:\n";
    getline(cin >> ws, country);
    return;
}
void address::print()
{
    cout << "1-� �����: " << line1 << "\n";
    if (line2 != "")
        cout << "                  "
             << "2-� �����: " << line2 << "\n";
    cout << "                  ";
    cout << "�����: " << city << "\n";
    cout << "                  ";
    cout << "�������: " << state << "\n";
    cout << "                  ";
    cout << "�������� ������: " << pinCode << "\n";
    cout << "                  ";
    cout << "������: " << country << "\n";
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