import { assert, expect } from "chai";
import { keyHandler, mouseMoveHandler } from "../src/inputListener.js";
import { MoveMessage, RotateMessage, SlamMessage } from "../src/messages.js";
import { cellPixelSize } from "../src/constants.js";

describe("Input Listener", () => {
  it("should not send duplicate messages when mouse moves within the same column", () => {
    const receivedMessages = [];
    const messageListener = (message) => receivedMessages.push(message);
    const handler = mouseMoveHandler(messageListener);

    // Simulate two mouse events in the same column
    handler({ offsetX: 10 }); // Column 0
    handler({ offsetX: 20 }); // Still Column 0

    expect(receivedMessages).to.have.lengthOf(
      1,
      "Only one message should be sent for the same column"
    );
    expect(receivedMessages[0]).to.be.instanceOf(
      MoveMessage,
      "The message should be a MoveMessage"
    );
    expect(receivedMessages[0].getCol()).to.equal(0, "The message should target column 0");
  });

  it("should compute the correct column based on mouse position", () => {
    const receivedMessages = [];
    const messageListener = (message) => receivedMessages.push(message);
    const handler = mouseMoveHandler(messageListener);

    // Test various mouse positions and their expected columns
    const testCases = [
      { offsetX: 0, expectedColumn: 0 }, // Start of column 0
      { offsetX: cellPixelSize, expectedColumn: 1 }, // Start of column 1
      { offsetX: cellPixelSize - 1, expectedColumn: 0 }, // End of column 0
      { offsetX: cellPixelSize * 2.5, expectedColumn: 2 }, // Middle of column 2
      { offsetX: cellPixelSize * 3.9, expectedColumn: 3 }, // End of column 3
    ];

    testCases.forEach(({ offsetX, expectedColumn }) => {
      // Clear previous messages
      receivedMessages.length = 0;

      // Simulate mouse move event
      handler({ offsetX });

      // Verify the message
      expect(receivedMessages).to.have.lengthOf(
        1,
        `One message should be sent for position ${offsetX}`
      );
      expect(receivedMessages[0]).to.be.instanceOf(
        MoveMessage,
        "The message should be a MoveMessage"
      );
      expect(receivedMessages[0].getCol()).to.equal(
        expectedColumn,
        `Mouse position ${offsetX} should map to column ${expectedColumn}`
      );
    });
  });
});

describe("Key Handler", () => {
  it("should send the correct messages for arrow keys", () => {
    const receivedMessages = [];
    const messageListener = (message) => receivedMessages.push(message);
    const handler = keyHandler(messageListener);

    const testCases = [
      {
        key: "ArrowLeft",
        expectedMessage: new RotateMessage("left"),
        description: "left rotation",
      },
      {
        key: "ArrowRight",
        expectedMessage: new RotateMessage("right"),
        description: "right rotation",
      },
      {
        key: "ArrowDown",
        expectedMessage: new SlamMessage(),
        description: "slam",
      },
    ];

    testCases.forEach(({ key, expectedMessage, description }) => {
      // Clear previous messages
      receivedMessages.length = 0;

      // Create mock event
      const mockEvent = {
        key,
        preventDefault: () => {},
      };

      // Simulate key press
      handler(mockEvent);

      // Verify the message
      expect(receivedMessages).to.have.lengthOf(
        1,
        `One message should be sent for ${description}`
      );
      expect(receivedMessages[0]).to.deep.equal(
        expectedMessage,
        `The correct message should be sent for ${description}`
      );
    });
  });

  it("should not send messages for non-arrow keys", () => {
    const receivedMessages = [];
    const messageListener = (message) => receivedMessages.push(message);
    const handler = keyHandler(messageListener);

    const nonArrowKeys = ["a", "Enter", "Escape", "Space"];

    nonArrowKeys.forEach((key) => {
      // Create mock event
      const mockEvent = {
        key,
        preventDefault: () => {},
      };

      // Simulate key press
      handler(mockEvent);

      // Verify no messages are sent
      expect(receivedMessages).to.have.lengthOf(
        0,
        `No message should be sent for key ${key}`
      );
    });
  });
});
