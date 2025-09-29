#ifndef CORE_H
# define CORE_H

# include <stddef.h>

typedef struct s_engine	t_engine;

int		engine_initialize(t_engine *engine, char *map_file);
int		engine_main_loop(t_engine *engine);
void	engine_update(t_engine *engine);
void	engine_shutdown(t_engine *engine);

void	*safe_malloc(size_t size);
void	*safe_calloc(size_t count, size_t size);
void	safe_free(void *ptr);

#endif
