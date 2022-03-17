#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define INF 12345678
using namespace std;
vector<int> A;
vector<int> tree;
vector<int> B;

void segment_tree(int node, int start, int end){
	if(start==end){
		tree[node] = A[start];
		return;
	}
	else{
		segment_tree(2*node,start, (start+end)/2);
		segment_tree(2*node+1 , (start+end)/2+1, end);
		tree[node] = min(tree[2*node], tree[2*node+1]);
		return;
	}
}

int find_min(int node, int start, int end, int left, int right){
	if(left<=start && end<=right){
		return tree[node];
	}
	if(left>end || right<start){
		return INF;
	}
	
	int a = find_min(2*node, start, (start+end)/2, left, right);
	int b = find_min(2*node+1, (start+end)/2+1, end, left, right);
	return min(a,b);
}

int main() {
	int n, k, num;
	cin >> n >> k;
	int tree_num = pow(2, ceil(log2(n))+1);
	
	for(int i=0;i<tree_num;i++){ //트리 0으로 초기화
		tree.push_back(0);
	}
	
	for(int i=0;i<n;i++){
		cin >> num;
		A.push_back(num);
	}
	
	segment_tree(1,0,n-1); //트리 만들기
	
	for(int i=0;i<n-k+1;i++){
		B.push_back(find_min(1,0,n-1,i,i+k-1)); //최솟값 찾아서 B에 저장
	}
	
	for(int i=0;i<B.size();i++){
		cout << B[i] << " ";
	}

}
