import gdb

class SetArchitecture(gdb.Command):
    def __init__(self):
        super(SetArchitecture, self).__init__("set_architecture", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        if arg:
            gdb.execute(f'set architecture {arg}')
            print(f'Architecture set to {arg}')
        else:
            print("Usage: set-architecture <architecture>")

class LoadSymbolFile(gdb.Command):
    def __init__(self):
        super(LoadSymbolFile, self).__init__("load_sym_file", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        gdb.execute(f'add-symbol-file {arg} 0')
        print(f'Loaded symbol file for {arg}')

class DisplayFileInfo(gdb.Command):
    def __init__(self):
        super(DisplayFileInfo, self).__init__("display_file_info", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        gdb.execute(f'info files')
        print('Displayed file info')

class SetDisassemblyFlavor(gdb.Command):
    def __init__(self):
        super(SetDisassemblyFlavor, self).__init__("set_disassembly_flavor", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        gdb.execute(f'set disassembly-flavor {arg}')
        print(f'Set disassembly flavor to {arg}')

SetArchitecture()
LoadSymbolFile()
DisplayFileInfo
SetDisassemblyFlavor()
