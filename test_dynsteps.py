#!/usr/bin/env python3
"""Test des dynamic steps pour factorisat1."""

import sys
sys.path.insert(0, 'backend')

from core.oef.engine import load_and_render

# Le chemin .oef qui va automatiquement utiliser le .def
oef_path = 'ressources/H4/algebra/oefcalcullit.fr/src/factorisat1.oef'

print("=" * 80)
print("TEST DYNAMIC STEPS - factorisat1")
print("=" * 80)

# Test step 1
print("\n### STEP 1 ###")
result1 = load_and_render(oef_path, seed=42, m_step=1)
print(f"Title: {result1.title[:50]}")
print(f"is_dynsteps: {result1.is_dynsteps}")
print(f"current_step: {result1.current_step}")
print(f"total_steps: {result1.total_steps}")
print(f"Answers count: {len(result1.answers)}")
for i, ans in enumerate(result1.answers, 1):
    print(f"  {i}. {ans.input_name}: type={ans.answer_type}")
print(f"\nHTML (first 500 chars):\n{result1.statement_html[:500]}")

# Test step 2
print("\n" + "=" * 80)
print("### STEP 2 ###")
result2 = load_and_render(oef_path, seed=42, m_step=2)
print(f"current_step: {result2.current_step}")
print(f"Answers count: {len(result2.answers)}")
for i, ans in enumerate(result2.answers, 1):
    print(f"  {i}. {ans.input_name}: type={ans.answer_type}")
print(f"\nHTML (first 800 chars):\n{result2.statement_html[:800]}")

# Test step 4 (final)
print("\n" + "=" * 80)
print("### STEP 4 (final) ###")
result4 = load_and_render(oef_path, seed=42, m_step=4)
print(f"current_step: {result4.current_step}")
print(f"Answers count: {len(result4.answers)}")
for i, ans in enumerate(result4.answers, 1):
    print(f"  {i}. {ans.input_name}: type={ans.answer_type}")
print(f"\nHTML length: {len(result4.statement_html)} chars")
