#include <iostream>
#include <iomanip>
#include "mylib.h"
#include <fstream> 
#include <string>

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



void createTableMonhocs(int x, int y) {
	SetColor(11);
	int lenCol1 = 20;
	int lenCol2 = 30;
	int lenCol3 = 10;
	int lenCol4 = 10;
	gotoxy(x, y);
	cout << LT << setfill(TT) << setw(lenCol1) << TB << setfill(TT) << setw(lenCol2)
		<< TB << setfill(TT) << setw(lenCol3) << TB << setfill(TT) << setw(lenCol4) << RT << endl; 
	y++;
	for(int i = 1; i < 4; i++) {
		gotoxy(x, y); y++;
		cout << DT << setfill(' ') << setw(lenCol1) << DT << setfill(' ') << setw(lenCol2)
			<<  DT << setfill(' ') << setw(lenCol3) << DT << setfill(' ') << setw(lenCol4) << DT << endl;
		gotoxy(x, y); y++;
		cout << LL << setfill(TT) << setw(lenCol1) << CT << setfill(TT) << setw(lenCol2) 
			<<  CT << setfill(TT) << setw(lenCol3) << CT << setfill(TT) << setw(lenCol4)	<< RR << endl;
	}
	gotoxy(x, y); y++;
	cout << DT << setfill(' ') << setw(lenCol1) << DT << setfill(' ') << setw(lenCol2)
		<< DT << setfill(' ') << setw(lenCol3) << DT << setfill(' ') << setw(lenCol4)	<< DT << endl;
	gotoxy(x, y);
	cout << LB << setfill(TT) << setw(lenCol1) << BT << setfill(TT) << setw(lenCol2) 
		<< BT << setfill(TT) << setw(lenCol3) << BT << setfill(TT) << setw(lenCol4) << RB << endl;
}

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

// Binary Search Tree
template <typename T>
struct NodeTree {
	int key;
	T data;
	NodeTree<T> *left;
	NodeTree<T> *right;
};

template <typename T>
struct BinarySearchTree {
	NodeTree<T> *root;
};

template <typename T>
void newBinarySearchTree(BinarySearchTree<T> &bts) {
	bts.root = NULL;
}

template <typename T>
bool isEmpty(BinarySearchTree<T> &bts) {
	return bts.root == NULL ? true : false;
}

template <typename T>
void insertNode(NodeTree<T> *&nodeTree, int x, T data) {
	if (nodeTree == NULL) {
		nodeTree = new NodeTree<T>;
		nodeTree->key = x;
		nodeTree->data = data;
		nodeTree->left = nodeTree->right = NULL;
		return;
	} else if (nodeTree->key > x) {
		insertNode(nodeTree->left, x, data);
	} else if (nodeTree->key < x) {
		insertNode(nodeTree->right, x, data);
	}
}

template <typename T>
void add(BinarySearchTree<T> &bts, int x, T data) {
	insertNode(bts.root, x, data);
}

template <typename T>
void inorderNode(NodeTree<T> *root) {
	if (root != NULL) {
		inorderNode(root->left);
		cout << root->data;
		inorderNode(root->right);
	}
}

template <typename T>
void inorder(BinarySearchTree<T> &bts) {
	inorderNode(bts.root);
}

template <typename T>
NodeTree<T> *minValueNode(NodeTree<T> *root) {
    while (root->left != NULL) root = root->left;
    return root;
}

template <typename T>
NodeTree<T> *deleteNodeTree(NodeTree<T> *root, int key) {
	if(root == NULL) return root;
	else if(key < root->key) {
		root->left = deleteNodeTree(root->left, key);
	} else if(key > root->key) {
		root->right = deleteNodeTree(root->right, key);
	} else {
		if(root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		} else if(root->left == NULL) {
			NodeTree<T> *temp = root;
			root = root->right;
			delete temp;
		} else if(root->right == NULL) {
			NodeTree<T> *temp = root;
			root = root->left;
			delete temp;
		} else {	
			NodeTree<T> *temp = minValueNode(root->right);
			root->key = temp->key;
			root->data = temp->data;
			root->right = deleteNodeTree(root->right, temp->key);
		}
	}
		
	return root;
}
template <typename T>
T get(NodeTree<T> *root, int key) {
	if(root->key == key) return root->data;
	if(root->key > key) return get(root->left, key);
	if(root->key < key) return get(root->right, key);
}

int arr[1000];

void randomNumber() {
	for(int i = 0; i < 1000; i++) {
		arr[i] = i+1;
	}
}

void generateSetOfNumbers() {  
  	int j,temp;
  	for (int i=999; i>0; --i) {
	    j = rand() % i;
	    temp = arr[i];
	    arr[i] = arr[j];
	    arr[j] = temp;
  	}

}

void tokenize(string s, string del = " ") {
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        cout << s.substr(start, end - start) << endl;
        start = end + del.size();
        end = s.find(del, start);
    }
    cout << s.substr(start, end - start);
}

string *tokenize2(string s, string del = " ")
{
	string *str = new string[5];
    int start = 0;
    int end = s.find(del);
    int index = 0;
    while (end != -1) {
        str[index++] = s.substr(start, end - start);
        start = end + del.size();
        end = s.find(del, start);
    }

    str[index] = s.substr(start, end - start);
    return str;
}
string *split(string s, string del = " ") {
	string *str = new string[10];
    int start = 0;
    int end = s.find(del);
    int index = 0;
    while (end != -1) {
        str[index++] = s.substr(start, end - start);
        start = end + del.size();
        end = s.find(del, start);
    }
    str[index] = s.substr(start, end - start);
    return str;
}
int maLop = 1;
ifstream ifs_ltc;
void loadDataLopTinChi() {
	ifs_ltc.open("loptinchi.txt", ifstream::in);
	string line;
	string *str;
	while(getline(ifs_ltc, line)) {
		str = split(line+"\n", ",");
		cout << str[0] << endl;
		cout << str[1] << endl;
		cout << str[2] << endl;
		cout << str[3] << endl;
		cout << str[4] << endl;
		cout << str[5] << endl;
//		cout << str[1] << endl;
//		cout << str[2] << endl;
//		cout << str[3] << endl;
//		cout << str[4] << endl;
	}
}

int main() {

	loadDataLopTinChi();
	
	
	getch();
	return 0;
}
