#include "stdc++.h"
#include<vector>
#include <sstream>
#include <string>
#include<fstream>
#include "Min_Heap.h"
using namespace std;

ofstream out_file("output_file.txt");

int main(int argc, char** argv) {
    ifstream in_file(argv[1]);
    // create a objects for Red black Tree and MinHeap
    RedBlackTree rbt;
    MinHeap heap;
    string s,operation,value;
    vector<int> data;
    getline(in_file, s);
    while(s!="")
    {   
        data.clear();
        stringstream w(s);
        getline(w, operation, '(');
        if(operation != "GetNextRide")
        {
        while(getline(w, value, ','))
        {
            //rideNumber => data[0]; rideCost = data[1]; tripDuration = data[2]
            data.push_back(stoi(value));
        }
        }
        if(operation == "Print") // Print (both cases) loop
        {   
            if(data.size()==1){ // Print(rideNumber) loop
                Node* temp = rbt.searchRide(data[0]);
                if(temp == rbt.getExt_Black()){
                    out_file<<"(0,0,0)";
                }
                else{
                    out_file<<"("<<temp->ride<<","<<temp->cost<<","<<temp->dur<<")";
                }

            }
            else if(data.size()==2){ // Print(ride1, ride2) loop
				vector<string>ans;
                int ride1 = data[0], ride2 = data[1];
				rbt.searchRide(ride1,ride2,ans);
                int n = ans.size();
                if(n!=0){
                    for(int i=0;i<=n-2;i++){
                        out_file<<ans[i]<<",";
                    }
                    out_file<<ans[n-1];
				}
				else{
					out_file<<"(0,0,0)";
                }
            }
        }
        else if(operation == "Insert") // Insert Operation Loop
        {
			 Node *temp = rbt.searchRide(data[0]);
			if (temp == rbt.getExt_Black()) { //checking if the ride number is already present in the active rides 
				Node* insertedNode = rbt.insertRide(data[0],data[1],data[2]);
                heap.insertRide(insertedNode);
                
			}
            else{
                out_file<<"Duplicate RideNumber"; //If ride is already present in active rides, print as Duplicate ride and stop executing
                break;
            }
        }
        else if(operation == "GetNextRide"){ // GetNextRide Operation Loop
            int del_ride = heap.deleteMinCostRide();
                

            if(del_ride == -1){
                out_file<<"No active ride requests";
            }
            else{
                Node* temp = rbt.searchRide(del_ride);
                out_file<<"("<<temp->ride<<","<<temp->cost<<","<<temp->dur<<")";
                rbt.deleteRide(del_ride);
            }
        }
        else if(operation == "CancelRide") // CancelRide Operation Loop
        {
			Node* temp = rbt.searchRide(data[0]);
            if(temp != rbt.getExt_Black())
            {
                heap.deleteRide(temp->heap_index);
			    rbt.deleteRide(data[0]);

            }
                

        }
        else if(operation == "UpdateTrip"){ // Update Trip Operation Loop
            Node* temp = rbt.searchRide(data[0]);
            if(temp!=rbt.getExt_Black())
			{
                int Ride = data[0], newCost = temp->cost+10, newDuration = data[1];
			int oldDuration = temp->dur;
            if(newDuration<=oldDuration){   // Update Trip case 1 (only new duration is updated)
                temp->dur = newDuration;
                heap.heapifyUP(temp->heap_index); // We need to heapify here incase if minheap property is violated
            }
			else{
                Node* temp = rbt.searchRide(Ride);
                heap.deleteRide(temp->heap_index); // Delete the ride for both case 2 and case 3
				rbt.deleteRide(Ride);
				if(newDuration <= 2*oldDuration){
					Node* newNode = rbt.insertRide(Ride, newCost, newDuration); // Insert the ride again with new cost (old cost + 10), new Trip Duration
					heap.insertRide(newNode);
                }
			}
            }
                

        }
    getline(in_file, s);
    if(s!="" && (operation == "Print" || operation == "GetNextRide"))
        out_file<<"\n";
    }
    in_file.close();
    out_file.close();
    return 0;
}