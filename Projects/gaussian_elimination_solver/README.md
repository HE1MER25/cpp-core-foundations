---

### **Template 2: C++ Solver (The "Performance & Logic" Approach)**

```markdown
# Matrix Logic Engine - C++ Edition
### *High-Performance Linear Algebra Implementation*

## 📌 Overview
A robust C++ implementation of the **Gaussian Elimination** method. This project focuses on manual memory management and nested loop logic to perform Row Equivalent Operations (REOs).

## 🛠 Technical Highlights
* **Nested Loop Execution:** Uses optimized loops to perform row scaling and subtraction.
* **Precision Control:** Handles floating-point arithmetic to ensure "Pristine" output for fractional results.
* **Algorithmic Flow:**
    1. Forward Elimination (Upper Triangular Conversion).
    2. Diagnostic check for Row Health.
    3. Back Substitution.

## 🚀 Compilation & Execution
Use a C++ compiler (like G++) to build the executable:
```bash
g++ solver.cpp -o solver
./solver