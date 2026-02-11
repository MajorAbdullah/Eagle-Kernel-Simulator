# Eagle Kernel Simulator
### An interactive OS kernel simulator for process and memory management

Eagle Kernel Simulator is a C++ console application that simulates core operating system functionalities including process lifecycle management, CPU scheduling algorithms, and memory management with paging and page replacement. It provides a menu-driven interface for hands-on exploration of OS concepts.

---

## Features

- **Process Lifecycle Management** -- Create, destroy, suspend, resume, block, wake up, and dispatch processes through ready, running, and blocked queues
- **Multiple Scheduling Algorithms**
  - First-Come-First-Serve (FCFS)
  - Priority Scheduling
  - Shortest Job First (SJF)
  - Round-Robin (RR) with configurable time quantum
  - Multilevel Queue Scheduling (splits processes by priority threshold into separate queues)
- **Memory Management**
  - Configurable page size per process
  - Page count and frame calculation
  - Paging simulation with frame allocation
  - Least Recently Used (LRU) page replacement algorithm
- **Inter-Process Communication** -- Simulated message passing between processes
- **Dynamic Priority Management** -- Change process priorities at runtime
- **Automatic Process Generation** -- Bulk-create processes with randomized arrival times, burst times, and priorities
- **Action Logging** -- All operations are timestamped and logged to `process_log.txt` for auditing and debugging
- **Input Validation** -- Robust menu-driven interface with validated user input

---

## Tech Stack

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![GCC](https://img.shields.io/badge/GCC-A42E2B?style=for-the-badge&logo=gnu&logoColor=white)

---

## Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or later (GCC, Clang, or MSVC)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/MajorAbdullah/Eagle-Kernel-Simulator.git
   ```
2. Navigate to the project directory:
   ```bash
   cd Eagle-Kernel-Simulator
   ```
3. Compile the source code:
   ```bash
   g++ -o eagle_os Eagle_OS.cpp -std=c++11
   ```
4. Run the executable:
   ```bash
   ./eagle_os
   ```

---

## Usage

The application presents a hierarchical menu system:

### Main Menu

| Option | Description |
|--------|-------------|
| 1 | Process Management -- access scheduling, lifecycle, and communication operations |
| 2 | Memory Management -- set page sizes, calculate pages, perform paging, simulate LRU |
| 3 | Automatically Add Processes -- bulk-create processes with random attributes |
| 4 | Exit |

### Process Management Submenu

Create processes manually or automatically, then apply scheduling algorithms (FCFS, Priority, SJF, Round-Robin, Multilevel Queue). Manage process states by suspending, blocking, resuming, or dispatching individual processes. View the ready, running, and blocked queues after each operation.

### Memory Management Submenu

Set page sizes for individual processes, calculate the number of pages and frames required for a given memory allocation, perform paging simulations, and run LRU page replacement with custom frame counts and page reference strings.

---

## Project Structure

```
Eagle-Kernel-Simulator/
|-- Eagle_OS.cpp       # Complete simulator source (ProcessManager class, scheduling, memory management, main loop)
|-- .gitignore         # Git ignore rules
|-- LICENSE            # BSD 3-Clause License
|-- README.md          # Project documentation
```

---

## Contributing

Contributions are welcome. Please fork this repository, create a feature branch, and submit a pull request for review.

---

## License

This project is licensed under the **BSD 3-Clause License**. See the [LICENSE](LICENSE) file for details.

---

## Contact

- **Email:** sa.abdullahshah.2001@gmail.com
- **LinkedIn:** [Syed Abdullah Shah](https://www.linkedin.com/in/syed-abdullah-shah-4018a5176)
