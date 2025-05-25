from Crypto.Protocol.KDF import HKDF
from Crypto.Hash import SHA256
from Crypto.Cipher import AES
from base64 import b64encode, b64decode

def params():
    p = 50043062554237280172405801360375653460619548838234052036762494431728976610313
    a = 43327883319811199442996705732365163443043431995328598938729525921048235234958
    b = 45494814375791703888029144132071347443317277861841182091738819980027414195528
    gx = 34736706601617260336801089627448256371787243214661931571076381713565253696521
    gy = 5887497935320424287803691270199037907654978138532428031269063384390017951571
    n = 2550513000803
    E = EllipticCurve(GF(p), [a, b])
    G = E(gx, gy)
    return (G, E, n)
    


def keyGen(G, n):
    a = ZZ.random_element(n)
    A = a*G
    return (a, A)
    
def serialize_point_compressed(P):
    #no error in this code
    p = P.curve().base_field().order()
    byte_length = (p.nbits() + 7) // 8
    x_bytes = int(P[0]).to_bytes(byte_length, 'big')
    prefix = b'\x02' if int(P[1]) % 2 == 0 else b'\x03'
    return prefix + x_bytes

def deserialize_point_compressed(data, E):
    #no error in this code
    prefix = data[0]
    if prefix not in (2, 3):
        raise ValueError("Invalid compression prefix")

    x_bytes = data[1:]
    x = int.from_bytes(x_bytes, 'big')
    xF = E.base_field()(x)

    # lift_x returns a point with given x and the correct y parity
    try:
        P = E.lift_x(xF, all=False)
    except ValueError:
        raise ValueError("Invalid x: no point found on the curve")

    # Check parity
    if (int(P[1]) % 2 == 0 and prefix == 2) or (int(P[1]) % 2 == 1 and prefix == 3):
        return P
    else:
        # Flip to the other y if parity doesn't match
        return -P


def encrypt(A, M, G, n):
    r = ZZ.random_element(n)
    rA = r*A
    k = HKDF(serialize_point_compressed(rA), 32, b"", SHA256, num_keys=1)
    cipher = AES.new(k, AES.MODE_GCM)
    ciphertext, tag = cipher.encrypt_and_digest(M)
    return (serialize_point_compressed(r*G), (cipher.nonce, ciphertext, tag))

def decrypt(a, R_bytes, data, E):
    """
    a : clé privée du destinataire (int)
    R_bytes : point compressé rG (bytes)
    data : tuple (nonce, ciphertext, tag)
    E : courbe elliptique
    """
    R = deserialize_point_compressed(R_bytes, E)
    P = a * R  # point partagé
    k = HKDF(serialize_point_compressed(P), 32, b"", SHA256, num_keys=1)
    nonce, ciphertext, tag = data
    cipher = AES.new(k, AES.MODE_GCM, nonce=nonce)
    M = cipher.decrypt_and_verify(ciphertext, tag)
    return M

G, E, n = params()

# Initialisation des paramètres de la courbe
G, E, n = params()
print("Paramètres de la courbe elliptique")
print(" - Générateur G :", G)
print(" - Ordre n       :", n)
print(" - Equation      :", E)

# Génération de la clé (Bob)
a, A = keyGen(G, n)
print("\n Clés de Bob")
print(" - Clé privée a  :", a)
print(" - Clé publique A:", A)

# Message à chiffrer
message = b"Crypto"
print("\nMessage clair à chiffrer :", message.decode())

# Chiffrement (Alice envoie un message à Bob)
R_bytes, data = encrypt(A, message, G, n)
nonce, ciphertext, tag = data

print("\n Chiffrement par Alice")
print(" - Point éphémère R (compressé) :", R_bytes.hex())
print(" - Nonce AES                    :", nonce.hex())
print(" - Ciphertext                   :", ciphertext.hex())
print(" - Tag                          :", tag.hex())

# Déchiffrement (Bob)
message_dechiffre = decrypt(a, R_bytes, data, E)
print(" - Message déchiffré :", message_dechiffre.decode())

# 6. Vérification
if message_dechiffre == message:
    print("\nLe message envoyé de Bob et celui d'Alice sont les même  ")
else:
    print("\n Err")

