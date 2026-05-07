#!/usr/bin/env python3
"""Debug script pour factorisat1."""

import sys
sys.path.insert(0, '/home/correard/pax/backend')

from core.oef.def_engine import load_and_render

def main():
    def_path = '/home/correard/pax/ressources/H4/algebra/oefcalcullit.fr/def/factorisat1.def'

    result = load_and_render(def_path, seed=42)

    print("=== TITRE ===")
    print(result.title)

    print("\n=== ANSWERS ===")
    for i, ans in enumerate(result.answers, 1):
        print(f"{i}. {ans.input_name}: type={ans.answer_type}, label={ans.label}")
        if ans.answer_type in ('radio', 'menu'):
            print(f"   choices ({len(ans.options.get('choices', []))}): {ans.options.get('choices', [])[:3]}...")
        print(f"   expected: {ans.expected[:50] if len(ans.expected) > 50 else ans.expected}")

    print(f"\n=== STATEMENT_HTML (first 1500 chars) ===")
    print(result.statement_html[:1500])

    print(f"\n=== STATEMENT_SEGMENTS ===")
    for i, seg in enumerate(result.statement_segments[:10]):
        if seg['type'] == 'html':
            content = seg['content'][:80].replace('\n', '\\n')
            print(f"{i}. html: {content}...")
        else:
            print(f"{i}. {seg}")

if __name__ == '__main__':
    main()
