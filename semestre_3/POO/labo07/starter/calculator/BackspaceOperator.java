package calculator;

public class BackspaceOperator implements Operator {
    public void execute(State state) {
        // Récupérer la valeur actuelle sous forme de chaîne
        String current = String.valueOf(state.getCurrentValue());

        // Si la chaîne contient ".0" (par exemple "5.0"), la simplifier pour éviter des erreurs
        if (current.endsWith(".0")) {
            current = current.substring(0, current.length() - 2); // Retirer ".0"
        }

        // Vérifier si la chaîne a plus d'un caractère
        if (current.length() > 1) {
            // Supprimer le dernier caractère
            current = current.substring(0, current.length() - 1);

            // Si le point décimal est supprimé, mettre à jour l'indicateur
            if (!current.contains(".")) {
                state.setDecimalPoint(false); // Réinitialiser l'indicateur de point décimal
            }
        } else {
            // Si un seul caractère reste, réinitialiser à "0"
            current = "0";
            state.setDecimalPoint(false); // Réinitialiser l'indicateur de point décimal
        }

        // Mettre à jour la valeur courante après avoir retiré un caractère
        state.setCurrentValue(Double.parseDouble(current));
    }
}
