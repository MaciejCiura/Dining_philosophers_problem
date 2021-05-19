//
// Created by ciamek on 17.05.2021.
//

#ifndef UNTITLED_PHILOSOPHER_H
#define UNTITLED_PHILOSOPHER_H

#include <mutex>
#include <thread>
#include <atomic>

class Philosopher
{
public:
	Philosopher(unsigned int id, std::mutex& left, std::mutex& right, std::atomic<bool>& running);
	~Philosopher();
	void eat(std::atomic<bool>&);
	static void think();
private:
	unsigned int _id;
	std::mutex& _forkLeft;
	std::mutex& _forkRight;
	std::thread _task;
	
	static void say(const std::string&);
};


#endif //UNTITLED_PHILOSOPHER_H
