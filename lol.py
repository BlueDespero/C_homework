import math
print(math.gcd(*(lambda x: (int(x.split(' ')[0]), int(x.split(' ')[1])))(input('Podaj dwie liczby w formacie "a b": \n'))))