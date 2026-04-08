/*
╔══════════════════════════════════════════════════════════════════╗
║       GAUSSIAN ELIMINATION ENGINE — C++ IMPLEMENTATION           ║
║       HE1MER Kernel | Professor Ajulo-Omojesu                    ║
║       All EROs Present: Interchange | Scaling | Addition         ║
╚══════════════════════════════════════════════════════════════════╝

    Compile:  g++ -std=c++17 -o gaussian gaussian_elimination.cpp
    Run:      ./gaussian
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>

// ─────────────────────────────────────────────
// TYPE ALIAS & CONSTANTS
// ─────────────────────────────────────────────
using Matrix = std::vector<std::vector<double>>;
const double EPSILON = 1e-10;

// ─────────────────────────────────────────────
// OUTCOME ENUM — System Classification
// ─────────────────────────────────────────────
enum class Outcome {
    CONSISTENT_INDEPENDENT,   // Unique solution
    CONSISTENT_DEPENDENT,     // Infinite solutions
    INCONSISTENT              // No solution
};


// ─────────────────────────────────────────────
// UTILITY: PRINT MATRIX
// ─────────────────────────────────────────────
void printMatrix(const Matrix& M, const std::string& label = "") {
    if (!label.empty())
        std::cout << "\n  [" << label << "]\n";
    for (const auto& row : M) {
        std::cout << "  [ ";
        for (double val : row)
            std::cout << std::setw(10) << std::fixed << std::setprecision(4) << val << "  ";
        std::cout << "]\n";
    }
}

void printDivider(char c = '=', int width = 60) {
    std::cout << "\n  ";
    for (int i = 0; i < width; i++) std::cout << c;
    std::cout << "\n";
}


// ─────────────────────────────────────────────
// ERO 1 — INTERCHANGE: Ri ↔ Rj
// ─────────────────────────────────────────────
void ero_interchange(Matrix& M, int i, int j) {
    std::cout << "\n  ⟶ ERO 1 | INTERCHANGE: R" << i+1 << " ↔ R" << j+1 << "\n";
    std::swap(M[i], M[j]);
}


// ─────────────────────────────────────────────
// ERO 2 — SCALING: k·Ri → Ri
// ─────────────────────────────────────────────
void ero_scale(Matrix& M, int i, double k) {
    std::cout << "\n  ⟶ ERO 2 | SCALING: (" << k << ") × R" << i+1 << " → R" << i+1 << "\n";
    for (double& val : M[i])
        val *= k;
}


// ─────────────────────────────────────────────
// ERO 3 — ROW ADDITION: k·Ri + Rj → Rj
// ─────────────────────────────────────────────
void ero_add(Matrix& M, int i, int j, double k) {
    std::cout << "\n  ⟶ ERO 3 | ADDITION: (" << k << ") × R" << i+1
              << " + R" << j+1 << " → R" << j+1 << "\n";
    for (int col = 0; col < (int)M[j].size(); col++)
        M[j][col] += k * M[i][col];
}


// ─────────────────────────────────────────────
// PHASE A — FORWARD ELIMINATION
// ─────────────────────────────────────────────
void forwardElimination(Matrix& M) {
    int n = M.size();

    printDivider('=');
    std::cout << "  PHASE A — FORWARD ELIMINATION\n";
    printDivider('=');

    for (int col = 0; col < n; col++) {
        std::cout << "\n  ── Pivot Column: " << col+1 << " ──\n";

        // Partial pivoting: find row with largest absolute value in this column
        int maxRow = col;
        for (int row = col + 1; row < n; row++) {
            if (std::abs(M[row][col]) > std::abs(M[maxRow][col]))
                maxRow = row;
        }

        // ERO 1: Interchange if a better pivot is found below
        if (maxRow != col) {
            ero_interchange(M, col, maxRow);
            printMatrix(M, "After Interchange");
        }

        // Check for zero pivot
        if (std::abs(M[col][col]) < EPSILON) {
            std::cout << "\n  ⚠ Zero pivot at column " << col+1 << ". Skipping.\n";
            continue;
        }

        // ERO 2: Scale row to get leading 1
        double pivot = M[col][col];
        if (std::abs(pivot - 1.0) > EPSILON) {
            ero_scale(M, col, 1.0 / pivot);
            printMatrix(M, "After Scaling");
        }

        // ERO 3: Eliminate all entries below the pivot
        for (int row = col + 1; row < n; row++) {
            if (std::abs(M[row][col]) > EPSILON) {
                double factor = -M[row][col];
                ero_add(M, col, row, factor);
                std::cout << "  Eliminating R" << row+1 << ", Col " << col+1 << "\n";
                printMatrix(M, "After Addition");
            }
        }
    }
}


// ─────────────────────────────────────────────
// DIAGNOSTIC ENGINE — OUTCOME INTERPRETATION
// ─────────────────────────────────────────────
Outcome interpretOutcome(const Matrix& M) {
    int n = M.size();

    printDivider('=');
    std::cout << "  DIAGNOSTIC: SYSTEM CLASSIFICATION\n";
    printDivider('=');

    int zeroRows = 0;

    for (const auto& row : M) {
        bool allZeroCoeffs = true;
        for (int col = 0; col < n; col++) {
            if (std::abs(row[col]) > EPSILON) {
                allZeroCoeffs = false;
                break;
            }
        }

        if (allZeroCoeffs) {
            double rhs = row[n];

            if (std::abs(rhs) > EPSILON) {
                // INCONSISTENT
                std::cout << R"(
  ┌─────────────────────────────────────────┐
  │  OUTCOME: INCONSISTENT SYSTEM           │
  │  Row reads: 0 = non-zero value          │
  │  This is a mathematical contradiction.  │
  │  → No solution exists.                  │
  │  In geophysics: sensor conflict or      │
  │    corrupted field data detected.       │
  └─────────────────────────────────────────┘
)";
                return Outcome::INCONSISTENT;
            } else {
                zeroRows++;
            }
        }
    }

    if (zeroRows > 0) {
        // CONSISTENT & DEPENDENT
        std::cout << R"(
  ┌──────────────────────────────────────────────┐
  │  OUTCOME: CONSISTENT & DEPENDENT             │
  │  Row reads: 0 = 0  (redundant equation)      │
  │  → Infinitely many solutions exist.          │
  │  System has at least one free variable.      │
  │  In geophysics: insufficient measurements — │
  │    model is underdetermined.                 │
  └──────────────────────────────────────────────┘
)";
        return Outcome::CONSISTENT_DEPENDENT;
    }

    // CONSISTENT & INDEPENDENT
    std::cout << R"(
  ┌──────────────────────────────────────────────┐
  │  OUTCOME: CONSISTENT & INDEPENDENT           │
  │  Unique pivot in every row.                  │
  │  → Exactly one solution exists.              │
  │  System is fully determined.                 │
  │  In geophysics: clean delineation result —  │
  │    subsurface model resolved precisely.      │
  └──────────────────────────────────────────────┘
)";
    return Outcome::CONSISTENT_INDEPENDENT;
}


// ─────────────────────────────────────────────
// PHASE B — BACKWARD SUBSTITUTION
// ─────────────────────────────────────────────
std::vector<double> backwardSubstitution(const Matrix& M) {
    int n = M.size();
    std::vector<double> solution(n, 0.0);

    printDivider('=');
    std::cout << "  PHASE B — BACKWARD SUBSTITUTION\n";
    printDivider('=');

    for (int row = n - 1; row >= 0; row--) {
        double rhs = M[row][n];

        // Subtract already-known variables
        for (int col = row + 1; col < n; col++)
            rhs -= M[row][col] * solution[col];

        double pivot = M[row][row];
        if (std::abs(pivot) > EPSILON) {
            solution[row] = rhs / pivot;
            std::cout << "\n  Variable x" << row+1
                      << " = " << std::fixed << std::setprecision(4)
                      << solution[row] << "\n";
        }
    }

    return solution;
}


// ─────────────────────────────────────────────
// MAIN GAUSSIAN ENGINE
// ─────────────────────────────────────────────
void gaussianElimination(Matrix matrix, const std::string& testLabel) {
    std::cout << "\n\n";
    for (int i = 0; i < 60; i++) std::cout << "█";
    std::cout << "\n  " << testLabel << "\n";
    for (int i = 0; i < 60; i++) std::cout << "█";
    std::cout << "\n";

    printMatrix(matrix, "INITIAL AUGMENTED MATRIX");

    // Phase A
    forwardElimination(matrix);

    printDivider('-');
    printMatrix(matrix, "FINAL ROW ECHELON FORM (REF)");

    // Diagnostic
    Outcome result = interpretOutcome(matrix);

    // Phase B — only if unique solution exists
    if (result == Outcome::CONSISTENT_INDEPENDENT) {
        auto solution = backwardSubstitution(matrix);

        printDivider('*');
        std::cout << "  FINAL SOLUTION\n";
        printDivider('*');
        for (int i = 0; i < (int)solution.size(); i++)
            std::cout << "  x" << i+1 << " = "
                      << std::fixed << std::setprecision(4)
                      << solution[i] << "\n";
        std::cout << "\n";
    }
}


// ─────────────────────────────────────────────
// ENTRY POINT — TEST CASES
// ─────────────────────────────────────────────
int main() {

    // ── TEST 1: CONSISTENT & INDEPENDENT ──
    Matrix A1 = {
        {1, 1, 1,  6},
        {2, 3, 1, 14},
        {1, 2, 3, 14}
    };
    gaussianElimination(A1,
        "TEST 1: CONSISTENT & INDEPENDENT | x+y+z=6, 2x+3y+z=14, x+2y+3z=14");


    // ── TEST 2: INCONSISTENT ──
    Matrix A2 = {
        {1, 1, 3},
        {1, 1, 5}
    };
    gaussianElimination(A2,
        "TEST 2: INCONSISTENT | x+y=3, x+y=5");


    // ── TEST 3: CONSISTENT & DEPENDENT ──
    Matrix A3 = {
        {1, 1, 4},
        {2, 2, 8}
    };
    gaussianElimination(A3,
        "TEST 3: CONSISTENT & DEPENDENT | x+y=4, 2x+2y=8");


    return 0;
}
