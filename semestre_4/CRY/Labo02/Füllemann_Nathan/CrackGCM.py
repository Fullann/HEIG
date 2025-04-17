from Crypto.Cipher import AES
from Crypto.Util import strxor
from Crypto.Util.Padding import pad
import base64
import hashlib

BLOCK_SIZE = 16
IV_SIZE = 12
COUNTER_SIZE = BLOCK_SIZE - IV_SIZE

# Fonctions fournies dans l'énoncé
def xor(a, b):
    return strxor.strxor(a, b)

def f(x):
    b = '{:0{width}b}'.format(int.from_bytes(x, 'little'), width=128)
    return int(b[::-1], 2).to_bytes(16, 'little')

# Implémentation GCM avec l'erreur conservée
class FlawedGCM:
    def __init__(self, key):
        self.key = key
        self.cipher = AES.new(key, AES.MODE_ECB)
        
    def authenticate(self, ct, T):
        # Création explicite de l'anneau et récupération de la variable y
        G = PolynomialRing(GF(2), 'y')
        y = G.gen()
        
        # Création du corps fini avec le modulus correct
        F = GF(2^128, modulus=y^128 + y^7 + y^2 + y + 1, names='x')
        x = F.gen()
        
        # Calcul de H avec la variable y
        H = self._strToPoly(f(self.cipher.encrypt(b"\x00"*BLOCK_SIZE)), y)
        
        tag = b"\x00"*BLOCK_SIZE
        for i in range(len(ct)//BLOCK_SIZE):
            tag = xor(tag, f(ct[BLOCK_SIZE*i: BLOCK_SIZE*(i+1)]))
            tag = self._multByH(tag, H, y)  # On passe y explicitement
        
        tag = xor(tag, f(T))
        return f(tag)


    
    def encrypt(self, iv, plaintext):
        ciphertext = self._CTR(iv, plaintext)
        T = self.cipher.encrypt(iv + b"\x00"*(COUNTER_SIZE-1) + b"\x01")
        tag = self.authenticate(ciphertext, T)
        return ciphertext, tag
    
    def decrypt(self, iv, ciphertext, tag):
        T = self.cipher.encrypt(iv + b"\x00"*(COUNTER_SIZE-1) + b"\x01")
        calculated_tag = self.authenticate(ciphertext, T)
        
        if calculated_tag != tag:
            raise Exception("Tag invalide")
            
        return self._CTR(iv, ciphertext)
    
    def _CTR(self, iv, message):
        ctr = iv + b"\x00"*(COUNTER_SIZE-1) + b"\x02"
        ciphertext = []
        for i in range(0, len(message), BLOCK_SIZE):
            keystream = self.cipher.encrypt(ctr)
            ciphertext.append(xor(message[i:i+BLOCK_SIZE], keystream))
            ctr = self._increase_counter(ctr)
        return b"".join(ciphertext)
    
    def _increase_counter(self, ctr):
        return (int.from_bytes(ctr, "big") + 1).to_bytes(BLOCK_SIZE, "big")
    
    def _strToPoly(self, s, x):
        res = 0
        for i in range(BLOCK_SIZE):
            res *= x^8
            temp = s[i]
            for j in range(8):
                res += x^j * ((temp >> j) & 1)
        return res
    
    def _multByH(self, b, H, x):
        p = self._strToPoly(b, x)
        return self._polyToStr(p * H)
    
    def _polyToStr(self, p):
        coefs = p.polynomial().coefficients(sparse=False)
        res = 0
        for c in reversed(coefs):
            res = (res << 1) | c
        return res.to_bytes(BLOCK_SIZE, "big")

# Attaques
def xor_attack(c1, c2, m1):
    """Récupère m2 à partir de deux chiffrés avec même IV"""
    return xor(xor(c1, c2), m1)

def forge_challenge(key, iv, m_chall):
    """Génère un (c, t) valide pour mChall"""
    gcm = FlawedGCM(key)
    
    # Chiffrement CTR simple
    cipher = AES.new(key, AES.MODE_ECB)
    ctr = iv + b"\x00"*(COUNTER_SIZE-1) + b"\x02"
    keystream = cipher.encrypt(ctr)
    c = xor(m_chall, keystream)
    
    # Calcul du tag avec l'implémentation défectueuse
    T = cipher.encrypt(iv + b"\x00"*(COUNTER_SIZE-1) + b"\x01")
    tag = gcm.authenticate(c, T)
    
    return c, tag

# Paramètres fournis
key = hashlib.md5(b"SECRET_KEY").digest()  # Clé dérivée pour l'exemple
m1 = b'This is a Test !'
iv1 = b'W5ZS9Yu3dEs3hDtB'
c1 = base64.b64decode('2s9IB8rcQZh/Gljgb+WWQw==')
t1 = base64.b64decode('MD4tYk+xhF1j58oX7m3AXA==')
iv2 = iv1  # Même IV!
c2 = base64.b64decode('3sZSB8qIEtFqU2LgbvDEGw==')
t2 = base64.b64decode('IajN3Q9omEsjsAS2nbg9SA==')
mChall = b'100.00CHF to ADC'

# Test 1: Déchiffrement normal
gcm = FlawedGCM(key)
try:
    decrypted = gcm.decrypt(iv1, c1, t1)
    print(f"[+] Déchiffrement réussi: {decrypted}")
except Exception as e:
    print(f"[-] Erreur: {e}")

# Test 2: Attaque par réutilisation d'IV
m2 = xor_attack(c1, c2, m1)
print(f"[+] Message 2 récupéré: {m2}")

# Test 3: Forgeage de message
c_chall, t_chall = forge_challenge(key, iv1, mChall)
print(f"[+] Message forgé (base64):")
print(f"IV: {base64.b64encode(iv1).decode()}")
print(f"Chiffré: {base64.b64encode(c_chall).decode()}")
print(f"Tag: {base64.b64encode(t_chall).decode()}")
