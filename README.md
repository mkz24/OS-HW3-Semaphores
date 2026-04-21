# OS Homework 3: Semaphores for Competition and Cooperation
**Operating Systems | Roya Hosseini | Spring 2026**

---

## Part 1: Process Competition — Shared Counter with a Binary Semaphore

**Goal:** Protect a shared variable so two threads do not update it at the same time.

### File: `part1_shared_counter.c`

**Compile and Run:**
```bash
gcc -o part1 part1_shared_counter.c -lpthread
./part1
```

**Sample Output:**
```
Final counter value: 200000
```

### Explanation
- The semaphore is needed because both threads share the same variable `counter`. Without it, a race condition occurs and the final value may be less than 200000.
- If removed, both threads may read and update `counter` at the same time, giving an incorrect result.

---

## Part 2: Process Cooperation — Producer-Consumer with Semaphores

**Goal:** Use semaphores to coordinate a producer and a consumer sharing a buffer.

### File: `part2_producer_consumer.c`

**Compile and Run:**
```bash
gcc -o part2 part2_producer_consumer.c -lpthread
./part2
```

**Sample Output:**
```
Produced: 1 at position 0
Produced: 2 at position 1
Consumed: 1 from position 0
Produced: 3 at position 2
Consumed: 2 from position 1
...
Produced: 10 at position 4
Consumed: 10 from position 4
```

### Role of Each Semaphore
| Semaphore | Role |
|-----------|------|
| `empty` | Counts empty slots in the buffer. Producer waits if buffer is full. |
| `full` | Counts filled slots in the buffer. Consumer waits if buffer is empty. |
| `mutex` | Protects the buffer. Only one thread can access it at a time. |

### What Happens if Removed
| Semaphore Removed | Problem |
|-------------------|---------|
| `empty` | Producer overflows the buffer (writes to full buffer). |
| `full` | Consumer reads from empty buffer (invalid data/underflow). |
| `mutex` | Race condition — both threads access buffer simultaneously, corrupting data. |
