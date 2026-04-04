#ifndef OSEK_PRIORITY_INTERLEAVING_TASKS_H
#define OSEK_PRIORITY_INTERLEAVING_TASKS_H

#include "../osek/osek_api.h"

TASK(controller);
TASK(worker);
TASK(cleanup);

#endif
