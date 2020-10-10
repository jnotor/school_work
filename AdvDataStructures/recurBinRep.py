def binRep(n):
    ''' NOTE: exceeds max recursion depth with even as small as 2 lol
    '''
    if not n:
        return ''
    return binRep(n/2 + n % 2)

binRep(2)