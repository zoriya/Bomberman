/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** main
*/


#include <iostream>
#include "Runner/Runner.hpp"

void usage(const std::string &bin)
{
	std::cout << "Bomberman." << std::endl
		<< "\tUsage: " << bin << " [options]" << std::endl
		<< "Options:" << std::endl
		<< "\t-h:\tPrint this help message" << std::endl;
}

int main(int argc, char **argv)
{
	if (argc == 2 && std::string(argv[1]) == "-h") {
		usage(argv[0]);
		return 1;
	}
	return BBM::Runner::run();
}
