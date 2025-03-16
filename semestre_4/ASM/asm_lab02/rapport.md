# **Rapport – Laboratoire ASM_Lab02**

## **Étape 2 : Compilation pour l'architecture x86**
> **a) Dans le répertoire x86, compiler les sources avec la commande make.**  

**Toolchain utilisée :**  
`i686-linux-gcc`  

---

## **Étape 3 : Compilation pour l'architecture ARM**
> **a) Dans le répertoire arm, compiler les sources avec la commande make.**  

**Toolchain utilisée :**  
`arm-linux-gnueabihf-gcc`  

---

## **Étape 4 : Déploiement et test de l'application sur cible ARM**
> **i) Compiler, déployer sur la cible ARM et tester l’application à l’aide du debugger. Mettre un breakpoint à l’entrée de la fonction « main() » (fichier podometer.c) par exemple, et faire du pas-à-pas sur quelques instructions.**  

### **Commande de déploiement et exécution sous U-Boot :**
```sh
setenv podometer "tftp arm/makefiles/podometer/podometer.bin"
run podometer
go 0x82000000
```
### **Débogage :**  
1. Lancer GDB et se connecter à la cible ARM.  
2. Placer un breakpoint dans la fonction `main()` :
   ```sh
   b main
   ```
3. Lancer le programme en mode pas-à-pas pour observer son comportement :
   ```sh
   c  # Continue l’exécution jusqu’au breakpoint
   si # Exécute les instructions une par une
   ```

---

## **Étape 5 : Débogage et contournement du check_password()**
> **g) Une fois votre approche validée, la décrire dans le fichier « crackme_reg.txt » à la racine du dossier « asm_lab02 ».**  

### **Approche utilisée pour contourner la vérification du mot de passe :**  
#### **Architecture ARM :**  
1. Placer un breakpoint sur la fonction `check_password()` au niveau du `return` :
   ```sh
   b check_password
   ```
2. Lancer le programme et entrer un mot de passe quelconque.  
3. Avancer en pas-à-pas jusqu'à l’instruction de comparaison `if` située à **l’adresse 0x82000194**.  
4. Observer que la comparaison est effectuée entre :  
   - Le registre `r3` (résultat de `strcmp()` sur le hash du mot de passe).  
   - La valeur `0` (indiquant un hash valide).  
5. Modifier la valeur du registre `r3` pour forcer la validation :
   ```sh
   set $r3=1
   ```
6. Continuer l’exécution :
   ```sh
   c
   ```
7. Résultat : le programme affiche **"Good job !"** sans avoir entré le bon mot de passe.  

### **Autres approches possibles pour contourner `check_password()` :**  
- Modifier **r2** ou **r3** pour qu’ils correspondent lors de la comparaison des hash (à l'adresse **0x82000070**).  
- Modifier directement le code en mémoire avant son exécution (patching).  

### **Pourquoi ne pas modifier directement le registre `PC` (Program Counter) ?**  
Changer directement la valeur du `PC` pour exécuter `printf("Good job !")` n’est pas une bonne approche car :  
1. Cela ne simulerait pas une authentification réelle.  
2. Le programme pourrait manquer des étapes cruciales, comme la génération et l'envoi d'un **cookie d’identification**.  
3. Certaines fonctions internes pourraient dépendre de cette authentification, ce qui entraînerait des incohérences dans le programme.  

---

## **Étape 6 : Patching direct du binaire**
> **x86 : Modifier le binaire en mémoire pour contourner la vérification.**  

### **Méthode utilisée :**  
1. Identifier l’instruction de saut conditionnel (`je`) qui empêche l’affichage du message.  
2. Repérer son adresse :  
   ```
   0x4011d: 74 21  je  0x40140 <main+0xea>
   ```
3. Modifier cette instruction pour la remplacer par des **NOPs** (instructions ne faisant rien).  
4. Commandes utilisées sous U-Boot :
   ```sh
   md.w 0x4011d       # Vérifier la valeur actuelle
   mw.w 0x4011d 0x9090  # Remplacer "je" par deux NOP (0x90 0x90)
   md.w 0x4011d       # Vérifier la modification
   go 0x40000        # Exécuter le programme
   ```
5. Résultat :  
   - L’instruction de saut (`je`) est supprimée.  
   - Le programme affiche immédiatement `"Good job !"` sans vérifier le mot de passe.  
