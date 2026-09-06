"""L'application s'importe — le seul test qui attrape un import circulaire.

`pytest tests/core/oef/` charge les modules du moteur dans un ordre qui masque
les cycles : c'est ainsi qu'un `from .def_engine import wims_lists` posé en
tête d'`evaluator.py` a laissé 762 tests au vert pendant que `uvicorn
main:app` mourait sur un `ImportError: cannot import name 'AnswerDef' from
partially initialized module 'core.oef.engine'`.

Importer `main` reproduit exactement le chemin d'`uvicorn`.
"""

import importlib


def test_main_importe_sans_cycle():
    importlib.import_module("main")


def test_le_moteur_s_importe_depuis_l_api():
    """L'ordre d'import de l'API : les routes d'abord, le moteur ensuite."""
    importlib.import_module("api.routes.render")
    importlib.import_module("core.oef.engine")
    importlib.import_module("core.oef.def_engine")
