#include <iostream>
#include <iomanip>
#include "mylib.h"

using namespace std;

const char TT = 196; 
const char DT = 179; 
const char RR = 180; 
const char LL = 195; 
const char CT = 197; 
const char LT = 218;
const char RT = 191;
const char RB = 217;
const char LB = 192;
const char BT = 193;
const char TB = 194; 


void printFrame(int width, int height, int x, int y, int color) {
	SetColor(color);
	gotoxy(x, y);
	cout << LT << setfill(TT) << setw(width) << RT << endl;
	
	for(int i = 1; i < height-1; i++) {
		gotoxy(x, y + i);
		cout << DT << setfill(' ') << setw(width) << DT << endl;
	}
	gotoxy(x, height);
	cout << LB << setfill(TT) << setw(width) << RB << endl;
}

void createTable(int x, int y, int row) {
	SetColor(11);
	gotoxy(x, y);
	cout << LT << setfill(TT) << setw(20) << TB << setfill(TT) << setw(10) << RT << endl; 
	y++;
	for(int i = 1; i < row; i++) {
		gotoxy(x, y); y++;
		cout << DT << setfill(' ') << setw(20) << DT << setfill(' ') << setw(10) << DT << endl;
		gotoxy(x, y); y++;
		cout << LL << setfill(TT) << setw(20) << CT << setfill(TT) << setw(10) << RR << endl;
	}
	gotoxy(x, y); y++;
	cout << DT << setfill(' ') << setw(20) << DT << setfill(' ') << setw(10) << DT << endl;
	gotoxy(x, y);
	cout << LB << setfill(TT) << setw(20) << BT << setfill(TT) << setw(10) << RB << endl;
}

template <typename T>
struct ArrayList {
	int member;
	int size;
	T *array;
};

template <typename T>
bool isFull(ArrayList<T> &arraylist) {
	return arraylist.size == arraylist.member;
}

template <typename T>
bool isEmpty(ArrayList<T> &arraylist) {
	return arraylist.size == 0;
}

template <typename T>
int getSize(ArrayList<T> &arraylist) {
	return arraylist.size;
}

template <typename T>
void newArrayList(ArrayList<T> &arraylist, int member) {
	arraylist.member = member;
	arraylist.size = 0;
	arraylist.array = new T[member];
}

template <typename T>
void add(ArrayList<T> &arraylist, T data) {
	if (isFull(arraylist)) {
		cout << "Danh Sach Da Day";
	} else {
		arraylist.array[arraylist.size++] = data;
	}
}

template <typename T>
void add(ArrayList<T> &arraylist,int index, T data) {
	if (isFull(arraylist)) {
		cout << "Danh Sach Da Day";
	} else if (index < 0 || index > arraylist.size) {
		cout << "Index khong hop le";
	} else {
		for (int i = arraylist.size; i > index; i--) {
			arraylist.array[i] = arraylist.array[i - 1];
		}
		arraylist.array[index] = data;
		arraylist.size++;
	}
}

template <typename T>
T get(ArrayList<T> &arraylist, int index) {
	if (index < 0 || index > arraylist.size || arraylist.size == 0) {
		cout << "Index khong hop le";
	} else {
		return arraylist.array[index];
	}
}

template <typename T>
void remove(ArrayList<T> &arraylist, int index) {
	if (index < 0 || index > arraylist.size || arraylist.size == 0) {
		cout << "Index khong hop le"; 
	} else {
		for (int i = index, size = arraylist.size; i < size; i++) {
			arraylist.array[i] = arraylist.array[i + 1];
		}
		arraylist.size--;
	}
}


// Danh Sach Lien Ket
template <typename T>
struct Node {
	T data;
	Node *next;
};

template <typename T>
struct LinkedList {
	Node<T> *head;
	int size;
};

template <typename T>
void newLinkedList(LinkedList<T> &linkedlist) {
	linkedlist.head = NULL;
	linkedlist.size = 0;
}

template <typename T>
bool isEmpty(LinkedList<T> &linkedlist) {
	return linkedlist.size == 0;
}

template <typename T>
void addFirst(LinkedList<T> &linkedlist, T data) {
	Node<T> *newNode = new Node<T>; 
	newNode->data = data;
	newNode->next = linkedlist.head;
	linkedlist.head = newNode;
	linkedlist.size++;
}

template <typename T>
void add(LinkedList<T> &linkedlist, T data) {
	Node<T> *newNode = new Node<T>;
	newNode->data = data;
	newNode->next = NULL;
	if (linkedlist.head != NULL) {
		Node<T> *temp = new Node<T>;
		temp = linkedlist.head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
		linkedlist.size++;
		temp = NULL;
		delete temp;
	} else {
		linkedlist.head = newNode;
		linkedlist.size++;
	}
}

template <typename T>
void add(LinkedList<T> &linkedlist, int index, T data) {
	if (index < 0 || index >= linkedlist.size || isEmpty(linkedlist)) {
		cout << "Index Khong Hop Le.";
	} else if (index == 0) {
		addFirst(linkedlist, data);
	} else {
		Node<T> *newNode = new Node<T>;
		newNode->data = data;
		newNode->next = NULL;
		Node<T> *temp = new Node<T>;
		temp = linkedlist.head;
		for (int i = 1; i < index; i++) {
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
		linkedlist.size++;
		temp = NULL;
		delete temp;
	}
}

template <typename T>
T get(LinkedList<T> &linkedlist, int index) {
	Node<T> *temp = new Node<T>;
	temp = linkedlist.head;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	T result = temp->data;
	temp = NULL;
	delete temp;
	return result;
}

template <typename T>
void removeFirst(LinkedList<T> &linkedlist) {
	if (isEmpty(linkedlist)) {
		return;
	} 
	Node<T> *nodeRemove = new Node<T>;
	nodeRemove = linkedlist.head;
	linkedlist.head = nodeRemove->next;
	delete nodeRemove;
	linkedlist.size--;
}

template <typename T>
void remove(LinkedList<T> &linkedlist, int index) {
	if (index < 0 || index >= linkedlist.size || isEmpty(linkedlist)) {
		cout << "Index khong hop le";
		return;
	} else if (index == 0) {
		removeFirst(linkedlist);
	} else {
		Node<T> *temp = new Node<T>;
		Node<T> *nodeRemove = new Node<T>;
		temp = linkedlist.head;
		nodeRemove = linkedlist.head;
		for (int i = 0; i < index; i++) {
			temp = nodeRemove;
			nodeRemove = nodeRemove->next;
		}
		temp->next = nodeRemove->next;
		linkedlist.size--;
		delete nodeRemove;
	}
}

template <typename T>
void show(LinkedList<T> &linkedlist) {
	for(int i = 0, size = linkedlist.size; i < size; i++) {
		cout << get(linkedlist, i) << endl;
	}
}

int main() {

	LinkedList<int> lists;
	newLinkedList(lists);
	add(lists, 1);
	addFirst(lists, 2);
	add(lists, 3);
	add(lists, 1, 4);
	show(lists);
	
	cout << "REMOVE\n" ;
	remove(lists, 3);
	show(lists);
	
	cout << "\n";
	
	add(lists, 5);
	show(lists);
	cout << "\n";
	addFirst(lists, 6);
	show(lists);
	

	return 0;
}
