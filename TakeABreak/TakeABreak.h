#pragma once
#include<iostream>
#include<windows.h>
#include<thread>
#include<string>

#define DECIMAL 10
#define DATE_BUFF_SIZE 30
#define ONE_SECOND 1000
#define INVALID_TIME 0
#define MILLISECONDS_IN_SECOND 1000
#define SECONDS_IN_MINUTE 60

class TakeABreak {
	bool m_more_exercises = true;
	bool m_beeping = false;
	int m_minute_counter = 0;
	int m_min_exercise_minutes;
	int m_max_exercise_minutes;

public:
	TakeABreak(int argc = 0, char** argv = NULL);
	// start exercises loop
	void run();

private:
	// configure min&max times from cmd args or from user input
	void get_min_max_times(int argc, char** argv);
	// randomize X minutes till next alarm
	int get_random_minutes();
	// print current time, minutes till alarm, alarm time...
	void print_time_stuff(int exercise_length);
	// one exercise routine: rand tine, print messages, wait, and alarm
	void one_exercise();
	// sound beeps until a flag is reset
	void beep();
	// get user commands for next moves
	void when_exercise_ends();
};