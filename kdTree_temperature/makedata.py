import random

hi = 10
n = random.randint(1, hi)
m = random.randint(1, hi)
print(n)
min = -10
max = 10
sup = 10000
for _ in range(n):
	print(random.randint(min, max), random.randint(min, max), random.randint(0, sup))
print(m)
for _ in range(m):
	a = random.randint(min, max - 1)
	b = random.randint(min, max - 1)
	print(a, random.randint(a + 1, max), b, random.randint(b + 1, max))
		
