#include "MyVectorQueue.h"
#include <iostream>

using namespace std;

template <class T>
void pokaz(const MyVectorQueue<T>& kolejka) {
	std::cout << kolejka.size() << "/" << kolejka.get_tab_size() << ": ";
	const T* tab = kolejka.get_tab();
	std::cout << "( ";
	for (size_t i = kolejka.get_index_start(); i != kolejka.get_index_end(); i = kolejka.get_next_index(i)) {
		std::cout << tab[i] << " ";
	}
	std::cout << ") " << std::endl;
}

int main() {
	MyVectorQueue<int> kolejka;

	char cmd;
	int nr;
	
	cin >> cmd;
	while (cmd != 'q') {
		if (cmd == 'p') {
			cin >> nr;
			kolejka.push(nr);
		}
		else if (cmd == 'c') {
			kolejka.clear();
		}
		else {
			kolejka.pop();
		}

		system("CLS");
		pokaz(kolejka);
		cout << endl;
		cin >> cmd;
	}

	return 0;
}