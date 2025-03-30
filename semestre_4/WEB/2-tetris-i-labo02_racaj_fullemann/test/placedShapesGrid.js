import { assert, expect } from 'chai';
import { PlayerInfo } from '../src/playerInfo.js';
import { Game } from '../src/game.js';
import { PlacedShapesGrid } from '../src/placedShapesGrid.js';
import { FallingShape } from '../src/fallingShape.js';

function getTestSlammingOnGround(hovering) {
    return () => {
        const grid = new PlacedShapesGrid(5, 5);
        const shape = new FallingShape(0, 1, 2, 3 - (hovering ? 1 : 0), 0);
        grid.slamShape(shape);
        expect(grid.map, "Game grid after slamming shape").to.deep.equal([
            [-1, -1, -1, -1, -1],
            [-1, -1, -1, -1, -1],
            [-1, -1, -1, -1, -1],
            [-1, 1, 1, 1, -1],
            [-1, -1, 1, -1, -1]]);
    }
}

function getTestSlammingOnShape(hovering) {
    return () => {
        const grid = new PlacedShapesGrid(5, 5);
        grid.map = [
            [-1, -1, -1, -1, -1],
            [-1, -1, -1, -1, -1],
            [-1, -1, -1, -1, -1],
            [-1, 2, -1, -1, -1],
            [-1, 2, -1, -1, -1]];
        const shape = new FallingShape(0, 1, 2, 2 - (hovering ? 2 : 0), 0);
        grid.slamShape(shape);
        expect(grid.map, "Game grid after slamming shape").to.deep.equal([
            [-1, -1, -1, -1, -1],
            [-1, -1, -1, -1, -1],
            [-1, 1, 1, 1, -1],
            [-1, 2, 1, -1, -1],
            [-1, 2, -1, -1, -1]]);
    }
}

function getTestTestShapeOverlap(origin, rotated) {
    return () => {
        const grid = new PlacedShapesGrid(5, 5);
        grid.map = [
            [-1, -1, -1, -1, -1],
            [-1, -1, -1, -1, -1],
            [-1, 2, -1, -1, -1],
            [-1, -1, -1, -1, -1],
            [-1, -1, -1, -1, -1]];
        const shape = new FallingShape(0, 1, 2 - (origin ? 1 : 0), 2, rotated ? 3 : 0);

        if (rotated) {
            expect(grid.testShape(shape), "Whether shape after rotation overlaps").to.be.true;
        } else {
            expect(grid.testShape(shape), "Whether shape overlaps").to.be.false;
        }
    }
}

function getTestTestShapeOutOfBounds(origin, rotated) {
    return () => {
        const grid = new PlacedShapesGrid(5, 5);
        const shape = new FallingShape(0, 1, 0 - (origin ? 1 : 0), 2, rotated ? 3 : 0);

        if (rotated) {
            expect(grid.testShape(shape), "Whether shape after rotation is out of bounds").to.be.true;
        } else {
            expect(grid.testShape(shape), "Whether shape is out of bounds").to.be.false;
        }
    }
}

describe('Slamming a shape', () => {
    it('Shape is touching bottom of grid.', getTestSlammingOnGround(false));
    it('Shape is hovering over bottom of grid.', getTestSlammingOnGround(true));
    it('Shape is touching already placed blocks.', getTestSlammingOnShape(false));
    it('Shape is hovering already placed blocks.', getTestSlammingOnShape(true));
});

describe("Detecting shape collisions", () => {
    it('Shape overlaps placed shape at non-origin coordinates, if not rotated.', getTestTestShapeOverlap(false, false));
    it('Shape does not overlap placed shape if rotated.', getTestTestShapeOverlap(false, true));
    it('Shape overlaps placed shape at its origin.', getTestTestShapeOverlap(true, false));

    it('Shape out of bounds at non-origin coordinates, if not rotated.', getTestTestShapeOutOfBounds(false, false));
    it('Shape not out of bounds iff rotated.', getTestTestShapeOutOfBounds(false, true));
    it('Shape out of bounds at its origin.', getTestTestShapeOutOfBounds(true, false));
});

describe("Clearing full rows", () => {
    it('Exactly one row to clear.', () => {
        const grid = new PlacedShapesGrid(5, 5);
        grid.map = [
            [-1, -1, -1, -1, -1],
            [-1, -1, 1, -1, -1],
            [1, 2, 1, 1, 5],
            [-1, -1, -1, 4, -1],
            [-1, -1, 3, -1, -1]];
        grid.clearFullRows();

        expect(grid.map, "Game grid after full rows are cleared").to.deep.equal([
            [-1, -1, -1, -1, -1],
            [-1, -1, -1, -1, -1],
            [-1, -1, 1, -1, -1],
            [-1, -1, -1, 4, -1],
            [-1, -1, 3, -1, -1]
        ]);
    });
    it('Multiple rows to clear.', () => {
        const grid = new PlacedShapesGrid(3, 7);
        grid.map = [
            [-1, -1, 1],
            [-1, 1, -1],
            [7, 8, 9],
            [3, 4, 5],
            [6, -1, -1],
            [1, 2, 3],
            [-1, -1, -1]];
        grid.clearFullRows();

        expect(grid.map, "Game grid after full rows are cleared").to.deep.equal([
            [-1, -1, -1],
            [-1, -1, -1],
            [-1, -1, -1],
            [-1, -1, 1],
            [-1, 1, -1],
            [6, -1, -1],
            [-1, -1, -1]]);
    });
    it('No rows to clear.', () => {
        const grid = new PlacedShapesGrid(3, 5);
        grid.map = [
            [7, -1, 9],
            [-1, 4, 5],
            [6, 5, -1],
            [1, 2, -1],
            [-1, -1, -1]];
        grid.clearFullRows();

        expect(grid.map, "Game grid after full rows are cleared").to.deep.equal([
            [7, -1, 9],
            [-1, 4, 5],
            [6, 5, -1],
            [1, 2, -1],
            [-1, -1, -1]]);
    });
});
