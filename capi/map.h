
#ifndef __MAP_H__
#define __MAP_H__

#include <stdlib.h>
#include "rbtree.h"

#define lock_t int
#define lock_init(x) 
#define lock_exit(x) 

#ifndef NULL
#define NULL 0
#endif

#define __assert(x)
#define __free(x) free(x)
#define __malloc(x) malloc(x)
#define __memcpy(d,s,len) memcpy((d),(s),(len))

extern struct map;

typedef int(*CMP_FUNC)(const void *d1, const void *d2);

typedef struct mnode{
	struct rb_node node;
	void *key;
	void *private;
}mnode_t;

/*
typedef struct ops{
struct mnode*(*find)(struct map *map, void *key, CMP_FUNC cmpf);
int (*insert_alloc)(struct map *map, void *key,
void *private, size_t size, CMP_FUNC cmpf);
int (*remove_free)(struct map *map, void *key, CMP_FUNC cmpf);
int (*insert)(struct map *map, struct mnode *data, CMP_FUNC cmpf);
int (*remove)(struct map *map, void *key, CMP_FUNC cmpf);
}ops_t;
*/

typedef struct map{
	struct rb_root root;
	lock_t lock;
}map_t;

extern int map_init(struct map* map);
extern int map_exit(struct map* map);

struct mnode* __rbfind(struct map *map, void *key, CMP_FUNC cmpf);
int __rbinsert_alloc(struct map *map, void *key,
	void *private, size_t size, CMP_FUNC cmpf);
int __rbremove_free(struct map *map, void *key, CMP_FUNC cmpf);
int __rbinsert(struct map *map, struct mnode *data, CMP_FUNC cmpf);
int __rbremove(struct map *map, void *key, CMP_FUNC cmpf);

#define map_find(map,key,cmpf) \
	__rbfind((map), (key), (cmpf))

#define map_insert_alloc(map,key,priv,size,cmpf) \
	__rbinsert_alloc((map), (key), (priv), (size), (cmpf))

#define map_remove_free(map,key,cmpf) \
	__rbremove_free((map), (key), (cmpf))

#if 0
#define map_insert(map,data,cmpf) \
	__rbinsert((map), (data), (cmpf))
#define map_remove(map,key,cmpf) \
	__rbremove((map), (key), (cmpf))
#endif


#define map_entry(ptr, type, member) container_of(ptr, type, member)

extern struct mnode *map_first(const struct map *map);
extern struct mnode *map_last(const struct map *map);
extern struct mnode *map_next(const struct mnode *mnode);
extern struct mnode *map_prev(const struct mnode *mnode);

extern void map_dump(const struct map* map);


#endif