"""Unit tests for the XKCD-style French passphrase generator."""

import sys
import os

# scripts/ isn't a package; add it to path the same way create_user.py does.
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "scripts"))

import pytest

from _passphrase import (  # type: ignore[import-not-found]
    _WORDS,
    generate_passphrase,
    wordlist_size,
)


class TestPassphrase:
    def test_default_has_four_words(self):
        p = generate_passphrase()
        assert len(p.split("-")) == 4

    def test_word_count_respected(self):
        assert len(generate_passphrase(n_words=6).split("-")) == 6

    def test_separator_respected(self):
        assert "_" in generate_passphrase(separator="_")
        assert "-" not in generate_passphrase(separator="_")

    def test_each_word_is_from_wordlist(self):
        for _ in range(20):
            for word in generate_passphrase().split("-"):
                assert word in _WORDS

    def test_no_duplicate_entries_in_wordlist(self):
        # Duplicates would silently lower entropy.
        assert len(set(_WORDS)) == len(_WORDS)

    def test_wordlist_has_minimum_size(self):
        # 200 words × 4 picks ≈ 30 bits; the floor we promise to ourselves.
        assert wordlist_size() >= 200

    def test_words_are_lowercase_ascii(self):
        # Keep typing easy on any keyboard layout the first login.
        for w in _WORDS:
            assert w == w.lower()
            assert all(ch.isascii() and ch.isalpha() for ch in w), w

    def test_zero_words_rejected(self):
        with pytest.raises(ValueError):
            generate_passphrase(n_words=0)

    def test_two_runs_usually_differ(self):
        # 1-in-N**4 chance of collision; not flaky in practice.
        a = {generate_passphrase() for _ in range(20)}
        assert len(a) > 1
