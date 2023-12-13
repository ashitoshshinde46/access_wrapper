import ctypes
# Load the shared library
lib = ctypes.cdll.LoadLibrary("/mnt/f/dynalog/shared_memory/build/shared_lib/libacces_dio.so")
# Get the address of the function to be called
func = lib.dio_writesingle
a=ctypes.c_int(10)

# by_ref_in_c(xp)

# Call the function
result = func(a, True)

# Print the result
print(result)