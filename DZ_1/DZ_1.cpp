#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Имеется база сотрудников и номеров их телефонов.Требуется написать соответствующие структуры для хранения данных, 
// и заполнить контейнер записями из базы.Затем необходимо реализовать методы обработки данных, а также вывести на экран всю необходимую информацию.
// Важно! Имена переменным, классам и функциям давайте осознанные, состоящие из слов на английском языке.

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Создайте структуру Person с 3 полями: фамилия, имя, отчество. 
// Поле отчество должно быть опционального типа, т.к. не у всех людей есть отчество. 
// Перегрузите оператор вывода данных для этой структуры.
// Также перегрузите операторы < и == (используйте tie).

struct Person 
{
    string surname;
    string name;
    optional<string> patronymic;    
};

ostream& operator << (ostream& out, const Person& p)
{
    out << left << setw(15) << p.surname << setw(15) << p.name << setw(15) << p.patronymic.value_or("");

    return out;
};

bool operator < (const Person& p1, const Person& p2)
{
    return tie(p1.surname, p1.name, p1.patronymic) < tie(p2.surname, p2.name, p2.patronymic);
};

bool operator == (const Person& p1, const Person& p2)
{
    return tie(p1.surname, p1.name, p1.patronymic) == tie(p2.surname, p2.name, p2.patronymic);
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// Создайте структуру PhoneNumber с 4 полями:
// · код страны(целое число)
// · код города(целое число)
// · номер(строка)
// · добавочный номер(целое число, опциональный тип)
// Для этой структуры перегрузите оператор вывода.
// Необходимо, чтобы номер телефона выводился в формате : +7(911)1234567 12, 
// где 7 – это номер страны, 911 – номер города, 1234567 – номер, 12 – добавочный номер.
// Если добавочного номера нет, то его выводить не надо.
// Также перегрузите операторы < и == (используйте tie)

struct PhoneNumber
{
    int countryCode;
    int cityCode;
    string number;
    optional<int> add = nullopt;
};

ostream& operator << (ostream& out, const PhoneNumber& p)
{
    out << '+' << p.countryCode << '(' << p.cityCode << ')' << p.number;

    if (p.add.has_value())
    {
        out << ' ' << p.add.value();
    }

    return out;
};

bool operator < (const PhoneNumber& p1, const PhoneNumber& p2)
{       
    return tie(p1.countryCode, p1.cityCode, p1.number, p1.add) < tie(p2.countryCode, p2.cityCode, p2.number, p2.add);
};

bool operator == (const PhoneNumber& p1, const PhoneNumber& p2)
{
    return tie(p1.countryCode, p1.cityCode, p1.number, p1.add) == tie(p2.countryCode, p2.cityCode, p2.number, p2.add);
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

// Создайте класс PhoneBook, который будет в контейнере хранить пары : Человек – Номер телефона.
// Конструктор этого класса должен принимать параметр типа ifstream – поток данных, полученных из файла.
// В теле конструктора происходит считывание данных из файла и заполнение контейнера.

class PhoneBook
{
private:
    vector<pair<Person, PhoneNumber>> m_phoneBook;
public:
    PhoneBook(ifstream &file)
    {    
        
        if (file.is_open())
        {   
            Person p;
            PhoneNumber n;
            string patronymic;
            string addNumber;
            while (!file.eof())
            {
                file >> p.surname >> p.name >> patronymic >> n.countryCode >> n.cityCode >> n.number >> addNumber;

                if (patronymic != "-")
                    p.patronymic = patronymic;
                else
                    p.patronymic = nullopt;

                if (addNumber != "-")
                    n.add = stoi(addNumber);
                else
                    n.add = nullopt;

                m_phoneBook.emplace_back(p,n);                
            }

            file.close();
        }
        else
        {
            cout << "Не удаётся открыть файл!" << endl;
        }
    }  

    // В классе PhoneBook реализуйте метод SortByName, который должен сортировать элементы контейнера по фамилии людей в алфавитном порядке.
    // Если фамилии будут одинаковыми, то сортировка должна выполняться по именам, если имена будут одинаковы, то сортировка производится по отчествам.
    // Используйте алгоритмическую функцию sort.

    void SortByName()
    {
        sort(m_phoneBook.begin(), m_phoneBook.end(), [](const pair<Person, PhoneNumber>& lhs, const pair<Person, PhoneNumber>& rhs)
        {
            return lhs.first < rhs.first;
        });
    }

    // Реализуйте метод SortByPhone, который должен сортировать элементы контейнера по номерам телефонов.Используйте алгоритмическую функцию sort.

    void SortByPhone()
    {
        sort(m_phoneBook.begin(), m_phoneBook.end(), [](const pair<Person, PhoneNumber>& lhs, const pair<Person, PhoneNumber>& rhs)
        {
            return lhs.second < rhs.second;
        });
    }

    // Реализуйте метод GetPhoneNumber, который принимает фамилию человека, а возвращает кортеж из строки и PhoneNumber.
    // Строка должна быть пустой, если найден ровно один человек с заданном фамилией в списке.Если не найден ни один человек с заданной фамилией, 
    // то в строке должна быть запись «not found», если было найдено больше одного человека, то в строке должно быть «found more than 1».

    pair<string, PhoneNumber> GetPhoneNumber(const string &find_surname)
    {   
        PhoneNumber number;
        int count = 0;

        for_each(m_phoneBook.begin(), m_phoneBook.end(), [&](const auto& entry)
        {            
            if (entry.first.surname == find_surname)
            {
                number = entry.second;
                ++count;
            }
        });

        switch (count)
        {
        case 0:
            return { "not found", number };
        case 1:
            return { "", number };
        default:
            return { "found more than 1", number };
        }
    }

    // Реализуйте метод ChangePhoneNumber, который принимает человека и новый номер телефона и, если находит заданного человека в контейнере, 
    // то меняет его номер телефона на новый, иначе ничего не делает.

    void ChangePhoneNumber(const Person& p, const PhoneNumber& pn)
    {
        auto entry = find_if(m_phoneBook.begin(), m_phoneBook.end(), [&](const auto& entry)
        {
            return entry.first == p;
        });

        if (entry != m_phoneBook.end())
        {
            entry->second = pn;
        }
    }

    // Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.

    friend ostream& operator << (ostream& out, const PhoneBook& pb)
    {           
        for (const auto& [pers, numb] : pb.m_phoneBook)
        {
            out << pers << "\t" << numb << endl;
        }
        return out;
    };
};

int main()
{
    setlocale(LC_ALL, "Russian");

    ifstream file("PhoneBook.txt"); // путь к файлу PhoneBook.txt
    PhoneBook book(file);
    cout << book;    
    
    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;

    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;

    cout << "-----GetPhoneNumber-----" << endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname) {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            cout << get<1>(answer);
        else
            cout << get<0>(answer);
        cout << endl;
    };

    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov"); 
    print_phone_number("Solovev");

    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;

    return 0;
}