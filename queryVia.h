#ifndef QUERY_VIA_H
#define QUERY_VIA_H

#include <stdio.h>
#include <string.h>
#include "geometry/point.h"
#include "data_structures/hash_table.h"
#include "city_elements/resident.h"
#include "city_elements/hydrant.h"
#include "city_elements/traffic_light.h"
#include "city_elements/radio_tower.h"

void setRegister(Point *registers, char *r, Point point);

void treatRegisterM(Point *registers, char *r, char *cep, HashTable residents);

void treatRegisterE(Point *registers, char *r, char *cep, char *face, int num, HashTable blocks);

void treatRegisterG(Point *registers, char *r, char *id, HashTable hydrants, HashTable tLights, HashTable rTowers);

#endif