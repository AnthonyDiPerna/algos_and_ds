import os 
import re

print("AOC Day 2 - DIVE!!!")

# THIS IS HOW YOU SEE ALL THE FILES IN THE DIRECTORY
# print(os.listdir())

#Open the file and read the lines
file1 = open('advent_of_code_2021/aoc_2_puzzle_input.txt', 'r')
Lines = file1.readlines()

countTotalLines = 0
horizontal = 0
depth = 0

for line in Lines:
    #special case for the first number, can't be bigger since there is no previous number
    lineValue = line.strip()
    lineNumber= int(re.findall(r'\d+', line)[0])
    #print("Line {} : Value {} ".format(lineValue, lineNumber))
    #is it forward (horizontal) or up/down (depth)?
    if re.match("forward",lineValue):
        #add horizontal position
        horizontal += lineNumber
    elif re.match("up",lineValue):
        depth -= lineNumber
        if depth < 0: depth = 0
    elif re.match("down",lineValue):
        depth += lineNumber
    
    #print("   Horizontal {} : Depth {}".format(horizontal, depth))
countTotalLines += 1

print("Final MULTIPLY {} : Horizontal {} : Depth {} : Lines {}".format(horizontal*depth, horizontal,depth, countTotalLines))



#PART 2

countTotalLines = 0
horizontal = 0
depth = 0
aim = 0

for line in Lines:
    #special case for the first number, can't be bigger since there is no previous number
    lineValue = line.strip()
    lineNumber= int(re.findall(r'\d+', line)[0])
    print("Part2 Line {} : Value {} ".format(lineValue, lineNumber))
    #is it forward (horizontal) or up/down (aim)?
    if re.match("forward",lineValue):
        #add horizontal position and depth by aim
        horizontal += lineNumber
        depth += aim * lineNumber 
    elif re.match("up",lineValue):
        aim -= lineNumber
        if depth < 0: depth = 0
    elif re.match("down",lineValue):
        aim += lineNumber
    
    print("Part2   Horizontal {} : Depth {} : Aim {}".format(horizontal, depth, aim))
countTotalLines += 1

print("Part2 Final MULTIPLY {} : Horizontal {} : Depth {} : Aim {} : Lines {}".format(horizontal*depth, horizontal,depth,aim,countTotalLines))
