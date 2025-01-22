package calculator;

public class DivideOperator implements Operator {
    public void execute(State state) {
        // Vérifier si la pile a au moins deux éléments
        if (state.getStack().isEmpty()) {
            state.setErrorMessage("Pas assez d'opérandes pour /");
            return;
        }

        // Extraire les deux valeurs de la pile
        Double b = state.getCurrentValue(); // Assurez-vous que 'b' est un Double
        if (b == 0) {
            state.setErrorMessage("Division par zéro");
            return;
        }
        Double a = state.pop(); // Assurez-vous que 'a' est un Double

        // Effectuer la division
        Double result = a / b;

        // Pousser le résultat
        state.setCurrentValue(result);
        state.setOperationJustPerformed(true);
        state.setDecimalPoint(false);
    }
}
