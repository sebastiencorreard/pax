target=graphique1,graphique2,graphique3,graphique4,graphique5
#include "author.inc"
\precision{100}
#if defined TARGET_graphique1
# define NUM 1
#endif
#if defined TARGET_graphique2
# define NUM 2
#endif
#if defined TARGET_graphique3
# define NUM 3
#endif
#if defined TARGET_graphique4
# define NUM 4
#endif
#if defined TARGET_graphique5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{f=randitem(f,g,h)}
\integer{size=300}

#if defined TARGET_graphique1
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=1}
 \integer{b=\v[1]}
 \text{ltfonctions=\b/\a*x,\a/\b*x,-\b/\a*x,-\a/\b*x}
 \text{fnct=texmath(\ltfonctions[1])}
 \text{enonce=Soit \(\f\) la fonction linéaire définie par : \(\f : x\mapsto \fnct\).Quelle est sa représentation graphique}
#endif
#if defined TARGET_graphique2
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{b=\v[1]}
 \text{ltfonctions=\b*x,1/\b*x,-\b*x,-1/\b*x}
 \text{fnct=texmath(\ltfonctions[1])}
 \text{enonce=Soit \(\f\) une fonction linéaire telle que \(\f(1) = \b\). Quelle est sa représentation graphique}
#endif
#if defined TARGET_graphique3
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=\v[2]}
 \integer{b=\v[1]}
 \text{ltfonctions=\b/\a*x,\a/\b*x,-\b/\a*x,-\a/\b*x}
 \text{fnct=texmath(\ltfonctions[1])}
 \text{enonce=Soit \(\f\) une fonction linéaire telle que \(\f(\a) = \b\). Quelle est sa représentation graphique}
#endif
#if defined TARGET_graphique5
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=\v[2]}
 \integer{b=\v[1]}
 \text{ltfonctions=\b/\a*x,\a/\b*x,-\b/\a*x,-\a/\b*x}
 \text{fnct=texmath(\ltfonctions[1])}
 \text{enonce=Soit \(\f\) la fonction linéaire définie par : \(\f : x\mapsto \fnct\). Quelle est sa représentation graphique}
#endif
#if defined TARGET_graphique4
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=\v[2]}
 \integer{b=\v[1]}
 \integer{c=randitem(1,-1)*randint(1..3)}
 \text{ltfonctions=\b/\a*x,(\a-\c)/\b*x+(\c),(\b-\c)/\a*x+(\c),\a/\b*x}
 \text{fnct=texmath(\ltfonctions[1])}
 \text{enonce=Soit \(\f\) la fonction linéaire définie par : \(\f : x\mapsto \fnct\).
 Quelle est sa représentation graphique}
#endif
!! gestionnaire de l'exercice.

\text{repere=slib(draw/repere \size,\size,0,-10,10,-10,10,1,1,black,grey)}
\text{repere=wims(line 3 to -1 of \repere)}
\text{dessin=}
\for{i=1 to 4}{
 \text{fonction=\item(\i,\ltfonctions)}
 \text{figure=draw(\size,\size
\repere
range -10,10,-10,10
plot blue,\fonction
text black,9.5,-0.3,medium,X
text black,-0.6,10,medium,Y
text black,0.9,-0.3,medium,1
text black,-0.6,1.5,medium,1)}
 \text{dessin=wims(append item \figure to \dessin)}
}

\text{lettres=A,B,C,D,E,F,G,H}
\text{good=item(1,\dessin)}
\text{bad=shuffle(\dessin)}
\text{po=positionof(\good,\bad)}
\text{Good=item(\po,\lettres)}
\text{Bad=A,B,C,D}
\statement{
\enonce ?
<table class="wimscenter wimsborder">
 <tr>
  <td>Réponse A :<br><img src="\bad[1]" alt=""></td>
  <td>Réponse B :<br><img src="\bad[2]" alt=""></td>
 </tr><tr>
   <td>Réponse C :<br><img src="\bad[3]" alt=""></td>
   <td>Réponse D :<br><img src="\bad[4]" alt=""></td>
 </tr>
</table>
<b>Votre réponse :</b>
<div class="wimscenter">
  La bonne réponse est : \embed{c1}.
</div>}

\choice{réponse}{\Good}{\Bad}
