from Crypto.Random import get_random_bytes
from Crypto.Signature.pss import MGF1
from Crypto.Hash import SHA256
from Crypto.Util.strxor import strxor
from Crypto.Util.Padding import pad, unpad


BIT_LEN_PRIME = 1024#2048
BYTE_LEN_RANDOMNESS = 128
REDUNDANCY = 10


def keyGen():
    p = 1
    while p %4 != 3: 
        p = random_prime(2**BIT_LEN_PRIME, proof = False, lbound = 2**(BIT_LEN_PRIME-1)) #proof = False for performances
    q = 1
    while q % 4 != 3: 
        q = random_prime(2**BIT_LEN_PRIME, proof = False, lbound = 2**(BIT_LEN_PRIME-1)) #proof = False for performances
    return (p, q, p*q)


def mgf(seed, length):
    #This function is correct and you don't need to look at it
    #It generates a mask of given length using the seed as input
    return MGF1(seed, length, SHA256)

def encrypt(m, n):
    BYTE_LEN_MESSAGE_PART = int(log(n,2))//8 - BYTE_LEN_RANDOMNESS
    if len(m) > BYTE_LEN_MESSAGE_PART - REDUNDANCY - 1 :
        raise Exception("Message too long. Maximum " + str(BYTE_LEN_MESSAGE_PART - REDUNDANCY - 1) + " bytes")
    m = pad(m, BYTE_LEN_MESSAGE_PART, style = 'iso7816')
    r = get_random_bytes(BYTE_LEN_RANDOMNESS)
    h = mgf(r, BYTE_LEN_MESSAGE_PART)
    m = strxor(m, h) + r
    return (int.from_bytes(m, 'little')**2) % n

def sqrtmod(c, p, q):
    # Racines modulo p et q (p, q ≡ 3 mod 4)
    r_p = power_mod(c, (p + 1) // 4, p)
    r_q = power_mod(c, (q + 1) // 4, q)
    
    # Utilisation du CRT pour combiner les racines
    roots = []
    for s_p in [r_p, -r_p % p]:
        for s_q in [r_q, -r_q % q]:
            root = crt([s_p, s_q], [p, q])
            roots.append(root)
    return roots


def decrypt(c, p, q):
    n = p * q
    BYTE_LEN_MESSAGE_PART = int(log(n,2))//8 - BYTE_LEN_RANDOMNESS

    roots = sqrtmod(c, p, q)
    for x in roots:
        m_bytes = x.to_bytes((x.bit_length() + 7) // 8, byteorder='little')
        
        # On vérifie que la taille est correcte
        if len(m_bytes) < BYTE_LEN_RANDOMNESS:
            continue
        m_padded_xor = m_bytes[:BYTE_LEN_MESSAGE_PART]
        r = m_bytes[BYTE_LEN_MESSAGE_PART:BYTE_LEN_MESSAGE_PART+BYTE_LEN_RANDOMNESS]
        if len(r) != BYTE_LEN_RANDOMNESS:
            continue

        h = mgf(r, BYTE_LEN_MESSAGE_PART)
        m_padded = strxor(m_padded_xor, h)

        try:
            m = unpad(m_padded, BYTE_LEN_MESSAGE_PART, style='iso7816')
            return m
        except ValueError:
            continue
    raise Exception("Decryption failed: valid root not found")

# Générer les clés
(p, q, n) = keyGen()

# Message original
message = b"Crypto"

# Chiffrement
c = encrypt(message, n)
print("message chiffrer",c)
# Déchiffrement
m_decrypted = decrypt(c, p, q)

# Affichage
print("Message original :", message)
print("Message déchiffré :", m_decrypted)
print("Succès :", message == m_decrypted)
