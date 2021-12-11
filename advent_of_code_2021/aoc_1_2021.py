import os 

print("My name is jacob")

# THIS IS HOW YOU SEE ALL THE FILES IN THE DIRECTORY
# print(os.listdir())

#Open the file and read the lines
file1 = open('advent_of_code_2021/aoc_1_first_puzzle_input.txt', 'r')
Lines = file1.readlines()

countTotalLines = 0
countLargerMeasurements = 0
previousMeasurement = 0
# Strips the newline character
for line in Lines:
    #special case for the first number, can't be bigger since there is no previous number
    currentMeasurement = int(line.strip())

    if previousMeasurement > 0:
        #we have a previous measurement
        
        #current measurement is larger, count it!
        #print("Measurement check {} : {}".format(previousMeasurement, currentMeasurement))
        if currentMeasurement > previousMeasurement:
            countLargerMeasurements += 1
            #print("   Increase {}".format(countLargerMeasurements))
    
    previousMeasurement = currentMeasurement


    countTotalLines += 1
    #print("Line{}: {}".format(countTotalLines, line.strip()))

print("Measurements that are larger {}: Total Measurements {}".format(countLargerMeasurements, countTotalLines))




countTotalWindows = 0
countLargerMeasurements = 0
previousMeasurement = 0
i = 0
# Strips the newline character
while i < (len(Lines)-2):
    currentMeasurement = int(Lines[i].strip()) + int(Lines[i+1].strip()) + int(Lines[i+2].strip())

    if previousMeasurement > 0:
        #we have a previous measurement
        
        #current measurement is larger, count it!
        print("SW Measurement check {} : {}".format(previousMeasurement, currentMeasurement))
        if currentMeasurement > previousMeasurement:
            countLargerMeasurements += 1
            print("SW    Increase {}".format(countLargerMeasurements))
    
    previousMeasurement = currentMeasurement
    i = i + 1
    countTotalWindows += 1
print("SW Windows {}: {}".format(countLargerMeasurements, countTotalLines))