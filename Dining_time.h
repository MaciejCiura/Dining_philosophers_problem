//
// Created by Maciej Ciura on 20.05.2021.
//

#ifndef UNTITLED_DINING_TIME_H
#define UNTITLED_DINING_TIME_H

#include <random>

struct Dining_time {
public:
	Dining_time(unsigned int sleep_time, unsigned int eat_time) : sleep_dist_(sleep_time*800, sleep_time*1200), eat_dist_(eat_time*800, eat_time*1200) {}
	int get_sleep_time(){
		return sleep_dist_(rng_);
	}
	
	int get_eat_time(){
		return eat_dist_(rng_);
	}
private:
	std::mt19937 rng_{std::random_device {}()};
	std::uniform_int_distribution<std::mt19937::result_type> sleep_dist_;
	std::uniform_int_distribution<std::mt19937::result_type> eat_dist_;
};


#endif //UNTITLED_DINING_TIME_H
