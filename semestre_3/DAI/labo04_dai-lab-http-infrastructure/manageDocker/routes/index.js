const express = require('express');
const Docker = require('dockerode');
const compose = require('docker-compose');
const path = require('path');

const router = express.Router();
const docker = new Docker();

const staticImgName = "dai-lab-http-infrastructure-static";
const expressImgName = "hdai-lab-http-infrastructure-express";

// Utility function to handle errors
const handleError = (res, err) => {
  const statusCode = err.statusCode || 500;
  const message = err.json?.message || err.message || "An error occurred";
  res.status(statusCode).json({ error: message });
};

// GET all containers
router.get('/', async (req, res) => {
  try {
    const containers = await docker.listContainers({ all: true });
    res.render('index', { containers });
  } catch (err) {
    handleError(res, err);
  }
});

// Start a container
router.put('/run', async (req, res) => {
  try {
    const container = docker.getContainer(req.body.id);
    await container.start();
    res.status(200).json({ msg: "Container started" });
  } catch (err) {
    handleError(res, err);
  }
});

// Stop a container
router.put('/stop', async (req, res) => {
  try {
    const container = docker.getContainer(req.body.id);
    await container.stop();
    res.status(200).json({ msg: "Container stopped" });
  } catch (err) {
    handleError(res, err);
  }
});

// Remove a container
router.delete('/remove', async (req, res) => {
  try {
    const container = docker.getContainer(req.body.id);
    await container.remove();
    res.status(200).json({ msg: "Container removed" });
  } catch (err) {
    handleError(res, err);
  }
});

// Start all containers
router.put('/runAll', async (req, res) => {
  try {
    const containers = await docker.listContainers({ all: true });
    await Promise.all(
      containers.map(async (containerInfo) => {
        const container = docker.getContainer(containerInfo.Id);
        try {
          await container.start();
        } catch (err) {
          if (err.statusCode !== 304) throw err; // Ignore "already started" error
        }
      })
    );
    res.status(200).json({ msg: "All containers are running" });
  } catch (err) {
    handleError(res, err);
  }
});

// Stop all containers
router.put('/stopAll', async (req, res) => {
  try {
    const containers = await docker.listContainers();
    await Promise.all(
      containers.map(async (containerInfo) => {
        const container = docker.getContainer(containerInfo.Id);
        await container.stop();
      })
    );
    res.status(200).json({ msg: "All containers are stopped" });
  } catch (err) {
    handleError(res, err);
  }
});

// Create a new instance
router.post('/create', async (req, res) => {
  try {
    const type = req.body.type;
    const home = path.join(__dirname, '..');

    const containers = await docker.listContainers({ all: true });
    const nbInstance = containers.reduce(
      (counts, container) => {
        if (container.Image === staticImgName) counts.static++;
        if (container.Image === expressImgName) counts.express++;
        return counts;
      },
      { express: 0, static: 0 }
    );

    if (type === "static") nbInstance.static++;
    if (type === "express") nbInstance.express++;

    const staticOpt = `static=${nbInstance.static}`;
    const expressOpt = `express=${nbInstance.express}`;

    await compose.upAll({
      cwd: home,
      commandOptions: [["--scale", staticOpt], ["--scale", expressOpt]],
    });

    res.status(200).json({ msg: `Instance of ${type} created` });
  } catch (err) {
    handleError(res, err);
  }
});

module.exports = router;
