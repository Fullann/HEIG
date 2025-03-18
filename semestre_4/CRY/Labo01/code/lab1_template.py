
# IMPORTANT
# IL EST PRIMORDIAL DE NE PAS CHANGER LA SIGNATURE DES FONCTIONS
# SINON LES CORRECTIONS RISQUENT DE NE PAS FONCTIONNER CORRECTEMENT


import string
import unicodedata
from itertools import product

def sanitize_text(text):
    """
    Convertit le texte en majuscules, retire les accents et supprime
    les caractères non alphabétiques.
    """
    text = unicodedata.normalize('NFD', text)
    text = text.encode('ascii', 'ignore').decode("utf-8")
    text = text.upper()
    text = ''.join(c for c in text if c in string.ascii_uppercase)
    return text

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
        shifted = (ord(c) - ord('A') + key) % 26
        result += chr(shifted + ord('A'))
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
        shifted = (ord(c) - ord('A') - key) % 26
        result += chr(shifted + ord('A'))
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
    freq_vector = [0] * 26
    total = len(text)
    if total == 0:
        return freq_vector
    for c in text:
        idx = ord(c) - ord('A')
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
    best_key = 0
    min_chi2 = float('inf')
    total = len(text)
    for key in range(26):
        decrypted = caesar_decrypt(text, key)
        counts = [0] * 26
        for c in decrypted:
            counts[ord(c) - ord('A')] += 1
        chi2 = 0
        for i in range(26):
            expected = ref_freq[i] * total
            if expected > 0:
                chi2 += ((counts[i] - expected) ** 2) / expected
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
        shift = ord(key[i % key_length]) - ord('A')
        shifted = (ord(c) - ord('A') + shift) % 26
        result += chr(shifted + ord('A'))
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
        shift = ord(key[i % key_length]) - ord('A')
        shifted = (ord(c) - ord('A') - shift) % 26
        result += chr(shifted + ord('A'))
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
    N = len(text)
    if N <= 1:
        return 0
    counts = [0] * 26
    for c in text:
        counts[ord(c) - ord('A')] += 1
    numerator = sum(n * (n - 1) for n in counts)
    denominator = N * (N - 1)
    ic = (26 * numerator) / denominator
    return ic

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
    best_key_length = 1
    best_ic_diff = float('inf')
    max_len = min(20, len(text))
    for L in range(1, max_len + 1):
        ic_list = []
        for j in range(L):
            group = text[j::L]
            ic_list.append(coincidence_index(group))
        avg_ic = sum(ic_list) / len(ic_list)
        diff = abs(avg_ic - ref_ci)
        if diff < best_ic_diff:
            best_ic_diff = diff
            best_key_length = L

    key = ""
    for j in range(best_key_length):
        group = text[j::best_key_length]
        total = len(group)
        best_shift = 0
        min_chi2 = float('inf')
        for shift in range(26):
            decrypted = ""
            for c in group:
                shifted = (ord(c) - ord('A') - shift) % 26
                decrypted += chr(shifted + ord('A'))
            counts = [0] * 26
            for c in decrypted:
                counts[ord(c) - ord('A')] += 1
            chi2 = 0
            for i in range(26):
                expected = ref_freq[i] * total
                if expected > 0:
                    chi2 += ((counts[i] - expected) ** 2) / expected
            if chi2 < min_chi2:
                min_chi2 = chi2
                best_shift = shift
        key += chr(best_shift + ord('A'))
    return key

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
            shift = ord(current_key[j]) - ord('A')
            shifted = (ord(c) - ord('A') + shift) % 26
            block_cipher += chr(shifted + ord('A'))
        
        result += block_cipher

        if len(block) == block_size:
            current_key = vigenere_encrypt(current_key, block_cipher)  # Mise à jour de la clé

    return result


def vigenere_improved_decrypt(text, key):
    """
    Déchiffrement Vigenère amélioré en recalculant la clé à chaque bloc
    """
    text = sanitize_text(text)
    key = sanitize_text(key)
    result = ""
    block_size = len(key)
    current_key = key

    for i in range(0, len(text), block_size):
        block = text[i:i + block_size]
        block_plain = ""
        
        for j, c in enumerate(block):
            shift = ord(current_key[j]) - ord('A')
            shifted = (ord(c) - ord('A') - shift) % 26
            block_plain += chr(shifted + ord('A'))
        
        result += block_plain

        if len(block) == block_size:
            current_key = vigenere_encrypt(current_key, block)  # Mise à jour de la clé

    return result


def vigenere_improved_break(text, ref_freq, ref_ci):
    """
    Casse heuristique du Vigenère amélioré en essayant d'identifier la clé initiale
    """
    text = sanitize_text(text)

    # Estimation de la longueur probable de la clé
    best_key_length = 8
    best_ic_diff = float('inf')
    max_len = min(10, len(text))

    for L in range(1, max_len + 1):
        ic_list = [coincidence_index(text[j::L]) for j in range(L)]
        avg_ic = sum(ic_list) / len(ic_list)
        diff = abs(avg_ic - ref_ci)
        if diff < best_ic_diff:
            best_ic_diff = diff
            best_key_length = L

    # Récupération de la clé initiale par analyse fréquentielle
    key = ""
    for j in range(best_key_length):
        group = text[j::best_key_length]
        best_shift = 0
        min_chi2 = float('inf')
        total = len(group)

        for shift in range(26):
            decrypted = "".join(chr((ord(c) - ord('A') - shift) % 26 + ord('A')) for c in group)
            counts = [0] * 26
            for c in decrypted:
                counts[ord(c) - ord('A')] += 1
            chi2 = sum(((counts[i] - ref_freq[i] * total) ** 2) / (ref_freq[i] * total) if ref_freq[i] * total > 0 else 0 for i in range(26))

            if chi2 < min_chi2:
                min_chi2 = chi2
                best_shift = shift

        key += chr(best_shift + ord('A'))

    return key


def main():
    print("Welcome to the Vigenere breaking tool")
    
    # 2 Exemple de chiffrement/déchiffrement avec le chiffre de César
    plain = "LACRYPTOCESTRIGOLO"
    key_caesar = 3
    encrypted_caesar = caesar_encrypt(plain, key_caesar)
    print("Caesar Encrypted:", encrypted_caesar)
    decrypted_caesar = caesar_decrypt(encrypted_caesar, key_caesar)
    print("Caesar Decrypted:", decrypted_caesar)
    
    # 2.1 Chargement du texte de référence pour l'analyse fréquentielle
    try:
        with open("reference.txt", "r", encoding="utf-8") as f:
            reference = f.read()
    except Exception as e:
        print("reference.txt non trouvé")
    
    ref_freq = freq_analysis(reference)
    ref_ci = coincidence_index(reference)
    print("Reference frequencies:", ref_freq)   
    print("Reference index of coincidence:", ref_ci)
    # 2.2 Casse du chiffre de César

    # Chiffrement/déchiffrement avec le chiffre de Vigenère classique
    key_vigenere = "MAISON"
    encrypted_vigenere = vigenere_encrypt(plain, key_vigenere)
    print("Vigenere Encrypted:", encrypted_vigenere)
    decrypted_vigenere = vigenere_decrypt(encrypted_vigenere, key_vigenere)
    print("Vigenere Decrypted:", decrypted_vigenere)
    
    # Casse du chiffre de Vigenère
    recovered_key = vigenere_break(encrypted_vigenere, ref_freq, ref_ci)
    print("Recovered Vigenere key:", recovered_key)
    
    # Chiffrement/déchiffrement avec le chiffre de Vigenère amélioré
    encrypted_vigenere_imp = vigenere_improved_encrypt(plain, key_vigenere)
    print("Improved Vigenere Encrypted:", encrypted_vigenere_imp)
    decrypted_vigenere_imp = vigenere_improved_decrypt(encrypted_vigenere_imp, key_vigenere)
    print("Improved Vigenere Decrypted:", decrypted_vigenere_imp)
    
    # Casse du chiffre de Vigenère amélioré (heuristique)
    recovered_key_imp = vigenere_improved_break(encrypted_vigenere_imp, ref_freq, ref_ci)
    print("Recovered Improved Vigenere key (heuristic):", recovered_key_imp)
    

    # Déchiffrement du fichier vigenere.txt
    try:
        with open("vigenere.txt", "r", encoding="utf-8") as f:
            vigenere_cipher = f.read()
        recovered_key_file = vigenere_break(vigenere_cipher, ref_freq, ref_ci)
        decrypted_vigenere_file = vigenere_decrypt(vigenere_cipher, recovered_key_file)
        print("\n=== Déchiffrement de vigenere.txt ===")
        print("Clé retrouvée :", recovered_key_file)
        print("Texte déchiffré :", decrypted_vigenere_file)
    except Exception as e:
        print("Erreur lors du traitement de vigenere.txt :", e)
    
    # Déchiffrement du fichier vigenere_improved.txt
    try:
        with open("vigenere_improved.txt", "r", encoding="utf-8") as f:
            vigenere_improved_cipher = f.read()
        recovered_key_imp_file = vigenere_improved_break(vigenere_improved_cipher, ref_freq, ref_ci)
        decrypted_vigenere_imp_file = vigenere_improved_decrypt(vigenere_improved_cipher, recovered_key_imp_file)
        print("\n=== Déchiffrement de vigenere_improved.txt ===")
        print("Clé retrouvée :", recovered_key_imp_file)
        print("Texte déchiffré :", decrypted_vigenere_imp_file)
    except Exception as e:
        print("Erreur lors du traitement de vigenere_improved.txt :", e)

if __name__ == "__main__":
    main()
