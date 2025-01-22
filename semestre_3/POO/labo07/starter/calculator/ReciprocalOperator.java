package calculator;

public class ReciprocalOperator implements Operator {
    public void execute(State state) {
        // Vérifier si la valeur courante est zéro
        if (state.getCurrentValue() == 0) {
            state.setErrorMessage("Division par zéro");
            return;
        }

        // Calculer le réciproque
        Double result = 1 / state.getCurrentValue();

        // Mettre à jour la valeur courante
        state.setCurrentValue(result);
        state.setOperationJustPerformed(true);
        state.setDecimalPoint(false);
    }
}
