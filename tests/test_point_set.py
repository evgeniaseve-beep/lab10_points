#!/usr/bin/env python3
import ctypes
import math
import os

lib_path = os.path.join(os.path.dirname(__file__), '..', 'build', 'libpoint_set.so')
lib = ctypes.CDLL(lib_path)

class Point(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_double),
        ("y", ctypes.c_double)
    ]

class PointSet(ctypes.Structure):
    _fields_ = [
        ("points", ctypes.POINTER(Point)),
        ("capacity", ctypes.c_size_t),
        ("size", ctypes.c_size_t)
    ]

# Определяем прототипы функций
lib.point_set_create.argtypes = []
lib.point_set_create.restype = ctypes.POINTER(PointSet)

lib.point_set_destroy.argtypes = [ctypes.POINTER(PointSet)]
lib.point_set_destroy.restype = None

lib.point_set_add.argtypes = [ctypes.POINTER(PointSet), Point]
lib.point_set_add.restype = ctypes.c_int

lib.point_set_remove.argtypes = [ctypes.POINTER(PointSet), Point]
lib.point_set_remove.restype = ctypes.c_int

lib.point_set_find.argtypes = [ctypes.POINTER(PointSet), Point]
lib.point_set_find.restype = ctypes.c_bool

lib.point_distance.argtypes = [ctypes.POINTER(Point), ctypes.POINTER(Point)]
lib.point_distance.restype = ctypes.c_double

lib.point_set_find_nearest.argtypes = [
    ctypes.POINTER(PointSet),
    ctypes.POINTER(Point),
    ctypes.POINTER(Point)
]
lib.point_set_find_nearest.restype = ctypes.c_int

lib.point_set_bounding_box.argtypes = [
    ctypes.POINTER(PointSet),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double)
]
lib.point_set_bounding_box.restype = ctypes.c_int

def test_point_set():
    print("=== Python Tests ===\n")
    
    # Создаём множество
    set_ptr = lib.point_set_create()
    assert set_ptr
    
    # Добавляем точки
    p1 = Point(0.0, 0.0)
    p2 = Point(3.0, 0.0)
    p3 = Point(0.0, 4.0)
    
    assert lib.point_set_add(set_ptr, p1) == 0
    assert lib.point_set_add(set_ptr, p2) == 0
    assert lib.point_set_add(set_ptr, p3) == 0
    print("Add points: OK")
    
    # Проверяем размер
    assert set_ptr.contents.size == 3
    print(f"Set size = {set_ptr.contents.size}: OK")
    
    # Поиск точки
    assert lib.point_set_find(set_ptr, p1) == True
    assert lib.point_set_find(set_ptr, Point(99.0, 99.0)) == False
    print("Find points: OK")
    
    # Расстояние
    dist = lib.point_distance(p1, p2)
    assert abs(dist - 3.0) < 0.0001
    print(f"Distance (0,0)-(3,0) = {dist}: OK")
    
    # Ближайшая точка
    target = Point(1.0, 1.0)
    nearest = Point()
    assert lib.point_set_find_nearest(set_ptr, target, nearest) == 0
    print(f"Nearest to (1,1) = ({nearest.x}, {nearest.y}): OK")
    
    # Ограничивающий прямоугольник
    min_x = ctypes.c_double()
    min_y = ctypes.c_double()
    max_x = ctypes.c_double()
    max_y = ctypes.c_double()
    
    assert lib.point_set_bounding_box(set_ptr, min_x, min_y, max_x, max_y) == 0
    print(f"Bounding box: x=[{min_x.value}, {max_x.value}], y=[{min_y.value}, {max_y.value}]: OK")
    
    # Удаление точки
    assert lib.point_set_remove(set_ptr, p1) == 0
    assert set_ptr.contents.size == 2
    assert lib.point_set_find(set_ptr, p1) == False
    print("Remove point: OK")
    
    # Освобождаем память
    lib.point_set_destroy(set_ptr)
    print("\nAll Python tests passed!")

if __name__ == "__main__":
    test_point_set()
