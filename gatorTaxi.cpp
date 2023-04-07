    #include <iostream>
    #include <bits/stdc++.h>


    using namespace std;

    struct ride{
        int ride_number;
        int ride_cost;
        int trip_duration;
    };

    // struct minHeap{
    //     int *arr; //let's use vector<ride> arr;
    //     int size;
    //     int capacity; //can change this again now for vector implementation
    // };

    // int parent_heap(int i){
    //     return (i-1)/2;
    // }

    // int left_heap_child(int i){
    //     return (2*i+1);
    // }

    // int right_heap_child(int i){
    //     return (2*i+2);
    // }

    
    // int get_min(minHeap* heap) {
    //     // Return the root node element,
    //     // since that's the minimum, by the min-heap
    //     // property
    //     return heap->arr[0];
    // }  

//changed the code from a struct to class. 
class MinHeap {
private:
    vector<ride> heap;

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
    void cancelRide(int ride_num) {
        // for (int i = 0; i < heap.size(); i++) {
        //     cout << "Ride Number: " << heap[i].ride_number << ", Cost: " << heap[i].ride_cost << ", Duration: " << heap[i].trip_duration << endl;
        // }
        //TO DO: implement the delete
         cout<< "deleting Ride" <<endl;
         cout << ride_num <<endl;
         for (int i = 0; i < heap.size(); i++) {
            if (heap[i].ride_number == ride_num) {
                cout << heap[i].ride_number << " " <<heap[i].ride_cost << endl;
                heap[i] = heap.back();
                heap.pop_back();
                heapify(i);
                break;
            }
        }
        cout<< "inside cancel Ride" <<endl;
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
// int main() {
//     MinHeap heap;
//     ride r1 = {1, 10, 20};
//     ride r2 = {2, 5, 30};
//     ride r3 = {3, 15, 25};
//     heap.insert(r1);
//     heap.insert(r2);
//     heap.insert(r3);
//     heap.print(); // Output: Ride Number: 1, Cost: 10, Duration: 20
//                   //         Ride Number: 2, Cost: 5, Duration: 30
//                   //         Ride Number: 3, Cost: 15, Duration: 25
//     ride min_ride = heap.extractMin();
//     cout << "Min Ride: Ride Number: " << min_ride.ride_number << ", Cost: " << min_ride.ride_cost << ", Duration: " << min_ride.trip_duration << endl; // Output: Min Ride: Ride Number: 2, Cost: 5, Duration: 30
//     cout << "Next Min Cost: " << heap.getMin().ride_cost << endl; // Output: Next Min Cost: 10
//     return 0;
// }


    int main(int argc, char** argv) {
        cout << "welcome to the gator taxi\n";
        if (argc != 2) {
            cout << "Usage: " << argv[0] << " input_file" << endl;
            return 1;
        }

        // string input_file = argv[1];
        
        ifstream fin(argv[1]);

        if (!fin.is_open()) {
            cout << "Unable to open input file" << endl;
            return 1;
        }
        cout << "dekho" <<endl;
        // map<int, tuple<int, int>> redBlackTree; //ride number, tuple = ride cost and trip duration. //can't use this as of now.
        MinHeap heap; //initialized heap at this point

        string command;
        string line;
        int count =1;
    while (getline(fin, line)) {
        stringstream ss(line);
       
        string command,data;
        ss >> command;
        // cout << command <<endl;
        int ride_num, ride_cost, trip_duration;
        
        if (command.find("Insert")!= string::npos) {
            // cout<<command<<endl;
            // cout << count++ << endl;
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
            // cout << "Command: " << command << endl;
            // cout << "Ride Number: " << ride_num << endl;
            // cout << "Ride Cost: " << ride_cost << endl;
            // cout << "Trip Duration: " << trip_duration << endl;
            
            // char dummy;
            // ss >> dummy >> ride_num >> dummy >> ride_cost >> dummy >> trip_duration >> dummy;

            // TODO: implement Insert command
        } else if (command.find("Print")!= string::npos) {
            cout << "print m hun bc"<< endl;
            // heap.print();
            // char dummy;
            // ss >> dummy >> ride_num;
            // TODO: implement Print command
        } else if (command == "UpdateTrip") {
            cout << "UpdateTrip m hun bc"<< endl;
            char dummy;
            ss >> dummy >> ride_num >> dummy >> trip_duration >> dummy;
            // TODO: implement UpdateTrip command
        } else if (command.find("GetNextRide")!= string::npos) {
            heap.getMin();
            cout << "GetNextRide m hun bc"<< endl;
            // TODO: implement GetNextRide command
        } else if (command.find("CancelRide")!=string::npos) {
            cout << command<<endl;
            data = command.substr(command.find("(") + 1, command.find(")") - command.find("(") - 1);
            stringstream ss(data);
            // stringstream ss(data);
            string token;
            getline(ss, token, ',');
            ride_num = stoi(token);
            cout << "CancelRide m hun bc"<< endl;
            heap.cancelRide(ride_num);
            heap.print();
            // char dummy;
            // ss >> dummy >> ride_num >> dummy;
            // TODO: implement CancelRide command
        }
    }
        

        fin.close();

        return 0;
    }



// int main() {
//     cout << "Welcome to the gator Taxi app\n" << endl;
    // map<int, tuple<int, int>> redBlackTree; //ride number, tuple = ride cost and trip duration.
    // priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> minHeap; //tuple conatains all three
    
//     return 0;
// }

// cout << "expecting a command\n";
        // while (getline(fin, line)) {
        // string command = line.substr(0, line.find('('));
        // // remove whitespace
        // command.erase(remove_if(command.begin(), command.end(), ::isspace), command.end());
        // cout << command << endl;

        // // extract arguments
        // istringstream iss(line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1));
        // vector<string> args;
        // string arg;
        //         while (getline(iss, arg, ',')) {
        //             cout << arg<<endl;
        //             args.push_back(arg);
        //         }
        //     cout << command << endl;
        //     if (command == "Insert") {
        //         fin >> ride_num >> ride_cost >> trip_duration;
        //         cout << ride_num << " " << ride_cost << " " <<trip_duration << " " << endl;
        //         if (redBlackTree.find(ride_num) != redBlackTree.end()) {
        //             cout << "Duplicate RideNumber" << endl;
        //         } else {
        //             cout << "here\n";
        //             auto ride1 = make_tuple(ride_cost, trip_duration);
        //             auto ride2 = make_tuple(ride_cost, ride_num, trip_duration);
        //             redBlackTree[ride_num] = ride1;
        //             minHeap.push(ride2);
        //         }
        //     }
        //     else if (command == "Print") {
        //     //     fin >> ride_num;
        //     //     if (redBlackTree.find(ride_num) != redBlackTree.end()) {
        //     //         auto ride = redBlackTree.find(ride_num);
        //     //         cout << "(" << ride.first << "," << get<1>(ride.second) << "," << get<2>(ride.second) << ")" << endl;
        //     //     } else {
        //     //         cout << "(0,0,0)" << endl;
        //     //     }
        //     //  }
        //     // else if (command == "UpdateTrip") {
        //     //     fin >> ride_num >> trip_duration;
        //     //     if (redBlackTree.contains(ride_num)) {
        //     //         auto ride = redBlackTree.find(ride_num);
        //     //         auto new_ride = make_tuple(ride_num, get<1>(ride.second), trip_duration);
        //     //         redBlackTree.update(ride_num, new_ride);
        //     //         minHeap.update(ride_num, new_ride);
        //     //     }
        //     cout << "inside print statement but not doing anything\n";
        //     }
        //     else if (command == "GetNextRide") {
        //         // auto ride = minHeap.extract_min();
        //         // if (ride) {
        //         //     cout << "(" << get<0>(*ride) << "," << get<1>(*ride) << "," << get<2>(*ride) << ")" << endl;
        //         //     redBlackTree.remove(get<0>(*ride));
        //         // } else {
        //         //     cout << "No active ride requests" << endl;
        //         // }
        //         cout << "inside the getNextRide function\n";
        //     } else if (command == "CancelRide") {
        //         // fin >> ride_num;
        //         // if (redBlackTree.contains(ride_num)) {
        //         //     redBlackTree.remove(ride_num);
        //         //     minHeap.remove(ride_num);
        //         // }
        //         cout << "inside the cancel ride conditions\n";
        //     } else if (command == "PrintRange") {
        //         // int ride_num1, ride_num2;
        //         // fin >> ride_num1 >> ride_num2;
        //         // auto rides = redBlackTree.in_order_range_query(ride_num1, ride_num2);
        //         // int cnt = 0;
        //         // for (auto ride : rides) {
        //         //     cout << "(" << ride.first << "," << get<1>(ride.second) << "," << get<2>(ride.second) << ")";
        //         //     if (++cnt < rides.size()) {
        //         //         cout << ",";
        //         //     }
        //         // }
        //         cout <<  "print Range\n";
        //         cout << endl;
        //     }
        // }