## Exercice 1 : Structures

1. **Z₍₂₅₆₎ muni de l’addition et de la multiplication**  
   – La structure (ℤ₂₅₆, +, ×) est un **anneau commutatif à unité**.  
   – Le groupe additif (ℤ₂₅₆, +) est abélien et comporte 256 éléments, mais la multiplication n’est pas inversible pour tous les éléments (seuls les éléments inversibles forment le groupe des unités).  
   – **Cardinalité** : 256.

2. **Z₂₃ muni de l’addition et de la multiplication**  
   – Puisque 23 est premier, ℤ₂₃ est un **corps** (tout élément non nul possède un inverse multiplicatif).  
   – **Cardinalité** : 23.

3. **Z*₍₂₅₆₎**  
   – Il s’agit du **groupe multiplicatif** des éléments inversibles de ℤ₂₅₆.  
   – Son cardinal est φ(256) (la fonction indicatrice d’Euler). Comme 256 = 2⁸, on a φ(256) = 256 · (1 – ½) = 128.  
   – **Cardinalité** : 128.

4. **Z₁₇[x]**  
   – C’est l’anneau des polynômes à coefficients dans ℤ₁₇. Comme ℤ₁₇ est un corps, ℤ₁₇[x] est un **domaine d’intégrité** (mais pas un corps, car un inverse existe uniquement pour les polynômes constants non nuls).  
   – **Cardinalité** : Infini (dénombrable).

5. **Z₁₇[x]/(x² + 5)**  
   – On vérifie que dans ℤ₁₇, le polynôme \(x^2+5\) est irréductible (en effet, si on cherche une racine, on doit résoudre \(x^2=-5\) ; or \(-5\) modulo 17 correspond à 12, qui n’est pas un carré dans ℤ₁₇).  
   – Le quotient est donc un **corps**.  
   – **Cardinalité** : \(17^2 = 289\).

---

## Exercice 2 : Polynômes sur un corps fini  
On effectue les calculs dans ℤ₂[x] et ℤ₃[x] :

### 2.1 Division euclidienne de  
\[
x^5 + x^4 + 1 \quad \text{par} \quad x^2 + 1
\]

- **Dans ℤ₂[x]** :  
  1. \(x^5 ÷ x^2 = x^3\).  
     \(x^3(x^2+1)= x^5 + x^3\).  
     Soustraction : \( (x^5+x^4+1) - (x^5+x^3)= x^4 + x^3 + 1\).  
  2. \(x^4 ÷ x^2 = x^2\).  
     \(x^2(x^2+1)= x^4 + x^2\).  
     Soustraction : \( (x^4+x^3+1) - (x^4+x^2)= x^3 + x^2 + 1\).  
  3. \(x^3 ÷ x^2 = x\).  
     \(x(x^2+1)= x^3+x\).  
     Soustraction : \( (x^3+x^2+1) - (x^3+x)= x^2 + x + 1\).  
  4. \(x^2 ÷ x^2 = 1\).  
     \(1\cdot(x^2+1)= x^2+1\).  
     Soustraction : \( (x^2+x+1) - (x^2+1)= x\).  

  **Quotient** : \(x^3+x^2+x+1\)  
  **Reste** : \(x\).

- **Dans ℤ₃[x]** :  
  On procède de même en effectuant la division en considérant les calculs modulo 3 (en notant que −1 ≡ 2 mod 3) :

  1. \(x^5 ÷ x^2 = x^3\).  
     \(x^3(x^2+1)= x^5+x^3\).  
     Soustraction : \(x^5+x^4+1 - (x^5+x^3)= x^4 - x^3 + 1\) (soit \(x^4+2x^3+1\) en ℤ₃).  
  2. \(x^4 ÷ x^2 = x^2\).  
     \(x^2(x^2+1)= x^4+x^2\).  
     Soustraction : \((x^4+2x^3+1) - (x^4+x^2)= 2x^3 - x^2 + 1\) (c'est-à-dire \(2x^3+2x^2+1\)).  
  3. \(2x^3 ÷ x^2 = 2x\).  
     \(2x(x^2+1)= 2x^3+2x\).  
     Soustraction : \((2x^3+2x^2+1) - (2x^3+2x)= 2x^2 - 2x + 1\) (or \(-2 \equiv 1\) mod 3, donc \(2x^2+x+1\)).  
  4. \(2x^2 ÷ x^2 = 2\).  
     \(2(x^2+1)= 2x^2+2\).  
     Soustraction : \((2x^2+x+1) - (2x^2+2)= x - 1\) (avec \(-1 \equiv 2\) mod 3, on obtient \(x+2\)).  

  **Quotient** : \(x^3+x^2+2x+2\)  
  **Reste** : \(x+2\).

---

### 2.2 Calcul du produit  
\[
(x^7+x^5+x^2+1) \cdot (x^9+x^3+x^2+x+1)
\]

- **Dans ℤ₂[x]** :  
  Chaque coefficient est 1 et la somme se fait modulo 2 (addition XOR). En listant les sommes d’exposants et en réduisant modulo 2, on trouve :  
  \[
  x^{16}+x^{14}+x^{11}+x^{10}+x^6+x^4+x+1.
  \]

- **Dans ℤ₃[x]** :  
  On compte le nombre de fois où chaque exposant apparaît (les coefficients se réduisant modulo 3). Le résultat est :
  \[
  x^{16} + x^{14} + x^{11} + x^{10} + 2x^9 + 2x^8 + 2x^7 + x^6 + 2x^5 + x^4 + 2x^3 + 2x^2 + x + 1.
  \]

---

### 2.3 Calcul du PGCD  
Trouver \(\gcd(x^8+x^7+x^6+x^4+x^2+1,\; x^4+1)\).

- **Dans ℤ₂[x]** :  
  En appliquant l’algorithme d’Euclide, on trouve successivement :
  - \(x^8+x^7+x^6+x^4+x^2+1 = (x^4)(x^4+1) + (x^7+x^6+x^2+1)\)
  - Puis, en poursuivant la division, on obtient finalement un reste égal à \(x+1\).  
  **PGCD** : \(x+1\).

- **Dans ℤ₃[x]** :  
  Le même procédé mène à un PGCD constant (associé à 1).  
  **PGCD** : 1.

---

### 2.4 Calcul de l’inverse de  
\(x+1\) modulo \(x^2+x+1\)

- **Dans ℤ₂[x]** :  
  On cherche \(Q(x)= ax+b\) tel que  
  \[
  (x+1)(ax+b) \equiv 1 \quad (\text{mod } x^2+x+1).
  \]
  En passant modulo \(x^2+x+1\) (où \(x^2 \equiv x+1\)), on trouve que \(Q(x)= x\) convient (car \((x+1)x=x^2+x \equiv (x+1)+x=1\) dans ℤ₂, puisque \(1=-1\)).  
  **Inverse dans ℤ₂[x]** : \(x\).

- **Dans ℤ₃[x]** :  
  De même, on montre que l’inverse de \(x+1\) est \(2x\) (car \((x+1)(2x)=2x^2+2x\) et, en remplaçant \(x^2\) par \(-x-1\) dans ℤ₃, on obtient \(2(-x-1)+2x=-2\equiv 1\) mod 3).  
  **Inverse dans ℤ₃[x]** : \(2x\).

---

## Exercice 3 : Corps finis

### 3.1 Existence de corps de cardinal donné

Un corps fini existe si et seulement si son nombre d’éléments est une puissance d’un nombre premier \(p^n\).

- **7 éléments** : \(7=7^1\) → Oui.
- **15 éléments** : \(15=3\times5\) (pas une puissance d’un seul premier) → Non.
- **81 éléments** : \(81=3^4\) → Oui.
- **100 éléments** : \(100=2^2 \times 5^2\) → Non.
- **157 éléments** : 157 est premier → Oui.
- **10001 éléments** : \(10001=73\times137\) → Non.

### 3.2 Pour le corps GF(37)

- **Caractéristique** : 37.
- **Groupe additif** : 37 éléments.
- **Groupe multiplicatif** : 37 – 1 = 36 éléments.

### 3.3 Construction d’un corps à 5 éléments

On prend GF(5) = ℤ₅. Les tables sont :

**Table d’addition (mod 5) :**

| + | 0 | 1 | 2 | 3 | 4 |
|:-:|:-:|:-:|:-:|:-:|:-:|
| **0** | 0 | 1 | 2 | 3 | 4 |
| **1** | 1 | 2 | 3 | 4 | 0 |
| **2** | 2 | 3 | 4 | 0 | 1 |
| **3** | 3 | 4 | 0 | 1 | 2 |
| **4** | 4 | 0 | 1 | 2 | 3 |

**Table de multiplication (mod 5) :**

| × | 0 | 1 | 2 | 3 | 4 |
|:-:|:-:|:-:|:-:|:-:|:-:|
| **0** | 0 | 0 | 0 | 0 | 0 |
| **1** | 0 | 1 | 2 | 3 | 4 |
| **2** | 0 | 2 | 4 | 1 | 3 |
| **3** | 0 | 3 | 1 | 4 | 2 |
| **4** | 0 | 4 | 3 | 2 | 1 |

### 3.4 Tables de Z₂[x]/(x²+x+1)

Dans ce corps à 4 éléments, on peut représenter les éléments par :  
\[
\{0,\; 1,\; x,\; x+1\},
\]
avec la relation \(x^2 = x+1\).

**Table d’addition :**

| +   | 0   | 1   | x   | x+1 |
|-----|-----|-----|-----|-----|
| **0**   | 0   | 1   | x   | x+1 |
| **1**   | 1   | 0   | x+1 | x   |
| **x**   | x   | x+1 | 0   | 1   |
| **x+1** | x+1 | x   | 1   | 0   |

**Table de multiplication :**

| ×   | 0   | 1   | x     | x+1   |
|-----|-----|-----|-------|-------|
| **0**   | 0   | 0   | 0     | 0     |
| **1**   | 0   | 1   | x     | x+1   |
| **x**   | 0   | x   | x+1   | 1     |
| **x+1** | 0   | x+1 | 1     | x     |

*(On vérifie par exemple : \(x\cdot x = x^2 = x+1\) et \(x\cdot (x+1) = x^2+x = (x+1)+x = 1\) dans ℤ₂.)*

### 3.5 Polynôme \(p(x)=x^4+x^3+x^2+x+1\) sur GF(2)

On montre que dans le corps \(GF(2)[x]/(p(x))\) (qui a 16 éléments, donc son groupe multiplicatif est cyclique d’ordre 15), l’élément « x » n’engendre pas tout le groupe.  
En effet, en utilisant la relation imposée par \(p(x)=0\) :
\[
x^4+x^3+x^2+x+1=0 \quad\Rightarrow\quad x^4 = x^3+x^2+x+1,
\]
on peut calculer :
\[
x^5 = x\cdot x^4 = x(x^3+x^2+x+1)= x^4+x^3+x^2+x.
\]
Mais en substituant \(x^4\) par \(x^3+x^2+x+1\) on trouve :
\[
x^5 = (x^3+x^2+x+1)+ x^3+x^2+x = 1.
\]
Ainsi, l’ordre de \(x\) divise 5 (et ici \(x^5=1\)), or 5 est strictement inférieur à 15.  
**Conclusion** : \(x\) n’engendre pas \((GF(2)[x]/(p(x)))^*\).

### 3.6 Construction de GF(16) et GF(25)

- **GF(16)** : Un corps à 16 éléments se construit comme  
  \[
  GF(16) \cong \mathbb{Z}_2[x]/(p(x))
  \]
  où \(p(x)\) est un polynôme irréductible de degré 4. Par exemple, on peut prendre  
  \[
  p(x)= x^4+x+1.
  \]

- **GF(25)** : Un corps à 25 éléments se construit comme  
  \[
  GF(25) \cong \mathbb{Z}_5[x]/(q(x))
  \]
  où \(q(x)\) est un polynôme irréductible de degré 2 sur ℤ₅. Par exemple, \(q(x)= x^2+x+2\) est irréductible dans ℤ₅ (aucune valeur de \(x \in \{0,1,2,3,4\}\) ne vérifie \(x^2+x+2=0\) mod 5).

---

## Exercice 4 : Identité remarquable

Pour un nombre premier \(p\), le binôme de Newton montre que pour tout entier \(k\) avec \(1\le k\le p-1\), le coefficient \(\binom{p}{k}\) est divisible par \(p\) (et donc nul dans \(\mathbb{Z}_p\)).  
Il suit que :
\[
(a+b)^p = a^p + b^p \quad \text{dans } \mathbb{Z}_p.
\]
De plus, d’après le petit théorème de Fermat, \(a^p = a\) pour tout \(a\) dans \(\mathbb{Z}_p\), d’où :
\[
(a+b)^p = a+b.
\]

---

## Exercice 5 : Polynômes irréductibles

### 5.1 Tous les polynômes irréductibles de degré 2 dans ℤ₂[x]

Les polynômes moniques de degré 2 dans ℤ₂[x] sont de la forme :
\[
x^2+ax+b,\quad a,b\in\{0,1\}.
\]
On a alors :
- \(x^2\) (non de degré 2, ou bien réductible car \(x^2=x\cdot x\)).  
- \(x^2+1\) : pour \(x=1\), \(1+1=0\) → réductible (se factorise en \((x+1)^2\)).  
- \(x^2+x\) : factorisable en \(x(x+1)\).  
- \(x^2+x+1\) : pour \(x=0\), donne 1 ; pour \(x=1\), \(1+1+1=3\equiv1\) mod2. Aucun zéro dans ℤ₂.  
**Conclusion** : Le seul polynôme irréductible de degré 2 (à multiplication par unité près) est  
\[
x^2+x+1.
\]

### 5.2 Le polynôme \(x^4+x^2+1\)  
- **Dans ℤ₂[x]** :  
  On vérifie que  
  \[
  (x^2+x+1)^2 = x^4 + 2x^3 + 3x^2 + 2x + 1,
  \]
  or dans ℤ₂, \(2\equiv0\) et \(3\equiv1\), ce qui donne  
  \[
  (x^2+x+1)^2 = x^4+x^2+1.
  \]
  Ainsi, \(x^4+x^2+1\) est réductible (c’est un carré).

- **Dans ℤ₃[x]** :  
  On constate que \(x=1\) est racine car  
  \[
  1^4+1^2+1 = 1+1+1=3\equiv0\text{ mod 3},
  \]
  et de même \(x=-1\) (i.e. \(x=2\) mod 3) est racine. En fait, on peut montrer que  
  \[
  x^4+x^2+1=(x-1)^2(x+1)^2 \quad \text{dans } \mathbb{Z}_3[x].
  \]
  Donc, \(x^4+x^2+1\) est également réductible dans ℤ₃[x].

---

## Exercice 6 : Exercice Pratique  
Nous travaillons dans le corps à 256 éléments
\[
GF(256) \cong \mathbb{Z}_2[x]/(x^8+x^4+x^3+x+1).
\]
Notons que l’addition se fait via le XOR. Voici un exemple de code Python qui implémente :

1. Une routine d’addition,  
2. Une routine de multiplication,  
3. Une routine de calcul de l’inverse multiplicatif.

```python
# Polynôme irréductible pour GF(256) : x⁸ + x⁴ + x³ + x + 1
# Ce polynôme est utilisé notamment dans l’AES et est représenté par 0x11B.
IRRED_POLY = 0x11B

def gf256_add(a, b):
    """Addition dans GF(256) : opération XOR."""
    return a ^ b

def gf256_mult(a, b):
    """Multiplication dans GF(256) modulo le polynôme irréductible."""
    result = 0
    for _ in range(8):
        if b & 1:
            result ^= a
        carry = a & 0x80  # bit de poids fort
        a <<= 1
        if carry:
            a ^= IRRED_POLY
        a &= 0xFF  # on garde un octet
        b >>= 1
    return result

def gf256_pow(a, power):
    """Exponenciation dans GF(256) par exponentiation rapide."""
    result = 1
    while power:
        if power & 1:
            result = gf256_mult(result, a)
        a = gf256_mult(a, a)
        power //= 2
    return result

def gf256_inv(a):
    """Calcul de l'inverse multiplicatif dans GF(256) par exponentiation.
       Dans un corps à 256 éléments, a^(254) = a^(-1) pour tout a ≠ 0."""
    if a == 0:
        raise ValueError("0 n'a pas d'inverse dans GF(256)")
    return gf256_pow(a, 254)

# Exemples de test
if __name__ == "__main__":
    a, b = 0x57, 0x83  # exemples d'éléments dans GF(256)
    
    print("Addition : 0x57 ⊕ 0x83 =", hex(gf256_add(a, b)))
    print("Multiplication : 0x57 * 0x83 =", hex(gf256_mult(a, b)))
    
    a_inv = gf256_inv(a)
    print("Inverse de 0x57 =", hex(a_inv))
    print("Vérification : 0x57 * (inverse) =", hex(gf256_mult(a, a_inv)))
```

Ce code définit :
- **gf256_add** pour l’addition (opération XOR),  
- **gf256_mult** pour la multiplication modulo le polynôme 0x11B,  
- **gf256_inv** qui calcule l’inverse multiplicatif en utilisant l’exponentiation (car dans GF(256), pour \(a\neq0\), on a \(a^{254}=a^{-1}\)).
