import { Renderer } from "./renderer.js";
import { Game } from "./game.js";
import { PlayerInfo } from "./playerInfo.js";
import { PlacedShapesGrid } from "./placedShapesGrid.js";
import { gameCols, gameRows, stepIntervalMs } from "./constants.js";

const canvas = document.getElementById("canvas");
const context = canvas.getContext("2d");
const grid = new PlacedShapesGrid(gameCols, gameRows);
const game = new Game(grid);

const playerId = 0;
game.set(playerId, new PlayerInfo(playerId));
game.addNewFallingShape(playerId);

const renderer = new Renderer(game, context);

// Game loop
setInterval(() => {
  game.step();
}, stepIntervalMs);

// Render loop
function loop() {
  renderer.render();
  requestAnimationFrame(loop);
}
requestAnimationFrame(loop);

setListeners(canvas, (message) => game.onMessage(playerId, message));
