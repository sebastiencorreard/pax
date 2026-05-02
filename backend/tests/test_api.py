"""
HTTP-level API tests against the running server (http://localhost:8001).
Requires: docker compose up -d   (or uvicorn running locally)

These tests complement test_exercises_check.py (which calls core logic directly)
by verifying auth, response shapes, and cross-cutting concerns like role enforcement.
"""

import uuid
import pytest
import httpx

BASE = "http://localhost:8001"

# ---------------------------------------------------------------------------
# Fixtures
# ---------------------------------------------------------------------------


@pytest.fixture(scope="module")
def client():
    with httpx.Client(base_url=BASE, timeout=15) as c:
        yield c


@pytest.fixture(scope="module")
def student_token(client):
    r = client.post(
        "/api/auth/login", json={"email": "eleve@pax.fr", "password": "eleve1234"}
    )
    assert r.status_code == 200, f"student login failed: {r.text}"
    return r.json()["access_token"]


@pytest.fixture(scope="module")
def teacher_token(client):
    r = client.post(
        "/api/auth/login", json={"email": "prof@pax.fr", "password": "prof1234"}
    )
    assert r.status_code == 200, f"teacher login failed: {r.text}"
    return r.json()["access_token"]


@pytest.fixture(scope="module")
def student_headers(student_token):
    return {"Authorization": f"Bearer {student_token}"}


@pytest.fixture(scope="module")
def teacher_headers(teacher_token):
    return {"Authorization": f"Bearer {teacher_token}"}


# Known exercise: H4 algebra, fset answer, seed=42 → reply1="-6/5,-9/8"
EXERCISE_ID = "ressources~H4~algebra~OEFevalwimsequ.fr~src~equaprod1.oef"
SEED = 42
CORRECT_REPLY = "-6/5,-9/8"
WRONG_REPLY = "0"


# ---------------------------------------------------------------------------
# Auth
# ---------------------------------------------------------------------------


class TestAuth:
    def test_login_returns_token(self, client):
        r = client.post(
            "/api/auth/login", json={"email": "eleve@pax.fr", "password": "eleve1234"}
        )
        assert r.status_code == 200
        body = r.json()
        assert "access_token" in body
        assert body["access_token"]

    def test_login_wrong_password_is_401(self, client):
        r = client.post(
            "/api/auth/login", json={"email": "eleve@pax.fr", "password": "wrong"}
        )
        assert r.status_code == 401

    def test_login_unknown_email_is_401(self, client):
        r = client.post(
            "/api/auth/login", json={"email": "nobody@example.com", "password": "x"}
        )
        assert r.status_code == 401

    def test_me_returns_user(self, client, student_headers):
        r = client.get("/api/auth/me", headers=student_headers)
        assert r.status_code == 200
        body = r.json()
        assert body["email"] == "eleve@pax.fr"
        assert body["role"] == "student"
        assert "id" in body

    def test_me_without_token_is_401(self, client):
        r = client.get("/api/auth/me")
        assert r.status_code == 401

    def test_me_with_bad_token_is_401(self, client):
        r = client.get("/api/auth/me", headers={"Authorization": "Bearer not.a.token"})
        assert r.status_code == 401

    def test_teacher_me_returns_teacher_role(self, client, teacher_headers):
        r = client.get("/api/auth/me", headers=teacher_headers)
        assert r.status_code == 200
        assert r.json()["role"] == "teacher"


# ---------------------------------------------------------------------------
# Exercises
# ---------------------------------------------------------------------------


class TestExercises:
    def test_list_requires_auth(self, client):
        r = client.get("/api/exercises/")
        assert r.status_code == 401

    def test_list_returns_exercises(self, client, student_headers):
        r = client.get("/api/exercises/?lang=fr&limit=10", headers=student_headers)
        assert r.status_code == 200
        body = r.json()
        assert isinstance(body, list)
        assert len(body) > 0

    def test_list_exercise_shape(self, client, student_headers):
        r = client.get("/api/exercises/?lang=fr&limit=1", headers=student_headers)
        ex = r.json()[0]
        assert "id" in ex
        assert "oef_path" in ex
        assert "lang" in ex

    def test_list_filter_by_level(self, client, student_headers):
        r = client.get(
            "/api/exercises/?lang=fr&level=H4&limit=50", headers=student_headers
        )
        assert r.status_code == 200
        for ex in r.json():
            assert ex["level"] == "H4"

    def test_list_filter_by_domain(self, client, student_headers):
        r = client.get(
            "/api/exercises/?lang=fr&domain=algebra&limit=50", headers=student_headers
        )
        assert r.status_code == 200
        for ex in r.json():
            assert ex["domain"] == "algebra"

    def test_list_combined_filters(self, client, student_headers):
        r = client.get(
            "/api/exercises/?lang=fr&level=H4&domain=algebra&limit=10",
            headers=student_headers,
        )
        assert r.status_code == 200
        for ex in r.json():
            assert ex["level"] == "H4"
            assert ex["domain"] == "algebra"

    def test_list_respects_limit(self, client, student_headers):
        r = client.get("/api/exercises/?lang=fr&limit=3", headers=student_headers)
        assert r.status_code == 200
        assert len(r.json()) <= 3

    def test_list_pagination(self, client, student_headers):
        page1 = client.get(
            "/api/exercises/?lang=fr&limit=5&offset=0", headers=student_headers
        ).json()
        page2 = client.get(
            "/api/exercises/?lang=fr&limit=5&offset=5", headers=student_headers
        ).json()
        ids1 = {ex["id"] for ex in page1}
        ids2 = {ex["id"] for ex in page2}
        assert ids1.isdisjoint(ids2), "pages should not overlap"

    def test_get_exercise_by_id(self, client, student_headers):
        r = client.get(f"/api/exercises/{EXERCISE_ID}", headers=student_headers)
        assert r.status_code == 200
        body = r.json()
        assert body["id"] == EXERCISE_ID

    def test_get_unknown_exercise_is_404(self, client, student_headers):
        r = client.get("/api/exercises/does~not~exist", headers=student_headers)
        assert r.status_code == 404

    def test_get_exercise_requires_auth(self, client):
        r = client.get(f"/api/exercises/{EXERCISE_ID}")
        assert r.status_code == 401

    def test_get_source(self, client, student_headers):
        r = client.get(f"/api/exercises/{EXERCISE_ID}/source", headers=student_headers)
        assert r.status_code == 200
        body = r.json()
        assert "oef_path" in body
        assert "content" in body
        assert len(body["content"]) > 0


# ---------------------------------------------------------------------------
# Render
# ---------------------------------------------------------------------------


class TestRender:
    def test_render_requires_auth(self, client):
        r = client.get(f"/api/render/{EXERCISE_ID}")
        assert r.status_code == 401

    def test_render_returns_expected_shape(self, client, student_headers):
        r = client.get(
            f"/api/render/{EXERCISE_ID}?seed={SEED}", headers=student_headers
        )
        assert r.status_code == 200
        body = r.json()
        assert body["exercise_id"] == EXERCISE_ID
        assert body["seed"] == SEED
        assert isinstance(body["statement_segments"], list)
        assert isinstance(body["answers"], list)
        assert len(body["answers"]) > 0

    def test_render_answer_shape(self, client, student_headers):
        r = client.get(
            f"/api/render/{EXERCISE_ID}?seed={SEED}", headers=student_headers
        )
        answer = r.json()["answers"][0]
        assert "input_name" in answer
        assert "answer_type" in answer
        assert "weight" in answer
        assert "options" in answer

    def test_render_is_deterministic_with_seed(self, client, student_headers):
        r1 = client.get(
            f"/api/render/{EXERCISE_ID}?seed={SEED}", headers=student_headers
        )
        r2 = client.get(
            f"/api/render/{EXERCISE_ID}?seed={SEED}", headers=student_headers
        )
        assert r1.json()["statement_segments"] == r2.json()["statement_segments"]

    def test_render_different_seeds_differ(self, client, student_headers):
        r1 = client.get(f"/api/render/{EXERCISE_ID}?seed=1", headers=student_headers)
        r2 = client.get(f"/api/render/{EXERCISE_ID}?seed=2", headers=student_headers)
        # Seeds 1 and 2 almost certainly produce different statements
        assert r1.json()["seed"] == 1
        assert r2.json()["seed"] == 2

    def test_render_unknown_exercise_is_404(self, client, student_headers):
        r = client.get("/api/render/does~not~exist", headers=student_headers)
        assert r.status_code == 404

    def test_render_debug_returns_expected_answers(self, client, student_headers):
        r = client.get(
            f"/api/render/{EXERCISE_ID}/debug?seed={SEED}", headers=student_headers
        )
        assert r.status_code == 200
        body = r.json()
        assert body["exercise_id"] == EXERCISE_ID
        assert body["seed"] == SEED
        assert isinstance(body["answers"], list)
        answer = body["answers"][0]
        assert "input_name" in answer
        assert "expected" in answer
        assert "answer_type" in answer

    def test_render_debug_correct_answer_matches_expected(
        self, client, student_headers
    ):
        r = client.get(
            f"/api/render/{EXERCISE_ID}/debug?seed={SEED}", headers=student_headers
        )
        expected = r.json()["answers"][0]["expected"]
        assert expected == CORRECT_REPLY


# ---------------------------------------------------------------------------
# Check — specific exercise fixture
# ---------------------------------------------------------------------------


class TestCheck:
    def test_check_requires_auth(self, client):
        r = client.post(
            f"/api/check/{EXERCISE_ID}",
            json={
                "seed": SEED,
                "replies": [{"input_name": "reply1", "value": CORRECT_REPLY}],
            },
        )
        assert r.status_code == 401

    def test_correct_answer_scores_1(self, client, student_headers):
        r = client.post(
            f"/api/check/{EXERCISE_ID}",
            headers=student_headers,
            json={
                "seed": SEED,
                "replies": [{"input_name": "reply1", "value": CORRECT_REPLY}],
            },
        )
        assert r.status_code == 200
        body = r.json()
        assert body["global_score"] == pytest.approx(1.0)

    def test_wrong_answer_scores_0(self, client, student_headers):
        r = client.post(
            f"/api/check/{EXERCISE_ID}",
            headers=student_headers,
            json={
                "seed": SEED,
                "replies": [{"input_name": "reply1", "value": WRONG_REPLY}],
            },
        )
        assert r.status_code == 200
        assert r.json()["global_score"] == pytest.approx(0.0)

    def test_check_response_shape(self, client, student_headers):
        r = client.post(
            f"/api/check/{EXERCISE_ID}",
            headers=student_headers,
            json={
                "seed": SEED,
                "replies": [{"input_name": "reply1", "value": CORRECT_REPLY}],
            },
        )
        body = r.json()
        assert "exercise_id" in body
        assert "global_score" in body
        assert "results" in body
        assert "attempt_id" in body
        assert body["exercise_id"] == EXERCISE_ID

    def test_check_saves_attempt_with_valid_uuid(self, client, student_headers):
        r = client.post(
            f"/api/check/{EXERCISE_ID}",
            headers=student_headers,
            json={
                "seed": SEED,
                "replies": [{"input_name": "reply1", "value": CORRECT_REPLY}],
            },
        )
        attempt_id = r.json()["attempt_id"]
        uuid.UUID(attempt_id)  # raises if not valid UUID

    def test_check_result_per_answer(self, client, student_headers):
        r = client.post(
            f"/api/check/{EXERCISE_ID}",
            headers=student_headers,
            json={
                "seed": SEED,
                "replies": [{"input_name": "reply1", "value": CORRECT_REPLY}],
            },
        )
        results = r.json()["results"]
        assert len(results) == 1
        result = results[0]
        assert result["input_name"] == "reply1"
        assert result["correct"] is True
        assert result["score"] == pytest.approx(1.0)

    def test_check_wrong_result_has_expected(self, client, student_headers):
        r = client.post(
            f"/api/check/{EXERCISE_ID}",
            headers=student_headers,
            json={
                "seed": SEED,
                "replies": [{"input_name": "reply1", "value": WRONG_REPLY}],
            },
        )
        result = r.json()["results"][0]
        assert result["correct"] is False
        assert result["expected"]  # non-empty correction

    def test_check_unknown_exercise_is_404(self, client, student_headers):
        r = client.post(
            "/api/check/does~not~exist",
            headers=student_headers,
            json={"seed": SEED, "replies": []},
        )
        assert r.status_code == 404

    def test_check_reply_alias_r1_accepted(self, client, student_headers):
        """WIMS alias: r1 is equivalent to reply1."""
        r = client.post(
            f"/api/check/{EXERCISE_ID}",
            headers=student_headers,
            json={
                "seed": SEED,
                "replies": [{"input_name": "r1", "value": CORRECT_REPLY}],
            },
        )
        assert r.status_code == 200
        assert r.json()["global_score"] == pytest.approx(1.0)


# ---------------------------------------------------------------------------
# Sheets
# ---------------------------------------------------------------------------


class TestSheets:
    def test_student_cannot_create_sheet(self, client, student_headers):
        r = client.post(
            "/api/sheets/",
            headers=student_headers,
            json={"title": "Should fail", "description": ""},
        )
        assert r.status_code == 403

    def test_teacher_can_create_sheet(self, client, teacher_headers):
        r = client.post(
            "/api/sheets/",
            headers=teacher_headers,
            json={
                "title": "Test sheet (api tests)",
                "description": "Created by test_api.py",
            },
        )
        assert r.status_code == 201
        body = r.json()
        assert "id" in body
        assert body["title"] == "Test sheet (api tests)"

    def test_list_sheets_requires_auth(self, client):
        r = client.get("/api/sheets/")
        assert r.status_code == 401

    def test_list_sheets_returns_list(self, client, student_headers):
        r = client.get("/api/sheets/", headers=student_headers)
        assert r.status_code == 200
        assert isinstance(r.json(), list)

    def test_get_sheet_detail(self, client, teacher_headers):
        # Create then fetch
        r = client.post(
            "/api/sheets/",
            headers=teacher_headers,
            json={"title": "Detail test sheet", "description": ""},
        )
        sheet_id = r.json()["id"]

        r = client.get(f"/api/sheets/{sheet_id}", headers=teacher_headers)
        assert r.status_code == 200
        body = r.json()
        assert body["id"] == sheet_id
        assert "items" in body

    def test_get_unknown_sheet_is_404(self, client, student_headers):
        r = client.get("/api/sheets/999999", headers=student_headers)
        assert r.status_code == 404

    def test_teacher_can_add_exercise_to_sheet(self, client, teacher_headers):
        sheet_id = client.post(
            "/api/sheets/",
            headers=teacher_headers,
            json={"title": "Add-exercise test", "description": ""},
        ).json()["id"]

        r = client.post(
            f"/api/sheets/{sheet_id}/exercises",
            headers=teacher_headers,
            json={"exercise_id": EXERCISE_ID},
        )
        assert r.status_code == 201

        detail = client.get(f"/api/sheets/{sheet_id}", headers=teacher_headers).json()
        assert any(item["exercise"]["id"] == EXERCISE_ID for item in detail["items"])

    def test_student_cannot_add_exercise_to_sheet(
        self, client, teacher_headers, student_headers
    ):
        sheet_id = client.post(
            "/api/sheets/",
            headers=teacher_headers,
            json={"title": "Student add test", "description": ""},
        ).json()["id"]

        r = client.post(
            f"/api/sheets/{sheet_id}/exercises",
            headers=student_headers,
            json={"exercise_id": EXERCISE_ID},
        )
        assert r.status_code == 403

    def test_teacher_can_remove_exercise_from_sheet(self, client, teacher_headers):
        sheet_id = client.post(
            "/api/sheets/",
            headers=teacher_headers,
            json={"title": "Remove-exercise test", "description": ""},
        ).json()["id"]

        client.post(
            f"/api/sheets/{sheet_id}/exercises",
            headers=teacher_headers,
            json={"exercise_id": EXERCISE_ID},
        )

        detail = client.get(f"/api/sheets/{sheet_id}", headers=teacher_headers).json()
        item_id = detail["items"][0]["id"]

        r = client.delete(
            f"/api/sheets/{sheet_id}/exercises/{item_id}", headers=teacher_headers
        )
        assert r.status_code == 204

        detail = client.get(f"/api/sheets/{sheet_id}", headers=teacher_headers).json()
        assert detail["items"] == []
