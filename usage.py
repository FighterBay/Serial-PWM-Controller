import serial


def send_PWM(ser,PWM1,PWM2):
  to_send = str(PWM1) + ":" + str(PWM2) + ":|"
  ser.write(to_send.encode())
  ser.flushInput()

ser = serial.Serial(
  port='/dev/ttyUSB0',  #Assuming arduino is connected @ ttyUSB0
  baudrate = 9600,    #Baudrate
  parity=serial.PARITY_NONE,
  stopbits=serial.STOPBITS_ONE,
  bytesize=serial.EIGHTBITS,
  timeout=2
)

send_PWM(ser,1000,1000)
