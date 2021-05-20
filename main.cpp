#include <iostream>
#include <vector>
#include "Philosopher.h"

int main()
{
	unsigned int n = 0, sleep_time = 0, eat_time = 0;
	std::atomic<bool> running = true;
	
	std::cout << "Number of philosophers:" << std::endl;
	std::cin >> n;
	
	std::cout << "Sleep time:" << std::endl;
	std::cin >> sleep_time;
	
	std::cout << "Eat time:" << std::endl;
	std::cin >> eat_time;
	
	std::cout << "\033c";
	std::cout << "To exit type 'q'." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout << "\033c";
	
	Dining_time time(sleep_time, eat_time);
	
	std::vector<std::mutex> forks(n);
	
	std::vector<std::unique_ptr<Philosopher>> philosophers;
	philosophers.reserve(n);

	for(int i=0; i<n-1; i++)
		philosophers.push_back(std::make_unique<Philosopher>(i, forks[i], forks[i+1], std::ref(running), time));
	philosophers.push_back(std::make_unique<Philosopher>(n-1, forks[0], forks[n-1], std::ref(running), time)); // <--- protection against deadlock

	char cin_char = 'a';
	while(cin_char != 'q')
		std::cin >> cin_char;
	
	running = false;
	
	philosophers.clear();
}