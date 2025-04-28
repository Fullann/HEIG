from Crypto.Cipher import AES
from Crypto.Util.strxor import strxor
import itertools
import string
import base64
raw_bytes = base64.b64decode(b'zZFA10Jx7vH5g/liWgyzWfXCuiM7GOEEUtFNeeN64xq9Pa6SbjY9+nAbuE2JCjl7y69uO4zHRZTYmT2Yi925Ag==')
hex_hash = raw_bytes.hex()

TARGET_HASH = bytes.fromhex(hex_hash) 

H0 = TARGET_HASH[:15]
H1 = TARGET_HASH[15:]

cipher = AES.new(b"\x07"*16, AES.MODE_ECB)

## Étape 1 : Trouver S_absorb en bruteforçant le 16ème byte
S_absorb = None
for x in range(256):
    candidate = H0 + bytes([x])
    if cipher.encrypt(candidate)[0] == H1[0]:
        S_absorb = candidate
        break

if not S_absorb:
    print("Échec : S_absorb non trouvé")
    exit()

## Étape 2 : Calculer l'état avant permutation finale
state_before_perm = cipher.decrypt(S_absorb)

## Étape 3 : Bruteforce des 3 derniers caractères
print("Bruteforce des caractères manquants...")
for chars in itertools.product(string.printable, repeat=3):
    # Construction de block1 avec les 3 caractères et le padding
    block1 = ''.join(chars).encode('latin-1') + b'}' + b'\x80' + bytes(10)
    
    # Calcul de la partie connue de state_after_block0
    state_part = strxor(state_before_perm[:15], block1)
    
    # Construction du candidat state_after_block0 complet
    state_candidate = state_part + bytes([state_before_perm[15]])
    
    # Décryptage pour vérifier la structure
    decrypted = cipher.decrypt(state_candidate)
    
    if decrypted.startswith(b'FLAG{') and decrypted[15] == 0:
        # Extraction des parties du flag
        known_part = decrypted[5:15].decode()
        flag = f"FLAG{{{known_part}{''.join(chars)}}}"
        print("\nFlag trouvé :", flag)
        exit()

print("Aucun flag valide trouvé")
