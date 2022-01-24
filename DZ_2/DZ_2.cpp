#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>
#include <fstream>

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;
    std::string m_name;
    std::chrono::time_point<clock_t> m_beg;
    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now()
            - m_beg).count();
    }
public:
    Timer() : m_beg(clock_t::now()) { }
    Timer(std::string name) : m_name(name), m_beg(clock_t::now()) { }
    void start(std::string name) {
        m_name = name;
        m_beg = clock_t::now();
    }
    ~Timer() { print(); }
    void print() const {
        std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
    }
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения, на которые указывают эти указатели
// (нужно обменивать именно сами указатели, переменные должны оставаться в тех же адресах памяти).

template<typename T>
void Swap1(T* foo, T* bar)
{
    T temp = *foo;
    *foo = *bar;
    *bar = temp;
}

template<typename T>
void Swap2(T& foo, T& bar)
{
    T temp = foo;
    foo = bar;
    bar = temp;
}

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей и сортирует указатели по значениям, на которые они указывают.

template<typename T>
void SortPointers(std::vector<T*>& ptr)
{
    std::sort(ptr.begin(), ptr.end(), [](const auto& ptr1, const auto& ptr2)
    {
        return *ptr1 < *ptr2;
    });
}

void PrintVec(std::vector<int*> Vptr,size_t length)
{    
    for (int i = 0; i < length; ++i)
    {
        std::cout << *Vptr[i] << ' ';
    }
    std::cout << std::endl;
}

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

// Подсчитайте количество гласных букв в книге “Война и мир”.Для подсчета используйте 4 способа:
// count_if и find
// count_if и цикл for
// цикл for и find
// 2 цикла for
// Замерьте время каждого способа подсчета и сделайте выводы.
 
// Справка :
// count_if - это алгоритмическая функция из STL, которая принимает 3 параметра : 
// итератор на начало, итератор на конец и унарный предикат(функцию, принимающую один параметр и возвращающую тип bool).

// find - это метод класса string, который возвращает позицию символа(строки), переданного в качестве параметра, 
// в исходной строке.Если символ не найден, то метод возвращает string::npos.

class WaP
{
private: 
    const std::string_view vowels {"AEIOUYaeiouy"};    

public:
   
    void method_number_one(const std::string_view& text)
    {
        Timer timer1("1 способ");
        size_t count = count_if(text.begin(), text.end(), [&](const auto& v)
            {
                return vowels.find(v) != std::string::npos;
            });
        std::cout << "Количество гласных букв: " << count << std::endl;        
    }

    void method_number_two(const std::string_view& text)
    {
        std::cout << "============================================" << std::endl;
        Timer timer2("2 способ");
        size_t count = count_if(text.begin(), text.end(), [&](const auto& v)
        {
            for (size_t i = 0; i < vowels.size(); ++i)
            {
                if (vowels[i] == v)
                    return true;
            }
            return false;
        });
        std::cout << "Количество гласных букв: " << count << std::endl;
    }

    void method_number_three(const std::string_view& text)
    {
        std::cout << "============================================" << std::endl;
        Timer timer3("3 способ");
        size_t count = 0;
        for (size_t i = 0; i < text.size(); ++i)
        {
            if (vowels.find(text[i]) != std::string::npos)
            {
                ++count;
            }
        }
        std::cout << "Количество гласных букв: " << count << std::endl;
    }

    void method_number_four(const std::string_view& text)
    {
        std::cout << "============================================" << std::endl;
        Timer timer4("4 способ");
        size_t count = 0;
        for (size_t i = 0; i < text.size(); ++i)
        {
            for (size_t j = 0; j < vowels.size(); ++j)
            {
                if (vowels[j] == text[i])
                    ++count;
            }
        }
        std::cout << "Количество гласных букв: " << count << std::endl;
    }

};

int main()
{
    setlocale(LC_ALL, "Russian");

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================
    {
        std::cout << "  ========== Домашнее задание № 1 ========== " << std::endl << std::endl;

        int a(100);
        int b(999);

        int* ptrA = &a;
        int* ptrB = &b;

        // Возможно неверно понял задание, поэтому реализовал 2мя способами
         
        // Способ № 1
        std::cout << a << ' ' << b << std::endl;
        std::cout << ptrA << ' ' << ptrB << std::endl;
        Swap1(&a, &b);
        std::cout << ptrA << ' ' << ptrB << std::endl;
        std::cout << a << ' ' << b << std::endl;

        // Способ № 2
        std::cout << "============================================" << std::endl;
        std::cout << a << ' ' << b << std::endl;
        std::cout << ptrA << ' ' << ptrB << std::endl;
        Swap2(ptrA, ptrB);
        std::cout << ptrA << ' ' << ptrB << std::endl;
        std::cout << a << ' ' << b << std::endl;
    }

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
    {
        std::cout << std::endl << "  ========== Домашнее задание № 2 ========== " << std::endl << std::endl;

        std::vector<int*> vec;               
        size_t length = 10;

        for (int i = 0; i < length; ++i)
        {
            int* a = new int;
            *a = rand() % 20;
            vec.push_back(a);
        }        
        PrintVec(vec, length);
        SortPointers(vec);
        PrintVec(vec, length);
    }

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================
    {
        std::cout << std::endl << "  ========== Домашнее задание № 3 ========== " << std::endl << std::endl;               

        std::ifstream file("WAR_and_PEACE.txt");
        if (!file)
        {
            std::cout << "Ошибка: отсутствует файл: WAR_and_PEACE.txt" << std::endl;
        }
        else
        {
            // Получение размера файла
            file.seekg(0, file.end);
            size_t length = file.tellg();
            std::string TEXT(length, ' ');
            file.seekg(0, file.beg);
            // Считывание данных из файла
            file.read(&TEXT[0], length);
            // Закрытие файла
            file.close();

            WaP FOO;
            FOO.method_number_one(TEXT);
            FOO.method_number_two(TEXT);
            FOO.method_number_three(TEXT);
            FOO.method_number_four(TEXT);
            std::cout << std::endl;
        }        
    }
}
