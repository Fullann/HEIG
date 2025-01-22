package calculator;

public class EnterOperator implements Operator {
    public void execute(State state) {
        state.push(state.getCurrentValue());
        state.setCurrentValue(0);
        state.setDecimalPoint(false);
    }
}
