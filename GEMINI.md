# PAX - OEF Parser Integration Context

## Current Status (May 1st, 2026)
- **Feature**: Replaced the legacy manual OEF parser with a robust **Lark-based parser (V9)**.
- **Location**: `backend/core/oef/parser.py` (Parser) and `backend/core/oef/evaluator.py` (AST Evaluation).
- **Achievements**:
    - Unified parsing: One pass generates a full Abstract Syntax Tree (AST).
    - Robustness: Handles nested blocks, complex LaTeX, and orphan backslashes.
    - Integration: `OEFEvaluator` now traverses the AST directly, eliminating redundant string-based parsing.
    - Backward Compatibility: Maintained `Directive` dataclass for parts of the engine still relying on it.

## Key Components
- **`parser.py`**: Contains the EBNF grammar and the `OEFNode` structure.
- **`evaluator.py`**: Updated `_eval_node` to recursively process AST instructions (`\if`, `\while`, `\integer`, etc.).
- **`engine.py`**: Entry point `load_and_render` now uses the AST-based flow.

## Next Steps
- [ ] Complete the migration of `_extract_answers_from_source` in `engine.py` to use the AST instead of regex.
- [ ] Refactor `_eval_expr` in `evaluator.py` to use the secondary logic parser for all calculations.
- [ ] Ensure 100% test coverage for complex nested OEF structures.

## Technical Notes
- **Grammar**: Uses Earley parser to handle the inherent ambiguity of mixed text/math/code in OEF.
- **AST**: The tree is composed of `OEFNode` objects, which can be easily serialized to JSON.
