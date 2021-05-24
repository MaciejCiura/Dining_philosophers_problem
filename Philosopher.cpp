//
// Created by Maciej Ciura on 17.05.2021.
//

#include <iostream>
#include <chrono>
#include <functional>
#include "Philosopher.h"

unsigned int Philosopher::ID = 0;

Philosopher::Philosopher(std::mutex& left, std::mutex& right, std::atomic<bool>& running, Dining_time time) :
		forkLeft_(left),
		forkRight_(right),
		meals_(0),
		time_(time),
		task_(&Philosopher::eat, this, std::ref(running)){
	id_ = ID++;
}

Philosopher::~Philosopher()
{
	task_.join();
	//say("Philosopher nr. " + std::to_string(id_) + " ate " + std::to_string(meals_) + " meals.");
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
		state_ = Philosopher_state::AWAKE;
		
		/* Left fork */
		forkLeft_.lock();
		state_ = Philosopher_state::ONE_FORK;
		std::this_thread::sleep_for(std::chrono::milliseconds (10));
		//say("Nr. " + std::to_string(id_) + " picked up left fork.");
		
		
		/* Right fork */
		forkRight_.lock();
		std::this_thread::sleep_for(std::chrono::milliseconds (10));
		//say("Nr. " + std::to_string(id_) + " picked up right fork.");
		
		/* Eating */
		//say("Nr. " + std::to_string(id_) + " eating " + std::to_string(meals_) + ". time.");
		state_ = Philosopher_state::EATING;
		std::this_thread::sleep_for(std::chrono::milliseconds (time_.get_eat_time()));
		meals_++;
		
		forkLeft_.unlock();
		//say("Nr. " + std::to_string(id_) + " put down left fork.");
		forkRight_.unlock();
		//say("Nr. " + std::to_string(id_) + " put down right fork.");
		
		/* Sleeping */
		//say("Nr. " + std::to_string(id_) + " going to sleep.");
		state_ = Philosopher_state::SLEEPING;
		std::this_thread::sleep_for(std::chrono::milliseconds (time_.get_sleep_time()));
	}
}

unsigned int Philosopher::get_id() const
{
	return id_;
}

unsigned int Philosopher::get_meals() const
{
	return meals_;
}

std::string Philosopher::get_state() const
{
	switch (static_cast<int>(state_))
	{
		case 0:
			return "Awake   ";
		
		case 1:
			return "Sleeping";
		
		case 2:
			return "One fork";
		
		case 3:
			return "Eating  ";
		
		default:
			break;
	}
	return "Wrong state";
}



