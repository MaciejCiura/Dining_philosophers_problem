//
// Created by Maciej Ciura on 17.05.2021.
//

#include <iostream>
#include <chrono>
#include <functional>
#include "Philosopher.h"

Philosopher::Philosopher(unsigned int id, std::mutex& left, std::mutex& right, std::atomic<bool>& running, Dining_time time) :
		id_(id),
		forkLeft_(left),
		forkRight_(right),
		meals_(0),
		time_(time),
		task_(&Philosopher::eat, this, std::ref(running)){
}

Philosopher::~Philosopher()
{
	task_.join();
	say("Philosopher nr. " + std::to_string(id_) + " ate " + std::to_string(meals_) + " meals.");
}

void Philosopher::say(const std::string &message)
{
	static std::mutex cout_mutex;
	cout_mutex.lock();
	std::cout << message << std::endl;
	cout_mutex.unlock();
}

void Philosopher::eat(std::atomic<bool> &running)
{
	while (running)
	{
		forkLeft_.lock();
		say("Nr. " + std::to_string(id_) + " picked up left fork.");
		forkRight_.lock();
		say("Nr. " + std::to_string(id_) + " picked up right fork.");
//		std::lock_guard<std::mutex> left_lock(forkLeft_, std::adopt_lock);
		
		
		say("Nr. " + std::to_string(id_) + " eating " + std::to_string(++meals_) + ". time.");
		std::this_thread::sleep_for(std::chrono::milliseconds (time_.get_eat_time()));
		
		
		forkLeft_.unlock();
		say("Nr. " + std::to_string(id_) + " put down left fork.");
		forkRight_.unlock();
		say("Nr. " + std::to_string(id_) + " put down right fork.");
		
		say("Nr. " + std::to_string(id_) + " going to sleep.");
		std::this_thread::sleep_for(std::chrono::milliseconds (time_.get_sleep_time()));
	}
}


