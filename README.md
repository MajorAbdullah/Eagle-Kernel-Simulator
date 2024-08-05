# Process Manager and Memory Management Simulation

## Overview
The Process Manager and Memory Management Simulation is a C++ application designed to simulate various aspects of process management and memory management in an operating system. This system allows you to create, manage, and schedule processes, as well as handle memory management operations like paging and Least Recently Used (LRU) page replacement.

## Features
1. **Process Management**: Create, destroy, suspend, resume, block, wake up, and dispatch processes.
2. **Scheduling Algorithms**:
    - First-Come-First-Serve (FCFS)
    - Priority Scheduling
    - Shortest Job First (SJF)
    - Round-Robin (RR)
    - Multilevel Queue Scheduling
3. **Memory Management**:
    - Set page size for processes
    - Calculate the number of pages required
    - Perform paging for processes
    - Simulate Least Recently Used (LRU) page replacement
4. **Process Communication**: Simulate communication between processes.
5. **Logging**: Actions performed during the simulation are logged to a file (`process_log.txt`) for tracking and debugging purposes.

## Requirements
- C++ Compiler (e.g., GCC, MSVC)
- CMake (for building the project)
- Google Test (for unit testing)

## How to Run
1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/process-manager-simulation.git
    ```
2. **Navigate to the project directory**:
    ```bash
    cd process-manager-simulation
    ```
3. **Build the project**:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
4. **Run the executable**:
    ```bash
    ./process_manager
    ```

## Usage
Upon running the program, you will be presented with a menu to choose from various options:

### Main Menu:
1. **Process Management**: Manage processes using various operations and scheduling algorithms.
2. **Memory Management**: Perform memory management operations like paging and LRU.
3. **Automatically Add Processes**: Automatically create processes with random values.
4. **Exit**: Exit the program.

### Process Management Menu:
- **Create a Process**: Manually create processes by specifying the arrival time, burst time, and priority.
- **Destroy a Process**: Remove a process from the system.
- **Suspend a Process**: Suspend a running process and move it back to the ready queue.
- **Resume a Process**: Resume a suspended process and move it to the running state.
- **Block a Process**: Block a running process and move it to the blocked queue.
- **Wake Up a Process**: Wake up a blocked process and move it to the ready queue.
- **Dispatch a Process**: Move a ready process to the running state.
- **Change Process Priority**: Change the priority of a process.
- **Process Communication**: Simulate communication between processes.
- **Scheduling Algorithms**: Choose and execute different scheduling algorithms.

### Memory Management Menu:
- **Set Page Size**: Set the page size for a specific process.
- **Calculate Pages**: Calculate the number of pages required based on memory allocation and process size.
- **Perform Paging**: Perform paging for a specific process.
- **Perform LRU**: Simulate LRU page replacement.

## Testing
Unit tests are provided to verify the correctness of the major functionalities. The tests are written using Google Test.

### Running Tests
1. **Build and run the tests**:
    ```bash
    make process_manager_test
    ./process_manager_test
    ```
    This will run all the unit tests and display the results.

## Contributing
Contributions are welcome! If you'd like to contribute, please follow these steps:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit them (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

## License
This project is licensed under the BSD 3-Clause License. 
This code is protected under an "All Rights Reserved" license. You must obtain explicit permission from the copyright holder before using, distributing, or modifying this work.


## Contact
For any queries or suggestions, feel free to reach out:
- **Email:** sa.abdullahshah.2001@gmail.com
- **LinkedIn:** [Syed Abdullah Shah](https://www.linkedin.com/in/syed-abdullah-shah-4018a5176) 
