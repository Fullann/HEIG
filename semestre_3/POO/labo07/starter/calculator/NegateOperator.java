package calculator;

public class NegateOperator implements Operator {
    public void execute(State state) {
        // Négation de la valeur actuelle
        double currentValue = state.getCurrentValue();
        state.setCurrentValue(-currentValue);
    }
}
