#include "/Users/evgeniasuhodolova/lab10_points/lab10_points/include/point_set.h"
#include <stdio.h>

int main() {
    printf("=== Point Set Library Demo ===\n\n");
    
    // Создаём множество
    point_set_t* set = point_set_create();
    
    // Добавляем точки
    point_t p1 = {0.0, 0.0};
    point_t p2 = {3.0, 0.0};
    point_t p3 = {0.0, 4.0};
    point_t p4 = {5.0, 5.0};
    
    point_set_add(set, p1);
    point_set_add(set, p2);
    point_set_add(set, p3);
    point_set_add(set, p4);
    
    point_set_print(set);
    
    // Расстояние между двумя точками
    double dist = point_distance(&p1, &p2);
    printf("\nDistance between (0,0) and (3,0): %.2f\n", dist);
    
    // Поиск ближайшей точки к (1,1)
    point_t target = {1.0, 1.0};
    point_t nearest;
    if (point_set_find_nearest(set, &target, &nearest) == POINT_OK) {
        printf("Nearest point to (1,1): (%.2f, %.2f)\n", nearest.x, nearest.y);
    }
    
    // Ограничивающий прямоугольник
    double min_x, min_y, max_x, max_y;
    if (point_set_bounding_box(set, &min_x, &min_y, &max_x, &max_y) == POINT_OK) {
        printf("Bounding box: x=[%.2f, %.2f], y=[%.2f, %.2f]\n", min_x, max_x, min_y, max_y);
    }
    
    // Удаление точки
    printf("\nRemoving point (0,0)...\n");
    point_set_remove(set, p1);
    point_set_print(set);
    
    // Поиск точки
    printf("\nFinding point (0,0): %s\n", 
           point_set_find(set, p1) ? "FOUND" : "NOT FOUND");
    printf("Finding point (3,0): %s\n", 
           point_set_find(set, p2) ? "FOUND" : "NOT FOUND");
    
    // Освобождаем память
    point_set_destroy(set);
    
    return 0;
}
