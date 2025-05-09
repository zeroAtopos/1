#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
using namespace std;

template <class T>
struct binode {
    T data;
    binode<T>* lch;
    binode<T>* rch;
};

template <class T>
class tree {
private:
    void create(binode<T>*& r, T data[], int i, int size);
    void release(binode<T>* r);

public:
    binode<T>* root;
    tree(T data[], int size);
    void preorder(binode<T>* r);
    void preorder2(binode<T>* r);
    void inorder(binode<T>* r);
    void postorder(binode<T>* r);
    void levelorder(binode<T>* r);
    int treedepth(binode<T>* r);
    int treedepth2(binode<T>* r);
    string findpath(binode<T>* r, binode<T>* target, vector<T>& path);
    bool findvalue(binode<T>* r, T target);
    ~tree();
};

template <class T>
void tree<T>::create(binode<T>*& r, T data[], int i, int size) {
    if (i <= size && data[i - 1] != 0) {
        r = new binode<T>;
        r->data = data[i - 1];
        r->lch = r->rch = nullptr;
        create(r->lch, data, 2 * i, size);
        create(r->rch, data, 2 * i + 1, size);
    }
}

template <class T>
tree<T>::tree(T data[], int size) {
    create(root, data, 1, size);
}

template <class T>
void tree<T>::preorder(binode<T>* r) {
    if (r != nullptr) {
        cout << r->data;
        preorder(r->lch);
        preorder(r->rch);
    }
}

template <class T>
void tree<T>::preorder2(binode<T>* r) {
    stack<binode<T>*> s;
    while (r != nullptr || !s.empty()) {
        if (r != nullptr) {
            cout << r->data;
            s.push(r);
            r = r->lch;
        }
        else {
            r = s.top();
            s.pop();
            r = r->rch;
        }
    }
}

template <class T>
void tree<T>::inorder(binode<T>* r) {
    if (r != nullptr) {
        inorder(r->lch);
        cout << r->data;
        inorder(r->rch);
    }
}

template <class T>
void tree<T>::postorder(binode<T>* r) {
    if (r != nullptr) {
        postorder(r->lch);
        postorder(r->rch);
        cout << r->data;
    }
}

template <class T>
void tree<T>::levelorder(binode<T>* r) {
    queue<binode<T>*> q;
    if (r != nullptr) q.push(r);
    while (!q.empty()) {
        binode<T>* p = q.front();
        q.pop();
        cout << p->data;
        if (p->lch != nullptr) q.push(p->lch);
        if (p->rch != nullptr) q.push(p->rch);
    }
}

template <class T>
int tree<T>::treedepth(binode<T>* r) {
    if (r == nullptr) {
        return 0;
    }
    queue<binode<T>*> q;
    q.push(r);
    int depth = 0;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            binode<T>* node = q.front();
            q.pop();
            if (node->lch) {
                q.push(node->lch);
            }
            if (node->rch) {
                q.push(node->rch);
            }
        }
        ++depth;
    }
    return depth;
}

template <class T>
int tree<T>::treedepth2(binode<T>* root) {
    if (root == nullptr) return 0;
    else {
        int left = treedepth2(root->lch);
        int right = treedepth2(root->rch);
        return (left > right ? left : right) + 1;
    }
}

template <class T>
string tree<T>::findpath(binode<T>* root, binode<T>* target, vector<T>& path) {
    if (root == nullptr) return "";
    path.push_back(root->data);
    if (root == target) {
        string pathStr = "找到路径: ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) {
                pathStr += ", ";
            }
            pathStr += to_string(path[i]);
        }
        return pathStr;
    }
    string leftPath = findpath(root->lch, target, path);
    if (!leftPath.empty()) {
        return leftPath;
    }
    string rightPath = findpath(root->rch, target, path);
    if (!rightPath.empty()) {
        return rightPath;
    }
    path.pop_back();
    return "";
}

template <class T>
bool tree<T>::findvalue(binode<T>* r, T target) {
    if (r == nullptr) {
        return false;
    }
    queue<binode<T>*> q;
    q.push(r);

    while (!q.empty()) {
        binode<T>* node = q.front();
        q.pop();
        if (node->data == target) {
            return true;
        }

        if (node->lch) {
            q.push(node->lch);
        }
        if (node->rch) {
            q.push(node->rch);
        }
    }
    return false;
}

template <class T>
void tree<T>::release(binode<T>* r) {
    if (r != nullptr) {
        release(r->lch);
        release(r->rch);
        delete r;
    }
}

template <class T>
tree<T>::~tree() {
    release(root);
}

int main() {
    int data[] = { 3, 9, 20, 0, 0, 15, 7 };
    int size = sizeof(data) / sizeof(data[0]);
    tree<int> t(data, size);
    cout << "前序遍历: ";
    t.preorder(t.root);
    cout << endl;
    cout << "中序遍历: ";
    t.inorder(t.root);
    cout << endl;
    cout << "后序遍历: ";
    t.postorder(t.root);
    cout << endl;
    cout << "层序遍历: ";
    t.levelorder(t.root);
    cout << endl;
    cout << "树的深度: " << t.treedepth(t.root) << endl;
    int target = 7;
    if (t.findvalue(t.root, target)) {
        cout << "找到了值为 " << target << " 的节点。" << endl;
    }
    else {
        cout << "未找到值为 " << target << " 的节点。" << endl;
    }
    vector<int> path;
    binode<int>* targetNode = nullptr;
    queue<binode<int>*> q;
    q.push(t.root);
    while (!q.empty()) {
        binode<int>* node = q.front();
        q.pop();
        if (node->data == target) {
            targetNode = node;
            break;
        }
        if (node->lch) q.push(node->lch);
        if (node->rch) q.push(node->rch);
    }
    if (targetNode) {
        string pathStr = t.findpath(t.root, targetNode, path);
        if (!pathStr.empty()) {
            cout << pathStr << endl;
        }
    }

    return 0;
}