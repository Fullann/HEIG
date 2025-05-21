from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA
from base64 import b64decode
import math

def fermat_factorize(n):
    """
    Factorisation de Fermat pour des nombres dont les facteurs sont proches
    
    Args:
        n: le module RSA à factoriser
    
    Returns:
        (p, q) les deux facteurs de n
    """
    print("Début de la factorisation de Fermat...")
    # Convertir n en entier Python standard pour éviter les problèmes de compatibilité
    n = int(n)
    
    # Utiliser la fonction de racine carrée de la bibliothèque math
    a = math.isqrt(n)  # Partie entière de la racine carrée de n
    
    if a * a == n:
        return int(a), int(a)  # n est un carré parfait
    
    a += 1  # Commencer avec a > sqrt(n)
    
    while True:
        b_squared = a * a - n
        b = math.isqrt(b_squared)
        
        if b * b == b_squared:  # Vérifier si b_squared est un carré parfait
            p = a + b
            q = a - b
            print(f"Factorisation trouvée! p = {p}, q = {q}")
            return int(p), int(q)  # Convertir explicitement en entiers Python
        
        a += 1
        
        # Afficher progression toutes les 1000 itérations
        if a % 1000 == 0:
            print(f"Testé a = {a}...")

# Fonction pour reconstruire la clé privée à partir de la clé publique et des facteurs p et q
def reconstruct_private_key(public_key, p, q):
    # Convertir explicitement en entiers Python standards
    p = int(p)
    q = int(q)
    n = p * q
    e = int(public_key.e)
    phi = (p - 1) * (q - 1)
    d = pow(e, -1, phi)  # Inverse modulaire de e modulo phi
    
    # Reconstruire la clé privée RSA
    return RSA.construct((int(n), int(e), int(d)), consistency_check=True)

# On suppose que vous avez ces valeurs
# key contient la clé publique au format PEM
key = b'''-----BEGIN PUBLIC KEY-----
MIIBKDANBgkqhkiG9w0BAQEFAAOCARUAMIIBEAKCAQcAhA3tDaT+HkcZNdvKksXP\nZYvyuuy65/ZE0rlB4dAPYoZx4Jz65ZL+4w7MmxYN4YjIGPY/sCNOT+55OFMX8GlZ\nWt+XD5ex3df6LY5AyrK+G44j4p2Jo9Ns2QDd2rRqsWpoUXe2hkVsfONqnxZqy5gV\nduaMFxMy1tfhY+9OF6Lnn1Wq1KOj2w18bszIsyx7r8dHCQ0O9I1ApeOcNeoZgl0C\n1fHly31rBYOX0qxhAsSJ8fAmzsD1R56mRVP/1h3xM+DlEyRk1mD/DgGs+6V6nTdh\nJCyMNoLktsbP3pFYpapykg+9PQJ9oNLKA6Vbqgvxe64Vl35Oj0mQEbs35Y9Nex3A\n3xgcsUsj/wIDAQAB
-----END PUBLIC KEY-----'''

# c contient le texte chiffré en base64
c = b'aJ7wR9164ROn+hxgyzh5xawPxILcz73t6KzLKZ9OxUBfqdxCBZ44a+tK2Fx1kv1vuHiCxyrPTrj7X2n0kLT0v5g6EZhzD9lrZLrjYGod5HJVboYStIVi6FRljYIus41TtvbgzFX72m9aIKdu9RQr5V/Du+Wxo/wfgL4xequ+cjyO9+2CIhfUZqXFHOdF9mTvHWmG2OiXRaiIPN4GBkLS9iFGmiP+d0dcjFtjABkrqRK5TQbTHeZ9+vG0tt1QbAlhZEs1hluQTwp4UqsbkC85EoQ1A8n+Xm2VG6BMl0Q4oIY55YThunnW2Dgy4AXuQB5Extqx8VMANo1IH9wL5tnSib0cm4mHQA=='

# Charger la clé publique
public_key = RSA.import_key(key)
print(f"Module n: {public_key.n}")
print(f"Exposant e: {public_key.e}")

# Factoriser n avec l'algorithme de Fermat
p, q = fermat_factorize(public_key.n)
print(f"p = {p}")
print(f"q = {q}")
print(f"Vérification: p*q = {p*q}")
print(f"Module n   = {public_key.n}")

# Reconstruire la clé privée
private_key = reconstruct_private_key(public_key, p, q)

# Déchiffrer le message
cipher = PKCS1_OAEP.new(private_key)
ciphertext = b64decode(c)
plaintext = cipher.decrypt(ciphertext)

print("\nMessage déchiffré:")
print(plaintext.decode('utf-8'))