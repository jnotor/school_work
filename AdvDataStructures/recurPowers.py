def Powers(x, p):
    ''' recursive solution for computing x^p given positive p
    '''
    if p == 1:
        return x
    # if even
    if not p % 2:
        return Powers(x*x, p/2)
    else:
        return x*Powers(x, p-1)

print(Powers(x=5, p=3))