import { FallingShape } from "./fallingShape.js";
import {
  SetPlayerMessage,
  RemovePlayerMessage,
  UpdateGridMessage,
  GameOverMessage,
  MessageCodec,
} from "./messages.js";
import { scorePerLine } from "./constants.js";

/**
 * A game of Tetris that can be drawn by a renderer.
 */
export class DrawableGame extends Map {
  constructor(grid) {
    super();
    this.grid = grid;
  }

  /**
   * Returns FallingShape of given player, or undefined if no such player or shape.
   * @param {Number} id Id of the player whose falling shape is to be returned.
   */
  getFallingShape(id) {
    return this.get(id)?.getFallingShape();
  }

  /**
   * Executes the provided function on each falling shape in the game.
   * @param {Function} f The function to be executed. It takes a falling shape as unique parameters, and its return value is ignored.
   */
  forEachFallingShape(f) {
    this.forEach((p) => {
      if (p && p.shape) {
        f(p.shape);
      }
    });
  }

  /**
   * Computes and returns the total scores of every player in the game.
   *
   * The total score of a player is {@link scorePerLine} times the number of lines they have cleared, minus the number of blocks belonging to them that are still on the grid.
   */
  getTotalScores() {
    const scores = new Map();
    const bpp = this.grid.getBlocksPerPlayer();
    bpp.forEach((blocks, key) => {
      scores.set(key, -blocks);
    });

    this.forEach((pInfo, key) => {
      const currentScore = scores.get(key) || 0;
      scores.set(key, currentScore + pInfo.getClearedLines() * scorePerLine);
    });

    return scores;
  }
}

/**
 * A game of Tetris that lives on the server and handles the game logic.
 */
export class Game extends DrawableGame {
  /**
   *
   * @param {PlacedShapesGrid} grid The map on which the game is played.
   * @param {Function} messageSender A function that will broadcast any message passed to it to all connected players.
   * @param {Function} onGameOver A function that will be called when the game is over.
   */
  constructor(grid, messageSender, onGameOver) {
    super(grid);
    this.onGameOver = onGameOver;
    this.sendMessage = messageSender;
  }

  /**
   * Moves the given shape to the given column, if possible.
   * @param {Number} id The id of the player whose shape should be moved.
   * @param {Number} col The column to which the shape should be moved.
   */
  moveShape(id, col) {
    const shape = this.getFallingShape(id);
    if (shape === undefined) {
      console.log("Shape " + id + " does not exist ; cannot move it");
      return;
    }
    if (this.grid.testShape(shape, shape.row, col)) {
      shape.col = col;
      // Broadcast updated player info
      this.sendMessage(new SetPlayerMessage(this.get(id)));
    }
  }

  /**
   * Rotates the given shape in the given direction, if possible.
   * @param {Number} id The id of the player whose shape should be rotated.
   * @param {String} rotation The direction of the rotation, either "left" or "right"
   */
  rotateShape(id, rotation) {
    let shape = this.getFallingShape(id);
    if (shape === undefined) {
      console.log("Shape " + id + " does not exist ; cannot rotate it");
      return;
    }

    rotation = (shape.rotation + (rotation === "left" ? 3 : 1)) % 4;

    if (this.grid.testShape(shape, shape.row, shape.col, rotation)) {
      shape.rotation = rotation;
      // Broadcast updated player info
      this.sendMessage(new SetPlayerMessage(this.get(id)));
    }
  }

  /**
   * Tries to slam the given player's falling shape, i.e. move it down until it touches something if necessary, and then placing it onto the grid.
   * @param {Number} playerId The id of the player whose falling shape should be slammed
   */
  slamShape(playerId) {
    const player = this.get(playerId);
    if (player === undefined) {
      console.log("Cannot find player " + playerId + "; ignoring");
      return;
    }

    const shape = player.shape;
    if (shape === undefined) {
      console.log(
        "Shape " + playerId + " does not exist; cannot slam it; ignoring"
      );
      return;
    }

    this.grid.slamShape(shape);

    // Count cleared lines and update player info
    const clearedLines = this.grid.clearFullRows();
    if (clearedLines > 0) {
      player.clearedLines += clearedLines;
    }

    // Send updated grid
    this.sendMessage(new UpdateGridMessage(this.grid));

    // Replace this shape and any overlapping falling
    this.addNewFallingShape(player.id);

    this.forEach((p, id) => {
      const shape = p.shape;
      if (shape !== undefined && id !== player.id) {
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
    let toSlam = [];
    let hasChanges = false;

    this.forEachFallingShape((shape) => {
      const row = shape.row;
      if (row === undefined) {
        console.log("Invalid coordinates for shape. Ignoring it.");
        return;
      }
      // If they can move down, move them down
      if (this.grid.testShape(shape, row + 1)) {
        shape.row++;
        hasChanges = true;
      } else {
        // If they cannot move down, ground them
        toSlam.push(shape);
      }
    });

    this.forEach((player) => {
      this.sendMessage(new SetPlayerMessage(player));
    });

    toSlam.forEach((shape) => {
      const id = shape.playerId;
      if (this.grid.testShape(shape)) {
        this.slamShape(id);
        hasChanges = true;
      } else {
        console.log(
          "Shape was not slammable, doing nothing because assuming that a previous `slamShape` has reset it."
        );
      }
    });
  }

  /**
   * Informs the game that a new player has joined, and gives them a new shape.
   *
   * @param {PlayerInfo} player The player that has joined. If it has a shape, it will be overwritten by a new random one.
   */
  introduceNewPlayer(player) {
    if (!this.get(player.getId())) {
      this.set(player.getId(), player);
      this.addNewFallingShape(player.getId());
    }
  }

  /**
   * Replace current falling shape of given player id (if any) with a new random shape.
   * @param {Number} id Id of the player whose shape should be replaced.
   */
  addNewFallingShape(id) {
    const col = parseInt(this.grid.width / 2);
    const shapeType = FallingShape.getRandomShapeType();
    const shape = new FallingShape(shapeType, id, col, 0, 0);
    const player = this.get(id);
    if (player !== undefined) {
      player.shape = shape;
      // Broadcast updated player info
      this.sendMessage(new SetPlayerMessage(player));
    } else {
      throw new Error("Cannot find player with id " + id);
    }

    if (!this.grid.testShape(shape)) {
      this.gameOver();
    }
  }

  /**
   * Resets the game upon game over.
   */
  gameOver() {
    this.sendMessage(new GameOverMessage());
    this.clear();
    this.grid.clear();
    this.onGameOver();
  }

  /**
   * Handles an incoming message.
   * @param {Number} playerId The id of the player that sent this message.
   * @param {Message} message The message to be handled.
   */
  onMessage(playerId, message) {
    switch (message.constructor.name) {
      case "RotateMessage":
        this.rotateShape(playerId, message.getDirection());
        break;
      case "MoveMessage":
        this.moveShape(playerId, message.getCol());
        break;
      case "SlamMessage":
        this.slamShape(playerId);
        break;
      default:
        throw new Error("Unknown message type: " + message.constructor.name);
    }
  }

  /**
   * Informs the game that a player has left. The game will then remove the player from the game.
   *
   * @param {number} playerId The id of the player that has left.
   */
  quit(playerId) {
    this.delete(playerId);
    this.sendMessage(new RemovePlayerMessage(playerId));
  }
}

/**
 * A game of Tetris that lives on the client and is only responsible for remaining in sync with the server's instance of the game.
 */
export class Replica extends DrawableGame {
  /**
   * Handles incoming messages from the server.
   * @param {Message} message The message to be handled.
   */
  onMessage(message) {
    if (message instanceof MessageCodec.types.SetPlayerMessage) {
      this.set(message.getPlayerId(), message.getPlayer());
    }
    if (message instanceof MessageCodec.types.UpdateGridMessage) {
      this.grid = message.getGrid();
    }
    if (message instanceof MessageCodec.types.RemovePlayerMessage) {
      this.delete(message.getPlayerId());
    }
    if (message instanceof MessageCodec.types.GameOverMessage) {
      this.gameOver();
    }
  }

  /**
   * Displays a popup informing the player that the game is over, and the id of the winning player, along with their score.
   */
  gameOver() {
    const scores = this.getTotalScores();
    const sortedScores = [...scores.entries()].sort((a, b) => b[1] - a[1]);

    if (sortedScores.length > 0) {
      const [id, score] = sortedScores[0];

      alert(`Player ${id} wins! Score: ${score}`);
    } else {
      alert("Game over! No players left.");
    }
  }
}
