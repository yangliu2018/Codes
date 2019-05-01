# A Simple Operating System

### [Reference Data] Writing a Simple Operating System_ from Scartch, by Nick Blundell

## function call sequence
- load_kernel
    - disk_load
- switch_to_pm (switch CPU from 16-bit read mode to 32-bit read mode)
    - init_pm
        - BEGIN_PM
            - KERNEL_OFFSET (main function written in C)

## folder structure
- boot: boot sector and anything related to booting
- kernel: the kernel's main file and any other kernel related code except device specific code
- drivers: hardware specific driver code
