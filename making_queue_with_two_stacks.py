answer = []
list_a = []
list_b = []

def deq():
	if(len(list_a)>0 and len(list_b)==0):
		while(True):
			list_b.append(list_a.pop())
			if(len(list_a)==0):
				answer.append(list_b.pop())
				break
	elif(len(list_b)>0):
		answer.append(list_b.pop())
		return
	else:
		answer.append("EMPTY")
		return


while(True):
	a = input()
	if(a=="exit"):
		break
	elif(a[0]=='d'):
		deq()
	else:
		num = int(a.split()[1])
		list_a.append(num)
		

for i in range(0, len(answer)):
	print(answer[i])
  
