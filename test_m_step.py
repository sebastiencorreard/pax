import sys
sys.path.insert(0, 'backend')

from core.oef.def_engine import load_and_render

def_path = '/home/correard/pax/ressources/H4/algebra/oefcalcullit.fr/def/factorisat1.def'

# Test avec m_step=2
result = load_and_render(def_path, seed=42, m_step=2)

print(f"m_step dans le contexte: {result.ev_ctx.get('m_step')}")
print(f"\nHTML (first 2000 chars):\n{result.statement_html[:2000]}")
print(f"\nval12 = {result.ev_ctx.get('val12')}")
print(f"\nRecherche 'Deuxième' dans HTML: {'Deuxième' in result.statement_html}")
print(f"Recherche 'val12' dans HTML: {'val12' in result.statement_html}")
