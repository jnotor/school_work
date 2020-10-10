# TODO:
# procedure MaxMin3(L[0:n – 1],MaxValue,MinValue)
# Input: L[0:n – 1] (a list of size n)
# Output: MaxValue,MinValue (the maximum and minimum values in L[0:n – 1])
# if even(n) then //n is even
# MM(L[0],L[1],MaxValue,MinValue)
# for i ← 2 to n – 2 by 2 do
# MM(L[i],L[i + 1],b,a)
# if a < MinValue then MinValue ← a endif
# if b > MaxValue then MaxValue ← b endif
# endfor
# else //n is odd
# MaxValue ← L[0]; MinValue ← L[0];
# for i ← 1 to n – 2 by 2 do
# MM(L[i],L[i + 1],b,a)
# if a < MinValue then MinValue ← a endif
# if b > MaxValue then MaxValue ← b endif
# endfor
# endif
# end MaxMin3