/**
 * @file point_set.h
 * @author Суходолова Евгения КБ-251
 * @date 3 июня 2026 г.
 * @brief Библиотека для работы с множеством точек на плоскости.
 * @details Реализует структуры point_t и point_set_t, операции
 *          добавления, удаления, поиска точек, вычисления расстояния,
 *          поиска ближайшей точки и ограничивающего прямоугольника.
 */

#ifndef POINT_SET_H
#define POINT_SET_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Коды ошибок библиотеки
 */
typedef enum {
    POINT_OK = 0,           ///< Успешное выполнение
    POINT_ERR_NULL_PTR = -1, ///< NULL-указатель
    POINT_ERR_ALLOC = -2,    ///< Ошибка выделения памяти
    POINT_ERR_NOT_FOUND = -3, ///< Точка не найдена
    POINT_ERR_EMPTY = -4,    ///< Множество пусто
    POINT_ERR_DUPLICATE = -5 ///< Точка уже существует
} PointError;

/**
 * @brief Структура точки на плоскости
 */
typedef struct {
    double x;   ///< Координата X
    double y;   ///< Координата Y
} point_t;

/**
 * @brief Структура множества точек
 */
typedef struct {
    point_t* points;   ///< Динамический массив точек
    size_t capacity;   ///< Вместимость массива
    size_t size;       ///< Текущее количество точек
} point_set_t;

/**
 * @brief Создаёт пустое множество точек
 * @return Указатель на созданное множество, NULL при ошибке
 */
point_set_t* point_set_create(void);

/**
 * @brief Освобождает память множества точек
 * @param set Указатель на множество
 */
void point_set_destroy(point_set_t* set);

/**
 * @brief Добавляет точку во множество
 * @param set Указатель на множество
 * @param p Точка для добавления
 * @return POINT_OK при успехе, код ошибки иначе
 */
PointError point_set_add(point_set_t* set, point_t p);

/**
 * @brief Удаляет точку из множества
 * @param set Указатель на множество
 * @param p Точка для удаления
 * @return POINT_OK при успехе, код ошибки иначе
 */
PointError point_set_remove(point_set_t* set, point_t p);

/**
 * @brief Ищет точку во множестве
 * @param set Указатель на множество
 * @param p Искомая точка
 * @return true если точка найдена, false иначе
 */
bool point_set_find(const point_set_t* set, point_t p);

/**
 * @brief Вычисляет расстояние между двумя точками
 * @param a Первая точка
 * @param b Вторая точка
 * @return Расстояние между точками
 */
double point_distance(const point_t* a, const point_t* b);

/**
 * @brief Находит ближайшую точку к заданной
 * @param set Указатель на множество
 * @param p Заданная точка
 * @param nearest Указатель для сохранения ближайшей точки
 * @return POINT_OK при успехе, код ошибки иначе
 */
PointError point_set_find_nearest(const point_set_t* set, const point_t* p, point_t* nearest);

/**
 * @brief Вычисляет ограничивающий прямоугольник для множества точек
 * @param set Указатель на множество
 * @param min_x Минимальная X (выходной параметр)
 * @param min_y Минимальная Y (выходной параметр)
 * @param max_x Максимальная X (выходной параметр)
 * @param max_y Максимальная Y (выходной параметр)
 * @return POINT_OK при успехе, код ошибки иначе
 */
PointError point_set_bounding_box(const point_set_t* set, double* min_x, double* min_y, double* max_x, double* max_y);

/**
 * @brief Выводит все точки множества (для отладки)
 * @param set Указатель на множество
 */
void point_set_print(const point_set_t* set);

#endif
