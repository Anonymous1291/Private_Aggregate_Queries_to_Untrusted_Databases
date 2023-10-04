import mathplotlib.pyplot as plt

x = [14, 16, 18, 20]
y_8 = [30528, 31008, 21248, 9024]
y_16 = [30144, 34208, 22464, 8768]
y_128 = [32640, 31488, 22720, 8928]
y_256 = [35104, 33120, 22880, 8960]
y_512 = [33888, 33504, 23424, 8608]
display = ['2^11', '2^13' ]
plt.yticks()
plt.plot(x, y_8, label = "2^8")
plt.plot(x, y_16, label = "2^16")
plt.plot(x, y_128, label = "2^128")
plt.plot(x, y_256, label = "2^256")
plt.plot(x, y_512, label = "2^512")

plt.legend()
plt.show()