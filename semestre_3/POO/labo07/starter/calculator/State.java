package calculator;

public class State {
    private Stack<Double> stack;
    private double currentValue;
    private String errorMessage;
    private Double memory;
    private boolean hasDecimalPoint = false;
    private boolean operationJustPerformed = false;

    public State() {
        this.stack = new Stack<>();
        this.currentValue = 0;
        this.errorMessage = null;
    }

    public Double getMemory() {
        return memory;
    }

    public void setMemory(Double memory) {
        this.memory = memory;
    }

    public double getCurrentValue() {
        return currentValue;
    }

    public void setCurrentValue(double value) {
        this.currentValue = value;
    }
    public boolean isOperationJustPerformed() {
        return operationJustPerformed;
    }

    public void setOperationJustPerformed(boolean operationJustPerformed) {
        this.operationJustPerformed = operationJustPerformed;
    }

    public Stack<Double> getStack() {
        return stack;
    }

    public String getErrorMessage() {
        return errorMessage;
    }

    public void setErrorMessage(String message) {
        this.errorMessage = message;
    }

    public void push(double value) {
        stack.push(value);
    }

    public double pop() {
        if (stack.isEmpty()) {
            setErrorMessage("Pile vide");
            return 0;
        }
        return stack.pop();
    }

    public void clear() {
        stack = new Stack<>();
        currentValue = 0;
        errorMessage = null;
    }

    public boolean hasDecimalPoint() {
        return hasDecimalPoint;
    }

    public void setDecimalPoint(boolean hasDecimalPoint) {
        this.hasDecimalPoint = hasDecimalPoint;
    }
}
