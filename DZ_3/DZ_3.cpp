#include <iostream>
#include <list>
#include <iterator>
#include <random>

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Написать функцию, добавляющую в конец списка вещественных чисел элемент, 
// значение которого равно среднему арифметическому всех его элементов.

void d_push(std::list <double>& lst)
{
    std::list<double>::const_iterator p = lst.begin();
    double s(0);
    int    n(0);
    while (p != lst.end())
    {
        s = s + *p;
        ++n;
        ++p;
    }
    if (n != 0) lst.push_back(s / n);
}

void d_print(std::list<double>& lst)
{
    std::copy(lst.begin(), lst.end(), std::ostream_iterator<double>(std::cout, " "));
    std::cout << std::endl;
}

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// Создать класс, представляющий матрицу. Реализовать в нем метод, вычисляющий определитель матрицы.

class matrix
{
private:
    int m_size;
    int** m_data;
public:
    matrix(int& size) : m_size(size)
    {   
        if (m_size % 2 == 0)
        {
            srand(time(0));
            m_data = new int* [m_size];
            for (size_t r = 0; r < m_size; r++)
            {
                m_data[r] = new int[m_size];
                for (size_t c = 0; c < m_size; c++)
                {
                    m_data[r][c] = rand() % 10;
                }
            }
        }
        else
        {
            std::cout << "Определитель можно вычислить только для квадратных матриц ( кратных 2 )" << std::endl << std::endl;           
        }        
    }

    ~matrix() 
    { 
        for (size_t i = 0; i < m_size; i++)
        {
            delete m_data[i];
        } 
    }  

    void GetMatr(int** m_data, int** p, int i, int j, int m_size)
    {
        int ki, kj, di, dj;
        di = 0;

        for (ki = 0; ki < m_size - 1; ki++) 
        { 
            if (ki == i) di = 1;
            dj = 0;

            for (kj = 0; kj < m_size - 1; kj++) 
            { 
                if (kj == j) dj = 1;
                p[ki][kj] = m_data[ki + di][kj + dj];
            }
        }
    }

    int Determinant(int** m_data, int m_size) {
        int i, j, d, k, n;
        int** p;
        p = new int* [m_size];

        for (i = 0; i < m_size; i++)
            p[i] = new int[m_size];

        j = 0; d = 0;
        k = 1; 
        n = m_size - 1;

        if (m_size < 1) std::cout << "Определитель вычислить невозможно!";

        if (m_size == 1)
        {
            d = m_data[0][0];
            return(d);
        }

        if (m_size == 2)
        {
            d = m_data[0][0] * m_data[1][1] -(m_data[1][0] * m_data[0][1]);
            return(d);
        }

        if (m_size > 2) 
        {
            for (i = 0; i < m_size; i++) 
            {
                GetMatr(m_data, p, i, 0, m_size);
                d = d + k * m_data[i][0] * Determinant(p, n);
                k = -k;
            }
        }
        return(d);

        for (size_t i = 0; i < m_size; i++)
        {
            delete p[i];
        }                     
    }

    void print()
    {
        for (size_t r = 0; r < m_size; r++)
        {
            for (size_t c = 0; c < m_size; c++)
            {
                std::cout << m_data[r][c] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << "Определитель матрицы: " << Determinant(m_data, m_size) << std::endl;
    }
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

// Реализовать собственный класс итератора, с помощью которого можно будет проитерироваться по диапазону целых чисел в цикле for - range - based.

template <class T>
class MyArray
{
private:
    T* arr = nullptr;
    int size;

public:
    
    MyArray(int s = 1) : size(s)
    {
        arr = new T[s];
    };

    ~MyArray() { delete[] arr; };

    T& operator [] (const int& s)
    {
        if (s > 0 && s < size)
        {
            return arr[s];
        }
        return arr[0];
    };    

    class MyIterator
    {
    private:
        T* current;

    public:
        MyIterator(T* itr) : current(itr) {};
        ~MyIterator() = default;

        T& operator +  (int val) { return *(current + val); };
        T& operator -  (int val) { return *(current - val); };
        T& operator ++ (int)     { return *(++current);     };
        T& operator -- (int)     { return *(--current);     };
        T& operator ++ ()        { return *(++current);     };
        T& operator -- ()        { return *(--current);     };
        T& operator *  ()        { return *(current);       };

        bool operator != (const MyIterator& it) { return current != it.current; };
        bool operator == (const MyIterator& it) { return current == it.current; };        
    };

    MyIterator begin() { return (arr);        };
    MyIterator end()   { return (arr + size); };
};

int main()
{
	setlocale(LC_ALL, "Russian");

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================
    {
        std::cout << std::endl << "  ========== Домашнее задание № 1 ========== " << std::endl << std::endl;

        std::list <double> foo{1.2, 2.4, 5.3, 6.2};
        d_print(foo);
        d_push(foo);
        d_print(foo);
    }

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
    {
        std::cout << std::endl << "  ========== Домашнее задание № 2 ========== " << std::endl << std::endl;        
        
        int size = 4;
        matrix foo(size);
        foo.print();       
    }

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================
    {
        std::cout << std::endl << "  ========== Домашнее задание № 3 ========== " << std::endl << std::endl;

        MyArray<int> arr(3);
        arr[0] = 100;
        arr[1] = 444;
        arr[2] = 999;

        for (auto itr : arr)
        {
            std::cout << itr << " ";
        }
        std::cout << std::endl << std::endl;
    }
}