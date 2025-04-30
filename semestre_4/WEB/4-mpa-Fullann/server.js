import express from "express";
import sqlite3 from "sqlite3";
import path from "path";
import { fileURLToPath } from "url";

const app = express();
const db = new sqlite3.Database("dictons.sqlite");

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Configuration du moteur de templates EJS
app.set("view engine", "ejs");
app.set("views", path.join(__dirname, "views")); 

// Middleware pour parser les données de formulaire
app.use(express.urlencoded({ extended: true }));

// GET / - Affiche un dicton aléatoire
app.get("/", (req, res) => {
  db.get("SELECT * FROM dictons ORDER BY RANDOM() LIMIT 1", (err, row) => {
    if (err) return res.status(500).send(err.message);
    res.render("index", { dicton: row?.dicton || "Aucun dicton trouvé" });
  });
});

// GET /list - Liste tous les dictons
app.get("/list", (req, res) => {
  db.all("SELECT * FROM dictons ORDER BY id", (err, rows) => {
    if (err) return res.status(500).send(err.message);
    res.render("list", { dictons: rows });
  });
});

// GET /create - Formulaire de création
app.get("/create", (req, res) => {
  res.render("create");
});

// POST /create - Traitement du formulaire
app.post("/create", (req, res) => {
  const { dicton } = req.body;
  db.run("INSERT INTO dictons (dicton) VALUES (?)", [dicton], function (err) {
    if (err) return res.status(500).send(err.message);
    res.redirect("/list");
  });
});

// GET /:id - Affiche un dicton par ID
app.get("/:id", (req, res) => {
  const { id } = req.params;
  db.get("SELECT * FROM dictons WHERE id = ?", [id], (err, row) => {
    if (err) return res.status(500).send(err.message);
    if (!row) return res.status(404).send("Dicton non trouvé");

    res.render("dicton", { dicton: row.dicton, id });
  });
});

export default app;
