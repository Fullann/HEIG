/**
 * Laboratoire 6
 * Author : Nathan Füllemann
 * Date : 02.10.2023
 *
 * Name: What is the shape
 * Desc : Programme ou l on rentre les coordonnées de 4 points et qui nous dit si c est un carré, rectangle, losange, parallélogramme ou trapèze
 */
#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    int x, y;
};

// Fonction pour calculer la distance entre deux points
double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Fonction pour calculer l'angle entre trois points
double angle(Point p1, Point p2, Point p3) {
    double a = distance(p1, p2);
    double b = distance(p2, p3);
    double c = distance(p3, p1);
    return acos((a * a + b * b - c * c) / (2 * a * b));
}

int main() {
    const int nbAngle = 4;
    Point points[nbAngle];
    cout << "Entrez les coordonnées du premier sommet du quadrilatère (x y) : ";
    cin >> points[0].x >> points[0].y;

    cout << "Entrez les coordonnées du deuxième sommet du quadrilatère (x y) : ";
    cin >> points[1].x >> points[1].y;

    cout << "Entrez les coordonnées du troisième sommet du quadrilatère (x y) : ";
    cin >> points[2].x >> points[2].y;

    cout << "Entrez les coordonnées du quatrième sommet du quadrilatère (x y) : ";
    cin >> points[3].x >> points[3].y;

    double sides[nbAngle];
    double angles[nbAngle];

    sides[0] = distance(points[0], points[1]);
    sides[1] = distance(points[1], points[2]);
    sides[2] = distance(points[2], points[3]);
    sides[3] = distance(points[3], points[0]);

    angles[0] = angle(points[0], points[1], points[2]);
    angles[1] = angle(points[1], points[2], points[3]);
    angles[2] = angle(points[2], points[3], points[0]);
    angles[3] = angle(points[3], points[0], points[1]);

    // Vérification des propriétés du quadrilatère
    bool isSquare = sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3] && angles[0] == angles[1] && angles[1] == angles[2] && angles[2] == angles[3];
    bool isRectangle = angles[0] == angles[1] && angles[1] == angles[2] && angles[2] == angles[3];
    bool isRhombus = sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3] && angles[0] != angles[1] && angles[1] != angles[2] && angles[2] != angles[3];
    bool isParallelogram = angles[0] == angles[2] && angles[1] == angles[3];
    bool isTrapezoid = (sides[0] == sides[2] && sides[1] != sides[3]) || (sides[0] != sides[2] && sides[1] == sides[3]);

    cout << "(" << points[0].x << "," << points[0].y << "),(" << points[1].x << "," << points[1].y << "),(" << points[2].x << "," << points[2].y << "),(" << points[3].x << "," << points[3].y << ") : ";
    
    if (isSquare) {
        cout << "Le quadrilatère est un carré." << endl;
    } else if (isRectangle) {
        cout << "Le quadrilatère est un rectangle." << endl;
    } else if (isRhombus) {
        cout << "Le quadrilatère est un losange." << endl;
    } else if (isParallelogram) {
        cout << "Le quadrilatère est un parallélogramme." << endl;
    } else if (isTrapezoid) {
        cout << "Le quadrilatère est un trapèze." << endl;
    } else {
        cout << "Le quadrilatère n'est aucune de ces formes." << endl;
    }
}
