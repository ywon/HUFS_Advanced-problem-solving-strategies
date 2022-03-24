#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> board;

int total = 0;
void find_loc(int row, int col){
	for(int i=0;i<n;i++){
		if(row==i){ //같은 행인지 확인
			continue;
		}
		for(int j=0;j<n;j++){
			if((col == j) || (abs(row-i) == abs(col-j))){ //같은 열인지 + 같은 대각선 위인지 확인
				continue;
			}
			else{
				total++;
			}
		}
	}
}
int main() {
	cin >> n;
	
	for(int i=0;i<n;i++){
		board.push_back(0);
	}
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			board[i] = j;
			find_loc(i, board[i]);
		}
	}
	cout << total / 2;
}
