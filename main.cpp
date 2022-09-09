#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;


const int dx[4]{ 0,0,1,-1 };
const int dy[4]{ 1,-1,0,0 };
struct Boundries {
	int startRow, endRow;
	int startCol, endCol;
	Boundries() : startRow{ INT_MAX }, endRow{ INT_MIN }, startCol{ INT_MAX }, endCol{ INT_MIN }{}
	Boundries(int _startRow, int _endRow, int _startCol, int _endCol) :
		startRow{ _startRow }, endRow{ _endRow }, startCol{ _startCol }, endCol{ _endCol }{}
};
string hashIsland(const vector<vector<int>>& mat, const Boundries& b) {
	string hash{};
	char rowCtn = '1';
	for (int i = b.startRow; i <= b.endRow; ++i) {
		for (int j = b.startCol; j <= b.endCol; ++j) {
			if (mat[i][j] == 0)
				hash += '0';
			else
				hash += rowCtn;
		}
		++rowCtn;
	}
	return hash;
}
void setBoundries(Boundries* b, int row, int col) {
	b->startRow = min(b->startRow, row);
	b->endRow = max(b->endRow, row);
	b->startCol = min(b->startCol, col);
	b->endCol = max(b->endCol, col);
}
bool valid(const vector<vector<int>>& mat, int row, int col) {
	return row >= 0 && row < mat.size() && col >= 0 && col < mat[0].size();
}
void dfs(const vector<vector<int>>& mat, vector<vector<bool>>& visited, int row, int col, Boundries* b) {
	if (!valid(mat, row, col) || mat[row][col] == 0 || visited[row][col]) return;
	visited[row][col] = true;
	setBoundries(b, row, col);
	for (int i = 0; i < 4; ++i) {
		dfs(mat, visited, row + dx[i], col + dy[i], b);
	}
}
int uniqueIslands(const vector<vector<int>>& mat) {
	const int n = mat.size();
	const int m = mat[0].size();
	vector<vector<bool>> visited(n, vector<bool>(m));
	unordered_set<string> seen{};
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (mat[i][j] == 1 && !visited[i][j]) {
				Boundries* b = new Boundries();
				dfs(mat, visited, i, j, b);
				seen.insert(hashIsland(mat, *b));
				delete b;
			}
		}
	}
	return seen.size();
}

int main() {
	vector<vector<int>> mat{
		{0,1,1,0,1,1},
		{0,0,0,0,1,0},
		{0,0,1,0,0,0},
		{0,1,1,0,1,1},
	};
	cout << uniqueIslands(mat); // 3
}
