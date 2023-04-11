#include <iostream>
#include <queue>
#include <map>
#include <unordered_map>
using namespace std;

// Define a struct to represent a ride triplet
#include <iostream>
#include <vector>
#include <map>

// Define a struct to represent a ride triplet

#include <algorithm>

// Define the ride struct
struct Ride
{
    int rideNumber;
    int rideCost;
    int tripDuration;

    // Define a comparison operator to order the heap
    bool operator<(const Ride &other) const
    {
        if (rideCost == other.rideCost)
        {
            return tripDuration < other.tripDuration;
        }
        return rideCost < other.rideCost;
    }
};

vector<Ride> rides;
unordered_map<int, int> heapmp;
// Define a function to heapify the vector
void heapify(vector<Ride> &rides, int i, int n)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && rides[left].rideCost < rides[smallest].rideCost)
    {
        smallest = left;
    }

    if (right < n && rides[right].rideCost < rides[smallest].rideCost)
    {
        smallest = right;
    }

    if (smallest != i)
    {
        swap(rides[i], rides[smallest]);
        heapify(rides, smallest, n);
    }
}

// Define a function to build the heap
void buildHeap(vector<Ride> &rides)
{
    int n = rides.size();
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(rides, i, n);
    }
}

void insert(vector<Ride> &rides, Ride ride)
{
    // Insert the new ride at the end of the vector
    rides.push_back(ride);
    heapmp[ride.rideNumber] = ride.rideCost;

    // Heapify the vector from the bottom up
    int i = rides.size() - 1;
    while (i > 0 && rides[(i - 1) / 2].rideCost > rides[i].rideCost)
    {
        swap(rides[(i - 1) / 2], rides[i]);
        i = (i - 1) / 2;
    }
}

void deleteMin(vector<Ride> &rides)
{
    // Swap the root with the last element and remove the last element
    swap(rides[0], rides.back());
    rides.pop_back();

    // Heapify the vector from the root down
    heapify(rides, 0, rides.size());
}

Ride search_heap(int rideNumber)
{
    for (int i = 0; i < rides.size(); i++)
    {
        if (rides[i].rideNumber == rideNumber)
        {
            return rides[i];
        }
    }

    return {};
}

Ride getRide(int rideNumber)
{
    Ride ride = search_heap(rideNumber);

    return ride;
}

// Test the RideManager class

// ____-----------__----___-------_--------___----------_--------___-

enum Color
{
    RED,
    BLACK
};

// Node structure for the RBT
struct Node
{
    int rideNumber;
    int rideCost;
    int tripDuration;
    Color color;
    Node *left;
    Node *right;
    Node *parent;

    Node(int rideNumber, int rideCost, int tripDuration)
    {
        this->rideNumber = rideNumber;
        this->rideCost = rideCost;
        this->tripDuration = tripDuration;
        color = RED;
        left = right = parent = nullptr;
    }
};

// Class definition for the RBT
class RedBlackTree
{
private:
    Node *root;

    // Helper functions for RBT operations
    void leftRotate(Node *x);
    void rightRotate(Node *x);
    void insertFixup(Node *z);
    void transplant(Node *u, Node *v);
    void deleteFixup(Node *x);
    Node *minimum(Node *x);

    // void printHelper(Node* node, int indent) {
    //     if (node != nullptr) {
    //         string color = (node->color == RED) ? "RED" : "BLACK";
    //         cout << string(indent, ' ') << node->rideNumber << " (" << node->rideCost << ", " << node->tripDuration << ") [" << color << "] ";
    //         if (node->left != nullptr) {
    //             cout << "<- ";
    //         }
    //         else {
    //             cout << "   ";
    //         }
    //         if (node->right != nullptr) {
    //             cout << "->";
    //         }
    //         cout << endl;
    //         printHelper(node->left, indent + 4);
    //         printHelper(node->right, indent + 4);
    //     }
    // }

    void printHelper(Node *node, string indent, bool last)
    {
        // print the tree structure on the screen
        if (node != nullptr)
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

            string sColor = node->color ? "Black" : "Red";
            cout << "{" << node->rideNumber << "," << node->rideCost << "," << node->tripDuration
                 << "}"
                 << "(" << sColor << ")" << endl;
            printHelper(node->left, indent, false);
            printHelper(node->right, indent, true);
        }
        // cout<<root->left->data<<endl;
    }

public:
    RedBlackTree()
    {
        root = nullptr;
    }

    // Public functions for RBT operations
    void insert(int rideNumber, int rideCost, int tripDuration);
    void Print(int rideNumber);
    void Print(int rideN1, int rideN2);
    void remove(int rideNumber);
    Node *search(int rideNumber);
    //  void print() {
    //     printHelper(root, 0);
    // }

    void print()
    {
        if (root)
        {
            printHelper(this->root, "", false);
        }
    }
};

// Helper function for left rotation
void RedBlackTree::leftRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Helper function for right rotation
void RedBlackTree::rightRotate(Node *x)
{
    Node *y = x->left;
    x->left = y->right;
    if (y->right != nullptr)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RedBlackTree::insertFixup(Node *z)
{
    while (z->parent != nullptr && z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node *y = z->parent->parent->right;
            if (y != nullptr && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else
        {
            Node *y = z->parent->parent->left;
            if (y != nullptr && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::transplant(Node *u, Node *v)
{

    if (u->parent == nullptr)
    {
        cout << "idhar" << endl;
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
    cout << "idhar 2" << endl;
}

void RedBlackTree::deleteFixup(Node *x)
{
    while (x != root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right == nullptr || w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            Node *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left == nullptr || w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

Node *RedBlackTree::minimum(Node *x)
{
    while (x->left != nullptr)
    {
        x = x->left;
    }
    return x;
}

void RedBlackTree::insert(int rideNumber, int rideCost, int tripDuration)
{
    Node *z = new Node(rideNumber, rideCost, tripDuration);
    Node *y = nullptr;

    Node *x = root;
    while (x != nullptr)
    {
        y = x;
        if (z->rideNumber < x->rideNumber)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr)
    {
        root = z;
    }
    else if (z->rideNumber < y->rideNumber)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    // z->left = nullptr;
    // z->right = nullptr;
    // z->color = RED;

    if (z->parent == nullptr)
    {
        z->color = BLACK;
        return;
    }
    if (z->parent->parent == nullptr)
    {

        return;
    }

    insertFixup(z);
}

void RedBlackTree::remove(int rideNumber)
{
    // Find the node with the given rideNumber
    Node *TNULL;
    Node *z = root;
    while (z != nullptr && z->rideNumber != rideNumber)
    {
        if (z->rideNumber > rideNumber)
        {
            z = z->left;
        }
        else
        {
            z = z->right;
        }
    }

    // If the node was not found, return
    if (z == nullptr)
    {
        return;
    }

    // Determine the node to splice out
    Node *y;
    Node *x;
    Color original_color = z->color;

    if (z->left == nullptr)
    {
        y = z;
        x = z->right;
        cout << "here1" << endl;
        transplant(z, z->right);
        cout << "here vaaops" << endl;
    }
    else if (z->right == nullptr)
    {
        y = z;
        x = z->left;
        cout << "here2" << endl;
        transplant(z, z->left);
    }
    else
    {
        y = minimum(z->right);
        original_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            cout << "here3" << endl;
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        cout << "here4" << endl;
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        cout << "here5" << endl;
    }
    cout << "here6" << endl;
    // If the spliced out node was black, rebalance the tree
    if (original_color == BLACK)
    {
        deleteFixup(x);
    }
}

Node *RedBlackTree::search(int rideNumber)
{
    Node *z = root;
    while (z != nullptr)
    {
        if (z->rideNumber == rideNumber)
        {
            break;
        }
        else if (z->rideNumber > rideNumber)
        {
            z = z->left;
        }
        else
        {
            z = z->right;
        }
    }

    return z;
}

void RedBlackTree::Print(int rideNumber)
{
    Node *k = search(rideNumber);
    cout << k->rideNumber << k->rideCost << k->tripDuration << "\n";
}

void inorder(Node *n, int rideN1, int rideN2)
{
    if (n == NULL)
    {
        return;
    }
    inorder(n->left, rideN1, rideN2);
    if (n->rideNumber > rideN1 && n->rideNumber < rideN2)
        cout << n->rideNumber << "\n";
    inorder(n->right, rideN1, rideN2);
}

void RedBlackTree::Print(int rideN1, int rideN2)
{
    Node *k = root;
    inorder(k, rideN1, rideN2);
}

int main()
{

    RedBlackTree rb;
    rb.insert(25, 98, 46);
    rb.print();
    rb.remove(25);
    cout << "inserting" << endl;
    rb.insert(42, 17, 89);
    rb.print();
    rb.insert(9, 76, 31);
    rb.print();
    rb.insert(53, 97, 22);

    rb.print();
    rb.insert(20, 49, 59);

    rb.print();

    // rb.Print(9);
    // rb.Print(53);
    rb.Print(2, 25);

    rb.print();

    // Get the ride with the lowest cost
    // Ride* lowestCostRide = rideManager.getLowestCostRide();
    // Ride nr1 = {1,20,30};
    // Ride nr2 = {2,10,40};
    // Ride nr3 = {3,15,50};

    // insert(rides,nr1);
    // insert(rides,nr2);
    // insert(rides,nr3);

    // cout << "Lowest cost ride: #" << rides[0].rideNumber << endl;

    // // Get a ride by ride number
    // // Ride* ride2 = rideManager.getRide(2);

    // Ride ride2 = getRide(2);

    // cout << "Ride #" << ride2.rideNumber << ": cost=" << ride2.rideCost << ", duration=" << ride2.tripDuration << endl;

    // // Remove a ride
    // // rideManager.removeRide(1);

    // // Get the new ride with the lowest cost
    // // lowestCostRide = rideManager.getLowestCostRide();
    // deleteMin(rides);
    // cout << "New lowest cost ride: #" << rides[0].rideNumber << endl;

    return 0;
}