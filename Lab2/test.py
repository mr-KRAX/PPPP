#!/bin/python3

import subprocess
import json

progName = "./Solver"

def execProg(args):
  cmd = [progName] + args.split()
  completed_proc = subprocess.run(cmd, stdout=subprocess.PIPE)
  return completed_proc.stdout.decode("utf-8")

def runTest(test):
  print ("{name:18} {args:14} {res:8} | ".format(**test), end="")
  res = execProg(test["args"])
  status = (res == test["res"])
  print("{res:8}  {status:4}".format(res=res, status=("GOOD" if status else "BAD")))
  return status


def loadTests():
  with open("tests.json", "r") as read_file:
    data = json.load(read_file)
  if data:
    print("> Tests has been loaded")
  return data

if (__name__ == "__main__"):
  tests = loadTests()

  print("\n-------------------------------------------+----------------")
  print("Test name          Args           Expected | Res      Status")
  print("-------------------------------------------+----------------")

  bad_count = 0
  for t in tests:
    res = runTest(t)
    if not (res):
      bad_count += 1

  print("-------------------------------------------+----------------\n")
  print("> All tests are done!")
  print("> Total: " + str(len(tests)) + "; Bad: " + str(bad_count))
    
    
