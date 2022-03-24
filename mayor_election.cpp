#include <iostream>
#include <vector>
using namespace std;
int main() {
	vector<int> count;
	int n, num;
	cin >> n;
	
	for(int i=0;i<n+1;i++){
		count.push_back(0);
	}
	
	for(int i=1;i<n+1;i++){
		cin >> num;
		count[num]++;
	}
	int max = 0;
	int pick = -1;
	for(int i=1;i<n+1;i++){
		if(count[i]>max){
			max = count[i];
			pick = i;
		}
	}
	
	if(max > n/2){
		cout << pick;
	}
	else{
		cout << -1;
	}
	
}
