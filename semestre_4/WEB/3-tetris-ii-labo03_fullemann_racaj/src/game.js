import { gameRows, gameCols, shapeTypes } from "./constants.js";
import { FallingShape } from "./fallingShape.js";
import { PlacedShapesGrid } from "./placedShapesGrid.js";
import { RotateMessage, MoveMessage, SlamMessage } from "./messages.js";

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
   * @param {Function} f The function to be executed. It takes a falling shape as unique parameters, and its return value is ignored.
   */
  forEachFallingShape(f) {
    this.forEach((p) => f(p.shape));
  }

  /**
   * Moves the given shape to the given column, if possible.
   * @param {Number} id The id of the player whose shape should be moved.
   * @param {Number} col The column to which the shape should be moved.
   */
  moveShape(id, col) {
    const shape = this.getFallingShape(id);
    if (!shape) {
      console.warn(`Cannot move shape for player ${id}: shape does not exist.`);
      return;
    }

    if (Number.isInteger(col) && col >= 0 && col < this.grid.width) {
      if (this.grid.testShape(shape, shape.row, col)) {
      shape.col = col;
      } else {
      console.info(`Shape for player ${id} cannot move to column ${col}: position blocked.`);
      }
    } else {
      console.error(`Invalid column ${col} for player ${id}.`);
    }
  }

  /**
   * Rotates the given shape in the given direction, if possible.
   * @param {Number} id The id of the player whose shape should be rotated.
   * @param {String} rotation The direction of the rotation, either "left" or "right"
   */
  rotateShape(id, rotation) {
    const shape = this.getFallingShape(id);
    if (!shape) {
      console.warn(`Cannot rotate shape for player ${id}: shape does not exist.`);
      return;
    }

    const direction = rotation === "left" ? -1 : rotation === "right" ? 1 : 0;
    if (direction === 0) {
      console.error(`Invalid rotation direction "${rotation}" for player ${id}.`);
      return;
    }

    const totalRotations = shapeTypes[shape.shapeType].length;
    const newRotation = (shape.rotation + direction + totalRotations) % totalRotations;

    if (this.grid.testShape(shape, shape.row, shape.col, newRotation)) {
      shape.rotation = newRotation;
    } else {
      console.info(`Shape for player ${id} cannot rotate to "${rotation}": position blocked.`);
    }
  }

  /**
   * Tries to slam the given player's falling shape, i.e. move it down until it touches something if necessary, and then placing it onto the grid.
   * @param {Number} playerId The id of the player whose falling shape should be slammed
   */
  slamShape(playerId) {
    let player = this.get(playerId);
    if (player === undefined) {
      console.log("Cannot find player " + playerId + "; ignoring");
      return;
    }

    let shape = player.shape;
    if (shape === undefined) {
      console.log(
        "Shape " + playerId + " does not exist; cannot slam it; ignoring"
      );
      return;
    }

    this.grid.slamShape(shape);

    const count = this.grid.clearFullRows();

    // Replace this shape and any overlapping falling
    this.addNewFallingShape(player.id);

    this.forEach((p, id) => {
      let shape = p.shape;
      if (shape !== undefined && id != player.id) {
        if (!this.grid.testShape(shape)) {
          this.addNewFallingShape(id);
        }
      }
    });
  }

  /**
   * Advances the game by one step, i.e. moves all falling shapes down by one, places any shape that was touching the ground, and replaces it with a new one.
   */
  step() {
    if (this.isGameOver) {
      console.log("Game over, not stepping");
      return;
    }

    let toSlam = [];

    // Move all shapes
    for (let player of this.values()) {
      const shape = player.shape;
      if (shape === undefined) {
        continue;
      }
      let row = shape.row;
      if (row === undefined) {
        console.log("Invalid coordinates for shape. Ignoring it.");
        return;
      }
      // If they can move down, move them down
      if (this.grid.testShape(shape, row + 1)) {
        shape.row++;
      } else {
        // If they cannot move down, ground them
        toSlam.push(shape);
        continue;
      }
    }

    toSlam.forEach((shape) => {
      let id = shape.playerId;
      if (this.grid.testShape(shape)) {
        this.slamShape(id);
      } else {
        console.log(
          "Shape was not slammable, doing nothing because assuming that a previous `slamShape` has reset it."
        );
      }
    });
  }

  /**
   * Replace current falling shape of given player id (if any) with a new random shape.
   * @param {Number} id Id of the player whose shape should be replaced.
   */
  addNewFallingShape(id) {
    let col = parseInt(this.grid.width / 2);
    let shapeType = FallingShape.getRandomShapeType();
    let shape = new FallingShape(shapeType, id, col, 0, 0);
    let player = this.get(id);
    if (player !== undefined) {
      player.shape = shape;
    } else {
      throw "Cannot find player with id " + id;
    }

    if (!this.grid.testShape(shape)) {
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

  /**
   * Handles an incoming message.
   * @param {Number} playerId The id of the player that sent this message.
   * @param {Message} message The message to be handled.
   */
  onMessage(playerId, message) {
    if (this.isGameOver) {
      console.warn(`Game over. Ignoring message from player ${playerId}.`);
      return;
    }

    switch (true) {
      case message instanceof RotateMessage:
      this.rotateShape(playerId, message.getDirection());
      break;
      case message instanceof MoveMessage:
      this.moveShape(playerId, message.getCol());
      break;
      case message instanceof SlamMessage:
      this.slamShape(playerId);
      break;
      default:
      console.error(`Unknown message type from player ${playerId}: ${message.constructor.name}`);
    }
  }
}
