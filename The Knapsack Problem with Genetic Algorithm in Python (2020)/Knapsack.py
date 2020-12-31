import random
import heapq
import math

# Setting up boxes

BOXES = []

class box:
    def __init__(self, weight, importance):
        self.weight = weight
        self.importance = importance

BOXES.append(box(20, 6))
BOXES.append(box(30, 5))
BOXES.append(box(60, 8))
BOXES.append(box(90, 7))
BOXES.append(box(50, 6))
BOXES.append(box(70, 9))
BOXES.append(box(30, 4))
BOXES.append(box(30, 5))
BOXES.append(box(70, 4))
BOXES.append(box(20, 9))
BOXES.append(box(20, 2))
BOXES.append(box(60, 1))

#Creates a random given sized population of sets of boxes. 
def randomize_pop(POPULATION, POP_SIZE):
    for _ in range(0, POP_SIZE):
        backpack_list = []
        for _ in range (0, len(BOXES)):
            backpack_list.append(random.randint(0, 1))
        bag = backpack(backpack_list)
        fitness = bag.fitness
        heapq.heappush(POPULATION, ((-1)*fitness, id(bag), bag))

# backpack object, represents a set of boxes in a backpack
class backpack:
    def __init__(self, pop):
        self.max_weight = 250
        self.rep = pop                          #the index representation of the boxes
        self.content = []                       #the set of the boxes with the weight and value info
        self.populate(pop)                      #populate the set with the given index representation
        self.fitness = self.calc_fitness()      #the fitness of the set

    def total_weight(self):
        sum = 0
        for box in self.content:
            sum += box.weight
        return sum

    def calc_fitness(self):
        if self.total_weight() > self.max_weight:
            return 0    #return 0 in fitness if too heavy
        total_value = 0
        for box in self.content:
            total_value += box.importance
        return total_value #if in weight range, return the total value of boxes

    def populate(self, pop):
        for x in range(0, len(BOXES)):
            if pop[x] == 1:
                self.content.append(BOXES[x])

#Cut the population in half
def Culling(POPULATION, POP_SIZE):
    temp = POPULATION[:(len(POPULATION)//2)]
    POPULATION = temp.copy()
    POP_SIZE = len(POPULATION)
    return POPULATION, POP_SIZE

#Choose a random index and create 2 child from the parents,
#one child take the first part of parent_1 and second part of parent_2
#the other take the first part of parent_2 and first part of parent_1
def crossover_then_mutate(new_gen, parent_1, parent_2):
    index = random.randint(0, len(BOXES) - 1)
    child_1 = parent_1[:index]
    child_1.extend(parent_2[index:])
    child_2 = parent_2[:index]
    child_2.extend(parent_1[index:])

    child_1 = mutate(child_1)
    child_2 = mutate(child_2)

    c_1 = backpack(child_1)
    c_1_fitness = c_1.fitness
    heapq.heappush(new_gen, ((-1)*c_1_fitness, id(c_1), c_1))
    c_2 = backpack(child_2)
    c_2_fitness = c_2.fitness
    heapq.heappush(new_gen, ((-1)*c_2_fitness, id(c_2), c_2))

#Take away one random box or add in one random box
def mutate(pop):
    new_pop = pop.copy()
    index = random.randint(0, len(BOXES) - 1)
    if new_pop[index] == 0:
        new_pop[index] = 1
    else:
        new_pop[index] = 0
    old_p = backpack(pop)
    new_p = backpack(new_pop)
    #Return mutated set only if better fit
    if (new_p.fitness >= old_p.fitness):
        return new_pop
    else:
        return pop


#Create the next generation of the population with Genetic Algorithm
def next_gen(POPULATION, POP_SIZE):
    POPULATION, new_size = Culling(POPULATION, POP_SIZE)
    new_gen= []
    not_empty = False
    for x in range(0, len(POPULATION) - 1):
        if (not (x % 2)) and (not (x+1) >= len(POPULATION)):
            crossover_then_mutate(new_gen, POPULATION[x][2].rep, POPULATION[x+1][2].rep)
            not_empty = True

    
    #only change to next generation if the best fitting set in new generation is better
    if (not_empty) and (new_gen[0][0] <= POPULATION[0][0]):
        POPULATION = new_gen.copy()

    return POPULATION, new_size
            


if __name__ == "__main__":
    POPULATION = []
    POP_SIZE = 800 #The higher starting population, the longer it takes, but the more likely solution is optimal
    randomize_pop(POPULATION, POP_SIZE)

    while POP_SIZE > 1:
        POPULATION, POP_SIZE = next_gen(POPULATION, POP_SIZE)

    #Solution is not always optimal, but usually is or is pretty high
    #Best possible value for the listed items is 44
    print("Solution box index: ", POPULATION[0][2].rep)
    print("weight: ", POPULATION[0][2].total_weight(), "fitness: ", POPULATION[0][2].fitness)
