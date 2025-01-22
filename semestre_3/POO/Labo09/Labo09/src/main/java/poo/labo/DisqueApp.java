package poo.labo;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.LinkedList;
import java.util.ListIterator;

public class DisqueApp {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new DisqueFrame().setVisible(true));
    }
}

class DisqueFrame extends JFrame {
    private final DrawingPanel drawingPanel;

    public DisqueFrame() {
        setTitle("Application de Dessin de Disques");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        drawingPanel = new DrawingPanel();
        add(drawingPanel, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel();
        JButton clearButton = new JButton("Clear");
        JButton quitButton = new JButton("Quit");

        clearButton.addActionListener(e -> drawingPanel.clearDisques());
        quitButton.addActionListener(e -> System.exit(0));

        buttonPanel.add(clearButton);
        buttonPanel.add(quitButton);
        add(buttonPanel, BorderLayout.SOUTH);

        pack();
        setLocationRelativeTo(null);
    }
}

class DrawingPanel extends JPanel implements MouseListener, MouseMotionListener {
    private final LinkedList<Disque> disques;
    private Point center;
    private Point currentPoint;
    private Disque movingDisque;
    private boolean isMoving;
    private boolean shiftPressed;

    public static final Color[] COLORS = {Color.BLUE, Color.RED, Color.GREEN, Color.MAGENTA, Color.ORANGE};

    public DrawingPanel() {
        disques = new LinkedList<>();
        setBackground(Color.WHITE);
        addMouseListener(this);
        addMouseMotionListener(this);
        setPreferredSize(new Dimension(800, 600));

        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_SHIFT) {
                    shiftPressed = true;
                }
            }

            @Override
            public void keyReleased(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_SHIFT) {
                    shiftPressed = false;
                }
            }
        });
        setFocusable(true);
    }

    public void clearDisques() {
        disques.clear();
        repaint();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;

        // Dessiner tous les disques
        for (Disque disque : disques) {
            disque.draw(g2);
        }

        // Dessiner le disque en cours de création
        if (center != null && currentPoint != null && !isMoving) {
            int radius = (int) center.distance(currentPoint);
            g2.setColor(Color.GRAY);
            g2.drawOval(center.x - radius, center.y - radius, 2 * radius, 2 * radius);
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {
        if (e.getButton() == MouseEvent.BUTTON1) { // Bouton gauche
            if (shiftPressed) {
                for (Disque disque : disques) {
                    if (disque.contains(e.getPoint())) {
                        movingDisque = disque;
                        isMoving = true;
                        return;
                    }
                }
            } else {
                center = e.getPoint();
                currentPoint = null;
            }
        } else if (e.getButton() == MouseEvent.BUTTON3) { // Bouton droit
            for (ListIterator<Disque> it = disques.listIterator(disques.size()); it.hasPrevious(); ) {
                Disque disque = it.previous();
                if (disque.contains(e.getPoint())) {
                    it.remove();
                    repaint();
                    return;
                }
            }
        }
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        if (e.getButton() == MouseEvent.BUTTON1) {
            if (isMoving) {
                isMoving = false;
                movingDisque = null;
            } else if (center != null) {
                int radius = (int) center.distance(e.getPoint());
                disques.add(new Disque(center, radius, disques.size() % COLORS.length));
                center = null;
                currentPoint = null;
                repaint();
            }
        }
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        if (isMoving && movingDisque != null) {
            movingDisque.setCenter(e.getPoint());
            repaint();
        } else if (center != null) {
            currentPoint = e.getPoint();
            repaint();
        }
    }

    @Override
    public void mouseMoved(MouseEvent e) {
        // Non utilisé
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        // Non utilisé
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        // Non utilisé
    }

    @Override
    public void mouseExited(MouseEvent e) {
        // Non utilisé
    }
}

class Disque {
    private Point center;
    private final int radius;
    private final int colorIndex;

    public Disque(Point center, int radius, int colorIndex) {
        this.center = center;
        this.radius = radius;
        this.colorIndex = colorIndex;
    }

    public void draw(Graphics2D g) {
        g.setColor(DrawingPanel.COLORS[colorIndex]);
        g.fillOval(center.x - radius, center.y - radius, 2 * radius, 2 * radius);
    }

    public boolean contains(Point p) {
        return center.distance(p) <= radius;
    }

    public void setCenter(Point newCenter) {
        this.center = newCenter;
    }
}
