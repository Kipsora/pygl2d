import ctypes

import numpy

_lib = ctypes.cdll.LoadLibrary('lib/libpygl2d.dylib')


def init_window(w, h, title):
    assert isinstance(w, int) and w > 0
    assert isinstance(h, int) and h > 0
    assert isinstance(title, str)
    _w = ctypes.c_int(w)
    _h = ctypes.c_int(h)
    _title = ctypes.c_char_p(title.encode('utf8'))
    _lib.initWindow.restype = ctypes.c_void_p
    handle = _lib.initWindow(_w, _h, _title)
    if not handle:
        raise RuntimeError("Cannot initialize OpenGL window")
    return handle


def set_clear_color(r, g, b, a):
    assert 0 <= float(r) <= 1
    assert 0 <= float(g) <= 1
    assert 0 <= float(b) <= 1
    assert 0 <= float(a) <= 1
    _r = ctypes.c_float(float(r))
    _g = ctypes.c_float(float(g))
    _b = ctypes.c_float(float(b))
    _a = ctypes.c_float(float(a))
    _lib.setClearColor(_r, _g, _b, _a)


def clear(handle):
    _handle = ctypes.c_void_p(handle)
    _lib.clear(_handle)


def display(handle):
    _handle = ctypes.c_void_p(handle)
    _lib.display(_handle)


def on_close(handle):
    _handle = ctypes.c_void_p(handle)
    _lib.eventOnClose.restype = ctypes.c_int
    return _lib.eventOnClose(_handle)


def poll():
    _lib.pollEvents()


def terminate():
    _lib.terminate()


def draw_triangle(x1, y1, x2, y2, x3, y3, r, g, b, a):
    assert 0 <= float(r) <= 1
    assert 0 <= float(g) <= 1
    assert 0 <= float(b) <= 1
    assert 0 <= float(a) <= 1
    _x1 = ctypes.c_float(float(x1))
    _x2 = ctypes.c_float(float(x2))
    _x3 = ctypes.c_float(float(x3))
    _y1 = ctypes.c_float(float(y1))
    _y2 = ctypes.c_float(float(y2))
    _y3 = ctypes.c_float(float(y3))
    _r = ctypes.c_float(float(r))
    _g = ctypes.c_float(float(g))
    _b = ctypes.c_float(float(b))
    _a = ctypes.c_float(float(a))
    _lib.drawTriangle(_x1, _y1, _x2, _y2, _x3, _y3, _r, _g, _b, _a)


def draw_triangle_fan(x, y, r, g, b, a):
    assert len(x) == len(y)
    assert 0 <= float(r) <= 1
    assert 0 <= float(g) <= 1
    assert 0 <= float(b) <= 1
    assert 0 <= float(a) <= 1
    _x = list(map(float, x))
    _y = list(map(float, y))
    _n = ctypes.c_int(len(x))
    _x = (ctypes.c_float * len(_x))(*_x)
    _y = (ctypes.c_float * len(_y))(*_y)
    _r = ctypes.c_float(float(r))
    _g = ctypes.c_float(float(g))
    _b = ctypes.c_float(float(b))
    _a = ctypes.c_float(float(a))
    _lib.drawTriangleFan(_n, _x, _y, _r, _g, _b, _a)


def draw_rectangle(x1, y1, x2, y2, r, g, b, a):
    draw_triangle_fan(
        (x1, x1, x2, x2),
        (y1, y2, y2, y1),
        r, g, b, a
    )


def draw_quad(x1, y1, x2, y2, x3, y3, x4, y4, r, g, b, a):
    draw_triangle_fan(
        (x1, x2, x3, x4),
        (y1, y2, y3, y4),
        r, g, b, a
    )


def draw_line(x1, y1, x2, y2, r, g, b, a, smooth=True):
    assert 0 <= float(r) <= 1
    assert 0 <= float(g) <= 1
    assert 0 <= float(b) <= 1
    assert 0 <= float(a) <= 1
    _x1 = ctypes.c_float(float(x1))
    _x2 = ctypes.c_float(float(x2))
    _y1 = ctypes.c_float(float(y1))
    _y2 = ctypes.c_float(float(y2))
    _r = ctypes.c_float(float(r))
    _g = ctypes.c_float(float(g))
    _b = ctypes.c_float(float(b))
    _a = ctypes.c_float(float(a))
    _smooth = ctypes.c_bool(bool(smooth))
    _lib.drawLine(_x1, _y1, _x2, _y2, _r, _g, _b, _a, _smooth)


def draw_circle(x, y, radius, r, g, b, a, s=40):
    _x, _y = [], []
    for i in range(s):
        _x.append(x + radius * numpy.cos(float(i) / s * 2 * numpy.pi))
        _y.append(y + radius * numpy.sin(float(i) / s * 2 * numpy.pi))
    draw_triangle_fan(_x, _y, r, g, b, a)
