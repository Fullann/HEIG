package calculator;

public class AddOperator implements Operator {
    public void execute(State state) {
        // Vérification : suffisamment d'opérandes dans la pile
        if (state.getStack().isEmpty()) {
            state.setErrorMessage("Pas assez d'opérandes pour +");
            return;
        }

        // Effectuer l'opération d'addition
        try {
            double b = state.getCurrentValue(); // Deuxième opérande
            double a = state.pop(); // Premier opérande
            double result = a + b;  // Résultat de l'addition

            // Mettre à jour la pile et la valeur courante
            state.setCurrentValue(result);
            state.setOperationJustPerformed(true);
            state.setDecimalPoint(false);

            // Effacer tout message d'erreur précédent
            state.setErrorMessage(null);
        } catch (Exception e) {
            // Gestion des erreurs inattendues
            state.setErrorMessage("Erreur lors de l'exécution de l'opération +");
        }
    }
}
