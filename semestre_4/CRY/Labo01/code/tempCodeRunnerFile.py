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