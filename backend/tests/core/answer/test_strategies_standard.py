"""run_standard: mapping des positions `mark` vers les étiquettes (feedback)."""

from types import SimpleNamespace

from core.answer.strategies.standard import run_standard


def _mark_ansdef():
    return SimpleNamespace(
        input_name="reply1",
        answer_type="mark",
        expected="2",  # position correcte
        options={"choices": ["5000 g", "5000 kg", "5000 tonnes"]},
        weight=1.0,
    )


def test_mark_feedback_uses_labels_not_positions():
    a = _mark_ansdef()
    # clic position 3 (faux)
    _, results = run_standard([a], {"reply1": "3"})
    r = results[0]
    assert r.reply == "5000 tonnes"
    assert r.expected == "5000 kg"
    assert not r.correct


def test_mark_correct_click_label():
    a = _mark_ansdef()
    _, results = run_standard([a], {"reply1": "2"})
    assert results[0].reply == "5000 kg" and results[0].correct


def test_mark_out_of_range_position_kept_verbatim():
    # pas de clic / position invalide → on garde la valeur telle quelle
    a = _mark_ansdef()
    _, results = run_standard([a], {"reply1": ""})
    assert results[0].reply == ""
