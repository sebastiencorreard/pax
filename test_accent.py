#!/usr/bin/env python3
"""Test pour vérifier que les accents sont bien gérés."""

import sys
sys.path.insert(0, 'backend')

from core.oef.def_engine import load_and_render

# Test avec dev2exp.def (Développer deux expressions)
def_path = 'ressources/H4/algebra/oefcalcullit.fr/def/dev2exp.def'

result = load_and_render(def_path, seed=42)

print("=" * 80)
print("TITRE:", repr(result.title))
print("=" * 80)
print("\nATTENDU: 'Développer deux expressions'")
print("RÉSULTAT:", result.title)
print("\nACCENTS CORRECTS ?", "Développer deux expressions" == result.title)
print("\n" + "=" * 80)
print("HTML (premiers 500 caractères):")
print("=" * 80)
print(result.statement_html[:500])
