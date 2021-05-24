//
// Created by Maciej Ciura on 17.05.2021.
//

#ifndef UNTITLED_PHILOSOPHER_H
#define UNTITLED_PHILOSOPHER_H

#include <mutex>
#include <thread>
#include <atomic>
#include "Dining_time.h"

enum class Philosopher_state {
	AWAKE,
	SLEEPING,
	ONE_FORK,
	EATING
};

class Philosopher
{

public:
	Philosopher(std::mutex& left, std::mutex& right, std::atomic<bool>& running, Dining_time time);
	~Philosopher();
	
	void eat(std::atomic<bool>&);
	unsigned int get_id() const;
	unsigned int get_meals() const;
	std::string get_state() const;
	
protected:
	static unsigned int ID;
	
private:
	unsigned int id_;
	std::mutex& forkLeft_;
	std::mutex& forkRight_;
	std::thread task_;
	unsigned int meals_;
	
	Dining_time time_;
	
	Philosopher_state state_{Philosopher_state::SLEEPING};
	
	static void say(const std::string&);
};

#endif //UNTITLED_PHILOSOPHER_H
