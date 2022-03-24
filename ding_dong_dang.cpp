#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int>A;
vector<int>C; //combination vector
int n;
int cnt = 0;

void find_vec(int p, int c_index, int a_index){
	if(p==0){
		int a = C[1]-C[0];
		int b = C[2]-C[1];
		if((a <= b) && (b <= 2*a)){
			cnt++;
		}
	}
	else if(a_index == n){
		return;
	}
	else{
		C[c_index] =A[a_index];
		find_vec(p-1, c_index+1, a_index+1);
		find_vec(p, c_index, a_index+1);
	}
}
int main() {
	int num;
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> num;
		A.push_back(num);
	}
	
	C.push_back(0);
	C.push_back(0);
	C.push_back(0);
	
	sort(A.begin(), A.end());
	
	find_vec(3,0,0);
	cout << cnt;
}
