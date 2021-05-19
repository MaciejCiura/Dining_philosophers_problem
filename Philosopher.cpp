//
// Created by ciamek on 17.05.2021.
//

#include <iostream>
#include <chrono>
#include "Philosopher.h"

Philosopher::Philosopher(unsigned int id, std::mutex& left, std::mutex& right, std::atomic<bool>& running) :
		_id(id),
		_forkLeft(left),
		_forkRight(right),
		_task(&Philosopher::eat, this, std::ref(running)){}
	
Philosopher::~Philosopher()
{
	_task.join();
	say("Elo mówi nr.: " + std::to_string(_id) + '.');
}

void Philosopher::say(const std::string& message)
{
	static std::mutex cout_mutex;
	cout_mutex.lock();
	std::cout << message << std::endl;
	cout_mutex.unlock();
}

void Philosopher::eat(std::atomic<bool>& running)
{
	while(running)
	{
		_forkLeft.lock();
		say("Nr. " + std::to_string(_id) + " picked up left fork.");
		_forkRight.lock();
		say("Nr. " + std::to_string(_id) + " picked up right fork.");
//		std::lock_guard<std::mutex> left_lock(_forkLeft, std::adopt_lock);

		say("Nr. " + std::to_string(_id) + " eating");
		std::this_thread::sleep_for(std::chrono::seconds(2));
		
		_forkLeft.unlock();
		say("Nr. " + std::to_string(_id) + " put down left fork.");
		_forkRight.unlock();
		say("Nr. " + std::to_string(_id) + " put down right fork.");
		
		say("Nr. " + std::to_string(_id) + " going to sleep.");
		think();
	}
}

void Philosopher::think()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
}



