# MiniRT - Ray Tracing Engine

A minimalistic ray tracing engine written in C as part of the 42 School curriculum. MiniRT implements fundamental ray tracing concepts to render 3D scenes with basic geometric primitives and lighting.

## 🎯 Project Overview

MiniRT is designed to introduce students to computer graphics through ray tracing - a rendering technique that simulates the path of light to create photorealistic images. The project focuses on understanding mathematical concepts behind 3D graphics while implementing efficient algorithms in C.

## ✨ Features

### Supported Objects
- **Spheres** - Perfect spheres with customizable radius and position
- **Planes** - Infinite planes defined by point and normal vector
- **Cylinders** - Finite cylinders with diameter, height, and orientation

### Lighting System
- **Ambient lighting** - Global illumination for scene ambiance
- **Diffuse lighting** - Lambertian reflection for realistic surface shading
- **Point lights** - Directional light sources with customizable intensity

### Interactive Controls
- **Real-time object manipulation** - Select and modify objects during runtime
- **Translation and rotation** - Move and rotate objects with keyboard controls
- **Object scaling** - Resize objects interactively
- **Tab navigation** - Cycle through scene objects

### Core Features
- **Shadows** - Hard shadows for realistic depth perception
- **Color management** - RGB color system with proper blending
- **Scene parsing** - Custom file format for scene description
- **Real-time rendering** - Interactive scene exploration


## 🎮 Controls

The program provides interactive controls for real-time scene manipulation:

```
==== miniRT Controls ====
ESC         : Exit program
TAB         : Select next object
R           : Toggle between rotation and translation mode
Arrow keys  : Move or rotate selected object
+ / -       : Resize selected object
=====================
```

## 🚀 Getting Started

### Prerequisites
- GCC compiler
- Make
- MinilibX (MLX) graphics library
- Linux/macOS environment

### Installation

```bash
# Compile the project
make

# Run with a scene file
./miniRT scenes/basic.rt
```

### Basic Usage

```bash
# Example output when running
sh-5.2$ ./miniRT scenes/basic.rt
Scene parsed. Number of objects: 3
==== miniRT Controls ====
ESC         : Exit program
TAB         : Select next object
R           : Toggle between rotation and translation mode
Arrow keys  : Move or rotate selected object
+ / -       : Resize selected object
=====================
```

## 🎨 Example Scenes

The project supports scene files with various geometric objects and lighting configurations.

## 🔧 Compilation

```bash
# Standard compilation
make

# Clean build files
make clean

# Remove all generated files
make fclean

# Recompile everything
make re
```

## 📊 Performance

The ray tracer provides real-time rendering capabilities with interactive object manipulation. Performance depends on scene complexity and the number of objects being rendered.

## 🧪 Testing

Test the program with various scene files to explore different geometric configurations and lighting setups.

## 📚 Learning Resources

### Mathematical Concepts
- Linear algebra and vector mathematics
- Analytical geometry
- Ray-object intersection algorithms
- Basic lighting models

## 🙏 Acknowledgments

- **42 School** - For the comprehensive computer graphics curriculum
- **MinilibX team** - For the graphics library
- **Ray tracing community** - For extensive documentation and resources
