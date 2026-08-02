"""`\\special{imagefill}` — des champs à remplir posés sur une grande image.

Port d'`oef/special/imagefill.phtml`. WIMS empile des calques DynAPI à des
coordonnées absolues ; en CSS cela se réduit à un conteneur `position:relative`
et des cases `position:absolute`, ce qui est tout le mécanisme.

Le special n'étant pas reconnu, les 14 exercices concernés affichaient leur
image sans la moindre case : insolubles.
"""

import re

import pytest

from core.oef.def_engine import DefEngine, load_and_render
from core.oef.engine import _segment_statement


def engine(**types) -> DefEngine:
    e = DefEngine(seed=1)
    for n, t in types.items():
        e.ctx[f"replytype{n[1:]}"] = t
    return e


def slots(html: str) -> list[tuple[str, str, str]]:
    """(nom, left, top) de chaque case rendue."""
    return re.findall(r'name="(reply\d+)"[^>]*left:(\d+)px;top:(\d+)px', html)


class TestParsing:
    def test_positions_are_kept_verbatim(self):
        e = engine(r1="clickfill", r2="clickfill")
        out = e._render_imagefill("img.png,250x250,40x27\tr1,147 x 175\tr2,170 x 78")
        assert slots(out) == [("reply1", "147", "175"), ("reply2", "170", "78")]
        assert 'width:250px;height:250px' in out

    def test_semicolons_separate_rows_too(self):
        """`imagefill.phtml` traduit les tabulations en `;` **puis** découpe sur
        `;` : les deux séparateurs sont équivalents, et `oefmolecule` livre
        effectivement ses champs en `;`."""
        e = engine(r2="clickfill", r3="clickfill")
        out = e._render_imagefill("img.png,200 x 200, 20 x 20\t  r 2,90x100;  r 3,155x140")
        assert slots(out) == [("reply2", "90", "100"), ("reply3", "155", "140")]

    def test_only_fill_replies_get_a_slot(self):
        """WIMS : `$(replytype$n) iswordof clickfill dragfill`."""
        e = engine(r1="clickfill", r2="numeric")
        out = e._render_imagefill("img.png,100x100,20x20\tr1,10,10\tr2,50,50")
        assert [s[0] for s in slots(out)] == ["reply1"]

    def test_label_count_gives_several_boxes_side_by_side(self):
        """4ᵉ paramètre = nombre d'étiquettes acceptées, d'où le
        `stretchH:$sizei*$ssizex` du calque WIMS."""
        e = engine(r1="clickfill")
        out = e._render_imagefill("img.png,300x100,30x20\tr1,10,10,3")
        assert slots(out) == [("reply1", "10", "10"), ("reply1", "40", "10"),
                              ("reply1", "70", "10")]

    def test_unevaluated_size_still_shows_the_image(self):
        """`unitecell` passe `[227,13,146,15] x [18,120,48,117]` — une taille non
        évaluée ne doit pas coûter l'image."""
        out = engine()._render_imagefill("img.png,[227,13] x [18,120],200 x 30")
        assert 'src="img.png"' in out
        assert "width:[" not in out

    def test_no_image_no_output(self):
        assert engine()._render_imagefill("") == ""


class TestSegmentation:
    def test_the_container_is_not_split_into_segments(self):
        """Les cases ne valent que par leur position absolue dans le conteneur :
        les découper en segments ferait perdre le positionnement."""
        html = (
            '<div class="oef-imagefill" style="position:relative">'
            '<img src="i.png" alt="">'
            '<cf-slot name="reply1" data-index="0" style="position:absolute"></cf-slot>'
            "</div>"
        )
        segs = _segment_statement(html)
        assert all(s["type"] != "slot" for s in segs)
        assert "".join(s.get("content", "") for s in segs).count("<cf-slot") == 1


class TestCorpus:
    @pytest.mark.parametrize("path,cells", [
        ("H3/geometry/oeftrigo2.fr/def/vocabulaire3", 3),
        ("H3/stat/oefstat.fr/def/baton", 20),
        ("H4/chemistry/oefmolecule.fr/def/cramnom1", 5),
    ])
    def test_exercises_render_their_boxes(self, path, cells):
        r = load_and_render(f"/ressources/{path}.def", seed=42)
        html = "".join(
            s.get("content", "") for s in r.statement_segments if s.get("type") == "html"
        )
        assert "oef-imagefill" in html
        assert html.count("<cf-slot") == cells

    def test_positions_match_what_the_exercise_declares(self):
        r = load_and_render(
            "/ressources/H3/geometry/oeftrigo2.fr/def/vocabulaire3.def", seed=42
        )
        html = "".join(
            s.get("content", "") for s in r.statement_segments if s.get("type") == "html"
        )
        # Le `.def` déclare r1,147 x 175 / r2,170 x 78 / r3,110 x 115.
        assert slots(html) == [
            ("reply1", "147", "175"), ("reply2", "170", "78"), ("reply3", "110", "115"),
        ]
