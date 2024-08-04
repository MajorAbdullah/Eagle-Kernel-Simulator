#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

struct Process
{
    int process_id;
    int AT;           // Arrival Time
    int BT;           // Burst Time
    int remainingBT;  // Remaining Burst Time for Round-Robin
    int priority;     // Priority
    int page_size;
    int memory_allocated;
    int process_size;
    string state;
    Process *next;
};

class ProcessManager
{
private:
    Process *readyHead;
    Process *runningHead;
    Process *blockedHead;
    int processCounter;
    const int timeQuantum = 10; // Time quantum for Round-Robin
    const int frameSize = 256;  // Frame size for paging
    ofstream logFile;

    // Utility function to delete a process from a list
    void deleteProcess(Process *&head, Process *target)
    {
        if (!head)
            return;
        if (head == target)
        {
            Process *temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Process *prev = head;
        while (prev->next && prev->next != target)
            prev = prev->next;
        if (prev->next)
        {
            Process *temp = prev->next;
            prev->next = temp->next;
            delete temp;
        }
    }

    // Utility function to find a process in a list by ID
    Process *findProcess(Process *head, int pid)
    {
        Process *temp = head;
        while (temp && temp->process_id != pid)
            temp = temp->next;
        return temp;
    }

    // Utility function to move a process from one list to another
    void moveProcess(Process *&from, Process *&to, int pid, const string &newState)
    {
        Process *process = findProcess(from, pid);
        if (process)
        {
            logAction("Process " + to_string(process->process_id) + " moved to " + newState);
            process->state = newState;
            deleteProcess(from, process);
            process->next = to;
            to = process;
        }
    }

    // Utility function to display a process list
    void displayList(Process *head)
    {
        if (!head)
        {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Process ID\tArrival Time\tBurst Time\tRemaining BT\tPriority\tState" << endl;
        while (head)
        {
            cout << head->process_id << "\t\t" << head->AT << "\t\t" << head->BT << "\t\t" << head->remainingBT << "\t\t" << head->priority << "\t\t" << head->state << endl;
            head = head->next;
        }
    }

    // Utility function to log actions
    void logAction(const string &action)
    {
        time_t now = time(0);
        string timestamp = ctime(&now);
        timestamp.pop_back(); // Remove newline character
        logFile << "[" << timestamp << "] " << action << endl;
    }

public:
    ProcessManager() : readyHead(nullptr), runningHead(nullptr), blockedHead(nullptr), processCounter(0)
    {
        logFile.open("process_log.txt", ios::app);
        if (!logFile)
        {
            cerr << "Unable to open log file." << endl;
            exit(1);
        }
        logAction("Process Manager initialized.");
    }

    ~ProcessManager()
    {
        logAction("Process Manager terminated.");
        logFile.close();
    }

    // Public utility functions for input validation
    int getValidatedChoice(int min, int max)
    {
        int choice;
        while (true)
        {
            cout << "Enter your choice (" << min << "-" << max << "): ";
            cin >> choice;
            if (cin.fail() || choice < min || choice > max)
            {
                cin.clear(); // clear input buffer to restore cin to a usable state
                cin.ignore(INT_MAX, '\n'); // ignore last input
                cout << "Invalid choice, please try again." << endl;
            }
            else
            {
                cin.ignore(INT_MAX, '\n'); // clear input buffer
                break;
            }
        }
        return choice;
    }

    int getValidatedProcessID()
    {
        int pid;
        while (true)
        {
            cout << "Enter Process ID: ";
            cin >> pid;
            if (cin.fail() || pid <= 0)
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid Process ID, please try again." << endl;
            }
            else
            {
                cin.ignore(INT_MAX, '\n');
                break;
            }
        }
        return pid;
    }

    // Create a new process
    void createProcess(int AT, int BT, int priority)
    {
        Process *newProcess = new Process{++processCounter, AT, BT, BT, priority, 0, 0, 0, "Ready", nullptr};
        newProcess->next = readyHead;
        readyHead = newProcess;
        logAction("Created Process " + to_string(newProcess->process_id) + " with AT=" + to_string(AT) + ", BT=" + to_string(BT) + ", Priority=" + to_string(priority));
    }

    // Automatically create multiple processes with random values
    void createMultipleProcesses(int numProcesses)
    {
        int AT, BT, priority;
        for (int i = 0; i < numProcesses; i++)
        {
            AT = rand() % 100;
            BT = rand() % 100;
            priority = rand() % 10;
            createProcess(AT, BT, priority);
        }
        logAction("Automatically created " + to_string(numProcesses) + " processes with random values.");
    }

    // Destroy a process
    void destroyProcess(int pid)
    {
        Process *process = findProcess(readyHead, pid);
        if (process)
        {
            deleteProcess(readyHead, process);
            logAction("Destroyed Process " + to_string(pid));
        }
        else
        {
            cout << "Process ID " << pid << " not found." << endl;
        }
    }

    // Change process priority
    void changeProcessPriority(int pid, int newPriority)
    {
        Process *process = findProcess(readyHead, pid);
        if (process)
        {
            process->priority = newPriority;
            logAction("Changed priority of Process " + to_string(pid) + " to " + to_string(newPriority));
            cout << "Priority of process " << pid << " has been changed to " << newPriority << endl;
        }
        else
        {
            cout << "Process ID " << pid << " not found." << endl;
        }
    }

    // Process communication simulation
    void processCommunication(int senderPid, int receiverPid, const string &message)
    {
        Process *sender = findProcess(readyHead, senderPid);
        Process *receiver = findProcess(readyHead, receiverPid);

        if (sender && receiver)
        {
            logAction("Process " + to_string(senderPid) + " communicated with Process " + to_string(receiverPid) + ": " + message);
            cout << "Process " << senderPid << " sent a message to Process " << receiverPid << ": " << message << endl;
        }
        else
        {
            cout << "One or both process IDs not found." << endl;
        }
    }

    // Suspend a process
    void suspendProcess(int pid)
    {
        moveProcess(runningHead, readyHead, pid, "Suspended");
    }

    // Resume a process
    void resumeProcess()
    {
        if (readyHead)
        {
            Process *toResume = readyHead; // Assume the first found process to be resumed
            moveProcess(readyHead, runningHead, toResume->process_id, "Running");
        }
    }

    // Block a process
    void blockProcess(int pid)
    {
        moveProcess(runningHead, blockedHead, pid, "Blocked");
    }

    // Wake up a process
    void wakeupProcess()
    {
        if (blockedHead)
        {
            Process *toWakeup = blockedHead; // Assume the first found process to be woken up
            moveProcess(blockedHead, readyHead, toWakeup->process_id, "Ready");
        }
    }

    // Dispatch a process
    void dispatchProcess(int pid)
    {
        moveProcess(readyHead, runningHead, pid, "Running");
    }

    // First-Come-First-Serve (FCFS) scheduling
    void fcfs()
    {
        if (!readyHead)
            return;
        Process *toRun = readyHead;
        Process *prev = nullptr;
        Process *curr = readyHead;
        while (curr)
        {
            if (curr->AT < toRun->AT || (curr->AT == toRun->AT && curr->process_id < toRun->process_id))
            {
                toRun = curr;
                prev = (prev == nullptr) ? readyHead : prev->next;
            }
            curr = curr->next;
        }
        dispatchProcess(toRun->process_id);
    }

    // Priority Scheduling
    void priorityScheduling()
    {
        if (!readyHead)
            return;
        Process *toRun = readyHead;
        Process *prev = nullptr;
        Process *curr = readyHead;
        while (curr)
        {
            if (curr->priority > toRun->priority || (curr->priority == toRun->priority && curr->AT < toRun->AT))
            {
                toRun = curr;
                prev = (prev == nullptr) ? readyHead : prev->next;
            }
            curr = curr->next;
        }
        dispatchProcess(toRun->process_id);
    }

    // Shortest Job First (SJF) scheduling
    void sjf()
    {
        if (!readyHead)
            return;
        Process *toRun = readyHead;
        Process *prev = nullptr;
        Process *curr = readyHead;
        while (curr)
        {
            if (curr->BT < toRun->BT || (curr->BT == toRun->BT && curr->AT < toRun->AT))
            {
                toRun = curr;
                prev = (prev == nullptr) ? readyHead : prev->next;
            }
            curr = curr->next;
        }
        dispatchProcess(toRun->process_id);
    }

    // Round-Robin (RR) scheduling
    void roundRobin()
    {
        Process *curr = readyHead;
        Process *prev = nullptr;
        while (curr)
        {
            if (curr->remainingBT > timeQuantum)
            {
                curr->remainingBT -= timeQuantum;
                prev = curr;
                curr = curr->next;
            }
            else
            {
                dispatchProcess(curr->process_id);
                curr = prev ? prev->next : readyHead;
            }
        }
    }

    // Multilevel Queue Scheduling
    void multilevelQueueScheduling()
    {
        // High priority queue - Use Priority Scheduling
        Process *highPriorityHead = nullptr;
        // Low priority queue - Use Round-Robin Scheduling
        Process *lowPriorityHead = nullptr;

        // Split ready queue into high and low priority queues
        Process *curr = readyHead;
        while (curr)
        {
            if (curr->priority >= 5) // Arbitrary priority threshold
            {
                Process *next = curr->next;
                curr->next = highPriorityHead;
                highPriorityHead = curr;
                curr = next;
            }
            else
            {
                Process *next = curr->next;
                curr->next = lowPriorityHead;
                lowPriorityHead = curr;
                curr = next;
            }
        }

        // Run Priority Scheduling on high priority queue
        readyHead = highPriorityHead;
        priorityScheduling();

        // Run Round-Robin Scheduling on low priority queue
        readyHead = lowPriorityHead;
        roundRobin();

        // Merge back the queues
        if (!highPriorityHead)
            readyHead = lowPriorityHead;
        else
        {
            Process *tail = highPriorityHead;
            while (tail->next)
                tail = tail->next;
            tail->next = lowPriorityHead;
            readyHead = highPriorityHead;
        }
    }

    // Perform Paging
    void performPaging(int pid)
    {
        Process *process = findProcess(readyHead, pid);
        if (process)
        {
            int numPages = (process->process_size + frameSize - 1) / frameSize;
            cout << "Process " << pid << " requires " << numPages << " pages." << endl;
            logAction("Performed paging for Process " + to_string(pid) + ": " + to_string(numPages) + " pages required.");
        }
        else
        {
            cout << "Process ID " << pid << " not found." << endl;
        }
    }

    // Perform LRU page replacement simulation
    void performLRU(int numFrames, vector<int> pageReferences)
    {
        vector<int> frames;
        vector<pair<int, int>> pageTable; // Stores <page, time> to track usage

        int time = 0;
        for (int page : pageReferences)
        {
            time++;
            bool found = false;

            // Check if page is already in frames
            for (int i = 0; i < frames.size(); i++)
            {
                if (frames[i] == page)
                {
                    pageTable[i].second = time; // Update the time of usage
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                if (frames.size() < numFrames)
                {
                    frames.push_back(page);
                    pageTable.push_back({page, time});
                }
                else
                {
                    // Find the least recently used page
                    int lruIndex = 0;
                    for (int i = 1; i < pageTable.size(); i++)
                    {
                        if (pageTable[i].second < pageTable[lruIndex].second)
                        {
                            lruIndex = i;
                        }
                    }

                    frames[lruIndex] = page;
                    pageTable[lruIndex] = {page, time};
                }

                logAction("Page " + to_string(page) + " added to frames.");
            }
        }

        cout << "Final frame contents: ";
        for (int frame : frames)
            cout << frame << " ";
        cout << endl;
    }

    // Set page size for a process
    void setPageSize(int pid, int pageSize)
    {
        Process *process = findProcess(readyHead, pid);
        if (process)
        {
            process->page_size = pageSize;
            logAction("Page size of process " + to_string(pid) + " set to " + to_string(pageSize));
            cout << "Page size of process " << pid << " has been set to " << pageSize << endl;
        }
        else
        {
            cout << "Process ID " << pid << " not found." << endl;
        }
    }

    // Calculate number of pages required
    void calculatePages(int pid, int memoryAllocated, int processSize)
    {
        Process *process = findProcess(readyHead, pid);
        if (process)
        {
            process->memory_allocated = memoryAllocated;
            process->process_size = processSize;

            int numberOfPages = process->memory_allocated / process->page_size;
            int numberOfFrames = process->process_size / process->page_size;
            int numberOfEntries = numberOfPages * numberOfFrames;

            logAction("Calculated pages for process " + to_string(pid));
            cout << "Memory needed for process " << pid << " is " << memoryAllocated << endl;
            cout << "Number of pages in the process: " << numberOfPages << endl;
            cout << "Number of frames in memory for process " << pid << " : " << numberOfFrames << endl;
            cout << "Number of entries: " << numberOfEntries << endl;
        }
        else
        {
            cout << "Process ID " << pid << " not found." << endl;
        }
    }

    // Display all queues
    void displayAll()
    {
        cout << "Ready Queue:" << endl;
        displayList(readyHead);
        cout << "Running Queue:" << endl;
        displayList(runningHead);
        cout << "Blocked Queue:" << endl;
        displayList(blockedHead);
    }
};

int main()
{
    srand(time(0));
    ProcessManager pm;

    while (true)
    {
        cout << "Main Menu:" << endl;
        cout << "1. Process Management" << endl;
        cout << "2. Memory Management" << endl;
        cout << "3. Automatically Add Processes" << endl;
        cout << "4. Exit" << endl;
        int choice = pm.getValidatedChoice(1, 4);

        switch (choice)
        {
        case 1:
        {
            while (true)
            {
                cout << "Process Management Menu:" << endl;
                cout << "1. Create a process" << endl;
                cout << "2. Destroy a process" << endl;
                cout << "3. Suspend a process" << endl;
                cout << "4. Resume a process" << endl;
                cout << "5. Block a process" << endl;
                cout << "6. Wake up a process" << endl;
                cout << "7. Dispatch a process" << endl;
                cout << "8. Change process priority" << endl;
                cout << "9. Process communication" << endl;
                cout << "10. First-Come-First-Serve (FCFS) Scheduling" << endl;
                cout << "11. Priority Scheduling" << endl;
                cout << "12. Shortest Job First (SJF) Scheduling" << endl;
                cout << "13. Round-Robin (RR) Scheduling" << endl;
                cout << "14. Multilevel Queue Scheduling" << endl;
                cout << "15. Back to Main Menu" << endl;
                int pmChoice = pm.getValidatedChoice(1, 15);

                if (pmChoice == 1)
                {
                    int numProcesses, AT, BT, priority;
                    cout << "Enter number of processes: ";
                    cin >> numProcesses;
                    for (int i = 0; i < numProcesses; i++)
                    {
                        AT = rand() % 100;
                        BT = rand() % 100;
                        priority = rand() % 10;
                        pm.createProcess(AT, BT, priority);
                    }
                    pm.displayAll();
                }
                else if (pmChoice == 2)
                {
                    int pid = pm.getValidatedProcessID();
                    pm.destroyProcess(pid);
                    pm.displayAll();
                }
                else if (pmChoice == 3)
                {
                    int pid = pm.getValidatedProcessID();
                    pm.suspendProcess(pid);
                    pm.displayAll();
                }
                else if (pmChoice == 4)
                {
                    pm.resumeProcess();
                    pm.displayAll();
                }
                else if (pmChoice == 5)
                {
                    int pid = pm.getValidatedProcessID();
                    pm.blockProcess(pid);
                    pm.displayAll();
                }
                else if (pmChoice == 6)
                {
                    pm.wakeupProcess();
                    pm.displayAll();
                }
                else if (pmChoice == 7)
                {
                    int pid = pm.getValidatedProcessID();
                    pm.dispatchProcess(pid);
                    pm.displayAll();
                }
                else if (pmChoice == 8)
                {
                    int pid = pm.getValidatedProcessID();
                    int newPriority;
                    cout << "Enter new priority: ";
                    cin >> newPriority;
                    pm.changeProcessPriority(pid, newPriority);
                    pm.displayAll();
                }
                else if (pmChoice == 9)
                {
                    int senderPid = pm.getValidatedProcessID();
                    int receiverPid = pm.getValidatedProcessID();
                    string message;
                    cout << "Enter message to send: ";
                    cin.ignore(); // To clear the newline left in the input buffer
                    getline(cin, message);
                    pm.processCommunication(senderPid, receiverPid, message);
                    pm.displayAll();
                }
                else if (pmChoice == 10)
                {
                    pm.fcfs();
                    pm.displayAll();
                }
                else if (pmChoice == 11)
                {
                    pm.priorityScheduling();
                    pm.displayAll();
                }
                else if (pmChoice == 12)
                {
                    pm.sjf();
                    pm.displayAll();
                }
                else if (pmChoice == 13)
                {
                    pm.roundRobin();
                    pm.displayAll();
                }
                else if (pmChoice == 14)
                {
                    pm.multilevelQueueScheduling();
                    pm.displayAll();
                }
                else if (pmChoice == 15)
                {
                    break;
                }
            }
            break;
        }
        case 2:
        {
            while (true)
            {
                cout << "Memory Management Menu:" << endl;
                cout << "1. Set Page Size" << endl;
                cout << "2. Calculate Pages" << endl;
                cout << "3. Perform Paging" << endl;
                cout << "4. Perform LRU" << endl;
                cout << "5. Back to Main Menu" << endl;
                int mmChoice = pm.getValidatedChoice(1, 5);

                if (mmChoice == 1)
                {
                    int pid = pm.getValidatedProcessID();
                    int pageSize;
                    cout << "Enter Page Size: ";
                    cin >> pageSize;
                    pm.setPageSize(pid, pageSize);
                }
                else if (mmChoice == 2)
                {
                    int pid = pm.getValidatedProcessID();
                    int memoryAllocated, processSize;
                    cout << "Enter Memory Size: ";
                    cin >> memoryAllocated;
                    cout << "Enter Process Size: ";
                    cin >> processSize;
                    pm.calculatePages(pid, memoryAllocated, processSize);
                }
                else if (mmChoice == 3)
                {
                    int pid = pm.getValidatedProcessID();
                    pm.performPaging(pid);
                }
                else if (mmChoice == 4)
                {
                    int numFrames;
                    int numReferences;
                    vector<int> pageReferences;
                    cout << "Enter number of frames: ";
                    cin >> numFrames;
                    cout << "Enter number of page references: ";
                    cin >> numReferences;
                    pageReferences.resize(numReferences);
                    cout << "Enter page references: ";
                    for (int i = 0; i < numReferences; i++)
                        cin >> pageReferences[i];
                    pm.performLRU(numFrames, pageReferences);
                }
                else if (mmChoice == 5)
                {
                    break;
                }
            }
            break;
        }
        case 3:
        {
            int numProcesses;
            cout << "Enter number of processes to add: ";
            cin >> numProcesses;
            pm.createMultipleProcesses(numProcesses);
            pm.displayAll();
            break;
        }
        case 4:
            cout << "Exit" << endl;
            return 0;
        }
    }
}
