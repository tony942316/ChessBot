#pragma once

#include <vector>
#include <iostream>

class buggy
{
public:
	buggy();
public:
	void addTrace(std::string trace);
	void printTrace();
private:
	std::vector<std::string> tracer;
};