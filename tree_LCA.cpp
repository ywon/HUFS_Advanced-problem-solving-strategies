#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> tour;
vector<int> depth_;
vector<int> input;
int depth;
vector<int> ST; //segment tree

void dfs_preorder(vector<int> tree[], int start, bool visited[]) {
	visited[start] = 1;
	depth++;
	for (int i = 0; i < tree[start].size(); i++) {
		int j = tree[start][i];
		tour.push_back(start);	
		depth_.push_back(depth);
		if (visited[j] != true) {
			dfs_preorder(tree, j, visited);
			tour.push_back(j);
			depth_.push_back(depth);
		}
		depth--;
	}
}

int make_segment_tree(int node, int start, int end){
	if (start == end) return ST[node] = depth_[start]; 
	int mid = (start + end) / 2;
	return ST[node] = min(make_segment_tree(2 * node, start, mid), make_segment_tree(2 * node + 1, mid + 1, end));	
}

int position(int num){
	int index;
	for(int i=0;i<tour.size();i++){
		if(num==tour[i]){
			index = i;
			break;
		}
	}
	
	return index;
}

int find_min(int node, int start, int end, int left, int right){
	if (end < left || right < start){
		 return 100000;
	}
	if (left <= start && end <= right) {
		return ST[node];
	}
	int mid = (start + end) / 2;
	return min(find_min(2 * node, start, mid, left, right), find_min(2 * node + 1, mid + 1, end, left, right)); 
}

int query_min(int c, int d){
	int index;
	
	for(int i=c;i<=d;i++){
		if(find_min(1,0,depth_.size()-1,c,d)==depth_[i]){
			index = i;
			break;
		}
	}
	return tour[index];
}

int main() {
	int n, q;
	int a,b,c,d;
	depth = 0;
	cin >> n >> q;
	
	vector<int> tree[n + 1];
	bool visited_pre[n + 1] = { 0, };
	
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		tree[a].push_back(b);
	}
		
	dfs_preorder(tree,1,visited_pre);
	tour.push_back(1);
	depth_.push_back(1);

	int seg_tree_size = 1 << ((int)ceil(log2(depth_.size())) + 1);
	for(int i=0;i<seg_tree_size;i++){
		ST.push_back(0);
	}
	
	make_segment_tree(1,0,depth_.size()-1);
	
	for(int i=0;i<q;i++){
		cin >> c >> d;
		if(c==1 || d==1){
			cout << 1 << endl;
		}
		else if(c==d){
			cout << c << endl;
		}
		else{
			int pos_l = position(c);
			int pos_r = position(d);
			if(pos_l<pos_r){
				cout << query_min(pos_l,pos_r) << endl;
			}
			else{
				cout << query_min(pos_r,pos_l) << endl;
			}
		}
	}
}
