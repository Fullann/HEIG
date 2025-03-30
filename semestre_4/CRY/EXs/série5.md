## Exercice 1 : Mauvaise Implémentation de ChaCha20 (style CTF)
### Schéma
```
         ┌─────────────────────────────┐
         │  État initial               │
         │  = [constantes | clé | pos | nonce] │
         └──────────────┬──────────────┘
                        │
                        ▼
         ┌─────────────────────────────┐
         │  10 double-rounds ChaCha20  │
         │     (fonction f)            │
         └──────────────┬──────────────┘
                        │
          (étape finale manquante : ajout de l’état initial)
                        │
                        ▼
         ┌─────────────────────────────┐
         │   Keystream = f(état initial)│
         └──────────────┬──────────────┘
                        │
                        ▼
         ┌─────────────────────────────┐
         │ XOR avec le texte en clair  │
         └─────────────────────────────┘
                        │
                        ▼
         ┌─────────────────────────────┐
         │     Texte chiffré           │
         └─────────────────────────────┘
```
### Déchifrement


## Exercice 2 : 

**Contexte :**  
On travaille dans GF(2⁸) avec le polynôme irréductible  
\(m(x)=x^8+x^4+x^3+x+1\).

1. **0x2b** :  
   0x2b en binaire est 00101011, donc  
   \[
   0x2b = x^5+x^3+x+1.
   \]

2. **Addition 0x53 + 0xb8** :  
   \(0x53 = 01010011_2\) et \(0xb8 = 10111000_2\).  
   Leur XOR donne 11101011, soit 0xEB.

3. **Multiplication 0x21 × 0x25** :  
   \(0x21 = x^5+1\) et \(0x25 = x^5+x^2+1\).  
   Le produit est \( (x^5+1)(x^5+x^2+1)= x^{10}+x^7+x^2+1\).  
   En réduisant avec \(x^8=x^4+x^3+x+1\), on obtient  
   \[
   x^7+x^6+x^5+x^3+1,
   \]
   soit 0xE9.

4. **Inverse de 0x02** :  
   0x02 correspond à \(x\).  
   En appliquant l’algorithme d’Euclide étendu, on trouve  
   \[
   x\cdot(x^7+x^3+x^2+1)\equiv 1,
   \]
   donc l’inverse de 0x02 est 0x8D.