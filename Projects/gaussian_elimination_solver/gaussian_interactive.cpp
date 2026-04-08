/*
╔══════════════════════════════════════════════════════════════════╗
║     INTERACTIVE GAUSSIAN ELIMINATION ENGINE — C++                ║
║     HE1MER Kernel | Professor Ajulo-Omojesu                      ║
║     User-Driven: 2×2 or 3×3 | Full ERO Pipeline                 ║
╚══════════════════════════════════════════════════════════════════╝

    Compile:  g++ -std=c++17 -o gaussian_interactive gaussian_interactive.cpp
    Run:      ./gaussian_interactive
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <limits>

// ─────────────────────────────────────────────
// TYPE ALIAS & CONSTANTS
// ─────────────────────────────────────────────
using Matrix = std::vector<std::vector<double>>;
const double EPSILON = 1e-10;

enum class Outcome {
    CONSISTENT_INDEPENDENT,
    CONSISTENT_DEPENDENT,
    INCONSISTENT
};


// ─────────────────────────────────────────────
// UTILITY FUNCTIONS
// ─────────────────────────────────────────────
void divider(char c = '=', int width = 58) {
    std::cout << "\n  ";
    for (int i = 0; i < width; i++) std::cout << c;
    std::cout << "\n";
}

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

// Safe float input — rejects non-numeric input
double getFloat(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cout << "  ⚠  Invalid input. Enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


// ─────────────────────────────────────────────
// ERO 1 — INTERCHANGE: Ri ↔ Rj
// ─────────────────────────────────────────────
void ero_interchange(Matrix& M, int i, int j) {
    std::cout << "\n  --> ERO 1 | INTERCHANGE: R" << i+1 << " <-> R" << j+1 << "\n";
    std::swap(M[i], M[j]);
}


// ─────────────────────────────────────────────
// ERO 2 — SCALING: k·Ri → Ri
// ─────────────────────────────────────────────
void ero_scale(Matrix& M, int i, double k) {
    std::cout << "\n  --> ERO 2 | SCALING: (" << std::fixed
              << std::setprecision(4) << k << ") x R" << i+1
              << " -> R" << i+1 << "\n";
    for (double& val : M[i]) val *= k;
}


// ─────────────────────────────────────────────
// ERO 3 — ROW ADDITION: k·Ri + Rj → Rj
// ─────────────────────────────────────────────
void ero_add(Matrix& M, int i, int j, double k) {
    std::cout << "\n  --> ERO 3 | ADDITION: (" << std::fixed
              << std::setprecision(4) << k << ") x R" << i+1
              << " + R" << j+1 << " -> R" << j+1 << "\n";
    for (int col = 0; col < (int)M[j].size(); col++)
        M[j][col] += k * M[i][col];
}


// ─────────────────────────────────────────────
// PHASE A — FORWARD ELIMINATION
// ─────────────────────────────────────────────
void forwardElimination(Matrix& M) {
    int n = (int)M.size();
    divider('=');
    std::cout << "  PHASE A -- FORWARD ELIMINATION\n";
    divider('=');

    for (int col = 0; col < n; col++) {
        std::cout << "\n  -- Pivot Column: " << col+1 << " --\n";

        // Partial pivot: find max row
        int maxRow = col;
        for (int row = col + 1; row < n; row++)
            if (std::abs(M[row][col]) > std::abs(M[maxRow][col]))
                maxRow = row;

        // ERO 1: Interchange if needed
        if (maxRow != col) {
            ero_interchange(M, col, maxRow);
            printMatrix(M, "After Interchange");
        }

        // Zero pivot check
        if (std::abs(M[col][col]) < EPSILON) {
            std::cout << "\n  [!] Zero pivot at column " << col+1 << ". Skipping.\n";
            continue;
        }

        // ERO 2: Scale to leading 1
        double pivot = M[col][col];
        if (std::abs(pivot - 1.0) > EPSILON) {
            ero_scale(M, col, 1.0 / pivot);
            printMatrix(M, "After Scaling");
        }

        // ERO 3: Eliminate entries below pivot
        for (int row = col + 1; row < n; row++) {
            if (std::abs(M[row][col]) > EPSILON) {
                double factor = -M[row][col];
                ero_add(M, col, row, factor);
                printMatrix(M, "After Addition");
            }
        }
    }
}


// ─────────────────────────────────────────────
// DIAGNOSTIC — SYSTEM CLASSIFICATION
// ─────────────────────────────────────────────
Outcome diagnose(const Matrix& M, int n) {
    divider('=');
    std::cout << "  DIAGNOSTIC: SYSTEM CLASSIFICATION\n";
    divider('=');

    int zeroRows = 0;

    for (const auto& row : M) {
        bool coeffsZero = true;
        for (int c = 0; c < n; c++) {
            if (std::abs(row[c]) > EPSILON) { coeffsZero = false; break; }
        }

        if (coeffsZero) {
            if (std::abs(row[n]) > EPSILON) {
                std::cout << R"(
  +-------------------------------------------------+
  |  OUTCOME: INCONSISTENT                          |
  |  A row reads  0 = non-zero  -- contradiction.   |
  |  --> No solution exists.                        |
  |  Geophysics flag: sensor conflict / bad data.   |
  +-------------------------------------------------+
)";
                return Outcome::INCONSISTENT;
            } else {
                zeroRows++;
            }
        }
    }

    if (zeroRows > 0) {
        std::cout << R"(
  +-------------------------------------------------+
  |  OUTCOME: CONSISTENT & DEPENDENT               |
  |  A row reads  0 = 0  -- redundant equation.    |
  |  --> Infinitely many solutions (free variable). |
  |  Geophysics flag: underdetermined model.        |
  +-------------------------------------------------+
)";
        return Outcome::CONSISTENT_DEPENDENT;
    }

    std::cout << R"(
  +-------------------------------------------------+
  |  OUTCOME: CONSISTENT & INDEPENDENT             |
  |  Every row has a unique pivot.                  |
  |  --> Exactly one solution exists.               |
  |  Geophysics flag: model fully resolved.         |
  +-------------------------------------------------+
)";
    return Outcome::CONSISTENT_INDEPENDENT;
}


// ─────────────────────────────────────────────
// PHASE B — BACKWARD SUBSTITUTION
// ─────────────────────────────────────────────
std::vector<double> backwardSubstitution(
    const Matrix& M,
    const std::vector<std::string>& varNames)
{
    int n = (int)M.size();
    std::vector<double> sol(n, 0.0);

    divider('=');
    std::cout << "  PHASE B -- BACKWARD SUBSTITUTION\n";
    divider('=');

    for (int row = n - 1; row >= 0; row--) {
        double rhs = M[row][n];
        for (int col = row + 1; col < n; col++)
            rhs -= M[row][col] * sol[col];

        double pivot = M[row][row];
        if (std::abs(pivot) > EPSILON) {
            sol[row] = rhs / pivot;
            std::cout << "\n  " << varNames[row] << " = "
                      << std::fixed << std::setprecision(4) << sol[row] << "\n";
        }
    }
    return sol;
}


// ─────────────────────────────────────────────
// INPUT: BUILD AUGMENTED MATRIX FROM USER
// ─────────────────────────────────────────────
Matrix buildMatrix(int n, const std::vector<std::string>& varNames) {
    Matrix M(n, std::vector<double>(n + 1));

    std::cout << "\n  Enter coefficients for each equation.\n\n";

    for (int eq = 0; eq < n; eq++) {
        std::cout << "  -- Equation " << eq + 1 << " --\n";
        for (int v = 0; v < n; v++) {
            M[eq][v] = getFloat("    Coefficient of " + varNames[v] + ": ");
        }
        M[eq][n] = getFloat("    Right-hand side (constant): ");
        std::cout << "\n";
    }
    return M;
}


// ─────────────────────────────────────────────
// DISPLAY SYSTEM AS EQUATIONS
// ─────────────────────────────────────────────
void displaySystem(const Matrix& M, const std::vector<std::string>& varNames, int n) {
    std::cout << "\n  Your system of equations:\n";
    for (int eq = 0; eq < n; eq++) {
        std::cout << "  ";
        for (int v = 0; v < n; v++) {
            std::cout << "(" << std::fixed << std::setprecision(2)
                      << M[eq][v] << ")" << varNames[v];
            if (v < n - 1) std::cout << " + ";
        }
        std::cout << " = " << std::fixed << std::setprecision(2) << M[eq][n] << "\n";
    }
}


// ─────────────────────────────────────────────
// ENTRY POINT
// ─────────────────────────────────────────────
int main() {

    std::cout << "\n";
    for (int i = 0; i < 60; i++) std::cout << "=";
    std::cout << "\n  GAUSSIAN ELIMINATION -- INTERACTIVE ENGINE\n";
    std::cout << "  HE1MER Learning Lab  |  Pristine Standard\n";
    for (int i = 0; i < 60; i++) std::cout << "=";
    std::cout << "\n";

    const std::vector<std::string> allVars = {"x", "y", "z"};

    char runAgain = 'y';
    while (runAgain == 'y' || runAgain == 'Y') {

        // ── STEP 1: Choose dimension ──
        divider('-');
        std::cout << "\n  SELECT MATRIX DIMENSION:\n\n";
        std::cout << "    [1]  2x2  (variables: x, y)\n";
        std::cout << "    [2]  3x3  (variables: x, y, z)\n";
        std::cout << "    [0]  Exit\n\n";
        std::cout << "  Your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) {
            std::cout << "\n  Engine closed. Execute with precision.\n\n";
            break;
        }

        int n;
        if (choice == 1)      n = 2;
        else if (choice == 2) n = 3;
        else {
            std::cout << "  [!] Invalid choice. Enter 1, 2, or 0.\n";
            continue;
        }

        std::cout << "\n  Selected: " << n << "x" << n << " system\n";

        std::vector<std::string> varNames(allVars.begin(), allVars.begin() + n);

        // ── STEP 2: Get coefficients ──
        Matrix input = buildMatrix(n, varNames);
        displaySystem(input, varNames, n);

        // ── STEP 3: Confirm ──
        std::cout << "\n  Proceed with elimination? (y/n): ";
        char confirm;
        std::cin >> confirm;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (confirm != 'y' && confirm != 'Y') {
            std::cout << "  Restarting...\n";
            continue;
        }

        // ── STEP 4: Run elimination ──
        Matrix M = input;   // working copy

        divider('=');
        std::cout << "  GAUSSIAN ELIMINATION ENGINE -- RUNNING\n";
        divider('=');

        printMatrix(M, "INITIAL AUGMENTED MATRIX");
        forwardElimination(M);

        divider('-');
        printMatrix(M, "FINAL ROW ECHELON FORM (REF)");

        Outcome result = diagnose(M, n);

        if (result == Outcome::CONSISTENT_INDEPENDENT) {
            auto sol = backwardSubstitution(M, varNames);

            divider('=');
            std::cout << "  FINAL SOLUTION\n";
            divider('=');
            for (int i = 0; i < n; i++)
                std::cout << "  " << varNames[i] << " = "
                          << std::fixed << std::setprecision(4) << sol[i] << "\n";

            // Verification
            std::cout << "\n  VERIFICATION:\n";
            for (int eq = 0; eq < n; eq++) {
                double computed = 0.0;
                for (int v = 0; v < n; v++)
                    computed += input[eq][v] * sol[v];
                std::string status = (std::abs(computed - input[eq][n]) < 1e-6) ? "[OK]" : "[FAIL]";
                std::cout << "  Equation " << eq+1 << ": "
                          << std::fixed << std::setprecision(4) << computed
                          << " = " << input[eq][n] << "  " << status << "\n";
            }
        }

        // ── Repeat? ──
        std::cout << "\n  Solve another system? (y/n): ";
        std::cin >> runAgain;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (runAgain != 'y' && runAgain != 'Y') {
        std::cout << "\n  Engine closed. Execute with precision.\n\n";
    }

    return 0;
}
