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


int getIndexMaSV(char maSV[15]);
bool findMaSV(char maSV[15]);
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
	string phai;
//	char sdt[10];
	string sdt;
	char maLop[15];
};

struct DangKy {
	char maSV[15];
	float diem;
	int maLop;
};



template <typename T>
struct ArrayList {
	int member;
	int size;
	T *array;
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
	ArrayList<SinhVien> sv;
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

void writeFileDK(LinkedList<DangKy> &dk);

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
T *get(LinkedList<T> &linkedlist, int index) {
	Node<T> *temp = new Node<T>;
	temp = linkedlist.head;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return &temp->data;
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

ofstream ofs_dk;

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
LinkedList<SinhVien> sinhviens;
LinkedList<DangKy> dangkys;

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
    MonHoc pivot = arr[high];
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

void bubbleSort(MonHoc *mh, int size) {
	for(int i = 0; i < size - 1; i++) {
		for(int j = i + 1; j < size; j++) {
			if(strcasecmp(mh[i].tenMH, mh[j].maMH) > 0) {
				swap(mh[i], mh[j]);
			}
		}
	}
}

void printMonHoc(MonHoc *mh) {
//	quickSort(BtsToArray, 0, indexArrayBST);
	bubbleSort(mh, indexArrayBST);
	rowMonhoc+=2;
	for (int i = 0; i < indexArrayBST; i++) {
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

bool enterMaMH(MonHoc &mh, int row) {
	do {
		string s_maMh;
		gotoxy(51, row);
		cout << "                            ";
		gotoxy(51, row);				
		getline(cin, s_maMh);
		if(s_maMh == "") return true;
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
	return false;
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

void clearMH() {
	gotoxy(51, 15);
	cout << "                ";
	gotoxy(51, 17);
	cout << "                ";
	gotoxy(51, 19);
	cout << "                ";
	gotoxy(51, 21);
	cout << "                ";
}

void processQLMH() {
	
	int choose;
	int size = sizeof(optionQLMH)/sizeof(optionQLMH[0]);
	do {
		
		indexArrayBST = 0;
		generateKey(monhocs.root);
		balanceBST(monhocs.root, BtsToArray, 0, indexArrayBST - 1);
		rowMonhoc = 14;    
		sizeMonhoc = 0;
		getSizeMonHoc(monhocs.root);
		
		system("cls");
		printTitleQLMH();
		choose = printOptionQLMH();
		switch(choose) {
			
			case 0: {   // Them MH
				system("cls");
				printTitleQLMH();
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
				bool exit = false;
				do {
					exit = enterMaMH(mh, 15); if(exit) break;
					enterTenMH(mh, 17);
					enterSTCLT(mh, 19);
					enterSTCTH(mh, 21);	
					add(monhocs, arrRandom[keyMonhoc], mh);
					keyMonhoc++;
					
					generateKey(monhocs.root);
					gotoxy(45, 10);
					cout << "Them Thanh Cong";
					Sleep(1000);
					gotoxy(45, 10);
					cout << "               "; 
					clearMH();
				} while (!exit);
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
				gotoxy(24, 14 );
				cout << "MA MON HOC" << endl;
				gotoxy(44, 14);
				cout << "TEN MON HOC" << endl;
				gotoxy(74, 14 );
				cout << "STCLT" << endl;
				gotoxy(84, 14);
				cout << "STCTH" << endl;
				gotoxy(94, 14);
				printMonHoc(BtsToArray);
				getch();
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
	printFrame(75, 12, COLUMN_FRAME_MENU, ROW_FRAME_MENU, COLOR_SL);
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

void createTableBangDiem(int x, int y, int row) {
	SetColor(11);
	int lenCol1 = 20;
	int lenCol2 = 20;
	int lenCol3 = 20;
	int lenCol4 = 20;
	int lenCol5 = 20;
	gotoxy(x, y);
	cout << LT << setfill(TT) << setw(lenCol1) << TB << setfill(TT) << setw(lenCol2)
		<< TB << setfill(TT) << setw(lenCol3) << TB << setfill(TT) << setw(lenCol4)
		<< TB << setfill(TT) << setw(lenCol5)  << RT << endl; 
	y++;
	for(int i = 1; i <= row+1; i++) {
		gotoxy(x, y); y++;
		cout << DT << setfill(' ') << setw(lenCol1) << DT << setfill(' ') << setw(lenCol2)
			<<  DT << setfill(' ') << setw(lenCol3) << DT << setfill(' ') << setw(lenCol4)
			<< DT << setfill(' ') << setw(lenCol5)   << DT << endl;
		gotoxy(x, y); y++;
		cout << LL << setfill(TT) << setw(lenCol1) << CT << setfill(TT) << setw(lenCol2) 
			<<  CT << setfill(TT) << setw(lenCol3) << CT << setfill(TT) << setw(lenCol4)
			<< CT << setfill(TT) << setw(lenCol5)   << RR << endl;
	}
	gotoxy(x, y); y++;
	cout << DT << setfill(' ') << setw(lenCol1) << DT << setfill(' ') << setw(lenCol2)
		<< DT << setfill(' ') << setw(lenCol3) << DT << setfill(' ') << setw(lenCol4)
		<< DT << setfill(' ') << setw(lenCol5)  << DT << endl;
	gotoxy(x, y);
	cout << LB << setfill(TT) << setw(lenCol1) << BT << setfill(TT) << setw(lenCol2) 
		<< BT << setfill(TT) << setw(lenCol3) << BT << setfill(TT) << setw(lenCol4) 
		<< BT << setfill(TT) << setw(lenCol5)  << RB << endl;
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

ifstream ifs_dk;
void loadDataDangKy() {
	ifs_dk.open("dangky.txt", ifstream::in);
	string line;
	string *s;
	while(getline(ifs_dk, line)) {
		DangKy dk;
		s = split(line+"\n", ",");
		strcpy(dk.maSV, s[0].c_str());
		dk.diem = stof(s[1]);
		dk.maLop = stof(s[2]);
		add(dangkys, dk);
	}
}

string optionQLTC[] = {
	"1. Them Lop Tin Chi",
	"2. Sua Lop Tin Chi",
	"3. Xoa Lop Tin Chi",
	"4. Danh Sach Lop Tin Chi",
	"5. Danh Sach Sinh Vien Cua Mot Lop Tin Chi",
	"6. Quan Ly Sinh Vien Cua Lop Tin Chi",
	"7. Nhap Diem",
	"8. In Bang Diem",
	"9. Luu Vao File",
	"10. Quay Lai"
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
	"hk1", "hk2", "hk3"
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
			ltc.array[i].SvMax << "," << ltc.array[i].huyLop << "," << ltc.array[i].sv.size << "\n";
			for(int j = 0, size = ltc.array[i].sv.size; j < size; j++) {
				SinhVien *sv = get(ltc.array[i].sv, j);
				ofs_ltc << sv->maSV << "," << sv->ho << "," << sv->ten << "," <<
					sv->phai << "," << sv->sdt << "," << sv->maLop ;
			}
	}
}

int maLop = 1;
ifstream ifs_ltc;
void loadDataLopTinChi() {
	ifs_ltc.open("loptinchi.txt", ifstream::in);
	string line;
	string *str;
	string *sv;
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
		newArrayList(ltc.sv, ltc.SvMax);
		for(int i = 0, size = stoi(str[8]); i < size; i++) {
			if(getline(ifs_ltc, line)) {
				sv = split(line+"\n", ",");
				SinhVien t;
				strcpy(t.maSV, sv[0].c_str());
				strcpy(t.ho, sv[1].c_str());
				strcpy(t.ten, sv[2].c_str());
				t.phai = sv[3];
				t.sdt = sv[4];
				strcpy(t.maLop, sv[5].c_str());
				add(ltc.sv, t);	
			}
			
		}
		
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

bool enterMaMH(LopTC &ltc, int row) {
	do {
		gotoxy(51, row);	
		cout << "                             ";
		gotoxy(51, row);	
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
	return false;
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

bool checkExitsLTC(LopTC &ltc) {
	for(int i = 0, size = lopTinChis.size; i < size; i++) {
		LopTC *temp = get(lopTinChis, i);
		if(strcmp(temp->maMH, ltc.maMH) == 0 &&
			temp->niemKhoa == ltc.niemKhoa &&
			strcmp(temp->hocKi, ltc.hocKi) == 0 &&
			temp->nhom == ltc.nhom ) {
			
			return true;	
		} 
	}
	return false;
}

LopTC *getExitsLTC(LopTC &ltc) {
	for(int i = 0, size = lopTinChis.size; i < size; i++) {
		LopTC *temp = get(lopTinChis, i);
		if(strcmp(temp->maMH, ltc.maMH) == 0 &&
			temp->niemKhoa == ltc.niemKhoa &&
			strcmp(temp->hocKi, ltc.hocKi) == 0 &&
			temp->nhom == ltc.nhom ) {
			
			return temp;	
		} 
	}
	return NULL;
}

void clearLTC() {
	gotoxy(51, 17);
	cout << "                   ";
	gotoxy(51, 19);
	cout << "                   ";
	gotoxy(51, 21);
	cout << "                   ";
	gotoxy(51, 23);
	cout << "                   ";
	gotoxy(51, 25);
	cout << "                   ";
}

string options_SV_LTC[] = {
		"1. Them Sinh Vien Vao Lop Tin Chi",
		"2. Xoa Sinh Vien Cua Lop Tin Chi",
		"3. Quay lai"
	};

int printOption_SV_LTC() {
	int choose = 0;
	printFrame(75, 7, COLUMN_FRAME_MENU, ROW_FRAME_MENU + 5, COLOR_SL);
	
	int size = sizeof(options_SV_LTC)/sizeof(options_SV_LTC[0]);
	int col = COLUMN_FRAME_MENU + 20;
	int row = ROW_FRAME_MENU + 7;
	for(int i = 0; i < size; i++) {
		if(choose == i) {
			gotoxy(col, row + i);
			cout << options_SV_LTC[i];
		} else {
			SetColor(COLOR_DF);
			gotoxy(col, row + i);
			cout << options_SV_LTC[i];
		}
	}
	char c;
	while(true) {
		c = getch();
		if(c == UP && choose != 0) {
			SetColor(COLOR_DF);
			gotoxy(col, row + choose);
			cout << options_SV_LTC[choose--];
			SetColor(COLOR_SL);
			gotoxy(col, row + choose);
			cout << options_SV_LTC[choose];
		} else if (c == DOWN && choose != size - 1) {
			SetColor(COLOR_DF);
			gotoxy(col, row + choose);
			cout << options_SV_LTC[choose++];
			SetColor(COLOR_SL);
			gotoxy(col, row + choose);
			cout << options_SV_LTC[choose];
		} else if (c == ENTER) {
			return choose;	
		}
	}	
}

void addDK() {
	for(int i = 0, size = lopTinChis.size; i < size; i++) {
		
		LopTC *ltc = get(lopTinChis, i);
		for(int j = 0, size2 = ltc->sv.size; j < size2; j++) {
			DangKy dk;
			SinhVien *sv = get(ltc->sv, j);
			strcpy(dk.maSV, sv->maSV);
			dk.maLop = ltc->maLop;
			dk.diem = 0;
			add(dangkys, dk);
		}
		
	}
	
//	for(int j = 0, size = dangkys.size; j < size; j++) {
//			DangKy *dk = get(dangkys, j);
//			cout << dk->maLop << " | masv " << dk->maSV << " | diem " << dk->diem << "\n";
//	}
//	getch();	
}

void printTitleBangDiem() {
	printFrame(75, 5, COLUMN_FRAME_TITLE, ROW_FRAME_TITLE, COLOR_SL);
	string op[] = {
		"BANG DIEM MON HOC" ,
		"Nien khoa  :        Hoc ky :        Nhom :      "
		
	};
	int size = sizeof(op)/sizeof(op[0]);
	for(int i = 0; i < size; i++) {
		int len = op[i].length();
		gotoxy((20+75)/1.6 - len/2 , ROW_FRAME_TITLE + 2 + i);
		cout << op[i];
	}
}


void processQLTC() {
	int choose;
	int size = sizeof(optionQLTC)/sizeof(optionQLTC[0]);
//	addDK();
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
				do {
					exit = enterMaMH(ltc, 15);
					if(!exit) {
						enterNiemKhoa(ltc, 17);
						enterHocKi(ltc, 19);
						enterNhom(ltc, 21);
						enterSVMin(ltc, 23);
						enterSVMax(ltc, 25);
						ltc.maLop = ++maLop;
						ltc.huyLop = false;
						newArrayList(ltc.sv, ltc.SvMax);
						if(checkExitsLTC(ltc)) {
							gotoxy(51, 11);	
							cout << "LTC Da Ton Tai";
							Sleep(1000);	
							gotoxy(51, 11);	
							cout << "                  ";
							clearLTC();	
						} else {
							gotoxy(51, 11);	
							cout << "Them Thanh Cong";
							Sleep(1000);
							gotoxy(51, 11);	
							cout << "               ";
							clearLTC();
							add(lopTinChis, ltc);
						}
												
					}
					fflush(stdin);
				} while (!exit);
				
				break;
			}
			
			case 1: { // sua ltc
				
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
				
				
				string maLopTC;
				int maLoptc;
				gotoxy(31, 13);
				cout << "Nhap Ma Lop Tin Chi";
				do {
					gotoxy(51, 13);	
					cout << "                             ";
					gotoxy(51, 13);
					getline(cin, maLopTC);
					if(maLopTC == "") break;
					try {
				        maLoptc = stoi(maLopTC);
				        if(maLoptc == 0 || findMaLTC(lopTinChis, maLoptc)) {
						break;
						} else {
							gotoxy(45, 11);	
							cout << "Khong Tim Thay Lop Tin Chi";
							Sleep(1000);
							gotoxy(45, 11);	
							cout << "                             ";
						}
				    } catch(invalid_argument e) {
				        gotoxy(45, 11);	
						cout << "Ma Lop Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
				    }
					fflush(stdin);					
				} while (true);
				
				if(maLoptc == 0 || maLopTC == "") break;
		
				int index = binarySearch(lopTinChis.array, 0 , lopTinChis.size - 1, maLoptc);
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
				LopTC *temp = new LopTC;
				
				do {
					do {
						gotoxy(51, 17);	
						cout << "                             ";
						gotoxy(51, 17);	
						gets(temp->maMH);	
						int key = searchKeyMaMH(temp->maMH);
						if(key != -1 && strcmp(temp->maMH,"") != 0) {			
							break;
						} else {
							gotoxy(45, 11);	
							cout << "khong tim thay ma mon hoc";
							Sleep(1000);
							gotoxy(45, 11);	
							cout << "                           ";
						}
					} while (true);
					
					enterNiemKhoa(*temp, 19);
					enterHocKi(*temp, 21);
					enterNhom(*temp, 23);	
					enterSVMin(*temp, 25);
					enterSVMax(*temp, 27);
					if(checkExitsLTC(*temp)) {
						gotoxy(45, 11);	
						cout << "LTC trung";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
					} else {
						strcpy(ltc->maMH, temp->maMH);
						ltc->niemKhoa = temp->niemKhoa;
						strcpy(ltc->hocKi, temp->hocKi);
						ltc->nhom = temp->nhom;
						ltc->SvMin = temp->SvMin;
						ltc->SvMax = temp->SvMax;
						break;	
					}
				} while (true);
				
				break;
			}
			
			case 2: {
				system("cls");
				printTitleQLTC();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 1);
				
				string s_maLop;
				int maLopTC;
				gotoxy(31, 13);
				cout << "Nhap Ma Lop Tin Chi";
				do {
					gotoxy(51, 13);	
					cout << "                             ";
					gotoxy(51, 13);
					getline(cin, s_maLop);
					if(s_maLop == "") break;
					try {
				        maLopTC = stoi(s_maLop);
				        if(maLopTC == 0 || findMaLTC(lopTinChis, maLopTC)) {
							break;
						} else {
							gotoxy(45, 11);	
							cout << "Khong Tim Thay Lop Tin Chi";
							Sleep(1000);
							gotoxy(45, 11);	
							cout << "                             ";
						}
				    } catch(invalid_argument e) {
				        gotoxy(45, 11);	
						cout << "Ma Lop Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
				    }
					fflush(stdin);					
				} while (true);
				
				if(maLopTC == 0 || s_maLop == "") break;
		
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
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 2, 4);
				
				gotoxy(31, 15);
				cout << "Nhap Ma Mon Hoc";
				gotoxy(31, 17);
				cout << "Nhap Niem Khoa";
				gotoxy(31, 19);
				cout << "Nhap Hoc Ky";
				gotoxy(31, 21);
				cout << "Nhap Nhom";
				
				LopTC ltc;
				bool exit = false;
				do {
					exit = enterMaMH(ltc, 15); if(exit) break;
					enterNiemKhoa(ltc, 17);
					enterHocKi(ltc, 19);
					enterNhom(ltc, 21);
					if(checkExitsLTC(ltc)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "LTC Khong Ton Tai. Nhap Lai";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
					}
				} while (true);
				
				if(exit) break;
				
				LopTC *ltc_sv = getExitsLTC(ltc);
				createTableDSSV(COLUMN_FRAME_MENU - 10, ROW_FRAME_MENU + 12, ltc_sv->sv.size);
				gotoxy(11, 25);	
				cout << "Ma Sinh Vien";
				gotoxy(31, 25);	
				cout << "Ho";
				gotoxy(51, 25);	
				cout << "Ten";
				gotoxy(71, 25);	
				cout << "Phai";
				gotoxy(91, 25);	
				cout << "So Dien Thoai";
				gotoxy(111, 25);	
				cout << "Ma Lop";
				
				
				
				
				int row_sv_ltc = 27;
				for(int i = 0, size = ltc_sv->sv.size; i < size; i++) {
					SinhVien *sv = get(ltc_sv->sv, i);
					gotoxy(11, row_sv_ltc);
					cout << sv->maSV;
					gotoxy(31, row_sv_ltc);
					cout << sv->ho;
					gotoxy(51, row_sv_ltc);
					cout << sv->ten;
					gotoxy(71, row_sv_ltc);
					cout << sv->phai;
					gotoxy(91, row_sv_ltc);
					cout << sv->sdt;
					gotoxy(111, row_sv_ltc);
					cout << sv->maLop;
					row_sv_ltc+=2;
				}
				
				
				getch();
				break;
			}
			
			case 5: {
				system("cls");
				printTitleQLTC();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 1);
				
				
				string maLopTC;
				int maLoptc;
				gotoxy(31, 13);
				cout << "Nhap Ma Lop Tin Chi";
				
				do {
					gotoxy(51, 13);	
					cout << "                             ";
					gotoxy(51, 13);
					getline(cin, maLopTC);
					if(maLopTC == "") break;
					try {
				        maLoptc = stoi(maLopTC);
				        if(maLoptc == 0 || findMaLTC(lopTinChis, maLoptc)) {
							break;
						} else {
							gotoxy(45, 11);	
							cout << "Khong Tim Thay Lop Tin Chi";
							Sleep(1000);
							gotoxy(45, 11);	
							cout << "                             ";
						}
				    } catch(invalid_argument e) {
				        gotoxy(45, 11);	
						cout << "Ma Lop Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
				    }
					fflush(stdin);					
				} while (true);
				
				if(maLoptc == 0 || maLopTC == "") break;
		
				int index = binarySearch(lopTinChis.array, 0 , lopTinChis.size - 1, maLoptc);
				LopTC *ltc = get(lopTinChis, index);
				
				
				int size_SV_LTC = sizeof(options_SV_LTC)/sizeof(options_SV_LTC[0]);
				int choose_SV_LTC = -1;
				do {
					system("cls");
					printTitleQLTC();
					choose_SV_LTC = printOption_SV_LTC();
					switch(choose_SV_LTC) {
						case 0: {
							fflush(stdin);
							system("cls");
							printTitleQLTC();
							createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 1);
							gotoxy(31, 13);
							cout << "Nhap Ma Sinh Vien";
				
							char maSV[15];
							int indexSV;
							do {
								fflush(stdin);
								gotoxy(51, 13);	
								cout << "                             ";
								gotoxy(51, 13);
								gets(maSV);
								if(strcmp(maSV, "") == 0) break;
								if(findMaSV(maSV)) {
									indexSV = getIndexMaSV(maSV);
									SinhVien *sv = get(sinhviens, indexSV);
									
									add(ltc->sv, *sv);
									
									gotoxy(45, 11);	
									cout << "Them Thanh Cong";
									Sleep(1000);
									gotoxy(45, 11);	
									cout << "                             ";
									
								} else {
									gotoxy(45, 11);	
									cout << "Khong Tim Thay Ma Sinh Vien";
									Sleep(1000);
									gotoxy(45, 11);	
									cout << "                             ";
								}					
							} while (true);
							
							
							
							break;
						}
						case 1:{
//							remove_SV_LTC();
							break;
						}		
					}
				} while (choose_SV_LTC != size_SV_LTC - 1);
				getch();
				break;
			}
			
			case 6: {
				system("cls");
				printTitleQLTC();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 2, 4);
				
				gotoxy(31, 15);
				cout << "Nhap Ma Mon Hoc";
				gotoxy(31, 17);
				cout << "Nhap Niem Khoa";
				gotoxy(31, 19);
				cout << "Nhap Hoc Ky";
				gotoxy(31, 21);
				cout << "Nhap Nhom";
				LopTC ltc;
				bool exit = false;
				do {
					exit = enterMaMH(ltc, 15); if(exit) break;
					enterNiemKhoa(ltc, 17);
					enterHocKi(ltc, 19);
					enterNhom(ltc, 21);
					if(checkExitsLTC(ltc)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "LTC Khong Ton Tai. Nhap Lai";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
					}
				} while (true);
				
				if(exit) break;
				
				
				exit =false;
				do {
					system("cls");
					printTitleQLTC();
					createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 2, 2);
					gotoxy(31, 15);
					cout << "Nhap Ma Sinh Vien";
					gotoxy(31, 17);
					cout << "Nhap Diem";
					
					int stt = 1;
					LopTC *ltc_sv = getExitsLTC(ltc);
					createTableBangDiem(COLUMN_FRAME_MENU - 10, ROW_FRAME_MENU + 12, ltc_sv->sv.size);
					gotoxy(11, 25);	
					cout << "STT";
					gotoxy(31, 25);	
					cout << "Ma Sinh Vien";
					gotoxy(51, 25);	
					cout << "Ho";
					gotoxy(71, 25);	
					cout << "Ten";
					gotoxy(91, 25);	
					cout << "Diem";
					
					int row_sv_ltc = 27;
					for(int i = 0, size = ltc_sv->sv.size; i < size; i++) {
						SinhVien *sv = get(ltc_sv->sv, i);
						gotoxy(11, row_sv_ltc);
						cout << stt++;
						gotoxy(31, row_sv_ltc);
						cout << sv->maSV;
						gotoxy(51, row_sv_ltc);
						cout << sv->ho;
						gotoxy(71, row_sv_ltc);
						cout << sv->ten;
						
						for(int j = 0, size2 = dangkys.size; j < size2; j++) {
							DangKy *dk = get(dangkys, j);
							if(strcmp(sv->maSV, dk->maSV) == 0 && ltc_sv->maLop == dk->maLop) {
								gotoxy(91, row_sv_ltc);
								cout << dk->diem ;
							}
						}
						
						row_sv_ltc+=2;
					}
					
					
					
					char maSV[15];
					do {
						fflush(stdin);
						gotoxy(51, 15);	
						cout << "                             ";
						gotoxy(51, 15);
						gets(maSV);
						if(strcmp(maSV, "") == 0) exit = true;
						if(exit) break;
						if(findMaSV(maSV)) {
							break;
						} else {
							gotoxy(45, 11);	
							cout << "Khong Tim Thay Ma Sinh Vien";
							Sleep(1000);
							gotoxy(45, 11);	
							cout << "                             ";
						}					
					} while (true);
					
					if(exit) break;
					
					if(strcmp(maSV, "") == 0) break;
				
					float diem = 0;
					do {
						fflush(stdin);
						gotoxy(51, 17);	
						cout << "                             ";
						gotoxy(51, 17);
						cin >> diem;
						if(diem > 10 || diem < 0) {
							gotoxy(45, 11);	
							cout << "Diem Khong Hop Le";
							Sleep(1000);
							gotoxy(45, 11);	
							cout << "                             ";
						} else {
							break;
						}
											
					} while (true);

					for(int i = 0, size = dangkys.size; i < size; i++) {
						DangKy *dk = get(dangkys, i);
						if( (strcmp(maSV, dk->maSV) == 0 ) && (dk->maLop == ltc_sv->maLop)) {
							dk->diem = diem;
						}
					}
				} while(!exit);
				
				break;
			}
			
			case 7: {
				system("cls");
					
				printTitleQLTC();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 2, 4);
				
				gotoxy(31, 15);
				cout << "Nhap Ma Mon Hoc";
				gotoxy(31, 17);
				cout << "Nhap Niem Khoa";
				gotoxy(31, 19);
				cout << "Nhap Hoc Ky";
				gotoxy(31, 21);
				cout << "Nhap Nhom";
				LopTC ltc;
				bool exit = false;
				do {
					exit = enterMaMH(ltc, 15); if(exit) break;
					enterNiemKhoa(ltc, 17);
					enterHocKi(ltc, 19);
					enterNhom(ltc, 21);
					if(checkExitsLTC(ltc)) {
						break;
					} else {
						gotoxy(45, 11);	
						cout << "LTC Khong Ton Tai. Nhap Lai";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
					}
				} while (true);
				
				if(exit) break;
				
				system("cls");
				printTitleBangDiem();
				gotoxy(47, 5);
				cout << ltc.niemKhoa;
				gotoxy(65, 5);
				cout << ltc.hocKi;
				gotoxy(80, 5);
				cout << ltc.nhom;
				LopTC *ltc_sv = getExitsLTC(ltc);
				createTableBangDiem(COLUMN_FRAME_MENU - 10, ROW_FRAME_MENU , ltc_sv->sv.size);
				gotoxy(11, 13);	
				cout << "STT";
				gotoxy(31, 13);	
				cout << "Ma Sinh Vien";
				gotoxy(51, 13);	
				cout << "Ho";
				gotoxy(71, 13);	
				cout << "Ten";
				gotoxy(91, 13);	
				cout << "Diem";
				int stt= 1;
				
				int row_sv_ltc = 15;
				for(int i = 0, size = ltc_sv->sv.size; i < size; i++) {
					SinhVien *sv = get(ltc_sv->sv, i);
					gotoxy(11, row_sv_ltc);
					cout << stt++;
					gotoxy(31, row_sv_ltc);
					cout << sv->maSV;
					gotoxy(51, row_sv_ltc);
					cout << sv->ho;
					gotoxy(71, row_sv_ltc);
					cout << sv->ten;

					for(int j = 0, size2 = dangkys.size; j < size2; j++) {
						DangKy *dk = get(dangkys, j);
						if(strcmp(sv->maSV, dk->maSV) == 0 && ltc_sv->maLop == dk->maLop) {
							gotoxy(91, row_sv_ltc);
							cout << dk->diem ;
						} 
					}
					
					row_sv_ltc+=2;
				}
				getch();
				break;
			}
			
			case 8: {
				ofs_ltc.open("loptinchi.txt", ofstream::out);
				writeFileLopTinChi(lopTinChis);
				ofs_ltc.close();
				
				ofs_dk.open("dangky.txt", ofstream::out);
				writeFileDK(dangkys);
				ofs_dk.close();
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
	"5 Danh Sach Sinh Vien Cua Mot Lop",
	"6 Dang Ky Lop Tin Chi",
	"7 Luu Vao File",
	"8 Quay Lai"
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

int printOptionQLSV() {
	int choose = 0;
	printFrame(75, 12, COLUMN_FRAME_MENU, ROW_FRAME_MENU, COLOR_SL);
	int size = sizeof(optionQLSV)/sizeof(optionQLSV[0]);
	int col = COLUMN_FRAME_MENU + 20;
	int row = ROW_FRAME_MENU + 2;
	for(int i = 0; i < size; i++) {
		if(choose == i) {
			gotoxy(col, row + i);
			cout << optionQLSV[i];
		} else {
			SetColor(COLOR_DF);
			gotoxy(col, row + i);
			cout << optionQLSV[i];
		}
	}
	char c;
	while(true) {
		c = getch();
		if(c == UP && choose != 0) {
			SetColor(COLOR_DF);
			gotoxy(col, row + choose);
			cout << optionQLSV[choose--];
			SetColor(COLOR_SL);
			gotoxy(col, row + choose);
			cout << optionQLSV[choose];
		} else if (c == DOWN && choose != size - 1) {
			SetColor(COLOR_DF);
			gotoxy(col, row + choose);
			cout << optionQLSV[choose++];
			SetColor(COLOR_SL);
			gotoxy(col, row + choose);
			cout << optionQLSV[choose];
		} else if (c == ENTER) {
			return choose;
		}
	}
}

ifstream ifs_sv;
void loadDataDSSinhVien() {
	ifs_sv.open("sinhvien.txt", ifstream::in);
	string line;
	string *s;
	while(getline(ifs_sv, line)) {
		SinhVien sv;
		s = split(line+"\n", ",");
		strcpy(sv.maSV, s[0].c_str());
		strcpy(sv.ho, s[1].c_str());
		strcpy(sv.ten, s[2].c_str());
		sv.phai = s[3];
		sv.sdt = s[4];
		strcpy(sv.maLop, s[5].c_str());
		add(sinhviens, sv);
	}
}


bool enterMaSV(SinhVien &sv, int row) {
	do {
		string s_maSV;
		gotoxy(51, row);
		cout << "                    ";
		gotoxy(51, row);
		getline(cin, s_maSV);
		if(s_maSV == "") return true;
		if(s_maSV.length() <= 15) {
			strcpy(sv.maSV, s_maSV.c_str());
			break;
		} else {
			gotoxy(45, 11);	
			cout << "Ma Sinh Vien Khong Dung";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                              ";
		}
	} while(true);
	return false;
}

void enterHoSV(SinhVien &sv, int row) {
	do {
		string s_hosv;
		gotoxy(51, row);
		cout << "                    ";
		gotoxy(51, row);
		getline(cin, s_hosv);
		if(s_hosv.length() <= 15) {
			strcpy(sv.ho, s_hosv.c_str());
			break;
		} else {
			gotoxy(45, 11);	
			cout << "Ho Sinh Vien Khong Dung";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                              ";
		}
	} while(true);
}

void enterTenSV(SinhVien &sv, int row) {
	do {
		string s_tensv;
		gotoxy(51, row);
		cout << "                    ";
		gotoxy(51, row);
		getline(cin, s_tensv);
		if(s_tensv.length() <= 15) {
			strcpy(sv.ten, s_tensv.c_str());
			break;
		} else {
			gotoxy(45, 11);	
			cout << "Ten Sinh Vien Khong Dung";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                              ";
		}
	} while(true);
}

bool isPhai(string &s) {
	if(s == "m" || s == "M" || s == "f" || s == "F") return true;
	return false;
}

void enterPhai(SinhVien &sv, int row) {
	do {
		gotoxy(51, row);
		cout << "                    ";
		gotoxy(51, row);
		getline(cin, sv.phai);
		if(isPhai(sv.phai)) {
			break;
		} else {
			gotoxy(45, 11);	
			cout << "Gioi Tinh Sinh Vien Khong Dung";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                              ";
		}
	} while (true);
}

void enterSDT(SinhVien &sv, int row) {
	do {
		fflush(stdin);
		gotoxy(51, row);
		cout << "                    ";
		gotoxy(51, row);
		getline(cin, sv.sdt);
		if(sv.sdt.length() == 10) {
			break;
		} else {
			gotoxy(45, 11);	
			cout << "SDT Sinh Vien Khong Dung";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                              ";
		}
	} while(true);
} 

void enterMaLopSV(SinhVien &sv, int row) {
	do {
		
		fflush(stdin);
		gotoxy(51, row);
		cout << "                    ";
		gotoxy(51, row);
		gets(sv.maLop);
		if(strlen(sv.maLop) <= 15) {
			break;
		} else {
			gotoxy(45, 11);	
			cout << "Ma Lop Sinh Vien Khong Dung";
			Sleep(1000);
			gotoxy(45, 11);	
			cout << "                              ";
		}
	} while(true);
}

int rowSV = 16;
void printDanhSachSV(LinkedList<SinhVien> &sv) {
	for (int i = 0, size = sv.size; i < size; i++) {
		SinhVien *tempSV = get(sv, i);
		gotoxy(11, rowSV);
		cout << tempSV->maSV;
		gotoxy(31, rowSV);
		cout << tempSV->ho;
		gotoxy(51, rowSV);
		cout << tempSV->ten;
		gotoxy(71, rowSV);
		cout << tempSV->phai;
		gotoxy(91, rowSV);
		cout << tempSV->sdt;
		gotoxy(111, rowSV);
		cout << tempSV->maLop;
		rowSV+=2; 
	}
}

void clearSV() {
	gotoxy(51, 17);
	cout << "                    ";
	gotoxy(51, 19);
	cout << "                    ";
	gotoxy(51, 21);
	cout << "                    ";
	gotoxy(51, 23);
	cout << "                    ";
	gotoxy(51, 25);
	cout << "                    ";
}

bool findMaSV(char maSV[15]) {
	for(int i = 0, size = sinhviens.size; i < size; i++) {
		if(strcmp(get(sinhviens, i)->maSV, maSV) == 0 ) {
			return true;
		}
	}
	
	return false;
}

bool checkMaLop(char maLop[15]) {
	for(int i = 0, size = sinhviens.size; i < size; i++) {
		SinhVien *t = get(sinhviens, i);
		if(strcmp(t->maLop, maLop) == 0 ) {
			return true;
		}
	}
	
	return false;
}

int getIndexMaSV(char maSV[15]) {
	for(int i = 0, size = sinhviens.size; i < size; i++) {
		if(strcmp(get(sinhviens, i)->maSV, maSV) == 0 ) {
			return i;
		}
	}
	return -1;
}

int getIndexMaLop(char maLop[15]) {
	for(int i = 0, size = sinhviens.size; i < size; i++) {
		if(strcmp(get(sinhviens, i)->maLop, maLop) == 0 ) {
			return i;
		}
	}
	return -1;
}

ofstream ofs_sv;
void writeFileSV(LinkedList<SinhVien> &sv) {

	for(int i = 0, size = sv.size; i < size; i++) {
		SinhVien *t = get(sv, i);
		ofs_sv << t->maSV << "," << t->ho << "," << 
			t->ten << "," << t->phai << "," << 
			t->sdt << "," << t->maLop << "," << "\n";
	}
}


void writeFileDK(LinkedList<DangKy> &dk) {

	for(int i = 0, size = dk.size; i < size; i++) {
		DangKy *t = get(dk, i);
		ofs_dk << t->maSV << "," << t->diem << "," << 
			 t->maLop << "," << "\n";
	}
}

bool checkExistSV(SinhVien &sv) {
	for(int i = 0, size = sinhviens.size; i < size; i++) {
		SinhVien *temp = get(sinhviens, i);
		if(strcmp(temp->maSV, sv.maSV) == 0) {
			return true;
		}
	}
	return false;
}

void bubbleSortSV(ArrayList<SinhVien> &sv) {
	for(int i = 0, size = sv.size - 1; i < size; i++) {
		for(int j = i + 1, size = sv.size; j < size; j++) {
			
			if(strcmp(sv.array[i].ten, sv.array[j].ten) > 0) {
				SinhVien t = sv.array[i];
				sv.array[i] = sv.array[j];
				sv.array[j] = t;
			}
			
			if(strcmp(sv.array[i].ten, sv.array[j].ten) == 0) {
				if(strcmp(sv.array[i].ho, sv.array[j].ho) > 0 ) {
					SinhVien t = sv.array[i];
					sv.array[i] = sv.array[j];
					sv.array[j] = t;
				}
			}
		}
	}
}

void processQLSV() {
	int choose;
	int size = sizeof(optionQLSV)/sizeof(optionQLSV[0]);
	do {
		rowSV=16;
		generateKey(monhocs.root);
		system("cls");
		printTitleQLSV();
		choose = printOptionQLSV();
		switch(choose) {
			
			case 0: { 	// them sinh vien
				fflush(stdin);
				system("cls");
				printTitleQLSV();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 2, 6);
				gotoxy(31, 15);
				cout << "Ma Sinh Vien";
				gotoxy(31, 17);
				cout << "Ho";
				gotoxy(31, 19);
				cout << "Ten";
				gotoxy(31, 21);
				cout << "Phai";
				gotoxy(31, 23);
				cout << "So Dien Thoai";
				gotoxy(31, 25);
				cout << "Ma Lop";
				
				
				SinhVien sv;
				bool exit = false;
				do {
					exit = enterMaSV(sv, 15); if(exit) break;
					enterHoSV(sv, 17);
					enterTenSV(sv, 19);	
					enterPhai(sv, 21);	
					enterSDT(sv, 23);	
					enterMaLopSV(sv, 25);
					
					if(checkExistSV(sv)) {
						gotoxy(45, 10);
						cout << "Sinh Vien Da Ton Tai";
						Sleep(1000);
						gotoxy(45, 10);
						cout << "                     ";
					} else {
						add(sinhviens, sv);
						gotoxy(45, 10);
						cout << "Them Thanh Cong";
						Sleep(1000);
						gotoxy(45, 10);
						cout << "               ";
						clearSV();
					}
				} while (!exit);
				
				break;
			}
			
			case 1: {  // sua sinh vien
				system("cls");
				printTitleQLSV();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 1);
				gotoxy(31, 13);
				cout << "Nhap Ma Sinh Vien";
				
				char maSV[15];
				int indexSV;
				do {
					fflush(stdin);
					gotoxy(51, 13);	
					cout << "                             ";
					gotoxy(51, 13);
					gets(maSV);
					if(strcmp(maSV, "") == 0) break;
					if(findMaSV(maSV)) {
						indexSV = getIndexMaSV(maSV);
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Khong Tim Thay Ma Sinh Vien";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                             ";
					}					
				} while (true);
				
				if(strcmp(maSV, "") == 0) break;
				SinhVien *sv = get(sinhviens, indexSV);
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU + 6, 6);
				gotoxy(31, 19);
				cout << "Ma Sinh Vien";
				gotoxy(31, 21);
				cout << "Ho";
				gotoxy(31, 23);
				cout << "Ten";
				gotoxy(31, 25);
				cout << "Phai";
				gotoxy(31, 27);
				cout << "So Dien Thoai";
				gotoxy(31, 29);
				cout << "Ma Lop";
				
				gotoxy(51, 19);
				cout << sv->maSV;
				gotoxy(51, 21);
				cout << sv->ho;
				gotoxy(51, 23);
				cout << sv->ten;
				gotoxy(51, 25);
				cout << sv->phai;
				gotoxy(51, 27);
				cout << sv->sdt;
				gotoxy(51, 29);
				cout << sv->maLop;
				
				
				Sleep(500);
				
//				enterMaSV(*sv, 19);
				enterHoSV(*sv, 21);
				enterTenSV(*sv, 23);	
				enterPhai(*sv, 25);	
				enterSDT(*sv, 27);	
				enterMaLopSV(*sv, 29);
				
				
				gotoxy(45, 10);
				cout << "Sua Thanh Cong";
				Sleep(1000);
				gotoxy(45, 10);
				cout << "               ";
				
				
				
				break;
			}
			
			case 2: { // xoa sinh vien
				system("cls");
				printTitleQLSV();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 1);
				gotoxy(31, 13);
				cout << "Nhap Ma Sinh Vien";
				char maSV[15];
				int indexSV;
				do {
					fflush(stdin);
					gotoxy(51, 13);	
					cout << "                             ";
					gotoxy(51, 13);
					gets(maSV);
					if(strcmp(maSV, "") == 0) break;
					if(findMaSV(maSV)) {
						indexSV = getIndexMaSV(maSV);
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Khong Tim Thay Ma Sinh Vien";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                             ";
					}					
				} while (true);
				
				remove(sinhviens, indexSV);
				gotoxy(45, 10);
				cout << "Xoa Thanh Cong";
				Sleep(1000);
				gotoxy(45, 10);
				cout << "                  ";
				getch();
				break;
			}
			
			case 3: { // danh sach sinh vien
				system("cls");
				printTitleQLSV();
				createTableDSSV(COLUMN_FRAME_MENU - 10, ROW_FRAME_MENU + 1, sinhviens.size);
				gotoxy(11, 14);
				cout << "Ma Sinh Vien";
				gotoxy(31, 14);
				cout << "Ho ";
				gotoxy(51, 14);
				cout << "Ten ";
				gotoxy(71, 14);
				cout << "Phai ";
				gotoxy(91, 14);
				cout << "So Dien Thoai ";
				gotoxy(111, 14);
				cout << "Ma Lop";
				printDanhSachSV(sinhviens);
				getch();
				break;
			}	
			
			case 4:{ // dssv cua lop
			
				system("cls");
				printTitleQLSV();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 1);
				gotoxy(31, 13);
				cout << "Nhap Ma Lop";
				
				char malop[15];
				ArrayList<SinhVien> sv;
				newArrayList(sv, 100);
				do {
					fflush(stdin);
					gotoxy(51, 13);	
					cout << "                             ";
					gotoxy(51, 13);
					gets(malop);
					if(strcmp(malop, "") == 0 ) break;
					if(checkMaLop(malop)) {
						for(int i = 0, size = sinhviens.size; i < size; i++) {
							SinhVien *t = get(sinhviens, i);
							if(strcmp(t->maLop, malop) == 0 ) {
								add(sv, *t);
							}
						}
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Khong Tim Thay Ma Lop";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                             ";
					}					
				} while (true);
				if(strcmp(malop, "") == 0 ) break;
				
				createTableDSSV(COLUMN_FRAME_MENU - 10, ROW_FRAME_MENU + 3, sv.size);
				gotoxy(11, 16);
				cout << "Ma Sinh Vien";
				gotoxy(31, 16);
				cout << "Ho ";
				gotoxy(51, 16);
				cout << "Ten ";
				gotoxy(71, 16);
				cout << "Phai ";
				gotoxy(91, 16);
				cout << "So Dien Thoai ";
				gotoxy(111, 16);
				cout << "Ma Lop";
				
				bubbleSortSV(sv);
				for (int i = 0, size = sv.size; i < size; i++) {
					SinhVien *tempSV = get(sv, i);
					gotoxy(11, rowSV+ 2);
					cout << tempSV->maSV;
					gotoxy(31, rowSV + 2);
					cout << tempSV->ho;
					gotoxy(51, rowSV + 2);
					cout << tempSV->ten;
					gotoxy(71, rowSV + 2);
					cout << tempSV->phai;
					gotoxy(91, rowSV + 2);
					cout << tempSV->sdt;
					gotoxy(111, rowSV + 2);
					cout << tempSV->maLop;
					rowSV+=2; 
				}
				
				getch();
				break;
			}
			
			case 5: { // dang ky ltc
				system("cls");
				printTitleQLSV();
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU, 3);
				gotoxy(31, 13);
				cout << "Nhap Ma Sinh Vien";
				gotoxy(31, 15);
				cout << "Nhap Niem Khoa";
				gotoxy(31, 17);
				cout << "Nhap Hoc Ki";
				
				char maSV[15];
				int indexSV;
				do {
					fflush(stdin);
					gotoxy(51, 13);	
					cout << "                             ";
					gotoxy(51, 13);
					gets(maSV);
					if(strcmp(maSV, "") == 0) break;
					if(findMaSV(maSV)) {
						indexSV = getIndexMaSV(maSV);
						break;
					} else {
						gotoxy(45, 11);	
						cout << "Khong Tim Thay Ma Sinh Vien";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                             ";
					}					
				} while (true);
				if(strcmp(maSV, "") == 0) break;
				
				LopTC ltc;
				enterNiemKhoa(ltc, 15);
				enterHocKi(ltc, 17);
				
				ArrayList<LopTC> temp;
				newArrayList(temp, 100);
				
				for(int i = 0, size = lopTinChis.size; i < size; i++) {
					LopTC *t = get(lopTinChis, i);
					if(t->niemKhoa == ltc.niemKhoa && strcmp(t->hocKi, ltc.hocKi) == 0) {
						add(temp, *t);
					}
				}
				
				system("cls");
				printTitleQLTC();
				

				
				createTableLTC(COLUMN_FRAME_MENU - 8, ROW_FRAME_MENU + 1, lopTinChis.size);
				gotoxy(13, 14);	
				cout << "Ma Lop TC";
				gotoxy(23, 14);	
				cout << "Ma Mon Hoc";
				gotoxy(43, 14);	
				cout << "Ten MH";
				gotoxy(63, 14);	
				cout << "Nhom";
				gotoxy(73, 14);	
				cout << "SV DK";
				gotoxy(83, 14);	
				cout << "con lai";

				int row = 16;
				for(int i = 0, size = temp.size; i < size; i++) {
					LopTC *t = get(temp, i); 
					gotoxy(13, row);
					cout << get(temp, i)->maLop;
					gotoxy(23, row);
					cout << get(temp, i)->maMH;
					
					gotoxy(43, row);
					int key = searchKeyMaMH(t->maMH);
					MonHoc mh = searchMaMH(monhocs.root, key);
					cout << mh.tenMH;
					
					gotoxy(63, row);
					cout << t->nhom;
					gotoxy(73, row);
					cout << t->sv.size;
					gotoxy(83, row);
					cout << (t->SvMax - t->sv.size);
					row+=2;
				}
				
				SinhVien *sv = get(sinhviens, indexSV);
				string maLopTC;
				int maLoptc;
				createTable(COLUMN_FRAME_MENU + 10, ROW_FRAME_MENU - 2, 1);
				gotoxy(31, 11);
				cout << "Nhap Ma Lop Tin Chi";
				do {
					gotoxy(51, 11);	
					cout << "                             ";
					gotoxy(51, 11);
					getline(cin, maLopTC);
					if(maLopTC == "") break;
					try {
				        maLoptc = stoi(maLopTC);
				        if(maLoptc == 0 || findMaLTC(lopTinChis, maLoptc)) {
						break;
						} else {
							gotoxy(45, 9);	
							cout << "Khong Tim Thay Lop Tin Chi";
							Sleep(1000);
							gotoxy(45, 9);	
							cout << "                             ";
						}
				    } catch(invalid_argument e) {
				        gotoxy(45, 11);	
						cout << "Ma Lop Khong Hop Le";
						Sleep(1000);
						gotoxy(45, 11);	
						cout << "                           ";
				    }
					fflush(stdin);					
				} while (true);
				
				if(maLoptc == 0 || maLopTC == "") break;
		
				int index = binarySearch(lopTinChis.array, 0 , lopTinChis.size - 1, maLoptc);
				LopTC *ltc_t = get(lopTinChis, index);
				
				add(ltc_t->sv, *sv);
				
				getch();
				break;
			}
			case 6: { // luu file
				ofs_sv.open("sinhvien.txt", ofstream::out);
				writeFileSV(sinhviens);
				ofs_sv.close();
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
	newLinkedList(sinhviens);
	newLinkedList(dangkys);
	
	loadDataMonHoc();
	loadDataLopTinChi();
	loadDataDSSinhVien();
	loadDataDangKy();
	
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
