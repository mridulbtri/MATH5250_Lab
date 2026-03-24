
def append(l, value):
    l.append(value)
    return l

def clear(l):
    l.clear()
    return l

def copy(list_1, list_2):
    list_2 = list_1.copy()
    return list_2

def count(l):
    length = len(l)
    return length

def extend(l, extension):
    l.extend(extension)
    return l

def index(l, value):
    return l.index(value)

def insert(l, index, value):
    new_list = l.insert(index, value)
    return new_list

def pop(l, index):
    value = l.pop(index)
    return value

def remove(l,value):
    new_list = l.remove(value)
    return new_list

def reverse(l):
    reversed_list= l.reverse()
    return reversed_list

def sort(l):
    sorted_list = l.sort()
    return sorted_list


# operations on a python list 
List_1 = [3.0, 5.6, 7.9, 22, 'apple', 0, 5, 'math']
List_2 = [7, 9, 3, 2.2, 'ball', 2.9, 'science']

print("List 1:", List_1)
print("List 2:",List_2)
print("===========================================")
print("Append \n")
print("Appending 21 to List1 :", append(List_1, 21))

print("\n=========================================")
print("Clearing all elements from list 1")
print("List 1:", clear(List_1))

print("\n=========================================")
print("Copying Lists")
List_3=[5, 22, 'apple', 'car', 24, 22]
print("Creating a new list List_3:", List_3)
print("Copying all elements of List_3 to List_1...")
List_1 = copy(List_3, List_1)
print("List_1 :", List_1)

print("\n=========================================")
print("Count Elements")
print("Number of elements in Listt_1", count(List_1))

print("\n=========================================")
print("Extend List")
print("Adding entries ('carrot', 43.7) to List_1")
print("List_1:",extend(List_1, ("Carrot", 43.7)))

print("\n=========================================")
print("Index")
print("Index of element 24 in List_1", index(List_1, 24))

print("\n=========================================")
print("Insert Element")
print("Inserting 'cherry' in List_1 at 5th index")
insert(List_1,5, 'cherry')
print("List_1 :", List_1)

print("\n=========================================")
print("Pop")
print("The 5th element from List_2 is ", pop(List_2, 4))

print("\n=========================================")
print("Remove item")
remove(List_2,2.2)
print("Removing 2.2 from List_2")
print("list_2", List_2)

print("\n=========================================")
print("Reverse")
reverse(List_2)
print('Reversing the order in List_2:', List_2 )

print("\n=========================================")
print("Sort")
print("Creating list 3 that is purely made of numbers")
List_3 = [2,3, 4, 0.2, -2, 100.3, 5.7]
print("List_3:", List_3)
sort(List_3)
print("Sorting List_3 in ascending order", List_3)




