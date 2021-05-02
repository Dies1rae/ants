#include "polygone.h"

#include <iostream>
#include <Windows.h>

using namespace std;

void set_console_size(size_t size) {
	HANDLE hOut;
	SMALL_RECT DisplayArea = { 0, 0, 0, 0 };
	//set x and y to whatever ye' want
	int x = size + 5;
	int y = size + 5;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DisplayArea.Right = x;
	DisplayArea.Bottom = y;

	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
}


int main() {
	int poly_size = 0;
	int nest_size = 0;
	cout << "Set polygon size: " << endl;
	cin >> poly_size;
	cout << "Set ant nest size: " << endl;
	cin >> nest_size;


	if (poly_size == 0 || nest_size == 0) {
		cout << "you don't wanna play" << endl;
		return 1;
	}

	polygone* main_ground = new polygone(poly_size, nest_size);
	set_console_size(poly_size);
	//main_ground->display_playground(std::cout);
	//main_ground->display_size_debug_info(std::cout);
	main_ground->main_loop(std::cout);
	return 0;
}