## DSA-Queue-Simulator

It is a project designed to model a traffic signal management system using queue-based data structures and algorithms for a four-way intersection ,developed as a part of Date Structure and Algorithms (COMP202) course
![traffic_simulation](https://github.com/user-attachments/assets/f9b57824-2b22-4678-b19e-02c233a06d7b)


## 📘 Project Overview

Vehicle flow at the four-way intersection is handled using queue-based data structures. Efficient traffic control is achieved by dynamically modifying signal timings according to queue occupancy and vehicle turning behavior.

## ✨ Key Features

- **Queue-Based Traffic Handling**
Each lane at the intersection uses a FIFO (First-In-First-Out) queue to ensure vehicles are processed in an orderly and fair manner.

- **Left-Turn Support**
Around 15% of the vehicles are designed to take left turns, allowing realistic and smooth turning behavior at the intersection.

- **Smart Traffic Signals**
The traffic lights work intelligently—vehicles making left turns are allowed to move even during a red signal, while vehicles going straight must wait.

- **Real-Time Visual Simulation**
The system uses SDL2 graphics to display vehicles in soft pastel colors moving over a green background, making the simulation visually clear and appealing.

- **Collision Prevention**
To ensure safety, the system maintains a minimum distance of 80 pixels between consecutive vehicles in the same lane.

- **High Performance**
The simulation runs smoothly at 60 frames per second (FPS), providing a seamless real-time experience.


## 🧱 Data Structures

|🗂️**Structure** |🔧**Implementation** |🎯**Purpose** |
|-----------|----------------|---------|
| Queue | Array-based | Stores vehicles in each lane |
| Priority Queue | Modified queue | Handles high-priority or congested lanes |


## 🏗️System Architecture
- Traffic Management Rules
- Traffic lights switch every 5 seconds between North–South and East–West
- Left-turn vehicles are allowed to move on red signals
- Straight-moving vehicles must stop at red lights
- FIFO order is followed in every lane
- A minimum safety gap of 80 pixels is enforced


## 🧩 Core Components
**main.c**
Initializes SDL, starts the program, and runs the main event loop.
**traffic_simulation.c**
Handles queue operations, vehicle logic, collision checks, and rendering.
**traffic_simulation.h**
Contains data structures, constants, and function declarations

## ⚙️ Algorithm Design

### 🔁 Main Simulation Flow
- Initialize SDL and create four lane queues
- Generate a vehicle every 2 seconds
- Assign direction with a 15% chance of left turn
- For each lane:
    Check distance from the vehicle ahead
    Check traffic signal status
    Allow left-turn vehicles to move on red
    Perform turning at the intersection center
    Move vehicle forward
    Remove vehicle once it leaves the screen
- Update traffic signals every 5 seconds
- Render roads, signals, and vehicles
- Repeat at 60 FPS
- 
## ⏳ Time Complexity Analysis
| 🔍**Operation** |⏱️**Complexity** | 📝**Description** |
|-----------|-----------|-------------|
| Enqueue/Dequeue | O(1) | Fast queue operations |
| Vehicle Update | O(n) | Update all active vehicles |
| Collision Check | O(n) | Check same lane |
| Overall | O(n) | n = number of vehicles |

## 🚀 Installation and Setup

### Prerequisites
- C++ Compiler (GCC or MinGW)
- SDL2 library
- Git (optional)

### Installation Steps
**Windows (MSYS2):**
```bash
pacman -S mingw-w64-x86_64-SDL2
```

**Windows (Manual):**
- Download SDL2 from [https://www.libsdl.org/download-2.0.php](https://www.libsdl.org/download-2.0.php)

---

### Building the Project

```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/DSA-Queue-Simulator.git
cd DSA-Queue-Simulator

# Compile the generator and Compile the simulator
	gcc -o bin/generator src/generator.c src/traffic_simulation.c -lSDL2 -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2

  gcc main.c generator.c traffic_simulation.c -o main.exe -lmingw32 -lSDL2main -lSDL2

#Run the program
./bin/main.exe
