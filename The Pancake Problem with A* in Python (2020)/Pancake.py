import heapq
import random

# Function: Reverse
# Input: a list of pancake orders
# Output: a reversed list of pancake orders
# Description: Creates a new list that is the
#              reverse of the given list. 
def reverse(order):
    i = len(order) - 1
    reversed = []
    while (i >= 0):
        reversed += [order[i]]
        i = i - 1
    return reversed

# Function: sample_goal
# Input: number of element(pancakes)
# Output: An ordered list
# Description: Creates a new list of s elements that is ordered,
#              used for goal checks. 
def sample_goal(s):
    return list(range(1, s + 1))

# The pancakes class represents a state of a stack of pancakes
# It contains the order, backward cost, and the path taken to get to this state
class pancakes:
    
    def __init__(self, order = [], backcost = 0, path = []):
        self.order = order
        self.backcost = backcost
        self.path = path

    #Returns length of stack
    def length(self):
        return len(self.order)

    #Returns order of stack
    def get_order(self):
        return self.order

    #Returns backward cost
    def get_backcost(self):
        return self.backcost

    #Returns path taken
    def get_path(self):
        return self.path

    #Adds 1 to the backward cost
    def add_backcost(self):
        self.backcost += 1

    #Add given number to the path taken
    def add_path(self, n):
        self.path += [n]

    #Check if the current order is the goal order
    def if_goal(self, goal):
        if (self.order == goal):
            return True
        else:
            return False

    #Calculates the heuristic value with the gap heuristic equation
    def heuristic(self):
        value = 0
        length = len(self.order)
        i = 0
        while (i < length - 1):
            cur = self.order[i]
            if ((self.order[i + 1] != cur + 1) and 
                (self.order[i + 1] != cur - 1)):
                value = value + 1
            i = i + 1
        return value

    #Reverse all the pancakes above the given value
    def flip(self, n):
        if (n == self.length()):
            return reverse(self.order)
        else:
            return reverse(self.order[:n]) + self.order[n:]
        


    
# The A* Search Algorithm
def A_Star(stack):
    length = stack.length()
    goal = sample_goal(length)

    #If the stack is already in order. 
    if (stack.if_goal(goal)):
        return []

    queue = []      #The Priority Queue
    visited = []    #A list to keep track of visited orders

    #All the possible flips are from position 2 to length - 1
    #This for loop handles one flip at each location and initiates
    #the rest of the search. 
    for x in range(2, length):
        oldpath = stack.get_path()
        path = oldpath.copy()
        path.append(x)
        cost = stack.get_backcost() + 1
        new_state = pancakes(stack.flip(x), cost, path)
        #If at goal, return the current state,
        #else, add the state to the queue and visited lists
        if (new_state.if_goal(goal)):
            return new_state
        else: 
            cost = new_state.get_backcost() + new_state.heuristic()
            heapq.heappush(queue, (cost, id(new_state), new_state))
            visited += [new_state.get_order()]

    #Keep popping states from the beginning of the priority queue
    #until the result is found, or until queue is empty.
    while len(queue) > 0:
        curr = heapq.heappop(queue)
        curr_order = curr[2]
        path = curr_order.get_path()
        last_flip = path[len(path) - 1]
        
        for x in range(2, length):
            if (x != last_flip):
                new_order = curr_order.flip(x)
                check = True
                #Check if current order has been visited before,
                #if so, ignore current state
                for list in visited:
                    if new_order == list:
                        check = False
                if check == True:
                    new_path = path.copy()
                    new_path.append(x)
                    new_state = pancakes(new_order, 
                                curr_order.get_backcost() + 1, new_path)
                    #If at goal, return the current state,
                    #else, add the state to the queue and visited lists
                    if (new_state.if_goal(goal)):
                        return new_state
                    else: 
                        cost = new_state.get_backcost() + new_state.heuristic()
                        heapq.heappush(queue, (cost, id(new_state), new_state))
                        visited += [new_state.get_order()]
    print("There is no solution")
    

    

# Main

if __name__ == "__main__":
    Mode = input("Please enter 'A' for Auto mode of 10 random pancakes or 'M' for Manual enter Mode: ")
    stack = []
    if Mode == 'A':
        #Generate random stack of 10 pancakes
        stack = list(range(1, 11))
        random.shuffle(stack)
    elif Mode == 'M':
        num = int(input("Please enter number of pancakes(ex: 10): "))
        stack = []
        for i in range(0, num):
            print("Value for number(from the top to bottom)", i + 1, "pancake is: ")
            ele = int(input())
            stack.append(ele)
    
    num = len(stack)
    print("\nYour stack from top to bottom is: \n", stack)
    stack.append(num + 1) #Adds the plate to the stack
    print("\nRunning A*\n")
    search = pancakes(stack, 0, [])
    result = A_Star(search) #The actual search
    if not result:
        print("Pancakes already in order\n")
    else: 
        print("The required flips in order are: \n")
        path = result.get_path() #The correct order of the flip
        #Printing the result and the stack after each flip
        for n in path:
            order = search.flip(n)
            print("Flip the top", n, "pancakes:")
            print(order[:num], "\n")
            search = pancakes(order, 0, [])
