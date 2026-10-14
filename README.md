# Codexion

*This project has been created as part of the 42 curriculum by aeuvrard.*

## Description

Codexion is a concurrency simulation written in C and relying on POSIX threads
(`pthread_create`, `pthread_mutex_t`, `pthread_cond_t`). A given number of coders
(`number_of_coders`) sit around a circular, inclusive co-working hub. Between
each pair of neighbouring coders there is exactly one USB dongle, so there are as
many dongles as coders, and compiling quantum code requires **two dongles at the
same time**: the one on the coder's left and the one on its right. Coders never
communicate with each other and do not know whether one of their neighbours is
about to burn out.

Each coder (represented by one thread) endlessly repeats the same cycle:

1. register a compilation request and wait until it is allowed to compile,
2. take its two dongles, then compile for `time_to_compile` ms,
3. put the dongles back on the table (they stay unavailable during
   `dongle_cooldown` ms),
4. debug for `time_to_debug` ms,
5. refactor for `time_to_refactor` ms,
6. go back to step 1.

If a coder does not *start* a new compilation within `time_to_burnout` ms after
the beginning of its last compilation (or after the beginning of the simulation
for the very first one), it burns out and the whole simulation stops. The
simulation also stops normally as soon as every coder has compiled at least
`number_of_compiles_required` times.

The **goal** of the project is to share a limited resource (the dongles) between
competing threads without any deadlock, without starving anyone and without
anyone burning out, using a scheduling policy chosen on the command line:

- `fifo` — First In, First Out: the dongle is granted to the coder whose request
  arrived first;
- `edf` — Earliest Deadline First: the dongle is granted to the coder whose
  deadline (`last_compile_start + time_to_burnout`) is the earliest.

A separate **monitor** thread permanently watches the coders, prints the burnout
message within 10 ms of the actual burnout and stops the simulation.

## Instructions

### Arguments

| Position | Name                          | Meaning |
|----------|-------------------------------|---------|
| 1        | `number_of_coders`            | Number of coders (and number of dongles). |
| 2        | `time_to_burnout`             | Milliseconds a coder can survive without starting a new compilation. |
| 3        | `time_to_compile`             | Milliseconds spent compiling. |
| 4        | `time_to_debug`               | Milliseconds spent debugging. |
| 5        | `time_to_refactor`            | Milliseconds spent refactoring. |
| 6        | `number_of_compiles_required` | How many compilations each coder must complete before the simulation stops. |
| 7        | `dongle_cooldown`             | Milliseconds a dongle stays unavailable after being released. |
| 8        | `scheduler`                   | `fifo` or `edf`. |

### Compilation

The project is compiled with `cc` and the flags
`-Wall -Wextra -Werror -pthread`:

```sh
make
```

### Execution

```sh
./codexion number_of_coders time_to_burnout time_to_compile \
    time_to_debug time_to_refactor number_of_compiles_required \
    dongle_cooldown scheduler
```

For example:

```sh
./codexion 4 5000 300 300 300 2 50 fifo
```

### Makefile rules

- `make` / `make all` — compile the mandatory part and produce `codexion`;
- `make clean` — remove the object files;
- `make fclean` — `clean` plus the executable;
- `make re` — `fclean` then `all`.

Extra convenience rules are provided: `make run` runs the program with the
default arguments, `make valgrind` runs it under Valgrind, `make helgrind`
runs it under Helgrind and `make help` lists the available rules.

### Log format

Every state change of a coder is printed on a single line as:

```text
timestamp_in_ms X has taken a dongle
timestamp_in_ms X is compiling
timestamp_in_ms X is debugging
timestamp_in_ms X is refactoring
timestamp_in_ms X burned out
```

where `X` is the coder id and the timestamp is in milliseconds since the
beginning of the simulation.


## Resources

- `man` pages: `pthread_create`, `pthread_join`, `pthread_mutex_init`,
  `pthread_mutex_lock`, `pthread_mutex_unlock`, `pthread_mutex_destroy`,
  `pthread_cond_init`, `pthread_cond_wait`, `pthread_cond_timedwait`,
  `pthread_cond_signal`, `pthread_cond_broadcast`, `pthread_cond_destroy`,
  `clock_gettime`, `nanosleep`, `usleep`.
- *Operating System Concepts* (Silberschatz, Galvin, Gagne) — chapters about
  thread synchronisation, mutexes, condition variables, deadlock, starvation
  and scheduling.
- Dijkstra's *Dining Philosophers* problem — the classic reference this
  simulation is based on.
- POSIX Threads documentation and the *Linux Programmer's Manual* (`pthreads(7)`).
- Documentation and tutorials found on Stack Overflow and 42 community threads
  about concurrency debugging.

### AI usage

AI was used as a support tool, never as a replacement for understanding. It was
used for:

- **Documentation and design**: discussing the difference between FIFO and EDF
  arbitration and how to model the request queue (the `t_heap` array of `t_ask`).
- **Concurrency review**: re-reading the locking strategy (the single arbiter
  mutex `mutex_ask` plus the condition variable `cond`, and the dedicated
  `log_mutex`) to check for missing locks and deadlock risks.
- **Debugging**: helping interpret Valgrind and Helgrind reports about data
  races, leaks and thread lifecycle.
- **Documentation**: getting clear explanations of `pthread_cond_wait` and
  `pthread_cond_broadcast` semantics.

Every AI-generated suggestion was reviewed, adapted to this codebase and
validated by the author with the `make valgrind` and `make helgrind` targets.


## Blocking cases handled

- **Deadlock prevention**: a single arbitration mutex (`mutex_ask`) protects both
  the request queue and the state of every dongle, and a coder takes its two
  dongles *atomically* while holding it. A coder never holds one dongle while
  waiting for the second one, so the circular-wait condition can never happen.
- **Starvation prevention**: requests are stored in a priority queue and the
  arbitration policy (`fifo` on `arrival_time`, `edf` on
  `last_compile_start + time_to_burnout`) always selects the most deserving
  waiting coder. `pthread_cond_broadcast` is called every time the queue or a
  dongle changes, so waiting coders are re-evaluated.
- **Cooldown handling**: after a compilation, `let_dongles` sleeps
  `dongle_cooldown` ms before flagging the two dongles as available again, so a
  just-released dongle cannot be grabbed immediately.
- **Precise burnout detection**: the monitor thread loops every millisecond
  (`usleep(1000)`) and compares `now - last_compile_start` with
  `time_to_burnout`, which keeps the burnout log within the required 10 ms.
- **Log serialization**: every `printf` is done while holding `log_mutex`, so
  two log lines can never interleave.
- **Normal termination**: the monitor detects when all coders have reached
  `number_of_compiles_required` and stops the simulation.
- **Single coder / same dongle**: when a coder has the same dongle on its left
  and on its right (only one coder, or a single dongle on the table), the
  waiting condition rejects it so it never tries to take the same dongle twice.
- **Parsing errors**: a wrong number of arguments, non-integer/negative values
  and an invalid scheduler are rejected before any allocation.
- **Clean exit**: `clean_up` stops the simulation, joins the monitor and the
  coder threads, destroys the mutex/condition variables and frees the heap,
  the coders and the dongles (no leaks, no `still reachable` blocks).

## Thread synchronization mechanisms

- `pthread_mutex_t mutex_ask` — global arbiter mutex. It protects the request
  queue (`data->heap`), the availability of every dongle, the `stopped` flag
  and per-coder data (`last_compile_start`, `nbr_compiles`).
- `pthread_cond_t cond` — condition variable associated with `mutex_ask`. A
  coder waits on it while it is not the coder selected by the scheduler or
  while one of its two dongles is still marked available. Every state change is
  followed by `pthread_cond_broadcast`, and `pthread_cond_wait` atomically
  releases `mutex_ask`.
- `pthread_mutex_t log_mutex` — dedicated mutex serializing all writes to
  standard output.
- **Monitor thread** — created in `create_thread_mutex`, it polls the coders
  under `mutex_ask` and signals the end of the simulation (burnout or
  completion). It communicates with the coders only through the shared state
  protected by `mutex_ask`/`cond`, which is what makes the communication
  thread-safe.
- **Time source** — `clock_gettime(CLOCK_MONOTONIC)` (`now_ms`) provides a
  monotonic clock; timestamps are relative to `data->start_time`.

### Race conditions prevented (examples)

- *Two coders requesting the same dongle*: both push a request under
  `mutex_ask`; only the coder returned by `algorithm()` leaves the wait loop
  and sets `available = 1` on both dongles while still holding `mutex_ask`, so
  no other coder can take one of them in between.
- *Monitor reading a coder's state while it compiles*: the monitor reads
  `nbr_compiles` and `last_compile_start`, and the coder updates them, always
  under `mutex_ask`, so no torn read can trigger a false burnout.
- *Two coders printing at the same time*: `log_mutex` guarantees that
  "has taken a dongle", "is compiling", … lines stay intact.
- *Stopping while a coder waits*: `stop_generation` sets `stopped` and
  broadcasts under `mutex_ask`; every woken coder re-checks `stopped` before
  doing anything, so no coder keeps taking resources after the end signal.

