[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/orCrxYnf)
# Multi-page Application

In this assignment, you are asked to implement a multi-page application with
Express and SQLite. The goal is to create a small web site for managing french
[dictons](https://fr.wiktionary.org/wiki/Annexe:Liste_de_proverbes_fran%C3%A7ais).

The `dictons.sqlite` file contains the SQLite database.

The pages displayed by the applications are described in the `server.js` file.
All your changes should take place in this file.

You must use a template engine to render the Web pages.

A few unit tests have been included in the `test/tests.js` file to guide you
through the assignment and validate your progress.

To complete this assignment, you will probably have to read some documentation
and to include some modules. Remember that the simplest and boring solutions are
often the best (i.e. You can have fun with an ORM but it is not a requirement).

## Prerequisites

- Node 22 (LTS)

## Setup

Install project dependencies

```sh
npm install
```

Start the server

```sh
npm run start

# or start server in watch mode
# so it automatically restarts on file changes
npm run watch
```

The website is available at [http://localhost:3000](http://localhost:3000)

Run tests

```sh
npm run test
```

## Additional information

It will require a bit more research and autonomy.

I advise you to have a look at the ExpressJS documentation, to do the hello
world guide. Search for "ExpressJS + Sqlite" tutorials using your favorite
search engine.

The theoretical example is <https://github.com/web-classroom/example-express>

The available tests will help you to find out what is expected of you, i.e. a
web application with the following endpoints (pages) :

- [localhost:3000/](localhost:3000/): a page that gives you a random saying
- [localhost:3000/list](localhost:3000/list): a page that shows you a list of
  sayings
- [localhost:3000/create](localhost:3000/create): a page that lets you create a
  saying
- [localhost:3000/:id](https://www.youtube.com/watch?v=bAojxWZRVKk): a page that
  shows you a saying by its id

The keywords for this type of application are :

- "CRUD": Short for "Create, Read, Update and Delete", we're looking to read and
  create sayings.
- "ExpressJS": this is the framework we use.
- "Sqlite3": this is the database we provide that contains sayings.
- "template engines": we no longer use HTML, but templates such as "ejs", "pug",
  "nunjucks".

If you accounter any issues with the tests, please check
[the following](https://pptr.dev/troubleshooting)
