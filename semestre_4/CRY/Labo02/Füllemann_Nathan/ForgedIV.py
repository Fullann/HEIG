from Crypto.Cipher import AES
from Crypto.Util.strxor import strxor as xor
import base64

# Données fournies
m1 = b'This is a Test !'
iv2 = b'W5ZS9Yu3dEs3hDtB'
c1_b64 = b'2s9IB8rcQZh/Gljgb+WWQw=='
t1_b64 = b'MD4tYk+xhF1j58oX7m3AXA=='
mChall = b'100.00CHF to ADC'

# Décodage des données
c1 = base64.b64decode(c1_b64)
t1 = base64.b64decode(t1_b64)

# Récupération du keystream (même IV => même séquence)
keystream = xor(c1, m1)

# Chiffrement du message cible
c_chall = xor(mChall, keystream[:len(mChall)])

# Encodage en base64
c_chall_b64 = base64.b64encode(c_chall).decode()
t_forged_b64 = base64.b64encode(t1).decode()  # Réutilisation du tag existant

print(f"IV forgé : {base64.b64encode(iv2).decode()}")
print(f"Cihertext forgé : {c_chall_b64}")
print(f"Tag forgé : {t_forged_b64}")