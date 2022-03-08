def solve(A):
	for i in range (0, len(A)-1):
		if(i%2==0): #짝->홀
			if(A[i]<A[i+1]):
				continue
			else:
				temp = A[i]
				A[i] = A[i+1]
				A[i+1] = temp
		else : #홀->짝
			if(A[i]>A[i+1]):
				continue
			else:
				temp = A[i]
				A[i] = A[i+1]
				A[i+1] = temp
	
	return A

def check(B):
	if not (B[0] <= B[1]): return False
	for i in range(1, len(B)-1):
		if i%2 == 1 and not (B[i] >= B[i+1]):
			return False
		if i%2 == 0 and not (B[i] <= B[i+1]):
			return False
	return True		
	
A = [int(x) for x in input().split()]
B = solve(A)
print(check(B))
