from serial import Serial

ser:Serial = Serial()
ser.baudrate = 3000000
ser.port="COM6"

ser.open()

ser.write('HELLO WORLD'.encode('utf-8'))
res = ser.read(11)
print(res)

ser.close()