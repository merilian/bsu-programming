import yaml


doc = """
- b: 3
  a: 2.9
- g: string
  a: False
"""

decoded_str = yaml.load(doc, yaml.Loader)

print(decoded_str)

toSave = {
    'a': 5,
    'b': 1.7,
    'c': 'str',
    'e': {1: 4, 2: 'qwe'},
    'f': False,
    'd': [1, 2, 3.9, [7, 8], {'a1': 1}],
}

#res = yaml.dumps(toSave, indent=2, sort_keys=True)
#print(res)

decoded = yaml.load(open('yaml/test.yaml'), yaml.Loader)

#print(decoded[0]['a'])
#print(decoded[1]['a'])
#print(decoded)

yaml.dump(toSave, open('yaml/test_out', 'w'), indent=2)