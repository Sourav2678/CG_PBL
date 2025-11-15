📌 3D Projection Visualizer (C++ & graphics.h)

An interactive 3D Projection Visualizer built using C++ and the classic graphics.h (BGI / WinBGIm) graphics library.
This tool helps users understand how 3D objects are projected onto a 2D screen through different projection methods—Orthographic, Perspective, and Isometric.

The project includes real-time rotation, zooming, object switching, and multi-object visualization, making it ideal for computer graphics learning and academic demonstrations.

🌟 Features
🔹 Multiple 3D Objects

Cube

Cuboid

Pyramid

Sphere (wireframe)

🔹 Projection Modes

Orthographic Projection

Perspective Projection

Isometric Projection

🔹 Interactive Controls
Action	Keys
Rotate X-axis	↑ / ↓
Rotate Y-axis	← / →
Rotate Z-axis	A / D
Zoom In / Out	+ / –
Switch Projections	O (Ortho), P (Persp), I (Iso)
Switch Objects	1, 2, 3, 4
Multi-Object Mode	M
Exit	ESC
🔹 Smooth Real-Time Rendering

~60 FPS redraw loop

Dynamic rotation & scaling

Low flickering using optimized redraw

📐 How It Works
✔ 3D Transformations

Rotation is computed using standard trigonometric transformation matrices:

Rotation about X-axis

Rotation about Y-axis

Rotation about Z-axis

Zooming is handled via a uniform scale factor.

✔ Projection Models

Each projection uses a different mapping from 3D → 2D:

Orthographic: Ignores depth

Perspective: Farther objects appear smaller

Isometric: All axes equally foreshortened

✔ Rendering

Objects are drawn using:

line() for edges

Parametric equations for sphere generation

trigonometric functions for coordinate transformation

🖥 System Requirements
Hardware

CPU: Intel i3 or above

RAM: 2 GB minimum

Display: 1024×768 or higher

Keyboard: Required for controls

Software

Windows 7/10/11

Turbo C++ or Code::Blocks/MinGW with WinBGIm

C++ compiler supporting <graphics.h>

<math.h> for trigonometric functions

📦 Installation & Setup
✔ Using Code::Blocks + WinBGIm

Install Code::Blocks (MinGW)

Download WinBGIm graphics.h

Add these to your MinGW include/lib folders:

graphics.h

libbgi.a

Link the required libraries in Build Options → Linker:

-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

✔ Using Turbo C++

Just place the graphics.h and BGI folder inside the include path.

📂 Project Structure
/3D-Projection-Visualizer
│── README.md
│── main.cpp
│── images/  (optional screenshots)
│── resources/ (BGI/WinBGIm files)

🧪 Output Samples

✔ Cube – Orthographic

✔ Cube – Perspective

✔ Pyramid – Isometric

✔ Sphere Wireframe

✔ Multi-Object Mode

(You can add screenshots here later.)

🏁 Result

The project successfully demonstrates:

3D → 2D projection concepts

Real-time object transformation

Mathematics of rotation & projection

Interactive computer graphics programming

It serves as an excellent learning tool for understanding the Computer Graphics pipeline and can be expanded into a more advanced OpenGL-based visualizer.

📚 References

Hearn & Baker — Computer Graphics

Foley et al. — Computer Graphics: Principles & Practice

BGI & WinBGIm Documentation

GeeksforGeeks (3D Transformations, Projection Types)

TutorialsPoint — Computer Graphics Basics
