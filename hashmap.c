#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long pos = hash(key, map->capacity);
    Pair * pair = createPair(key, value);
    pair->value = value;
    pair->key = key;
    if(map->buckets[pos] == NULL){
        map->buckets[pos] = pair;
        map->size++;
    }else{
        for(int i = pos; i < map->capacity; i++){
            if(map->buckets[i] == NULL){
                map->buckets[i] = pair;
                map->size++;
                break;
            }
            if(i == map->capacity - 1){
                i = 0;
            }
        }
    }
}

void enlarge(HashMap * map) {
    /*Pair ** old_buckets = map->buckets;
    long old_capacity = map->capacity;
    map->capacity *= 2;
    map->buckets = (Pair **)malloc(sizeof(Pair *) * map->capacity);
    for (int i = 0; i < map->capacity; i++) {
        map->buckets[i] = NULL;
    }

    enlarge_called = 1; //no borrar (testing purposes)*/
}

HashMap * createMap(long capacity) {
    HashMap *mapa = (HashMap *)malloc(sizeof(HashMap));
    mapa->buckets = (Pair **)malloc(sizeof(Pair *) * capacity);
    for (int i = 0; i < capacity; i++) {
        mapa->buckets[i] = NULL;
    }
    mapa->size = 0;
    mapa->capacity = capacity;
    mapa->current = -1;
    return mapa;
}

void eraseMap(HashMap * map,  char * key) {   /*
    long pos = hash(key, map->capacity);
    for(int i = pos; i <= map->capacity; i++){
        if(is_equal(map->buckets[i]->key, key)){
            map->buckets[i]->key = NULL;
            map->buckets[i]->value = NULL;
            map->size--;
        }
        if(i == map->capacity){
            i = 0;
        }
    }
*/
}

Pair * searchMap(HashMap * map,  char * key) {
    long pos = hash(key, map->capacity);
    for(int i = pos; i <= map->capacity; i++){
        if(is_equal(map->buckets[i]->key, key)){
            map->current = i;
            return map->buckets[i];
        }
        if(i == map->capacity){
            i = 0;
        }
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {/*
    for(int i = 0; i < map->capacity; i++){
        if(map->buckets[i] != NULL){
            map->current = i;
            return map->buckets[i];
        }
    }*/    
    return NULL;
}

Pair * nextMap(HashMap * map) {/*
    for(int i = map->current + 1; i < map->capacity; i++){
        if(map->buckets[i] != NULL){
            map->current = i;
            return map->buckets[i];
        }
    }*/
    return NULL;
}
