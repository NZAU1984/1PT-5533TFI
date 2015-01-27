#include <main.h>
#include "tp1.h"

/*
 * main method
 * 'main.h' is located at 'glbase-dist/include/main.h'
 */
int main(int argc, const char* argv[])
{
	// First argument is log file, if it exists
	if (argc >= 1)
		Log::SetFile(argv[0]);

	// Creates a new instance of 'core' on the stack.
	CoreTP1 core;

	core.Run();

	// End of program, returns '0' to mean no error.
	return 0;
}
