package calculator;

import java.awt.Color;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

//import java.awt.event.*;

public class JCalculator extends JFrame
{
  // Tableau representant une pile vide
  private static final String[] empty = { "< empty stack >" };

  // Zone de texte contenant la valeur introduite ou resultat courant
  private final JTextField jNumber = new JTextField("0");

  // Composant liste representant le contenu de la pile
  private final JList jStack = new JList(empty);

  // Contraintes pour le placement des composants graphiques
  private final GridBagConstraints constraints = new GridBagConstraints();

  private final State calculatorState = new State();

  private void update() {
    // Mise à jour de la zone de texte avec la valeur courante
    if (calculatorState.getErrorMessage() != null) {
      jNumber.setText(calculatorState.getErrorMessage()); // Affiche le message d'erreur si présent
    } else {
      jNumber.setText(String.valueOf(calculatorState.getCurrentValue())); // Sinon, affiche la valeur courante
    }

    // Mise à jour de la liste représentant la pile
    // Conversion de la pile (qui est une Stack<Double>) en un tableau de String
    Object[] stackContents = calculatorState.getStack().toArray();
    String[] stackStrings = new String[stackContents.length];

    // Convertir chaque élément de la pile en String
    for (int i = 0; i < stackContents.length; i++) {
      stackStrings[i] = String.valueOf(stackContents[i]);
    }

    // Mettre à jour le JList avec les éléments convertis en String
    jStack.setListData(stackStrings);
  }



  // Ajout d'un bouton dans l'interface et de l'operation associee,
  // instance de la classe Operation, possedeant une methode execute()
  private void addOperatorButton(String name, int x, int y, Color color, final Operator operator) {
    JButton b = new JButton(name);
    b.setForeground(color);
    constraints.gridx = x;
    constraints.gridy = y;
    getContentPane().add(b, constraints);

    b.addActionListener(e -> {
      if (operator != null) {
        // Exécuter l'opérateur avec l'état actuel
        operator.execute(calculatorState);
      }
      update(); // Mettre à jour l'interface après l'exécution
    });
  }

  public JCalculator() 
  {
    super("JCalculator");
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    getContentPane().setLayout(new GridBagLayout());

    // Contraintes des composants graphiques
    constraints.insets = new Insets(3, 3, 3, 3);
    constraints.fill = GridBagConstraints.HORIZONTAL;

    // Nombre courant
    jNumber.setEditable(false);
    jNumber.setBackground(Color.WHITE);
    jNumber.setHorizontalAlignment(JTextField.RIGHT);
    constraints.gridx = 0;
    constraints.gridy = 0;
    constraints.gridwidth = 5;
    getContentPane().add(jNumber, constraints);
    constraints.gridwidth = 1; // reset width

    // Rappel de la valeur en memoire
    addOperatorButton("MR", 0, 1, Color.RED, new MemoryRecallOperator());

    // Stockage d'une valeur en mémoire
    addOperatorButton("MS", 1, 1, Color.RED, new MemoryStoreOperator());

    // Backspace
    addOperatorButton("<=", 2, 1, Color.RED, new BackspaceOperator());

    // Mise à zéro de la valeur courante + suppression des erreurs
    addOperatorButton("CE", 3, 1, Color.RED, new ClearEntryOperator());

    // Comme CE + vide la pile
    addOperatorButton("C",  4, 1, Color.RED, new ClearOperator());

    // Boutons 1-9
    for (int i = 1; i < 10; i++) {
      addOperatorButton(String.valueOf(i), (i - 1) % 3, 4 - (i - 1) / 3, Color.BLUE, new DigitOperator(i));
    }

    // Bouton 0
    addOperatorButton("0", 0, 5, Color.BLUE, new DigitOperator(0));

    // Changement de signe de la valeur courante
    addOperatorButton("+/-", 1, 5, Color.BLUE, new NegateOperator());

    // Opérateur point (chiffres après la virgule)
    addOperatorButton(".", 2, 5, Color.BLUE, new DecimalPointOperator());

    // Opérateurs arithmétiques à deux opérandes: /, *, -, +
    addOperatorButton("/", 3, 2, Color.RED, new DivideOperator());
    addOperatorButton("*", 3, 3, Color.RED, new MultiplyOperator());
    addOperatorButton("-", 3, 4, Color.RED, new SubtractOperator());
    addOperatorButton("+", 3, 5, Color.RED, new AddOperator());

    // Opérateurs arithmétiques à un opérande: 1/x, x^2, Sqrt
    addOperatorButton("1/x", 4, 2, Color.RED, new ReciprocalOperator());
    addOperatorButton("x^2", 4, 3, Color.RED, new SquareOperator());
    addOperatorButton("Sqrt", 4, 4, Color.RED, new SqrtOperator());

    // Entrée: met la valeur courante sur le sommet de la pile
    addOperatorButton("Ent", 4, 5, Color.RED, new EnterOperator());

    // Affichage de la pile
    JLabel jLabel = new JLabel("Stack");
    jLabel.setFont(new Font("Dialog", 0, 12));
    jLabel.setHorizontalAlignment(JLabel.CENTER);
    constraints.gridx = 5;
    constraints.gridy = 0;
    getContentPane().add(jLabel, constraints);

    jStack.setFont(new Font("Dialog", 0, 12));
    jStack.setVisibleRowCount(8);
    JScrollPane scrollPane = new JScrollPane(jStack);
    constraints.gridx = 5;
    constraints.gridy = 1;
    constraints.gridheight = 5;
    getContentPane().add(scrollPane, constraints);
    constraints.gridheight = 1; // reset height

    setResizable(false);
    pack();
    setVisible(true);
  }
}
