#include <iostream>
#include <vector>
#include <ncurses.h>
#include "Philosopher.h"

int main()
{
	initscr();

	unsigned int n = 0, sleep_time = 0, eat_time = 0;
	std::atomic<bool> running = true;
	
	printw("Number of philosophers: ");
	refresh();
	scanw("%u", &n);
	
	printw("Sleep time: ");
	refresh();
	scanw("%u", &sleep_time);
	
	printw("Eat time: ");
	refresh();
	scanw("%u", &eat_time);
	
	erase();
	refresh();
	
	Dining_time time(sleep_time, eat_time);
	
	std::vector<std::mutex> forks(n);
	
	std::vector<std::unique_ptr<Philosopher>> philosophers;
	philosophers.reserve(n);
	
	for (int i = 0; i < n - 1; i++)
		philosophers.push_back(std::make_unique<Philosopher>(forks[i], forks[i + 1], std::ref(running), time));
	philosophers.push_back(std::make_unique<Philosopher>(forks[0], forks[n - 1], std::ref(running), time)); // <--- protection against deadlock
	
	std::thread scanner([&running]() {
		while (running)
			if (getch() == 'q')
				running = false;
	});
	
	while (running)
	{
		erase();
		refresh();
		
		printw("| Id  \t| State \t| Meals |\n");
		printw("_________________________________\n");
		for (const auto &p : philosophers)
		{
			printw("| %d\t| %s\t| %d\t|\n", p->get_id(), p->get_state().c_str(), p->get_meals());
			refresh();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	scanner.join();
	philosophers.clear();
	endwin();
}