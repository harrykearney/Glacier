import sys

with open("evaluation.txt", "w+") as f:
    evaluation = eval(sys.argv[1])
    f.write(str(evaluation))