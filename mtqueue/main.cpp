#include <iostream>
#include <thread>
#include <chrono>

#include "queue.hpp"


int main() {
	Queue<int> q;

	auto f1 = [&]() {
		std::auto_ptr<int> c = q.pop();
		std::cout << *c << std::endl;
	};

	auto f2 = [&]() {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		q.push(5);
	};


	std::thread t1(f1);
	std::thread t2(f2);
	t1.join();
	t2.join();

}
