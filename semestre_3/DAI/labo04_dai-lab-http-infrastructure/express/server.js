const express = require("express");
const app = express();
const PORT = process.env.PORT || 3000;

// Middleware pour parser le JSON
app.use(express.json());

// Stockage des données en mémoire
let items = [];
let currentId = 1;

// Route principale
app.get("/", (req, res) => {
  res.send({ message: "Bienvenue sur l'API!" });
});

// Vérification du statut de l'API
app.get("/api/status", (req, res) => {
  res.send({ status: "success", message: "API en ligne!" });
});

// CRUD Operations
// Créer un nouvel élément
app.post("/api/items", (req, res) => {
  const { name, value } = req.body;
  if (!name || !value) {
    return res.status(400).send({ error: "Les champs 'name' et 'value' sont requis." });
  }
  const newItem = { id: currentId++, name, value };
  items.push(newItem);
  res.status(201).send(newItem);
});

// Lire tous les éléments
app.get("/api/items", (req, res) => {
  res.send(items);
});

// Lire un élément par ID
app.get("/api/items/:id", (req, res) => {
  const { id } = req.params;
  const item = items.find((item) => item.id === parseInt(id));
  if (!item) {
    return res.status(404).send({ error: "Élément non trouvé." });
  }
  res.send(item);
});

// Mettre à jour un élément
app.put("/api/items/:id", (req, res) => {
  const { id } = req.params;
  const { name, value } = req.body;
  const item = items.find((item) => item.id === parseInt(id));
  if (!item) {
    return res.status(404).send({ error: "Élément non trouvé." });
  }
  if (name) item.name = name;
  if (value) item.value = value;
  res.send(item);
});

// Supprimer un élément
app.delete("/api/items/:id", (req, res) => {
  const { id } = req.params;
  const index = items.findIndex((item) => item.id === parseInt(id));
  if (index === -1) {
    return res.status(404).send({ error: "Élément non trouvé." });
  }
  const deletedItem = items.splice(index, 1);
  res.send(deletedItem[0]);
});

// Lancer le serveur
app.listen(PORT, () => {
  console.log(`Serveur démarré sur le port ${PORT}`);
});
