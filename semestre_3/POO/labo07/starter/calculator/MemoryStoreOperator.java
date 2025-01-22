package calculator;

public class MemoryStoreOperator implements Operator {
    public void execute(State state) {
        // Stockage de la valeur courante dans la mémoire
        state.setMemory(state.getCurrentValue());
    }
}
