package calculator;

public class MemoryRecallOperator implements Operator {
    public void execute(State state) {
        // Vérification si la mémoire contient une valeur
        if (state.getMemory() == null) {
            state.setErrorMessage("Mémoire vide");
        } else {
            state.setCurrentValue(state.getMemory());
        }
    }
}
