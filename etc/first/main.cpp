#include <iostream>

using namespace std;

void func();

int main()
{
	cout << "Hello GDB" << endl;
	
	func();

	cout << "Finished" << endl;

	return EXIT_SUCCESS;
}

void func()
{
	for(int i = 0; i < 10; ++i) {
		cout << i << "\n";
	}
}

