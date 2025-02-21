import json

doc = """
{
  "a": 2,
  "b": {
    "c": "string",
    "d": 1.5
  }
}
"""

#decoded = json.loads(doc)

#print(decoded['b']['c'])
#print(decoded)

toSave = {
    'a': 5,
    'b': 1.7,
    'c': 'str',
    'e': {1: 4, 2: 'qwe'},
    'f': False,
    'd': [1, 2, 3.9, [7, 8], {'a1': 1}],
}

res = json.dumps(toSave, indent=2, sort_keys=True)
#print(res)

decoded = json.load(open('json/file_example.json'))

print(decoded['b']['c'])
print(decoded)

json.dump(toSave, open('json/out.json', 'w'), indent=2)