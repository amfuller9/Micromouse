#include <Stepper.h>
#define MAZE_SIZE 9  // Define maze dimensions
class Cell {
  public:
    bool northWall, eastWall, southWall, westWall;
    bool visited;

    // Constructor: Initializes a cell with all walls present
    Cell() {
      northWall = eastWall = southWall = westWall = true;
      visited = false;
    }

    // Function to remove a wall
    void removeWall(char direction) {
      switch (direction) {
        case 'N': northWall = false; break;
        case 'E': eastWall = false; break;
        case 'S': southWall = false; break;
        case 'W': westWall = false; break;
      }
    }

    // Function to mark as visited
    void markVisited() {
      visited = true;
    }

    // Function to get a simple character representation
    char getDisplayChar() {
      return visited ? '.' : '?'; // '?' = unexplored, '.' = explored
    }
};

class Maze {
  private:
    Cell grid[MAZE_SIZE][MAZE_SIZE];
    int robotX, robotY;  // Robot's current position

  public:
    // Constructor
    Maze() {
      robotX = 0;
      robotY = 0;
      grid[robotX][robotY].markVisited();  // Mark start as visited
    }

    // Function to remove walls between two cells
    void removeWallBetween(int x1, int y1, int x2, int y2) {
      if (x1 == x2) {  // Same row (moving left or right)
        if (y1 < y2) {  // Moving right
          grid[x1][y1].removeWall('E');
          grid[x2][y2].removeWall('W');
        } else {  // Moving left
          grid[x1][y1].removeWall('W');
          grid[x2][y2].removeWall('E');
        }
      } else if (y1 == y2) {  // Same column (moving up or down)
        if (x1 < x2) {  // Moving down
          grid[x1][y1].removeWall('S');
          grid[x2][y2].removeWall('N');
        } else {  // Moving up
          grid[x1][y1].removeWall('N');
          grid[x2][y2].removeWall('S');
        }
      }
    }

    // Function to move the robot
    void moveRobot(int newX, int newY) {
      if (newX >= 0 && newX < MAZE_SIZE && newY >= 0 && newY < MAZE_SIZE) {
        robotX = newX;
        robotY = newY;
        grid[robotX][robotY].markVisited();
      }
    }

    // Function to display the maze in the Serial Monitor
    void displayMaze() {
      for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
          Serial.print(grid[i][j].getDisplayChar());
          Serial.print(" ");
        }
        Serial.println();
      }
      Serial.println();
    }
};

// Define the number of steps per revolution for the 28BYJ-48 motor
const int stepsPerRevolution = 2038;  // Full revolution for the 28BYJ-48 motor in full-step mode

// Define the motor connections
const int motorPin1 = 8;  
const int motorPin2 = 9;  
const int motorPin3 = 10; 
const int motorPin4 = 11; 

// Create a Stepper object
Stepper myStepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4);

void setup() {
  // Set the motor speed (RPM)
  myStepper.setSpeed(10);  // Set a lower speed to reduce RPM (adjust to your needs)
}

void loop() {
  // Rotate the motor one direction
  myStepper.step(stepsPerRevolution);  // Rotate 1 full revolution
}
