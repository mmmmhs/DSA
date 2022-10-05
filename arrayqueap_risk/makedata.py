import random

n = 20
m = 5
hi = 100
print(n)
for i in range(n):   
	print(random.randint(1, hi), end = " ")
print("")	
r = -1 			
for i in range(n):  
	r = random.randint(r, i - 1)
	print(i - r, end = " ")
print("")	
print(m)
for i in range(m):
	a = random.randint(1, hi)
	print(a, random.randint(a, hi))
print("")	
