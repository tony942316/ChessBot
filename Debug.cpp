#include "Debug.h"

buggy::buggy()
{

}

void buggy::addTrace(std::string trace)
{
	tracer.push_back(trace);
}

void buggy::printTrace()
{
	for (std::string trace : tracer)
	{
		std::cout << trace << std::endl;
	}

	tracer.clear();
}