#pragma once
#include<vector>
using namespace std;
class Node {
public:
	bool lwall, rwall, upwall, downwall;
	int id;
	int row;
	int line;
	Node(int _id);
	int visittime;
	int step;
	bool isShortestPath;
};
Node::Node(int _id) :lwall(false), rwall(false), upwall(false), downwall(false), id(_id), visittime(-1),step(0),isShortestPath(false){
}
class Maze {
public:
	int r, c;
	vector<vector<Node>> Nodes;
	Maze(int _r, int _c);
};
Maze::Maze(int _r, int _c) :r(_r), c(_c),Nodes(vector<vector<Node>>(_r)){
	for (int i = 0; i < _r ; ++i) {
		for (int j = 0; j < _c; ++j) {
			Node tem(i * c + j);
			tem.row = i;
			tem.line = j;
			Nodes[i].push_back(tem);
		}
	}
}