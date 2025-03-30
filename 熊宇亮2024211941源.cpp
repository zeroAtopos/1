#include<iostream>
using namespace std;
const int maxsize = 100;
template<class T>
struct staticnode {
	T data;
	int next;
};
template<class T>
class staticlink {
public:
	staticlink();
	staticlink(T a[], int n);
	void insert(T a);
	T del(int i);
	void find(T x);
	int getline();
	void destroy();
	void print() {
		int curr = front;
		while (curr != -1) {
			cout << sarray[curr].data << " ";
			curr = sarray[curr].next;
		}
		cout << endl;
	}
private:
	int front;
	int tail;
	int length = 0;
	int free;//空闲链表头指针
	int allocatenode() {
		if (free == -1) {
			return -1;
		}
		int newnode = free;
		free = sarray[free].next;
		return newnode;
	}
	staticnode<T> sarray[maxsize];
};
template<class T>
staticlink<T>::staticlink() {
	for (int i = 0; i < maxsize - 1; i++) {
		sarray[i].next = i + 1;
	}sarray[maxsize - 1].next = -1;
	front = -1;
	tail = -1;
	length = 0;
	free = 0;

}
//头插法
//template<class T>
//staticlink<T>::staticlink(T a[], int n) {
//	if (n > maxsize)throw"溢出";
//		for (int i = 0; i < n; i++) {
//			int newnode = free;
//			free = sarray[free].next;
//			sarray[newnode].data = a[i];
//			sarray[newnode].next = front;
//			front = newnode;
//			if(tail==-1){
//				tail = newnode;
//		}
//		++length;
//	}
//}
//尾插法
template<class T>
staticlink<T>::staticlink(T a[], int n) {
	if (n > maxsize)throw"溢出";

	for (int i = 0; i < maxsize - 1; i++) {
		sarray[i].next = i + 1;
	}sarray[maxsize - 1].next = -1;
	front = -1;
	tail = -1;
	length = 0;
	free = 0;

	for (int i = 0; i < n; i++) {
		if (free == -1) throw "溢出";

		int newnode = free;
		free = sarray[free].next;
		sarray[newnode].data = a[i];
		sarray[newnode].next = -1;
		if (tail == -1) {

			front = newnode;
			tail = newnode;
		}
		else {
			sarray[tail].next = newnode;
			tail = newnode;
		}
		++length;
	}
}
template<class T>
void staticlink<T>::insert(T a) {
	int newnode = allocatenode();
	if (newnode == -1) throw"错误";
	sarray[newnode].data = a;
	sarray[newnode].next = -1;
	if (front == -1 || a < sarray[front].data) {
		sarray[newnode].next = front;
		front = newnode;
	}
	else {
		int x = front;
		while (sarray[x].next != -1 && sarray[sarray[x].next].data < a) {
			x = sarray[x].next;
		}
		sarray[newnode].next = sarray[x].next;
		sarray[x].next = newnode;
	}
	++length;
}
template<class T>
T staticlink<T>::del(int i) {
	if (i < 0 || i >= length)throw"错误";
	int prev = -1;
	int curr = front;
	int index = 0;
	while (index < i) {
		prev = curr;
		curr = sarray[curr].next;
		++index;
	}
	T deldata = sarray[curr].data;
	if (prev == -1) {
		front = sarray[curr].next;
	}
	else {
		sarray[prev].next = sarray[curr].next;
	}
	sarray[curr].next = free;
	--length;
	return deldata;
}
template<class T>
void staticlink<T>::find(T x) {
	if (front == -1)throw"链表为空";
	int curr = front;
	bool found = false;
	while (curr != -1) {
		if (sarray[curr].data == x) {
			cout << "数据位置为：" << curr << endl;
		}
		found = true;
		curr = sarray[curr].next;
	}
	if (!found) {
		cout << "未找到值为 " << x << " 的节点" << endl;
	}
}
template<class T>
int staticlink<T>::getline() {
	return length;
}
template<class T>
void staticlink<T>::destroy() {
	if (front == -1) {
		return;
	}
	int curr = front;
	while (curr != -1) {
		int next = sarray[curr].next;
		sarray[curr].next = free;
		free = curr;
		curr = next;
	}
	front = -1;
	tail = -1;
	length = 0;
}
int main() {
	int a[5] = { 10,20,20,60,80 };
	int n = 70;
	int m = 40;
	staticlink<int>list(a, 5);
	list.print();
	cout << list.getline() << endl;
	list.insert(n);
	list.print();
	cout << list.getline() << endl;
	list.del(3);
	list.print();
	cout << list.getline() << endl;
	list.find(20);
	list.destroy();
	list.print();
	cout << list.getline() << endl;
	return 0;
}