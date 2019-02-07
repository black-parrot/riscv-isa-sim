#ifndef EXTRA_H
#define EXTRA_H

typedef struct {
bool on_cycle=false;
bool on_pc=false;
long stop_pc;
long stop_cycle=0;
long cur_cycle=0;
} stop_t;

#endif

