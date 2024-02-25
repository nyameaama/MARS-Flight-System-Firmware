from ctypes import *
import os

# Update the import path to include needed files

# Load the shared library
so_file = CDLL("C:\\Users\\lukas\\MARS-Flight-System-Firmware\\test\\VBV_subsystem\\main\\.\vbv_sub.so")

# Declare the function prototype
alt_sensor_check = so_file.alt_sensor_check
alt_sensor_check.argtypes = [c_double]
alt_sensor_check.restype = None
