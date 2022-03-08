stack_a = []
stack_b = []
answer = []
max = 0

while(True):
	a = input()
	if(a=="exit"):
		break
	elif(a=="pop"):
		if(len(stack_a) == 0):
			answer.append("EMPTY")
		else:
			n = stack_a.pop()
			answer.append(n)
			if(n == max):
				stack_b.pop()
				if(len(stack_b)==0):
					continue
				else:
					max = stack_b[-1]
	elif(a=="max"):
		if(len(stack_a) == 0):
			answer.append("EMPTY")
		else:
			answer.append(max)
	else:
		num = int(a.split()[1])
		if(num >= max):
			max = num
			stack_b.append(max)
		stack_a.append(num)
		
		
for i in range(0, len(answer)):
	print(answer[i])
	
