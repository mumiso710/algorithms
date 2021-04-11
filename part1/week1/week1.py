import math

def karatsuba(x, y):
    n = max(len(x), len(y))
    x = paddingZero(x, n)
    y = paddingZero(y, n)
    if n == 1:
        return str(int(x) * int(y))
    else:
        if n%2 != 0:
            x = paddingZero(x, n+1)
            y = paddingZero(y, n+1)
            n += 1 
        a = x[:n//2]
        b = x[n//2:]
        c = y[:n//2]
        d = y[n//2:]

        p = karatsubaAdd(a, b)
        q = karatsubaAdd(c, d)

        ac = karatsuba(a,  c)
        bd = karatsuba(b,  d)
        pq = karatsuba(p,  q)

        adbc = karatsubaSub(karatsubaSub(pq, ac), bd)


        return str(pow(10, n) * int(ac) + pow(10, n//2) * int(adbc) + int(bd))


def karatsubaAdd(x, y):
    n = max(len(x), len(y))
    x = paddingZero(x, n)
    y = paddingZero(y, n)
    curry = 0
    ans = ""
    for i in reversed(range(n)):
        ithSum = int(x[i]) + int(y[i]) + curry
        curry = 0
        if ithSum >= 10:
            curry = 1
            ithSum -= 10
        ans = str(ithSum) + ans
    if curry == 1:
        ans = "1" + ans
    return ans



def karatsubaSub(x, y):
    n = max(len(x), len(y))
    x = paddingZero(x, n)
    y = paddingZero(y, n)
    curry = 0
    ans = ""
    for i in reversed(range(n)):
        ithSum = int(x[i]) - (int(y[i]) + curry)
        curry = 0
        if ithSum < 0:
            curry = 1
            ithSum += 10
        ans = str(ithSum) + ans
    return ans 
        
def paddingZero(num, length):
    while(len(num) < length):
        num = "0" + num
    return num





if __name__ == "__main__":
    x = "3141592653589793238462643383279502884197169399375105820974944592"
    y = "2718281828459045235360287471352662497757247093699959574966967627"
    print(karatsuba(x, y))


