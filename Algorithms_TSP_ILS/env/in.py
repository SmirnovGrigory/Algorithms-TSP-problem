n = int(input())
ar=[]
for i in range(n):
	a, b, c=map(int, input().split())
	ar.append([b, c])
print(n)
for x in ar:
	print(x[0], x[1])
print(*list(range(1000)))
print('-1')