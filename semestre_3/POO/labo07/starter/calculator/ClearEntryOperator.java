package calculator;

public class ClearEntryOperator implements Operator {
    public void execute(State state) {
        state.setCurrentValue(0);
        state.setDecimalPoint(false);
        state.setErrorMessage(null);
    }
}
