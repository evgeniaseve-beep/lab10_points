#include "/Users/evgeniasuhodolova/lab10_points/lab10_points/include/point_set.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define TEST_PASS() printf("%s: PASSED\n", __func__)

void test_create_destroy() {
    point_set_t* set = point_set_create();
    assert(set != NULL);
    assert(set->size == 0);
    point_set_destroy(set);
    TEST_PASS();
}

void test_add_and_find() {
    point_set_t* set = point_set_create();
    point_t p = {1.0, 2.0};
    
    assert(point_set_add(set, p) == POINT_OK);
    assert(set->size == 1);
    assert(point_set_find(set, p) == true);
    
    point_t p2 = {1.0, 2.0};
    assert(point_set_add(set, p2) == POINT_ERR_DUPLICATE);
    
    point_set_destroy(set);
    TEST_PASS();
}

void test_remove() {
    point_set_t* set = point_set_create();
    point_t p1 = {1.0, 1.0};
    point_t p2 = {2.0, 2.0};
    
    point_set_add(set, p1);
    point_set_add(set, p2);
    assert(set->size == 2);
    
    assert(point_set_remove(set, p1) == POINT_OK);
    assert(set->size == 1);
    assert(point_set_find(set, p1) == false);
    assert(point_set_find(set, p2) == true);
    
    assert(point_set_remove(set, p1) == POINT_ERR_NOT_FOUND);
    
    point_set_destroy(set);
    TEST_PASS();
}

void test_distance() {
    point_t a = {0.0, 0.0};
    point_t b = {3.0, 4.0};
    
    double dist = point_distance(&a, &b);
    assert(fabs(dist - 5.0) < 0.0001);
    
    TEST_PASS();
}

void test_find_nearest() {
    point_set_t* set = point_set_create();
    point_t p1 = {0.0, 0.0};
    point_t p2 = {10.0, 0.0};
    point_t p3 = {0.0, 10.0};
    
    point_set_add(set, p1);
    point_set_add(set, p2);
    point_set_add(set, p3);
    
    point_t target = {1.0, 1.0};
    point_t nearest;
    
    assert(point_set_find_nearest(set, &target, &nearest) == POINT_OK);
    assert(nearest.x == 0.0 && nearest.y == 0.0);
    
    point_set_destroy(set);
    TEST_PASS();
}

void test_bounding_box() {
    point_set_t* set = point_set_create();
    point_t p1 = {-1.0, -2.0};
    point_t p2 = {3.0, 4.0};
    point_t p3 = {0.0, 0.0};
    
    point_set_add(set, p1);
    point_set_add(set, p2);
    point_set_add(set, p3);
    
    double min_x, min_y, max_x, max_y;
    assert(point_set_bounding_box(set, &min_x, &min_y, &max_x, &max_y) == POINT_OK);
    assert(fabs(min_x + 1.0) < 0.0001);
    assert(fabs(min_y + 2.0) < 0.0001);
    assert(fabs(max_x - 3.0) < 0.0001);
    assert(fabs(max_y - 4.0) < 0.0001);
    
    point_set_destroy(set);
    TEST_PASS();
}

void test_empty_set() {
    point_set_t* set = point_set_create();
    point_t target = {0.0, 0.0};
    point_t nearest;
    double min_x, min_y, max_x, max_y;
    
    assert(point_set_find_nearest(set, &target, &nearest) == POINT_ERR_EMPTY);
    assert(point_set_bounding_box(set, &min_x, &min_y, &max_x, &max_y) == POINT_ERR_EMPTY);
    
    point_set_destroy(set);
    TEST_PASS();
}

void test_null_checks() {
    point_t p = {1.0, 1.0};
    point_t nearest;
    
    assert(point_set_add(NULL, p) == POINT_ERR_NULL_PTR);
    assert(point_set_remove(NULL, p) == POINT_ERR_NULL_PTR);
    assert(point_set_find(NULL, p) == false);
    assert(point_set_find_nearest(NULL, &p, &nearest) == POINT_ERR_NULL_PTR);
    
    TEST_PASS();
}

int main() {
    test_create_destroy();
    test_add_and_find();
    test_remove();
    test_distance();
    test_find_nearest();
    test_bounding_box();
    test_empty_set();
    test_null_checks();
    
    printf("\n========== ALL C TESTS PASSED ==========\n");
    return 0;
}
