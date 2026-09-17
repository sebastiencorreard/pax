import pytest
from core.oef.def_engine import DefEngine, check_analyze
from core.oef.def_engine.cas import _call_maxima, _call_pari, _sympify_arg
from core.oef.def_parser import Assign, IfBlock

def test_sympify_implicit_multiplication():
    # Test implicit multiplication support
    expr1 = _sympify_arg("8 x")
    assert str(expr1) == "8*x"

    expr2 = _sympify_arg("8(x - 1)")
    assert str(expr2) == "8*x - 8"

def test_sympify_sign_normalization():
    # Test normalization of WIMS-style signs
    expr = _sympify_arg("8*x +- 8")
    assert str(expr) == "8*x - 8"
    
    expr2 = _sympify_arg("8*x -- 8")
    assert str(expr2) == "8*x + 8"

def test_def_engine_issametext():
    engine = DefEngine(seed=42)
    # Literal equality
    assert engine._eval_condition("ifval", "foo issametext foo") is True
    assert engine._eval_condition("ifval", "foo issametext bar") is False
    assert engine._eval_condition("ifval", "expand(8*x-8) isnotreexpanded expand(8*x-8)") is True

def test_def_engine_cmd_exec_subst():
    engine = DefEngine(seed=42)
    engine.ctx["t_"] = "expand((8*x-8)*(8-5*x))"
    # The engine should substitute $t_ before sending to CAS
    res = engine._eval_value("!exec maxima $t_")
    # Result should be the expanded polynomial
    assert res == "-40*x**2 + 104*x - 64"

def test_check_analyze():
    # Mock context from factdir1.def
    ev_ctx = {
        "val63": "-40*x**2 + 104*x - 64"
    }
    postdef = [
        Assign(name="t_", value="!exec maxima expand($val64 * $val65)"),
        Assign(name="val66", value="!exec maxima $t_")
    ]
    test_instr = [
        IfBlock(
            kind="ifval", 
            condition="$val66 issametext $val63",
            then_body=[Assign(name="condtest1", value="1")],
            else_body=[Assign(name="condtest1", value="0")]
        )
    ]

    # Test exact expected factors
    replies_perfect = {64: "8*x-8", 65: "8-5*x"}
    res1, _ = check_analyze(ev_ctx, postdef, test_instr, replies_perfect, seed=1)
    assert res1.get("condtest1") == 1

    # Test alternative valid factors (swapped)
    replies_swapped = {64: "8-5*x", 65: "8*x-8"}
    res2, _ = check_analyze(ev_ctx, postdef, test_instr, replies_swapped, seed=1)
    assert res2.get("condtest1") == 1

    # Test alternative valid factors (implicit mult and factored out)
    replies_implicit = {64: "8(x-1)", 65: "8 - 5 x"}
    res3, _ = check_analyze(ev_ctx, postdef, test_instr, replies_implicit, seed=1)
    assert res3.get("condtest1") == 1

    # Test invalid factors
    replies_wrong = {64: "8*x", 65: "8-5*x"}
    res4, _ = check_analyze(ev_ctx, postdef, test_instr, replies_wrong, seed=1)
    assert res4.get("condtest1") == 0


def test_analyze_wrap_keeps_simple_fractions_atomic():
    """A bare number/fraction must NOT be wrapped — wrapping "-23/5" as
    "(-23/5)" breaks issamecase/issametext string comparisons (cant's
    irreducible-fraction check), while changing nothing arithmetically."""
    from core.oef.def_engine.analyze import _analyze_wrap

    assert _analyze_wrap("-23/5") == "-23/5"
    assert _analyze_wrap("3/4") == "3/4"
    assert _analyze_wrap("-5") == "-5"
    assert _analyze_wrap("3.5") == "3.5"
    # Real expressions still get guarded for precedence.
    assert _analyze_wrap("1+2") == "(1+2)"
    assert _analyze_wrap("x-1") == "(x-1)"


def test_cant_irreducible_fraction_scoring():
    """cant: ?analyze with two weighted conditions (value w3, irreducible form
    w1). The correct irreducible answer scores 1.0; a correct-but-reducible
    answer scores the weighted 0.75 (not the unweighted 0.5)."""
    import os
    from core.oef.def_engine import load_and_render
    from core.answer.strategies.analyze import run_analyze

    ress = os.path.abspath(
        os.path.join(os.path.dirname(__file__), "..", "..", "..", "..", "ressources")
    )
    defp = os.path.join(ress, "H3/analysis/fonctaffin.fr/def/cant.def")
    r = load_and_render(defp, seed=684903783)
    a = r.answers[0]
    assert a.expected == "-23/5"

    score, results = run_analyze(r, [a], {a.input_name: "-23/5"}, seed=684903783)
    assert score == 1.0 and results[0].correct

    score_red, _ = run_analyze(r, [a], {a.input_name: "-46/10"}, seed=684903783)
    assert score_red == 0.75  # value right (w3), form wrong (w1)

    score_wrong, _ = run_analyze(r, [a], {a.input_name: "23/5"}, seed=684903783)
    assert score_wrong == 0.0


def test_branche_disjointe_choisie_sur_sa_premisse():
    """`?analyze` dont le `:test` énumère les réponses acceptables par branches.

    `oefexpalog10/expaequ6` écrit, pour une seule réponse :

        ($val13<=0 and $val14 issametext aucune) or ($val13>0 and $val14==$val9)

    « aucune » quand l'équation n'a pas de solution, la solution sinon. Lire la
    première égalité venue donnait « aucune » à toutes les graines, et la copie
    juste notait 0. On n'ouvre que les branches dont la prémisse — ce qui ne
    porte sur aucune réponse — tient à cette graine.
    """
    import os
    from core.oef.def_engine import load_and_render
    from core.answer.strategies.analyze import run_analyze

    ress = os.path.abspath(
        os.path.join(os.path.dirname(__file__), "..", "..", "..", "..", "ressources")
    )
    defp = os.path.join(ress, "H6/analysis/oefexpalog10.fr/def/expaequ6.def")
    r = load_and_render(defp, seed=42)
    a = r.answers[0]
    # $val13 > 0 à cette graine : c'est la seconde branche qui décrit la
    # réponse, et son attendu est $val9 — surtout pas le littéral « aucune ».
    assert a.expected == "0.69897"

    score, _ = run_analyze(r, [a], {a.input_name: a.expected}, seed=42)
    assert score == 1.0
    score_faux, _ = run_analyze(r, [a], {a.input_name: "aucune"}, seed=42)
    assert score_faux == 0.0


def test_branches_sans_premisse_decidable_restent_ouvertes():
    """Une disjonction dont on ne peut rien exclure garde le choix d'avant.

    Les prémisses qui portent elles-mêmes sur une réponse ne sont pas
    évaluables au rendu — aucune réponse n'est encore soumise. Les écarter
    toutes rendrait un attendu vide là où l'ancien code en trouvait un.
    """
    from core.oef.def_engine import DefEngine

    engine = DefEngine(seed=42)
    engine.ctx["replygood1"] = "?analyze 13"
    engine.ctx["replygood2"] = "?analyze 14"
    cond = "$val13=1 and $val14=2 or $val13=3 and $val14=4"
    # val13 et val14 sont deux réponses : rien n'est décidable, les deux
    # branches restent ouvertes et l'appelant les lit dans l'ordre — c'est-à-
    # dire qu'il retombe sur l'égalité que l'ancien code retenait.
    assert engine._branches_viables(cond, "ifval", "val14") == [
        "$val13=1 and $val14=2",
        "$val13=3 and $val14=4",
    ]

    # Une prémisse portant sur l'énoncé, elle, tranche.
    engine.ctx["val20"] = "5"
    cond2 = "($val20=9 and $val14=2) or ($val20=5 and $val14=4)"
    assert engine._branches_viables(cond2, "ifval", "val14") == ["$val20=5 and $val14=4"]


def test_appariement_des_membres_dun_produit():
    """Deux réponses, une seule équation : la convention d'appariement.

    `frac5/mult` fait saisir le numérateur et le dénominateur d'un produit de
    fractions, et ne teste que le produit croisé
    `$val6*$val8*$val14 = $val7*$val9*$val13`. Toutes les fractions
    équivalentes le satisfont ; on en nomme une, celle où chaque inconnue
    reçoit les facteurs connus d'en face — ici le produit des numérateurs sur
    le produit des dénominateurs.

    Elle se vérifie sur l'exercice lui-même : `val10` et `val11`, que l'auteur
    calcule pour son propre corrigé, valent exactement ce que l'appariement
    rend.
    """
    import os
    from core.oef.def_engine import load_and_render
    from core.answer.strategies.analyze import run_analyze

    ress = os.path.abspath(
        os.path.join(os.path.dirname(__file__), "..", "..", "..", "..", "ressources")
    )
    r = load_and_render(os.path.join(ress, "H1/algebra/frac5.fr/def/mult.def"), seed=42)
    ctx = r.check_sections["ctx"]
    attendus = [a.expected for a in r.answers]
    assert attendus == [ctx["val10"], ctx["val11"]] == ["0", "18"]

    copie = {a.input_name: a.expected for a in r.answers}
    score, _ = run_analyze(r, r.answers, copie, seed=42)
    assert score == 1.0


def test_appariement_refuse_ce_quil_ne_sait_pas_borner():
    """La convention ne s'applique qu'à des produits purs, et conjoint à conjoint.

    Une somme, une division ou deux inconnues dans le même membre sortent du
    cadre : mieux vaut pas d'attendu qu'un attendu faux. Et une conjonction
    pose plusieurs égalités, qu'il faut borner avant de les lire — sans quoi
    le membre droit de la première avale la seconde.
    """
    from core.oef.def_engine import DefEngine

    engine = DefEngine(seed=42)
    engine.ctx.update({"replygood1": "?analyze 14", "replygood2": "?analyze 16",
                       "val11": "3", "val12": "4", "val13": "5"})

    # Conjonction : chaque égalité est bornée, et val16 s'apparie avec val13.
    cond = "$val14*$val13=$val16*$val11 and $val14*$val12=$val15*$val11"
    assert engine._attendu_par_appariement(cond, "val16") == "5"

    # Somme dans un membre : hors cadre.
    assert engine._attendu_par_appariement("$val14*$val13=$val16+$val11", "val16") == ""
    # Deux inconnues du même côté : l'équation ne se résout pas en une seule.
    assert engine._attendu_par_appariement("$val14*$val16=$val11*$val12", "val16") == ""
    # Variable seule : laissée aux motifs d'égalité, qui gardent sa forme.
    assert engine._attendu_par_appariement("$val16=$val11*$val12", "val16") == ""


def test_attendu_lu_sur_un_quotient_de_deux_reponses():
    """Une condition sur le quotient fixe les deux réponses ensemble.

    `frac5/multsimp` pose deux conditions : le produit croisé, que l'appariement
    des facteurs satisfait par la forme directe `5/30`, puis
    `$val19/$val20 issametext $val14`, qui veut la fraction irréductible et
    refuse la première. C'est la seconde qui dit la réponse, d'où sa priorité.
    """
    import os
    from core.oef.def_engine import load_and_render
    from core.answer.strategies.analyze import run_analyze

    ress = os.path.abspath(
        os.path.join(os.path.dirname(__file__), "..", "..", "..", "..", "ressources")
    )
    r = load_and_render(
        os.path.join(ress, "H1/algebra/frac5.fr/def/multsimp.def"), seed=42
    )
    assert [a.expected for a in r.answers] == ["1", "6"]
    copie = {a.input_name: a.expected for a in r.answers}
    score, _ = run_analyze(r, r.answers, copie, seed=42)
    assert score == 1.0


def test_quotient_ne_lit_que_deux_reponses_sur_une_fraction():
    """La lecture est textuelle, et bornée à ce qu'elle sait apparier."""
    from core.oef.def_engine import DefEngine

    engine = DefEngine(seed=42)
    engine.ctx.update({"replygood1": "?analyze 19", "replygood2": "?analyze 20",
                       "val14": "-1/6", "val15": "0.25"})
    cond = "$val19/$val20 issametext $val14"
    assert engine._attendu_par_quotient(cond, "val19") == "-1"
    assert engine._attendu_par_quotient(cond, "val20") == "6"

    # L'autre membre n'est pas une fraction : rien à apparier.
    assert engine._attendu_par_quotient("$val19/$val20=$val15", "val19") == ""
    # Le quotient ne porte pas deux réponses.
    assert engine._attendu_par_quotient("$val19/$val14 issametext $val14", "val19") == ""
