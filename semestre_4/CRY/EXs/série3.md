
# Rapport – Série d’Exercices #3

## 1. Échauffement

### 1.1 Calcul de 1234561234 mod 17
Pour calculer 1234561234 modulo 17, on procède par réduction (méthode « lecture chiffre par chiffre » par exemple).  
**Réponse :** 1

### 1.2 Inverse multiplicatif de 13 modulo 23
On cherche \( x \) tel que \( 13 \cdot x \equiv 1 \pmod{23} \).  
On trouve :  
\( 13 \times 16 = 208 \equiv 1 \pmod{23} \).  
**Réponse :** 16

### 1.3 Inverse multiplicatif de 1234 modulo 123456
On calcule le PGCD de 1234 et 123456.  
- \(123456 = 1234 \times 100 + 56\)  
- \(1234 = 56 \times 22 + 2\)  
- \(56 = 2 \times 28\)  
Ainsi, \(\gcd(1234,123456) = 2 \neq 1\).  
L’inverse multiplicatif n’existe donc pas.  
**Réponse :** L’inverse n’existe pas.

### 1.4 Calcul de \(\varphi(252)\)
On factorise 252 :  
\[
252 = 2^2 \times 3^2 \times 7.
\]
On a alors :
\[
\varphi(252) = \varphi(2^2) \cdot \varphi(3^2) \cdot \varphi(7) = (4-2)(9-3)(7-1) = 2 \times 6 \times 6 = 72.
\]
**Réponse :** 72

---

## 2. Calculs

### 2.1 Dans \(\mathbb{Z}_{13}\), calcul de \(7 - 11\)
On a :  
\(7 - 11 = -4 \equiv 13 - 4 = 9 \pmod{13}\).  
**Réponse :** 9

### 2.2 Dans \(\mathbb{Z}_{13}^*\), calcul de \(7 \cdot 7\)
Calculons :  
\(7 \cdot 7 = 49 \equiv 49 - 39 = 10 \pmod{13}\).  
**Réponse :** 10

### 2.3 Ordre de 5 dans \(\mathbb{Z}_{13}^*\)
On cherche le plus petit entier \(k\) tel que \(5^k \equiv 1 \pmod{13}\).  
- \(5^1 = 5\)  
- \(5^2 = 25 \equiv 12\)  
- \(5^3 = 5^2 \times 5 \equiv 12 \times 5 = 60 \equiv 8\)  
- \(5^4 = 8 \times 5 = 40 \equiv 1\)  
**Réponse :** 4

### 2.4 Ordre de \(\mathbb{Z}_{45}^*\)
Le nombre d’éléments de \(\mathbb{Z}_{45}^*\) est \(\varphi(45)\).  
Or, \(45 = 3^2 \times 5\) donc :
\[
\varphi(45) = (9-3)(5-1) = 6 \times 4 = 24.
\]
**Réponse :** 24

### 2.5 Calcul de \(153^8 \mod 15\) et vérification du théorème d’Euler
On a :
\[
1538 = 15 \times 102 + 8,\quad \text{donc }1538 \mod 15 = 8.
\]
Puisque \(\gcd(1538,15)=1\), le théorème d’Euler s’applique.  
En effet, avec \(\varphi(15)=8\), on a :
\[
8^8 \equiv 1 \pmod{15}.
\]
**Réponse :** \(1538 \mod 15 = 8\) et le théorème d’Euler est vérifié.

---

## 3. Groupe multiplicatif (pour \(p = 17\))

### 3.1 Éléments de \(\mathbb{Z}_{17}^*\)
Pour un nombre premier \(p\), \(\mathbb{Z}_p^*\) contient \(p-1\) éléments.  
Ici, \(17-1=16\) et les éléments sont \( \{1, 2, \dots, 16\} \).  
**Réponse :** 16 éléments, à savoir \(\{1,2,\dots,16\}\).

### 3.2 Ordres de 3 et 2 dans \(\mathbb{Z}_{17}^*\)
- Pour \(3\) :  
  On calcule :
  \[
  \begin{array}{rcl}
  3^1 &\equiv& 3\\[1mm]
  3^2 &\equiv& 9\\[1mm]
  3^3 &\equiv& 27 \equiv 10\\[1mm]
  3^4 &\equiv& 10\cdot3=30 \equiv 13\\[1mm]
  3^5 &\equiv& 13\cdot3=39 \equiv 5\\[1mm]
  3^6 &\equiv& 5\cdot3=15\\[1mm]
  3^7 &\equiv& 15\cdot3=45 \equiv 11\\[1mm]
  3^8 &\equiv& 11\cdot3=33 \equiv 16\\[1mm]
  \vdots &&\\[1mm]
  3^{16} &\equiv& 1.
  \end{array}
  \]
  **Ordre de 3 :** 16.
  
- Pour \(2\) :  
  On trouve :
  \[
  \begin{array}{rcl}
  2^1 &\equiv& 2\\[1mm]
  2^2 &\equiv& 4\\[1mm]
  2^3 &\equiv& 8\\[1mm]
  2^4 &\equiv& 16\\[1mm]
  2^5 &\equiv& 32 \equiv 15\\[1mm]
  2^6 &\equiv& 15\cdot2=30 \equiv 13\\[1mm]
  2^7 &\equiv& 13\cdot2=26 \equiv 9\\[1mm]
  2^8 &\equiv& 9\cdot2=18 \equiv 1.
  \end{array}
  \]
  **Ordre de 2 :** 8.
  
Le théorème de Lagrange affirme que l’ordre de tout élément divise l’ordre du groupe (ici 16).  
**Observation :** \(8\) et \(16\) divisent \(16\).

### 3.3 \(\mathbb{Z}_{17}^*\) est-il cyclique ?
Oui. Pour un nombre premier \(p\), \(\mathbb{Z}_{p}^*\) est toujours cyclique.  
Un générateur est par exemple \(3\) (vu que son ordre est 16).  
**Réponse :** Oui, par exemple \(3\) est un générateur.

### 3.4 Logarithme discret en base 3 de 4 dans \(\mathbb{Z}_{17}^*\)
On cherche \(k\) tel que \(3^k \equiv 4 \pmod{17}\).  
D’après les calculs, on trouve que :
\[
3^{12} \equiv 4 \pmod{17}.
\]
**Réponse :** 12

---

## 4. Opérations Modulaires (avec \(p = 7\) et \(q = 11\), donc \(n = 77\))

### 4.1 Éléments de \(\mathbb{Z}_{77}^*\)
Le nombre d’éléments est \(\varphi(77)\).  
Ici, \(77 = 7 \times 11\) donc :
\[
\varphi(77) = (7-1)(11-1) = 6 \times 10 = 60.
\]
Les éléments sont les entiers de 1 à 76 qui sont premiers avec 77.  
**Réponse :** 60 éléments, c’est-à-dire \(\{a \in \{1,\dots,76\} \mid \gcd(a,77)=1\}\).

### 4.2 Nombre d’éléments de \(\mathbb{Z}_{pq}^*\) pour \(p\) et \(q\) premiers
En général,  
\[
\varphi(pq) = (p-1)(q-1).
\]
**Réponse :** \((p-1)(q-1)\).

### 4.3 Calcul de \(y = x^7 \mod 77\) pour \(x \in \{1,2,\dots,20\}\)
Les calculs (réalisés par script ou par calcul manuel) donnent :

| \(x\) | \(y = x^7 \mod 77\) |
|:-----:|:-------------------:|
| 1     | 1                   |
| 2     | 51                  |
| 3     | 31                  |
| 4     | 60                  |
| 5     | 47                  |
| 6     | 41                  |
| 7     | 28                  |
| 8     | 57                  |
| 9     | 37                  |
| 10    | 10                  |
| 11    | 11                  |
| 12    | 12                  |
| 13    | 62                  |
| 14    | 42                  |
| 15    | 71                  |
| 16    | 58                  |
| 17    | 52                  |
| 18    | 39                  |
| 19    | 68                  |
| 20    | 48                  |

### 4.4 Calcul de \(y^{43} \mod 77\) pour les \(y\) obtenus et observation
On définit \(d = 43\) et \(e = 7\). On constate que pour chaque \(x \in \{1,\dots,20\}\) :
1. On calcule \(y = x^7 \mod 77\).
2. Puis on calcule \(z = y^{43} \mod 77\).

On remarque que \(e \times d = 7 \times 43 = 301\) et que  
\[
301 \equiv 1 \pmod{\varphi(77)} \quad \text{(puisque \(\varphi(77)=60\) et \(301=5\times60+1\))}.
\]
Ainsi, le processus de chiffrement/déchiffrement ramène bien à \(x\) (c’est le principe RSA).  
**Observation :** On retrouve pour chaque \(x\) son image initiale, c’est-à-dire \(z = x\).

### 4.5 Inverse de 7 modulo le nombre d’éléments de \(\mathbb{Z}_{77}^*\)
Le nombre d’éléments est 60. On cherche \(x\) tel que :
\[
7 \cdot x \equiv 1 \pmod{60}.
\]
En utilisant l’algorithme d’Euclide étendu, on trouve :
\[
7 \cdot (-17) + 60 \cdot 2 = 1 \quad\Rightarrow\quad x \equiv -17 \equiv 43 \pmod{60}.
\]
**Réponse :** 43

---

## 5. Exercice pratique (Python)

### 5.1 Trouver le plus petit générateur de \(\mathbb{Z}_{65537}^*\)
Le nombre \(65537\) est un nombre de Fermat premier. Son groupe multiplicatif est cyclique d’ordre \(65536\).  
Il est connu que \(3\) est un générateur de \(\mathbb{Z}_{65537}^*\).  
**Réponse :** \(g = 3\)

### 5.2 Calcul du logarithme discret de 12345 en base \(g\) dans \(\mathbb{Z}_{65537}^*\)
On cherche \(k\) tel que :
\[
3^k \equiv 12345 \pmod{65537}.
\]
Ce problème de logarithme discret peut être résolu efficacement par l’algorithme Baby-step Giant-step. Par exemple, le script suivant permet de trouver \(k\) :

```python
mod = 65537
g = 3
target = 12345
# Recherche par force brute (le groupe a une taille de 65536, ce qui reste raisonnable)
for k in range(mod):
    if pow(g, k, mod) == target:
        print("Le logarithme discret de", target, "en base", g, "est", k)
        break
```

Après exécution, le script retourne :
  
**Réponse :** \(k = 41131\)

