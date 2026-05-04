# PAX - OEF & WIMS Engine Context

## Current Status (May 4th, 2026)
- **Unified Parsing**: Replaced manual OEF parsing with a robust **Lark-based AST parser (V9)** in `backend/core/oef/parser.py`.
- **AST Evaluation**: `OEFEvaluator` now traverses the AST directly, supporting nested structures, complex logic, and math expressions.
- **DefEngine (New Core)**: Introduced a sophisticated engine for compiled WIMS `.def` scripts (`backend/core/oef/def_engine.py`).
    - Full interpreter for WIMS script commands (`!if`, `!for`, `!readproc`, etc.).
    - CAS integration: Uses **SymPy** as a drop-in replacement for Maxima/Pari/GP operations.
    - Slib support: Executing shared WIMS library scripts.
- **Flydraw Renderer**: Re-implemented WIMS' vector drawing language in `backend/core/oef/flydraw.py`, producing high-quality inline SVGs.
- **Robust Answer Checking**: `backend/core/answer/checkers.py` uses SymPy for symbolic, algebraic, and formal equivalence verification.

## Key Components
- **`parser.py` / `evaluator.py`**: EBNF grammar and recursive evaluator for `.oef` source files.
- **`def_parser.py` / `def_engine.py`**: Parser and execution engine for pre-compiled WIMS scripts.
- **`engine.py`**: High-level dispatcher that favors the compiled `.def` pipeline when available.
- **`flydraw.py`**: Vector graphics engine with support for flood fill and function plotting.

## Next Steps
- [ ] **Sandboxing**: Implement a secure runner for profesor-defined code to prevent arbitrary execution.
- [ ] **Performance**: Optimize the SymPy-based CAS calls (caching, process pooling).
- [ ] **Frontend Integration**: Enhance the Nuxt 3 exercise player with more interactive handlers (Drag & Drop, D3.js).
- [ ] **Validation**: Increase test coverage for the edge cases identified in the large exercise corpus (H4 level).

## Technical Notes
- **ID System**: Exercises are identified by **path slugs** (e.g., `ressources~H4~algebra~complex.oef`) for determinism across environments.
- **Encoding**: Handles both UTF-8 and ISO-8859-1 (Latin-1) legacy files automatically.
- **Math**: KaTeX is used for client-side rendering; the backend prepares LaTeX strings using SymPy and custom normalization.

