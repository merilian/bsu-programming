# ()
'''
c = (1, 4, 'sfdgd', 23.7)
print(c[1])

c1, c2, c3, c4 = c

cc7 = c1, c2, c3, c4


def square(x):
    return (x, x**2)

x, x_square = square(5)
'''

# {} set
'''
s = {1, 2, 3, 4, 1, 2, 3, 4}
#print(s)

s = {x for x in 'abcdacbd'}
#print(s)

#for e in s:
    #print(e)

#print(list(s))

s1 = {1, 2, 3, 4}
s2 = {3, 4, 5, 6}
print(s1 | s2)
print(s1 & s2)
print(s1 - s2)
print(s1 ^ s2)
'''

# {} dictionary
'''
d = {1: 'one', 2: 'two', 'one': 1, 'two':2}
print(d[2])
print(d[d[d[d[d[d[d[d[d[1]]]]]]]]])
for k,v in d.items():
    print(k)

d[3] = 'three'
del d[2]
print(d)
'''

