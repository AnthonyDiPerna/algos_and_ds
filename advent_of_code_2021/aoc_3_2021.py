# aoc_template.py
#RUN - python3 aoc_3_2021.py aoc_3_puzzle_input.txt

import pathlib
import sys
from functools import reduce
from operator import xor

print("AOC Day 3 - BINARY DIAGNOSTIC!!!")

def parse(puzzle_input):
    """Parse input - break into lines"""
    return list(filter(bool,puzzle_input.splitlines(False)))
    

def part1(data):
    """Solve part 1"""
    trackZeros  = [0,0,0,0,0,0,0,0,0,0,0,0]
    trackOnes   = [0,0,0,0,0,0,0,0,0,0,0,0]
    gammaBits = [0,0,0,0,0,0,0,0,0,0,0,0]
    epsilonBits = [0,0,0,0,0,0,0,0,0,0,0,0]
    print("Solve part 1")
    #iterate through each line in the list of input data
    for line in data:
        #iterate through each characterin the string
        index = 0
        for b in line:
            #print("Part1 b {} ".format(b))
            if int(b) == 0:
                trackZeros[index] += 1
            else:
                trackOnes[index] += 1
            
            #update final answer
            if trackOnes[index] > trackZeros[index]:
                gammaBits[index] = 1
                epsilonBits[index] = 0
            else:
                gammaBits[index] = 0 
                epsilonBits[index] = 1
            
            #print("   Part1 zeros {} ones {} answer {}".format(trackZeros,trackOnes,gammaBits))
            index += 1

    gammaDecimalValue = int("".join(str(x) for x in gammaBits), 2)
    epsilonDecimalValue = int("".join(str(x) for x in epsilonBits), 2)
    print("Part1 Answer Gamma x Epsilon {} Gamma Decimal {} Gamma bits {} Epsilon Decimal {} Epsilon bits {}".format(gammaDecimalValue*epsilonDecimalValue,gammaDecimalValue, gammaBits, epsilonDecimalValue, epsilonBits))

def part2(data):
    """Solve part 2"""

def solve(puzzle_input):
    """Solve the puzzle for the given input"""
    data = parse(puzzle_input)
    solution1 = part1(data)
    solution2 = part2(data)

    return solution1, solution2

if __name__ == "__main__":
    for path in sys.argv[1:]:
        print(f"{path}:")
        puzzle_input = pathlib.Path(path).read_text().strip()
        solutions = solve(puzzle_input)
        print("\n".join(str(solution) for solution in solutions))
