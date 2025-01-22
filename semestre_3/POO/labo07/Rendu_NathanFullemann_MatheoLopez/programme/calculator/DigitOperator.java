package calculator;

public class DigitOperator implements Operator {
    private final int digit;

    public DigitOperator(int digit) {
        this.digit = digit;
    }

    public void execute(State state) {
        try {
            // Si une opération vient d'être effectuée, ajouter la valeur courante à la pile
            if (state.isOperationJustPerformed()) {
                state.push(state.getCurrentValue()); // Ajouter currentValue à la pile
                state.setCurrentValue(0); // Réinitialiser currentValue pour la nouvelle entrée
                state.setOperationJustPerformed(false); // Réinitialiser le drapeau
            }

            // Vérifier si un point décimal a été ajouté
            if (!state.hasDecimalPoint()) {
                // Si aucun point décimal, traiter comme un entier
                int currentIntValue = (int) state.getCurrentValue();
                currentIntValue = currentIntValue * 10 + digit; // Ajouter le chiffre
                state.setCurrentValue(currentIntValue); // Mettre à jour comme un entier
            } else {
                // Si un point décimal a été ajouté, traiter comme un nombre flottant
                String current = String.valueOf(state.getCurrentValue());

                // Supprimer les zéros inutiles
                if (current.endsWith(".0")) {
                    current = current.substring(0, current.length() - 1);
                }

                // Ajouter le chiffre après le point
                current += digit;

                // Convertir et mettre à jour la valeur actuelle
                state.setCurrentValue(Double.parseDouble(current));
            }
        } catch (NumberFormatException e) {
            // En cas d'erreur, enregistrer un message d'erreur
            state.setErrorMessage("Entrée non valide");
        }
    }
}
