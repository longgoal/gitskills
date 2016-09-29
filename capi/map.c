
#define DEBUG
#include "map.h"

#define mnode_init(mnode) {\
	(mnode)->node.rb_parent_color = 0; \
	(mnode)->node.rb_right = 0; \
	(mnode)->node.rb_left = 0; \
	(mnode)->key = 0; \
	(mnode)->private = 0; \
}


void map_dump(const struct map* map)
{
	struct mnode *mnode;
	int cnt = 0;
	for (mnode = map_first(map); mnode; mnode = map_next(mnode))
		printf("key=%03d%s", *(int*)mnode->key, ++cnt % 10 == 0 ? "\n" : " ");
	printf("\n");
}


static int __cmp_default(long *d1, long *d2)
{
	// printf("-- d1:%d, d2:%d\n", *d1, *d2);
	if (*d1 < *d2) return -1;
	else if (*d1 > *d2) return 1;
	else return 0;
}

struct mnode* __rbfind(struct map *map, void *key, CMP_FUNC cmpf)
{
	int result;
	CMP_FUNC cmp;
	struct mnode *data;
	struct rb_node *node = map->root.rb_node;

	__assert(map && key);

	cmp = cmpf ? cmpf : __cmp_default;
	/* printf("==> entry %s key:%d\n", __func__, *(int*)key); */
	while (node)
	{
		data = container_of(node, struct mnode, node);
		/* printf("data->key:%d VS key:%d\n", *(int*)(data->key), *(int*)key);*/
		result = cmp(key, data->key);
		/*printf("result=%d, node->rb_left=%p, node->rb_right=%p\n",
		result, node->rb_left, node->rb_right);*/
		if (result < 0)
			node = node->rb_left;
		else if (result > 0)
			node = node->rb_right;
		else
			return data;
	}
	//printf("node=%p\n", node);
	return NULL;
}

int __rbinsert(struct map *map, struct mnode *data, CMP_FUNC cmpf)
{
	int result;
	struct mnode *this;
	CMP_FUNC cmp;
	struct rb_node **new = &(map->root.rb_node), *parent = NULL;

	__assert(map && data);

	cmp = cmpf ? cmpf : __cmp_default;

	/* Figure out where to put new node */
	while (*new)
	{
		this = container_of(*new, struct mnode, node);
		result = cmp(data->key, this->key);

		parent = *new;
		if (result < 0) new = &((*new)->rb_left);
		else if (result > 0) new = &((*new)->rb_right);
		else return -2;
	}
	/* Add new node and rebalance tree. */
	rb_link_node(&(data->node), parent, new);
	rb_insert_color(&(data->node), &(map->root));
	return 0;
}

int __rbremove(struct map *map, void *key, CMP_FUNC cmpf)
{
	struct mnode* data = __rbfind(map, key, cmpf);
	__assert(map && key);
	if (data)
		rb_erase(&(data->node), &(map->root));
	return 0;
}

int __rbinsert_alloc(struct map *map, void *key,
	void *private, size_t size, CMP_FUNC cmpf)
{
	struct mnode *new;
	__assert(map && key && private);
	new = (struct mnode*)__malloc(size + sizeof(struct mnode));
	__assert(new);
	mnode_init(new);
	new->key = key;
	new->private = new + 1;
	if (private)
		__memcpy(new->private, private, size);

	return __rbinsert(map, new, cmpf);
}

int __rbremove_free(struct map *map, void *key, CMP_FUNC cmpf)
{
	struct mnode* data;
	__assert(map && key);
	data = __rbfind(map, key, cmpf);
	/* printf("%s: key: %d\n", __func__, *(int*)(data->key)); */
	if (data)
	{
		/* printf("%s: deleted!\n", __func__);*/
		rb_erase(&(data->node), &(map->root));
		__free(data);
	}
	return 0;
}

struct mnode *map_first(const struct map *map)
{
	struct rb_node *node;
	__assert(map);
	node = rb_first(&(map->root));
	if (node)
		return map_entry(node, struct mnode, node);
	return NULL;
}

struct mnode *map_last(const struct map *map)
{
	struct rb_node *node;
	__assert(map);
	node = rb_last(&(map->root));
	if (node)
		return map_entry(node, struct mnode, node);
	return NULL;
}

struct mnode *map_next(const struct mnode *mnode)
{
	struct rb_node *node;
	__assert(mnode);
	node = rb_next(&(mnode->node));
	if (node)
		return map_entry(node, struct mnode, node);
	return NULL;
}

struct mnode *map_prev(const struct mnode *mnode)
{
	struct rb_node *node;
	__assert(mnode);
	node = rb_prev(&(mnode->node));
	if (node)
		return map_entry(node, struct mnode, node);
	return NULL;
}


int map_init(struct map* map)
{
	map->root.rb_node = NULL;
	lock_init(map->lock);
	return 0;
}

int map_exit(struct map* map)
{
	lock_exit(map->lock);
	return 0;
}
