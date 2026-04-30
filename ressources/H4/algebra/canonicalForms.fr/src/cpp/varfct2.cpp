target=varfct2degcomp varffctinv

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"


\integer{sa=randitem(-1,1)}
#if defined TARGET_varfct2degcomp
\integer{a=\sa*random(1..8)}
\integer{b=random(-10..10)}
#endif
#if defined TARGET_varffctinv
\integer{a=\sa*random(2..8)}
\integer{b0=random(1..10)}
\integer{b=randitem(-1,1)*\b0}
#endif
\integer{sc=randitem(-1,1)}
\integer{c=\sc*random(1..8)}
\integer{d=random(-10..10)}

\function{ux=maxima(\c*x+\d)}
\text{ux=wims(replace internal * by in \ux)}
\rational{x0=-\d/\c}
<!-- à gauche ou à droite de x0-->
\integer{pos=randitem(-1,1)}
\text{infty=&#8734;}
#if defined TARGET_varfct2degcomp
\text{interval1=\pos==1?&#91; \x0&#160;;&#160;+\infty &#91; :
  &#93; -\infty&#160; ; &#160;\x0 &#93;}
\text{interval=\pos==1?&#91; \x0&#160;;&#160;+\infty &#91; :
  &#93; -\infty&#160; ; &#160;\x0 &#93;}
#endif
#if defined TARGET_varffctinv
\text{interval=\pos==1?&#93; \x0 ; +\infty &#91; : &#93; -\infty ; \x0 &#91;}
#endif
<!-- sens var u-->
\integer{rep1=\sc==1?1:2}
<!-- signe de u -->
\integer{rep2=\sc*\pos==1?1:2}
#if defined TARGET_varfct2degcomp
\text{intR=\rep2==1?\(\RR+\):\(\RR-\)}
<!-- var carre pour u de signe \sc -->
#endif
#if defined TARGET_varffctinv
\text{intR=\rep2==1?\(\RR^{*}+\):\(\RR^{*}-\)}
<!-- var inv sur intervalles d'arrivée de u (de signe \sc) -->
#endif
\integer{rep3=\rep2==1?1:2}

\function{vt=maxima(\a*t+\b)}
\text{vt=wims(replace internal * by in \vt)}

<!-- sens var v-->
\integer{rep4=\sa==1?1:2}
#if defined TARGET_varfct2degcomp
\function{f=\a(\ux)^2+\b}
\text{f=wims(replace internal * by in \f)}
#endif
#if defined TARGET_varffctinv
\text{tb=\b>0? + \b0 : - \b0}
\function{f=\frac{\a}{\ux} \tb}
#endif
#if defined TARGET_varfct2degcomp
<!-- sens var u^2-->
\integer{rep5=\rep1*\rep3==2?2:1}
\text{domdef=\(\,\RR\)}
#endif
#if defined TARGET_varffctinv
<!-- sens var inv(u)=inverse de celui de u -->
\integer{rep5=\rep1==1?2:1}
\text{domdef=\(\RR \setminus\{\x0\}\)}
#endif
\integer{rep6=\rep5*\rep4==2?2:1}
<div style="background:#F6E497;padding:2;">
\statement{
On considère la fonction \(f\) définie sur \domdef par \(f : x \mapsto \f\).
On étudie son sens de variation sur l'intervalle \interval.
<p>
Complétez le texte suivant, afin que l'étude de variation
soit correcte sur \interval.
</p>
<div class="wims_question">
#if defined TARGET_varfct2degcomp
La fonction \(f\) s'obtient comme composée \(v\circ c \circ u\)
  des fonctions suivantes :
#endif
#if defined TARGET_varffctinv
La fonction \(f\) s'obtient en enchaînant les fonctions suivantes,
  à la suite l'un de l'autre :
#endif
<ol><li>
d'abord, la fonction affine \(u : x \mapsto \ux\) qui est
  \embed{reply1} sur \(\,\RR\)
et qui prend des valeurs \embed{reply2} sur l'intervalle \interval.
</li><li>
#if defined TARGET_varfct2degcomp
puis, la fonction carré \(c : X \mapsto X^2\) qui est \embed{reply3}.
#endif
#if defined TARGET_varffctinv
ensuite, la fonction inverse \(i : X \mapsto 1/X\) qui est \embed{reply3}.
#endif
</li><li>
Enfin, la fonction affine \(v : t \mapsto \vt\) qui est \embed{reply4} sur \(\,\RR\).
</li></ol>
On en déduit que :
<ol><li>
#if defined TARGET_varfct2degcomp
La fonction \(x \mapsto (\ux)^2\) est \embed{reply5} sur l'intervalle \interval.
</li><li>
Par composition avec la fonction <b>\(v\)</b>, on conclut que la fonction
\(f : x \mapsto \f\) est \embed{reply6} sur \interval.
#endif
#if defined TARGET_varffctinv
Les deux premières étapes produisent la fonction \(x \mapsto \frac{1}{\ux}\),
  qui est \embed{reply5} sur l'intervalle \interval.
</li><li>
En appliquant ensuite la fonction <b>\(v\)</b>, on conclut que la fonction
\(f : x \mapsto \f\) est \embed{reply6} sur \interval.
#endif
</li></ol>
</div>
}
\answer{Variation de u}{\rep1;\choix1}{type=menu}
#if defined TARGET_varfct2degcomp
\answer{}{\rep2;\choix2}{type=menu}
\answer{Variation des carrés}{\rep3;\choix3[1] &#91; 0 &#59; +\infty&#91;,\choix3[2] &#93; -\infty &#59; 0 &#93;,\choix3[2] &#93; 0 &#59; +\infty&#91;,\choix3[1] &#93; -\infty &#59; 0 &#91;}{type=menu}{option=shuffle}
\answer{Variation de v}{\rep4;\choix1}{type=menu}
\answer{Variation de u^2}{\rep5;\choix1}{type=menu}
#endif
#if defined TARGET_varffctinv
\answer{}{\rep2;\choix2}{type=menu}
\answer{Variation des inverses}{\rep3;\choix3[2] &#93; 0 &#59; +\infty&#91;,\choix3[2] &#93; -\infty &#59; 0 &#91;,\choix3[1] &#93; 0 &#59; +\infty&#91;,\choix3[1] &#93; -\infty &#59; 0 &#91;}{type=menu}{option=shuffle}
\answer{Variation de v}{\rep4;\choix1}{type=menu}
\answer{Variation de 1/u}{\rep5;\choix1}{type=menu}
#endif
\answer{Variation de f}{\rep6;\choix1}{type=menu}
\hint{
  <ul><li>
  Si la fonction \(u\) est strictement croissante sur \(I\)
  et prend ses valeurs dans \(J\), et si la fonction \(v\) est
  strictement croissante sur \(J\), alors la composée \(v \circ u\)
  (soit \(u\) suivie de \(v\)) est strictement croissante sur \(I\).
  </li><li>
  Si la fonction \(u\) est strictement croissante sur \(I\)
  et prend ses valeurs dans \(J\), et si la fonction \(v\) est
  strictement décroissante sur \(J\), alors la composée
  \(v \circ u\) (soit \(u\) suivie de \(v\)) est strictement décroissante sur \(I\).
  </li></ul>
  De façon générale :
  <ul><li>
  composer avec une fonction croissante revient à <b>conserver</b> le sens de variation de la première fonction ;
  </li><li>
  composer avec une fonction décroissante revient à <b>inverser</b> le sens de variation de la première fonction.
  </li></ul>
}
