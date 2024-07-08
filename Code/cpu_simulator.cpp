#include <iostream>
#include <vector>
#include <cstring> // For memcpy function

using namespace std;

// Declare external assembly functions
extern "C" {
    extern void load(unsigned char address, unsigned char reg_index); // External LOAD function
    extern void store(unsigned char address, unsigned char reg_index); // External STORE function
    extern void add(unsigned char reg_index1, unsigned char reg_index2); // External ADD function
    extern void sub(unsigned char reg_index1, unsigned char reg_index2); // External SUB function

    unsigned char memory[256]; // Memory array to simulate CPU memory (256 bytes)
    int pc = 0; // Program counter to track the current instruction index
}

// Function to load a program into simulated memory
void load_program(const vector<unsigned char>& program) {
    memcpy(memory, program.data(), program.size()); // Copy program instructions into memory
}

// Function to execute a single instruction based on opcode
void execute_instruction(const unsigned char* instruction) {
    switch (instruction[0]) {
        case 0x01: // LOAD instruction
            // Print operation details
            cout << "PC: " << pc << " - Executing LOAD instruction: Load value from memory address " 
                 << static_cast<int>(instruction[2]) << " into register " << static_cast<int>(instruction[1]) << endl;
            load(instruction[2], instruction[1]); // Call assembly function for LOAD
            break;
        case 0x02: // STORE instruction
            // Print operation details
            cout << "PC: " << pc << " - Executing STORE instruction: Store value from register " 
                 << static_cast<int>(instruction[1]) << " into memory address " << static_cast<int>(instruction[2]) << endl;
            store(instruction[2], instruction[1]); // Call assembly function for STORE
            break;
        case 0x03: // ADD instruction
            // Print operation details
            cout << "PC: " << pc << " - Executing ADD instruction: Add values of registers " 
                 << static_cast<int>(instruction[1]) << " and " << static_cast<int>(instruction[2]) << endl;
            add(instruction[1], instruction[2]); // Call assembly function for ADD
            break;
        case 0x04: // SUB instruction
            // Print operation details
            cout << "PC: " << pc << " - Executing SUB instruction: Subtract value of register " 
                 << static_cast<int>(instruction[2]) << " from register " << static_cast<int>(instruction[1]) << endl;
            sub(instruction[1], instruction[2]); // Call assembly function for SUB
            break;
        default: // Unrecognized instruction
            // Print message for unrecognized instruction
            cout << "PC: " << pc << " - Unrecognized instruction" << endl;
            break;
    }
}

int main() {
    // Example usage instructions
    vector<unsigned char> program = {
        0x01, 0x01, 0x02, // Load memory[2] into register[1]
        0x02, 0x02, 0x01, // Store register[1] into memory[2]
        0x03, 0x01, 0x02, // Add register[1] and register[2]
        0x04, 0x01, 0x02  // Subtract register[2] from register[1]
    };

    cout << "Starting CPU simulation..." << endl;

    load_program(program); // Load program into memory

    // Execute each instruction in the program
    for (pc = 0; pc < program.size(); pc += 3) {
        execute_instruction(&memory[pc]); // Execute current instruction
    }

    cout << "CPU Simulation Successful" << endl;

    return 0;
}
