# Set the architecture
# set architecture pei-x86-64

# Load the logger object file
# add-symbol-file logger.o 0

# Display information about loaded files
# info files

# Set disassembly flavor to Intel syntax
set disassembly-flavor intel

disass EVENT_LOG_SSL 
