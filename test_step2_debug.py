#!/usr/bin/env python3
"""Debug étape 2 de factorisat1."""

import sys
sys.path.insert(0, 'backend')

from core.oef.def_parser import parse as parse_def

def_path = 'ressources/H4/algebra/oefcalcullit.fr/def/factorisat1.def'

# Read file
try:
    with open(def_path, encoding='utf-8') as f:
        text = f.read()
except UnicodeDecodeError:
    with open(def_path, encoding='iso-8859-1') as f:
        text = f.read()

print("=== TEST ENCODAGE ===")
print("Type de 'text':", type(text))
print("\nval12 dans le fichier:")
for line in text.split('\n'):
    if line.startswith('val12='):
        print(repr(line))
        print("Hex:", line.encode('utf-8').hex())
        break

print("\nval13 dans le fichier:")
for line in text.split('\n'):
    if line.startswith('val13='):
        print(repr(line))
        print("Hex:", line.encode('utf-8').hex())
        break

# Now test with def_engine
print("\n" + "="*80)
print("=== TEST RENDU ÉTAPE 2 ===")
print("="*80)

from core.oef.def_engine import DefEngine
from core.oef.def_parser import parse as parse_def

def_file = parse_def(text)
engine = DefEngine(seed=42, def_path=def_path)
engine.ctx["m_step"] = "2"
engine.ctx["step"] = "2"

# Execute var instructions
engine._exec(def_file.var_instructions, output_buf=None)

print("\nval12 =", repr(engine.ctx.get('val12', 'NOT SET')))
print("val13 =", repr(engine.ctx.get('val13', 'NOT SET')))
print("val60 =", repr(engine.ctx.get('val60', 'NOT SET')))
print("val62 =", repr(engine.ctx.get('val62', 'NOT SET')))
print("val63 =", repr(engine.ctx.get('val63', 'NOT SET')))

# Test list indexing
print("\n=== TEST INDEXATION ===")
val12 = engine.ctx.get('val12', '')
print("val12 brut:", repr(val12))
parts = val12.split(',')
print("Splité par virgule:", [repr(p.strip()) for p in parts])

# Render question section
print("\n=== RENDU SECTION QUESTION ===")
q_section = def_file.sections.get('question', [])
html = engine._render_section(q_section)
print("HTML (first 1500 chars):")
print(html[:1500])

print("\n=== RECHERCHE CONSIGNE ===")
print("'Deuxième' dans HTML:", 'Deuxi' in html)
print("'val12' dans HTML:", 'val12' in html)
print("'Isolement' dans HTML:", 'Isolement' in html)
