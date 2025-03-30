import { cellPixelSize, shapeColors, gameCols, gameRows } from "./constants.js";
import { Game } from "./game.js";
import { FallingShape } from "./fallingShape.js";
import { PlacedShapesGrid } from "./placedShapesGrid.js";

function cellToPixel(x) {
  return x * cellPixelSize;
}

export class Renderer {
  constructor(game, context) {
    this.game = game;
    this.context = context;
  }

  /**
   * Clears the context and draws all falling and placed shapes.
   */
  render() {
    this.#resetContext();
    this.#drawShapes();
    this.#drawGround();
  }

  #mapRect() {
    return [
      0, // x1
      0, // y1
      cellToPixel(gameCols), // x2
      cellToPixel(gameRows), // y2
    ];
  }

  #resetContext() {
    this.context.clearRect(...this.#mapRect());
  }

  #drawShapes() {
    this.game.forEachFallingShape((shape) => this.#drawShape(shape));
  }

  #drawShape(fallingShape) {
    const coords = fallingShape.getCoordinates();
    coords.forEach(([dx, dy]) => {
      this.#drawCell(
        fallingShape.playerId,
        fallingShape.row + dy,
        fallingShape.col + dx
      );
    });
  }
  #drawGround() {
    const { grid } = this.game;
    for (let row = grid.height - 1; row >= 0; row--) {
      for (let col = 0; col < grid.width; col++) {
        const playerId = grid.getPlayerAt(row, col);
        if (playerId > -1) {
          this.#drawCell(playerId, row, col);
        }
      }
    }
  }
  #drawCell(playerId, row, col) {
    this.context.fillStyle = shapeColors[playerId];
    this.context.fillRect(
      cellToPixel(col),
      cellToPixel(row),
      cellPixelSize,
      cellPixelSize
    );
  }
}
