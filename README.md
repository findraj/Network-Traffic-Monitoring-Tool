
# ISA-TOP: Network Traffic Monitoring Tool

## Project Description

**ISA-TOP** is a network monitoring tool designed to display the top 10 most active network connections on a specified network interface. The tool is similar to `iftop` and provides real-time statistics about network traffic, including the speed of data transmission in bits per second (b/s) or packets per second (p/s). The tool is primarily developed for Ubuntu but should work on other Linux distributions as well.

### Features

- **Real-time Monitoring**: Displays the top 10 most active network connections in real-time.
- **Sorting Options**: Connections can be sorted by speed in bits per second (b/s) or packets per second (p/s).
- **Customizable Update Period**: The update period for collecting data can be customized (default is 1 second).
- **Support for Multiple Protocols**: Supports IPv4, IPv6, TCP, UDP, ICMP, and other protocols.
- **User-friendly Interface**: Uses the `ncurses` library to provide a clean and interactive terminal interface.

## Installation

### Dependencies

Before compiling and running **ISA-TOP**, ensure that the following libraries are installed on your system:

- **libpcap-dev**: For packet capturing.
- **libncurses5-dev**: For the terminal-based user interface.

On Ubuntu, you can install these dependencies using the following commands:

```bash
sudo apt update
sudo apt upgrade
sudo apt install libpcap-dev libncurses5-dev
```

### Compilation

To compile the program, navigate to the project directory and run:

```bash
make
```

This will generate the executable `isa-top`.

## Usage

### Command Syntax

```bash
isa-top -i interface [-s b|p] [-t period]
```

### Options

- **`-i interface`**: Specifies the network interface to monitor (mandatory).
- **`-s b|p`**: Specifies the sorting order. Use `b` to sort by bits per second (default) or `p` to sort by packets per second (optional).
- **`-t period`**: Specifies the update period in seconds (optional, default is 1 second).

### Example

To monitor the `eth0` interface and sort by packets per second with an update period of 2 seconds, use:

```bash
sudo isa-top -i eth0 -s p -t 2
```

### Cleaning Up

To clean up the compiled files and other generated files, use:

```bash
make clean
```

### Packaging

To package the project into a `.tar` archive for easy distribution, use:

```bash
make pack
```

## Implementation

### Key Components

- **Packet Capture**: The tool uses the `libpcap` library to capture network packets on the specified interface.
- **Packet Processing**: Captured packets are processed to extract relevant information such as source/destination IP addresses, ports, and protocol types.
- **Statistics Collection**: The tool collects statistics about the speed of data transmission (in bits or packets per second) for each connection.
- **User Interface**: The `ncurses` library is used to display the top 10 connections in a user-friendly table format.

### Code Organization

The project is organized into the following files:

- **`_args.cpp`**: Handles command-line argument parsing.
- **`_main.cpp`**: Contains the main logic of the program.
- **`_packetHandler.cpp`**: Processes captured packets and extracts relevant information.
- **`_screen.cpp`**: Manages the display of statistics using the `ncurses` library.
- **`_test`**: Contains test scripts for automated testing.

## Testing

### Manual Testing

Most of the testing was done manually by comparing the output of **ISA-TOP** with other network monitoring tools like `iftop` and `Wireshark`. The tool was tested on both Ubuntu 22.04 LTS and Ubuntu 24.04 LTS.

### Automated Testing

Automated tests are provided in the `test.sh` script, which checks the program's handling of various command-line arguments. To run the tests, use:

```bash
make test
```

or

```bash
sudo ./test/test.sh
```

## Conclusion

**ISA-TOP** is a lightweight and efficient tool for monitoring network traffic in real-time. It provides valuable insights into the most active network connections and can be easily customized to suit different monitoring needs. The tool is particularly useful for network administrators and developers who need to analyze network traffic on Linux systems.

## References

- **libpcap**: [https://www.tcpdump.org/](https://www.tcpdump.org/)
- **ncurses**: [https://invisible-island.net/ncurses/](https://invisible-island.net/ncurses/)
- **ISO/OSI Model**: [Wikipedia](https://en.wikipedia.org/wiki/OSI_model)

## Author

- **Ján Findra** (<xfindr01@stud.fit.vutbr.cz>)

## License

This project is licensed under the **GNU General Public License (GPL)**.
