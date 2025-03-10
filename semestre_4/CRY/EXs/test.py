def pgcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

print(pgcd(36182736189736918736192873, 131556721028295178496))