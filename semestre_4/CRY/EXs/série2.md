# Série 2
## 1 Opérations Modulaires
### Donnée
Calculer à la main (ou avec une calculatrice simple) les réductions modulaires suivantes :
1. 12 mod 7
2. 55 mod 17
3. 56 mod 3129283791837128723618273687163
4. 3618736 mod 3728
5. 32092830 mod 328
6. 2^20 mod 3 
### Réponse
1. 5
2. 4
3. 56
4. 2576
5. 326
6. 1

## 2 Nombres Premiers
### Donnée
1. Au moyen du crible d’Ératosthène, trouver tous les nombres premiers situés entre 100
et 130.
2. Combien l’estimation π(n) ≈ n/ ln n donne-t-elle de nombres premiers situés entre 100
et 130 ? Comparer avec le résultat que vous avez obtenu à la question précédente.
3. Soit p un nombre premier. Le nombre Mp = 2p − 1 est appelé un nombre de Mersenne.
Trouver les quatre plus petits nombres de Mersenne premiers.
4. Le nombre 137703491 est-il premier ? Justifier la méthode qui vous a permis d’arriver à
une conclusion.
### Réponse 
Code du crible d’Ératosthène
```py
def eratosthene(n):
    L = [ i for i in range(2,n+1) ]
    P = [ ]
    
    while len(L) != 0:
        P.append(L[0])
        i = L[0]
        for k in L:
            if k % i == 0:
                del(L[L.index(k)])
    
    return P
```
1.

