target=sensvar1 sensvar2 sensvar3

#define TITLE Sens de variation
#if defined TARGET_sensvar1
\title{TITLE 1}
\text{monotone=croissante, strictement croissante, décroissante, strictement décroissante}
\text{lstrep=\(f(x_1) \le f(x_2)), \(f(x_1) < f(x_2)), \(f(x_1) \ge f(x_2)), \(f(x_1) > f(x_2))}
\integer{k=randint(1..4)}
\text{k2l=2,1,4,3}
\integer{k2=\k2l[\k]}
\text{repl=2,1,2,1}
\integer{rep=\repl[\k]}
\text{size=50x150x150}
\steps{r1
r2}

\statement{<p>
\if{\step=1}
{
  Soit une fonction \(f) définie sur un intervalle \(I), et deux réels \(x_1) et \(x_2) de \(I),
  tels que \(x_1 < x_2):
</p><p>
  Mettre en correspondance le sens de variation et la définition algébrique :</p>
<div class="wimscenter">\embed{reply1,\size}</div>
}
{
  Soit une fonction \(f) définie sur un intervalle \(I) et <span class="wims_emph"> \monotone[\k] </span>.</p>
  D'après la définition, pour tous réels \(x_1) et \(x_2) de \(I), tels que \(x_1 < x_2), on a:
<div class="wimscenter"> \lstrep[\k] </div>
<p>
  Peut-on aussi en déduire :
</p>
<div class="wimscenter"> \lstrep[\k2] </div>
\embed{reply2}
}
}
\answer{}{\monotone;\lstrep}{type=correspond}
\answer{}{\rep;Oui,Non}{type=radio}
#endif

#if defined TARGET_sensvar4
\title{TITLE 4}
\text{monotone=croissante, strictement croissante, décroissante, strictement décroissante}
\text{lstrep=\(f(x_1) \le f(x_2)), \(f(x_1) < f(x_2)), \(f(x_1) \ge f(x_2)), \(f(x_1) > f(x_2)), on ne peut pas savoir}
\integer{k=randint(1..4)}
\if{\k=1}
 {\text{indrep=\k}}
\if{\k=2}
 {\text{indrep=1,2}}
\if{\k=3}
 {\text{indrep=\k}}
\if{\k=4}
 {\text{indrep=3,4}}

\statement{
  Soit une fonction \(f) définie sur un intervalle \(I) et <span class="wims_emph"> \monotone[\k] </span>.<p>
  Cocher la (ou les) proposition(s) vérifiée(s) pour tous réels \(x_1) et \(x_2) de \(I), tels que \(x_1 < x_2):
</p>
<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
</ul>
}
\answer{\(f) \monotone[\k]}{\indrep;\lstrep}{type=checkbox}
#endif
#if defined TARGET_sensvar2
\title{TITLE 2}
\integer{k=randint(1..4)}
\text{monotone=croissante, strictement croissante, décroissante, strictement décroissante, non monotone}
\text{lstrep=\(f(x_1) \le f(x_2)), \(f(x_1) < f(x_2)), \(f(x_1) \ge f(x_2)), \(f(x_1) > f(x_2)), on ne peut pas savoir}
\statement{
  Soit une fonction \(f) définie sur un intervalle \(I) , telle que
<div class="wimscenter"> pour tous réels \(x_1) et \(x_2) de \(I), tels que \(x_1 < x_2), on a \lstrep[\k]</div>
  Alors \(f) est:

<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
</ul>
}
\answer{\lstrep[\k]}{\k;\monotone}{type=radio}
#endif
#if defined TARGET_sensvar3
\title{TITLE 3}
\text{extrem=maximum,maximum strict,minimum, minimum strict}
\integer{k=randint(1..4)}
\text{val=\k<3?M:m}
\text{lstrep=\(f(x) \le \val), \(f(x) < \val), \(f(x) \ge \val), \(f(x) > \val), on ne peut pas savoir}
\statement{
  Soit une fonction \(f) définie sur un intervalle \(I) , admettant <span class="wims_emph">un \extrem[\k] \val </span> sur \(I) en \(x_0).<p>
  Alors, pour tout \(x \in I), \(x \neq x_0):
</p>
<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
</ul>
}
\answer{\(f) admet un \extrem[\k]}{\k;\lstrep}{type=radio}
#endif
