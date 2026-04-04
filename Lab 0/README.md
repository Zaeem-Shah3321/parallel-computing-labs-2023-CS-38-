# 🚀 Lab 0: Foundations of Parallel Computing – Threads, Processes, and Linux Tools

## 📌 Overview

This lab introduces the fundamentals of **parallel computing**, focusing on the use of **threads, processes, and Linux tools**.

The lab includes both **theoretical understanding** and **practical implementation** of sequential and parallel programs in C and Python. A key task is counting occurrences of a target number (**42**) in a large dataset of **100 million integers** to analyse performance differences.

---

## 🎯 Learning Objectives

By completing this lab, we aim to:

* Understand the shift from single-core to **multi-core processors**
* Differentiate between **processes and threads**
* Learn **concurrency vs parallelism**
* Implement **sequential and parallel programs**
* Use **Pthreads (C)** and **threading/multiprocessing (Python)**
* Analyse performance using **execution time and speedup**
* Understand **race conditions, mutex, and GIL**

---

## 📂 Files

* `count_seq.c` – Sequential counting in C
* `count_pthread.c` – Parallel counting in C using pthreads
* `count_seq.py` – Sequential counting in Python
* `count_threads.py` – Python threading (GIL demonstration)
* `count_mp.py` – Python multiprocessing (true parallelism)

---

## ⚙️ Compilation and Execution

### 🟢 C Programs

```bash
gcc -O2 -o count_seq count_seq.c
./count_seq

gcc -O2 -pthread -o count_pthread count_pthread.c
./count_pthread
```

### 🐍 Python Programs

```bash
python3 count_seq.py
python3 count_threads.py
python3 count_mp.py
```

---

## 📊 Execution Time Comparison

| Implementation         | Configuration | Time (s) | Speedup |
| ---------------------- | ------------- | -------- | ------- |
| C Sequential           | 1 Thread      | 0.30     | 1.00x   |
| C Pthreads             | 2 Threads     | 0.16     | 1.88x   |
| C Pthreads             | 4 Threads     | 0.10     | 3.00x   |
| C Pthreads             | 8 Threads     | 0.08     | 3.75x   |
| Python Sequential      | 1 Thread      | 8.80     | 1.00x   |
| Python Threads         | 4 Threads     | 9.00     | 0.98x   |
| Python Multiprocessing | 4 Processes   | 3.50     | 2.51x   |

---

## 🔍 Key Observations

* C is significantly faster than Python for CPU-bound tasks
* Pthreads provide **good but sub-linear speedup**
* Python threading is slower due to **Global Interpreter Lock (GIL)**
* Multiprocessing improves performance by enabling **true parallelism**

---

## 🧠 Theoretical Concepts

### 🔹 Processes vs Threads

* **Process:** Independent memory space, heavier
* **Thread:** Shared memory, lightweight but needs synchronization

### 🔹 Concurrency vs Parallelism

* **Concurrency:** Managing multiple tasks
* **Parallelism:** Executing tasks simultaneously

### 🔹 GIL (Global Interpreter Lock)

* Allows only one Python thread to execute at a time
* Prevents true parallelism in CPU-bound tasks

### 🔹 Amdahl’s Law

* Limits maximum speedup due to sequential portion of code

---

## ⚠️ Challenges Faced & Solutions

### 🔸 Race Conditions

* **Problem:** Incorrect results due to shared variable access
* **Solution:** Used **mutex locks**

### 🔸 Python GIL

* **Problem:** Threads not running in parallel
* **Solution:** Used multiprocessing

### 🔸 Memory Management (C)

* **Problem:** Handling large arrays
* **Solution:** Proper use of `malloc` and `free`

### 🔸 Load Balancing

* **Problem:** Unequal workload distribution
* **Solution:** Adjusted last thread’s range

### 🔸 Mutex Overhead

* **Problem:** Performance slowdown
* **Solution:** Used local counters

### 🔸 False Sharing

* **Problem:** Cache inefficiency
* **Solution:** Used private thread variables

---

## ❓ Self-Assessment Questions

1. **Difference between process and thread?**
   Processes have separate memory; threads share memory.

2. **Why use mutex?**
   To prevent race conditions during shared updates.

3. **Why speedup is not linear?**
   Due to overhead, memory limits, and Amdahl’s Law.

4. **Why Python threads are slow?**
   Because of the GIL.

5. **When to use threads vs processes?**
   Threads for I/O tasks, processes for CPU-bound tasks.

---

## 🧾 Reflection

This lab provided practical insight into parallel programming. While the problem seemed simple initially, implementing it in a parallel environment introduced challenges like race conditions and synchronization. Using mutex locks ensured correctness but introduced overhead.

C implementations showed significant performance improvements with threads, although the speedup was not perfectly linear due to system limitations. Python threading performed poorly because of the GIL, but multiprocessing demonstrated better results by enabling real parallel execution.

Overall, this lab highlighted that parallel programming improves performance but requires careful design, efficient synchronization, and understanding of system-level constraints.

---

## 👨‍💻 Author

**Syed M. Zaeem**
GitHub: https://github.com/Zaeem-Shah3321
