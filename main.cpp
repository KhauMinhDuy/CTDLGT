#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <fstream>
#include <stdexcept>
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

#define MAX_MH 1000
#define MAX_LTC 10000

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



void printTitleQLMH();
void printFrameInputMH();
int printOptionQLMH();
void printFrame(int width, int height, int x, int y, int color);
void printTitle(int width, int x);
void createTable(int x, int y, int row);
void printTitleMH(int width, int x);
void createTableMonhocs(int x, int y, int row);
void openwriteMH();

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
	char maLop[15];
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
	bool huyLop;
	int SvMin;
	int SvMax;
	SinhVien *sv;
};

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
T *get(ArrayList<T> &arraylist, int index) {
	if (index < 0 || index > arraylist.size || arraylist.size == 0) {
		cout << "Index khong hop le";
	} else {
		return &arraylist.array[index];
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
void inorderNode(NodeTree<T> *&root) {
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
	if(key < root->key) {
		root->left = deleteNodeTree(root->left, key);
	} else if(key > root->key) {
		root->right = deleteNodeTree(root->right, key);
	} else {
		if(root->left == NULL && root->right == NULL) {
			NodeTree<T> *temp = root;
			root = NULL;
			delete temp;
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

int arrRandom[100];

int sizeMonhoc = 0;

template <typename T>
void getSizeMonHoc(NodeTree<T> *&root) {
	if(root != NULL) {
		getSizeMonHoc(root->left);
		sizeMonhoc++;
		getSizeMonHoc(root->right);
	}
}

BinarySearchTree<MonHoc> monhocs;
ArrayList<LopTC> lopTinChis;
int keyMonhoc = 0;

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
	"1. Them MH",
	"2. Sua MH",
	"3. Xoa MH",
	"4. Danh Sach Mon Hoc",
	"5. Danh Sach Mon Hoc Tang Dan Theo Ten",
	"6. Luu Vao File",
	"7. Quay Lai"
};

string optionMH[] = {
	"Ten Mon Hoc",
	"Option 2",
	"Option 3",
	"Option 4"
};

string menus[] = {
	"1. Quan ly Mon Hoc",
	"2. Quan Ly Lop Tin Chi",
	"3. Quan Ly Sinh Vien",
	"4. Thoat"
};


void listMonhocs() {
	system("cls");
	printTitleQLMH();
	createTableMonhocs(COLUMN_FRAME_MENU + 2, ROW_FRAME_MENU + 1, sizeMonhoc);	
}


int rowMonhoc = 14;
void printMonHoc(NodeTree<MonHoc> *root) {
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

MonHoc searchMaMH(NodeTree<MonHoc> *root, int key) {
	if(root != NULL) {	
		if(root->key == key) {
			return root->data;
		}  	
	}
	if(root->key > key) return searchMaMH(root->left, key);
	if(root->key < key) return searchMaMH(root->right, key);	
}

string arrMamh[100];
MonHoc BtsToArray[100];

int indexArrayBST = 0;
void generateKey(NodeTree<MonHoc> *&root) {
	if(root != NULL) {
		generateKey(root->left);
		arrMamh[root->key] = root->data.maMH;
		BtsToArray[indexArrayBST++] = root->data;
		generateKey(root->right);
	}
}

void swap(MonHoc &mh1, MonHoc &mh2){
	MonHoc mh = mh1;
	mh1 = mh2;
	mh2 = mh;
}

int partition (MonHoc *arr, int low, int high){
    MonHoc pivot = arr[high];    // pivot
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && strcmp(arr[left].tenMH, pivot.tenMH) < 0) left++;
        while(right >= left && strcmp(arr[right].tenMH, pivot.tenMH) > 0) right--;
        if (left >= right) break;
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
    swap(arr[left], arr[high]);
    return left;
}

void quickSort(MonHoc *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printMonHoc(MonHoc *mh) {
	quickSort(BtsToArray, 0, indexArrayBST);
	int size = sizeof(mh)/sizeof(mh[0]);
	for (int i = 0; i <= indexArrayBST; i++) {
		gotoxy(24, rowMonhoc);
		cout << mh[i].maMH;
		gotoxy(44, rowMonhoc);
		cout << mh[i].tenMH;
		gotoxy(74, rowMonhoc);
		cout << mh[i].STCLY;
		gotoxy(84, rowMonhoc);
		cout << mh[i].STCTH;
		rowMonhoc+=2;
	}
}

int searchKeyMaMH(char s[10]) {
	for(int i = 0; i < 100; i++) {
		if(arrMamh[i] == s) {
			return i;
		}
	}
	return -1;	
}

void updateMonHoc(NodeTree<MonHoc> *&root, int key, MonHoc data){
	if(root->key == key) {
		root->data = data;
	}  
	if (root->left != NULL) {
		updateMonHoc(root->left, key, data);
	}  
	if(root->right != NULL) {
		updateMonHoc(root->right, key, data);
	}
}

void writeFileMonHoc(NodeTree<MonHoc> *&root) {
	if(root == NULL) {
		return;
	}
	ofs << root->data.maMH << "," << root->data.tenMH << "," 
		<< root->data.STCLY << "," << root->data.STCTH << "\n";
	writeFileMonHoc(root->left);
	writeFileMonHoc(root->right);
}

NodeTree<MonHoc> *newNode(MonHoc data) { 
    NodeTree<MonHoc> *node = new NodeTree<MonHoc>();
    node->key = searchKeyMaMH(data.maMH);
    node->data = data; 
    node->left = NULL; 
    node->right = NULL; 
    return node; 
} 

void balanceBST(NodeTree<MonHoc> *&root, MonHoc arr[], int start, int end) { 
    if (start > end) return; 

    int mid = (start + end)/2; 
    root = newNode(arr[mid]); 

    balanceBST(root->left, arr, start, mid - 1); 
    balanceBST(root->right,arr, mid + 1, end); 
}

bool isSTCLT(int stclt) {
	return (stclt < 0 || stclt > 4) ? false : true;
}

bool isSTCTH(int stcth) {
	return (stcth < 0 || stcth > 4) ? false : true;
}

void enterMaMH(MonHoc &mh, int row) {
	do {
		string s_maMh;
		gotoxy(51, row);
		cout << "                            ";
		gotoxy(51, row);				
		getline(cin, s_maMh);
		
		if(s_maMh.length() <= 10) {
			strcpy(mh.maMH, s_maMh.c_str());
			int key = searchKeyMaMH(mh.maMH);
			if(key != -1) {
				gotoxy(45, 11);	
				cout << "Ma Mon Hoc Da Ton Tai";
				Sleep(1000);
				gotoxy(45, 11);	
				cout << "                              ";
			} else {
				break;
			}
			
		} else {
			gotoxy(45, 11);	
			cout << "Ma Mon Hoc Khong Qua 10 Ku Tu";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                              ";
		}
		
	} while (true);
}

void enterTenMH(MonHoc &mh, int row) {
	do {
		string s_tenMh;
		gotoxy(51, row);
		cout << "                            ";
		gotoxy(51, row);				
		getline(cin, s_tenMh);
		if(s_tenMh.length() <= 50) {
			strcpy(mh.tenMH, s_tenMh.c_str());
			break;
		} else {
			gotoxy(45, 11);	
			cout << "Ma Mon Hoc Khong Qua 50 Ku Tu";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                              ";
		}
		
	} while (true);
}

void enterSTCLT(MonHoc &mh, int row) {
	do {
		string s_stclt;
		gotoxy(51, row);
		cout << "                            ";
		gotoxy(51, row);				
		getline(cin, s_stclt);
		try {
	        mh.STCLY = stoi(s_stclt);
	        if(isSTCLT(mh.STCLY)) {
				break;
			} else {
				gotoxy(45, 11);	
				cout << "STCLT Khong Hop Le";
				Sleep(1000);
				gotoxy(45, 11);	
				cout << "                           ";
			}	
	    } catch(invalid_argument e) {
	        gotoxy(45, 11);	
			cout << "STCLT Khong Hop Le";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                           ";
	    }
	} while(true);
}

void enterSTCTH(MonHoc &mh, int row) {
	do {
		string s_stcth;
		gotoxy(51, row);
		cout << "                            ";
		gotoxy(51, row);				
		getline(cin, s_stcth);
		try {
	        mh.STCTH = stoi(s_stcth);
	        if(isSTCTH(mh.STCTH)) {
				break;
			} else {
				gotoxy(45, 11);	
				cout << "STCTH Khong Hop Le";
				Sleep(1000);
				gotoxy(45, 11);	
				cout << "                           ";
			}	
	    } catch(invalid_argument e) {
	        gotoxy(45, 11);	
			cout << "Nhom Khong Hop Le";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                           ";
	    }
	} while(true);
}


void processQLMH() {
	
	int choose;
	int size = sizeof(optionQLMH)/sizeof(optionQLMH[0]);
	do {
		indexArrayBST = 0;
		generateKey(monhocs.root);
		balanceBST(monhocs.root, BtsToArray, 0, indexArrayBST - 1);
		rowMonhoc = 14;    // position first row
		sizeMonhoc = 0;
		getSizeMonHoc(monhocs.root);
		system("cls");
		printTitleQLMH();
		choose = printOptionQLMH();
		switch(choose) {
			
			case 0: {   // Them MH
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
				
				MonHoc mh;
				enterMaMH(mh, 15);
				enterTenMH(mh, 17);
				enterSTCLT(mh, 19);
				enterSTCTH(mh, 21);
				add(monhocs, arrRandom[keyMonhoc], mh);
				keyMonhoc++;
				break;
			}
			
			case 1: { // sua mon hoc
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
			
				char mamh[10];
				MonHoc mh;
				int key;
				do {
					fflush(stdin);
					gotoxy(31, 17);
					cout << "Nhap Ma Mon Hoc";
					gotoxy(51,17);
					gets(mamh);
					if(strcmp(mamh,"") == 0) {
						break;
					}
					key = searchKeyMaMH(mamh);
					if(key != -1) {
						mh = searchMaMH(monhocs.root, key);
					}
					
					gotoxy(51,17);
					cout << "                    ";
					if (key != -1) {
						gotoxy(51, 21);
						cout << mh.maMH;
						gotoxy(51, 23);
						cout << mh.tenMH;
						gotoxy(51, 25);
						cout << mh.STCLY;
						gotoxy(51, 27);
						cout << mh.STCTH;
						Sleep(1000);
						gotoxy(51, 23);
						cout << "                        ";
						enterTenMH(mh, 23);
						gotoxy(51, 25);
						cout << "                        ";
						enterSTCLT(mh, 25);
						gotoxy(51, 27);
						cout << "                        ";
						enterSTCTH(mh, 27);
						fflush(stdin);
						updateMonHoc(monhocs.root, key, mh);
						gotoxy(45, 10);
						cout << "Sua Thanh Cong";
						Sleep(1000);
						gotoxy(45, 10);
						cout << "               "; 
						break;
					} else {
						gotoxy(45, 15);
						cout << "khong tim thay mon hoc";
						Sleep(1000);
						gotoxy(45, 15);
						cout << "                        ";
					}
				} while(true);
				break;
			}
			
			case 2: { // xoa mon hoc
				system("cls");
				printTitleQLMH();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 4, 1);
				int key;
				char mamh[10];
				MonHoc mh;
				do {
					fflush(stdin);
					gotoxy(31, 17);
					cout << "Nhap Ma Mon Hoc";
					gotoxy(52,17);
					gets(mamh);
					if(strcmp(mamh,"") == 0) break;
					key = searchKeyMaMH(mamh);
					if(key != -1) mh = searchMaMH(monhocs.root, key);	
					cout << "mamh = " << mamh;
					cout << "\nkey = " << key;
					cout << "\n" << mh.maMH;
					gotoxy(52,17);
					cout << "                    ";
					
					if (key != -1) { 
						deleteNodeTree(monhocs.root, key);
						gotoxy(45, 10);
						cout << "Xoa Thanh Cong";
						Sleep(1000);
						gotoxy(45, 10);
						cout << "               ";
						break;
					} else {
						gotoxy(45, 15);
						cout << "khong tim thay mon hoc";
						Sleep(1000);
						gotoxy(45, 15);
						cout << "                        ";
					}
				} while(true);
				break;
			}
						
			case 3: { // danh sach mon hoc
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
				getch();
				break;
			}
				
			case 4: { // danh sach tang theo ten
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
				printMonHoc(BtsToArray);
				getch();
				break;
				break;
			}	
			case 5: { // luu danh sach mon hoc
				ofs.open("monhoc.txt", ofstream::out);
				writeFileMonHoc(monhocs.root);
				ofs.close();
				gotoxy(45, 10);
				cout << "Luu Thanh Cong";
				Sleep(1000);
				gotoxy(45, 10);
				cout << "               ";
				break;
			}
		}
	} while (choose != size - 1);
}

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

void createTableLTC(int x, int y, int row) {
	SetColor(11);
	int lenCol0 = 10;
	int lenCol1 = 20;
	int lenCol2 = 20;
	int lenCol3 = 10;
	int lenCol4 = 10;
	int lenCol5 = 10;
	int lenCol6 = 10;
	gotoxy(x, y);
	cout << LT << setfill(TT) << setw(lenCol0) << TB << setfill(TT) << setw(lenCol1) << TB 
		<< setfill(TT) << setw(lenCol2) << TB << setfill(TT) << setw(lenCol3) << TB 
		<< setfill(TT) << setw(lenCol4) << TB << setfill(TT) << setw(lenCol5) << TB
		<< setfill(TT) << setw(lenCol6) << RT << endl; 
	y++;
	for(int i = 1; i <= row+1; i++) {
		gotoxy(x, y); y++;
		cout << DT << setfill(' ') << setw(lenCol0) << DT << setfill(' ') << setw(lenCol1) 
			<< DT << setfill(' ') << setw(lenCol2) <<  DT << setfill(' ') << setw(lenCol3) 
			<< DT << setfill(' ') << setw(lenCol4) << DT << setfill(' ') << setw(lenCol5) 
			<< DT << setfill(' ') << setw(lenCol6) << DT << endl;
		gotoxy(x, y); y++;
		cout << LL << setfill(TT) << setw(lenCol0) << CT << setfill(TT) << setw(lenCol1) 
			<< CT << setfill(TT) << setw(lenCol2) <<  CT << setfill(TT) << setw(lenCol3) 
			<< CT << setfill(TT) << setw(lenCol4) << CT << setfill(TT) << setw(lenCol5) 
			<< CT << setfill(TT) << setw(lenCol6) << RR << endl;
	}
	gotoxy(x, y); y++;
	cout << DT << setfill(' ') << setw(lenCol0) << DT << setfill(' ') << setw(lenCol1) 
		<< DT << setfill(' ') << setw(lenCol2) << DT << setfill(' ') << setw(lenCol3) 
		<< DT << setfill(' ') << setw(lenCol4) << DT << setfill(' ') << setw(lenCol5) 
		<< DT << setfill(' ') << setw(lenCol6)  << DT << endl;
	gotoxy(x, y);
	cout << LB << setfill(TT) << setw(lenCol0) << BT << setfill(TT) << setw(lenCol1) 
		<< BT << setfill(TT) << setw(lenCol2) << BT << setfill(TT) << setw(lenCol3) 
		<< BT << setfill(TT) << setw(lenCol4) << BT << setfill(TT) << setw(lenCol5) 
		<< BT << setfill(TT) << setw(lenCol6) << RB << endl;
}

void createTableDSSV(int x, int y, int row) {
	SetColor(11);
	int lenCol1 = 20;
	int lenCol2 = 20;
	int lenCol3 = 20;
	int lenCol4 = 20;
	int lenCol5 = 20;
	int lenCol6 = 20;
	gotoxy(x, y);
	cout << LT << setfill(TT) << setw(lenCol1) << TB << setfill(TT) << setw(lenCol2)
		<< TB << setfill(TT) << setw(lenCol3) << TB << setfill(TT) << setw(lenCol4)
		<< TB << setfill(TT) << setw(lenCol5) << TB << setfill(TT) << setw(lenCol6) << RT << endl; 
	y++;
	for(int i = 1; i <= row+1; i++) {
		gotoxy(x, y); y++;
		cout << DT << setfill(' ') << setw(lenCol1) << DT << setfill(' ') << setw(lenCol2)
			<<  DT << setfill(' ') << setw(lenCol3) << DT << setfill(' ') << setw(lenCol4)
			<< DT << setfill(' ') << setw(lenCol5)  << DT << setfill(' ') << setw(lenCol6) << DT << endl;
		gotoxy(x, y); y++;
		cout << LL << setfill(TT) << setw(lenCol1) << CT << setfill(TT) << setw(lenCol2) 
			<<  CT << setfill(TT) << setw(lenCol3) << CT << setfill(TT) << setw(lenCol4)
			<< CT << setfill(TT) << setw(lenCol5)  << CT << setfill(TT) << setw(lenCol6) << RR << endl;
	}
	gotoxy(x, y); y++;
	cout << DT << setfill(' ') << setw(lenCol1) << DT << setfill(' ') << setw(lenCol2)
		<< DT << setfill(' ') << setw(lenCol3) << DT << setfill(' ') << setw(lenCol4)
		<< DT << setfill(' ') << setw(lenCol5) << DT << setfill(' ') << setw(lenCol6) << DT << endl;
	gotoxy(x, y);
	cout << LB << setfill(TT) << setw(lenCol1) << BT << setfill(TT) << setw(lenCol2) 
		<< BT << setfill(TT) << setw(lenCol3) << BT << setfill(TT) << setw(lenCol4) 
		<< BT << setfill(TT) << setw(lenCol5) << BT << setfill(TT) << setw(lenCol6) << RB << endl;
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
	for(int i = 0; i < 100; i++) {
		arrRandom[i] = i+1;
	}
}

void generateSetOfNumbers() {  
  	int j,temp;
  	for (int i=100; i > 0; --i) {
  		srand (time(NULL));
	    j = rand() % i;
	    temp = arrRandom[i-1];
	    arrRandom[i-1] = arrRandom[j];
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

ifstream ifs;
void loadDataMonHoc() {
	ifs.open("monhoc.txt", ifstream::in);
	string line;
	string *s;
	while(getline(ifs, line)) {
		MonHoc mh;
		s = split(line+"\n", ",");
		strcpy(mh.maMH, s[0].c_str());
		strcpy(mh.tenMH, s[1].c_str());
		mh.STCLY = stoi(s[2]);
		mh.STCTH = stoi(s[3]);
		add(monhocs, arrRandom[keyMonhoc], mh);
		keyMonhoc++;
	}
}

string optionQLTC[] = {
	"1. Them Lop Tin Chi",
	"2. Sua Lop Tin Chi",
	"3. Xoa Lop Tin Chi",
	"4. Danh Sach Lop Tin Chi",
	"5. Danh Sach Sinh Vien Cua Mot Lop Tin Chi",
	"6. Quan Ly Sinh Vien Cua Lop Tin Chi",
	"7. Luu Vao File",
	"8. Quay Lai"
};

string titlesQLTC[] = {
	"QUAN LY LOP TIN CHI"
};

void printTitleTC(int width, int x) {
	int size = sizeof(titlesQLTC)/sizeof(titlesQLTC[0]);
	for(int i = 0; i < size; i++) {
		int len = titlesQLTC[i].length();
		gotoxy((x+width)/1.6 - len/2 , ROW_FRAME_TITLE + 2 + i);
		cout << titlesQLTC[i];
	}
}

void printTitleQLTC() {
	printFrame(75, 5, COLUMN_FRAME_TITLE, ROW_FRAME_TITLE, COLOR_SL);
	printTitleTC(75, COLUMN_FRAME_TITLE);	
}

int printOptionQLTC() {
	int choose = 0;
	printFrame(75, 15, COLUMN_FRAME_MENU, ROW_FRAME_MENU, COLOR_SL);
	int size = sizeof(optionQLTC)/sizeof(optionQLTC[0]);
	int col = COLUMN_FRAME_MENU + 20;
	int row = ROW_FRAME_MENU + 2;
	for(int i = 0; i < size; i++) {
		if(choose == i) {
			gotoxy(col, row + i);
			cout << optionQLTC[i];
		} else {
			SetColor(COLOR_DF);
			gotoxy(col, row + i);
			cout << optionQLTC[i];
		}
	}
	char c;
	while(true) {
		c = getch();
		if(c == UP && choose != 0) {
			SetColor(COLOR_DF);
			gotoxy(col, row + choose);
			cout << optionQLTC[choose--];
			SetColor(COLOR_SL);
			gotoxy(col, row + choose);
			cout << optionQLTC[choose];
		} else if (c == DOWN && choose != size - 1) {
			SetColor(COLOR_DF);
			gotoxy(col, row + choose);
			cout << optionQLTC[choose++];
			SetColor(COLOR_SL);
			gotoxy(col, row + choose);
			cout << optionQLTC[choose];
		} else if (c == ENTER) {
			return choose;
		}
	}
}

int arrNienKhoa[] = {
	2010,2011,2012,2013,2014,2015,2016,2017,
	2018,2019,2020,2021,2022,2023,2024,2025
};

bool isNiemKhoa(int nienKhoa) {
	int size = sizeof(arrNienKhoa)/sizeof(arrNienKhoa[0]);
	for(int i = 0; i < size; i++) {
		if(arrNienKhoa[i] == nienKhoa) 
			return true;
	}
	return false;
}

string arrHocKi[] = {
	"1", "2", "3", "hk1", "hk2", "hk3"
};

bool isHocKi(char hocKi[3]) {
	int size = sizeof(arrHocKi)/sizeof(arrHocKi[0]);
	for(int i = 0; i < size; i++) {
		if(arrHocKi[i] == hocKi ) return true;
	}
	return false;
}

int arrNhom[] = {
	1,2,3,4,5
};

bool isNhom(int nhom) {
	int size = sizeof(arrNhom)/sizeof(arrNhom[0]);
	for(int i = 0; i < size; i++) {
		if(arrNhom[i] == nhom ) return true;
	}
	return false;
}

bool isSvMax(int svmax, int svmin) {
	if(svmax > 300 || svmax < svmin) return false;
	return true;
}

bool isSvMin(int svmin) {
	if(svmin < 20 || svmin > 50) return false;
	return true;
}

int binarySearch(LopTC arr[], int l, int r, int maLop) {
    if (r >= l) {
        int mid = (r + l) / 2;
        if (arr[mid].maLop == maLop)
            return mid;
        if (arr[mid].maLop > maLop) return binarySearch(arr, l, mid - 1, maLop);
        if (arr[mid].maLop < maLop) return binarySearch(arr, mid + 1, r, maLop);
    }
    return -1;
}

bool findMaLTC(ArrayList<LopTC> &ltc, int malop) {
	int index = binarySearch(lopTinChis.array, 0 , lopTinChis.size - 1, malop);
	if(index>=0) return true;
	return false;
}



ofstream ofs_ltc;
void writeFileLopTinChi(ArrayList<LopTC> &ltc) {
	for(int i = 0, size = ltc.size; i < size; i++) {
		ofs_ltc << ltc.array[i].maLop << "," << ltc.array[i].maMH << "," << 
			ltc.array[i].niemKhoa << "," << ltc.array[i].hocKi<< "," << 
			ltc.array[i].nhom << "," << ltc.array[i].SvMin << "," << 
			ltc.array[i].SvMax << "," << ltc.array[i].huyLop << "\n";
	}
}

int maLop = 1;
ifstream ifs_ltc;
void loadDataLopTinChi() {
	ifs_ltc.open("loptinchi.txt", ifstream::in);
	string line;
	string *str;
	while(getline(ifs_ltc, line)) {
		LopTC ltc;
		str = split(line+"\n", ",");
		ltc.maLop = stoi(str[0]);
		maLop = stoi(str[0]);
		strcpy(ltc.maMH, str[1].c_str());
		ltc.niemKhoa = stoi(str[2]);
		strcpy(ltc.hocKi, str[3].c_str());
		ltc.nhom = stoi(str[4]);
		ltc.SvMin = stoi(str[5]);
		ltc.SvMax = stoi(str[6]);
		ltc.huyLop = stoi(str[7]);
		ltc.sv = new SinhVien[ltc.SvMax];
		add(lopTinChis, ltc);
	}
}

void printLopTC() {
	int row = 16;
	for(int i = 0, size = lopTinChis.size; i < size; i++) {
		gotoxy(13, row);
		cout << get(lopTinChis, i)->maLop;
		gotoxy(23, row);
		cout << get(lopTinChis, i)->maMH;
		gotoxy(43, row);
		cout << get(lopTinChis, i)->niemKhoa;
		gotoxy(63, row);
		cout << get(lopTinChis, i)->hocKi;
		gotoxy(73, row);
		cout << get(lopTinChis, i)->SvMin;
		gotoxy(83, row);
		cout << get(lopTinChis, i)->SvMax;
		gotoxy(93, row);
		cout << get(lopTinChis, i)->nhom;
		row+=2;
	}
}

void printDSSV_LTC() {
	int row = 16;
	for(int i = 0, size = lopTinChis.size; i < size; i++) {
		gotoxy(23, row);
		cout << get(lopTinChis, i)->maMH;
		gotoxy(43, row);
		cout << get(lopTinChis, i)->niemKhoa;
		gotoxy(63, row);
		cout << get(lopTinChis, i)->hocKi;
		gotoxy(73, row);
		cout << get(lopTinChis, i)->SvMin;
		gotoxy(83, row);
		cout << get(lopTinChis, i)->SvMax;
		row+=2;
	}
}

bool checkMaLTC(ArrayList<LopTC> &ltc, int maTC) {

}

bool enterMaMH(LopTC &ltc) {
	do {
		gotoxy(51, 15);	
		cout << "                             ";
		gotoxy(51, 15);	
		gets(ltc.maMH);	
		int key = searchKeyMaMH(ltc.maMH);
		if(strcmp(ltc.maMH,"") == 0) return true;
		if(key != -1) {			
			break;
		} else {
			gotoxy(45, 13);	
			cout << "khong tim thay ma mon hoc";
			Sleep(1000);
			gotoxy(45, 13);	
			cout << "                           ";
		}
	} while (true);
}

void enterNiemKhoa(LopTC &ltc, int row) {
	do {
		string s_niemKhoa;
		gotoxy(51, row);	
		cout << "                             ";
		gotoxy(51, row);
		getline(cin, s_niemKhoa);
		try {
	        ltc.niemKhoa = stoi(s_niemKhoa);
	        if(isNiemKhoa(ltc.niemKhoa)) {
				break;
			} else {
				gotoxy(45, 11);	
				cout << "Niem Khoa Khong Hop Le";
				Sleep(1000);
				gotoxy(45, 11);	
				cout << "                           ";
			}	
	    } catch(invalid_argument e) {
	        gotoxy(45, 11);	
			cout << "Niem Khoa Khong Hop Le";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                           ";
	    }
		
	} while (true);
}

void enterHocKi(LopTC &ltc, int row) {
	do {
		string s_hocki;
		gotoxy(51, row);	
		cout << "                             ";
		gotoxy(51, row);
		getline(cin, s_hocki);
		if(s_hocki.length() <= 3) {
			strcpy(ltc.hocKi, s_hocki.c_str());
		} else {
			gotoxy(45, 11);	
			cout << "Hoc Ki Khong Hop Le";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                           ";
			continue;	
		}
		if(isHocKi(ltc.hocKi)) {
			break;
		} else {
			gotoxy(45, 11);	
			cout << "Hoc Ki Khong Hop Le";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                           ";
		}
		
	} while (true);
}

void enterNhom(LopTC &ltc, int row) {
	do {
		string s_nhom;
		gotoxy(51, row);	
		cout << "                             ";
		gotoxy(51, row);
		getline(cin, s_nhom);
		try {
	        ltc.nhom = stoi(s_nhom);
	        if(isNhom(ltc.nhom)) {
				break;
			} else {
				gotoxy(45, 11);	
				cout << "Nhom Khong Hop Le";
				Sleep(1000);
				gotoxy(45, 11);	
				cout << "                           ";
			}	
	    } catch(invalid_argument e) {
	        gotoxy(45, 11);	
			cout << "Nhom Khong Hop Le";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                           ";
	    }
						
	} while (true);
}

void enterSVMin(LopTC &ltc, int row) {
	do {
		string s_svMin;
		gotoxy(51, row);	
		cout << "                             ";
		gotoxy(51, row);
		getline(cin, s_svMin);
		try {
	        ltc.SvMin = stoi(s_svMin);
	        if(isSvMin(ltc.SvMin)) {
	        	break;
			} else {
				gotoxy(45, 11);	
				cout << "Sinh Vien Min Khong Hop Le";
				Sleep(1000);
				gotoxy(45, 11);	
				cout << "                           ";	
			}
	    } catch(invalid_argument e) {
	        gotoxy(45, 11);	
			cout << "Sinh Vien Min Khong Hop Le";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                           ";
	    }				
	} while (true);
}

void enterSVMax(LopTC &ltc, int row) {
	do {
		string s_svMax;
		gotoxy(51, row);	
		cout << "                             ";
		gotoxy(51, row);
		getline(cin, s_svMax);
		try {
	        ltc.SvMax = stoi(s_svMax);
	        if(isSvMax(ltc.SvMax, ltc.SvMin)) {
	        	break;
			} else {
				gotoxy(45, 11);	
				cout << "Sinh Vien Max Khong Hop Le";
				Sleep(1000);
				gotoxy(45, 11);	
				cout << "                           ";	
			}
	    } catch(invalid_argument e) {
	        gotoxy(45, 11);	
			cout << "Sinh Vien Max Khong Hop Le";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                           ";
	    }				
	} while (true);
}

void processQLTC() {
	int choose;
	int size = sizeof(optionQLTC)/sizeof(optionQLTC[0]);
	do {
		generateKey(monhocs.root);
		system("cls");
		printTitleQLTC();
		choose = printOptionQLTC();
		switch(choose) {
			
			case 0: {
				system("cls");
				printTitleQLTC();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 2, 6);
				gotoxy(31, 15);
				cout << "Ma Mon Hoc";
				gotoxy(31, 17);
				cout << "Nien Khoa";
				gotoxy(31, 19);
				cout << "Hoc Ky";
				gotoxy(31, 21);
				cout << "Nhom";
				gotoxy(31, 23);
				cout << "Sinh Vien Min";
				gotoxy(31, 25);
				cout << "Sinh Vien Max";
							
				LopTC ltc;
				bool exit = false;
				
				exit = enterMaMH(ltc);
				if(!exit) {
					enterNiemKhoa(ltc, 17);
					enterHocKi(ltc, 19);
					enterNhom(ltc, 21);
					enterSVMin(ltc, 23);
					enterSVMax(ltc, 25);
					ltc.maLop = ++maLop; // default value malop = 1
					ltc.huyLop = false;
					ltc.sv = new SinhVien[ltc.SvMax];
					add(lopTinChis, ltc);
					gotoxy(51, 35);	
				}
				break;
			}
			
			case 1: {
				system("cls");
				printTitleQLTC();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 1);
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 4, 6);
				gotoxy(31, 17);
				cout << "Ma Mon Hoc";
				gotoxy(31, 19);
				cout << "Nien Khoa";
				gotoxy(31, 21);
				cout << "Hoc Ky";
				gotoxy(31, 23);
				cout << "Nhom";
				gotoxy(31, 25);
				cout << "Sinh Vien Min";
				gotoxy(31, 27);
				cout << "Sinh Vien Max";
				
				
				int maLopTC;
				gotoxy(31, 13);
				cout << "Nhap Ma Lop Tin Chi";
				do {
					gotoxy(51, 13);	
					cout << "                             ";
					gotoxy(51, 13);
					cin >> maLopTC;
					fflush(stdin);
					if(maLopTC == 0 || findMaLTC(lopTinChis, maLopTC)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Khong Tim Thay Lop Tin Chi";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                             ";
					}					
				} while (true);
				
				if(maLopTC == 0) break;
		
				int index = binarySearch(lopTinChis.array, 0 , lopTinChis.size - 1, maLopTC);
				LopTC *ltc = get(lopTinChis, index);
				gotoxy(51, 17);
				cout << ltc->maMH;
				gotoxy(51, 19);
				cout << ltc->niemKhoa;
				gotoxy(51, 21);
				cout << ltc->hocKi;
				gotoxy(51, 23);
				cout << ltc->nhom;
				gotoxy(51, 25);
				cout << ltc->SvMin;
				gotoxy(51, 27);
				cout << ltc->SvMax;
				Sleep(1000);
				
				do {
					gotoxy(51, 17);	
					cout << "                             ";
					gotoxy(51, 17);	
					gets(ltc->maMH);	
					int key = searchKeyMaMH(ltc->maMH);
					if(key != -1 && strcmp(ltc->maMH,"") != 0) {			
						break;
					} else {
						gotoxy(45, 11);	
						cout << "khong tim thay ma mon hoc";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
					}
				} while (true);
				
				enterNiemKhoa(*ltc, 19);
				enterHocKi(*ltc, 21);
				enterNhom(*ltc, 23);	
				enterSVMin(*ltc, 25);
				enterSVMax(*ltc, 27);
				break;
			}
			
			case 2: {
				system("cls");
				printTitleQLTC();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 1);
				int maLopTC;
				gotoxy(31, 13);
				cout << "Nhap Ma Lop Tin Chi";
				do {
					gotoxy(51, 13);	
					cout << "                             ";
					gotoxy(51, 13);
					cin >> maLopTC;
					fflush(stdin);
					if(maLopTC == 0 || findMaLTC(lopTinChis, maLopTC)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Khong Tim Thay Lop Tin Chi";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                             ";
					}					
				} while (true);
				
				if(maLopTC == 0) break;
		
				int index = binarySearch(lopTinChis.array, 0 , lopTinChis.size - 1, maLopTC);
				remove(lopTinChis, index);
				gotoxy(45, 11);	
				cout << "Xoa Thanh Cong";
				Sleep(1000);
				break;
			}
			
			case 3: {
				system("cls");
				printTitleQLTC();
				createTableLTC(COLUMN_FRAME_MENU - 8, ROW_FRAME_MENU + 1, lopTinChis.size);
				gotoxy(13, 14);	
				cout << "Ma Lop TC";
				gotoxy(23, 14);	
				cout << "Ma Mon Hoc";
				gotoxy(43, 14);	
				cout << "Niem Khoa";
				gotoxy(63, 14);	
				cout << "Hoc Ky";
				gotoxy(73, 14);	
				cout << "Sv Min";
				gotoxy(83, 14);	
				cout << "Sv Max";
				gotoxy(93, 14);	
				cout << "Nhom";
				printLopTC();
				getch();
				break;
			}
			
			case 4: {
				system("cls");
				printTitleQLTC();
				createTableDSSV(COLUMN_FRAME_MENU -10, ROW_FRAME_MENU + 1, 10);
				gotoxy(11, 14);	
				cout << "Ma Sinh Vien";
				gotoxy(31, 14);	
				cout << "Ho";
				gotoxy(51, 14);	
				cout << "Ten";
				gotoxy(71, 14);	
				cout << "Phai";
				gotoxy(91, 14);	
				cout << "So Dien Thoai";
				gotoxy(111, 14);	
				cout << "Ma Lop";
				Sleep(1000);
				break;
			}
			
			case 5: {
				system("cls");
				printTitleQLTC();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 1);
				gotoxy(31, 13);
				cout << "Nhap Ma Lop Tin Chi";
				
				int maLTC;
				do {
					gotoxy(51,13);
					cin >> maLTC;
					
				} while(true);
				
				
				getch();
				break;
			}
			
			case 6: {
				ofs_ltc.open("loptinchi.txt", ofstream::out);
				writeFileLopTinChi(lopTinChis);
				ofs_ltc.close();
				gotoxy(45, 10);
				cout << "Luu Thanh Cong";
				Sleep(1000);
				gotoxy(45, 10);
				cout << "               ";
				break;
			}
		
		}
	} while (choose != size - 1);
}

string optionQLSV[] = {
	"1 Them Sinh Vien",
	"2 Sua Sinh Vien",
	"3 Xoa Sinh Vien",
	"4 Danh Sach Sinh Vien",
	"5 Luu Vao File",
	"6 Quay Lai"
};

string titlesQLSV[] = {
	"QUAN LY SINH VIEN"
};


void printTitleSV(int width, int x) {
	int size = sizeof(titlesQLSV)/sizeof(titlesQLSV[0]);
	for(int i = 0; i < size; i++) {
		int len = titlesQLSV[i].length();
		gotoxy((x+width)/1.6 - len/2 , ROW_FRAME_TITLE + 2 + i);
		cout << titlesQLSV[i];
	}
}

void printTitleQLSV() {
	printFrame(75, 5, COLUMN_FRAME_TITLE, ROW_FRAME_TITLE, COLOR_SL);
	printTitleSV(75, COLUMN_FRAME_TITLE);	
}

void processQLSV() {
	int choose;
	int size = sizeof(optionQLSV)/sizeof(optionQLSV[0]);
	do {
		generateKey(monhocs.root);
		system("cls");
		printTitleQLSV();
		choose = printOptionQLTC();
		switch(choose) {
			
			case 0: {
				system("cls");
				printTitleQLTC();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 2, 6);
				gotoxy(31, 15);
				cout << "Ma Mon Hoc";
				gotoxy(31, 17);
				cout << "Nien Khoa";
				gotoxy(31, 19);
				cout << "Hoc Ky";
				gotoxy(31, 21);
				cout << "Nhom";
				gotoxy(31, 23);
				cout << "Sinh Vien Min";
				gotoxy(31, 25);
				cout << "Sinh Vien Max";
							
				LopTC ltc;
				bool exit = false;
				
				do {
					gotoxy(51, 15);	
					cout << "                             ";
					gotoxy(51, 15);	
					gets(ltc.maMH);	
					int key = searchKeyMaMH(ltc.maMH);
					if(strcmp(ltc.maMH,"") == 0) exit = true;
					if(key != -1) {			
						break;
					} else {
						gotoxy(45, 13);	
						cout << "khong tim thay ma mon hoc";
						Sleep(1000);
						gotoxy(45, 13);	
						cout << "                           ";
					}
				} while (true);
				
				do {
					if(exit) break;
					gotoxy(51, 17);	
					cout << "                             ";
					gotoxy(51, 17);
					cin >> ltc.niemKhoa;
					fflush(stdin);
					if(isNiemKhoa(ltc.niemKhoa)) {
						break;
					} else {
						gotoxy(45, 13);	
						cout << "Niem Khoa Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 13);	
						cout << "                           ";
					}
				} while (true);
				
				do {
					if(exit) break;
					gotoxy(51, 19);	
					cout << "                             ";
					gotoxy(51, 19);
					gets(ltc.hocKi);
					if(isHocKi(ltc.hocKi)) {
						break;
					} else {
						gotoxy(45, 13);	
						cout << "Hoc Ki Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 13);	
						cout << "                           ";
					}
					
				} while (true);
				
				do {
					if(exit) break;
					gotoxy(51, 21);	
					cout << "                             ";
					gotoxy(51, 21);
					cin >> ltc.nhom;
					if(isNhom(ltc.nhom)) {
						break;
					} else {
						gotoxy(45, 13);	
						cout << "Nhom Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 13);	
						cout << "                           ";
					}					
				} while (true);
				
				do {
					if(exit) break;
					gotoxy(51, 23);	
					cout << "                             ";
					gotoxy(51, 23);
					cin >> ltc.SvMin;
					fflush(stdin);
					if(isSvMin(ltc.SvMin)) {
						break;
					} else {
						gotoxy(45, 13);	
						cout << "Sinh Vien Min Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 13);	
						cout << "                           ";
					}					
				} while (true);
				
				do {
					if(exit) break;
					gotoxy(51, 25);	
					cout << "                             ";
					gotoxy(51, 25);
					cin >> ltc.SvMax;
					fflush(stdin);
					if(isSvMax(ltc.SvMax, ltc.SvMin)) {
						break;
					} else {
						gotoxy(45, 13);	
						cout << "Sinh Vien Max Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 13);	
						cout << "                           ";
					}					
				} while (true);
				ltc.maLop = maLop++;
				ltc.huyLop = false;
				ltc.sv = new SinhVien[ltc.SvMax];
				add(lopTinChis, ltc);
				gotoxy(51, 35);
				break;
			}
			
			case 1: {
				system("cls");
				printTitleQLTC();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 1);
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 4, 6);
				gotoxy(31, 17);
				cout << "Ma Mon Hoc";
				gotoxy(31, 19);
				cout << "Nien Khoa";
				gotoxy(31, 21);
				cout << "Hoc Ky";
				gotoxy(31, 23);
				cout << "Nhom";
				gotoxy(31, 25);
				cout << "Sinh Vien Min";
				gotoxy(31, 27);
				cout << "Sinh Vien Max";
				
				
				int maLopTC;
				gotoxy(31, 13);
				cout << "Nhap Ma Lop Tin Chi";
				do {
					gotoxy(51, 13);	
					cout << "                             ";
					gotoxy(51, 13);
					cin >> maLopTC;
					fflush(stdin);
					if(maLopTC == 0 || findMaLTC(lopTinChis, maLopTC)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Khong Tim Thay Lop Tin Chi";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                             ";
					}					
				} while (true);
				
				if(maLopTC == 0) break;
		
				int index = binarySearch(lopTinChis.array, 0 , lopTinChis.size - 1, maLopTC);
				LopTC *ltc = get(lopTinChis, index);
				gotoxy(51, 17);
				cout << ltc->maMH;
				gotoxy(51, 19);
				cout << ltc->niemKhoa;
				gotoxy(51, 21);
				cout << ltc->hocKi;
				gotoxy(51, 23);
				cout << ltc->nhom;
				gotoxy(51, 25);
				cout << ltc->SvMin;
				gotoxy(51, 27);
				cout << ltc->SvMax;
				Sleep(1000);
				
				do {
					gotoxy(51, 17);	
					cout << "                             ";
					gotoxy(51, 17);	
					gets(ltc->maMH);	
					int key = searchKeyMaMH(ltc->maMH);
					if(key != -1 && strcmp(ltc->maMH,"") != 0) {			
						break;
					} else {
						gotoxy(45, 11);	
						cout << "khong tim thay ma mon hoc";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
					}
				} while (true);
				
				do {
					gotoxy(51, 19);	
					cout << "                             ";
					gotoxy(51, 19);
					cin >> ltc->niemKhoa;
					fflush(stdin);
					if(isNiemKhoa(ltc->niemKhoa)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Niem Khoa Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
					}
				} while (true);
				
				do {
					gotoxy(51, 21);	
					cout << "                             ";
					gotoxy(51, 21);
					gets(ltc->hocKi);
					if(isHocKi(ltc->hocKi)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Hoc Ki Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
					}					
				} while (true);
				
				do {
					gotoxy(51, 23);	
					cout << "                             ";
					gotoxy(51, 23);
					cin >> ltc->nhom;
					if(isNhom(ltc->nhom)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Nhom Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
					}					
				} while (true);
				
				do {
					gotoxy(51, 25);	
					cout << "                             ";
					gotoxy(51, 25);
					cin >> ltc->SvMin;
					fflush(stdin);
					if(isSvMin(ltc->SvMin)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Sinh Vien Min Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
					}					
				} while (true);
				
				do {
					gotoxy(51, 27);	
					cout << "                             ";
					gotoxy(51, 27);
					cin >> ltc->SvMax;
					fflush(stdin);
					if(isSvMax(ltc->SvMax, ltc->SvMin)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Sinh Vien Max Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
					}					
				} while (true);
				break;
			}
			
			case 2: {
				system("cls");
				printTitleQLTC();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 1);
				int maLopTC;
				gotoxy(31, 13);
				cout << "Nhap Ma Lop Tin Chi";
				do {
					gotoxy(51, 13);	
					cout << "                             ";
					gotoxy(51, 13);
					cin >> maLopTC;
					fflush(stdin);
					if(maLopTC == 0 || findMaLTC(lopTinChis, maLopTC)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Khong Tim Thay Lop Tin Chi";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                             ";
					}					
				} while (true);
				
				if(maLopTC == 0) break;
		
				int index = binarySearch(lopTinChis.array, 0 , lopTinChis.size - 1, maLopTC);
				remove(lopTinChis, index);
				gotoxy(45, 11);	
				cout << "Xoa Thanh Cong";
				Sleep(1000);
				break;
			}
			
			case 3: {
				system("cls");
				printTitleQLTC();
				createTableLTC(COLUMN_FRAME_MENU + 2, ROW_FRAME_MENU + 1, lopTinChis.size);
				gotoxy(23, 14);	
				cout << "Ma Mon Hoc";
				gotoxy(43, 14);	
				cout << "Niem Khoa";
				gotoxy(63, 14);	
				cout << "Hoc Ky";
				gotoxy(73, 14);	
				cout << "Sv Min";
				gotoxy(83, 14);	
				cout << "Sv Max";
				printLopTC();
				getch();
				break;
			}	
			
			case 4: {
				ofs_ltc.open("loptinchi.txt", ofstream::out);
				writeFileLopTinChi(lopTinChis);
				ofs_ltc.close();
				gotoxy(45, 10);
				cout << "Luu Thanh Cong";
				Sleep(1000);
				gotoxy(45, 10);
				cout << "               ";
				break;
			}
		
		}
	} while (choose != size - 1);
}

int main() {
	randomNumber();
	generateSetOfNumbers();
	newBinarySearchTree(monhocs);
	newArrayList(lopTinChis, MAX_LTC);
	loadDataMonHoc();
	loadDataLopTinChi();
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
				processQLTC();
				break;
			case 2:
				processQLSV();
				break;
			case 3:
				gotoxy(COLUMN_RS,ROW_RS);
				exit(0);
				break;
		}
	} while (true);
	gotoxy(20,30);
	return 0;
}
