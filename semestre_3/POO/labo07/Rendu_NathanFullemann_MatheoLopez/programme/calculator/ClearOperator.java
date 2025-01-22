package calculator;

public class ClearOperator implements Operator {
    public void execute(State state) {
        state.clear(); // Réinitialise la pile et la valeur courante
    }
}
