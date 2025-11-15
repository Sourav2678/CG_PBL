#include <graphics.h>
#include <iostream>
#include <math.h>
using namespace std;

// 3D Point Structure
struct Point3D {
    float x, y, z;
};

float angleX = 0, angleY = 0, angleZ = 0;  // rotation angles
float zoomLevel = 1.0;  // zoom factor

// Rotate points around X, Y, and Z axes
Point3D rotatePoint(Point3D p) {
    Point3D r = p;
    float radX = angleX * 3.1416 / 180;
    float radY = angleY * 3.1416 / 180;
    float radZ = angleZ * 3.1416 / 180;

    // Rotate around Z
    float tempX = r.x * cos(radZ) - r.y * sin(radZ);
    float tempY = r.x * sin(radZ) + r.y * cos(radZ);
    r.x = tempX;
    r.y = tempY;

    // Rotate around Y
    tempX = r.x * cos(radY) + r.z * sin(radY);
    float tempZ = -r.x * sin(radY) + r.z * cos(radY);
    r.x = tempX;
    r.z = tempZ;

    // Rotate around X
    tempY = r.y * cos(radX) - r.z * sin(radX);
    r.z = r.y * sin(radX) + r.z * cos(radX);
    r.y = tempY;

    return r;
}

// Orthographic projection
void projectOrthographic(Point3D p, int &x, int &y) {
    x = 320 + p.x * zoomLevel;
    y = 240 - p.y * zoomLevel;
}

// Perspective projection
void projectPerspective(Point3D p, int &x, int &y) {
    float d = 200;
    x = 320 + (p.x * d * zoomLevel) / (p.z + d);
    y = 240 - (p.y * d * zoomLevel) / (p.z + d);
}

// Isometric projection
void projectIsometric(Point3D p, int &x, int &y) {
    float cos30 = 0.866;  // cos(30°)
    float sin30 = 0.5;    // sin(30°)
    x = 320 + (p.x - p.y) * cos30 * zoomLevel;
    y = 240 - ((p.x + p.y) * sin30 * zoomLevel + p.z * zoomLevel);
}

// Draw cube or cuboid
void drawBox(Point3D shape[], void (*proj)(Point3D, int&, int&)) {
    int x[8], y[8];
    for (int i = 0; i < 8; i++) {
        Point3D rotated = rotatePoint(shape[i]);
        proj(rotated, x[i], y[i]);
    }

    // Draw edges
    line(x[0], y[0], x[1], y[1]);
    line(x[1], y[1], x[2], y[2]);
    line(x[2], y[2], x[3], y[3]);
    line(x[3], y[3], x[0], y[0]);
    line(x[4], y[4], x[5], y[5]);
    line(x[5], y[5], x[6], y[6]);
    line(x[6], y[6], x[7], y[7]);
    line(x[7], y[7], x[4], y[4]);
    for (int i = 0; i < 4; i++)
        line(x[i], y[i], x[i + 4], y[i + 4]);
}

// Draw pyramid
void drawPyramid(Point3D shape[], void (*proj)(Point3D, int&, int&)) {
    int x[5], y[5];
    for (int i = 0; i < 5; i++) {
        Point3D rotated = rotatePoint(shape[i]);
        proj(rotated, x[i], y[i]);
    }

    // Base square
    line(x[0], y[0], x[1], y[1]);
    line(x[1], y[1], x[2], y[2]);
    line(x[2], y[2], x[3], y[3]);
    line(x[3], y[3], x[0], y[0]);

    // Sides to apex
    for (int i = 0; i < 4; i++)
        line(x[i], y[i], x[4], y[4]);
}

// Draw sphere (simple wireframe)
void drawSphere(void (*proj)(Point3D, int&, int&)) {
    float r = 60;
    // Draw latitude circles
    for (int phi = -90; phi <= 90; phi += 30) {
        int prevX = -1, prevY = -1;
        for (int theta = 0; theta <= 360; theta += 5) {
            Point3D p;
            p.x = r * cos(phi * 3.14 / 180) * cos(theta * 3.14 / 180);
            p.y = r * sin(phi * 3.14 / 180);
            p.z = r * cos(phi * 3.14 / 180) * sin(theta * 3.14 / 180);
            Point3D rotated = rotatePoint(p);
            int x, y;
            proj(rotated, x, y);
            if (prevX != -1) line(prevX, prevY, x, y);
            prevX = x;
            prevY = y;
        }
    }
    // Draw longitude circles
    for (int theta = 0; theta < 360; theta += 30) {
        int prevX = -1, prevY = -1;
        for (int phi = -90; phi <= 90; phi += 5) {
            Point3D p;
            p.x = r * cos(phi * 3.14 / 180) * cos(theta * 3.14 / 180);
            p.y = r * sin(phi * 3.14 / 180);
            p.z = r * cos(phi * 3.14 / 180) * sin(theta * 3.14 / 180);
            Point3D rotated = rotatePoint(p);
            int x, y;
            proj(rotated, x, y);
            if (prevX != -1) line(prevX, prevY, x, y);
            prevX = x;
            prevY = y;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int choice = 1;  // Default to cube
    bool multiMode = false;  // Toggle for multi-object scene

    void (*projection)(Point3D, int&, int&) = projectPerspective;

    // Define shapes
    Point3D cube[8] = {
        {-50, -50, -50}, {50, -50, -50}, {50, 50, -50}, {-50, 50, -50},
        {-50, -50, 50}, {50, -50, 50}, {50, 50, 50}, {-50, 50, 50}
    };

    Point3D cuboid[8] = {
        {-70, -40, -30}, {70, -40, -30}, {70, 40, -30}, {-70, 40, -30},
        {-70, -40, 30}, {70, -40, 30}, {70, 40, 30}, {-70, 40, 30}
    };

    Point3D pyramid[5] = {
        {-50, -50, 50}, {50, -50, 50}, {50, -50, -50}, {-50, -50, -50}, {0, 50, 0}
    };

    while (true) {
        cleardevice();

        // Display instructions and status
        outtextxy(10, 10, (char*)"3D Projection Visualizer");
        outtextxy(10, 30, (char*)"1-4: Shapes | Arrow: Rotate X/Y | A/D: Rotate Z | +/-: Zoom");
        outtextxy(10, 50, (char*)"O: Ortho | P: Persp | I: Isometric | M: Multi-Mode | ESC: Exit");

        char projText[50];
        if (projection == projectOrthographic) sprintf(projText, "Projection: Orthographic");
        else if (projection == projectPerspective) sprintf(projText, "Projection: Perspective");
        else sprintf(projText, "Projection: Isometric");
        outtextxy(10, 70, projText);

        char zoomText[50];
        sprintf(zoomText, "Zoom: %.1f", zoomLevel);
        outtextxy(10, 90, zoomText);

        char modeText[50];
        sprintf(modeText, "Mode: %s", multiMode ? "Multi-Object" : "Single Shape");
        outtextxy(10, 110, modeText);

        char shapeText[50];
        if (choice == 1) sprintf(shapeText, "Shape: Cube");
        else if (choice == 2) sprintf(shapeText, "Shape: Cuboid");
        else if (choice == 3) sprintf(shapeText, "Shape: Pyramid");
        else sprintf(shapeText, "Shape: Sphere");
        outtextxy(10, 130, shapeText);

        // Draw shapes
        if (multiMode) {
            drawBox(cube, projection);
            drawPyramid(pyramid, projection);
        } else {
            if (choice == 1) drawBox(cube, projection);
            else if (choice == 2) drawBox(cuboid, projection);
            else if (choice == 3) drawPyramid(pyramid, projection);
            else if (choice == 4) drawSphere(projection);
        }

        // --- FIXED KEY HANDLING ---
        if (kbhit()) {
            int ch = getch();

            // Handle extended keys (arrow keys)
            if (ch == 0 || ch == 224) {
                ch = getch();
                if (ch == 72) angleX -= 5;  // Up
                else if (ch == 80) angleX += 5;  // Down
                else if (ch == 75) angleY -= 5;  // Left
                else if (ch == 77) angleY += 5;  // Right
            }
            else {
                // Normal keys
                if (ch == 27) break;  // ESC
                else if (ch >= '1' && ch <= '4') choice = ch - '0';
                else if (ch == 'm' || ch == 'M') multiMode = !multiMode;
                else if (ch == 'o' || ch == 'O') projection = projectOrthographic;
                else if (ch == 'p' || ch == 'P') projection = projectPerspective;
                else if (ch == 'i' || ch == 'I') projection = projectIsometric;
                else if (ch == '+') zoomLevel += 0.1;
                else if (ch == '-') zoomLevel -= 0.1;
                else if (ch == 'a' || ch == 'A') angleZ -= 5;
                else if (ch == 'd' || ch == 'D') angleZ += 5;
            }

            if (zoomLevel < 0.1) zoomLevel = 0.1;
        }
        // --- END FIXED SECTION ---

        delay(40);  // ~60 FPS
    }

    closegraph();
    return 0;
}
