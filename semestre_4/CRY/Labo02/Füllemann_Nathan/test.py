from speck import Speck
import base64
from collections import defaultdict

# Charger le ciphertext
with open("Füllemann_Nathan-speck.txt", "r") as f:
    ct = base64.b64decode(f.read())

# Paramètres Speck (à adapter selon speck.py)
KEY = b"\x01\x23\x45\x67\x89\xab\xcd\xef"  # Clé de la tour radio (exemple)
BLOCK_SIZE = 4  # 32 bits

# Initialiser Speck
speck = Speck(KEY, block_size=32)

# Découpage en blocs de 4 octets
blocks = [ct[i:i+BLOCK_SIZE] for i in range(0, len(ct), BLOCK_SIZE)]

# Dictionnaire pour compter les candidats
password_candidates = defaultdict(int)

# Analyser les paires de blocs
for i in range(1, len(blocks)):
    prev_block = blocks[i-1]
    current_block = blocks[i]
    
    # Décrypter et XOR avec le bloc précédent
    decrypted = speck.decrypt(current_block)
    candidate = bytes([a ^ b for a, b in zip(decrypted, prev_block)])
    
    password_candidates[candidate] += 1

# Trouver le candidat le plus fréquent
password = max(password_candidates, key=password_candidates.get)
print(f"Mot de passe trouvé : {password.decode()}")
