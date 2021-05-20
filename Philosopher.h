//
// Created by Maciej Ciura on 17.05.2021.
//

#ifndef UNTITLED_PHILOSOPHER_H
#define UNTITLED_PHILOSOPHER_H

#include <mutex>
#include <thread>
#include <atomic>
#include "Dining_time.h"

class Philosopher
{
public:
	Philosopher(unsigned int id, std::mutex& left, std::mutex& right, std::atomic<bool>& running, Dining_time time);
	
	~Philosopher();
	void eat(std::atomic<bool>&);
	
private:
	unsigned int id_;
	std::mutex& forkLeft_;
	std::mutex& forkRight_;
	std::thread task_;
	unsigned int meals_;
	
	Dining_time time_;
	
	static void say(const std::string&);
};

#endif //UNTITLED_PHILOSOPHER_H
