import { FallingShape } from "./fallingShape.js";
import { PlacedShapesGrid } from "./placedShapesGrid.js";
import { PlayerInfo } from "./playerInfo.js";

/**
 * Parent class for all messages used to communicate between server and client.
 */
export class Message {
  constructor(data) {
    this.data = data;
  }
}

/**
 * Message describing a request by the client to rotate their shape
 */
export class RotateMessage extends Message {
  /**
   * @param {String} direction The direction of rotation : either "left" or "right".
   */
  constructor(direction) {
    super(direction);
  }

  getDirection() {
    return this.data;
  }
}

/**
 * Message describing a request by the client to move their shape.
 */
export class MoveMessage extends Message {
  /**
   * @param {Number} col The column the shape should be moved to.
   */
  constructor(col) {
    super(col);
  }

  getCol() {
    return this.data;
  }
}

/**
 * Message describing a request by the client to slam their shape.
 */
export class SlamMessage extends Message {
  constructor() {
    super();
  }
}

/**
 * Message describing a notification by the server of a player's new state.
 */
export class SetPlayerMessage extends Message {
  /**
   * @param {PlayerInfo} player The PlayerInfo describing the player's new state.
   */
  constructor(player) {
    super(player);
  }

  /**
   * @returns {FallingShape} An instance of FallingShape describing the player's falling shape.
   */
  getFallingShape() {
    const s = this.data.shape;
    if (!s) return undefined;
    return new FallingShape(s.shapeType, s.playerId, s.col, s.row, s.rotation);
  }

  getPlayerId() {
    return this.data.id;
  }

  getClearedLines() {
    return this.data.clearedLines;
  }

  /**
   * @returns {PlayerInfo} An instance of PlayerInfo describing the player's new state, including all fields of the class in the correct type.
   */
  getPlayer() {
    return new PlayerInfo(
      this.getPlayerId(),
      this.getFallingShape(),
      this.getClearedLines()
    );
  }
}

/**
 * Message describing a notification by the server of a player's removal.
 */
export class RemovePlayerMessage extends Message {
  /**
   * @param {Number} playerId The id of the player to be removed.
   */
  constructor(playerId) {
    super(playerId);
  }

  getPlayerId() {
    return this.data;
  }
}

/**
 * Message describing a notification by the server of a new placed shapes grid state.
 */
export class UpdateGridMessage extends Message {
  /**
   * @param {PlacedShapesGrid} grid The new game map state.
   */
  constructor(grid) {
    super(grid);
  }

  getGrid() {
    const data = this.data;
    const placedShapesGrid = new PlacedShapesGrid(data.width, data.height);

    // Copy grid data
    if (data.grid) {
      placedShapesGrid.grid = JSON.parse(JSON.stringify(data.grid));
    }

    // Copy map data
    if (data.map) {
      placedShapesGrid.map = JSON.parse(JSON.stringify(data.map));
    }

    return placedShapesGrid;
  }
}

/**
 * Message describing a notification by the server that the game is over.
 */
export class GameOverMessage extends Message {
  constructor() {
    super();
  }
}

/**
 * Message describing a notification by the server that a new player has joined.
 */
export class JoinMessage extends Message {
  /**
   * @param {Number} playerId The id of the new player.
   */
  constructor(playerId) {
    super(playerId);
    this.playerId = playerId;
  }

  getPlayerId() {
    return this.data;
  }
}

/**
 * Codec for encoding and decoding messages.
 */
export class MessageCodec {
  static types = {
    MoveMessage,
    RotateMessage,
    SlamMessage,
    SetPlayerMessage,
    RemovePlayerMessage,
    UpdateGridMessage,
    JoinMessage,
    GameOverMessage,
  };

  /**
   * Encodes a message into a string in JSON format.
   */
  static encode(message) {
    return JSON.stringify({
      type: message.constructor.name,
      data: message.data,
    });
  }

  /**
   * Decodes a message from a string in JSON format into an instance of the corresponding message class.
   * @param {String} string The string to be decoded.
   * @returns {Message} An instance of the corresponding message class.
   */
  static decode(string) {
    const msg = JSON.parse(string);
    const MessageType = MessageCodec.types[msg.type];

    if (!MessageType) {
      throw new Error(`Unknown message type: ${msg.type}`);
    }

    if ("data" in msg) {
      return new MessageType(msg.data);
    }

    return new MessageType();
  }
}
