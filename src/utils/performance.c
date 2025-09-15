#include "cub3d.h"
#include <sys/time.h>

typedef struct s_perf_monitor
{
	struct timeval	start_time;
	struct timeval	end_time;
	long			frame_count;
	long			total_render_time;
	double			avg_fps;
	double			current_fps;
}	t_perf_monitor;

static t_perf_monitor	g_perf = {0};

void	perf_start_frame(void)
{
	gettimeofday(&g_perf.start_time, NULL);
}

void	perf_end_frame(void)
{
	long	frame_time;

	gettimeofday(&g_perf.end_time, NULL);
	frame_time = (g_perf.end_time.tv_sec - g_perf.start_time.tv_sec) * 1000000;
	frame_time += (g_perf.end_time.tv_usec - g_perf.start_time.tv_usec);
	g_perf.total_render_time += frame_time;
	g_perf.frame_count++;
	if (frame_time > 0)
		g_perf.current_fps = 1000000.0 / frame_time;
	if (g_perf.frame_count % 60 == 0 && g_perf.total_render_time > 0)
	{
		g_perf.avg_fps = (60.0 * 1000000.0) / g_perf.total_render_time;
		g_perf.total_render_time = 0;
	}
}

double	perf_get_current_fps(void)
{
	return (g_perf.current_fps);
}

double	perf_get_average_fps(void)
{
	return (g_perf.avg_fps);
}

long	perf_get_frame_count(void)
{
	return (g_perf.frame_count);
}

void	perf_reset_stats(void)
{
	g_perf.frame_count = 0;
	g_perf.total_render_time = 0;
	g_perf.avg_fps = 0.0;
	g_perf.current_fps = 0.0;
}