#!/usr/bin/env python3
"""Test script to render factorisat1 and see the HTML output."""

import sys
sys.path.insert(0, '/home/correard/pax/backend')

# Import only what we need from def_engine, avoiding the parser import
from core.oef.def_parser import parse as parse_def

def main():
    def_path = '/home/correard/pax/ressources/H4/algebra/oefcalcullit.fr/def/factorisat1.def'

    # Read the file
    try:
        with open(def_path, encoding='utf-8') as f:
            text = f.read()
    except UnicodeDecodeError:
        with open(def_path, encoding='iso-8859-1') as f:
            text = f.read()

    # Parse it
    def_file = parse_def(text)

    print("=== TITLE ===")
    print(def_file.title)

    print("\n=== STATEMENT ===")
    print(repr(def_file.statement)[:200])

    print("\n=== QUESTION SECTION (first 10 instructions) ===")
    q_section = def_file.sections.get('question', [])
    for i, instr in enumerate(q_section[:10]):
        print(f"{i}: {type(instr).__name__} - {repr(str(instr))[:100]}")

    # Now test rendering with the engine
    from core.oef.def_engine import DefEngine
    engine = DefEngine(seed=42, def_path=def_path)

    # Execute variable instructions
    engine._exec(def_file.var_instructions, output_buf=None)

    print("\n=== SOME VARIABLES ===")
    print(f"val8 = {repr(engine.ctx.get('val8', 'NOT SET'))}")
    print(f"val65 = {repr(engine.ctx.get('val65', 'NOT SET'))[:200]}")
    print(f"val9 = {repr(engine.ctx.get('val9', 'NOT SET'))}")
    print(f"m_step = {repr(engine.ctx.get('m_step', 'NOT SET'))}")

    # Render the question section
    html = engine._render_section(q_section)

    print("\n=== RENDERED HTML (first 1500 chars) ===")
    print(html[:1500])

if __name__ == '__main__':
    main()
