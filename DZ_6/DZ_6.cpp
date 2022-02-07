#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <random>

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Создайте потокобезопасную оболочку для объекта cout. Назовите ее pcout. 
// Необходимо, чтобы несколько потоков могли обращаться к pcout и информация выводилась в консоль. 
// Продемонстрируйте работу pcout.

static std::mutex m;

class pcout
{
private:
	std::lock_guard<std::mutex> lg;
public:
	pcout() : lg(std::lock_guard<std::mutex>(m))
	{
	}

	template<typename T>
	pcout& operator<<(const T& data)
	{
		std::cout << data;
		return *this;
	}

	pcout& operator<<(std::ostream& (*x)(std::ostream&))                
	{                                                                    
		std::cout << x;                                                 
		return *this;                                                    
	}                                                                    
};

void use_pcout(int val)
{
	pcout() << "Начало потока " << val << std::endl;
	pcout() << "Конец  потока " << val << std::endl;
}

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// Реализовать функцию, возвращающую i-ое простое число (например, миллионное простое число равно 15485863). 
// Вычисления реализовать во вторичном потоке. В консоли отображать прогресс вычисления. 

size_t find_simple_number(size_t val)
{
	if (val <= 2) {
		std::cout << "Числа 1 и 2 простые" << std::endl;
		if (val == 1) {
			return 1;
		}
		else {
			return 2;
		}
	}

	if (val % 2 == 0) {
		--val;
	}

	bool flag = true; 
	size_t temp;
	size_t val_sqrt = std::sqrt(val); 

	std::cout << std::endl << "===== Начало вычислений =====" << std::endl;

	do
	{
		temp = val;
		flag = true;

		for (size_t i = 3; i < val_sqrt; i += 2) {
			if ((val) % i == 0) {
				val -= 2;
				flag = false;
				break;
			}
			
			std::cout << i << " ";
			
		}
	} while (!((temp == val) && flag));

	std::cout << std::endl << "===== Конец вычислений =====" << std::endl << std::endl;
	return temp;
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

// Промоделировать следующую ситуацию.
// Есть два человека(2 потока) : хозяин и вор.
// Хозяин приносит домой вещи (функция добавляющая случайное число в вектор с периодичностью 1 раз в секунду).
// При этом у каждой вещи есть своя ценность.
// Вор забирает вещи (функция, которая находит наибольшее число и удаляет из вектора с периодичностью 1 раз в 0.5 секунд), 
// каждый раз забирает вещь с наибольшей ценностью.

void add_item(std::vector<std::pair<size_t, char>>& house)
{
	while (!house.empty())
	{
		srand(time(0));
		size_t cost_element = (rand() % 90 + 10); // cost
		char name_element = (rand() % 25 + 65); // A-Z 
		{
			std::lock_guard lg(m);
			house.push_back({ cost_element, name_element });
			std::cout << "+++ Хозяин +++ | Принес: "
			<< " | название: "
			<< name_element
			<< " | цена: " 
			<< cost_element
			<< " | Количество вещей: "
			<< house.size()
			<< std::endl;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
};

void steal_item(std::vector<std::pair<size_t, char>>& house)
{
	while (!house.empty())
	{
		auto dell_element = std::max_element(house.begin(), house.end());
		std::pair<size_t, char> temp = *dell_element;
		{
			std::lock_guard lg(m);
			
			std::cout << "---  Вор   --- | Украл : "
			<< " | название: "
			<< temp.second
			<< " | цена: "
			<< temp.first
			<< " | Количество вещей: "
			<< house.size()
			<< std::endl;

			house.erase(dell_element);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	
	// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================
	{
		std::cout << std::endl << "  ========== Домашнее задание № 1 ========== " << std::endl << std::endl;

		std::thread th1(use_pcout, 1);
		std::thread th2(use_pcout, 2);
		std::thread th3(use_pcout, 3);
		th1.join();
		th2.join();
		th3.join();
	}

	// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
	{
		std::cout << std::endl << "  ========== Домашнее задание № 2 ========== " << std::endl << std::endl;
		
		size_t value = 15485863;

		m.lock();
		std::cout << "ID начального потока = " << std::this_thread::get_id() << std::endl;
		std::cout << find_simple_number(value) << " - простое число из " << value << std::endl;
		std::cout << "ID конечного потока = " << std::this_thread::get_id() << std::endl;
		m.unlock();
	}

	// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================
	{
		std::cout << std::endl << "  ========== Домашнее задание № 3 ========== " << std::endl << std::endl;

		std::vector<std::pair<size_t, char>> house;
		house.reserve(100);
		house.push_back({ 10,'A' });
		house.push_back({ 20,'B' });
		house.push_back({ 30,'C' });
		house.push_back({ 40,'D' });
		house.push_back({ 50,'E' });
		house.push_back({ 60,'F' });
		house.push_back({ 70,'G' });
		house.push_back({ 80,'H' });
		house.push_back({ 90,'I' });
		house.push_back({ 55,'J' });

		std::thread owner(add_item, ref(house));
		std::thread thief(steal_item, ref(house));

		owner.join();
		thief.join();
	}
}