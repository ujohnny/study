#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "queue.hpp"


int main() {
	Queue<int> q;
	srand(time(0));
	int i = 0;
	auto f1 = [&]() {
	/*
		while (i < 100) {
			int value = rand() % 2000;
			q.push(value);
			std::this_thread::sleep_for(std::chrono::milliseconds(value));
		}
		*/
		int value = 2000;
		q.push(value);
		std::this_thread::sleep_for(std::chrono::milliseconds(value));
		value = 1000;
		q.push(value);
		std::this_thread::sleep_for(std::chrono::milliseconds(value));
		value = 1500;
		q.push(value);
		std::this_thread::sleep_for(std::chrono::milliseconds(value));
	};

	auto f2 = [&]() {
		Queue<int>::iterator c = q.pop();
		std::cout << "1 " << *c << std::endl;
		c = q.pop();
		std::cout << "1 " << *c << std::endl;
		/*int value = *c;
		std::this_thread::sleep_for(std::chrono::milliseconds(value));
		if (i >= 100)
			return;
			*/
	};
	
	auto f3 = [&]() {
		Queue<int>::iterator c = q.pop();
		std::cout << "2 " << *c << std::endl;
		
		/*int value = *c;
		std::this_thread::sleep_for(std::chrono::milliseconds(value));
		if (i >= 100)
			return;
			*/
	};
	
/*	
	auto f3 = [&]() {
		Queue<int>::iterator c = q.pop();
		std::cout << *c << std::endl;
		int value = *c;
		std::this_thread::sleep_for(std::chrono::milliseconds(value));
		if (i >= 100)
			return;
	};
*/

	std::thread t1(f1);
	std::thread t2(f2);
	std::thread t3(f3);
	t1.join();
	t2.join();
	t3.join();

}
