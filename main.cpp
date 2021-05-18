#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <fstream>
#include "mylib.h"

using namespace std;

#define COLUMN_FRAME_TITLE 20
#define ROW_FRAME_TITLE 2

#define COLUMN_FRAME_MENU 20
#define ROW_FRAME_MENU 12

#define COLUMN_RS 30
#define ROW_RS 20

#define COLOR_SL 11
#define COLOR_DF 15

#define UP 72
#define DOWN 80
#define ENTER 13

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

int arrRandom[1000];


// define function
void printTitleQLMH();
void printFrameInputMH();
int printOptionQLMH();
void printFrame(int width, int height, int x, int y, int color);
void printTitle(int width, int x);
void createTable(int x, int y, int row);
void printTitleMH(int width, int x);
void createTableMonhocs(int x, int y, int row);
void openwriteMH();



// datastructe

struct MonHoc {
	char maMH[10];
	char tenMH[50];
	int STCLY;
	int STCTH;
};

struct SinhVien {
	char maSV[15];
	char ho[15];
	char ten[15];
	char phai;
	char sdt[10];
	int maLop;
};

struct DangKy {
	char maSV[15];
	float diem;
};

struct LopTC {
	int maLop;
	char maMH[10];
	int niemKhoa;
	char hocKi[3];
	int nhom;
	int SvMin;
	int SvMax;
	SinhVien *sv[100];
};



// Danh Sach Tuyen Tinh
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
		for (int i = 0; i < index; i++) {
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
	}
	if (nodeTree->key > x) {
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

int sizeMonhoc = 0;

template <typename T>
void getSizeMonHoc(NodeTree<T> *root) {
	if(root != NULL) {
		getSizeMonHoc(root->left);
		sizeMonhoc++;
		getSizeMonHoc(root->right);
	}
}

template <typename T>
void writeFileMonHoc(NodeTree<T> *root);


BinarySearchTree<MonHoc> monhocs;
int keyMonhoc = 0;

// title
string titles[] = {
	"DO AN QUAN LY SINH VIEN HE TIN CHI",
	"SINH VIEN THUC HIEN",
	"KHAU MINH DUY - N16DCAT014",
	"CHU NGUYEN LAM TRUONG - N16DCAT"

};

string titlesQLMH[] = {
	"QUAN LY MON HOC"
};

string optionQLMH[] = {
	"1 Them MH",
	"2 Sua MH",
	"3 Xoa MH",
	"4 Danh Sach Mon Hoc",
	"5 Luu Vao File",
	"6 Quay Lai"
};

string menus[] = {
	"1. Quan ly Mon Hoc",
	"2. Quan Ly Lop Tin Chi",
	"3. Quan Ly Sinh Vien",
	"4. Thoat"
};

string optionMH[] = {
	"Ten Mon Hoc",
	"Option 2",
	"Option 3",
	"Option 4"
};

void listMonhocs() {
	system("cls");
	printTitleQLMH();
	createTableMonhocs(COLUMN_FRAME_MENU + 2, ROW_FRAME_MENU + 1, sizeMonhoc);	
}

int rowMonhoc = 14;

template <typename T>
void printMonHoc(NodeTree<T> *root) {
	if(root != NULL) {
		printMonHoc(root->left);
		gotoxy(24, rowMonhoc);
		cout << root->data.maMH;
		gotoxy(44, rowMonhoc);
		cout << root->data.tenMH;
		gotoxy(74, rowMonhoc);
		cout << root->data.STCLY;
		gotoxy(84, rowMonhoc);
		cout << root->data.STCTH;
		gotoxy(95, rowMonhoc);
		cout << root->key;
		printMonHoc(root->right);
	} else {
		rowMonhoc+=2;
	}
}
ofstream ofs;

string *split(string s, string del = " ") {
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

void processQLMH() {
	int choose;
	int size = sizeof(optionQLMH)/sizeof(optionQLMH[0]);
	do {
		getSizeMonHoc(monhocs.root);
		system("cls");
		printTitleQLMH();
		choose = printOptionQLMH();
		switch(choose) {
			case 0:
				system("cls");
				printTitleQLMH();
				printFrame(75, 20, COLUMN_FRAME_MENU, ROW_FRAME_MENU, COLOR_SL);
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 2, 4);
				gotoxy(31, 15);
				cout << "Ma Mon Hoc";
				gotoxy(31, 17);
				cout << "Ten Mon Hoc";
				gotoxy(31, 19);
				cout << "STCLY";
				gotoxy(31, 21);
				cout << "STCTH";
				gotoxy(51, 15);
				MonHoc mh;
				gets(mh.maMH);
				gotoxy(51, 17);
				gets(mh.tenMH);
				gotoxy(51, 19);
				cin >> mh.STCLY;
				gotoxy(51, 21);
				cin >> mh.STCTH;
				fflush(stdin);
				add(monhocs, arrRandom[keyMonhoc], mh);
				keyMonhoc++;
				sizeMonhoc = 0;
				break;
			case 1:
				system("cls");
				printTitleQLMH();
				printFrame(75, 20, COLUMN_FRAME_MENU, ROW_FRAME_MENU, COLOR_SL);
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 4, 1);
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 8, 4);
				gotoxy(31, 21);
				cout << "Ma Mon Hoc";
				gotoxy(31, 23);
				cout << "Ten Mon Hoc";
				gotoxy(31, 25);
				cout << "STCLY";
				gotoxy(31, 27);
				cout << "STCTH";
				getch();
				break;
			case 2:
				
				break;
			case 3: {
				listMonhocs();
				int x = COLUMN_FRAME_MENU + 4;
				int y = ROW_FRAME_MENU + 2;
				gotoxy(x, y );
				cout << "MA MON HOC" << endl;
				gotoxy(x + 20, y);
				cout << "TEN MON HOC" << endl;
				gotoxy(x + 50, y );
				cout << "STCLT" << endl;
				gotoxy(x + 60, y );
				cout << "STCTH" << endl;
				gotoxy(x + 70, y );
				y+=2;
				
				printMonHoc(monhocs.root);
				rowMonhoc = 14;
				getch();
				
				break;
			}	
			case 4: {
				ofs.open("monhoc.txt", ofstream::out);
				writeFileMonHoc(monhocs.root);
				ofs.close();
				break;
			}
				
			
				
		}
	} while (choose != size - 1);
}



// menu & titles

void printTitles(int width, int height, int x, int y, int color) {
	printFrame(width, height, x, y, color);
	printTitle(width,x);
}

void printFrame(int width, int height, int x, int y, int color) {
	SetColor(color);
	gotoxy(x, y);
	cout << LT << setfill(TT) << setw(width) << RT << endl;
	
	for(int i = 1; i < height-1; i++) {
		gotoxy(x, y + i);
		cout << DT << setfill(' ') << setw(width) << DT << endl;
	}
	gotoxy(x, y + height - 1);
	cout << LB << setfill(TT) << setw(width) << RB << endl;
}

void printTitle(int width, int x) {
	int size = sizeof(titles)/sizeof(titles[0]);
	for(int i = 0; i < size; i++) {
		int len = titles[i].length();
		gotoxy((x+width)/1.6 - len/2 , ROW_FRAME_TITLE + 2 + i);
		cout << titles[i];
	}
}

void printTitleMH(int width, int x) {
	int size = sizeof(titlesQLMH)/sizeof(titlesQLMH[0]);
	for(int i = 0; i < size; i++) {
		int len = titlesQLMH[i].length();
		gotoxy((x+width)/1.6 - len/2 , ROW_FRAME_TITLE + 2 + i);
		cout << titlesQLMH[i];
	}
}

void printTitleQLMH() {
	printFrame(75, 5, COLUMN_FRAME_TITLE, ROW_FRAME_TITLE, COLOR_SL);
	printTitleMH(75, COLUMN_FRAME_TITLE);	
}

int printOptionQLMH() {
	int choose = 0;
	printFrame(75, 10, COLUMN_FRAME_MENU, ROW_FRAME_MENU, COLOR_SL);
	int size = sizeof(optionQLMH)/sizeof(optionQLMH[0]);
	int col = COLUMN_FRAME_MENU + 20;
	int row = ROW_FRAME_MENU + 2;
	for(int i = 0; i < size; i++) {
		if(choose == i) {
			gotoxy(col, row + i);
			cout << optionQLMH[i];
		} else {
			SetColor(COLOR_DF);
			gotoxy(col, row + i);
			cout << optionQLMH[i];
		}
		
	}
	char c;
	while(true) {
		c = getch();
		if(c == UP && choose != 0) {
			SetColor(COLOR_DF);
			gotoxy(col, row + choose);
			cout << optionQLMH[choose--];
			SetColor(COLOR_SL);
			gotoxy(col, row + choose);
			cout << optionQLMH[choose];
		} else if (c == DOWN && choose != size - 1) {
			SetColor(COLOR_DF);
			gotoxy(col, row + choose);
			cout << optionQLMH[choose++];
			SetColor(COLOR_SL);
			gotoxy(col, row + choose);
			cout << optionQLMH[choose];
		} else if (c == ENTER) {
			return choose;
		}
	}
}

void createTableMonhocs(int x, int y, int row) {
	SetColor(11);
	int lenCol1 = 20;
	int lenCol2 = 30;
	int lenCol3 = 10;
	int lenCol4 = 10;
	gotoxy(x, y);
	cout << LT << setfill(TT) << setw(lenCol1) << TB << setfill(TT) << setw(lenCol2)
		<< TB << setfill(TT) << setw(lenCol3) << TB << setfill(TT) << setw(lenCol4) << RT << endl; 
	y++;
	for(int i = 1; i <= row+1; i++) {
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

void createTable(int x, int y, int row) {
	SetColor(11);
	int lenCol1 = 20;
	int lenCol2 = 30;
	gotoxy(x, y);
	cout << LT << setfill(TT) << setw(lenCol1) << TB << setfill(TT) << setw(lenCol2) << RT << endl; 
	y++;
	for(int i = 1; i < row; i++) {
		gotoxy(x, y); y++;
		cout << DT << setfill(' ') << setw(lenCol1) << DT << setfill(' ') << setw(lenCol2) << DT << endl;
		gotoxy(x, y); y++;
		cout << LL << setfill(TT) << setw(lenCol1) << CT << setfill(TT) << setw(lenCol2) << RR << endl;
	}
	gotoxy(x, y); y++;
	cout << DT << setfill(' ') << setw(lenCol1) << DT << setfill(' ') << setw(lenCol2) << DT << endl;
	gotoxy(x, y);
	cout << LB << setfill(TT) << setw(lenCol1) << BT << setfill(TT) << setw(lenCol2) << RB << endl;
}



void randomNumber() {
	for(int i = 0; i < 1000; i++) {
		arrRandom[i] = i+1;
	}
}
void generateSetOfNumbers() {  
  	int j,temp;
  	for (int i=999; i>0; --i) {
	    j = rand() % i;
	    temp = arrRandom[i];
	    arrRandom[i] = arrRandom[j];
	    arrRandom[j] = temp;
  	}

}

int menu() {
	printTitles(75, 8, COLUMN_FRAME_MENU, ROW_FRAME_MENU, COLOR_SL);
	int choose = 0;
	int size_menu = sizeof(menus)/sizeof(menus[0]);
	int col = COLUMN_FRAME_MENU + 20;
	int row = ROW_FRAME_MENU + 2;
	for(int i = 0; i < size_menu; i++) {
		if(choose == i) {
			SetColor(COLOR_SL);
			gotoxy(col, row + i);
			cout << menus[i];
		} else {
			SetColor(COLOR_DF);
			gotoxy(col, row + i);
			cout << menus[i];
		}
	}
	
	char c;
	while(true) {
		c = getch();
		if(c == UP && choose != 0) {
			SetColor(COLOR_DF);
			gotoxy(col, row + choose);
			cout << menus[choose--];
			SetColor(COLOR_SL);
			gotoxy(col, row + choose);
			cout << menus[choose];
		} else if(c == DOWN && choose != size_menu - 1) {
			SetColor(COLOR_DF);
			gotoxy(col, row + choose);
			cout << menus[choose++];
			SetColor(COLOR_SL);
			gotoxy(col, row + choose);
			cout << menus[choose];
		} else if(c == ENTER) {
			return choose;
		}
	}
}

template <typename T>
void writeFileMonHoc(NodeTree<T> *root) {
	if(root != NULL) {
		writeFileMonHoc(root->left);
		ofs << root->key <<"," <<root->data.maMH << "," << root->data.tenMH << "," << root->data.STCLY << ","
			<< root->data.STCTH << "\n";
		writeFileMonHoc(root->right);
	}

	
}

ifstream ifs;

void loadDataMonHoc() {
	ifs.open("monhoc.txt", ifstream::in);
	string line;
	string *s;
	MonHoc mh;
	while(getline(ifs, line)) {
		s = split(line+"\n", ",");
		strcpy(mh.maMH, s[1].c_str());
		strcpy(mh.tenMH, s[2].c_str());
		mh.STCLY = stoi(s[3]);
		mh.STCTH = stoi(s[4]);
		add(monhocs, stoi(s[0]), mh);
		keyMonhoc++;
	}
}

int main() {
	randomNumber();
	generateSetOfNumbers();
	newBinarySearchTree(monhocs);
	loadDataMonHoc();
	
	int choose; 
	do {
		system("cls");
		printTitles(75, 8, COLUMN_FRAME_TITLE, ROW_FRAME_TITLE, COLOR_SL);
		choose = menu();
		switch(choose) {
			case 0:
				processQLMH();
				break;
			case 1:
				gotoxy(COLUMN_RS,ROW_RS);
				cout << "2";
				getchar();
				break;
			case 2:
				gotoxy(COLUMN_RS,ROW_RS);
				cout << "3";
				getchar();
				break;
			case 3:
				gotoxy(COLUMN_RS,ROW_RS);
				cout << "exit";
				getchar();
				exit(0);
				break;
		}
	} while (true);
	gotoxy(20,30);
	return 0;
}
