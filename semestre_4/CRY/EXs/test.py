def polybe_decrypt(ciphertext, grid, key, perm):
    # Construire la grille de chiffrement sous forme de dictionnaire
    mapping = {}
    index = 0
    for char in grid:
        mapping[char] = grid[index]
        index += 1
    
    # Appliquer la permutation inverse pour retrouver l'ordre original
    perm_inverse = sorted(range(len(perm)), key=lambda k: perm[k])
    
    # Séparer le texte en groupes de longueur correspondante à la permutation
    chunks = ciphertext.split()
    decrypted_chunks = []
    
    for chunk in chunks:
        if len(chunk) == len(perm):
            reordered_chunk = ''.join(chunk[i] for i in perm_inverse)
            decrypted_chunks.append(reordered_chunk)
        else:
            decrypted_chunks.append(chunk)  # Conserver les parties non affectées
    
    # Décoder chaque lettre via la grille de chiffrement
    decrypted_text = ''.join(mapping.get(letter, letter) for letter in ' '.join(decrypted_chunks))
    
    return decrypted_text

# Définition des paramètres
ciphertext = "VVVDA AGVVG VVDAA GXXFF FVVAG VAVFF VVAGG VDVVV XAXDX DVVVA AXVXV XVGDF VFAFX VGFFV AX"
grid = "a1b2c3d4e5f6g7h8i9j0klmnopqrstuvwxyz"
key = "LARS"
perm = [2, 1, 3, 4]

# Déchiffrement
result = polybe_decrypt(ciphertext, grid, key, perm)
print("Texte déchiffré :", result)
