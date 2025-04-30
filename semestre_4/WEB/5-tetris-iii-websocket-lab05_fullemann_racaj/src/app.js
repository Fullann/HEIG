import { Renderer } from "./renderer.js";
import { Replica } from "./game.js";
import { PlacedShapesGrid } from "./placedShapesGrid.js";
import { gameCols, gameRows,port } from "./constants.js";
import { MessageCodec } from "./messages.js";

const canvas = document.getElementById("canvas");
const context = canvas.getContext("2d");
const grid = new PlacedShapesGrid(gameCols, gameRows);
const replica = new Replica(grid);
const renderer = new Renderer(replica, context);
import { setListeners } from "./inputListener.js";

// Render loop
function loop() {
  renderer.render();
  requestAnimationFrame(loop);
}
requestAnimationFrame(loop);

// Get hostname from current URL, and use it to open a Web socket to the corresponding `ws://` URL.
const socket = new WebSocket(`ws://${window.location.hostname}:${port}`);

const { JoinMessage } = MessageCodec.types;

// Handle socket events
socket.onopen = () => {
  setListeners(canvas, (message) => {
    socket.send(MessageCodec.encode(message));
  });
};

socket.onmessage = (event) => {
  const decodedMsg = MessageCodec.decode(event.data);
  if (decodedMsg instanceof JoinMessage) {
    renderer.setPlayerId(decodedMsg.data);
  }
  replica.onMessage(decodedMsg);
};
