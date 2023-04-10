#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct ride
{
    int ride_number;
    int ride_cost;
    int trip_duration;
    int idx;
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
    void heapify(int i)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap.size() && heap[left].ride_cost < heap[smallest].ride_cost)
        {
            smallest = left;
        }

        if (right < heap.size() && heap[right].ride_cost < heap[smallest].ride_cost)
        {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            // update the idx values of the swapped rides
            indices[heap[i].ride_number] = i;
            indices[heap[smallest].ride_number] = smallest;
            heapify(smallest);
        }
        // update the idx value of the current ride
        indices[heap[i].ride_number] = i;
    }

public:
    void insert(ride value) {
        value.idx = heap.size(); // update the idx value of the ride to be inserted
        heap.push_back(value);
        int i = heap.size() - 1;
        while (i > 0 && heap[(i - 1) / 2].ride_cost > heap[i].ride_cost)
        {
            swap(heap[i], heap[(i - 1) / 2]);
            // update the idx values of the swapped rides
            indices[heap[i].ride_number] = i;
            indices[heap[(i - 1) / 2].ride_number] = (i - 1) / 2;
            i = (i - 1) / 2;
        }
        // update the idx value of the inserted ride
        indices[value.ride_number] = value.idx;
    }

    ride extractMin()
    {
        if (heap.size() == 0)
        {
            cout << "No active ride requests" << endl;
            return ride{-1, -1, -1, -1};
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

    void updateTrip(int rideNumber, int new_tripDuration)
    {
        // Check if rideNumber is in the heap
        if (indices.find(rideNumber) == indices.end())
        {
            // cout << "Ride " << rideNumber << " not found" << endl;
            return;
        }

        int index = indices[rideNumber];
        ride existing_ride = heap[index];
        // cout << "Existing ride info: "
        //      << "ride_number: " << existing_ride.ride_number << ", ride_cost: " << existing_ride.ride_cost << ", trip_duration: " << existing_ride.trip_duration << ", idx: " << existing_ride.idx << endl;

        if (new_tripDuration <= existing_ride.trip_duration)
        {
            // Case a: Trip Duration update
            existing_ride.trip_duration = new_tripDuration;
            // cout << "Trip duration updated " << existing_ride.trip_duration << endl;
            return;
        }
        else if (existing_ride.trip_duration < new_tripDuration <= 2 * existing_ride.trip_duration)
        {
            // Case b: driver cancels existing ride with a penalty of 10 and a new ride is created
            int new_cost = existing_ride.ride_cost + 10;
            ride new_ride = {existing_ride.ride_number, new_cost, new_tripDuration, existing_ride.idx};
            // cout << "Creating new ride with info: "
            //      << "ride_number: " << new_ride.ride_number << ", ride_cost: " << new_ride.ride_cost << ", trip_duration: " << new_ride.trip_duration << ", idx: " << new_ride.idx << endl;
            cancelRide(index);
            insert(new_ride);
        }
        else
        {
            // Case c: ride is automatically declined and removed from the heap
            // cout << "Ride " << rideNumber << " is automatically declined" << endl;
            cancelRide(index);
        }
    }

    void cancelRide(int index)
    {

        // Replace the element with the last element of the heap
        heap[index] = heap.back();
        heap.pop_back();
        // Restore the min heap property
        while (index > 0 && heap[index].ride_cost < heap[(index - 1) / 2].ride_cost)
        {
            swap(heap[index], heap[(index - 1) / 2]);
            // update the idx values of the swapped rides
            indices[heap[index].ride_number] = index;
            indices[heap[(index - 1) / 2].ride_number] = (index - 1) / 2;
            index = (index - 1) / 2;
        }
        heapify(index);
    }

    bool isEmpty() {
        return heap.size() == 0;
    }

     void print() {
        for (int i = 0; i < heap.size(); i++) {
            cout << "Ride Number: " << heap[i].ride_number << ", Cost: " << heap[i].ride_cost << ", Duration: " << heap[i].trip_duration << ", index: " << heap[i].idx << endl;
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
    // Updatefunction

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
            // cout << "Couldn't find key in the tree" << endl;
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

    // void printHelper(NodePtr root, string indent, bool last)
    // {
    //     // print the tree structure on the screen
    //     if (root != TNULL)
    //     {
    //         cout << indent;
    //         if (last)
    //         {
    //             cout << "R----";
    //             indent += "     ";
    //         }
    //         else
    //         {
    //             cout << "L----";
    //             indent += "|    ";
    //         }

    //         string sColor = root->color ? "RED" : "BLACK";
    //         cout << "{" << root->data.ride_number << "," << root->data.ride_cost << "," << root->data.trip_duration
    //              << "}"
    //              << "(" << sColor << ")" << endl;
    //         printHelper(root->left, indent, false);
    //         printHelper(root->right, indent, true);
    //     }
    //     // cout<<root->left->data<<endl;
    // }

    void printHelper(NodePtr root, int least, int max)
    {
        // cout << max << " " << least << endl;
        // print the tree structure on the screen
        if (root->data.ride_number >= least && root->data.ride_number <= max && root != TNULL)
        {
            printHelper(root->left, least, max);
            cout << "(" << root->data.ride_number << "," << root->data.ride_cost << "," << root->data.trip_duration
                 << ")"
                 << ",";
            printHelper(root->right, least, max);
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
    // update trip function call here;

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

    void updateTrip(int rideNumber, int duration)
    {

        if (searchTree(rideNumber) == TNULL)
        {
            cout << "Ride doesn't exist" << endl;
            return;
        }
        else
        {
            // Ordinary Binary Search Insertion
            NodePtr node = searchTree(rideNumber);
            node->data.trip_duration = duration;
        }
    }

    // insert the key to the tree in its appropriate position
    // and fix the tree
    void
    insert(ride key)
    {
        if (searchTree(key.ride_number) != TNULL)
        {
            cout << "Duplicate RideNumber" << endl;
            return;
        }
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
    void deleteNode(int ridenumber)
    {
        // cout << "RBT m se uda rela hai m " << ridenumber << endl;
        deleteNodeHelper(this->root, ridenumber);
    }

    // print the tree structure on the screen
    void prettyPrint(int n1, int n2)
    {
        // cout << "printing the triplets" << endl;
        if (root)
        {
            printHelper(this->root, n1, n2);
            cout << endl;
        }
        // cout << "ENOUGH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
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
    // cout << "dekho" << endl;
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
        // cout << command << endl;
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
            // cout << "inserting" << r.ride_number << endl;
            heap.insert(r);
            rbt.insert(r);
            // rbt.prettyPrint();
            // TODO: implement Insert command
        }
        else if (command.find("Print") != string::npos)
        {
            // cout << "inside print" << endl;
            int ride_num1 = 0, ride_num2 = 0;
            data = command.substr(command.find("(") + 1, command.find(")") - command.find("(") - 1);
            stringstream ss(data);
            if (data.length() != 1)
            {
                string token;
                getline(ss, token, ',');
                ride_num1 = stoi(token);
                getline(ss, token, ',');
                ride_num2 = stoi(token);
                rbt.prettyPrint(ride_num1, ride_num2);
                // heap.print();
            }
            else
            {
                ride_num1 = stoi(data);
                Node *res = rbt.searchTree(ride_num1);
                // cout << "Found the node-Here are the triplets: "
                cout << "(" << res->data.ride_number << "," << res->data.ride_cost << "," << res->data.trip_duration << ")" << endl;
            }

            //
            // getline(ss, token, ',');
            // trip_duration = stoi(token);
            // ride r = {ride_num, ride_cost, trip_duration};
            // cout << "ride #1:" << ride_num1 << " "
            //  << "ride #2:" << ride_num2 << " " << endl;
            // rbt.searchTree()
            //  rbt.prettyPrint();
            //  heap.print();
            //  TODO: implement Print command
        }
        else if (command.find("UpdateTrip") != string::npos)
        {
            // cout << "UpdateTrip m hun bc" << endl;
            int number = 0, duration = 0;
            data = command.substr(command.find("(") + 1, command.find(")") - command.find("(") - 1);
            stringstream ss(data);
            string token;
            getline(ss, token, ',');
            number = stoi(token);
            getline(ss, token, ',');
            duration = stoi(token);
            // cout << "number: " << number << "duration: " << duration << endl;
            // Node *res = rbt.searchTree(number);
            // heap.updateTrip(res->data.idx, number, duration);
            heap.updateTrip(number, duration);
            rbt.updateTrip(number, duration);
            // rbt.prettyPrint(1, 90);
            // char dummy;
            // ss >> dummy >> ride_num >> dummy >> trip_duration >> dummy;
            // TODO: implement UpdateTrip command
        }
        else if (command.find("GetNextRide") != string::npos)
        {
            ride nextRide = heap.extractMin();
            if (nextRide.ride_number != -1)
            {
                rbt.deleteNode(nextRide.ride_number);

                // rbt.prettyPrint(nextRide.ride_number, nextRide.ride_number);

                cout << "(" << nextRide.ride_number << "," << nextRide.ride_cost << "," << nextRide.trip_duration << ")" << endl;
                // TODO: implement GetNextRide command
            }
        }
        else if (command.find("CancelRide") != string::npos)
        {
            // cout << command << endl;
            data = command.substr(command.find("(") + 1, command.find(")") - command.find("(") - 1);
            stringstream ss(data);
            // stringstream ss(data);
            string token;
            getline(ss, token, ',');
            ride_num = stoi(token);
            // cout << "CancelRide m hun bc" << endl;
            // heap.cancelRide(ride_num);
            // Node *res = rbt.searchTree(ride_num);
            heap.cancelRide(ride_num);
            rbt.deleteNode(ride_num);
            // heap.print();
        }
    }

    fin.close();

    return 0;
}
