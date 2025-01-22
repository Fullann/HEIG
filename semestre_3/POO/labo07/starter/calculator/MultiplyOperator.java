package calculator;

public class MultiplyOperator implements Operator {
    @Override
    public void execute(State state) {
        try {
            // Récupérer les deux premiers éléments de la pile (convertir les éléments en Double)
            Double b = state.getCurrentValue(); // Récupérer la valeur du sommet de la pile (assurez-vous que c'est un Double)
            Double a = state.pop(); // Récupérer la valeur juste en dessous

            // Effectuer l'opération
            Double result = a * b;

            state.setCurrentValue(result);
            state.setOperationJustPerformed(true);
            state.setDecimalPoint(false);

        } catch (Exception e) {
            // Gérer l'erreur si la pile ne contient pas assez de valeurs ou une erreur dans l'opération
            state.setErrorMessage("Erreur : " + e.getMessage());
        }
    }
}
