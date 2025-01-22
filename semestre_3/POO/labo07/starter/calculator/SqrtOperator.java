package calculator;

public class SqrtOperator implements Operator {
    public void execute(State state) {
        // Vérifier si la pile est vide
        if (state.getStack().isEmpty()) {
            state.setErrorMessage("Pas d'opérande pour sqrt");
            return;
        }

        // Extraire la valeur de la pile
        Double a = state.pop(); // Conversion explicite en Double

        // Vérifier si la valeur est négative
        if (a < 0) {
            state.setErrorMessage("Racine carrée d'un nombre négatif");
            return;
        }

        // Calculer la racine carrée
        Double result = Math.sqrt(a);

        // Pousser le résultat sur la pile
        state.push(result);

        // Mettre à jour la valeur courante
        state.setCurrentValue(result);
        state.setOperationJustPerformed(true);
        state.setDecimalPoint(false);
    }
}
