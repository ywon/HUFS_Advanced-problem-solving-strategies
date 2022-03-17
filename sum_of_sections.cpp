#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
	vector<int> A;
	string answer="False";
	
	int n,k,j;
	int num;
	int sum;
	cin >> n >> k;
	for(int i=0;i<n;i++){
		cin >> num;
		A.push_back(num);
	}
	
	
	for(int i=0;i<n;i++){
		sum = 0;
		j=i;
		while(j<=n-1){
			sum+=A[j];
			if(sum==k){
				answer = "True";
				break;
			}
			else if(sum>k){
				break;
			}
			else{
				j++;
			}
		}
		if(answer=="True"){
			break;
		}
	}
	
	cout << answer;
	
}

