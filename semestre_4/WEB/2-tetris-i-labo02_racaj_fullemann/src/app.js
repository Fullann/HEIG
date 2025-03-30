import { Renderer } from "./renderer.js";
import { Game } from "./game.js";
import { PlayerInfo } from "./playerInfo.js";
import { PlacedShapesGrid } from "./placedShapesGrid.js";
import { gameCols, gameRows, stepIntervalMs } from "./constants.js";

const playerId = 0;
const canvas = document.getElementById("canvas");

if (!canvas) {
  console.error("Canvas element not found!");
} else {
  const context = canvas.getContext("2d");
  const game = new Game(new PlacedShapesGrid(gameCols, gameRows));
  const player = new PlayerInfo(playerId);
  const renderer = new Renderer(game, context);

  game.set(playerId, player);
  game.addNewFallingShape(playerId);

  const renderLoop = () => {
    renderer.render();
    requestAnimationFrame(renderLoop);
  };

  const gameLoop = () => game.step();

  requestAnimationFrame(renderLoop);
  setInterval(gameLoop, stepIntervalMs);
}
