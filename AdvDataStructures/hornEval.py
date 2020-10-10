def hornEval1(coeffs, val):
    ''' NOTE: assumes that if you wanted to skip a power, you'd represent it in
              list with a 0 as its coeff
    '''
    Sum = coeffs[-1]
    for i in reversed(range(len(coeffs))):
        Sum = Sum * val + coeffs[i]
        print(Sum)
    print('regSum: %s' % Sum)

coeffs = [1, 2, 3, 4]

hornEval1(coeffs=coeffs, val=-2)