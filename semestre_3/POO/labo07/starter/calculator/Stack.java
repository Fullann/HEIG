package calculator;

import java.util.Iterator;

public class Stack<T> {
    private Node<T> top;
    private int size = 0; // Ajout de la taille de la pile

    private static class Node<T> {
        T value;
        Node<T> next;

        Node(T value, Node<T> next) {
            this.value = value;
            this.next = next;
        }
    }

    // Empiler un objet sur le sommet de la pile
    public void push(T value) {
        top = new Node<>(value, top);
        size++; // Augmente la taille à chaque ajout
    }

    // Désempiler un objet du sommet de la pile
    public T pop() {
        if (top == null) throw new IllegalStateException("Stack is empty");
        T value = top.value;
        top = top.next;
        size--; // Diminue la taille à chaque retrait
        return value;
    }

    // Retourner une chaîne de caractères représentant le contenu de la pile
    public String toString() {
        StringBuilder sb = new StringBuilder();
        Node<T> current = top;
        while (current != null) {
            sb.append(current.value).append(" ");
            current = current.next;
        }
        return sb.toString().trim();
    }

    // Obtenir un tableau représentant l'état actuel de la pile
    public T[] toArray() {
        int currentSize = size;
        T[] array = (T[]) new Object[currentSize];
        Node<T> current = top;
        for (int i = 0; i < currentSize; i++) {
            array[i] = current.value;
            current = current.next;
        }
        return array;
    }

    // Retourner un itérateur sur la pile
    public Iterator<T> iterator() {
        return new Iterator<T>() {
            private Node<T> current = top;

            public boolean hasNext() {
                return current != null;
            }

            public T next() {
                if (current == null) throw new IllegalStateException("No more elements");
                T value = current.value;
                current = current.next;
                return value;
            }
        };
    }

    // Méthode pour obtenir la taille de la pile
    public int size() {
        return size;
    }

    // Méthode pour vérifier si la pile est vide
    public boolean isEmpty() {
        return size == 0;
    }
}
