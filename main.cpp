#include <iostream>
#include <vector>
#include <ncurses.h>

#include "Philosopher.h"

int main()
{
	initscr();
	unsigned int n = 0;
	std::atomic<bool> running = true;
	
	std::cout << "Number of philosophers:" << std::endl;
	
	std::cin >> n;
	std::vector<std::mutex> forks(n);
	
	std::vector<std::unique_ptr<Philosopher>> philosophers;
	philosophers.reserve(n);

	for(int i=0; i<n-1; i++)
		philosophers.push_back(std::make_unique<Philosopher>(i, forks[i], forks[i+1], std::ref(running)));
	philosophers.push_back(std::make_unique<Philosopher>(n-1, forks[0], forks[n-1], std::ref(running)));

	char cin_char = 'a';
	while(cin_char != 'q')
		cin_char = getch();
	
	running = false;
	philosophers.clear();
	endwin();
}