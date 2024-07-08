; This section defines memory allocation using reserve bytes (.bss)
section .bss
  ; Allocate 256 bytes for simulated memory
  memory resb 256  ; resb stands for reserve bytes
  ; Allocate 4 bytes for four general-purpose registers
  registers resb 4  ; resb stands for reserve bytes

; This section defines executable code (.text)
section .text
; Declare these functions as globally accessible (for calls from cpu_simulator.cpp)
    global load
    global store
    global add
    global sub

; Implementation of load function
load:
    push ebp           ; Save the base pointer
    mov ebp, esp       ; Set up a new base pointer
    ; Get address (argument 1) and register index (argument 2)
    mov eax, [ebp+8]   ; Load argument 1 (memory address)
    mov ebx, [ebp+12]  ; Load argument 2 (register index)
    ; Load value from memory into register
    mov edx, [memory + eax]  ; Load value from memory at the given address
    mov [registers + ebx], edx  ; Store the loaded value into the specified register
    pop ebp            ; Restore the base pointer
    ret                ; Return from function

; Implementation of store function
store:
    push ebp
    mov ebp, esp
    ; Get address (argument 1) and register index (argument 2)
    mov eax, [ebp+8]   ; Load argument 1 (memory address)
    mov ebx, [ebp+12]  ; Load argument 2 (register index)
    ; Store value from register into memory
    mov edx, [registers + ebx]  ; Load value from the specified register
    mov [memory + eax], edx     ; Store the loaded value into memory at the given address
    pop ebp
    ret

; Implementation of add function
add:
    push ebp
    mov ebp, esp
    ; Get index of register 1 (argument 1) and index of register 2 (argument 2)
    mov eax, [ebp+8]   ; Load argument 1 (index of register 1)
    mov ebx, [ebp+12]  ; Load argument 2 (index of register 2)
    ; Add values of two registers
    mov ecx, [registers + eax]  ; Load value from register 1
    add ecx, [registers + ebx]  ; Add value from register 2 to register 1
    mov [registers + eax], ecx  ; Store the result back into register 1
    pop ebp
    ret

; Implementation of sub function
sub:
    ; Function prologue
    push ebp
    mov ebp, esp
    ; Get index of register 1 (argument 1) and index of register 2 (argument 2)
    mov eax, [ebp+8]   ; Load argument 1 (index of register 1)
    mov ebx, [ebp+12]  ; Load argument 2 (index of register 2)
    ; Subtract value of one register from another
    mov ecx, [registers + eax]  ; Load value from register 1
    sub ecx, [registers + ebx]  ; Subtract value from register 2 from register 1
    mov [registers + eax], ecx  ; Store the result back into register 1
    pop ebp
    ret
