import math

import pygl2d

handle = pygl2d.init_window(400, 400, "Hello World")
pygl2d.set_clear_color(0, 0, 0, 0)

t = 0
while not pygl2d.on_close(handle):
    pygl2d.poll()
    pygl2d.clear(handle)
    pygl2d.draw_rectangle(0.0 + math.sin(t), 0.0, 0.3 + math.sin(t), 0.3, 1.0, 0.5, 0.2, 1.0)
    pygl2d.draw_line(0.0, 0.0, math.cos(t), math.sin(t), 1.0, 1.0, 0.2, 1.0)
    pygl2d.draw_circle(0, 0, 0.05, 1.0, 1.0, 0.2, 1.0)
    pygl2d.display(handle)
    t += 0.03
pygl2d.terminate()
