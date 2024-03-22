a = 5
a = 2.6
a = 'efgh"dfg'
a = "sdjfh'gkdj"


my_list = [1, 4, 7, 9]

print(my_list)

'''
print(my_list[2]) # 7
print(my_list[:2]) # [1, 4]
print(my_list[2:]) # [7, 9]
print(my_list[-1]) # 9
print(my_list[1:3]) # [4, 7]
'''

def square(a):
  return a*a

# print(square(3))

'''
new_list = []

for element in my_list:
  new_list.append(square(element))
'''

# new_list = [e**2 for e in my_list]
new_list = [square(e) for e in my_list]
# print(new_list)


m = [
  [1, 2, 4],
  [3, 6, 8],
  [2, 1, 1]
]

# print(m)
# print(m[2][2])

m2 = [[e, e**2, e**3] for e in my_list]
# print(m2)


m2t = []
for i in m2[0]:
	m2t.append([])

for line in m2:
  '''
  print(line)
  print(len(line))
  print(range(len(line)))
  print(list(range(len(line))))
  '''

  for i in range(len(line)):
    m2t[i].append(line[i])

# print(m2t)







l = len(my_list) - 1
while l >= 0:
  print(my_list[l])
  l -= 1

b = True
if len(my_list) < 4:
  my_list.append(3)
elif len(my_list) == 4:
  my_list.append(9)
else:
  my_list.pop()

print(my_list)
