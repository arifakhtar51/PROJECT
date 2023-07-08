#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ncurses.h>

// ... Graph and Dijkstra's algorithm implementation ...

// Function to initialize the GUI
void initializeGUI() {
    initscr(); // Initialize ncurses
    cbreak(); // Disable line buffering
    noecho(); // Disable echoing of input characters
    keypad(stdscr, TRUE); // Enable keyboard input
}

// Function to clean up and exit the GUI
void exitGUI() {
    endwin(); // Terminate ncurses
}

// Function to display a message in the GUI
void showMessage(const char* message) {
    clear(); // Clear the screen
    mvprintw(LINES / 2, (COLS - strlen(message)) / 2, message); // Display the message at the center of the screen
    refresh(); // Refresh the screen
    getch(); // Wait for user input
}

// Function to get user input in the GUI
int getUserInput(const char* message) {
    char input[100];
    clear();
    mvprintw(LINES / 2, (COLS - strlen(message)) / 2, message);
    mvprintw(LINES / 2 + 2, (COLS - 10) / 2, "Enter: ");
    echo(); // Enable echoing of input characters
    getstr(input); // Get user input as a string
    noecho(); // Disable echoing of input characters again
    return atoi(input); // Convert the input string to an integer
}

// Function to display the shortest path result in the GUI
void displayShortestPath(int source, int destination, int* parent, int* distance) {
    clear();
    mvprintw(0, (COLS - 18) / 2, "Shortest Path Result");
    mvprintw(2, 2, "Source: %d", source);
    mvprintw(3, 2, "Destination: %d", destination);
    mvprintw(5, 2, "Shortest Path: ");
    mvprintw(7, 2, "Distance: %d", distance[destination]);
    mvprintw(9, 2, "Path: ");
    int vertex = destination;
    int path[100]; // Assuming a maximum path length of 100
    int pathLength = 0;
    while (vertex != -1) {
        path[pathLength++] = vertex;
        vertex = parent[vertex];
    }
    for (int i = pathLength - 1, j = 0; i >= 0; i--, j++) {
        mvprintw(9, 8 + j * 3, "%d", path[i]);
    }
    mvprintw(LINES - 1, 2, "Press any key to continue...");
    refresh();
    getch();
}

// Main function
int main() {
    // Initialize the GUI
    initializeGUI();

    // ... Code for graph initialization ...

    // Get source and destination from the user
    int source = getUserInput("Enter the source vertex: ");
    int destination = getUserInput("Enter the destination vertex: ");

    // Run Dijkstra's algorithm
    int* parent = NULL; // Initialize parent array
    int* distance = NULL; // Initialize distance array
    dijkstra(graph, source, destination, &parent, &distance);

    // Display the shortest path result
    displayShortestPath(source, destination, parent, distance);

    // Clean up and exit the GUI
    free(parent);
    free(distance);
    exitGUI();

    return 0;
}
