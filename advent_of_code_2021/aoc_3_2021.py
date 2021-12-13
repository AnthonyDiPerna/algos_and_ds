# aoc_template.py
#RUN - python3 aoc_3_2021.py aoc_3_puzzle_input.txt

import pathlib
import sys
from functools import reduce
from operator import xor

print("AOC Day 3 - BINARY DIAGNOSTIC!!!")
NUM_BITS = 12

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
    return gammaBits

def part2(data,mostCommonBits):
    """Solve part 2"""
    oxygenData = []
    co2Data = []
    nextBitOxygenOnes = 0
    nextBitOxygenZeros = 0
    nextBitCO2Ones = 0
    nextBitCO2Zeros = 0
    #iterate through each line and determine if its oxygen data bit=1 or C02 data bit=0
    for line in data:
        #check first bit and split the data
        #print("Part2 line {} bit {} oxygenBit {}".format(line,line[0],mostCommonBits[0]))
        if int(line[0]) == mostCommonBits[0]:
            oxygenData.append(line)
            #print("   Oxygen")
            if int(line[1]) == 0:
                nextBitOxygenZeros += 1
            else:
                nextBitOxygenOnes += 1
        else:
            co2Data.append(line)
            #print("   CO2")
            if int(line[1]) == 0:
                nextBitCO2Zeros += 1
            else:
                nextBitCO2Ones += 1

        #keep track of the next bit to filter
      
    nextBit = 0
    if nextBitOxygenOnes >= nextBitOxygenZeros:
        nextBit = 1

    index = 1
    #narrow down to final 2
    print("~~~ OXYGEN ")
    while (len(oxygenData) >= 1 and index < NUM_BITS):
        nextBitOnes = 0
        nextBitZeros = 0

        if len(oxygenData) < 5:
            print("-- Oxygen Start {} Len {}".format(oxygenData,len(oxygenData)))
        
        #iterate over copy of the list and remove the parts you dont need
        for line in oxygenData[:]:
            if len(oxygenData)<5:
                print("    line {} index {} bit {} oxygenBit {}".format(line,index, line[index],nextBit))
            if int(line[index]) != nextBit:
                oxygenData.remove(line)
                if len(oxygenData)<5:
                    print("      remove")
            else:
                if (index < (NUM_BITS-1)):
                    if int(line[index+1]) == 0:
                        nextBitZeros += 1
                    else:
                        nextBitOnes += 1

        index += 1
        
        if nextBitOnes >= nextBitZeros:
            nextBit = 1
        else:
            nextBit = 0
        
        print("-- Ones {} Zeros {} Next {}".format(nextBitOnes,nextBitZeros, nextBit))
    
    if nextBitCO2Ones < nextBitCO2Zeros:
        nextBit = 1

    print("OXYGEN DATA {} ".format(oxygenData))
    
    index = 1
    print("~~~ CO2 ")
    while (len(co2Data) >= 2 and index < NUM_BITS):
        nextBitOnes = 0
        nextBitZeros = 0

        if len(co2Data) < 5:
            print("-- CO2 Start {} Len {}".format(co2Data,len(co2Data)))
        #iterate over copy of the list and remove the parts you dont need
        for line in co2Data[:]:
            
            if len(co2Data) < 5:
                print("    line {} index {} bit {} oxygenBit {}".format(line,index, line[index],nextBit))
            
            #print("    line {} index {} bit {} co2DataBit {}".format(line,index,line[index],nextBit))
            if int(line[index]) != nextBit:
                co2Data.remove(line)

                if len(co2Data)<5:
                    print("      remove")
            else:
                if (index < (NUM_BITS-1)):
                    if int(line[index+1]) == 0:
                        nextBitZeros += 1
                    else:
                        nextBitOnes += 1

        index += 1

        if nextBitZeros <= nextBitOnes:
            nextBit = 0
        else:
            nextBit = 1

        print("-- Ones {} Zeros {} Next {}".format(nextBitOnes,nextBitZeros, nextBit))


    print("Part2 Oxygen {} CO2 {}".format(oxygenData,co2Data))
    oxygenDecimalValue = int("".join(str(x) for x in oxygenData), 2)
    co2DecimalValue = int("".join(str(x) for x in co2Data), 2)
    print("Part2 Answer Oxygen x Co2 {} Oxygen Decimal {} Oxygen bits {} Co2 Decimal {} Co2 bits {}".format(oxygenDecimalValue*co2DecimalValue,oxygenDecimalValue,oxygenData,co2DecimalValue,co2Data))


def solve(puzzle_input):
    """Solve the puzzle for the given input"""
    data = parse(puzzle_input)
    solution1 = part1(data)
    solution2 = part2(data,solution1)

    return solution1, solution2

if __name__ == "__main__":
    for path in sys.argv[1:]:
        print(f"{path}:")
        puzzle_input = pathlib.Path(path).read_text().strip()
        solutions = solve(puzzle_input)
        print("\n".join(str(solution) for solution in solutions))
