#include <main.h>
#include "tp1.h"
#include <time.h>

/*
 * main method
 * 'main.h' is located at 'glbase-dist/include/main.h'
 */
int main(int argc, const char* argv[])
{
	// First argument is log file, if it exists
	if (argc >= 1)
		Log::SetFile(argv[0]);

	srand((uint) time(NULL));

	// Creates a new instance of 'core' on the stack.
	CoreTP1 core;

	core.Run();

	// End of program, returns '0' to mean no error.
	return 0;
}

float randomFloat(float minValue, float maxValue)
{
	int precision = 1000;
	int random    = rand() % (precision + 1); // between 0 and 1000

	return minValue + (maxValue - minValue) * ((float)random / precision);;
}
