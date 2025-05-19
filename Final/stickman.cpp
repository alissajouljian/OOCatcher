#include <GLFW/glfw3.h>
#include <cmath>

// Window size
const int windowWidth = 800;
const int windowHeight = 600;

int radius = 10;     // Head radius
float x = 50;        // Stickman X position
int midy;            // Ground Y position
int y;               // Head Y position (fixed relative to midy)

int frame = 0;       // Frame counter for animation timing
const int totalFrames = 5; // 5 pose images

// Draw circle function using GL_LINE_LOOP
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159f / 180.0f;
        glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta));
    }
    glEnd();
}

// Draw line between two points
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// Draw stickman for a given pose (1 to 5) exactly as in your Turbo C++ code
void drawStickmanPose(int pose) {
    // Draw ground line
    drawLine(0, midy, windowWidth, midy);

    // Head
    drawCircle(x, y, radius);

    // Body line
    drawLine(x, y + radius, x, y + radius + 50);

    // Legs and arms depending on pose
    switch (pose) {
        case 1:
            // Legs
            drawLine(x, y + radius + 50, x - 10, midy);
            drawLine(x, y + radius + 50, x + 10, midy - 30);
            drawLine(x + 10, midy - 30, x + 10, midy);

            // Hands
            drawLine(x, y + radius + 10, x - 15, y + radius + 30);
            drawLine(x - 15, y + radius + 30, x + 15, y + radius + 40);
            break;

        case 2:
            // Legs
            drawLine(x, y + radius + 50, x - 15, midy);
            drawLine(x, y + radius + 50, x + 10, midy - 30);
            drawLine(x + 10, midy - 30, x + 10, midy);

            // Hands
            drawLine(x, y + radius + 5, x - 10, y + radius + 20);
            drawLine(x - 10, y + radius + 20, x - 10, y + radius + 45);
            drawLine(x, y + radius + 5, x + 5, y + radius + 25);
            drawLine(x + 5, y + radius + 25, x + 15, y + radius + 45);
            break;

        case 3:
            // Legs
            drawLine(x, y + radius + 50, x - 20, midy);
            drawLine(x, y + radius + 50, x + 20, midy);

            // Hands
            drawLine(x, y + radius + 5, x - 20, y + radius + 20);
            drawLine(x - 20, y + radius + 20, x - 20, y + radius + 30);
            drawLine(x, y + radius + 5, x + 20, y + radius + 25);
            drawLine(x + 20, y + radius + 25, x + 30, y + radius + 30);
            break;

        case 4:
            // Legs
            drawLine(x, y + radius + 50, x - 8, midy - 30);
            drawLine(x - 8, midy - 30, x - 25, midy);
            drawLine(x, y + radius + 50, x + 10, midy - 30);
            drawLine(x + 10, midy - 30, x + 12, midy);

            // Hands
            drawLine(x, y + radius + 5, x - 10, y + radius + 10);
            drawLine(x - 10, y + radius + 10, x - 10, y + radius + 30);
            drawLine(x, y + radius + 5, x + 15, y + radius + 20);
            drawLine(x + 15, y + radius + 20, x + 30, y + radius + 20);
            break;

        case 5:
            // Legs
            drawLine(x, y + radius + 50, x + 3, midy);
            drawLine(x, y + radius + 50, x + 8, midy - 30);
            drawLine(x + 8, midy - 30, x - 20, midy);

            // Hands
            drawLine(x, y + radius + 5, x - 15, y + radius + 10);
            drawLine(x - 15, y + radius + 10, x - 8, y + radius + 25);
            drawLine(x, y + radius + 5, x + 15, y + radius + 20);
            drawLine(x + 15, y + radius + 20, x + 30, y + radius + 20);
            break;
    }
}

void display(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 0);

    // Calculate which pose to draw based on frame
    int pose = (frame / 20) % totalFrames + 1;  // Change pose every 20 frames

    drawStickmanPose(pose);

    glfwSwapBuffers(window);
}

void updateLogic() {
    frame++;
    x += 1.5f;  // Move stickman forward smoothly

    if (x > windowWidth + 50) {
        x = -50; // Reset to left side when offscreen right
    }
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Stickman Walk", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Set orthographic projection matching window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1, 1, 1, 1);

    midy = windowHeight / 2;
    y = midy - 100;

    while (!glfwWindowShouldClose(window)) {
        updateLogic();
        display(window);

        glfwPollEvents();
        // Frame delay ~33ms (~30 FPS)
        glfwWaitEventsTimeout(0.033);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
