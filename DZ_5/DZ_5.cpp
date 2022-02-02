#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>

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

// первый вариант
void sort_lines_1()
{
	std::multimap<size_t, std::string, std::greater<size_t>> lines;	
	std::cout << "  ========== первый вариант ========== " << std::endl << std::endl;
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

// второй вариант
std::string get_sentence(std::string& s)
{
	std::string punctuation_marks{ ".?!" };                               
	std::string temp;                                                     
	for (const char& c : s)                                               
	{
		temp.push_back(c);                                                
		if (punctuation_marks.find(c) != std::string::npos)                
		{
			s.erase(0, temp.size());                                      
			if (temp[0] == ' ') { temp.erase(0, 1); }                     
			return temp;                                                  
		}
	}
	return {};                                                            
}

void sort_lines_2()
{
	std::unordered_set<std::string, std::hash<std::string>> sentences;
	std::string current_string, temp_string; 
	std::cout << std::endl << "  ========== второй вариант ========== " << std::endl << std::endl;
	std::cout << "Введите текст: ";
	std::getline(std::cin, current_string);
	
	if (!current_string.empty())                                       
	{
		temp_string += current_string + ' ';                            
																		  
		while (true)
		{
			std::string sentence(std::move(get_sentence(temp_string))); 
			if (sentence.empty())
			{
				break;                                                
			}
			sentences.insert(std::move(sentence));                    
		}
	}	

	std::cout << std::endl << "Отсортированный ввод: " << std::endl;

	std::priority_queue<std::pair<size_t, std::string>> x;
	for (const auto& sentence : sentences)
	{
		x.push({ sentence.size(), sentence });
	}
	while (!x.empty())
	{
		std::cout << x.top().first << ": " << x.top().second << std::endl;
		x.pop();
	}
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

		// первый вариант
		sort_lines_1();

		// второй вариант
		sort_lines_2();
	}
}
