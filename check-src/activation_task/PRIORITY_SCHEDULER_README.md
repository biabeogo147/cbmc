### 1. Configuration File

```json
{
  "tasks": {
    "taskA": 10,
    "taskB": 5,
    "taskC": 1
  }
}
```

Alternative format (direct mapping):
```json
{
  "taskA": 10,
  "taskB": 5,
  "taskC": 1
}
```

### 2. Command Line Option

Use the `--task-priority-json` option to specify the configuration file:

```bash
esbmc check-src/activation_task/test_priority_schedule_x.c --task-priority-json check-src/activation_task/task_priorities.json
```

### 3. ActivationTask Intrinsic

Use the `__ESBMC_activation_task` intrinsic to create prioritized tasks.