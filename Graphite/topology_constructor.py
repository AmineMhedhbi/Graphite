def print_topology(num):
        arr = [list for x in range(num)]

	for i in range(num):
		arr[i] = [0 for x in range(num)]

	loop = 1
	for i in range(1,num):
		if i>num/2:
			temp = num
		else:
			temp = i
		for j in range(temp):
			changed = False
			for m in range(j,num+j,i):
				l = m%num
				if not (m + i > num + j) and arr[l][(l+i)%num] == 0:
					arr[l][(l+i)%num] = loop
					#print("from "+str(j)+" to "+str(num+j-1) + " by "+str(i) + ", at "+ str(l) + "," + str((l+i)%num))
					changed = True
			if changed:
				loop+=1
				changed = False
				#print(loop)
			for m in range(num+j,j-1,-i):
				l = m%num
				if not (m + i > num + j) and arr[l][(l+num-i)%num] == 0:
					arr[l][(l+num-i)%num] = loop
					#print("from "+str(num+j-1)+" to "+str(j) + " by "+str(-i) + ", at "+ str(l) + "," + str((l+num-i)%num))
					changed = True
			if changed:
				loop+=1
				#print(loop)

	for i in arr:
		row = ""
		for j in i:
			row+=str(j)+" "
		print(row)

if __name__ == "__main__":
	print_topology(2)
	print_topology(4)
	print_topology(8)
	print_topology(16)
	#print_topology(32)
	#print_topology(64)

