import pickle

test_object = {"name": "Bob", "values": [123,15,41,12,1], "city": "Boston"}

print(pickle.dumps(test_object))

with open("data.pickle", "wb") as f:
    pickle.dump(test_object, f)

with open("data.pickle", "rb") as f:
    loaded_obj = pickle.load(f)

print(loaded_obj)