import { gameRows, gameCols } from "./constants.js";
import { FallingShape } from "./fallingShape.js";
import { PlacedShapesGrid } from "./placedShapesGrid.js";

export class Game extends Map {
  constructor(grid) {
    super();
    this.grid = grid;
    this.isGameOver = false;
  }

  /**
   * Returns FallingShape of given player, or undefined if no such player or shape.
   * @param {Number} id Id of the player whose falling shape is to be returned.
   */
  getFallingShape(id) {
    return this.get(id)?.shape;
  }

  /**
   * Executes the provided function on each falling shape in the game.
   * @param {Function} f The function to be executed. It takes a falling shape as a parameter, and its return value is ignored.
   */
  forEachFallingShape(f) {
    this.forEach((player) => f(player.shape));
  }

  /**
   * Tries to slam the given player's falling shape, i.e. move it down until it touches something if necessary, and then placing it onto the grid.
   * @param {Number} playerId The id of the player whose falling shape should be slammed
   */
  slamShape(playerId) {
    const player = this.get(playerId);
    if (!player) {
      return;
    }
    this.grid.slamShape(player.shape);
    this.grid.clearFullRows();
    this.addNewFallingShape(playerId);
    this.#replaceBlockedShapes(playerId);
  }
  #replaceBlockedShapes(selfId) {
    this.forEach((player, playerId) => {
      if (playerId !== selfId && !this.grid.testShape(player.shape)) {
        this.addNewFallingShape(playerId);
      }
    });
  }
  /**
   * Advances the game by one step, i.e. moves all falling shapes down by one, places any shape that was touching the ground, and replaces it with a new one.
   */
  step() {
    if (this.isGameOver) {
      return;
    }

    const dropShapes = [];
    for (let player of this.values()) {
      const { shape } = player;
      if (!shape || shape.row === undefined) {
        continue;
      }

      if (this.grid.testShape(shape, shape.row + 1)) {
        shape.row++;
        continue;
      }

      dropShapes.push(shape);
    }

    dropShapes.forEach((shape) => {
      if (this.grid.testShape(shape)) {
        this.slamShape(shape.playerId);
      }
    });
  }

  /**
   * Replace current falling shape of given player id (if any) with a new random shape.
   * @param {Number} id Id of the player whose shape should be replaced.
   */
  addNewFallingShape(id) {
    let shapeCol = this.grid.width / 2;

    const player = this.get(id);
    if (!player) {
      return;
    }

    const type = FallingShape.getRandomShapeType();
    player.shape = new FallingShape(type, id, shapeCol, 0, 0);
    if (!this.grid.testShape(player.shape)) {
      this.gameOver();
    }
  }

  /**
   * Resets the game upon game over.
   */
  gameOver() {
    this.isGameOver = true;
    this.clear();
    this.grid = new PlacedShapesGrid(gameCols, gameRows);
  }
}
