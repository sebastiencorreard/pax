target=form2graph1,form2graph2,form2graph3,form2graph4,form2graph5
#include "author.inc"
\precision{100}
#if defined TARGET_form2graph1
# define NUM 1
#endif
#if defined TARGET_form2graph2
# define NUM 2
#endif
#if defined TARGET_form2graph3
# define NUM 3
#endif
#if defined TARGET_form2graph4
# define NUM 4
#endif
#if defined TARGET_form2graph5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{f=randitem(f,g,h)}
\integer{size=300}

#if defined TARGET_form2graph1
 \text{v=wims(values v,-v for v=2 to 5)}
 \text{v=shuffle(\v)}
\text{ltfonctions=\v[1]*x+\v[2],-\v[1]*x+\v[2],1/\v[1]*x+\v[2],-1/\v[1]*x+\v[2]}
#endif
#if defined TARGET_form2graph2
 \text{v=wims(values v,-v for v=2 to 5)}
 \text{v=shuffle(\v)}
\text{ltfonctions=\v[1]*x+\v[2],\v[1]*x-\v[2],\v[1]*x-\v[2]*\v[1],\v[1]*x+\v[2]*\v[1]}
#endif
#if defined TARGET_form2graph3
 \text{v=wims(values v,-v for v=2 to 5)}
 \text{v=shuffle(\v)}
\text{ltfonctions=\v[1]*x+\v[2],-\v[1]*x+\v[2],\v[2]*x+\v[1],-\v[2]*x+\v[1]}
#endif
#if defined TARGET_form2graph4
 \text{v=wims(values v,-v for v=2 to 5)}
 \text{v=shuffle(\v)}
\text{ltfonctions=\v[1]*x+\v[2],\v[1]*x-\v[2],\v[2]*x+\v[1],\v[2]*x-\v[1]}
#endif
#if defined TARGET_form2graph5
 \text{v=wims(values v,-v for v=2 to 5)}
 \text{v=shuffle(\v)}
\text{ltfonctions=\v[1]*x+\v[2],1/\v[1]*x-\v[2]/\v[1],-\v[1]*x+\v[2],-1/\v[1]*x-\v[2]/\v[1]}
#endif
\text{fnct=texmath(\ltfonctions[1])}
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
  Soit \(\f\) la fonction affine définie par : \(\f : x\mapsto \fnct).
  Quelle est sa représentation graphique ?
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
