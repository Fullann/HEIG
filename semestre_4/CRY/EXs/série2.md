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
#### 1. les nombres premiers situés entre 100 et 130
On prend tous les nombres
- 100,101,102...130
On prend la racine carrée de 130 pour determiner jusqu'à où on doit s'arreter dans notre cas 11,4
donc on enlve tous les multiple de 2,3,5,7,11 ce qui nous donne 101, 103, 107, 109, 113, 127

#### 2. Estimation de π(n) ≈ n / ln(n)

L'estimation du nombre de nombres premiers inférieurs à un certain \(n\) est donnée par la fonction :

$$
\pi(n) \approx \frac{n}{\ln(n)}
$$

Nous devons évaluer le nombre de nombres premiers entre **100 et 130**.

-  \(\pi(130) \approx \frac{130}{\ln(130)} \approx \frac{130}{4.87} \approx 26.7\)
- \(\pi(100) \approx \frac{100}{\ln(100)} \approx \frac{100}{4.61} \approx 21.7\)
- Nombre estimé de nombres premiers entre 100 et 130 :
  $$
  \pi(130) - \pi(100) \approx 26.7 - 21.7 = 5
  $$

Comparaison avec le **résultat exact** trouvé précédemment : **6 nombres premiers**.\
L'estimation est donc proche mais légèrement inférieure.

---

#### 3. Les quatre plus petits nombres de Mersenne premiers

Les nombres de **Mersenne premiers** sont définis comme \(M_p = 2^p - 1\), où \(p\) est un nombre premier.

Calculons les premiers cas :

- Pour \(p = 2\) : \(M_2 = 2^2 - 1 = 3\) (premier)
- Pour \(p = 3\) : \(M_3 = 2^3 - 1 = 7\) (premier)
- Pour \(p = 5\) : \(M_5 = 2^5 - 1 = 31\) (premier)
- Pour \(p = 7\) : \(M_7 = 2^7 - 1 = 127\) (premier)

Les **quatre plus petits nombres de Mersenne premiers** sont donc :\
**3, 7, 31, 127**.

---

#### 4. Vérifier si 137703491 est un nombre premier

Pour déterminer si \(137703491\) est premier, on peut :

- Vérifier s'il est divisible par **les nombres premiers inférieurs à \*\*\*\*\*\*\*\*****\(\sqrt{137703491}\)**.
- Utiliser un **algorithme de primalité** (ex : test de Fermat, test de Miller-Rabin).

Calculons \(\sqrt{137703491} \approx 11732\).\
Nous devons donc tester la divisibilité par les premiers jusqu'à environ 120.

Faisons un test rapide en divisant par quelques nombres premiers :

- **Divisible par 7** :\
  \(137703491 \div 7 = 19671927\) (nombre entier)\
  Donc **137703491 est divisible par 7**, il n'est **pas premier**.

Conclusion : **137703491 n'est pas un nombre premier**.
## 3 Calculs de PGDCs
### Donnée
À la main (avec une calculatrice simple), et au moyen de l’algorithme d’Euclide, calculer
les PGCDs suivants :
1. pgcd(3719, 12)
2. pgcd(123, 456)
3. pgcd(1000000, 3335)
4. pgcd(2^17 − 1, 2^16 + 2)
5. pgcd(3^10 − 2,58)
### Réponse

1. **pgcd(3719, 12)**
   - 3719 ÷ 12 = 309, reste 11
   - 12 ÷ 11 = 1, reste 1
   - 11 ÷ 1 = 11, reste 0
   - **PGCD = 1**

2. **pgcd(123, 456)**
   - 456 ÷ 123 = 3, reste 87
   - 123 ÷ 87 = 1, reste 36
   - 87 ÷ 36 = 2, reste 15
   - 36 ÷ 15 = 2, reste 6
   - 15 ÷ 6 = 2, reste 3
   - 6 ÷ 3 = 2, reste 0
   - **PGCD = 3**

3. **pgcd(1000000, 3335)**
   - 1000000 ÷ 3335 = 299, reste 2995
   - 3335 ÷ 2995 = 1, reste 340
   - 2995 ÷ 340 = 8, reste 315
   - 340 ÷ 315 = 1, reste 25
   - 315 ÷ 25 = 12, reste 15
   - 25 ÷ 15 = 1, reste 10
   - 15 ÷ 10 = 1, reste 5
   - 10 ÷ 5 = 2, reste 0
   - **PGCD = 5**

4. **pgcd(2^{17} - 1, 2^{16} + 2)**
   - 2¹⁷ - 1 = 131071
   - 2¹⁶ + 2 = 65538
   - 131071 ÷ 65538 = 1, reste 65533
   - 65538 ÷ 65533 = 1, reste 5
   - 65533 ÷ 5 = 13066, reste 3
   - 5 ÷ 3 = 1, reste 2
   - 3 ÷ 2 = 1, reste 1
   - 2 ÷ 1 = 2, reste 0
   - **PGCD = 1**

5. **pgcd(3^{10} - 2, 58)**
   - 3¹⁰ - 2 = 59049 - 2 = 59047
   - 59047 ÷ 58 = 1018, reste 21
   - 58 ÷ 21 = 2, reste 16
   - 21 ÷ 16 = 1, reste 5
   - 16 ÷ 5 = 3, reste 1
   - 5 ÷ 1 = 5, reste 0
   - **PGCD = 1**


### **4. Calcul de l'identité de Bézout à la main**

L'identité de Bézout dit que si \( a \) et \( b \) sont deux entiers, alors il existe deux entiers \( x \) et \( y \) tels que :

\[
ax + by = \text{PGCD}(a, b)
\]

Nous allons utiliser l'algorithme d'Euclide étendu.

#### **4.1. (3719, 12)**
On applique l'algorithme d'Euclide :

\[
3719 \div 12 = 309 \text{ reste } 11
\]
\[
12 \div 11 = 1 \text{ reste } 1
\]
\[
11 \div 1 = 11 \text{ reste } 0
\]

Donc, \( \text{PGCD}(3719, 12) = 1 \).

On remonte pour exprimer 1 sous forme de combinaison de 3719 et 12 :

\[
1 = 12 - 1 \times 11
\]
\[
1 = 12 - 1 \times (3719 - 309 \times 12)
\]
\[
1 = 12 - 1 \times 3719 + 309 \times 12
\]
\[
1 = 310 \times 12 - 1 \times 3719
\]

Donc, \( x = -1 \) et \( y = 310 \).

#### **4.2. (123, 456)**
Algorithme d'Euclide :

\[
456 \div 123 = 3 \text{ reste } 87
\]
\[
123 \div 87 = 1 \text{ reste } 36
\]
\[
87 \div 36 = 2 \text{ reste } 15
\]
\[
36 \div 15 = 2 \text{ reste } 6
\]
\[
15 \div 6 = 2 \text{ reste } 3
\]
\[
6 \div 3 = 2 \text{ reste } 0
\]

Donc, \( \text{PGCD}(123, 456) = 3 \).

En remontant :

\[
3 = 15 - 2 \times 6
\]
\[
3 = 15 - 2 \times (36 - 2 \times 15)
\]
\[
3 = 5 \times 15 - 2 \times 36
\]
\[
3 = 5 \times (87 - 2 \times 36) - 2 \times 36
\]
\[
3 = 5 \times 87 - 12 \times 36
\]
\[
3 = 5 \times (123 - 87) - 12 \times 36
\]
\[
3 = 5 \times 123 - 17 \times 87
\]
\[
3 = 5 \times 123 - 17 \times (456 - 3 \times 123)
\]
\[
3 = 56 \times 123 - 17 \times 456
\]

Donc, \( x = 56 \) et \( y = -17 \).

#### **4.3. \( (3^{10} - 2, 58) \)**
D'abord, on calcule :

\[
3^{10} = 59049
\]
\[
59049 - 2 = 59047
\]

On applique l'algorithme d'Euclide entre 59047 et 58 :

\[
59047 \div 58 = 1018 \text{ reste } 43
\]
\[
58 \div 43 = 1 \text{ reste } 15
\]
\[
43 \div 15 = 2 \text{ reste } 13
\]
\[
15 \div 13 = 1 \text{ reste } 2
\]
\[
13 \div 2 = 6 \text{ reste } 1
\]
\[
2 \div 1 = 2 \text{ reste } 0
\]

Donc, \( \text{PGCD}(59047, 58) = 1 \).

En remontant, on trouve :

\[
1 = -22489 \times 58 + 2207 \times (3^{10} - 2)
\]

### **5. Implémentation de l'algorithme d'Euclide en Python**

```python
def pgcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

print(pgcd(36182736189736918736192873, 131556721028295178496))
```

### **6. Implémentation de l'algorithme d'Euclide étendu en Python**

```python
def euclide_etendu(a, b):
    if b == 0:
        return a, 1, 0
    else:
        d, x1, y1 = euclide_etendu(b, a % b)
        x = y1
        y = x1 - (a // b) * y1
        return d, x, y

# Vérification avec les exemples
print(euclide_etendu(3719, 12))
print(euclide_etendu(123, 456))
print(euclide_etendu(3**10 - 2, 58))
```