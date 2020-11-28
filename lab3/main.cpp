#include<iostream>
#include<vector>
#include<time.h>
#include<queue>
#include<unordered_set>
#include"unionfound.h"
#include"Maze.h"
using namespace std;
int go1[] = { 0,0,1,-1 };
int go2[] = { 1,-1,0,0 };
bool check(int parent[],int size) {
	///bool allconnect = true;
	///
	int c = myfind(0,parent);
	for (int i = 1; i < size; ++i) if (myfind(i,parent) != c) return false;
	return true;
}
void PrintMaze(const Maze & maze,int parent[],const vector<int> & lines,int r,int c) {
	cout << "+  ";
	for (int j = 1; j < c; ++j) cout << "+--";
	cout << "+\n";
	for (int i = 0; i < r; ++i) {
		cout << "|";
		for (int j = 0; j < c - 1; ++j) {
			if (maze.Nodes[i][j].visittime > 0) printf("%2d", maze.Nodes[i][j].visittime);
			else printf("  ");
			if (maze.Nodes[i][j].rwall==false) cout << "|";
			else cout << " ";
		}
		if (maze.Nodes[i][c-1].visittime > 0) printf("%2d", maze.Nodes[i][c - 1].visittime);
		else printf("  ");
		cout  << "|\n";
		if (i < r - 1) {
			for (int j = 0; j < c; ++j) {
				if (maze.Nodes[i][j].downwall == false) cout << "+--";
				else cout << "+  ";
			}
			cout << "+\n";
		}
	}
	for (int j = 0; j < c-1; ++j) cout << "+--";
	cout << "+ ";
	/*for (int i = 0; i < r * c; ++i) {
		cout << "parent of " << i << "=" << myfind(i, parent) << endl;
	}*/
}
void InitMaze(Maze & maze,int height[],int parent[],vector<int>& lines, int r,int c) {
	int totallines = 2 * r * c - r - c;
	while (1) {
		int line = rand() % totallines;
		//cout << "line=" << line << "\n";
		if (line <= r * (c - 1) - 1) {
			//shubian
			int lhs = line / (c - 1) * c + line % (c - 1), rhs = lhs + 1;
			//int lhsp = myfind(lhs, parent), rhsp = myfind(rhs, parent);
			//cout << "lhsp=" << lhsp << "rhsp" << rhsp << endl;
			if (myfind(lhs, parent) != myfind(rhs, parent)) {
				//cout << "lhs=" << lhs << "rhs=" << rhs << "\n";
				Un(parent, height, lhs, rhs);
				lines[line] = 0;
				int nowr = lhs / c, nowl = lhs % c;
				maze.Nodes[nowr][nowl].rwall = true;
				maze.Nodes[nowr][nowl+1].lwall = true;
				//NumsConnected.insert(lhs);
				//NumsConnected.insert(rhs);
			}
		}
		else {
			int up = line - (r * (c - 1)), down = up + c;
			if (myfind(up, parent) != myfind(down, parent)) {
				//cout << "up=" << up << "down=" << down << "\n";
				Un(parent, height, up, down);
				lines[line] = 0;
				int nowr = up / c, nowl = up % c;
				maze.Nodes[nowr][nowl].downwall = true;
				maze.Nodes[nowr+1][nowl].upwall = true;
				//NumsConnected.insert(up);
				//NumsConnected.insert(down);
			}
		}
		if (check(parent, r * c)) break;
	}
}
void bfs(Maze & maze, int r, int c) {
	int time = 0;
	int _step = -1;
	queue<Node *> q;
	q.push(&maze.Nodes[0][0]);
	while (!q.empty()) {
		Node  * tem = q.front();
		++time;
		tem->visittime = time;
		//cout << "now row=" << tem->row << "now line=" << tem->line << endl;
		if (tem->row == r - 1 && tem->line == c - 1) return;
		q.pop();
		//int temr = tem.row, teml = tem.line;
		if (tem->rwall == true) {
			int temr = tem->row+go1[0], teml = tem->line+go2[0];
			if (temr < r && teml < c && temr >= 0 && teml >= 0 && maze.Nodes[temr][teml].visittime < 0) {
				q.push(&maze.Nodes[temr][teml]);
				maze.Nodes[temr][teml].step = tem->step + 1;
			}
		}
		if (tem->lwall == true) {
			int temr = tem->row + go1[1], teml = tem->line + go2[1];
			if (temr < r && teml < c && temr >= 0 && teml >= 0 && maze.Nodes[temr][teml].visittime < 0) {
				q.push(&maze.Nodes[temr][teml]);
				maze.Nodes[temr][teml].step = tem->step + 1;
			}
		}
		if (tem->downwall == true) {
			int temr = tem->row + go1[2], teml = tem->line + go2[2];
			if (temr < r && teml < c && temr >= 0 && teml >= 0 && maze.Nodes[temr][teml].visittime < 0) {
				q.push(&maze.Nodes[temr][teml]);
				maze.Nodes[temr][teml].step = tem->step + 1;
			}
		}
		if (tem->upwall == true) {
			int temr = tem->row + go1[3], teml = tem->line + go2[3];
			if (temr < r && teml < c && temr >= 0 && teml >= 0 && maze.Nodes[temr][teml].visittime < 0) {
				q.push(&maze.Nodes[temr][teml]);
				maze.Nodes[temr][teml].step = tem->step + 1;
			}
		}
	}
}
void BackToBegin(Maze& maze, int r, int c) {
	queue<Node*> q;
	q.push(&maze.Nodes[r-1][c-1]);
	maze.Nodes[r - 1][c - 1].isShortestPath = true;
	while (!q.empty()) {
		Node* tem = q.front();
		//cout << "now row=" << tem->row << "now line=" << tem->line << endl;
		if (tem->row == 0 && tem->line == 0) return;
		q.pop();
		//int temr = tem.row, teml = tem.line;
		if (tem->rwall == true) {
			int temr = tem->row + go1[0], teml = tem->line + go2[0];
			if (temr < r && teml < c && temr >= 0 && teml >= 0 && maze.Nodes[temr][teml].step==tem->step-1) {
				q.push(&maze.Nodes[temr][teml]);
				maze.Nodes[temr][teml].isShortestPath = true;
				continue;
				//maze.Nodes[temr][teml].step = tem->step + 1;
			}
		}
		if (tem->lwall == true) {
			int temr = tem->row + go1[1], teml = tem->line + go2[1];
			if (temr < r && teml < c && temr >= 0 && teml >= 0 && maze.Nodes[temr][teml].step == tem->step - 1) {
				q.push(&maze.Nodes[temr][teml]);
				maze.Nodes[temr][teml].isShortestPath = true;
				continue;
				//maze.Nodes[temr][teml].step = tem->step + 1;
			}
		}
		if (tem->downwall == true) {
			int temr = tem->row + go1[2], teml = tem->line + go2[2];
			if (temr < r && teml < c && temr >= 0 && teml >= 0 && maze.Nodes[temr][teml].step == tem->step - 1) {
				q.push(&maze.Nodes[temr][teml]);
				maze.Nodes[temr][teml].isShortestPath = true;
				continue;
				//maze.Nodes[temr][teml].step = tem->step + 1;
			}
		}
		if (tem->upwall == true) {
			int temr = tem->row + go1[3], teml = tem->line + go2[3];
			if (temr < r && teml < c && temr >= 0 && teml >= 0 && maze.Nodes[temr][teml].step == tem->step - 1) {
				q.push(&maze.Nodes[temr][teml]);
				maze.Nodes[temr][teml].isShortestPath = true;
				continue;
				//maze.Nodes[temr][teml].step = tem->step + 1;
			}
		}
	}
}
void PrintRoad(const Maze& maze, int parent[], const vector<int>& lines, int r, int c) {
	cout << "+  ";
	for (int j = 1; j < c; ++j) cout << "+--";
	cout << "+\n";
	for (int i = 0; i < r; ++i) {
		cout << "|";
		for (int j = 0; j < c - 1; ++j) {
			if (maze.Nodes[i][j].isShortestPath) printf(" *");
			else printf("  ");
			if (maze.Nodes[i][j].rwall == false) cout << "|";
			else cout << " ";
		}
		if (maze.Nodes[i][c - 1].isShortestPath) printf(" *");
		else printf("  ");
		cout << "|\n";
		if (i < r - 1) {
			for (int j = 0; j < c; ++j) {
				if (maze.Nodes[i][j].downwall == false) cout << "+--";
				else cout << "+  ";
			}
			cout << "+\n";
		}
	}
	for (int j = 0; j < c - 1; ++j) cout << "+--";
	cout << "+ ";
}
int main() {
	//cout << "cout r and c\n";
	int r=3, c=4;
	Maze maze(r, c);
	//cin >> r >> c;
	const int n = 100;
	int parent[n];
	int height[n];
	init(parent, height, n);
	/*while (1) {
		int choose = 0;
		cout << "make ur choose\n 1 for union 2 for find";
		cin >> choose;
		if (choose == 1) {
			cout << "cin the 2 nodes u want to union\n";
			int n1, n2;
			cin >> n1 >> n2;
			Un(parent, height, n1, n2);
		}
		else if (choose == 2) {
			cout << "cin the 2 nodes u want to find\n";
			int n1, n2;
			cin >> n1 >> n2;
			int n1p = myfind(n1, parent);
			int n2p = myfind(n2, parent);
			//cout << "n1p=" << n1p << "n2p=" << n2p << endl;
			if (n1p==n2p) cout << "the same\n";
			else cout << "not the same\n";
		}
		else break;
	}*/
	int totallines = 2 * r * c - r - c;
	vector<int> lines(totallines, 1);//前 r*(c-1) 竖边 ， 后(r-1)*c 横边
	srand(unsigned(time(NULL)));
	unordered_set<int> NumsConnected;
	NumsConnected.insert(0);
	NumsConnected.insert(r*c-1);
	InitMaze(maze, height, parent, lines, r, c);
	PrintMaze(maze,parent, lines, r, c);
	bfs(maze, r, c);
	std::cout << "\n";
	PrintMaze(maze, parent, lines, r, c);
	cout << "\nshortest path is" << maze.Nodes[r - 1][c - 1].step<<endl;
	BackToBegin(maze, r, c);
	PrintRoad(maze, parent, lines, r, c);
	return 0;
}