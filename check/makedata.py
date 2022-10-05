import random
	
hi = 10
n = random.randint(2, hi)
k = random.randint(0, hi)
print(n, k)
for _ in range(n):
	for __ in range(64):
		print(random.randint(1,1), end = "")
	print("")