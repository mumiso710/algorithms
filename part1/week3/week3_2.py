FILENAME = 'quicksort.txt'

def readFileAndCreateArray():
    arr = []
    with open(FILENAME, 'r') as file:
        lines = file.read().splitlines()
        for line in lines:
            arr.append(int(line))
    return arr

# in my quicksort use first element for pivot
def choosePivot(arr, l, r):
    return r-1


def partition(arr, l, r):
    pivot = arr[l]
    partitioned= l+1
    compNum = r - l - 1
    for unpartitioned in range(l+1, r):
        if arr[unpartitioned] < pivot:
            arr[unpartitioned], arr[partitioned] = arr[partitioned], arr[unpartitioned]
            partitioned += 1
    arr[l], arr[partitioned-1] = arr[partitioned-1], arr[l]
    return partitioned - 1, compNum


def quickSort(arr, l, r):
    if l >= r:
        return 0
    i = choosePivot(arr, l, r)
    # pivot set to most left
    arr[l], arr[i] = arr[i], arr[l] 
    j, compNum = partition(arr, l, r)
    compNum += quickSort(arr, l, j)
    compNum += quickSort(arr, j+1, r)

    return compNum


if __name__ == '__main__':

    arr = readFileAndCreateArray()
    ans = quickSort(arr, 0, len(arr))
    print(ans)
