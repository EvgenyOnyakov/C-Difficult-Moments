#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <numeric>
#include <random>

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Имеется отсортированный массив целых чисел.Необходимо разработать функцию insert_sorted, 
// которая принимает вектор и новое число и вставляет новое число в определенную позицию в векторе, 
// чтобы упорядоченность контейнера сохранялась.Реализуйте шаблонную функцию insert_sorted,
// которая сможет аналогично работать с любым контейнером, содержащим любой тип значения.

template <typename TContainer, typename TValue = typename TContainer::value_type>
void insert_sorted(TContainer& input_container, TValue input_value)
{
	TValue this_value, next_value;
	for (auto it = input_container.begin(); it != input_container.end();)
	{
		this_value = *it;
		++it;
		if (it == input_container.end())
		{
			input_container.push_back(input_value);
			return;
		}
		next_value = *it;
		if (this_value < input_value && input_value <= next_value)
		{
			input_container.insert(it, input_value);
			return;
		}
		else if (input_value < this_value)
		{
			input_container.insert(input_container.begin(), input_value);
			return;
		}
	}
}

template <typename TContainer>
void print(const TContainer& input) noexcept
{
	std::cout << std::endl;
	for (auto print : input) 
	{ 
		std::cout << print << " "; 
	}
}

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// Сгенерируйте вектор a, состоящий из 100 вещественный чисел, 
// представляющий собой значения аналогового сигнала.
// На основе этого массива чисел создайте другой вектор целых чисел b,
// представляющий цифровой сигнал, в котором будут откинуты дробные части чисел.
// Выведите получившиеся массивы чисел.Посчитайте ошибку, 
// которой обладает цифровой сигнал по сравнению с аналоговым по формуле.
// Постарайтесь воспользоваться алгоритмическими функциями, не используя циклы.

template <typename T>
void fill_vector(std::vector<T>& vec)
{
	T from = 0;
	T to = 99;
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<T> dis(from, to);
	auto rand = [&]() { return dis(gen); };
	std::generate(vec.begin(), vec.end(), rand);
}

double count_error(const std::vector<double>& input)
{
	double sum = std::accumulate(input.begin(), input.end(), 0.f, [](double current_sum, double const& value) {return current_sum + pow((value - (int)value), 2); });
	return sum;
}

int main()
{
    setlocale(LC_ALL, "Russian");

	// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
    {
        std::cout << std::endl << "  ========== Домашнее задание № 1 ========== " << std::endl << std::endl;

		auto add_val_1 = 3;
		std::string add_val_2 = "ccc";

		std::vector <double> vec = { 1.1, 2.2, 4.4, 5.5 };
		std::list<int> lst = { 1, 2, 4, 5 };
		std::deque<std::string> deq = { "aaa", "bbb", "ddd" };

		std::cout << "Добавляемые значения: " << add_val_1 << " | " << add_val_2 << std::endl << std::endl;
	
		std::cout  << "Vector:";
		print(vec);
		insert_sorted(vec, add_val_1);
		print(vec);
		std::cout << std::endl << std::endl << "Deque:";
		print(deq);		
		insert_sorted(deq, add_val_2);
		print(deq);
		std::cout << std::endl << std::endl << "List:";
		print(lst);
		insert_sorted(lst, add_val_1);
		print(lst);
		std::cout << std::endl;
    }

	// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
	{
		std::cout << std::endl << "  ========== Домашнее задание № 2 ========== " << std::endl << std::endl;

		size_t size = 100;
		std::vector<double> analog(size);
		fill_vector(analog);

		std::cout << "Аналоговый вектор:" << std::endl;
		print(analog);

		std::vector<int> digital(size);
		std::copy(analog.begin(), analog.end(), digital.begin());

		std::cout << std::endl << std::endl << "Цифровой вектор:" << std::endl;
		print(digital);

		std::cout << std::endl << std::endl << "Ошибка: " << count_error(analog);
		std::cout << std::endl << std::endl;
	}
}