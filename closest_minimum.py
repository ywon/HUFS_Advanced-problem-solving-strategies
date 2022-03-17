n = int(input())
A = list(map(int, input().split()))
stack = []
B = []
B.append(0)
stack.append(0)

for i in range(1, n):
	if(A[i-1] < A[i]):
		B.append(A[i-1])
		stack.append(A[i-1])
	else:
		for j in range(len(stack)-1,-1,-1):
			if(stack[j]<A[i]):
				B.append(stack[j])
				break
					

for i in range(0, n):
	print(B[i], end=' ')
