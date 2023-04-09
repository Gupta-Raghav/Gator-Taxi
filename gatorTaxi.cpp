#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct ride
{
    int ride_number;
    int ride_cost;
    int trip_duration;
};
struct Node
{
    ride data;
    // int data;     // holds the key
    Node *parent; // pointer to the parent
    Node *left;   // pointer to left child
    Node *right;  // pointer to right child
    int color;    // 1 -> Red, 0 -> Black
};

typedef Node *NodePtr;
//changed the code from a struct to class. 
class MinHeap {
private:
    vector<ride> heap;
    unordered_map<int, int> indices;
    void heapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap.size() && heap[left].ride_cost < heap[smallest].ride_cost) {
            smallest = left;
        }

        if (right < heap.size() && heap[right].ride_cost < heap[smallest].ride_cost) {
            smallest = right;
        }

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }

public:
    void insert(ride value) {
        heap.push_back(value);
        int i = heap.size() - 1;
        while (i > 0 && heap[(i - 1) / 2].ride_cost > heap[i].ride_cost) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    ride extractMin() {
        if (heap.size() == 0) {
            throw runtime_error("Heap is empty");
        }
        ride min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
        return min;
    }

    ride getMin() {
        if (heap.size() == 0) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }

    void cancelRide(int ride_num)
    {
        int index = -1;
        // Find the index of the element to be deleted
        for (int i = 0; i < heap.size(); i++)
        {
            if (heap[i].ride_number == ride_num)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            // Element not found
            return;
        }
        // Replace the element with the last element of the heap
        heap[index] = heap.back();
        heap.pop_back();
        // Restore the min heap property
        while (index > 0 && heap[index].ride_cost < heap[(index - 1) / 2].ride_cost)
        {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
        heapify(index);
    }
    bool isEmpty() {
        return heap.size() == 0;
    }

     void print() {
        for (int i = 0; i < heap.size(); i++) {
            cout << "Ride Number: " << heap[i].ride_number << ", Cost: " << heap[i].ride_cost << ", Duration: " << heap[i].trip_duration << endl;
        }
    }
};

class RBTree
{
private:
    Node *root;
    Node *TNULL;

    // initializes the nodes with appropriate values
    void initializeNULLNode(Node *node, Node *parent)
    {
        node->data.ride_number = 0;
        node->data.ride_cost = 0;
        node->data.trip_duration = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    void preOrderHelper(Node *node)
    {
        if (node != TNULL)
        {
            cout << node->data.ride_number << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(Node *node)
    {
        if (node != TNULL)
        {
            inOrderHelper(node->left);
            cout << node->data.ride_number << " ";
            inOrderHelper(node->right);
        }
    }

    void postOrderHelper(Node *node)
    {
        if (node != TNULL)
        {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data.ride_number << " ";
        }
    }

    Node *searchTreeHelper(Node *node, int key)
    {
        if (node == TNULL || key == node->data.ride_number)
        {
            return node;
        }

        if (key < node->data.ride_number)
        {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    // fix the rb tree modified by the delete operation
    void fixDelete(NodePtr x)
    {
        NodePtr s;
        while (x != root && x->color == 0)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->color == 1)
                {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0)
                {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == 0)
                    {
                        // case 3.3
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color == 1)
                {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0)
                {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == 0)
                    {
                        // case 3.3
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void rbTransplant(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key)
    {
        // find the node containing key
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL)
        {
            if (node->data.ride_number == key)
            {
                z = node;
            }

            if (node->data.ride_number <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if (z == TNULL)
        {
            cout << "Couldn't find key in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0)
        {
            fixDelete(x);
        }
    }

    // fix the red-black tree
    void fixInsert(NodePtr k)
    {
        NodePtr u;
        while (k->parent->color == 1)
        {
            if (k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left; // uncle
                if (u->color == 1)
                {
                    // case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        // case 3.2.2
                        k = k->parent;
                        rightRotate(k);
                    }
                    // case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right; // uncle

                if (u->color == 1)
                {
                    // mirror case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        // mirror case 3.2.2
                        k = k->parent;
                        leftRotate(k);
                    }
                    // mirror case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
            {
                break;
            }
        }
        root->color = 0;
    }

    void printHelper(NodePtr root, string indent, bool last)
    {
        // print the tree structure on the screen
        if (root != TNULL)
        {
            cout << indent;
            if (last)
            {
                cout << "R----";
                indent += "     ";
            }
            else
            {
                cout << "L----";
                indent += "|    ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << "{" << root->data.ride_number << "," << root->data.ride_cost << "," << root->data.trip_duration
                 << "}"
                 << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
        // cout<<root->left->data<<endl;
    }

public:
    RBTree()
    {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    // Pre-Order traversal
    // Node->Left Subtree->Right Subtree
    void preorder()
    {
        preOrderHelper(this->root);
    }

    // In-Order traversal
    // Left Subtree -> Node -> Right Subtree
    void inorder()
    {
        inOrderHelper(this->root);
    }

    // Post-Order traversal
    // Left Subtree -> Right Subtree -> Node
    void postorder()
    {
        postOrderHelper(this->root);
    }

    // search the tree for the key k
    // and return the corresponding node
    NodePtr searchTree(int k)
    {
        return searchTreeHelper(this->root, k);
    }

    // find the node with the minimum key
    NodePtr minimum(NodePtr node)
    {
        while (node->left != TNULL)
        {
            node = node->left;
        }
        return node;
    }

    // find the node with the maximum key
    NodePtr maximum(NodePtr node)
    {
        while (node->right != TNULL)
        {
            node = node->right;
        }
        return node;
    }

    // find the successor of a given node
    NodePtr successor(NodePtr x)
    {
        // if the right subtree is not null,
        // the successor is the leftmost node in the
        // right subtree
        if (x->right != TNULL)
        {
            return minimum(x->right);
        }

        // else it is the lowest ancestor of x whose
        // left child is also an ancestor of x.
        NodePtr y = x->parent;
        while (y != TNULL && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    // find the predecessor of a given node
    NodePtr predecessor(NodePtr x)
    {
        // if the left subtree is not null,
        // the predecessor is the rightmost node in the
        // left subtree
        if (x->left != TNULL)
        {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->left)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }

    // rotate left at node x
    void leftRotate(NodePtr x)
    {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // rotate right at node x
    void rightRotate(NodePtr x)
    {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // insert the key to the tree in its appropriate position
    // and fix the tree
    void insert(ride key)
    {
        // Ordinary Binary Search Insertion
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data.ride_number = key.ride_number;
        node->data.ride_cost = key.ride_cost;
        node->data.trip_duration = key.trip_duration;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1; // new node must be red

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL)
        {
            y = x;
            if (node->data.ride_number < x->data.ride_number)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        // y is parent of x
        // when the inserting node is the first node it skips the above while loop and reaches this
        // which sets the inserting node's parent to y in a way saying that this the root node as it won't have any parent.
        node->parent = y;
        if (y == nullptr)
        {
            root = node;
        }
        else if (node->data.ride_number < y->data.ride_number)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }

        // if new node is a root node, simply return
        if (node->parent == nullptr)
        {
            node->color = 0;
            return;
        }

        // if the grandparent is null, simply return
        if (node->parent->parent == nullptr)
        {
            return;
        }

        // Fix the tree
        fixInsert(node);
    }

    NodePtr getRoot()
    {
        return this->root;
    }

    // delete the node from the tree
    void deleteNode(int data)
    {
        deleteNodeHelper(this->root, data);
    }

    // print the tree structure on the screen
    void prettyPrint()
    {
        if (root)
        {
            printHelper(this->root, "", true);
        }
    }
};

int main(int argc, char **argv)
{
    cout << "welcome to the gator taxi\n";
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    // string input_file = argv[1];

    ifstream fin(argv[1]);

    if (!fin.is_open())
    {
        cout << "Unable to open input file" << endl;
        return 1;
    }
    cout << "dekho" << endl;
    // map<int, tuple<int, int>> redBlackTree; //ride number, tuple = ride cost and trip duration. //can't use this as of now.
    MinHeap heap; // initialized heap at this point
    RBTree rbt;   // initialized Red-black tree.
    string command;
    string line;
    int count = 1;
    while (getline(fin, line))
    {
        stringstream ss(line);

        string command, data;
        ss >> command;
        // cout << command <<endl;
        int ride_num, ride_cost, trip_duration;

        if (command.find("Insert") != string::npos)
        {
            // cout<<command<<endl;
            data = command.substr(command.find("(") + 1, command.find(")") - command.find("(") - 1);
            stringstream ss(data);
            string token;
            getline(ss, token, ',');
            ride_num = stoi(token);
            getline(ss, token, ',');
            ride_cost = stoi(token);
            getline(ss, token, ',');
            trip_duration = stoi(token);
            ride r = {ride_num, ride_cost, trip_duration};
            heap.insert(r);
            rbt.insert(r);
            rbt.prettyPrint();
            // TODO: implement Insert command
        }
        else if (command.find("Print") != string::npos)
        {
            cout << " " << endl;
            // rbt.prettyPrint();
            // heap.print();
            // TODO: implement Print command
        }
        else if (command == "UpdateTrip")
        {
            cout << "UpdateTrip m hun bc" << endl;
            char dummy;
            ss >> dummy >> ride_num >> dummy >> trip_duration >> dummy;
            // TODO: implement UpdateTrip command
        }
        else if (command.find("GetNextRide") != string::npos)
        {
            ride nextRide = heap.getMin();
            cout << "(" << nextRide.ride_number << "," << nextRide.ride_cost << "," << nextRide.trip_duration << ")" << endl;
            // TODO: implement GetNextRide command
        }
        else if (command.find("CancelRide") != string::npos)
        {
            cout << command << endl;
            data = command.substr(command.find("(") + 1, command.find(")") - command.find("(") - 1);
            stringstream ss(data);
            // stringstream ss(data);
            string token;
            getline(ss, token, ',');
            ride_num = stoi(token);
            cout << "CancelRide m hun bc" << endl;
            heap.cancelRide(ride_num);
            heap.print();
        }
    }

    fin.close();

    return 0;
}
