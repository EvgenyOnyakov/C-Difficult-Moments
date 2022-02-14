#include <iostream>
#include <iostream>
#include <numeric>
#include <fstream>
#include "students.pb.h"

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Установить библиотеку protobuf.

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// С помощью компилятора protobuf в отдельном пространстве имен сгенерировать классы
//     * FullName с полями имя, фамилия, отчество(отчество опционально).
//     * Student с полями полное имя, массив оценок, средний балл.
//     * StudentsGroup с полем массив студентов.

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

// Создать класс StudentsGroup, который реализует интерфейсы :

// class IRepository 
// {
//    virtual void Open() = 0; // бинарная десериализация в файл
//    virtual void Save() = 0; // бинарная сериализация в файл
// };
// 
// class IMethods 
// {
//    virtual double GetAverageScore(const FullName& name) = 0;
//    virtual string GetAllInfo(const FullName& name) = 0;
//    virtual string GetAllInfo() = 0;
// };

class IRepository
{
public:
    virtual void Open() = 0; // бинарная десериализация в файл
    virtual void Save() = 0; // бинарная сериализация в файл
    virtual ~IRepository() {};
};

class IMethods
{
public:
    virtual double GetAverageScore(const students::FullName& name) = 0;
    virtual std::string GetAllInfo(const students::FullName& name) = 0;
    virtual std::string GetAllInfo() = 0;
    virtual ~IMethods() {};
};

class StudentsGroup : public IRepository, public IMethods
{
private:
    std::vector<students::Student> m_students;
public:
    void add_student(const students::Student& s)
    {
        m_students.push_back(s);
    }

    double GetAverageScore(const students::FullName& name)
    {
        auto it = std::find_if(m_students.begin(), m_students.end(), [&](const students::Student& s)
            {
                return tie(s.name().name(), s.name().surname(), s.name().patronymic()) ==
                    tie(name.name(), name.surname(), name.patronymic());
            });

        if (it == m_students.end())
        {
            return 0.0;
        }

        return it->avg_score();
    }

    std::string GetAllInfo(const students::FullName& name)
    {
        auto it = std::find_if(m_students.begin(), m_students.end(), [&](const students::Student& s)
            {
                return tie(s.name().name(), s.name().surname(), s.name().patronymic()) ==
                    tie(name.name(), name.surname(), name.patronymic());
            });

        if (it == m_students.end())
        {
            return {};
        }

        std::string temp = "Имя:          " + it->name().name() + ' ' + it->name().surname() + ' ' + it->name().patronymic() + '\n';
        temp += "Оценки:       ";
        for (int i = 0; i < it->grades().size(); ++i)
        {
            temp += std::to_string(it->grades(i)) + "; ";
        }
        temp += '\n';
        temp += "Средний балл: " + std::to_string(it->avg_score()) + "\n\n";

        return temp;
    }

    std::string GetAllInfo()
    {
        std::string temp;

        std::for_each(m_students.begin(), m_students.end(), [&](const students::Student& s)
            {
                temp += GetAllInfo(s.name());
            });

        return temp;
    }

    void Save()
    {
        std::ofstream out("students.bin", std::ios_base::binary);
        auto size = m_students.size();
        out.write(reinterpret_cast<char*>(&size), sizeof(size));
        std::for_each(m_students.begin(), m_students.end(), [&](const students::Student& s)
            {
                s.SerializeToOstream(&out);
            });
        out.close();
    }

    void Open()
    {
        std::ifstream in("students.bin", std::ios_base::binary);
        size_t size = 0;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        while (size--)
        {
            students::Student s;
            s.ParseFromIstream(&in);
            m_students.push_back(std::move(s));
        }
        in.close();
    }

    virtual ~StudentsGroup() {};
};

int main()
{
    setlocale(LC_ALL, "Russian");   

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
    {
        std::cout << std::endl << "  ========== Домашнее задание № 2 ========== " << std::endl << std::endl;

        students::FullName fn;
        fn.set_name("Ivan");
        fn.set_surname("Ivanov");
        fn.set_patronymic("Ivanovich");

        students::Student s;
        *s.mutable_name() = fn;
        s.add_grades(5);
        s.add_grades(2);
        s.add_grades(4);
        s.add_grades(3);
        s.add_grades(4);
        s.add_grades(3);
        s.add_grades(4);
        s.add_grades(3);
        s.set_avg_score(std::accumulate(s.grades().begin(), s.grades().end(), 0) / s.grades().size());

        students::StudentsGroup sg;
        *sg.add_students() = s;

        std::ofstream out("students.bin", std::ios_base::binary);
        sg.SerializeToOstream(&out);
        out.close();

        students::StudentsGroup new_sg;
        std::ifstream in("students.bin", std::ios_base::binary);
        if (new_sg.ParseFromIstream(&in))
        {
            std::cout << "Студент:      " 
            << new_sg.students(0).name().surname() 
            << " " << new_sg.students(0).name().name()
            << " " << new_sg.students(0).name().patronymic() 
            << std::endl;

            std::cout << "Средний балл: " << new_sg.students(0).avg_score() << std::endl;
        }
        else
        {
            std::cout << "Ошибка!" << std::endl;
        }
        in.close();
    }

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================
    {
        std::cout << std::endl << "  ========== Домашнее задание № 3 ========== " << std::endl << std::endl;

        students::FullName fn;
        fn.set_name("Petr");
        fn.set_surname("Petrov");
        fn.set_patronymic("Petrovich");

        students::Student s;
        *s.mutable_name() = fn;
        s.add_grades(5);
        s.add_grades(2);
        s.add_grades(4);
        s.add_grades(3);
        s.add_grades(4);
        s.add_grades(3);
        s.add_grades(4);
        s.add_grades(3);
        s.set_avg_score(std::accumulate(s.grades().begin(), s.grades().end(), 0) / s.grades().size());

        StudentsGroup sg;
        sg.add_student(s);
        sg.Save();

        StudentsGroup new_sg;
        new_sg.Open();
        std::cout << new_sg.GetAllInfo(fn) << std::endl;
    }
}