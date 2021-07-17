#!/usr/bin/env python3

import pet
if __name__ == "__main__":
    p = pet.Pet("Michael")
    print(p)
    if p.getName() != "Michael":
        print("Oops")
    else:
        print("Welcome, {}".format(p.getName()))
