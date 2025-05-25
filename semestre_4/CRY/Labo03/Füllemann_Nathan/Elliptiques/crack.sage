from Crypto.Protocol.KDF import HKDF
from Crypto.Hash import SHA256
from Crypto.Cipher import AES
from base64 import b64encode, b64decode
import time

# Paramètres de la courbe elliptique
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

# Fonctions de sérialisation
def serialize_point_compressed(P):
    p = P.curve().base_field().order()
    byte_length = (p.nbits() + 7) // 8
    x_bytes = int(P[0]).to_bytes(byte_length, 'big')
    prefix = b'\x02' if int(P[1]) % 2 == 0 else b'\x03'
    return prefix + x_bytes

def deserialize_point_compressed(data, E):
    prefix = data[0]
    if prefix not in (2, 3):
        raise ValueError("Invalid compression prefix")

    x_bytes = data[1:]
    x = int.from_bytes(x_bytes, 'big')
    xF = E.base_field()(x)

    try:
        P = E.lift_x(xF, all=False)
    except ValueError:
        raise ValueError("Invalid x: no point found on the curve")

    if (int(P[1]) % 2 == 0 and prefix == 2) or (int(P[1]) % 2 == 1 and prefix == 3):
        return P
    else:
        return -P

def solve_discrete_log(G, A, n):
    """
    Résout le logarithme discret A = a*G en utilisant les fonctions intégrées de Sage
    """
    print(f"Ordre du groupe: {n} (~2^{n.nbits()} bits)")
    
    start_time = time.time()
    # Calcul du logarithme discret
    a = discrete_log(A, G, ord=n, operation='+')
    
    elapsed = time.time() - start_time
    print(f"Logarithme discret résolu en {elapsed:.2f} secondes")
    print(f"Clé privée trouvée: a = {a}")
    
    # Vérification
    if a * G == A:
        print(f"Vérification réussie: a * G = A")
        return a
    else:
        print(f"Err de vérification de a * G = A!")
        return None

def crack_ecies():
    """
    Fonction principale pour casser la construction ECIES
    """
  
    # Données fournies
    serialized_public_key = b'AwxseRl4RIGE1Ils8XsDxrA9aH8DKd6Q+K0bnfam02tX'
    c_0 = b'AiedRj0k+ssEMoIM5QiEAQJxuAM2NqzjGLvWReGzdr3v'
    nonce = b'/JeL0PyFMVd98dWUEoma4g=='
    ciphertext = b'ccvrZ7jfhmvBSt9STtEef3eZ40QaGSre5Gg22HL33mLAwtuEhXA8Kmvlj8AjJdDBGsxYkQR/XW4SF//P0ae1jec75a0bbg=='
    tag = b'2d3hI1wzI/FWCoju9kDMiw=='
    
    # Décodage base64
    pub_key_bytes = b64decode(serialized_public_key)
    c0_bytes = b64decode(c_0)
    nonce_bytes = b64decode(nonce)
    ciphertext_bytes = b64decode(ciphertext)
    tag_bytes = b64decode(tag)

    # Initialisation des paramètres de la courbe
    G, E, n = params()

    # Désérialisation des points
    A = deserialize_point_compressed(pub_key_bytes, E)
    rG = deserialize_point_compressed(c0_bytes, E)
    print(f"Points désérialisés avec succès")
    print(f"    - Clé publique A: ({A[0]}, {A[1]})")
    print(f"    - Point éphémère rG: ({rG[0]}, {rG[1]})")

    # Vérification que les points sont sur la courbe
    if A not in E or rG not in E:
        print("Les points ne sont pas sur la courbe!")
        return
    print(f"Points validés sur la courbe")
    
    print("RÉCUPÉRATION DE LA CLÉ PRIVÉE")
    a = solve_discrete_log(G, A, n)
    if a is None:
        print("Impossible de récupérer la clé privée")
        return

    print("DÉCRYPTAGE DU MESSAGE")
    # Calcul du secret partagé: rA = a * rG
    shared_secret = a * rG
    print(f"Secret partagé calculé: ({shared_secret[0]}, {shared_secret[1]})")
    
    # Dérivation de la clé AES avec HKDF
    shared_secret_bytes = serialize_point_compressed(shared_secret)
    k = HKDF(shared_secret_bytes, 32, b"", SHA256, num_keys=1)
    print(f"Clé AES dérivée: {k.hex()}")
    
    # Décryptage AES-GCM
    cipher = AES.new(k, AES.MODE_GCM, nonce=nonce_bytes)
    plaintext = cipher.decrypt_and_verify(ciphertext_bytes, tag_bytes)
        
    print(f"Message en clair (hex): {plaintext.hex()}")
    # Décodage en texte
    plaintext_str = plaintext.decode('utf-8')
    print(f"Message en clair: {plaintext_str}")

if __name__ == "__main__":
    crack_ecies()
