#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов, 
// и выводящую в консоль список уникальных слов
// (если слово повторяется больше 1 раза, то вывести его надо один раз).
// Продемонстрировать работу функции, передав итераторы различных типов.

template<typename T>
void unique_words(T it_begin, T it_end)
{
	std::set<typename T::value_type> unique_set(it_begin, it_end);
	std::for_each(unique_set.begin(), unique_set.end(), [](const auto& it) 
	{ 
		std::cout << it << " "; 
	});
	std::cout << std::endl;
}

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// Используя ассоциативный контейнер, напишите программу, 
// которая будет считывать данные введенные пользователем из стандартного потока ввода и разбивать их на предложения.
// Далее программа должна вывести пользователю все предложения, отсортировав их по длине.

void sort_lines()
{
	std::multimap<size_t, std::string, std::greater<size_t>> lines;	

	while (true)
	{
		std::string line;	
		std::cout << "Введите текст: ";
		std::getline(std::cin, line);
		if (line.empty())
		{
			break;
		}
		lines.insert(std::make_pair(line.size(), line));		
	}

	std::cout << std::endl << "Отсортированный ввод: " << std::endl;

	std::for_each(lines.begin(), lines.end(), [](const auto& v) 
	{ 
			std::cout << v.first << ": " << v.second << std::endl; 
	});
}

int main()
{
	setlocale(LC_ALL, "Russian");

	// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================
	{
		std::cout << std::endl << "  ========== Домашнее задание № 1 ========== " << std::endl << std::endl;

		std::cout << "Vector (char)  : ";
		const std::vector<char> vec = { 'a', 'a', 'a', 'b', 'b', 'b', 'c', 'c', 'c' };
		unique_words(vec.begin(), vec.end());

		std::cout << "Deque  (int)   : ";
		std::deque<int> deq = { 1, 1, 1, 2, 2, 2, 3, 3, 3 };
		unique_words(deq.begin(), deq.end());

		std::cout << "List   (string): ";
		std::list <std::string> lst = { "Test1", "Test1", "Test2", "Test2", "Test3", "Test3" };
		unique_words(lst.begin(), lst.end());
	}

	// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
	{
		std::cout << std::endl << "  ========== Домашнее задание № 2 ========== " << std::endl << std::endl;

		sort_lines();
	}
}