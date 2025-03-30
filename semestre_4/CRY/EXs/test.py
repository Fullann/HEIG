import base64
import struct

# Fonctions de rotation
def rol(x, n):
    return ((x << n) & 0xffffffff) | (x >> (32 - n))

def ror(x, n):
    return ((x >> n) | (x << (32 - n))) & 0xffffffff

# Implémentation du quarter round (fonction forward)
def quarter_round(a, b, c, d):
    a = (a + b) & 0xffffffff
    d = rol(d ^ a, 16)
    c = (c + d) & 0xffffffff
    b = rol(b ^ c, 12)
    a = (a + b) & 0xffffffff
    d = rol(d ^ a, 8)
    c = (c + d) & 0xffffffff
    b = rol(b ^ c, 7)
    return a, b, c, d

# Fonction inverse du quarter round
def inv_quarter_round(a, b, c, d):
    # Inverse de la dernière opération: b = rol(b xor c, 7)
    b = ror(b, 7) ^ c
    # Inverse de: c = (c + d)
    c = (c - d) & 0xffffffff
    # Inverse de: d = rol(d xor a, 8)
    d = ror(d, 8) ^ a
    # Inverse de: a = (a + b)
    a = (a - b) & 0xffffffff
    # Inverse de: b = rol(b xor c, 12)
    b = ror(b, 12) ^ c
    # Inverse de: c = (c + d)
    c = (c - d) & 0xffffffff
    # Inverse de: d = rol(d xor a, 16)
    d = ror(d, 16) ^ a
    # Inverse de: a = (a + b)
    a = (a - b) & 0xffffffff
    return a, b, c, d

# Fonction double round (comme dans l’implémentation fournie)
def double_round(state):
    state[0], state[4], state[8], state[12] = quarter_round(state[0], state[4], state[8], state[12])
    state[1], state[5], state[9], state[13] = quarter_round(state[1], state[5], state[9], state[13])
    state[2], state[6], state[10], state[14] = quarter_round(state[2], state[6], state[10], state[14])
    state[3], state[7], state[11], state[15] = quarter_round(state[3], state[7], state[11], state[15])
    state[0], state[5], state[10], state[15] = quarter_round(state[0], state[5], state[10], state[15])
    state[1], state[6], state[11], state[12] = quarter_round(state[1], state[6], state[11], state[12])
    state[2], state[7], state[8], state[13] = quarter_round(state[2], state[7], state[8], state[13])
    state[3], state[4], state[9], state[14] = quarter_round(state[3], state[4], state[9], state[14])
    return state

# Inverse d’un double round : appliquer les inverses des quarter rounds dans l’ordre inverse
def inv_double_round(state):
    state[3], state[4], state[9], state[14] = inv_quarter_round(state[3], state[4], state[9], state[14])
    state[2], state[7], state[8], state[13] = inv_quarter_round(state[2], state[7], state[8], state[13])
    state[1], state[6], state[11], state[12] = inv_quarter_round(state[1], state[6], state[11], state[12])
    state[0], state[5], state[10], state[15] = inv_quarter_round(state[0], state[5], state[10], state[15])
    state[3], state[7], state[11], state[15] = inv_quarter_round(state[3], state[7], state[11], state[15])
    state[2], state[6], state[10], state[14] = inv_quarter_round(state[2], state[6], state[10], state[14])
    state[1], state[5], state[9], state[13] = inv_quarter_round(state[1], state[5], state[9], state[13])
    state[0], state[4], state[8], state[12] = inv_quarter_round(state[0], state[4], state[8], state[12])
    return state

# ChaCha20 avec 10 double rounds (sans addition finale)
def chacha(state):
    s = state.copy()
    for _ in range(10):
        double_round(s)
    return s

# Fonction inverse de chacha (on inverse chaque double round)
def inv_chacha(state):
    s = state.copy()
    for _ in range(10):
        inv_double_round(s)
    return s

# Conversion entre état (liste de 16 entiers) et bytes (little-endian)
def state_to_bytes(state):
    return b''.join(struct.pack('<I', word) for word in state)

def bytes_to_state(b):
    return list(struct.unpack('<16I', b))

# Décryptage exploitant la faille
def decrypt():
    # Texte clair connu pour le 1er bloc (64 octets)
    m_known = "You will have trouble finding the flag. The original ChaCha20 is"
    # Texte chiffré en base64 (2 blocs de 64 octets chacun)
    c_b64 = "0C1dXd6CI4K9Wr55upsJKGWUgtvLWaLTTp3fidbnm6vN8M299QHhhJzXGpyz+MtUFnA7zDb2HPH2DgIa8QuGgvoTB/Lmvc3QESI9jGfuO1p3lhkE3LAv5EKkAj7tbrPI2kd06CPCgg=="
    
    ciphertext = base64.b64decode(c_b64)
    
    block1 = ciphertext[:64]
    block2 = ciphertext[64:]
    
    m1 = m_known.encode('utf8')
    if len(m1) != 64:
        print("Le texte clair connu doit faire exactement 64 octets.")
        return

    # Récupération du keystream du 1er bloc
    keystream1 = bytes([pt ^ ct for pt, ct in zip(m1, block1)])
    # On reconstitue l'état obtenu après les rounds de ChaCha20
    state_after = bytes_to_state(keystream1)
    
    # Inversion des rounds pour retrouver l'état initial du 1er bloc
    init_state = inv_chacha(state_after)
    
    # L'état initial se présente comme suit :
    #   state[0..3] : constantes
    #   state[4..11] : clé (8 mots)
    #   state[12] : compteur (pos)
    #   state[13..15] : nonce (3 mots)
    constants = init_state[:4]
    key = init_state[4:12]
    counter = init_state[12]
    nonce = init_state[13:16]
    
    print("Éléments récupérés de l'état initial du bloc 1:")
    print("Constantes :", [hex(x) for x in constants])
    print("Clé :", [hex(x) for x in key])
    print("Compteur :", counter)
    print("Nonce :", [hex(x) for x in nonce])
    
    # Construction de l'état initial pour le 2ème bloc (compteur incrémenté)
    counter2 = (counter + 1) & 0xffffffff
    init_state_block2 = constants + key + [counter2] + nonce
    
    # Calcul du keystream du 2ème bloc
    state2 = chacha(init_state_block2.copy())
    keystream2 = state_to_bytes(state2)
    
    # Déchiffrement du 2ème bloc
    m2 = bytes([ct ^ ks for ct, ks in zip(block2, keystream2)])
    
    try:
        print("\nMessage déchiffré (bloc 2) :")
        print(m2.decode('utf8'))
    except UnicodeDecodeError:
        print("Le texte déchiffré ne semble pas être en UTF-8 :", m2.hex())

if __name__ == "__main__":
    decrypt()
