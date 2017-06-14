#pragma once

/* Author: Piotr Biesek */

template <class T>
class MyVectorQueue {
public:
	const size_t default_tab_size;
	MyVectorQueue(const size_t default_tab_size = 10);
	MyVectorQueue(const MyVectorQueue<T>& other);
	MyVectorQueue(MyVectorQueue<T>&& other);
	~MyVectorQueue();
		
	operator bool() const;

	void push(const T& new_element);
	bool pop();
	void resize(double k=2); // k * tab_size
	void clear();

	T get_top();
	const T get_top() const;
	T get_end();
	const T get_end() const;

	bool is_empty() const;
	bool is_full() const;
	size_t size() const;

	const T* get_tab() const;
	size_t get_index_start() const;
	size_t get_index_end() const;
	size_t get_next_index(size_t index) const;
	size_t get_tab_size() const;

private:
	size_t tab_size;
	size_t index_start, index_end;
	T* tab;
};

template<class T>
MyVectorQueue<T>::MyVectorQueue(const size_t default_tab_size) : default_tab_size(default_tab_size) {
	tab_size = default_tab_size;
	index_start = index_end = 0;
	tab = new T[tab_size];
}

template<class T>
MyVectorQueue<T>::MyVectorQueue(const MyVectorQueue<T>& other) : default_tab_size(other.default_tab_size) {
	tab_size = other.tab_size;
	index_start = index_end = 0;
	tab = new T[tab_size];

	size_t help_index = other.index_start;
	for (size_t i = 0; i < other.size(); i++) {
		tab[index_start] = other.tab[other.help_index];

		help_index = other.get_next_index(help_index);
		index_start = get_next_index(index_start);
	}
}

template<class T>
MyVectorQueue<T>::MyVectorQueue(MyVectorQueue<T>&& other) : default_tab_size(other.default_tab_size) {
	tab_size = other.tab_size;
	index_start = other.index_start;
	index_end = other.index_end;
	tab = other.tab_size;
	other.tab = nullptr;
}

template<class T>
MyVectorQueue<T>::~MyVectorQueue() {
	if (tab) {
		delete[] tab;
	}
}

template<class T>
MyVectorQueue<T>::operator bool() const {
	return !empty();
}

template<class T>
void MyVectorQueue<T>::push(const T & new_element) {
	if (is_full()) {
		resize();
	}

	tab[index_end] = new_element;
	index_end = get_next_index(index_end);
}

template<class T>
bool MyVectorQueue<T>::pop() {
	if (is_empty()) {
		clear();
		return false;
	}
	
	index_start = get_next_index(index_start);
	return true;
}

template<class T>
void MyVectorQueue<T>::resize(double k) {
	size_t new_tab_size = tab_size*k;

	if (new_tab_size <= 0) {
		clear();
		new_tab_size = default_tab_size;
	}

	T* new_tab = new T[new_tab_size];
	size_t new_index_start = 0;
	size_t new_index_end = 0;
	size_t current_index = index_start;
	while (current_index != index_end) {
		new_tab[new_index_end] = tab[current_index];
		current_index = get_next_index(current_index);
		new_index_end = get_next_index(new_index_end);
	}

	delete[] tab;
	tab_size = new_tab_size;
	index_start = new_index_start;
	index_end = new_index_end;
	tab = new_tab;
}

template<class T>
void MyVectorQueue<T>::clear() {
	index_start = index_end = 0;
}

template<class T>
bool MyVectorQueue<T>::is_empty() const {
	return index_start == index_end;
}

template<class T>
bool MyVectorQueue<T>::is_full() const {
	return get_next_index(index_end) == index_start;
}

template<class T>
size_t MyVectorQueue<T>::size() const {
	if (index_start <= index_end) {
		return (index_end - index_start);
	}
	else {
		return (tab_size - (index_start - index_end) + 1);
	}
}

template<class T>
const T * MyVectorQueue<T>::get_tab() const {
	return tab;
}

template<class T>
size_t MyVectorQueue<T>::get_index_start() const {
	return index_start;
}

template<class T>
size_t MyVectorQueue<T>::get_index_end() const {
	return index_end;
}

template<class T>
size_t MyVectorQueue<T>::get_next_index(size_t index) const {
	return (index + 1) % tab_size;
}

template<class T>
size_t MyVectorQueue<T>::get_tab_size() const {
	return tab_size;
}

template<class T>
T MyVectorQueue<T>::get_top() {
	return tab[index_start];
}

template<class T>
const T MyVectorQueue<T>::get_top() const {
	return tab[index_start];
}

template<class T>
T MyVectorQueue<T>::get_end() {
	return tab[index_end];
}

template<class T>
const T MyVectorQueue<T>::get_end() const {
	return tab[index_end];
}