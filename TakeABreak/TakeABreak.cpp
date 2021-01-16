#include<iostream>
#include<windows.h>
#include<thread>
#include<string>
#include "TakeABreak.h"


TakeABreak::TakeABreak(int argc, char** argv) :
	m_more_exercises{ true },
	m_minute_counter{ 0 },
	m_min_exercise_minutes{ INVALID_TIME },
	m_max_exercise_minutes{ INVALID_TIME }
{
	get_min_max_times(argc, argv);
}

void TakeABreak::run()
{
	while (m_more_exercises)
	{
		one_exercise();
		system("cls");
	}

	std::cout << "Total minutes:	" << m_minute_counter << std::endl << std::endl;
	system("pause");
}

void TakeABreak::get_min_max_times(int argc, char** argv)
{
	if (argc == 3 && argv != NULL) // 2 parameters
	{
		m_min_exercise_minutes = strtol(argv[1], NULL, DECIMAL);
		m_max_exercise_minutes = strtol(argv[2], NULL, DECIMAL);
	}

	// user input, or invalid args
	while (m_min_exercise_minutes <= 0)
	{
		std::cout << "Enter minimun minutes for the exercise (1 or more): ";
		std::cin >> m_min_exercise_minutes;
	}
	while (m_max_exercise_minutes <= 0 || m_max_exercise_minutes <= m_min_exercise_minutes)
	{
		std::cout << "Enter maximum minutes for the exercise (" << m_min_exercise_minutes + 1 << " or more): ";
		std::cin >> m_max_exercise_minutes;
	}
	system("cls");
}

int TakeABreak::get_random_minutes()
{
	srand(time(NULL));
	int range = rand() % (m_max_exercise_minutes - m_min_exercise_minutes);

	return m_min_exercise_minutes + range;
}

void TakeABreak::print_time_stuff(int exercise_length_minutes)
{
	time_t now_seconds = time(NULL);
	char date_buffer[DATE_BUFF_SIZE];

	// messages
	std::cout << "Total minutes:	" << m_minute_counter << std::endl << std::endl;

	ctime_s(date_buffer, DATE_BUFF_SIZE, &now_seconds);
	std::cout << "Now is:		" << date_buffer;

	std::cout << "Alarm in:	" << exercise_length_minutes << " minutes\n";

	now_seconds += (time_t)exercise_length_minutes * SECONDS_IN_MINUTE;
	ctime_s(date_buffer, DATE_BUFF_SIZE, &now_seconds);
	std::cout << "Alarm at:	" << date_buffer << std::endl;
}

void TakeABreak::one_exercise()
{
	int minutes = get_random_minutes();
	print_time_stuff(minutes);

	// wait
	Sleep(minutes * SECONDS_IN_MINUTE * MILLISECONDS_IN_SECOND);

	// alarm
	m_beeping = true;
	std::thread tr{ &TakeABreak::beep, this };
	when_exercise_ends();
	tr.join();

	m_minute_counter += minutes;
}

void TakeABreak::beep()
{
	while (m_beeping)
	{
		std::cout << (char)7;
		Sleep(ONE_SECOND);
	}
}

void TakeABreak::when_exercise_ends()
{
	std::string s;
	std::cout << "Enter:\n" \
		"'x' to exit,\n" \
		"'p' to pause,\n" \
		"or any other key to restart:\n> ";
	std::cin >> s;
	for (auto& chr : s) chr = tolower(chr);

	if ("exit" == s || "x" == s) {
		m_more_exercises = false;
	}
	else if ("pause" == s || "p" == s) {
		m_beeping = false;
		system("pause");
	}

	m_beeping = false;
}
