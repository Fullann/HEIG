import { cellPixelSize, shapeColors } from "./constants.js";

function cellToPixel(x) {
  return x * cellPixelSize;
}

export class Renderer {
  constructor(game, context) {
    this.game = game;
    this.context = context;
    this.playerId = undefined;

    // Set a reference to allow the grid to update the UI with player info
    if (game && game.grid) {
      game.grid.playerId = undefined;
    }
  }

  /**
   * Sets the player id of the current player.
   * @param {number} playerId The id of the current player.
   */
  setPlayerId(playerId) {
    this.playerId = playerId;

    // Update the grid's reference to the player ID
    if (this.game && this.game.grid) {
      this.game.grid.playerId = playerId;
    }

    // Update the UI
    this.showCurrentPlayerId();
  }

  /**
   * Renders a block at the given position and with the given color.
   * @param {Number} col The column where the block should be drawn.
   * @param {Number} row The row where the block should be drawn.
   * @param {String} color The color of the block.
   */
  renderBlock(col, row, color) {
    this.context.fillStyle = color.replace("x", "0.7"); // Replace x with actual opacity
    this.context.fillRect(
      cellToPixel(col),
      cellToPixel(row),
      cellPixelSize,
      cellPixelSize
    );
    this.context.strokeStyle = "black";
    this.context.strokeRect(
      cellToPixel(col),
      cellToPixel(row),
      cellPixelSize,
      cellPixelSize
    );
  }

  /**
   * Renders the given falling shape.
   * @param {FallingShape} shape The shape to be drawn
   */
  renderFallingShape(shape) {
    if (shape === undefined) {
      return;
    }

    const coords = shape.getCoordinates();
    for (let i = 0; i < coords.length; i++) {
      const coord = coords[i];
      const x = shape.col + coord[0];
      const y = shape.row + coord[1];
      // Only draw if coordinates are within the visible area
      if (
        y >= 0 &&
        x >= 0 &&
        x < this.game.grid.width &&
        y < this.game.grid.height
      ) {
        const color = shapeColors[shape.playerId % shapeColors.length];
        this.renderBlock(x, y, color);
      }
    }
  }

  /**
   * Clears the context and draws all falling and placed shapes.
   */
  render() {
    // Only update the UI elements if we're in a browser environment
    if (typeof document !== "undefined") {
      this.showCurrentPlayerId();
      this.updateScores();
    }

    // Reset context
    this.context.strokeStyle = "black";
    this.context.clearRect(
      0,
      0,
      this.context.canvas.width,
      this.context.canvas.height
    );

    // Draw shapes
    this.game.forEachFallingShape((s) => {
      this.renderFallingShape(s);
    });

    // Draw map
    for (let row = 0; row < this.game.grid.height; row++) {
      for (let col = 0; col < this.game.grid.width; col++) {
        const cell = this.game.grid.getPlayerAt(row, col);
        if (cell !== -1) {
          const color = shapeColors[cell % shapeColors.length];
          this.renderBlock(col, row, color);
        }
      }
    }
  }

  /**
   * Updates the scores displayed on the page.
   */
  updateScores() {
    // Only proceed if document exists (browser environment)
    if (typeof document === "undefined") return;

    const scoresElem = document.getElementById("scores");
    if (!scoresElem) return;

    try {
      const scores = new Map(
        [...this.game.getTotalScores()].sort((a, b) => b[1] - a[1])
      );
      const table = document.createElement("table");
      table.setAttribute("id", "score_table");

      scores.forEach((score, playerId) => {
        const row = table.insertRow();
        row.insertCell(0).textContent = `Player ${playerId}`;
        row.insertCell(1).textContent = " : ";
        row.insertCell(2).textContent = score;
      });

      scoresElem.innerHTML = "";
      scoresElem.appendChild(table);
    } catch (e) {
      console.error("Error updating scores:", e);
    }
  }

  /**
   * Updates the current player id displayed on the page.
   */
  showCurrentPlayerId() {
    // Only proceed if document exists (browser environment)
    if (typeof document === "undefined") return;

    const curr_player = document.getElementById("currentPlayer");
    if (!curr_player) return;

    curr_player.textContent = `You are player ${this.playerId}`;
  }
}
