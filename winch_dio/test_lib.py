import ctypes
import time
# Load the shared library
lib = ctypes.cdll.LoadLibrary("/root/Documents/DIODO_Test/access_wrapper/test_dio/buiild/libacces_dio.so")
# Get the address of the function to be called
func = lib.readall_dio
a=ctypes.c_int(10)
numbers=[1,2,3,4,5,6,7,8,8,10,11,12,13,14,15,16]
array_type = ctypes.c_char * 16  # equiv. to C double[3] type
arr = array_type(*numbers)        # equiv. to double arr[3] = {...} instance
# by_ref_in_c(xp)

# Call the function
result = func(arr)

# Print the result
print(result)
while(1):
	for i in range(4):
		print("DIO %2d:",i,arr[i])
		time.sleep(1)
