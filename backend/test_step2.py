#!/usr/bin/env python3
"""Test étape 2 de factorisat1."""

import sys
sys.path.insert(0, '/app/backend')

from core.oef.def_engine import load_and_render

def_path = '/ressources/H4/algebra/oefcalcullit.fr/def/factorisat1.def'

print("=" * 80)
print("ÉTAPE 2 - factorisat1")
print("=" * 80)

result = load_and_render(def_path, seed=42, m_step=2)

print(f"\nTitle: {result.title}")
print(f"is_dynsteps: {result.is_dynsteps}")
print(f"current_step: {result.current_step}")
print(f"total_steps: {result.total_steps}")
print(f"\nAnswers ({len(result.answers)}):")
for i, ans in enumerate(result.answers, 1):
    print(f"  {i}. {ans.input_name}: type={ans.answer_type}")
    print(f"     expected: {repr(ans.expected)}")
    print(f"     expected (hex): {ans.expected.encode('utf-8').hex()}")

print(f"\n{'=' * 80}")
print("HTML (first 1200 chars):")
print("=" * 80)
print(result.statement_html[:1200])

print(f"\n{'=' * 80}")
print("Variables clés du contexte:")
print("=" * 80)
ctx = result.ev_ctx
print(f"m_step = {repr(ctx.get('m_step', 'NOT SET'))}")
print(f"val40 = {repr(ctx.get('val40', 'NOT SET'))}")
print(f"val57 = {repr(ctx.get('val57', 'NOT SET'))}")
print(f"val59 = {repr(ctx.get('val59', 'NOT SET'))}")
print(f"val60 = {repr(ctx.get('val60', 'NOT SET'))}")
print(f"val62 = {repr(ctx.get('val62', 'NOT SET'))}")
