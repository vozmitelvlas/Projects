from PiyPiy1 import begin
import time
import matplotlib.pyplot as plt

x, y = [], []
for i in range(2, 21):
    start = time.time()
    begin(i)
    end = time.time()
    x.append(i)
    y.append(end - start)

plt.xlabel("Square's size")
plt.ylabel("Time")
plt.grid(True)
plt.xticks(x)
plt.plot(x, y)
plt.scatter(x, y)
plt.show()
