#pragma once
#include<iostream>
using namespace std;
int myfind(int NodeNum,int parent[]) {
	if (parent[NodeNum] != NodeNum) return myfind(parent[NodeNum], parent);
	return NodeNum;
}
void init(int parent[], int height[],int size) {
	for (int i = 0; i < size; ++i) parent[i] = i,height[i]=1;
}
void Un(int parent[], int height[], int Node1, int Node2) {
	Node1 = myfind(Node1, parent);
	Node2 = myfind(Node2, parent);
	if (height[Node1] > height[Node2]) {
		parent[Node2] = Node1;
	}
	else {
		parent[Node1] = Node2;
		if (height[Node1] == height[Node2]) {
			height[Node2]++;
		}
		//cout << parent[parentOfNode2] << " " << parentOfNode1 << endl;
	}
}