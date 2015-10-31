#ifndef NCHAN_RBTREE_UTIL_HEADER
#define NCHAN_RBTREE_UTIL_HEADER

//#define NCHAN_RBTREE_DBG 1

typedef struct {
  char              *name;
  ngx_rbtree_t       tree;
  ngx_rbtree_node_t  sentinel;
  ngx_str_t         *(*id)(void *node);
  uint32_t           (*hash)(ngx_str_t *str);
  ngx_int_t          (*compare)(ngx_str_t *id1, ngx_str_t *id2);
#if NCHAN_RBTREE_DBG   
  ngx_uint_t         allocd_nodes;
  ngx_uint_t         active_nodes;
#endif
} rbtree_seed_t;


#if NCHAN_RBTREE_DBG 
typedef struct ngx_rbtree_debug_node_s ngx_rbtree_debug_node_t;

typedef struct {
  struct ngx_rbtree_debug_node_s  *prev;
  struct ngx_rbtree_debug_node_s  *next;
} ngx_rbtree_debug_node_link_t;

struct ngx_rbtree_debug_node_s {
  ngx_rbtree_node_t              node;
  ngx_rbtree_debug_node_link_t   allocd;
  ngx_rbtree_debug_node_link_t   active;
}; //ngx_rbtree_debug_node_t;
#endif


typedef ngx_int_t (*rbtree_walk_callback_pt)(rbtree_seed_t *, void *, void *);

ngx_int_t            rbtree_init(rbtree_seed_t *, char *, ngx_str_t *(*id)(void *), uint32_t (*hash)(ngx_str_t *), ngx_int_t (*compare)(ngx_str_t *, ngx_str_t *));
ngx_int_t            rbtree_shutdown(rbtree_seed_t *);

ngx_rbtree_node_t   *rbtree_create_node(rbtree_seed_t *, size_t);
ngx_int_t            rbtree_insert_node(rbtree_seed_t *, ngx_rbtree_node_t *);
ngx_int_t            rbtree_remove_node(rbtree_seed_t *, ngx_rbtree_node_t *);
ngx_int_t            rbtree_destroy_node(rbtree_seed_t *, ngx_rbtree_node_t *);

ngx_rbtree_node_t   *rbtree_find_node(rbtree_seed_t *, ngx_str_t *);
ngx_int_t            rbtree_walk(rbtree_seed_t *seed, rbtree_walk_callback_pt, void *data);

ngx_rbtree_node_t   *rbtree_node_from_data(void *);


#define rbtree_data_from_node(node) ((void *)(&node[1]))
#define rbtree_node_from_data(data) (ngx_rbtree_node_t *)((u_char *)data - sizeof(ngx_rbtree_node_t))

#endif /*NCHAN_RBTREE_UTIL_HEADER*/