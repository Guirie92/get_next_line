/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:18:59 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/24 22:33:01 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMING_H
# define TIMING_H

# include <time.h>
# include <stdint.h>

# ifndef TIMING_ENABLED
#  define TIMING_ENABLED 1
# endif

typedef struct s_timing
{
	struct timespec	start;
	struct timespec	end;
}	t_timing;

static inline void timing_start(t_timing *t)
{
    clock_gettime(CLOCK_MONOTONIC, &t->start);
}

static inline void timing_stop(t_timing *t)
{
    clock_gettime(CLOCK_MONOTONIC, &t->end);
}

/* 
 * Elapsed time in seconds (caller must ensure stop() was called,
 * otherwise values undefined)
 */
static inline double timing_elapsed_sec(const t_timing *t)
{
    return ((t->end.tv_sec - t->start.tv_sec)
            + (t->end.tv_nsec - t->start.tv_nsec) / 1e9);
}

static inline double timing_elapsed_ms(const t_timing *t)
{
    return timing_elapsed_sec(t) * 1000.0;
}

static inline double timing_elapsed_us(const t_timing *t)
{
    return timing_elapsed_sec(t) * 1e6;
}

# if TIMING_ENABLED

#  define TIMING_DECLARE(name) t_timing	name
#  define TIMING_PTR(name) (&(name))
#  define TIMING_START(name) do { timing_start(&(name)); } while (0)
#  define TIMING_STOP(name) do { timing_stop(&(name)); } while (0)

# else

#define TIMING_DECLARE(name) /* nothing */
#define TIMING_PTR(name) ((void*)0)
#define TIMING_START(name) ((void)0)
#define TIMING_STOP(name)  ((void)0)

# endif // TIMING_ENABLED


/* ------------------- logging hook -------------------- */
/* Prefer LOG_PRINT (from logging.h), otherwise fallback */
#ifndef TIMING_PRINTF
  #ifdef LOG_PRINT
    #define TIMING_PRINTF(fmt, ...) LOG_PRINT(fmt, ##__VA_ARGS__)
  #else
    #include <stdio.h>
    #define TIMING_PRINTF(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
  #endif
#endif

/* Default TIMING_LOG uses milliseconds */
#define TIMING_LOG(name, fmt, ...) TIMING_LOG_MS((name), (fmt), ##__VA_ARGS__)

/* Milliseconds: call timing_elapsed_ms once inline */
#define TIMING_LOG_MS(name, fmt, ...)                                                   \
    do {                                                                                \
        TIMING_PRINTF((fmt " (%.3f ms)\n"), ##__VA_ARGS__, timing_elapsed_ms(&(name))); \
    } while (0)

/* Seconds */
#define TIMING_LOG_SEC(name, fmt, ...)                                                  \
    do {                                                                                \
        TIMING_PRINTF((fmt " (%.2f s)\n"), ##__VA_ARGS__, timing_elapsed_sec(&(name))); \
    } while (0)

/* Seconds & milliseconds */
#define TIMING_LOG_SEC_MS(name, fmt, ...)                                               \
    do {                                                                                \
        TIMING_PRINTF((fmt " (%.2f s) (%.3f ms)\n"), ##__VA_ARGS__,                     \
        timing_elapsed_sec(&(name)), timing_elapsed_ms(&(name)));                       \
    } while (0)

/* Nanoseconds (approx, from elapsed seconds) */
#define TIMING_LOG_NS(name, fmt, ...)                                                   \
    do {                                                                                \
        long long _tim_ns_val = (long long)(timing_elapsed_sec(&(name)) * 1e9);         \
        TIMING_PRINTF((fmt " (%lld ns)\n"), ##__VA_ARGS__, _tim_ns_val);                \
    } while (0)

	

#endif // TIMING_H