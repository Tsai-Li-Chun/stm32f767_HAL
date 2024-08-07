import tkinter as tk
from tkinter import ttk
import serial
import threading
from PIL import ImageTk, Image

class ProgressBarApp:
	def __init__(self, root):
		self.root = root
		self.root.title("MACA LD-100E-M22 X6")

		self.style = ttk.Style()
		self.style.theme_use('default')
		self.style.configure("Red.Horizontal.TProgressbar",
								troughcolor='white',
								background='red'		)
		self.style.configure("Blue.Horizontal.TProgressbar",
								troughcolor='white',
								background='blue'		)

		# create Progressbar and img and label
		self.progress = []
		self.img = []
		self.photo = []
		self.canvas = []
		self.jpg_name = []
		self.dis_label = []
		for i in range(6):
			self.progress.append(ttk.Progressbar(root, style="Red.Horizontal.TProgressbar", orient="horizontal", length=300, mode="determinate"))
			self.progress[i]["maximum"] = 100
			self.jpg_name.append("id"+str(i+1)+".jpg")
			self.img.append(Image.open(self.jpg_name[i]))
			self.photo.append(ImageTk.PhotoImage(self.img[i]))
			self.canvas.append(tk.Canvas(root, width=100, height=68))
			self.canvas[i].create_image(0, 0, anchor='nw', image=self.photo[i])
			self.dis_label.append(tk.Label(root, text='xxxxxx um', font=('Arial',15)))
			self.canvas[i].grid(column=0, row=i)
			self.progress[i].grid(column=1, row=i)
			self.dis_label[i].grid(column=2, row=i)
		
		# create serial connection
		self.serial_port = serial.Serial('COM7', 9600, timeout=1)
		if self.serial_port.isOpen():
			self.serial_port.flushInput()  # Flush input buffer
			self.serial_port.flushOutput()  # Flush output buffer
			print("Open serial port success!")
		else:
			print("Open serial port error: Port is already open.")

		# steup serial read thread
		self.thread = threading.Thread(target=self.read_serial)
		self.thread.daemon = True
		self.thread.start()

	def hex_bytes_to_swapped_int(self, hex_bytes):
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

	def read_serial(self):
		all_data_history = []
		try:
			while True:
				self.serial_port.flushInput()  # Flush input buffer
				self.serial_port.flushOutput()  # Flush output buffer
				bool_disp = True
				temp_all_data = []

				while bool_disp:
					# print("In sec 2")
					rcev = self.serial_port.read(1)
					decoded_data = rcev.decode('utf-8', errors='ignore')
					disp_list = []
					if decoded_data == 'C':
						disp_list.append(decoded_data)
						for i in range(24):
							disp_list.append(self.serial_port.read(1).hex())
						for i in range(2):
							disp_list.append(self.serial_port.read(1).decode('utf-8', errors='ignore'))
		
						combined_int = [0]*6
						print("combined_int: ", end='')
						for i in range(6):
							combined_int[i] = self.hex_bytes_to_swapped_int(disp_list[(i*4+1):(i*4+5)])
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
						# update Progressbar
						for i in range(6):
							self.update_GUIwindows(i, combined_int[i])
				if bool_record:
					all_data_history.append(temp_all_data)
				
		except Exception as e1:
			print("Communicating error:", e1)
		finally:
			print("Time elapsed: ", time.time() - t1)
			self.serial_port.close()

	def update_GUIwindows(self, id, value):
		# update Progressbar value
		if (value<65000) or (value>135000):
			self.progress[id].configure(style="Red.Horizontal.TProgressbar")
			self.progress[id]["value"] = 100
			self.dis_label[id].config(text='xxxxxx um', fg='red')
		else:
			total_distance = 135000 - 65000
			current_distance = value - 65000
			position_ratio = (current_distance/total_distance)*100
			self.progress[id].configure(style="Blue.Horizontal.TProgressbar")
			self.progress[id]["value"] = position_ratio
			self.dis_label[id].config(text=str(value), fg='blue')
		self.root.update_idletasks()


if __name__ == "__main__":
	root = tk.Tk()
	app = ProgressBarApp(root)
	root.mainloop()
