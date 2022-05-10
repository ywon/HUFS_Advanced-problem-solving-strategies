#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> index_pre;
vector<int> index_post;

void dfs_preorder(vector<int> tree[], int start, bool visited[]){ //dfs preorder 순회 함수
	visited[start] = 1;
	index_pre.push_back(start);
	for(int i=0;i<tree[start].size();i++){
		int j = tree[start][i];
		if(visited[j]!=true){
			dfs_preorder(tree, j, visited);
		}
	}
}

void dfs_postorder(vector<int> tree[], int start, bool visited[]){ //dfs postorder 순회 함수
	visited[start] = 1;
	for(int i=0;i<tree[start].size();i++){
		int j = tree[start][i];
		if(visited[j]!=true){
			dfs_postorder(tree, j, visited);
		}
	}
	index_post.push_back(start);
	
}
bool query_ancestor(int u, int v){
	if(u==v){
		return true;
	}
	int pre_ancestor = find(index_pre.begin(), index_pre.end(), u) - index_pre.begin();
	int pre_child = find(index_pre.begin(), index_pre.end(), v) - index_pre.begin();
	int post_ancestor = find(index_post.begin(), index_post.end(), u) - index_post.begin();
  int post_child = find(index_post.begin(), index_post.end(), v) - index_post.begin();
	
	if(pre_ancestor < pre_child and post_ancestor > post_child){
		return true;
	}
	else{
		return false;
	}
	
}

int main() {
	int a,b;
	int n, q;
	int count = 0;
	cin >> n >> q;
	
	vector<int> tree[n+1];
	vector<int> index;
	bool visited_pre[n+1]={0,};
	bool visited_post[n+1]={0,};
	
	for(int i=0;i<n-1;i++){
		cin >> a >> b;
		tree[a].push_back(b);
	}

	dfs_preorder(tree,1,visited_pre);	
	dfs_postorder(tree,1,visited_post);	
	
	for(int i=0;i<q;i++){
		cin >> a >> b;
		if(query_ancestor(a,b)==true){
			count++;
		}
	}
	
	cout << count;
}
