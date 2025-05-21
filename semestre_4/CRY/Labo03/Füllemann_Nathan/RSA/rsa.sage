from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA
from base64 import b64decode, b64encode

def encrypt(m, key):
    cipher = PKCS1_OAEP.new(key)
    return cipher.encrypt(m)

def decrypt(c, key):
    """
    Déchiffre un message chiffré avec RSA-OAEP
    
    Args:
        c: le message chiffré (bytes)
        key: la clé RSA (doit contenir la clé privée)
    
    Returns:
        Le message en clair (bytes)
    """
    cipher = PKCS1_OAEP.new(key)
    return cipher.decrypt(c)

def keygen():
    phi = 65537
    e = 65537
    n = 1
    while gcd(phi, e) != 1:
        n = 1
        phi = 1
        p = random_prime(2^1048)
        q = next_prime(p + ZZ.random_element(2^15)) #to ensure that both primes have similar sizes
        n = p*q
        phi = (p-1)*(q-1)
    return RSA.construct((int(n), int(e), int(inverse_mod(e,phi))), consistency_check=True)

# Test du système RSA complet
def test_rsa():
    print("Test du système RSA:")
    
    # Génération de la paire de clés
    key = keygen()
    # Message à chiffrer
    message = b"Crypto"
    print(f"Message original: {message}")
    
    # Chiffrement
    ciphertext = encrypt(message, key)
    print(f"Message chiffré : {ciphertext.hex()[:64]}...")
    
    # Déchiffrement
    decrypted = decrypt(ciphertext, key)
    print(f"Message déchiffré: {decrypted}")
    
    # Vérification
    assert message == decrypted, "Err"
    print("Test réussi")

# Exécution du test
if __name__ == "__main__":
    test_rsa()