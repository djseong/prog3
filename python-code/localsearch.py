from random import *
from math import *
from karp import *
import copy

def newInput(original_lst, solution, size):
	new_input = []
	for j in range(size):
		new_input.append(0)

	for j in range(size):
		new_input[solution[j]] += original_lst[j]

	return new_input

def t_iteration(iter):
	return pow(10, 10) * pow(.8, float(iter)/300)


def hillClimbingLocalSearch(original_lst, random_solution, size, max_iteration):
	# random_solution = randomSol(size)
	new_input = newInput(original_lst, random_solution, size)

	prior_residue = karp(new_input, size)

	for i in range(max_iteration):
		# new_random_solution = random_solution
		new_random_solution = randomMove(random_solution, size)

		new_input2 = newInput(original_lst, new_random_solution, size)

		new_residue = karp(new_input2, size)

		if new_residue < prior_residue:
			prior_residue = new_residue
			random_solution = new_random_solution

	return random_solution


def simulatedAnnealingLocalSearch(original_lst, random_solution, size, max_iteration):
	# random_solution = randomSol(size)
	random_solution2 = random_solution

	new_input = newInput(original_lst, random_solution, size)

	prior_residue = karp(new_input, size)

	original_residue = prior_residue

	for i in range(max_iteration):
		new_random_solution = randomMove(random_solution, size)
		new_input2 = newInput(original_lst, new_random_solution, size)

		new_residue = karp(new_input2, size)

		if new_residue < prior_residue:
			prior_residue = new_residue
			random_solution = new_random_solution
		else:
			if random.random() < exp(-(new_residue - prior_residue)/float(t_iteration(i))):
				prior_residue = new_residue
				random_solution = new_random_solution

		if prior_residue < original_residue:
			random_solution2 = random_solution
			original_residue = prior_residue

	return random_solution2

def repeatedRandomLocalSearch(original_lst, random_solution, size, max_iteration):
	# random_solution = randomSol(size)
	new_input = newInput(original_lst, random_solution, size)

	prior_residue = karp(new_input, size)

	for i in range(max_iteration):
		new_random_solution = randomSol(size)
		new_input2 = newInput(original_lst, new_random_solution, size)

		new_residue = karp(new_input2, size)

		if new_residue < prior_residue:
			prior_residue = new_residue
			random_solution = new_random_solution

	return random_solution


#***********************************************************************************
def standardHillClimbingLocalSearch(original_lst, random_solution, size, max_iteration):
	random_solution = randomSol2(size)

	prior_residue = karp2(original_lst, random_solution, size)

	for i in range(max_iteration):
		new_random_solution = randomMove2(random_solution, size)
		

		new_residue = karp2(original_lst, new_random_solution, size)


		if new_residue < prior_residue:
			prior_residue = new_residue
			random_solution = new_random_solution

	return random_solution


def standardSimulatedAnnealingLocalSearch(original_lst, random_solution, size, max_iteration):
	# random_solution = randomSol2(size)
	random_solution2 = random_solution

	prior_residue = karp2(original_lst, random_solution, size)

	original_residue = prior_residue

	for i in range(max_iteration):
		new_random_solution = randomMove2(random_solution, size)

		new_residue = karp2(original_lst, new_random_solution, size)

		if new_residue < prior_residue:
			prior_residue = new_residue
			random_solution = new_random_solution
		else:
			if random.random() < exp(-(new_residue - prior_residue)/float(t_iteration(i))):
				prior_residue = new_residue
				random_solution = new_random_solution

		if prior_residue < original_residue:
			random_solution2 = random_solution
			original_residue = prior_residue

	return random_solution2

def standardRepeatedRandomLocalSearch(original_lst, random_solution, size, max_iteration):
	# random_solution = randomSol2(size)

	prior_residue = karp2(original_lst, random_solution, size)

	for i in range(max_iteration):
		new_random_solution = randomSol2(size)

		new_residue = karp2(original_lst, new_random_solution, size)

		

		if new_residue < prior_residue:
			prior_residue = new_residue
			random_solution = new_random_solution


	return random_solution

#****************************************************************************************

random.seed()
size = 100
max_iteration = 25000

writeFile("input.txt", size)
original_lst = readFile("input.txt", size)

random_solution_prepartioning = randomSol(size)
random_solution1 = copy.deepcopy(random_solution_prepartioning)
random_solution2 = copy.deepcopy(random_solution_prepartioning)
random_solution3 = copy.deepcopy(random_solution_prepartioning) 

print("prepartitioned repeated random results")
solution1 = repeatedRandomLocalSearch(original_lst, random_solution1, size, max_iteration)
# print solution1
# print newInput(original_lst, solution1, size)
print(karp(newInput(original_lst, solution1, size), size))

print("prepartitioned hill climbing results")
solution2 = hillClimbingLocalSearch(original_lst, random_solution2, size, max_iteration)
# print solution2
# print newInput(original_lst, solution2, size)
print(karp(newInput(original_lst, solution2, size), size))

print("prepartitioned simulated annealing results")
solution3 = simulatedAnnealingLocalSearch(original_lst, random_solution3, size, max_iteration)
# print solution3
# print newInput(original_lst, solution3, size)
print(karp(newInput(original_lst, solution3, size), size))


random_solution_standarized = randomSol2(size)
random_solution1 = copy.deepcopy(random_solution_standarized)
random_solution2 = copy.deepcopy(random_solution_standarized)
random_solution3 = copy.deepcopy(random_solution_standarized)


print("standard repeated random results")
standard_solution1 = standardRepeatedRandomLocalSearch(original_lst, random_solution1, size, max_iteration)
# print standard_solution1
print(karp2(original_lst, standard_solution1, size))

print("standard hill climbing results")
standard_solution2 = standardHillClimbingLocalSearch(original_lst, random_solution2, size, max_iteration)
# print standard_solution2
print(karp2(original_lst, standard_solution2, size))

print("standard simulated annealing results")
standard_solution3 = standardSimulatedAnnealingLocalSearch(original_lst, random_solution3, size, max_iteration)
# print standard_solution3
print(karp2(original_lst, standard_solution3, size))







