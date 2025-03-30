export class PlacedShapesGrid {
  constructor(width, height) {
    this.width = width;
    this.height = height;
    /** Tableau 2D contenant pour chaque position l’id du joueur dont le bloc est placé, ou -1 sinon. */
    this.map = Array.from({ length: height }, () => Array(width).fill(-1));
  }

  /**
   * Fait descendre la forme jusqu’à ce qu’elle touche un obstacle, puis la place sur la grille.
   * Si la forme est déjà bloquée sur sa position actuelle (déjà obstruée par un autre bloc), elle n’est pas placée.
   * @param {FallingShape} shape La forme à placer.
   */
  slamShape(shape) {
    // Si la forme ne peut pas être placée à sa position actuelle, on n’effectue aucun placement.
    if (!this.testShape(shape, shape.row)) return;

    let row = shape.row;
    while (row < this.height && this.testShape(shape, row)) {
      row++;
    }
    shape.row = row - 1;
    this.placeShape(shape);
  }

  /**
   * Place la forme sur la grille en transférant ses coordonnées dans la table.
   * @param {FallingShape} shape La forme à placer.
   */
  placeShape(shape) {
    const coords = shape.getCoordinates();
    coords.forEach(([dx, dy]) => {
      this.map[shape.row + dy][shape.col + dx] = shape.playerId;
    });
  }

  /**
   * Vérifie si la forme peut être placée à la position (row, col) avec une rotation donnée.
   * La forme est valide si elle n’est pas en dehors des limites (à gauche, à droite ou en bas) et ne chevauche pas de bloc déjà placé.
   * Note : On ne considère pas comme hors limites si la forme est partiellement au-dessus du haut.
   * @param {FallingShape} shape La forme à tester.
   * @param {Number} row La ligne à tester (défaut : shape.row).
   * @param {Number} col La colonne à tester (défaut : shape.col).
   * @param {Number} rotation La rotation à tester (défaut : shape.rotation).
   * @returns {Boolean} true si la forme peut être placée, false sinon.
   */
  testShape(
    shape,
    row = shape.row,
    col = shape.col,
    rotation = shape.rotation
  ) {
    const coords = shape.getCoordinates(rotation);
    return coords.every(([dx, dy]) => {
      const x = col + dx;
      const y = row + dy;
      return (
        x >= 0 && // borne gauche
        x < this.width && // borne droite
        y < this.height && // borne inférieure
        (y < 0 || this.getPlayerAt(y, x) === -1) // pas de chevauchement
      );
    });
  }

  /**
   * Parcourt les lignes et efface toute ligne entièrement remplie.
   */
  clearFullRows() {
    for (let row = 0; row < this.height; row++) {
      if (this.map[row].every((playerId) => playerId !== -1)) {
        this.clearRow(row);
      }
    }
  }

  /**
   * Efface une ligne donnée et décale les lignes supérieures d’une rangée.
   * @param {Number} row La ligne à effacer.
   */
  clearRow(row) {
    this.map.splice(row, 1);
    this.map.unshift(Array(this.width).fill(-1));
  }

  /**
   * Retourne l’id du joueur présent à la position (row, col) ou -1 si aucun.
   * @param {Number} row La ligne demandée.
   * @param {Number} col La colonne demandée.
   * @returns {Number} L’id du joueur ou -1.
   */
  getPlayerAt(row, col) {
    return this.map[row][col];
  }
}
