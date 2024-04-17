#include "Queue.h"

using namespace std;

void Queue::push(int value)
{
	for (size_t i = 0; i < 10; i++)
	{
		if (data[i] == 0) {
			data[i] = value;
		}
	}
}
