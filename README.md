# TIXB
TIXB is a toy bytecode interpreter

# Installation

```bash
git clone https://github.com/ninjamar/tixb
cd tixb
g++-11 src/cli.cpp -o tixb
```

# Usage
Create a new binary file called `test.tixb` extension in a hex editor. Put  `0001 0010 1064 0000 0002 0010 0000 0000` inside it. This is sets `rcx` to `100` and prints it. On the command line, run `./tixb test.tixb`. You should see 100 on the display.

# Documentation
coming soon
