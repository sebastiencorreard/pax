target=graph2form1,graph2form2,graph2form3,graph2form4,graph2form5
#include "author.inc"
\precision{100}
#if defined TARGET_graph2form1
# define NUM 1
#endif
#if defined TARGET_graph2form2
# define NUM 2
#endif
#if defined TARGET_graph2form3
# define NUM 3
#endif
#if defined TARGET_graph2form4
# define NUM 4
#endif
#if defined TARGET_graph2form5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{f=randitem(f,g,h)}
\integer{size=300}

#if defined TARGET_graph2form1
 \text{v=wims(values v,-v for v=2 to 5)}
 \text{v=shuffle(\v)}
\text{ltfonctions=\v[1]*x+\v[2],-\v[1]*x+\v[2],1/\v[1]*x+\v[2],-1/\v[1]*x+\v[2]}
#endif
#if defined TARGET_graph2form2
 \text{v=wims(values v,-v for v=2 to 5)}
 \text{v=shuffle(\v)}
\text{ltfonctions=\v[1]*x+\v[2],\v[1]*x-\v[2],\v[1]*x-\v[2]/\v[1],\v[1]*x+\v[2]/\v[1]}
#endif
#if defined TARGET_graph2form3
 \text{v=wims(values v,-v for v=2 to 5)}
 \text{v=shuffle(\v)}
\text{ltfonctions=\v[1]*x+\v[2],-\v[1]*x+\v[2],\v[2]*x+\v[1],-\v[2]*x+\v[1]}
#endif
#if defined TARGET_graph2form4
 \text{v=wims(values v,-v for v=2 to 5)}
 \text{v=shuffle(\v)}
\text{ltfonctions=\v[1]*x+\v[2],\v[1]*x-\v[2],\v[2]*x+\v[1],\v[2]*x-\v[1]}
#endif
#if defined TARGET_graph2form5
 \text{v=wims(values v,-v for v=2 to 5)}
 \text{v=shuffle(\v)}
\text{ltfonctions=\v[1]*x+\v[2],1/\v[1]*x-\v[2]/\v[1],-\v[1]*x+\v[2],-1/\v[1]*x-\v[2]/\v[1]}
#endif

\text{repere=slib(draw/repere \size,\size,0,-10,10,-10,10,1,1,black,grey)}
\text{repere=wims(line 3 to -1 of \repere)}
 \text{figure=draw(\size,\size
\repere
range -10,10,-10,10
plot blue,\ltfonctions[1]
text black,9.5,-0.3,medium,X
text black,-0.6,10,medium,Y
text black,0.9,-0.3,medium,1
text black,-0.6,1.5,medium,1)}
\text{afffnt=}
\for{i=1 to 4}{
 \text{fonction=maxima(\ltfonctions[\i];)}
 \text{fonction=texmath(\fonction)}
 \text{afffnt=wims(append item \fonction to \afffnt)}
}

\text{Bad=F,G,H,J}
\text{good=item(1,\afffnt)}
\text{bad=shuffle(\afffnt)}
\text{po=positionof(\good,\bad)}
\text{Good=\Bad[\po]}

\statement{
<div class="float_left spacer"><img src="\figure" alt=""></div>
  De quelle fonction la droite ci-contre est-elle la représentation graphique ?
 <ul>
  \for{k=1 to 4}{<li>\(\Bad[\k] : x \mapsto \bad[\k])</li>}
 </ul>
<b>Votre réponse :</b><br>
  C'est la représentation graphique de la fonction \embed{c1}.
}

\choice{réponse}{\Good}{\Bad}
