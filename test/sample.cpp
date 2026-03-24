// For some tests
// Brusnigin, Zaplatkin
#include "avl.h"  // добавлять по одному .h файлу, чтобы не было переопределений
#include <vector>


int main() {
	/*AVL<int, double> avl;

    avl.Insert(0, 3.14);
    avl.Insert(1, 2.718);
    avl.Insert(2, -9.123);

    avl.is_avl();*/

    //vector<pair<int, double>> v = {{2, 2.1}, {1, 1.3}, {3, 3.4}, {4, 1.5}};
    //BST<int, double> bst(v);
    //bst.is_bst();
    vector<pair<int, double>> v = {{0, 3.14}, {1, -2.7}, {2, 5.1}, {3, 9.9}, {4, -6.3}, {5, 10.13}};
    AVL<int, double> avl(v);
    avl.Print();
    avl.Delete(1);
    avl.Delete(3);
    //avl.Print();
    //avl.Delete(3);
    //avl.Print();
    //avl.Delete(1);
    //avl.Print();
    //avl.Delete(3);
    cout << avl.is_avl() << endl;
}
