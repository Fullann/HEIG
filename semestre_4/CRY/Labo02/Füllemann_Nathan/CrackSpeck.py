import base64
from collections import defaultdict

# Lecture et décodage du fichier en mode binaire
with open("Füllemann_Nathan-speck.txt", "rb") as f:
    ct_base64 = f.read()
ct = base64.b64decode(ct_base64)

# Découpage en blocs de 4 octets
block_size = 4
blocks = [ct[i:i+block_size] for i in range(0, len(ct), block_size)]

# Recherche de la paire valide la plus fréquente
pair_counts = defaultdict(int)
valid_pairs = []

for i in range(len(blocks) - 1):
    c_a = blocks[i]
    c_b = blocks[i+1]
    
    # Calcul du XOR byte par byte
    xor_bytes = bytes([a ^ b for a, b in zip(c_a, c_b)])
    
    # Vérification des caractères ASCII imprimables
    if all(32 <= b <= 126 for b in xor_bytes):
        pair = (c_a, c_b)
        pair_counts[pair] += 1
        valid_pairs.append(xor_bytes)

if valid_pairs:
    # Sélection du XOR le plus fréquent
    from collections import Counter
    most_common_xor = Counter(valid_pairs).most_common(1)[0][0]
    password = most_common_xor.decode('ascii')
    print(f"Mot de passe trouvé : {password}")
else:
    print("Aucun motif valide détecté")
