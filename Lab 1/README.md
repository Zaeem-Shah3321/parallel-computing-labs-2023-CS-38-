# 🚀 Lab 1: From Shared Memory to Distributed Memory with MPI

## 📌 Overview

This lab introduces **distributed-memory programming** using **MPI (Message Passing Interface)**. It builds on Lab 0 by reimplementing the counting problem (target number **42** in **100 million integers**) using MPI.

The lab highlights the **differences, trade-offs, and performance implications** between shared-memory (Pthreads) and distributed-memory systems.

---

## 🎯 Learning Objectives

By completing this lab, we aim to:

* Understand limitations of **shared-memory systems**
* Learn **MPI programming model** (SPMD, ranks, communicators)
* Implement MPI programs in C
* Use **point-to-point communication** (MPI_Send, MPI_Recv)
* Use **collective communication** (MPI_Bcast, MPI_Reduce)
* Compare MPI performance with **Pthreads (Lab 0)**
* Analyse communication overhead using **ping-pong program**

---

## 📂 Files

* `hello_mpi.c` – Basic MPI program (rank & size display)
* `pingpong.c` – Measures communication latency
* `count_mpi.c` – Parallel counting using MPI
* `graph.py` – To Make Speed Up Graphs

---

## ⚙️ Compilation and Execution

### 🟢 MPI Programs

```bash id="n8k2pz"
mpicc -O2 -o hello_mpi hello_mpi.c
mpirun --oversubscribe -np 4 --mca btl self,vader ./hello_mpi

mpicc -O2 -o pingpong pingpong.c
mpirun --oversubscribe -np 2 --mca btl self,vader ./pingpong

mpicc -O2 -o count_mpi count_mpi.c
mpirun --oversubscribe -np 4 --mca btl self,vader ./count_mpi
```

---

## 📊 Execution Time Comparison

| Implementation | Configuration | Time (s) | Speedup |
| -------------- | ------------- | -------- | ------- |
| MPI Counting   | 1 Process     | 0.205993 | 1.00x   |
| MPI Counting   | 2 Processes   | 0.095059 | 2.17x   |
| MPI Counting   | 4 Processes   | 0.168332 | 1.22x   |
| MPI Counting   | 8 Processes   | 0.094461 | 2.18x   |

---

## 🔍 Key Observations

* Best performance achieved with **2 processes** due to lower overhead
* Performance drops at 4 processes due to **communication cost**
* MPI is less efficient than Pthreads on a **single machine**
* Message passing introduces **extra overhead** compared to shared memory

---

## 🧠 Theoretical Concepts

### 🔹 Shared vs Distributed Memory

* **Shared Memory:** Same RAM, fast communication, limited scalability
* **Distributed Memory:** Separate memory, message passing, highly scalable

### 🔹 SPMD Model

* Single Program runs on multiple processes
* Each process works on **different data (based on rank)**

### 🔹 Collective Communication

* `MPI_Bcast` → Send data to all processes
* `MPI_Reduce` → Combine results from all processes

### 🔹 Amdahl’s Law

* Limits maximum speedup due to sequential portion
* Example: 95% parallel → max speedup ≈ **6.2x** on 8 processors

---

## ⚠️ Challenges Faced & Solutions

### 🔸 Deadlocks

* **Problem:** Both processes waiting on send/receive
* **Solution:** Correct ordering or use `MPI_Sendrecv`

### 🔸 Mismatched Tags/Ranks

* **Problem:** Messages not received properly
* **Solution:** Carefully match send/receive parameters

### 🔸 Missing Collective Calls

* **Problem:** Program hangs
* **Solution:** Ensure all processes call collective functions

### 🔸 Integer Overflow

* **Problem:** Large data size overflow
* **Solution:** Use `long` data type

### 🔸 Incorrect Timing

* **Problem:** Printing affects performance measurement
* **Solution:** Remove `printf` from timing loops

---

## ❓ Self-Assessment Questions

1. **Limitations of shared memory?**
   Limited to one machine, restricted by cores and RAM

2. **SPMD model?**
   Same program runs on all processes with different data

3. **Why generate data locally?**
   Avoid large communication overhead

4. **Missing MPI_Bcast effect?**
   Incorrect or undefined results

5. **MPI vs Pthreads speed?**
   MPI slower due to message passing overhead

6. **Message size vs time?**
   Small → latency, Large → bandwidth

7. **Amdahl’s Law result?**
   Max speedup ≈ 6.2x

8. **Why MPI less efficient?**
   Communication + process overhead

9. **Scatter vs local generation?**
   Trade-off between memory and communication

10. **Large cluster usage?**
    Use hybrid model (MPI + Threads)

---

## 🧾 Reflection

This lab demonstrated a major shift from **shared-memory programming (Pthreads)** to **distributed-memory programming (MPI)**. Unlike threads, MPI processes do not share memory, requiring explicit communication.

Initially, managing message passing was challenging, especially avoiding deadlocks and ensuring correct communication. One key learning was that increasing processes does not always improve performance due to communication overhead.

The most interesting observation was that **2 processes performed better than 4**, highlighting the cost of communication. Overall, this lab provided valuable insight into how distributed systems scale and the importance of efficient communication design.

---

## 👨‍💻 Author

**Syed M. Zaeem**
GitHub: https://github.com/Zaeem-Shah3321
