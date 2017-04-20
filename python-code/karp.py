
import random
import math


# read input file and store numbers into nums 
def readFile(filename, size):
	file_content = open(filename, "r")
	nums = []
	for line in file_content:
		nums.append(int(line));

	file_content.close()

	return nums


def writeFile(filename, size):
	file_content = open(filename, "w")
	for i in range(size):
		file_content.write(str(random.randint(1, pow(10,12))) + "\n")

	file_content.close()


def randomMove(lst, size):
	result = list(lst)
	i = random.randint(0, size - 1)
	j = random.randint(0, size - 1)

	if (result[i] != j):
		result[i] = j
	return result

def randomSol(size):
	nums = []
	for i in range (size):
		nums.append(random.randint(0, size - 1))
	return nums

def randomMove2(lst, size):
	result = list(lst)
	
	i = random.randint(0, size - 1)
	j = random.randint(0, size - 1)

	while i == j:
		j = random.randint(0, size - 1)

	if random.random() < .5:
		result[i] = -1 * result[i]

	if random.random() < .5:
		result[j] = -1 * result[j]

	return result


def randomSol2(size):
	nums = []
	for i in range(size):
		nums.append(random.choice([-1,1]))

	return nums

def karp2(original_lst, solution, size):
	residue = 0

	for i in range(size):
		residue += solution[i] * original_lst[i]

	return abs(residue)


def karp(nums, size):
	result = list(nums)
	result.sort(reverse=True)
	count = size
	while (count > 1):
		new_val = result[0] - result[1]
		result[0] = new_val
		result[1] = 0
		result.sort(reverse=True)
		count -= 1
	return result[0]

