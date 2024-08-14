## Scheduler

This repository contains an implementation of various scheduling algorithms as part of a system programming course at the Technical University of Berlin. The project involves creating a queue for job management and implementing multiple scheduling algorithms, both preemptive and non-preemptive.

### Table of Contents

- [Project Description](#project-description)
- [Installation](#installation)
- [Makefile Usage](#makefile-usage)
- [Usage](#usage)
- [Scheduling Algorithms](#scheduling-algorithms)
- [Memory Management](#memory-management)
- [Project Structure](#project-structure)

### Project Description

The Scheduler project is designed to simulate different CPU scheduling algorithms. It includes the implementation of a job queue and several scheduling techniques, such as First-Come-First-Serve (FCFS), Last-Come-First-Serve (LCFS), Highest Response Ratio Next (HRRN), Round Robin (RR), Multilevel Feedback Queue (MLF), Priority Preemptive (PRIO-P), and Shortest Remaining Time Next Preemptive (SRTN-P).

### Installation

To set up the project on your local machine, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/antonhtmnn/Scheduler.git
    ```
2. Navigate to the `Scheduler` directory:
    ```bash
    cd Scheduler/
    ```
3. Compile the code using the provided Makefile:
    ```bash
    make
    ```

### Makefile Usage

The provided Makefile automates the build and testing process. It uses the clang C-compiler. If you do not have clang installed, you can install it with:
```bash
sudo pacman -S clang
```
    
#### Make targets

- **`make build`** or **`make all`** or just **`make`**: Compiles all `.c` files. No executable is created at this stage.
- **`make all_tests`**: Builds and runs all tests.
- **`make list_tests`**: Lists all available tests.
- **`make test_*`**: Runs only the specified test. The target name is the same as the test file name (without `.c`). Example: `make test_fcfs_simple`
- **`make clean`**: Cleans up the build directory.

### Usage

To run the scheduler with different algorithms, use the compiled binaries from the `src` directory. Each scheduling algorithm can be tested with various job queues.

### Scheduling Algorithms

The project implements the following scheduling algorithms:

1. **First-Come-First-Serve (FCFS):** Jobs are processed in the order they arrive, without preemption.
2. **Last-Come-First-Serve (LCFS):** The most recently added job is processed first.
3. **Highest Response Ratio Next (HRRN):** Jobs are scheduled based on the highest response ratio.
4. **Round Robin (RR):** Jobs are processed in a circular order with a fixed time quantum.
5. **Multilevel Feedback Queue (MLF):** This algorithm uses four levels, with each level having a time quantum of \( \tau = 3^i \), where \( i \) is the level index. The last level operates as FCFS.
6. **Priority Preemptive (PRIO-P):** Jobs are scheduled based on priority, with higher priority jobs preempting lower priority ones.
7. **Shortest Remaining Time Next Preemptive (SRTN-P):** Jobs with the shortest remaining time are processed first, with preemption.

### Memory Management

To ensure efficient memory management and avoid memory leaks, the project can be tested using the `valgrind` tool. It is important to check that all allocated memory is properly freed to prevent memory leaks.

Example usage with `valgrind`:
```bash
valgrind --leak-check=full ./scheduler_binary
```

### Project Structure
The project is structured as follows:

```
Scheduler/
├── lib/
│   ├── scheduler.h   # Header file for the scheduler
│   ├── queue.h       # Header file for the job queue
│   ├── ...
├── src/
│   ├── scheduler.c   # Implementation of the scheduler
│   ├── queue.c       # Implementation of the job queue
│   ├── ...
├── tests/
│   ├── ...
├── Makefile          # Makefile for building the project
└── README.md
```
