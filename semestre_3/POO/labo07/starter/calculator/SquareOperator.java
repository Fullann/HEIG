package calculator;

public class SquareOperator implements Operator {
    public void execute(State state) {
        // Calculer le carré de la valeur actuelle
        double currentValue = state.getCurrentValue();
        double result = Math.pow(currentValue, 2);

        // Mettre à jour la valeur courante et la pile
        state.setCurrentValue(result);
        state.setOperationJustPerformed(true);
        state.setDecimalPoint(false);
    }
}
