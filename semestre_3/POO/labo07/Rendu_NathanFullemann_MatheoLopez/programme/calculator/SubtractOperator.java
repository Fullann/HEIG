package calculator;

public class SubtractOperator implements Operator {
    public void execute(State state) {
        // Vérifie si la pile a moins de deux éléments
        if (state.getStack().isEmpty()) {
            state.setErrorMessage("Pas assez d'opérandes pour -");
            return;
        }

        // Extraire les deux valeurs de la pile
        Double b = state.pop(); // Conversion explicite en Double
        Double a = state.getCurrentValue(); // Conversion explicite en Double

        // Effectuer la soustraction
        Double result = a - b;

        state.setCurrentValue(result);
        state.setOperationJustPerformed(true);
        state.setDecimalPoint(false);
    }
}
