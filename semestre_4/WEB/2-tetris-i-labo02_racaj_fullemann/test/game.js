import { assert, expect } from 'chai';
import { PlayerInfo } from '../src/playerInfo.js';
import { Game } from '../src/game.js';
import { PlacedShapesGrid } from '../src/placedShapesGrid.js';
import { FallingShape } from '../src/fallingShape.js';

class MockGrid extends PlacedShapesGrid {
    constructor(width, height, onPlaceShape, onClearFullRows) {
        super(width, height);
        this.onPlaceShape = onPlaceShape;
        this.onClearFullRows = onClearFullRows;
    }

    placeShape(shape) {
        if (this.onPlaceShape) {
            this.onPlaceShape(shape);
        }
        return super.placeShape(shape);
    }

    clearFullRows() {
        if (this.onClearFullRows) {
            this.onClearFullRows();
        }
        return super.clearFullRows();
    }
}

function createGame(grid, shapes) {
    let game = new Game(grid);
    shapes.forEach((shape) => {
        let pi = new PlayerInfo(shape.playerId, shape)
        game.set(shape.playerId, pi);
    });
    return game;
}

describe('Game stepping', () => {
    it('All shapes should move down by 1', () => {
        const grid = new PlacedShapesGrid(10, 10);
        let rows = new Map([[1, 3], [2, 5]]);
        let shapes = Array.from(rows.entries()).map(([id, row]) => new FallingShape(0, id, 5, row, 0));

        const game = createGame(grid, shapes);

        game.step();
        
        game.forEachFallingShape((s) => {
            expect(s, "Shape").to.not.be.undefined;
            expect(s.row, "Shape row").to.equal(rows.get(s.playerId) + 1)
        });

        expect(rows.keys, "Player ids").to.deep.equal(game.keys);
    });
    it('Should ask grid to place shape when touching the ground upon step, and clear full rows.', () => {
        let placeCount = 0;
        let clearCount = 0;

        let shape1 = new FallingShape(0, 1, 5, 3, 0);
        let shape2 = new FallingShape(0, 2, 5, 1, 0);

        const grid = new MockGrid(10, 5, (shape) => {
            placeCount++;
            // Only player 1's shape should be placed.
            expect(shape.playerId, "Player Id of the shape that got placed").to.equal(1);
        }, () => {
            clearCount++;
        });

        let game = createGame(grid, [shape1, shape2]);

        game.step();

        expect(placeCount, "Number of shapes placed on the grid").to.equal(1);
        expect(clearCount, "Number of times row was asked to be cleared").to.equal(1);
    });
    it('If multiple shapes touch the ground upon stepping, they should be placed and be replaced, the others unaffected.', () => {
        let shape1 = new FallingShape(0, 1, 2, 3, 0); // will be placed
        let shape2 = new FallingShape(0, 2, 5, 1, 0);
        let shape3 = new FallingShape(0, 3, 7, 3, 0); // will be placed

        shape1.testShape = true;
        shape2.testShape = true;
        shape3.testShape = true;

        let grid = new PlacedShapesGrid(10, 5);
        
        let game = createGame(grid, [shape1, shape2, shape3]);
        
        game.step();

        expect(game.size, "Number of players in the game").to.equal(3)
        
        expect(game.getFallingShape(1), "Shape after it was placed").to.not.be.undefined;
        expect(game.getFallingShape(3), "Shape after it was placed").to.not.be.undefined;
        
        expect(game.getFallingShape(1).testShape, "Whether shape is the same as before after it was placed").to.be.undefined;
        expect(game.getFallingShape(3).testShape, "Whether shape is the same as before after it was placed").to.be.undefined;

        expect(game.getFallingShape(2).testShape, "Whether shape is the same as before after another was placed").to.not.be.undefined;
    })
    it('If two shapes overlap when touching the ground, only one should be placed', () => {
        let shape1 = new FallingShape(0, 1, 5, 3, 0);
        let shape2 = new FallingShape(0, 2, 5, 3, 0);

        shape1.testShape = true;
        shape2.testShape = true;

        let placeCount = 0;

        let grid = new MockGrid(10, 5, (shape) => { placeCount++; });
        
        let game = createGame(grid, [shape1, shape2]);
        
        game.step();

        expect(game.size, "Number of players after placing.").to.equal(2)
        
        expect(game.getFallingShape(1), "Shape after it was placed").to.not.be.undefined;
        expect(game.getFallingShape(2), "Shape after it was placed.").to.not.be.undefined;
        
        expect(game.getFallingShape(1).testShape, "Whether shape is the same after it was placed").to.be.undefined;
        expect(game.getFallingShape(2).testShape, "Whether shape is the same after it was placed").to.be.undefined;

        expect(placeCount, "Number of shapes that actually placed on the grid").to.equal(1);
    })
});