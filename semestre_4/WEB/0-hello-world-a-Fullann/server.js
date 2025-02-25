import { createServer } from "http";
import process from "node:process";

const debugMode = process.argv.includes("--debug");

const port = 3000;

const hello = "Hello, World!";

const html = `
<!doctype html>
<link rel="stylesheet" href="/style.css" />
<script src="/script.js"></script>
<h1>Hello, World!</h1>
`;

const css = `
h1 {color: red;}
`;

const javascript = `
alert("${hello}");
`;

const info = function (message) {
  if (debugMode) {
    console.log("INFO: " + message);
  }
};

info(`Server running at http://localhost:${port}/`);

createServer(function (req, res) {
  if (req.url === "/" || req.url === "/index.html") {
    res.writeHead(200, { "Content-Type": "text/html" });
    res.write(html);
  } else if (req.url === "/style.css") {
    res.writeHead(200, { "Content-Type": "text/css" });
    res.write(css);
  } else if (req.url === "/script.js") {
    res.writeHead(200, { "Content-Type": "application/javascript" });
    res.write(javascript);
  } else {
    res.writeHead(404, { "Content-Type": "text/plain" });
    res.write("404 Not Found");
  }
  res.end();
}).listen(port, () => {
  console.log(`Server is running at http://localhost:${port}/`);
});
