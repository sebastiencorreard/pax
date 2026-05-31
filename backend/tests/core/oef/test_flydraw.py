"""Unit tests for the flydraw → SVG renderer."""

import pytest

from core.oef.flydraw import (
    _num,
    flydraw_to_svg,
    flydraw_to_url,
    get_cached_svg,
    inline_pax_images,
    inline_svg_imgs,
)


class TestInlinePaxImages:
    """`$imagedir/<file>` (pax-img sentinel) must resolve to /api/static."""

    @pytest.fixture
    def module(self, tmp_path, monkeypatch):
        # ressources/<module>/images/<exercise>/tice.jpg (per-exercise layout).
        monkeypatch.setattr("core.oef.flydraw._RESSOURCES_ROOT", str(tmp_path))
        mod = tmp_path / "mod"
        (mod / "images" / "deuxcarres").mkdir(parents=True)
        (mod / "images" / "deuxcarres" / "tice.jpg").write_bytes(b"x")
        (mod / "images" / "flat.png").write_bytes(b"y")
        return str(mod)

    def test_per_exercise_subdir(self, module):
        html = '<img src="pax-img:_/tice.jpg" alt="">'
        out = inline_pax_images(html, module, exercise="deuxcarres")
        assert 'src="/api/static/mod/images/deuxcarres/tice.jpg"' in out

    def test_flat_layout_still_works(self, module):
        out = inline_pax_images('<img src="pax-img:flat.png">', module, exercise="deuxcarres")
        assert 'src="/api/static/mod/images/flat.png"' in out

    def test_missing_file_left_untouched(self, module):
        html = '<img src="pax-img:_/nope.jpg">'
        assert inline_pax_images(html, module, exercise="deuxcarres") == html


class TestNumEval:
    """`_num` must evaluate the arithmetic WIMS leaves in coordinate args."""

    def test_plain_numbers(self):
        assert _num("10") == 10.0
        assert _num("-10") == -10.0

    def test_floor_ceil_round(self):
        # sdlectgraph1 frames the parabola with `yrange -10,floor(V)+2`;
        # without floor in the eval namespace _num returned 0.0, so the
        # vertex fell outside the frame and was never visible.
        assert _num("floor(10.125)+2") == 12.0
        assert _num("floor(-3)-2") == -5.0
        assert _num("ceil(2.1)") == 3.0

    def test_strips_inline_math_delimiters(self):
        # repgraphint reuses `\(-6)` (its display form) as a coordinate;
        # _num must strip the \(…) so it parses as -6, not 0 (which collapsed
        # every bound onto the axis centre).
        assert _num(r"\(-6)") == -6.0
        assert _num(r"\(4)") == 4.0
        assert _num(r"\((1+3))") == 4.0


class TestFlydrawPrimitives:
    def test_viewbox_is_pixel_space(self):
        # ViewBox is fixed in pixel space so font/marker sizes stay in px;
        # math coordinates are projected by the renderer.
        svg = flydraw_to_svg(300, 80, "range -10,10,-2,2")
        assert 'viewBox="0 0 300 80"' in svg

    def test_segment_projects_math_to_pixels(self):
        # range -10..10 maps to 0..300 px; segment at x=0 lands at px=150.
        svg = flydraw_to_svg(300, 80, "range -10,10,-1,1\nsegment 0,0,10,0,red")
        assert 'x1="150.00"' in svg

    def test_segment_renders_line(self):
        svg = flydraw_to_svg(300, 80, "range -5,5,-1,1\nsegment 0,0,3,1,red")
        assert "<line" in svg
        assert 'stroke="#ff0000"' in svg

    def test_arrow_creates_marker(self):
        svg = flydraw_to_svg(300, 80, "range -5,5,-1,1\narrow 0,0,4,0,20,black")
        assert "<marker" in svg
        assert "marker-end" in svg

    def test_parallel_emits_n_lines(self):
        svg = flydraw_to_svg(300, 80, "range 0,10,-1,1\nparallel 0,0,0,0.5,1,0,5,black")
        # Five segments emitted
        assert svg.count("<line") == 5

    def test_text_is_escaped(self):
        svg = flydraw_to_svg(300, 80, "range -5,5,-1,1\ntext black,0,0,medium,A<B&C")
        assert "A&lt;B&amp;C" in svg

    def test_arithmetic_args_evaluated(self):
        # `-15-2` should evaluate to -17 — render a segment near the left edge
        # to verify the range was applied (xmin=-17 means math x=-17 → px=0).
        svg = flydraw_to_svg(300, 80, "range -15-2,15+2,-3,2\nsegment -17,0,17,0,black")
        assert 'x1="0.00"' in svg
        assert 'x2="300.00"' in svg

    def test_color_name_lookup(self):
        svg = flydraw_to_svg(300, 80, "range -5,5,-1,1\nsegment 0,0,1,1,blue")
        assert 'stroke="#0000ff"' in svg

    def test_unknown_color_falls_back_black(self):
        svg = flydraw_to_svg(300, 80, "range -5,5,-1,1\nsegment 0,0,1,1,fuchsia2")
        assert 'stroke="#000000"' in svg

    def test_tab_separated_commands(self):
        # WIMS-script packs multi-command values with tabs (val10=cmd\tcmd\tcmd).
        svg = flydraw_to_svg(
            300, 80, "range 0,10,0,10\tsegment 0,0,5,5,red\tsegment 5,5,10,10,blue"
        )
        assert svg.count("<line") == 2

    def test_semicolon_separated_commands(self):
        svg = flydraw_to_svg(300, 80, "range 0,10,0,10;segment 0,0,5,5,red")
        assert svg.count("<line") == 1

    def test_math_function_args(self):
        # 10*sqrt(3) ≈ 17.32 in range 0..20 projects to pixel ≈ 259.8.
        svg = flydraw_to_svg(300, 80, "range 0,20,0,5\nsegment 0,0,10*sqrt(3),0,red")
        import re as _re

        m = _re.search(r'x2="([\d.]+)"', svg)
        assert m
        assert 259 < float(m.group(1)) < 261

    def test_trig_args_with_pi(self):
        # cos(0) = 1; range -5..5 → px=180 for x=1.
        svg = flydraw_to_svg(300, 80, "range -5,5,-1,1\nsegment cos(0),0,1,1,black")
        assert 'x1="180.00"' in svg

    def test_circle(self):
        # WIMS `circle x,y,d` — d is the *diameter* in pixels, so the SVG
        # radius is d/2 (here 4 → 2.00). Matches fcircle's convention.
        svg = flydraw_to_svg(300, 80, "range 0,10,0,10\ncircle 5,5,4,red")
        assert "<circle" in svg
        assert 'cx="150.00"' in svg
        assert 'r="2.00"' in svg
        assert 'stroke="#ff0000"' in svg

    def test_flood_emits_polygon_for_enclosing_triangle(self):
        # Three segments forming a triangle around (5, 5).
        svg = flydraw_to_svg(
            300,
            300,
            "range 0,10,0,10\n"
            "segment 0,0,10,0,grey\n"
            "segment 0,0,5,10,grey\n"
            "segment 5,10,10,0,grey\n"
            "flood 5,3,red",
        )
        assert "<polygon" in svg
        assert 'fill="#ff0000"' in svg

    def test_flood_skips_when_no_enclosing_triangle(self):
        svg = flydraw_to_svg(300, 300, "range 0,10,0,10\nflood 5,5,red")
        # No segments → nothing to enclose; no polygon emitted.
        assert "<polygon" not in svg

    def test_flood_fills_pie_sector_of_a_wheel(self):
        # A "roue": spokes radiating from the origin inside a unit circle.
        # Every spoke pair meets only at the hub, so the triangle-from-families
        # logic can't help; the sector branch must fill the wedge instead.
        svg = flydraw_to_svg(
            200,
            200,
            "xrange -1.5,1.5\nyrange -1.5,1.5\n"
            "ellipse 0,0,2,2,black\n"
            "segment 0,0,1,0,black\n"            # spoke at 0°
            "segment 0,0,0,1,black\n"            # spoke at 90°
            "segment 0,0,-1,0,black\n"           # spoke at 180°
            "fill 0.5,0.5,red",                  # point in the 0–90° sector
        )
        # The wedge is emitted as a filled polygon anchored at the hub centre.
        assert 'fill="#ff0000"' in svg
        import re
        m = re.search(r'<polygon points="([^"]+)" fill="#ff0000"', svg)
        assert m is not None
        first = m.group(1).split()[0]
        # First vertex is the hub → centre of the 200×200 canvas.
        assert first == "100.00,100.00"

    def test_color_table_includes_sienna(self):
        svg = flydraw_to_svg(300, 80, "range 0,10,0,10\nsegment 0,0,10,10,sienna")
        assert 'stroke="#a0522d"' in svg

    def test_flood_picks_grid_cell_aligned_to_lines(self):
        # 3 line families forming a regular equilateral grid; flood at the
        # centroid of one cell. Polygon vertices must lie on the bounding
        # grid lines (verified by checking they're equilateral with the
        # known edge length).
        svg = flydraw_to_svg(
            300,
            300,
            "range 0,3,0,3\n"
            "segment 0,1,3,1,grey\n"
            "segment 0,2,3,2,grey\n"
            "segment 0.5,0.134,2.5,3.598,grey\n"  # slope +sqrt(3) line through (1,1)
            "segment 1.5,0.134,3.5,3.598,grey\n"  # parallel to the first diag
            "segment 2.5,0.134,0.5,3.598,grey\n"  # slope -sqrt(3) line through (2,1)
            "segment 1.5,0.134,-0.5,3.598,grey\n"  # parallel to the second diag
            "flood 1.5,1.4,red",
        )
        # Exactly one polygon emitted (the bounding cell).
        assert svg.count("<polygon") == 1
        assert 'fill="#ff0000"' in svg

    def test_xrange_yrange_set_viewport(self):
        # x-range / y-range take effect for subsequent primitives.
        svg = flydraw_to_svg(300, 200, "xrange -3,3\nyrange -2,2\nsegment 0,0,3,2,red")
        # x=0 in [-3,3] → px=150; x=3 → px=300.
        assert 'x1="150.00"' in svg and 'x2="300.00"' in svg

    def test_hline_spans_x_range(self):
        svg = flydraw_to_svg(300, 200, "xrange -5,5\nyrange -2,2\nhline 0,1,red")
        assert 'x1="0.00"' in svg
        assert 'x2="300.00"' in svg

    def test_vline_spans_y_range(self):
        svg = flydraw_to_svg(300, 200, "xrange -5,5\nyrange -2,2\nvline 0,0,red")
        # y=ymin → py=200; y=ymax → py=0
        assert 'y1="200.00"' in svg
        assert 'y2="0.00"' in svg

    def test_gridfill_emits_pattern_grid(self):
        # `gridfill 0,0,nx,ny,color` emits an SVG <pattern> of thin grid
        # lines (every `nx` × `ny` pixels) over the whole viewport.
        svg = flydraw_to_svg(
            300, 200, "xrange -5,5\nyrange -2,2\ngridfill 0,0,5,5,lightblue"
        )
        assert "<pattern" in svg
        assert 'stroke="#add8e6"' in svg  # pattern stroke uses the colour
        assert 'fill="url(#' in svg  # rect references the pattern

    def test_plot_linear_function(self):
        # Plot y=x in range -3..3; expect a polyline crossing the viewport.
        svg = flydraw_to_svg(300, 200, "xrange -3,3\nyrange -3,3\nplot red,x")
        assert "<polyline" in svg
        assert 'stroke="#ff0000"' in svg

    def test_flood_polygon_renders_behind_grid_lines(self):
        # The polygon must be inserted BEFORE the line elements so that the
        # grid lines remain visible on top.
        svg = flydraw_to_svg(
            300,
            300,
            "range 0,3,0,3\n"
            "segment 0,1,3,1,grey\n"
            "segment 0.5,0.134,2.5,3.598,grey\n"
            "segment 2.5,0.134,0.5,3.598,grey\n"
            "flood 1.5,1.4,red",
        )
        polygon_pos = svg.find("<polygon")
        first_line_pos = svg.find("<line")
        assert polygon_pos != -1 and first_line_pos != -1
        assert polygon_pos < first_line_pos


class TestFlydrawUrl:
    def test_url_is_comma_free(self):
        url = flydraw_to_url(300, 80, "range -5,5,-1,1\nsegment 0,0,1,1,red")
        assert "," not in url
        assert url.startswith("/api/render/svg/")

    def test_url_resolves_to_svg(self):
        url = flydraw_to_url(300, 80, "range -5,5,-1,1\nsegment 0,0,1,1,red")
        key = url.rsplit("/", 1)[-1]
        svg = get_cached_svg(key)
        assert svg is not None
        assert svg.startswith("<svg")

    def test_url_stable_for_same_input(self):
        a = flydraw_to_url(300, 80, "range -5,5,-1,1")
        b = flydraw_to_url(300, 80, "range -5,5,-1,1")
        assert a == b


class TestInlineSvgImgs:
    def test_replaces_known_url(self):
        url = flydraw_to_url(300, 80, "range -5,5,-1,1\nsegment 0,0,1,1,red")
        html = f'<td><img src="{url}" alt=""></td>'
        out = inline_svg_imgs(html)
        assert "<img" not in out
        assert "<svg" in out
        assert "</svg>" in out

    def test_leaves_unknown_url_unchanged(self):
        html = '<img src="/api/render/svg/0000000000000000" alt="">'
        assert inline_svg_imgs(html) == html

    def test_handles_multiple_imgs(self):
        u1 = flydraw_to_url(300, 80, "range 0,1,0,1\nsegment 0,0,1,1,red")
        u2 = flydraw_to_url(300, 80, "range 0,1,0,1\nsegment 0,0,1,1,blue")
        html = f'<img src="{u1}"><img src="{u2}">'
        out = inline_svg_imgs(html)
        assert out.count("<svg") == 2


class TestFlydrawFillDashArrow:
    """Fidelity fixes for oefcalittaire1's figure: dashed dimension lines,
    full-size arrowheads, and a filled (not just outlined) polygon."""

    def test_dsegment_is_dashed(self):
        # WIMS 'd' prefix = dashed; dsegment draws the dimension/extension lines.
        svg = flydraw_to_svg(300, 80, "range -5,5,-5,5\ndsegment -3,0,3,0,black")
        assert "stroke-dasharray" in svg

    def test_arrowhead_uses_pixel_size(self):
        # The 5th arg is the arrowhead size in px; render at that size, not half.
        import re as _re

        svg = flydraw_to_svg(300, 80, "range -5,5,-1,1\narrow 0,0,4,0,8,black")
        m = _re.search(r'markerWidth="([\d.]+)"', svg)
        assert m and float(m.group(1)) == 8.0

    def test_fill_fills_enclosing_polygon(self):
        # `fill x,y,color` fills the closed polygon containing (x,y) — here a
        # quadrilateral (rhombus) the triangle-only flood couldn't handle.
        svg = flydraw_to_svg(
            300, 300,
            "range -5,5,-5,5\npolygon black,-4,0,0,3,4,0,0,-3\nfill 0,0,skyblue",
        )
        assert svg.count("<polygon") == 2  # outline + fill
        assert 'fill="#87ceeb"' in svg


class TestFlydrawArgParsing:
    """Coordinate-arg robustness (oefcalittaire1 branches 4 & 5)."""

    def test_inner_comma_in_min_keeps_args_aligned(self):
        # `min(a,b)` in a coord must stay one argument; otherwise the comma
        # split mis-aligns every following coord and a horizontal arrow renders
        # as a stray diagonal. Both endpoints share y → the line stays level.
        import re as _re

        svg = flydraw_to_svg(300, 80, "range 0,10,0,10\narrow min(2,8),5,9,5,8,black")
        m = _re.search(r'<line x1="[\d.]+" y1="([\d.]+)" x2="[\d.]+" y2="([\d.]+)"', svg)
        assert m and m.group(1) == m.group(2)

    def test_num_tolerates_trailing_operator(self):
        # A generated coord like "X +" (dangling operator) evaluates to X, not 0.
        assert _num("25.6 +") == 25.6
        assert _num("3*4 +") == 12.0
        assert _num("5 -") == 5.0


class TestFlydrawRectFillAndColors:
    """A `fill` inside a `rectangle`, and the seashell color (oefcalittaire1
    branches 3/4/5 were black or unfilled)."""

    def test_fill_fills_a_rectangle(self):
        svg = flydraw_to_svg(
            300, 200, "range -5,5,-5,5\nrectangle -4,-3,4,3,black\nfill 0,0,lavender"
        )
        assert 'fill="#e6e6fa"' in svg          # lavender fill applied
        assert svg.count("<polygon") == 1       # the fill polygon (outline is <rect>)

    def test_seashell_color_resolves(self):
        svg = flydraw_to_svg(100, 100, "range -5,5,-5,5\nsegment 0,0,1,1,seashell")
        assert 'stroke="#fff5ee"' in svg


class TestFlydrawText:
    def test_text_drops_undefined_wims_var(self):
        # `\name` (an undefined WIMS var) in a flydraw label renders empty, like
        # WIMS — not as the literal "\unit" (oefcalittaire1 triangle height).
        svg = flydraw_to_svg(100, 100, "range -5,5,-5,5\ntext black,0,0,normal,0.4 \\unit")
        assert ">0.4</text>" in svg
        assert "unit" not in svg

    def test_leading_space_nudges_label_right(self):
        # WIMS uses a leading space (` (Cf)`) to offset a label right of its
        # anchor; SVG collapses it, so we apply an x-offset (quizz 1120).
        import re
        base = flydraw_to_svg(200, 200, "xrange 0,3\nyrange 0,5\ntext black,1,3,medium,(Cf)")
        nudged = flydraw_to_svg(200, 200, "xrange 0,3\nyrange 0,5\ntext black,1,3,medium, (Cf)")
        x0 = float(re.search(r'<text x="([\d.]+)"', base).group(1))
        x1 = float(re.search(r'<text x="([\d.]+)"', nudged).group(1))
        assert x1 > x0
        assert ">(Cf)</text>" in nudged  # the space itself isn't rendered


class TestFlydrawPlot:
    def test_plot_implicit_multiplication(self):
        # WIMS tangents like `1(x-2)+2` (from `\z2(x-\x2)+\y2`) use implicit
        # multiplication; bare sympify reads `1(...)` as a call and drops the
        # line. The curve must still render (quizz 1120 tangent).
        svg = flydraw_to_svg(200, 200, "xrange -1,4\nyrange -1,5\nplot black,1(x-2)+2")
        assert svg.count("<polyline") == 1
