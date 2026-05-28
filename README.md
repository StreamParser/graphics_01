# graphics_01

A C++ application demonstrating very basic usage of the SFML 3.1.0 library for graphics rendering. 
This project serves as a simple example of how to set up and use SFML for creating a window and drawing shapes.
It currently only supports a fixed screen resolution of 3840x2160 (4K).
Currently, the only configuration supported by the solution is for an x64 Windows 10 environment.

## Demonstrates the Following SFML Features

- 🖼️ Create a window,
- 🔹 Draw lines
- 🎨 Set colors
- 🖌 Render the graphic objects
- 🕹️ Handle user keyboard input events

## Dependencies

- **SFML**: Simple and Fast Multimedia Library for graphics rendering

## Development

### Project Structure

```
.
└── graphics_01/
	│
    ├── dependencies/
	│	│
    │   ├── Debug/
    │   │   ├── sfml-audio-d-3.dll		# Debug version of the SFML audio library
    │   │   ├── sfml-graphics-d-3.dll	# Debug version of the SFML graphics library
    │   │   ├── sfml-network-d-3.dll	# Debug version of the SFML network library
    │   │   ├── sfml-system-d-3.dll		# Debug version of the SFML system library
	│	│	└── sfml-window-d-3.dll		# Debug version of the SFML window library
	│	│
	│	└── Release/
    │       ├── sfml-audio-3.dll		# Release version of the SFML audio library
    │       ├── sfml-graphics-3.dll		# Release version of the SFML graphics library
    │       ├── sfml-network-3.dll		# Release version of the SFML network library
    │       ├── sfml-system-3.dll		# Release version of the SFML system library
	│		└── sfml-window-3.dll		# Release version of the SFML window library
	│   
    ├── .gitignore						# Git ignore file
	├── graphics_01.rc					# Resource script file
	├── graphics_01.slnxml				# Visual Studio solution file
	├── graphics_01.vcxproj				# Visual Studio project file
	├── graphics_01.vcxproj.filters		# Visual Studio project filters file
    ├── main.cpp						# Main entry point
	├── README.md						# This file
	└── resources.h						# Header file for resource definitions

```
