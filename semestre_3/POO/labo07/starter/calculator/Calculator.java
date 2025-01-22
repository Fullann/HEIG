package calculator;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Calculator {

    public static void main(String[] args) {
        State state = new State();
        Scanner scanner = new Scanner(System.in);

        // Map associant les commandes utilisateur aux opérateurs
        Map<String, Operator> operators = new HashMap<>();
        operators.put("+", new AddOperator());
        operators.put("-", new SubtractOperator());
        operators.put("*", new MultiplyOperator());
        operators.put("/", new DivideOperator());
        operators.put("sqrt", new SqrtOperator());
        operators.put("1/x", new ReciprocalOperator());
        operators.put("x^2", new SquareOperator());
        operators.put("CE", new ClearEntryOperator());
        operators.put("C", new ClearOperator());
        operators.put("+/-", new NegateOperator());
        operators.put("Ent", new EnterOperator());

        System.out.println("Calculatrice RPN - Tapez 'exit' pour quitter.");

        while (true) {
            System.out.print("> ");
            String input = scanner.next();

            if (input.equalsIgnoreCase("exit")) {
                break;
            }

            try {
                // Essayer de lire un nombre
                double value = Double.parseDouble(input);
                state.push(value);
                System.out.println("Pile: " + state.getStack());
            } catch (NumberFormatException e) {
                // Rechercher l'opérateur correspondant
                Operator operator = operators.get(input);
                if (operator != null) {
                    operator.execute(state);
                    if (state.getErrorMessage() != null) {
                        System.out.println("Erreur: " + state.getErrorMessage());
                        state.setErrorMessage(null);
                    } else {
                        System.out.println("Résultat: " + state.getCurrentValue());
                        System.out.println("Pile: " + state.getStack());
                    }
                } else {
                    System.out.println("Commande inconnue: " + input);
                }
            }
        }

        scanner.close();
    }
}
