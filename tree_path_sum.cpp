#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <array>
using namespace std;

vector<int> cost_pre;
vector<int> index_pre;
vector<int> path_sum;
vector<int> FT;
vector<int> diff;
vector<int> range_vec;

void dfs_preorder(vector<int> tree[], int start, bool visited[]) { //dfs preorder 순회
	visited[start] = 1;
	index_pre.push_back(start);
	for (int i = 0; i < tree[start].size(); i++) {
		int j = tree[start][i];
		if (visited[j] != true) {
			dfs_preorder(tree, j, visited);
		}
	}
}

void make_path_sum(vector<int> tree[], int start, bool visited[]) { //path_sum 저장
	visited[start] = 1;
	for (int i = 0; i < tree[start].size(); i++) {
		int j = tree[start][i];
		int pos_j = find(index_pre.begin(), index_pre.end(), j) - index_pre.begin();
		int pos_s = find(index_pre.begin(), index_pre.end(), start) - index_pre.begin();
		path_sum[pos_j] = path_sum[pos_s]+cost_pre[pos_j+1];
		if (visited[j] != true) {
			make_path_sum(tree, j, visited);
		}
	}
}

void dfs_preorder_r(vector<int> tree[], int start, bool visited[]){
	visited[start] = 1;
	range_vec.push_back(start);
	for(int i=0;i<tree[start].size();i++){
		int j = tree[start][i];
		if(visited[j]!=true){
			dfs_preorder_r(tree, j, visited);
		}
	}
}

int query_sum(int index) { //root부터의 합 구하기
	int ans = 0;
	while (index > 0) {
		ans = ans + FT[index];
		index = index - (index & -index);
	}
	return ans;
}


void query_update(int index, int value) //펜윅 트리 update
{
	while (index < FT.size())
	{
		FT[index] = FT[index] + value;
		index = index + (index & -index);
	}
}

void make_Fenwick_tree(int n) { //펜윅 트리 생성
	for (int i = 1; i < n + 1; i++) {
		query_update(i, diff[i-1]);
	}
}

int main() {
	int n,q;
	int a,b,c;	
	int range;
	string query;
	
	cin >> n >> q;
	
	vector<string> s;
	vector<int> tree[n+1];
	vector<int> cost;
	bool visited_pre[n+1]={0,};
	bool visited[n+1]={0,};
	bool visited_r[n+1]={0,};
	
	cost.push_back(0);
	cost_pre.push_back(0);
	
	for(int i=0;i<n;i++){
		cin >> c;
		cost.push_back(c);
		cost_pre.push_back(0);
		path_sum.push_back(0);
	}
	
	for (int i = 0; i < n + 1; i++) {
		FT.push_back(0);
	}
	
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		tree[a].push_back(b);
	}
	
	dfs_preorder(tree,1,visited_pre);
	
	for (int i = 0; i < index_pre.size(); i++) {
		cost_pre[i + 1] = cost[index_pre[i]];
	}

	path_sum[0] = cost_pre[1];
	
	make_path_sum(tree,1,visited);
	
	diff.push_back(path_sum[0]);
	
	for(int i=0;i<n-1;i++){
		diff.push_back(path_sum[i+1]-path_sum[i]);
	}
	
	make_Fenwick_tree(n);

	string buffer;

	while (q >= 0) {
		getline(cin, query);
		istringstream iss(query);
		while (getline(iss, buffer, ' ')) {
			s.push_back(buffer);
		}
		if(query[0]=='s'){
			int pos_s = find(index_pre.begin(), index_pre.end(), stoi(s[1])) - index_pre.begin();
			cout << query_sum(pos_s+1) << endl;
		}
		if(query[0]=='u'){
			int pos_u = find(index_pre.begin(), index_pre.end(), stoi(s[1])) - index_pre.begin();
			dfs_preorder_r(tree,stoi(s[1]),visited_r);
			range = range_vec.size();
			query_update(pos_u+1, stoi(s[2]));
			query_update(pos_u+range+1, -stoi(s[2]));
			for(int i=0;i<n+1;i++){
				visited_r[i]=0;
			}
			range_vec.clear();
		}
		s.clear();
		q--;
	}
} 
