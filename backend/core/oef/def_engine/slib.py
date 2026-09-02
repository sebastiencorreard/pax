"""Sub-script (slib) execution + the small built-in proc handlers.

WIMS exercises delegate to *slib* scripts (under ``<module>/slib/<name>``
or the WIMS shared ``slib/<…>`` tree) and to the ``oef/draw.phtml`` /
``slib/stat/median`` built-ins. Both are entered through ``!readproc`` in
the .def, with the question section sometimes calling them via
``!read oef/draw.phtml`` for inline graphs.

The mixin in this module provides:

- ``_cmd_readproc`` — dispatcher: handles the two built-ins and
  delegates ``slib/<name>`` to ``_run_slib``.
- ``_run_slib`` — locates the script (module-local first, then the
  vendored WIMS ``scripts/slib/`` tree), reads it, and runs the line
  list through ``_run_script_lines`` while sharing the engine's ctx.
- ``_run_script_lines`` — flat single-pointer interpreter for the
  WIMS-script subset that slib needs (``!if/!else/!endif``,
  ``!for/!next``, ``!goto :label``, ``!exit``). Distinct from
  ``DefEngine._exec`` which walks the structured ``Instruction`` tree
  parsed from the .def itself.
- ``_compute_weighted_median`` — built-in for ``slib/stat/median`` so
  we don't have to fully run that slib's chain of dependencies.
- ``_find_wims_scripts_dir`` — walks up from ``def_path`` to find the
  vendored WIMS scripts directory.

The mixin reaches into ``DefEngine`` for ``ctx`` (the var dict),
``def_path`` (for path resolution), and the helpers ``_subst``,
``_eval_value``, ``_eval_arith``, ``_eval_condition``, ``_eval_cmd``.
"""

from __future__ import annotations

import os
import random
import re

from . import wims_lists as wl
from .cas import _MATH_NS  # noqa: F401  # re-exported for callers if needed


class _SlibExit(Exception):
    """Sentinel raised by `!exit` inside a slib script to stop execution."""


def _restaurer_boucle(ctx: dict, boucle: dict) -> None:
    """Rend à la variable d'une boucle la valeur qu'elle avait avant elle.

    Un `!for` de WIMS n'expose pas sa variable au-delà de son corps ; la
    version récursive de cet interpréteur le faisait en restaurant `saved`
    après l'appel. Le comportement est le même, qu'on sorte par le `!next`
    ou par un `!goto`.
    """
    var, saved = boucle.get("var"), boucle.get("saved")
    if not var:
        return
    if saved is not None:
        ctx[var] = saved
    else:
        ctx.pop(var, None)


class _SlibMixin:
    """Slib runner methods. Mixed into ``DefEngine`` — see ``runtime`` notes."""

    # Attributes provided by the concrete ``DefEngine`` class.
    ctx: dict[str, str]
    def_path: str | None
    rng: "random.Random"
    _getfile_store: dict[str, str]

    # Methods provided by the concrete ``DefEngine`` class. Stub bodies make
    # ``self._subst(...)`` resolvable for type-checkers; at runtime the MRO
    # picks ``DefEngine``'s real implementations, which override these.
    def _subst(self, s: str) -> str: ...

    def _eval_value(self, value: str) -> str: ...

    def _eval_arith(self, expr: str) -> str: ...

    def _eval_condition(self, kind: str, condition: str) -> bool: ...

    def _eval_cmd(self, cmd: str, args: str) -> str: ...

    # ── Public slib entry points ────────────────────────────────────────────

    def _cmd_randrecord(self, args: str) -> str:
        """``!randrecord <path>`` — pick a random record from a `.don` data file.

        Mirrors WIMS ``calc.c:calc_randfile``: records are separated by lines
        starting with ``:`` (WIMS' ``tag_string`` is ``"\\n:"``). Path is
        resolved relative to the .def file's module directory.
        """
        if not self.def_path:
            return ""
        path = self._subst(args.strip().split()[0]) if args.strip() else ""
        if not path:
            return ""
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        # `find_module_file` concatène le texte — `mkfname(buf,"%s/%s",…)` —, là
        # où `os.path.join` prend un chemin commençant par `/` pour un absolu et
        # jette le préfixe. C'est ainsi que le `!randfile /data1` de
        # `mouvrel/vitesse1` cherchait à la racine du disque : le module y perdait
        # ses données, et avec elles ses cinq réponses.
        full = f"{module_dir}/{path}"
        if not os.path.exists(full):
            return ""
        try:
            with open(full, encoding="utf-8") as f:
                text = f.read()
        except UnicodeDecodeError:
            with open(full, encoding="cp1252") as f:
                text = f.read()

        chunks = re.split(r"(?:^|\n):", text)
        records = [c.strip("\n") for c in chunks if c.strip()]
        if not records:
            return ""
        return self.rng.choice(records)

    def _cmd_readproc(self, args: str) -> None:
        """`!readproc <path> <args>` — execute a slib script or built-in proc.

        Supports two destinations:
        - ``oef/draw.phtml`` — built-in: render flydraw commands to an SVG
          data URI, store it in ``ctx['ins_url']``.
        - ``slib/<name>`` — read the script next to the .def file and run it
          as a sub-engine sharing this engine's ctx.
        """
        from ..flydraw import flydraw_to_url  # noqa: PLC0415

        rest = args.strip()
        m = re.match(r"^(\S+)\s*(.*)$", rest, re.DOTALL)
        if not m:
            return
        path = m.group(1).strip()
        proc_args = self._subst(m.group(2).strip())

        if path == "oef/img.phtml":
            self.ctx["_proc_html"] = self._proc_img(proc_args)
            return

        if path == "slib/stat/median":
            self.ctx["slib_out"] = self._compute_weighted_median(proc_args)
            return

        if path in ("oef/draw.phtml", "oef/canvasdraw.phtml"):
            head, _, body = proc_args.partition("\n")
            size_parts = [p.strip() for p in head.split(",")]
            try:
                xsize = int(float(size_parts[0])) if size_parts else 300
                ysize = int(float(size_parts[1])) if len(size_parts) > 1 else 80
            except ValueError:
                xsize, ysize = 300, 80
            # Module dir (…/quizz.fr) so `copy <file>` finds module-local images
            # (images/<file>), e.g. 1128's probability-tree skeleton.
            mod_dir = os.path.dirname(os.path.dirname(self.def_path)) if self.def_path else None
            url = flydraw_to_url(xsize, ysize, body, base_dir=mod_dir)
            # $ins_url stays a bare URL — WIMS callers wrap it explicitly in <img>.
            # $canvasdraw_out is used inline in question text without an explicit
            # <img>, so we store it as a ready-to-render <img> tag.
            self.ctx["ins_url"] = url
            # `$ins_filename` — WIMS y met le nom du fichier qu'il vient de
            # produire (`insert-3.gif`), et `slib/oef/insfilename` le rend aux
            # exercices qui doivent **désigner** cette image : la zone `bound`
            # d'un `type=coord` y renvoie pour dire « la région de cette
            # figure-là ». PAX ne produit pas de fichier, mais son URL de SVG
            # joue le même rôle de poignée — c'est elle qu'on pose.
            self.ctx["ins_filename"] = url
            self.ctx["canvasdraw_out"] = f'<img src="{url}" alt="">'
            return

        if path == "slib/geo2D/jsxgraph":
            self.ctx["slib_out"] = self._render_jsxgraph(proc_args)
            return

        if path == "slib/data/random":
            self.ctx["slib_out"] = self._slib_data_random(proc_args)
            return

        if path == "slib/commutesom":
            self.ctx["slib_out"] = self._slib_commutesom(proc_args)
            return

        if path == "slib/numeration/ecriturelettre":
            res = _ecriture_lettre(proc_args)
            if res is not None:
                self.ctx["slib_out"] = res
                return
            # Non-trivial case (en/it, ordinals, options) → fall through to the
            # generic runner below.

        if path.startswith("slib/"):
            self._run_slib(path, proc_args)
            # `draw/repere` returns "x0,y0\nex,-ey\n<commands>": its first two
            # rows are the pixel↔repère affine transform. Stash it so a `coord`
            # answer can report the click in repère units, not raw pixels.
            if path == "slib/draw/repere":
                rows = (self.ctx.get("slib_out") or "").split("\n")
                if len(rows) >= 2:
                    o = [p.strip() for p in rows[0].split(",")]
                    s = [p.strip() for p in rows[1].split(",")]
                    if len(o) >= 2 and len(s) >= 2:
                        self.ctx["_repere_transform"] = f"{o[0]},{o[1]},{s[0]},{s[1]}"
            return

        if path == "oef/steps.proc":
            self._proc_steps()
            return

        if path == "oef/togetfile.proc":
            self._proc_togetfile(proc_args)
            return

        # `gp/<nom>.gp` — une bibliothèque PARI, que le script pose dans une
        # variable (`!set slib_header_patron=…`) avant qu'un `!exec pari` ne
        # l'exécute. Ce n'est pas un slib : ni `slib_out`, ni paramètres. Sans
        # cette lecture, `slib/geo2D/polynet` appelait `!exec pari` sur une
        # chaîne vide, et les six exercices d'`oefpolynet` restaient muets.
        if path.startswith("gp/"):
            self._run_slib(path, proc_args)
            return

        # Les deux procs qu'on laisse tomber, et pourquoi chacun est **inerte**
        # — mesuré au rendu, pas déduit des sources :
        #
        #   oef/drawtikz.phtml   43 appels. Sa deuxième ligne est
        #                        `!if $printlatex!=yes → !exit` : il ne sert
        #                        que l'export LaTeX, que PAX n'a pas et dont
        #                        il ne pose jamais le drapeau. L'exécuter
        #                        serait un non-événement.
        #   js/geogebra/test     12 appels. Le fichier **n'existe pas**, pas
        #                        même dans l'arbre WIMS vendorisé : son rôle
        #                        est de poser `geogebra_exists`, et son absence
        #                        *est* la réponse. `slib/geo2D/geogebra` en
        #                        tire déjà l'avertissement de WIMS,
        #                        « GeoGebra is not installed ».
        #
        # Aucun des deux n'attend d'être porté : le premier est mort-né, le
        # second dit déjà la vérité. (`oef/togetfile.proc` complétait la liste
        # tant que Jmol manquait ; il est porté, plus haut.)
        return

    def _proc_togetfile(self, args: str) -> None:
        """`!readproc oef/togetfile.proc <nom> <mode>\\n<contenu>` — le magasin
        de fichiers de la session.

        WIMS écrit là un vrai fichier, sous `getfile/` dans le répertoire de
        session, et le ressert par `?cmd=getfile&special_parm=<nom>`. C'est par
        ce détour que la molécule atteint l'applet : `slib/geo3D/off2jmol` y
        dépose le `.xyz` (les coordonnées) et le `.spt` (le script Jmol), puis
        passe les deux URL à `slib/chemistry/jmolshow`.

        PAX n'a pas de session côté moteur, et n'a pas besoin d'en fabriquer
        une : le producteur et son unique lecteur — `_render_jmol_embed`, plus
        bas dans le même rendu — vivent dans le même moteur. Le magasin est
        donc un attribut d'instance, et l'URL rendue au script n'est qu'un
        jeton que ce lecteur redéréférence. Aucune route ne le sert : le
        contenu part vers le navigateur **inline**, dans le segment.

        Un attribut, et non une entrée de `ctx` : le contexte ne contient que
        des chaînes, et `_subst` s'y casse les dents sur tout le reste
        (`'dict' object has no attribute 'strip'`).

        Deux modes, ceux de WIMS : `new` écrase, `append` ajoute une ligne.
        `polyhedra` a besoin des deux — il écrit les sommets d'un polyèdre par
        tranches de 25 pour ne pas gonfler une variable sans fin.
        """
        entete, _, contenu = args.partition("\n")
        morceaux = entete.split()
        if not morceaux:
            return
        nom = morceaux[0]
        mode = morceaux[1].lower() if len(morceaux) > 1 else "new"
        magasin = self._getfile_store
        if mode == "append" and nom in magasin:
            magasin[nom] = f"{magasin[nom]}\n{contenu}"
        else:
            magasin[nom] = contenu

    def _proc_steps(self) -> None:
        r"""`!readproc oef/steps.proc` — normalise `oefsteps` et en tire ses
        compteurs.

        Le proc met la description des étapes sous une forme unique avant que
        quiconque la lise : tabulations en séparateurs de rangée, minuscules,
        `reply`/`replies` abrégés en `r` et `choice`/`choices` en `c`, blancs
        retirés, une étape par ligne. Il pose ensuite `oefstepcnt`, `rr`, `cc`,
        `creplycnt` et `cchoicecnt`.

        **Aucun exercice du corpus ne lit ces compteurs** : ils alimentent la
        machinerie de WIMS, pas les `.def`. Le seul effet qui porte est donc la
        normalisation en place, dont les consommateurs de PAX ont besoin — ils
        comparent des jetons `r1`, `c2`, et un `Reply 1` écrit par l'auteur ne
        leur ressemble pas.

        Une adaptation, et une seule : là où WIMS sépare les étapes par des
        tabulations, PAX porte de vrais sauts de ligne (`_merge_continuations`
        les produit, et le `.def` les encode ainsi). Les deux valent donc
        séparateur — sans quoi `!nospace`, qui chez WIMS peut retirer un saut
        de ligne sans dommage puisqu'il n'y en a jamais, souderait ici toutes
        les étapes en une.
        """
        brut = str(self.ctx.get("oefsteps", ""))
        if not brut.strip():
            self.ctx["oefstepcnt"] = "0"
            self.ctx["oefstep"] = "0"
            return
        s = re.sub(r"[\t\n\r]+", ";", brut).lower()
        for long, court in (
            ("replies", "r"), ("choices", "c"), ("reply", "r"), ("choice", "c")
        ):
            s = s.replace(long, court)
        s = re.sub(r"[^\S;]", "", s)
        lignes = [x for x in s.split(";") if x]
        # `!if $dynstep=yes` : une étape dynamique ne décrit que la courante.
        if str(self.ctx.get("dynstep", "")).strip().lower() == "yes" and lignes:
            lignes = lignes[:1]
        self.ctx["oefsteps"] = "\n".join(lignes)
        self.ctx["oefstepcnt"] = str(len(lignes))
        joint = "".join(lignes)
        self.ctx["rr"] = "r" * joint.count("r")
        self.ctx["cc"] = "c" * joint.count("c")
        self.ctx["creplycnt"] = str(joint.count("r"))
        self.ctx["cchoicecnt"] = str(joint.count("c"))
        if not str(self.ctx.get("oefstep", "")).strip():
            self.ctx["oefstep"] = "1"

    def _proc_img(self, args: str) -> str:
        """`!read oef/img.phtml CHEMIN [ATTRIBUTS]` — la balise `<img>` d'un `\\img{}`.

        Port du script (`scripts/oef/img.phtml`), qui tient en huit lignes :

            !set imgf_=!word 1 of $wims_read_parm
            !set imgf_=!replace internal datamodule by modules/data in $imgf_
            !if .. isin $imgf_
              !exit
            !endif
            !set options=!word 2 to -1 of $wims_read_parm
            !set newf_=!rename $imgf_
            !if alt notin $options
              !set options=$options alt=""
            !endif
            <img src="$newf_" $options>

        Le `!exit` sur `..` est une garde anti-remontée — le commentaire du
        script dit « avoids module errors if people try to hack » — et rend
        alors la chaîne vide, pas une balise.
        """
        parts = args.split()
        if not parts:
            return ""
        imgf = parts[0].replace("datamodule", "modules/data")
        if ".." in imgf:
            return ""
        options = " ".join(parts[1:])
        newf = self._cmd_rename(imgf)
        if "alt" not in options:
            options = f'{options} alt=""'
        return f'<img src="{newf}" {options}>'

    def _slib_commutesom(self, args: str) -> str:
        """Built-in for ``slib/commutesom POLY,VAR``.

        WIMS' commutesom returns *every* commutative ordering of a developed
        polynomial's monomials (liste séparée par des virgules), forme réduite
        canonique en tête. Deux usages :
        - tolérance d'ordre pour un `litexp` : chaque ordre est une alternative
          acceptée (et le flag `_commutesom_anyorder` marque l'answer `expand`) ;
        - affichage direct d'un ordre précis via `!item N of` (oefremplacer2 :
          E = forme développée, prise dans la liste).

        WIMS le fait via ``coeff``/``hipow`` Maxima + une table ``commutesom.don``
        que notre sous-moteur ne sait pas exécuter (ça fuyait en ``coeff(…)``
        littéral). On génère ici la liste avec SymPy : monômes en degré
        décroissant, puis toutes leurs permutations (bornées à 5 monômes pour
        éviter l'explosion factorielle). Repli sur l'entrée si parsing impossible.
        """
        self.ctx["_commutesom_anyorder"] = "1"
        poly_s = args.split(",")[0].strip()
        if not poly_s:
            return poly_s
        try:
            import itertools  # noqa: PLC0415
            import sympy  # noqa: PLC0415
            from sympy.parsing.sympy_parser import (  # noqa: PLC0415
                parse_expr,
                standard_transformations,
                implicit_multiplication_application,
            )
        except Exception:
            return poly_s
        try:
            T = standard_transformations + (implicit_multiplication_application,)
            expr = sympy.expand(
                parse_expr(poly_s.replace("^", "**"), transformations=T)
            )
            # Monômes du polynôme développé, en degré décroissant (forme
            # canonique « réduire »). On découpe la chaîne ordonnée par sstr
            # (`order='lex'`) plutôt que via make_args (qui réordonne).
            canon_str = sympy.sstr(expr, order="lex").replace("**", "^")
            _raw = re.split(r"\s+([+-])\s+", canon_str)
            term_strs = [_raw[0].strip()]
            for _i in range(1, len(_raw), 2):
                term_strs.append(("-" if _raw[_i] == "-" else "") + _raw[_i + 1].strip())
            canonical = _join_terms(term_strs)
            # WIMS commutesom renvoie TOUTES les permutations commutatives des
            # monômes (liste séparée par des virgules) — certaines exercices
            # l'utilisent directement (`!item N of`, oefremplacer2). Au-delà de
            # 5 monômes la factorielle explose : on se limite alors à la forme
            # canonique (le checker litexp reste tolérant à l'ordre via les
            # alternatives et le flag `_commutesom_anyorder`).
            if not (2 <= len(term_strs) <= 5):
                return canonical
            orderings = [_join_terms(list(p)) for p in itertools.permutations(term_strs)]
            # Canonique en tête (litexp affiche `!item 1` comme réponse type).
            seen = {canonical}
            ordered = [canonical] + [o for o in orderings if not (o in seen or seen.add(o))]
            return ",".join(ordered)
        except Exception:
            return poly_s

    def _slib_data_random(self, args: str) -> str:
        """Built-in for ``slib/data/random N,type,data`` — N random items of
        ``data`` (no replacement), seeded. ``type`` is item / word / row; the
        WIMS script chokes in our sub-engine (!distribute/!bound/…), so emulate
        it (couf builds its constant terms this way; without it the list was
        empty and the whole CAS chain derailed).
        """
        parts = args.split(",")
        if len(parts) < 3:
            return ""
        try:
            n = int(float(parts[0].strip()))
        except (ValueError, TypeError):
            return ""
        typ = parts[1].strip().lower()
        data = ",".join(parts[2:]).strip()
        if typ in ("word", "words"):
            items, sep = [w for w in data.split() if w], " "
        elif typ in ("row", "rows", "line", "lines"):
            items, sep = [r.strip() for r in re.split(r"[;\n]", data) if r.strip()], ";"
        else:  # item(s) — comma-separated
            items, sep = [c.strip() for c in data.split(",") if c.strip()], ","
        if not items:
            return ""
        n = max(1, min(n, len(items)))
        shuffled = items[:]
        self.rng.shuffle(shuffled)
        return sep.join(shuffled[:n])

    @staticmethod
    def _declose(s: str) -> str:
        """Strip one outer matching bracket pair: ``[python,[c]]`` → ``python,[c]``."""
        s = s.strip()
        if len(s) >= 2 and s[0] in "([{" and s[-1] in ")]}":
            return s[1:-1]
        return s

    # Le service que `jmolshow` désigne pour résoudre un identifiant chimique
    # (nom courant, SMILES, InChI) en un modèle 3D. Ce n'est pas PAX qui
    # l'interroge : l'URL part telle quelle dans le `set loadFormat` du script,
    # et c'est l'applet, dans le navigateur, qui va la chercher.
    _CACTUS = (
        "https://cactus.nci.nih.gov/chemical/structure/%FILE"
        "/file?format=sdf&get3d=True"
    )

    def _render_jmol_embed(self, params: str) -> str:
        """Built-in pour `slib/chemistry/jmolshow` : émet un marqueur `pax-jmol`
        portant la configuration de l'applet en JSON.

        Paramètres WIMS (`!distribute items`) :
        ``<fichier>,<largeur>,<hauteur>,<couleur>,<script>,<id>,<type>``

        Le premier en porte tout l'intérêt : **trois branches**, et le corpus
        les emprunte toutes les trois (mesuré sur les neuf exercices Jmol,
        trois graines) —

        - **un jeton de session** (`?…&+cmd=getfile&+special_parm=…`), déposé
          par `oef/togetfile.proc`. C'est la voie de `slib/geo3D/polyhedra` :
          `off2jmol` calcule le `.xyz` (les sommets) et le `.spt` (le script de
          tracé), le proc les range, et on les redéréférence ici pour les
          envoyer **inline**. 36 rendus sur 36, aucune donnée manquante.
        - **un chemin de fichier du module** — `data/benzene.pdb` chez
          `structure`, 1033 o déjà convertis et commités. Lu sur disque.
        - **un identifiant préfixé** (`@`, `=` ou `$`) — un SMILES chez
          `isomerie` et `jmol` (`@CCCCC`, `@C(=O)`). Il n'y a rien à lire :
          seul un convertisseur sait en tirer de la 3D. WIMS appelle
          `obabel.sh` et, sur son échec, laisse l'applet interroger cactus.
          PAX n'embarque pas Open Babel (`!exec obabel.sh` rend `-1`), donc
          c'est toujours cactus — 18 rendus sur 18.

        Le `<script>` reçoit le même traitement : `polyhedra` y passe
        ``script "<jeton .spt>";zoom 180``, dont le jeton se résout en contenu.
        """
        import html as _html  # noqa: PLC0415
        import json as _json  # noqa: PLC0415

        parts = wl.cutitems(params)

        def arg(i: int) -> str:
            return parts[i].strip() if len(parts) > i else ""

        fichier = arg(0)
        largeur = self._entier(arg(1), 200)
        hauteur = self._entier(arg(2), 200)
        couleur = arg(3) or "white"
        script = arg(4)
        applet_id = arg(5) or "0"

        cfg: dict = {
            "id": f"jmolApplet_{applet_id}",
            "width": largeur,
            "height": hauteur,
            "color": couleur,
        }

        # --- le modèle -----------------------------------------------------
        # Les trois préfixes que le slib traite ensemble : `$` (arrivé encodé
        # en `&#36;` quand il a traversé du HTML), `=` et `@`. Tous trois
        # disent « ceci n'est pas un fichier, c'est un identifiant ».
        nu = fichier
        for prefixe in ("&#36;", "$", "=", "@"):
            if nu.startswith(prefixe):
                nu = nu[len(prefixe) :]
                cfg["loadFormat"] = self._CACTUS
                cfg["load"] = f'load "={nu}";'
                break
        else:
            contenu = self._resoudre_fichier_jmol(fichier)
            cfg["data"] = contenu

        # --- le script -----------------------------------------------------
        # `script "<jeton>"` désigne un `.spt` du magasin : on l'inline, sans
        # quoi l'applet irait chercher une URL que PAX ne sert pas.
        def _inline_spt(m: re.Match) -> str:
            corps = self._resoudre_fichier_jmol(m.group(1))
            return corps if corps else ""

        script = re.sub(r'script\s+"([^"]*)"\s*;?', _inline_spt, script)

        # La queue que `jmolshow` ajoute toujours. `set DisablePopupMenu FALSE`
        # est inconditionnel chez WIMS — le slib pose la variable dans un `!if`
        # puis l'écrase juste après, si bien que le menu reste toujours actif ;
        # on reproduit son effet, pas son intention.
        survol = "" if "hover" in script else " hover off;"
        cfg["script"] = (
            f"{script}\n"
            "selectionhalos on;select none;set picking off;set frank off;"
            f"set DisablePopupMenu FALSE;{survol}"
        ).strip()

        charge = _html.escape(_json.dumps(cfg, ensure_ascii=False), quote=True)
        return (
            f'<div class="pax-jmol" id="{cfg["id"]}" '
            f'data-w="{largeur}" data-h="{hauteur}" data-jmol="{charge}"></div>'
        )

    @staticmethod
    def _entier(valeur: str, defaut: int) -> int:
        """Une taille WIMS, qui peut être vide (le slib a ses `!default`)."""
        try:
            return int(float(valeur))
        except (TypeError, ValueError):
            return defaut

    def _resoudre_fichier_jmol(self, ref: str) -> str:
        """Le contenu derrière une référence de `jmolshow` : jeton, puis disque.

        L'ordre compte — un jeton de session (`…&+special_parm=file_35.xyz`)
        n'est pas un chemin, et le chercher sur disque ne rendrait rien.
        """
        ref = ref.strip()
        if not ref:
            return ""
        jeton = re.search(r"special_parm=([^&\s]+)", ref)
        if jeton:
            return str(self._getfile_store.get(jeton.group(1), ""))
        if not self.def_path:
            return ""
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        # `jmolshow` retire `$module_dir/` d'un chemin absolu WIMS avant de
        # relire ; ici les chemins sont relatifs au module, plus le repli sur
        # l'arbre `wims-scripts` (c'est là que vivent les `data/molecule_pdb`).
        candidats = [os.path.join(module_dir, ref)]
        scripts_dir = self._find_wims_scripts_dir()
        if scripts_dir:
            candidats.append(os.path.join(scripts_dir, ref))
        for chemin in candidats:
            if os.path.isfile(chemin):
                try:
                    with open(chemin, encoding="utf-8") as f:
                        return f.read()
                except (OSError, UnicodeDecodeError):
                    continue
        return ""

    def _render_codeeditor(self, params: str) -> str:
        """Built-in for the slib ``coding/editor``: parse its argument string and
        emit a ``pax-codeeditor`` marker carrying the editor config as JSON.

        Args (WIMS): ``<codes>,<id>,<options>`` where ``<codes>`` is either a
        single ``[lang,[code]]`` or a multi list ``[[lang,[code],name,ro?],…]``,
        and ``<options>`` are space-separated words (``readonly``, ``fullscreen``,
        ``init``, ``theme=[a,b]``, ``instruction=[…]``). Newlines inside code are
        stored as TABs (WIMS convention) — restored to ``\\n`` here.
        """
        import html as _html  # noqa: PLC0415
        import json as _json  # noqa: PLC0415

        parts = wl.cutitems(params)
        code_field = parts[0].strip() if parts else ""
        editor_id = self._declose(parts[1]).strip() if len(parts) > 1 else "0"
        options = parts[2].strip() if len(parts) > 2 else ""

        # Options: space/comma-separated tokens, separators inside [...] kept.
        tokens: list[str] = []
        cur: list[str] = []
        depth = 0
        for ch in options:
            if ch == "[":
                depth += 1
            elif ch == "]":
                depth = max(0, depth - 1)
            if depth == 0 and (ch.isspace() or ch == ","):
                if cur:
                    tokens.append("".join(cur))
                    cur = []
            else:
                cur.append(ch)
        if cur:
            tokens.append("".join(cur))
        words = {t.lower() for t in tokens if "=" not in t}

        def getopt(key: str) -> str:
            for t in tokens:
                if "=" in t:
                    k, v = t.split("=", 1)
                    if k.strip().lower() == key:
                        return v.strip()
            return ""

        readonly_global = "readonly" in words
        theme_raw = getopt("theme")
        themes = [x.strip() for x in wl.cutitems(self._declose(theme_raw)) if x.strip()] if theme_raw else []
        instr_raw = getopt("instruction")
        instructions = [x.strip() for x in wl.cutitems(self._declose(instr_raw)) if x.strip()] if instr_raw else []

        def one_code(fields: list[str]) -> dict:
            lang = fields[0].strip() if fields else ""
            # `slib/coding/editor` : `!replace internal $\t$ by $\n$` — les
            # tabulations du `.def` sont les retours à la ligne du code source.
            #
            # Le slib fait lui-même cette conversion, mais pour un contexte JS :
            # il pose les deux caractères `\` et `n`, que le navigateur de WIMS
            # relit comme un saut de ligne en interprétant la chaîne. PAX
            # sérialise le code en JSON, où cette séquence ressortirait telle
            # quelle dans l'éditeur ; on la relit donc ici. La tabulation reste
            # traitée pour les appels qui n'ont pas traversé le slib.
            brut = self._declose(fields[1]) if len(fields) > 1 else ""
            code = brut.replace("\t", "\n").replace("\\n", "\n")
            name = fields[2].strip() if len(fields) > 2 else ""
            ro = readonly_global or (len(fields) > 3 and "readonly" in fields[3].lower())
            return {"lang": lang, "code": code, "name": name, "readonly": ro}

        inner = self._declose(code_field)
        sub = wl.cutitems(inner)
        if sub and sub[0].strip().startswith("["):
            codes = [one_code(wl.cutitems(self._declose(item))) for item in sub]
        else:
            codes = [one_code(sub)]

        config = {
            "id": editor_id or "0",
            "themes": themes,
            "fullscreen": "fullscreen" in words,
            "init": "init" in words,
            "instructions": instructions,
            "codes": codes,
        }
        data = _html.escape(_json.dumps(config, ensure_ascii=False), quote=True)
        return f'<div class="pax-codeeditor" data-codeeditor="{data}"></div>'

    def _render_jsxgraph(self, proc_args: str) -> str:
        """Built-in for ``slib/geo2D/jsxgraph``: emit a marker div that
        _segment_statement turns into a ``jsxgraph`` segment, rendered by the
        ExerciseJsxgraph Vue component.

        Args from the .def are ``<divid> <boardvar>,[<size>], <jscode>``. We
        keep the div id (the JS calls ``initBoard('<divid>', …)``) and the
        board-init JS. Because it becomes segment *data* (not statement HTML),
        the KaTeX pass never sees the ``\\(d_1\\)``-style labels inside it.
        """
        import html as _html  # noqa: PLC0415

        m = re.match(r"(\S+)\s+[^,]*,\s*\[([^\]]*)\]\s*,(.*)", proc_args, re.DOTALL)
        if m:
            div_id, size_spec, js = m.group(1).strip(), m.group(2), m.group(3).strip()
        else:
            div_id, size_spec, js = "jsxbox", "", proc_args.strip()
        wh = re.search(r"(\d+)\s*x\s*(\d+)", size_spec)
        w, h = (int(wh.group(1)), int(wh.group(2))) if wh else (500, 500)
        mx = re.search(r"max\s*=\s*(\d+)\s*px", size_spec)
        maxw = int(mx.group(1)) if mx else 500
        mn = re.search(r"min\s*=\s*(\d+)\s*px", size_spec)
        minw = int(mn.group(1)) if mn else 0
        minw_attr = f' data-minw="{minw}"' if minw else ""
        return (
            f'<div class="pax-jsxgraph" id="{div_id}" '
            f'data-w="{w}" data-h="{h}" data-maxw="{maxw}"{minw_attr} '
            f'data-jsxgraph="{_html.escape(js, quote=True)}"></div>'
        )

    def _run_slib(self, slib_path: str, params: str) -> None:
        """Locate and execute a ``slib/<name>`` script."""
        from ..def_parser import _merge_continuations  # noqa: PLC0415

        # The WYSIWYG code editor (slib `coding/editor`, often vendored locally
        # as `slib/editor`) builds a CodeMirror widget out of inline <script>s,
        # which can't run when injected via the front-end's v-html. Emit a
        # structured marker instead — _segment_statement turns it into a
        # `codeeditor` segment rendered by the Codemirror Vue component.
        if slib_path.rsplit("/", 1)[-1] == "editor":
            self.ctx["slib_out"] = self._render_codeeditor(params)
            return

        # `slib/chemistry/jmolshow` — même raison que l'éditeur : le slib rend
        # un `<script>` inline qui construit l'objet `Info` de `Jmol.getApplet`,
        # et un `<script>` injecté par le `v-html` du front ne s'exécute pas.
        # On émet un marqueur `pax-jmol` que le composant Vue interprète.
        if slib_path.rsplit("/", 1)[-1] == "jmolshow":
            self.ctx["slib_out"] = self._render_jmol_embed(params)
            return

        if not self.def_path:
            return
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        wims_scripts_dir = self._find_wims_scripts_dir()
        candidates = [os.path.join(module_dir, slib_path)]
        if slib_path.startswith("slib/"):
            candidates.append(
                os.path.join(module_dir, "slib", "local", slib_path[len("slib/") :])
            )
        if wims_scripts_dir:
            candidates.append(os.path.join(wims_scripts_dir, slib_path))
        script_path = next((p for p in candidates if os.path.exists(p)), None)
        if not script_path:
            return
        try:
            with open(script_path, encoding="utf-8") as f:
                text = f.read()
        except UnicodeDecodeError:
            with open(script_path, encoding="cp1252") as f:
                text = f.read()

        saved_parm = self.ctx.get("wims_read_parm", "")
        self.ctx["wims_read_parm"] = params

        lines = _merge_continuations(text.split("\n"))
        try:
            self._run_script_lines(lines)
        except _SlibExit:
            pass
        finally:
            self.ctx["wims_read_parm"] = saved_parm

    def _compute_weighted_median(self, args: str) -> str:
        """Compute the median for ``slib/stat/median`` argument forms.

        Accepts the WIMS ``slib_example`` shapes:
        - ``[v1,v2,...]`` — flat list, plain median
        - ``[v1,v2,...; w1,w2,...]`` — values + weights
        - ``[v1,v2,...],[w1,w2,...]`` — values, weights as separate lists
        """
        s = args.strip()
        if s.startswith("[") and s.endswith("]"):
            s = s[1:-1]
        elif s.startswith("[") and "],[" in s:
            s = s[1:-1].replace("],[", ";")

        if ";" in s:
            v_str, w_str = s.split(";", 1)
            values = [
                self._eval_arith(x.strip()) for x in v_str.split(",") if x.strip()
            ]
            weights = [
                self._eval_arith(x.strip()) for x in w_str.split(",") if x.strip()
            ]
        else:
            values = [self._eval_arith(x.strip()) for x in s.split(",") if x.strip()]
            weights = ["1"] * len(values)

        try:
            vals_f = [float(v) for v in values]
            wts_i = [int(round(float(w))) for w in weights]
        except (ValueError, TypeError):
            return ""

        expanded: list[float] = []
        for v, w in zip(vals_f, wts_i):
            if w > 0:
                expanded.extend([v] * w)
        if not expanded:
            return "0"
        expanded.sort()
        n = len(expanded)
        if n % 2 == 1:
            med = expanded[n // 2]
        else:
            med = (expanded[n // 2 - 1] + expanded[n // 2]) / 2
        if med == int(med):
            return str(int(med))
        return f"{med:g}"

    def _find_wims_scripts_dir(self) -> str | None:
        """Locate the WIMS scripts directory.

        Walks up from ``def_path`` looking for either ``wims-scripts/`` (the
        vendored subset committed under ``ressources/``) or the full
        ``wims/public_html/scripts/`` tree (only present when developing
        against a local WIMS checkout). The first match wins.
        """
        if not self.def_path:
            return None
        d = os.path.abspath(self.def_path)
        for _ in range(10):
            d = os.path.dirname(d)
            if not d:
                break
            for sub in ("wims-scripts", os.path.join("wims", "public_html", "scripts")):
                candidate = os.path.join(d, sub)
                if os.path.isdir(candidate):
                    return candidate
            if d == "/":
                break
        return None

    def _run_script_lines(self, lines: list[str]) -> None:
        """Execute a flat WIMS-script sequence (used for slib scripts).

        Single-pointer interpreter: walks the line list once with branching
        controlled by setting `i` directly. Supports ``!if/!else/!endif``,
        ``!goto :label``, ``!for/!next``, ``!exit``. Designed so a ``!goto``
        nested inside an ``!if`` body can still jump to a top-level
        ``:label`` marker — which is the common slib idiom for the
        help/help_proc dispatch.
        """
        labels: dict[str, int] = {}
        for idx, raw in enumerate(lines):
            s = raw.strip()
            if s.startswith(":") and len(s) > 1 and not s.startswith("::"):
                labels[s[1:].strip()] = idx

        if_stack: list[int] = []
        # Boucles en cours. Les tenir ici plutôt que dans la pile d'appels
        # Python rend l'interpréteur réellement « plat » : un `!goto` peut
        # sauter hors d'une boucle, ce que le corps exécuté récursivement
        # interdisait — le label lui restait invisible.
        loop_stack: list[dict] = []
        i = 0
        n = len(lines)
        # Un slib peut boucler via `!goto` (saut arrière) sans terminer si une
        # valeur amont est cassée. On respecte le budget temps du rendu ici
        # aussi (cet interpréteur ne passe pas par `_exec`).
        import time as _time  # noqa: PLC0415
        deadline = getattr(self, "_deadline", None)
        while i < n:
            if deadline is not None and _time.monotonic() > deadline:
                from . import _RenderBudgetExceeded  # noqa: PLC0415
                raise _RenderBudgetExceeded()
            line = lines[i]
            stripped = line.strip()
            # `!!` ouvre un commentaire WIMS (et `!!!!` un bandeau de version en
            # tête de slib). Sans ce filtre, chaque ligne de commentaire partait
            # dans le dispatch de commandes et en revenait avec `UNKNOWN_CMD:!`,
            # qui écrasait `slib_out` — `slib/function/tabsignes` ne renvoyait
            # que `UNKNOWN_CMD:!!!`, son en-tête de version.
            if (
                not stripped
                or stripped.startswith("#")
                or stripped.startswith("!!")
                or stripped.startswith(":")
            ):
                i += 1
                continue
            # `!ifval` (comparaison numérique) ouvre un bloc comme `!if` : il DOIT
            # compter dans la profondeur, sinon un `!ifval` interne fait matcher
            # le mauvais `!else`/`!endif` (slib/stat/effectif : la branche else
            # sautait ses premières lignes → comptes faux).
            if stripped.startswith("!if ") or stripped.startswith("!ifval "):
                kind = "ifval" if stripped.startswith("!ifval ") else "if"
                cond = stripped[len("!ifval ") if kind == "ifval" else len("!if "):]
                taken = self._eval_condition(kind, cond)
                depth = 1
                j = i + 1
                else_at = -1
                while j < n and depth > 0:
                    s = lines[j].strip()
                    if s.startswith("!if ") or s.startswith("!ifval "):
                        depth += 1
                    elif re.match(r"!endif\b", s):
                        depth -= 1
                        if depth == 0:
                            break
                    elif re.match(r"!else\b", s) and depth == 1:
                        else_at = j
                    j += 1
                if depth != 0:
                    return
                if_stack.append(j)
                if taken:
                    i += 1
                else:
                    i = (else_at + 1) if else_at != -1 else j
                continue
            # `!endif`/`!else` peuvent porter une annotation (`!endif weight` dans
            # slib/stat/variance) — un mot après le mot-clé, ignoré par WIMS. On
            # matche donc sur `\b` et non par égalité stricte, sinon le bloc
            # n'est pas fermé et l'appariement `!if/!else/!endif` se décale.
            if re.match(r"!else\b", stripped):
                if if_stack:
                    i = if_stack[-1]
                    continue
                i += 1
                continue
            if re.match(r"!endif\b", stripped):
                if if_stack:
                    if_stack.pop()
                i += 1
                continue
            if stripped == "!exit":
                raise _SlibExit()
            if stripped.startswith("!while "):
                # `!while COND … !endwhile`, sur le même pointeur que `!for` :
                # la condition se réévalue à chaque tour, et un `!goto` du corps
                # peut en sortir — ce que la garde des slib suppose
                # (`!if $currentwhile > $maxwhile` → `!goto too_many_iter`).
                # Sans cette branche, `!endwhile` remontait en `UNKNOWN_CMD`
                # jusque dans l'attendu de l'exercice.
                depth = 1
                j = i + 1
                while j < n and depth > 0:
                    s = lines[j].strip()
                    if s.startswith("!while "):
                        depth += 1
                    elif re.match(r"!endwhile\b", s):
                        depth -= 1
                        if depth == 0:
                            break
                    j += 1
                if depth != 0:
                    i = (j + 1) if j < n else n
                    continue
                cond = stripped[len("!while ") :]
                if not self._eval_condition("if", cond):
                    i = j + 1
                    continue
                loop_stack.append({
                    "kind": "while", "cond": cond, "head": i, "end": j, "tours": 0,
                })
                i += 1
                continue
            if re.match(r"!endwhile\b", stripped):
                # Même borne que le `WhileLoop` du moteur principal : une
                # condition qui ne retombe jamais ne doit pas emporter le rendu.
                if loop_stack and loop_stack[-1]["end"] == i:
                    top = loop_stack[-1]
                    top["tours"] += 1
                    if top["tours"] <= 100000 and self._eval_condition("if", top["cond"]):
                        i = top["head"] + 1
                        continue
                    _restaurer_boucle(self.ctx, loop_stack.pop())
                i += 1
                continue
            if stripped.startswith("!for "):
                depth = 1
                j = i + 1
                while j < n and depth > 0:
                    s = lines[j].strip()
                    if s.startswith("!for "):
                        depth += 1
                    elif s.startswith("!next"):
                        depth -= 1
                        if depth == 0:
                            break
                    j += 1
                if depth != 0:
                    i = (j + 1) if j < n else n
                    continue
                body = lines[i + 1 : j]
                spec = stripped[len("!for ") :]
                # Numeric form `VAR = a to b`, or list form `VAR in LIST`
                # (tab- or comma-separated) — the latter drives e.g. the slib
                # editor's per-theme CSS loop.
                # `from` vaut `=` (`exec.c`, `exec_for`) : `!for i from 3 to 5`.
                num_m = re.match(
                    r"(\w+)\s*(?:=|\bfrom\b)\s*(.+?)\s+to\s+(.+)$", spec
                )
                in_m = re.match(r"\$?(\w+)\s+in\s+(.*)$", spec, re.I | re.S)
                if num_m:
                    try:
                        start = int(round(float(self._eval_arith(self._subst(num_m.group(2))))))
                        end = int(round(float(self._eval_arith(self._subst(num_m.group(3))))))
                    except (ValueError, TypeError):
                        i = j + 1
                        continue
                    var, seq = num_m.group(1), [str(v) for v in range(start, end + 1)]
                elif in_m:
                    var = in_m.group(1)
                    items_raw = self._subst(in_m.group(2).strip())
                    # `cutfor` (`evalue.c`) : la virgule de profondeur zéro,
                    # items élagués — le `!for x in …` d'un slib ne se découpe
                    # pas autrement que celui d'un `.def`.
                    seq = wl.cutitems(items_raw)
                else:
                    i = j + 1
                    continue
                if not seq:
                    i = j + 1
                    continue
                # La boucle s'exécute **dans** le pointeur courant, et non par
                # un appel récursif : c'est ce qui permet à un `!goto` de son
                # corps d'atteindre un label extérieur. Le corps reste donc à
                # sa place dans `lines`, et `!next` décide de reboucler.
                loop_stack.append({
                    "kind": "for", "var": var, "seq": seq, "pos": 0,
                    "head": i, "end": j, "saved": self.ctx.get(var),
                })
                self.ctx[var] = seq[0]
                i += 1
                continue
            if stripped.startswith("!next"):
                # Fin de corps : on reboucle tant que la séquence n'est pas
                # épuisée, puis on rend à la variable la valeur qu'elle avait
                # avant la boucle — comme le faisait la version récursive.
                if loop_stack and loop_stack[-1]["end"] == i:
                    top = loop_stack[-1]
                    top["pos"] += 1
                    if top["pos"] < len(top["seq"]):
                        self.ctx[top["var"]] = top["seq"][top["pos"]]
                        i = top["head"] + 1
                        continue
                    _restaurer_boucle(self.ctx, loop_stack.pop())
                i += 1
                continue
            if stripped.startswith("!goto "):
                target = stripped[len("!goto ") :].strip().lstrip(":")
                tgt_idx = labels.get(target)
                if tgt_idx is not None:
                    if_stack.clear()
                    # Sauter hors d'une boucle la termine : on dépile celles
                    # dont le corps ne contient pas la cible, en rendant à
                    # chaque variable sa valeur d'avant. C'est l'idiome des
                    # gardes de slib — `!if $currentwhile > $maxwhile` suivi
                    # d'un `!goto too_many_iter` qui doit vraiment sortir.
                    while loop_stack and not (
                        loop_stack[-1]["head"] <= tgt_idx <= loop_stack[-1]["end"]
                    ):
                        _restaurer_boucle(self.ctx, loop_stack.pop())
                    i = tgt_idx + 1
                else:
                    i += 1
                continue
            if stripped.startswith("!set "):
                # `!set NAME=VALUE` — explicit assignment. NAME may contain a
                # dynamic part (`slib_theme$slib_n`) that must expand first.
                set_m = re.match(r"(.+?)\s*=\s*(.*)$", stripped[len("!set ") :], re.DOTALL)
                if set_m:
                    name = self._subst(set_m.group(1).strip())
                    self.ctx[name] = self._eval_value(set_m.group(2))
                i += 1
                continue
            if stripped.startswith("!"):
                cmd_line = stripped[1:].strip()
                cmd, _, cargs = cmd_line.partition(" ")
                # `!readproc` imbriqué (un slib en appelle un autre, ex.
                # stat/freq → stat/dataproc) : router vers _cmd_readproc, sinon
                # le sous-script ne s'exécute pas et ses sorties restent vides.
                if cmd.lower() == "readproc":
                    self._cmd_readproc(cargs)
                else:
                    # Command results in slib are either used for side effects
                    # or stored in slib_out — mais seulement quand il y a un
                    # résultat. Une commande sans valeur de retour (`!reset`,
                    # `!set`…) ne doit pas effacer ce que le script a déjà
                    # produit : `slib/function/tabsignes` assemble son tableau
                    # dans `slib_out`, puis termine par le `!reset` de ses
                    # variables de travail — qui renvoyait `""` et emportait le
                    # tableau avec lui.
                    result = self._eval_cmd(cmd.lower(), cargs)
                    if result:
                        self.ctx["slib_out"] = result
            else:
                # Assign: key=value. The key may be dynamically named
                # (`slib_code$jj=…`), so allow `$`/`()`/`[]` and expand it.
                m = re.match(r"^\s*([\w$()\[\]]+?)\s*=\s*(.*)$", line, re.DOTALL)
                if m:
                    name = self._subst(m.group(1).strip())
                    self.ctx[name] = self._eval_value(m.group(2))
            i += 1


# ── slib/numeration/ecriturelettre — French cardinal number → words ──────────
#
# Native port of the French *cardinal* path of the WIMS slib script (which is
# too command-heavy to run through the sub-engine, so it returned an empty
# slib_out — bug on quizz 0619). Follows the WIMS default `frrule=1990`: every
# component is joined by hyphens (`sept-millions-soixante-mille`). `vingt`/`cent`
# take a plural `s` only when they end the number; `mille` is invariable.
# English/Italian, ordinals and other options fall back to the generic runner.

_FR_UNITS = (
    "zéro", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit",
    "neuf", "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize",
    "dix-sept", "dix-huit", "dix-neuf",
)
_FR_TENS = {2: "vingt", 3: "trente", 4: "quarante", 5: "cinquante", 6: "soixante"}


def _fr_below_100(n: int, final: bool = True) -> str:
    if n < 20:
        return _FR_UNITS[n]
    t, u = divmod(n, 10)
    if t in _FR_TENS:  # 20..69
        base = _FR_TENS[t]
        if u == 0:
            return base
        if u == 1:
            return f"{base}-et-un"
        return f"{base}-{_FR_UNITS[u]}"
    if t == 7:  # 70..79  (soixante + 10..19; 71 = soixante-et-onze)
        if u == 1:
            return "soixante-et-onze"
        return f"soixante-{_FR_UNITS[10 + u]}"
    if t == 8:  # 80..89  (plural s only on a standalone 80)
        if u == 0:
            return "quatre-vingts" if final else "quatre-vingt"
        return f"quatre-vingt-{_FR_UNITS[u]}"
    return f"quatre-vingt-{_FR_UNITS[10 + u]}"  # 90..99


def _fr_below_1000(n: int, final: bool = True) -> str:
    if n < 100:
        return _fr_below_100(n, final)
    h, rest = divmod(n, 100)
    head = "cent" if h == 1 else f"{_FR_UNITS[h]}-cent"
    if rest == 0:
        return head + ("s" if (h > 1 and final) else "")
    return f"{head}-{_fr_below_100(rest, final)}"


def _fr_cardinal(n: int) -> str:
    if n < 0:
        return "moins-" + _fr_cardinal(-n)
    if n == 0:
        return "zéro"
    milliards, n = divmod(n, 1_000_000_000)
    millions, n = divmod(n, 1_000_000)
    milliers, units = divmod(n, 1000)

    parts: list[str] = []
    if milliards:
        c = _fr_below_1000(milliards, final=False)
        parts.append("un-milliard" if milliards == 1 else f"{c}-milliards")
    if millions:
        c = _fr_below_1000(millions, final=False)
        parts.append("un-million" if millions == 1 else f"{c}-millions")
    if milliers:
        # "mille" is invariable, and 1000 is "mille", not "un-mille".
        parts.append("mille" if milliers == 1
                     else f"{_fr_below_1000(milliers, final=False)}-mille")
    if units:
        parts.append(_fr_below_1000(units, final=True))
    return "-".join(parts)


def _join_terms(term_strs: list[str]) -> str:
    """Joint des monômes signés en une somme : premier terme tel quel, les
    suivants préfixés de `+` sauf s'ils commencent déjà par `-`."""
    if not term_strs:
        return ""
    out = term_strs[0]
    for t in term_strs[1:]:
        out += t if t.lstrip().startswith("-") else "+" + t
    return out


def _ecriture_lettre(args: str) -> str | None:
    """Built-in for ``slib/numeration/ecriturelettre``.

    Returns the WIMS item-list of French cardinal spellings, or ``None`` to
    signal the caller to fall back to the generic slib runner (non-French
    language, ordinals, or any explicit options — not ported natively).
    """
    fields = wl.cutitems(args)
    lang = fields[1].strip().lower() if len(fields) > 1 and fields[1].strip() else "fr"
    opts = fields[2].strip() if len(fields) > 2 else ""
    if lang != "fr" or opts:
        return None

    data = fields[0].strip() if fields else ""
    if data.startswith("[") and data.endswith("]"):
        items = [x.strip() for x in data[1:-1].split(",") if x.strip()]
    else:
        items = [data] if data else []

    words = []
    for x in items:
        try:
            n = int(round(float(x)))
        except (ValueError, TypeError):
            return None  # not a plain number → let the generic runner try
        words.append(_fr_cardinal(n))
    return ",".join(words)
