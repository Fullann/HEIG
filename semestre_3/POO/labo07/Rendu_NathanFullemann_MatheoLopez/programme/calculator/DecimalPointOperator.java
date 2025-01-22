package calculator;

public class DecimalPointOperator implements Operator {
    public void execute(State state) {


            String current = String.valueOf((int) state.getCurrentValue()); // Utiliser la valeur entière actuelle
            current += "."; // Ajouter un point
            state.setCurrentValue(Double.parseDouble(current)); // Mettre à jour la valeur comme flottant
            state.setDecimalPoint(true); // Indiquer que le point a été utilisé

    }
}
