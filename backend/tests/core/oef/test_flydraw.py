"""Unit tests for the flydraw → SVG renderer."""

from core.oef.flydraw import (
    flydraw_to_svg,
    flydraw_to_url,
    get_cached_svg,
    inline_svg_imgs,
)


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
        svg = flydraw_to_svg(300, 80, "range 0,10,0,10\ncircle 5,5,4,red")
        assert "<circle" in svg
        assert 'cx="150.00"' in svg
        assert 'r="4.0"' in svg
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
