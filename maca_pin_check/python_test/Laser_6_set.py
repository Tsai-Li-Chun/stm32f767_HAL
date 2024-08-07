import serial
import time
import sys

# Initialize the serial connection
ser = serial.Serial('COM7', baudrate=9600, timeout=1)


def hex_bytes_to_swapped_int(hex_bytes):
	# Convert string-formatted byte data to actual byte data
	byte_data = bytes.fromhex(''.join(hex_bytes))
	
	# Check if data length is 4
	if len(byte_data) != 4:
		raise ValueError("Byte data must be exactly 4 bytes long")
	
	# Swap the first and last two bytes
	swapped_byte_data = byte_data[2:] + byte_data[:2]
	
	# Convert byte data to a 32-bit integer (big-endian)
	combined = int.from_bytes(swapped_byte_data, byteorder='big')
	
	return combined

# disp_history = []
all_data_history = []
bool_disp = True
bool_force = True
t1 = time.time()

# Check if the serial port is open before proceeding
if ser.isOpen():
	ser.flushInput()  # Flush input buffer
	ser.flushOutput()  # Flush output buffer
	
	try:
		while True:
			# if time.time() - t1 > 5:
			#     break
			ser.flushInput()  # Flush input buffer
			ser.flushOutput()  # Flush output buffer
			bool_disp = True
			temp_all_data = []

			while bool_disp:
				# print("In sec 2")
				rcev = ser.read(1)
				decoded_data = rcev.decode('utf-8', errors='ignore')
				disp_list = []
				if decoded_data == 'C':
					disp_list.append(decoded_data)
					for i in range(24):
						disp_list.append(ser.read(1).hex())
					for i in range(2):
						disp_list.append(ser.read(1).decode('utf-8', errors='ignore'))
	
					combined_int = [0]*6
					print("combined_int: ", end='')
					for i in range(6):
						combined_int[i] = hex_bytes_to_swapped_int(disp_list[(i*4+1):(i*4+5)])
						print(combined_int[i], end=' , ')
					print("")
					temp_all_data.append(combined_int)
					# disp_history.append(combined_int)
					print("Hex: ", end='')
					for i in range(6):
						print(f"0x{combined_int[i]:08X}", end=' , ')  # Display in hexadecimal format
					print("")
					print("Decimal: ", end='')
					for i in range(6):
						print(f"{combined_int[i]}", end=' , ')    # Display in decimal format
					print("",end='\n\n')

					bool_disp = False
					bool_record = True
			if bool_record:
				all_data_history.append(temp_all_data)
			
	except Exception as e1:
		print("Communicating error:", e1)
	finally:
		print("Time elapsed: ", time.time() - t1)
		ser.close()
else:
	print("Open serial port error: Port is already open.")
