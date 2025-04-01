#ifndef STRUCTS_H
#define STRUCTS_H



typedef struct {
    char pizza_id[16];
    char order_id[16];
    char pizza_name_id[64];
    float quantity;
    char order_date[16];
    char order_time[16];
    float unit_price;
    float total_price;
    char pizza_size[8];
    char pizza_category[32];
    char pizza_ingredients[256];
    char pizza_name[128];
} VentaPizza;


typedef struct {
    char nombre[128];
    float cantidad_total;
} PizzaVenta;

#endif


