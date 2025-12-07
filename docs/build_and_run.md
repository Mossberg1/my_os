# Build and Run

To build and run this OS you need a UNIX environment like linux or macos. If you are on windows you should use WSL.
For macos homebrew is required.

## Development Tools

### macos
```sh
$ brew install llvm lld qemu
```
Also make sure everything is in your PATH.

### ubuntu
```sh
$ sudo apt update && sudo apt install -y clang llvm lld qemu-system-riscv32 curl
```

!!! tip  
    To check if clang has support for 32-bit RISC-V run this command
    and you should get the same output.

    ```sh
    $ clang -print-targets | grep riscv32 # Expected output: riscv32 - 32-bit RISC-V
    ```

    Clang on macos wont have support for this by default. So you have to use clang from the homebrew llvm package.

## Compile and start the VM
The run.sh script compiles and runs the virtual machine.
```sh
$ chmod +x run.sh
$ ./run.sh
```
