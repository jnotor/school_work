def euclidGCD(a, b):
    print(a, b)
    if not b:
        return a
    else:
        euclidGCD(b, a % b)

euclidGCD(43, 680)