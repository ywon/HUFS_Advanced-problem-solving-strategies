#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <array>
using namespace std;

vector<int> cost_pre;
vector<int> index_pre; 
vector<int> FT;
vector<int> range_vec;

void dfs_preorder(vector<int> tree[], int start, bool visited[]){ //dfs preorder 순회
	visited[start] = 1;
	index_pre.push_back(start);
	for(int i=0;i<tree[start].size();i++){
		int j = tree[start][i];
		if(visited[j]!=true){
			dfs_preorder(tree, j, visited);
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

int partial_sum(int index){ //1부터 index까지의 부분합 구하기
	int ans = 0;
	while (index > 0){
		ans = ans + FT[index];
		index = index - (index & -index);
	}
	return ans;
}

int query_subtree(int index,int range){ //subtree의 cost 구하기
	int pos = find(index_pre.begin(), index_pre.end(), index) - index_pre.begin();
	
	if(index==1){
		return partial_sum(index_pre.size());
	}
	else{
		return partial_sum(pos+range) - partial_sum(pos);
	}
}

void query_update(int index, int value) //펜윅 트리 update
{
	while (index < FT.size())
	{
		FT[index] = FT[index] + value;
		index = index + (index & -index);
	}
}

void make_Fenwick_tree(int n){ //펜윅 트리 생성
	for(int i=1;i<n+1;i++){
		query_update(i, cost_pre[i]);
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
		
	cost.push_back(0);
	cost_pre.push_back(0);
	
	for(int i=0;i<n;i++){
		cin >> c;
		cost.push_back(c);
		cost_pre.push_back(0);
	}
	
	for(int i=0;i<n+1;i++){
		FT.push_back(0);
	}
		
	for(int i=0;i<n-1;i++){
		cin >> a >> b;
		tree[a].push_back(b);
	}
		
	dfs_preorder(tree,1,visited_pre);

	for(int i=0;i<index_pre.size();i++){
		cost_pre[i+1] = cost[index_pre[i]];
	}
	
	make_Fenwick_tree(n);//펜윅트리 생성
	
	string buffer;
	
	while(q>=0){
		getline(cin,query);
		istringstream iss(query);
		while (getline(iss, buffer, ' ')){
			s.push_back(buffer);
		}
		if(query[0]=='s'){
			dfs_preorder_r(tree,stoi(s[1]),visited);
			range = range_vec.size();
			cout << query_subtree(stoi(s[1]),range) << endl;
			for(int i=0;i<n+1;i++){
				visited[i]=0;
			}
			range_vec.clear();
		}
		if(query[0]=='u'){
			int up = find(index_pre.begin(), index_pre.end(), stoi(s[1])) - index_pre.begin();
			query_update(up+1, stoi(s[2]));
		}
		s.clear();
		q--;
	}
	
}
