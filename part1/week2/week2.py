FILENAME = 'IntegerArray.txt'

def readFileAndCreateArray():
    file = open(FILENAME, 'r')
    lines = file.read().splitlines()
    file.close()
    numbers = []
    for line in lines:
        numbers.append(int(line))
    return numbers

def mergeAndContSplitInv(leftArr, rightArr):
    mergedArr = []
    splitInv = 0
    n = len(leftArr) + len(rightArr)
    leftIndex  = 0
    rightIndex = 0
    for _ in range(n):
        if rightIndex == len(rightArr) or (leftIndex < len(leftArr) and leftArr[leftIndex] < rightArr[rightIndex]):
            mergedArr.append(leftArr[leftIndex])
            leftIndex += 1
        else:
            mergedArr.append(rightArr[rightIndex])
            splitInv   += (len(leftArr) - leftIndex) 
            rightIndex += 1
    return mergedArr, splitInv
    

def sortAndCountInv(arr):
    n = len(arr)
    # base case
    if n == 0 or n == 1:
        return arr, 0
    # n >= 2
    leftArr, leftInv   = sortAndCountInv(arr[:n//2])
    rightArr, rightInv = sortAndCountInv(arr[n//2:])
    mergedArr, splitInv = mergeAndContSplitInv(leftArr, rightArr)
    return mergedArr, leftInv + rightInv + splitInv



if __name__ == '__main__':
    numbers = readFileAndCreateArray()
    numbers, ans = sortAndCountInv(numbers)
    print(ans)
