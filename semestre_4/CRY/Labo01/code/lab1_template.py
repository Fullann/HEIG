
# IMPORTANT
# IL EST PRIMORDIAL DE NE PAS CHANGER LA SIGNATURE DES FONCTIONS
# SINON LES CORRECTIONS RISQUENT DE NE PAS FONCTIONNER CORRECTEMENT

import string
import unicodedata
from statistics import mean

ASCII_SHIFT = ord('A') # will be used to skip the first 65 entries in the ASCII table
MAX_KEY_LENGTH = 20
NUM_LETTRE_ALPHA = 26

PLAINTEXT = "LACRYPTOCESTRIGOLO"
KEYVIGENERE = "MAISON"
KEYCAESAR = 3

def sanitize_text(text):
    """
    Convertit le texte en majuscules, retire les accents et supprime
    les caractères non alphabétiques.
    """
    if all(c in string.ascii_letters for c in text):
        return text.upper()

    text = unicodedata.normalize('NFD', text)
    text = text.encode('ascii', 'ignore').decode("utf-8")
    return ''.join(c for c in text.upper() if c in string.ascii_uppercase)

def caesar_encrypt(text, key):
    """
    Parameters
    ----------
    text: the plaintext to encrypt
    key: the shift which is a number

    Returns
    -------
    the ciphertext of <text> encrypted with Caesar under key <key>
    """
    text = sanitize_text(text)
    result = ""
    for c in text:
        shifted = (ord(c) - ASCII_SHIFT + key) % NUM_LETTRE_ALPHA
        result += chr(shifted + ASCII_SHIFT)
    return result

def caesar_decrypt(text, key):
    """
    Parameters
    ----------
    text: the ciphertext to decrypt
    key: the shift which is a number

    Returns
    -------
    the plaintext of <text> decrypted with Caesar under key <key>
    """
    text = sanitize_text(text)
    result = ""
    for c in text:
        shifted = (ord(c) - ASCII_SHIFT - key) % NUM_LETTRE_ALPHA
        result += chr(shifted + ASCII_SHIFT)
    return result

def freq_analysis(text):
    """
    Parameters
    ----------
    text: the text to analyse

    Returns
    -------
    list
        the frequencies of every letter (A-Z) in the text.
    """
    text = sanitize_text(text)
    freq_vector = [0] * NUM_LETTRE_ALPHA
    total = len(text)
    if total == 0:
        return freq_vector
    for c in text:
        idx = ord(c) - ASCII_SHIFT
        freq_vector[idx] += 1
    freq_vector = [count / total for count in freq_vector]
    return freq_vector

def caesar_break(text, ref_freq):
    """
    Parameters
    ----------
    text: the ciphertext to break
    ref_freq: the output of the freq_analysis function on a reference text

    Returns
    -------
    a number corresponding to the caesar key
    """
    text = sanitize_text(text)
    total = len(text)
    if total == 0:
        return 0
    
    observed_freq = freq_analysis(text)  # Éviter de recalculer les fréquences à chaque clé

    best_key = 0
    min_chi2 = float('inf')

    for key in range(NUM_LETTRE_ALPHA):
        chi2 = sum(((observed_freq[(i + key) % NUM_LETTRE_ALPHA] - ref_freq[i]) ** 2) / ref_freq[i]
                   for i in range(NUM_LETTRE_ALPHA) if ref_freq[i] > 0)
        if chi2 < min_chi2:
            min_chi2 = chi2
            best_key = key
    return best_key

def vigenere_encrypt(text, key):
    """
    Parameters
    ----------
    text: the plaintext to encrypt
    key: the keyword used in Vigenere (e.g. "pass")

    Returns
    -------
    the ciphertext of <text> encrypted with Vigenere under key <key>
    """
    text = sanitize_text(text)
    key = sanitize_text(key)
    result = ""
    key_length = len(key)
    for i, c in enumerate(text):
        shift = ord(key[i % key_length]) - ASCII_SHIFT
        shifted = (ord(c) - ASCII_SHIFT + shift) % NUM_LETTRE_ALPHA
        result += chr(shifted + ASCII_SHIFT)
    return result

def vigenere_decrypt(text, key):
    """
    Parameters
    ----------
    text: the ciphertext to decrypt
    key: the keyword used in Vigenere (e.g. "pass")

    Returns
    -------
    the plaintext of <text> decrypted with Vigenere under key <key>
    """
    text = sanitize_text(text)
    key = sanitize_text(key)
    result = ""
    key_length = len(key)
    for i, c in enumerate(text):
        shift = ord(key[i % key_length]) - ASCII_SHIFT
        shifted = (ord(c) - ASCII_SHIFT - shift) % NUM_LETTRE_ALPHA
        result += chr(shifted + ASCII_SHIFT)
    return result

def coincidence_index(text):
    """
    Parameters
    ----------
    text: the text to analyse

    Returns
    -------
    the index of coincidence of the text
    """
    text = sanitize_text(text)
    s = 0
    l = len(text)
    if l <= 1: return 0
    for i in range(NUM_LETTRE_ALPHA):
        occurrences = text.count(chr(i + ASCII_SHIFT))
        s += occurrences * (occurrences - 1)
    return (NUM_LETTRE_ALPHA * s) / (l * (l - 1))

def estimate_key_length(text, ref_ci):
    """
    Estime la longueur de la clé en utilisant l'indice de coïncidence comparé à un texte de référence.
    """
    text = sanitize_text(text)
    max_key_length = min(MAX_KEY_LENGTH,len(text))  # Limite supérieure pour la longueur de la clé
    best_length = 1
    best_ic = 0

    for key_length in range(1, max_key_length + 1):
        ic_values = []
        for i in range(key_length):
            sub_text = text[i::key_length]  # Extraire les lettres espacées de key_length
            ic_values.append(coincidence_index(sub_text))

        avg_ic = sum(ic_values) / len(ic_values)
        # Comparer l'IC estimé avec l'IC du texte de référence pour une estimation plus précise
        ic_diff = abs(avg_ic - ref_ci)
        if ic_diff < best_ic or best_ic == 0:
            best_ic = ic_diff
            best_length = key_length

    return best_length
def column_partition(text, column_len):
    """
    The text divided in chunks such that each chunk is composed of letters at 
    positions 0 + i, l + i, 2l + i, etc. for 0 <= i <= l
    """
    chunks = [""] * column_len
    text_len = len(text)
    for j in range(column_len):
        for i in range(j, text_len, column_len):
            chunks[j] += text[i]
    return chunks
def vigenere_break(text, ref_freq, ref_ci):
    """
    Parameters
    ----------
    text: the ciphertext to break
    ref_freq: the output of the freq_analysis function on a reference text
    ref_ci: the output of the coincidence_index function on a reference text

    Returns
    -------
    the keyword corresponding to the encryption key used to obtain the ciphertext
    """
    text = sanitize_text(text)
    best_candidate = {'ci': 0, 'chunks': ''}
    for l  in range(1, MAX_KEY_LENGTH + 1):
        chunks = column_partition(text, l)
        ci = mean(coincidence_index(c) for c in chunks)
        if abs(ci - ref_ci) < abs(best_candidate['ci'] - ref_ci):
            best_candidate['ci'] = ci
            best_candidate['chunks'] = chunks
    return "".join(chr(i + ASCII_SHIFT) for i in [caesar_break(p, ref_freq) for p in best_candidate['chunks']])
def vigenere_improved_encrypt(text, key):
    """
    Chiffrement Vigenère amélioré avec mise à jour dynamique de la clé
    """
    text = sanitize_text(text)
    key = sanitize_text(key)
    result = ""
    block_size = len(key)
    current_key = key

    for i in range(0, len(text), block_size):
        block = text[i:i + block_size]
        block_cipher = ""
        
        for j, c in enumerate(block):
            shift = ord(current_key[j]) - ASCII_SHIFT
            shifted = (ord(c) - ASCII_SHIFT + shift) % NUM_LETTRE_ALPHA
            block_cipher += chr(shifted + ASCII_SHIFT)
        
        result += block_cipher
        
        if len(block) == block_size:
            current_key = vigenere_encrypt(current_key, block_cipher)  # Mise à jour de la clé
    
    return result
def vigenere_improved_decrypt(text, key):
    """
    Déchiffrement Vigenère amélioré en recalculant la clé à chaque bloc
    """
    ciphertext = sanitize_text(text)

    result = ""
    block_size = len(key)
    current_key = key

    for i in range(0, len(ciphertext), block_size):
        block = ciphertext[i:i + block_size]
        block_plain = ""
        
        for j, c in enumerate(block):
            shift = ord(current_key[j]) - ASCII_SHIFT
            shifted = (ord(c) - ASCII_SHIFT - shift) % NUM_LETTRE_ALPHA
            block_plain += chr(shifted + ASCII_SHIFT)
        
        result += block_plain
        
        if len(block) == block_size:
            current_key = vigenere_encrypt(current_key, block)
    
    return result

def vigenere_improved_break(text, ref_freq, ref_ci):
    """
    Parameters
    ----------
    text: the ciphertext to break
    ref_freq: the output of the freq_analysis function on a reference text
    ref_ci: the output of the coincidence_index function on a reference text

    Returns
    -------
    the keyword corresponding to the key used to obtain the ciphertext
    """
    text = sanitize_text(text)
    key_length = estimate_key_length(text, ref_ci)
    key = ""
    
    # Pour chaque position de la clé, on essaie de trouver le meilleur décalage avec les sous-chaînes
    for i in range(key_length):
        sub_text = text[i::key_length]
        best_char = 0
        best_char_chi_score = float('inf')
        # On essaie chaque lettre de l'alphabet comme décalage
        for j in range(26):
            subtext_decrypt = vigenere_improved_decrypt(sub_text, chr(j + ord('A')))
            # On fait une analyse de fréquence sur le texte déchiffré
            subtext_freq = freq_analysis(subtext_decrypt)
            chi2_score = chi2_distance(subtext_freq, ref_freq)
            # On garde le décalage qui minimise la distance chi2
            if chi2_score < best_char_chi_score:
                best_char_chi_score = chi2_score
                best_char = chr(j + ord('A'))
        # On ajoute le caractère trouvé à la clé
        key += best_char
    return key
    
def chi2_distance(observed, expected):
                """
                Parameters
                ----------
                observed: list
                    Observed frequencies of letters (A-Z) in the text.
                expected: list
                    Expected frequencies of letters (A-Z) in the reference text.

                Returns
                -------
                float
                    The chi-squared distance between the observed and expected frequencies.
                """
                return sum(((o - e) ** 2) / e for o, e in zip(observed, expected) if e > 0)

def main():
    print("=== Welcome to the Vigenere Breaking Tool ===\n")

    # Example: Caesar Cipher Encryption/Decryption
    print("=== Caesar Cipher ===")
    
    encrypted_caesar = caesar_encrypt(PLAINTEXT, KEYCAESAR)
    print(f"Encrypted: {encrypted_caesar}")
    decrypted_caesar = caesar_decrypt(encrypted_caesar, KEYCAESAR)
    print(f"Decrypted: {decrypted_caesar}\n")

    # Load reference text for frequency analysis
    print("=== Loading Reference Text ===")
    try:
        with open("reference.txt", "r", encoding="utf-8") as f:
            reference = f.read()
        ref_freq = freq_analysis(reference)
        ref_ci = coincidence_index(reference)
        print(f"Reference Frequencies: {ref_freq}")
        print(f"Reference Index of Coincidence: {ref_ci}\n")
    except Exception as e:
        print(f"Error loading reference text: {e}\n")
        return

    # Vigenere Cipher Encryption/Decryption
    print("=== Vigenere Cipher ===")
    encrypted_vigenere = vigenere_encrypt(PLAINTEXT, KEYVIGENERE)
    print(f"Encrypted: {encrypted_vigenere}")
    decrypted_vigenere = vigenere_decrypt(encrypted_vigenere, KEYVIGENERE)
    print(f"Decrypted: {decrypted_vigenere}")

    # Break Vigenere Cipher
    recovered_key = vigenere_break(encrypted_vigenere, ref_freq, ref_ci)
    print(f"Recovered Key: {recovered_key}\n")

    # Improved Vigenere Cipher Encryption/Decryption
    print("=== Improved Vigenere Cipher ===")
    encrypted_vigenere_imp = vigenere_improved_encrypt(PLAINTEXT, KEYVIGENERE)
    print(f"Encrypted: {encrypted_vigenere_imp}")
    decrypted_vigenere_imp = vigenere_improved_decrypt(encrypted_vigenere_imp, KEYVIGENERE)
    print(f"Decrypted: {decrypted_vigenere_imp}")

    # Break Improved Vigenere Cipher
    recovered_key_imp = vigenere_improved_break(encrypted_vigenere_imp, ref_freq, ref_ci)
    print(f"Recovered Key (Heuristic): {recovered_key_imp}\n")

    # Decrypt vigenere.txt
    print("=== Decrypting vigenere.txt ===")

    with open("vigenere.txt", "r", encoding="utf-8") as f:
        vigenere_cipher = f.read()
    recovered_key_file = vigenere_break(vigenere_cipher, ref_freq, ref_ci)
    decrypted_vigenere_file = vigenere_decrypt(vigenere_cipher, recovered_key_file)
    print(f"Recovered Key: {recovered_key_file}")
    print(f"Decrypted Text: {decrypted_vigenere_file}\n")

    # Decrypt vigenere_improved.txt
    print("=== Decrypting vigenere_improved.txt ===")

    with open("vigenere_improved.txt", "r", encoding="utf-8") as f:
        vigenere_improved_cipher = f.read()
    recovered_key_imp_file = vigenere_improved_break(vigenere_improved_cipher, ref_freq, ref_ci)
    decrypted_vigenere_imp_file = vigenere_improved_decrypt(vigenere_improved_cipher, recovered_key_imp_file)
    print(f"Recovered Key: {recovered_key_imp_file}")
    print(f"Decrypted Text: {decrypted_vigenere_imp_file}\n")
   
if __name__ == "__main__":  
    main()
