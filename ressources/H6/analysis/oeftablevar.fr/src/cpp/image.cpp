target=image minmax image3 minmax3

#include "header.inc"
#include "values.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_image
 \text{size=60x40x1}
# include "tablegen.inc"
#endif
#if defined TARGET_minmax
 \text{size=70x40x1}
# include "tablegen.inc"
#endif

#if defined TARGET_image3
 \text{size=60x40x1}
# include "tablegen3.inc"
#endif
#if defined TARGET_minmax3
 \text{size=70x40x1}
# include "tablegen3.inc"
#endif

#include "common.inc"

\text{osign=item(\orient,+,-)}


\if{\tabcnt=4}{
 \text{presup=\osign(\ys[2])>\osign(\ys[4])?2:4}
 \text{premax=\presup}
 \text{preinf2=\osign(\YY[1])>\osign(\YY[5])?5:1}
 \text{preinf=\osign(\YY[\preinf2])<\osign(\ys[3])?\preinf2:3}
 \text{premin=\preinf=3?3:6}
 \if{\orient=1}{
  \text{sup=\yshow[\presup]}
  \text{max=\sup}
  \text{inf=\yshow[\preinf]}
  \text{min=\premin=6?\non:\inf}
 }{
  \text{inf=\yshow[\presup]}
  \text{min=\inf}
  \text{sup=\yshow[\preinf]}
  \text{max=\premin=6?\non:\sup}
 }
}{
 \text{presup=\osign(\ys[2])>\osign(\YY[4])?2:4}
 \text{premax=\presup=2?2:6}
 \text{preinf=\osign(\YY[1])<\osign(\ys[3])?1:3}
 \text{premin=\preinf=3?3:6}
 \if{\orient=1}{
  \text{sup=\yshow[\presup]}
  \text{max=\premax=6?\non:\sup}
  \text{inf=\yshow[\preinf]}
  \text{min=\premin=6?\non:\inf}
 }{
  \text{inf=\yshow[\presup]}
  \text{min=\premax=6?\non:\inf}
  \text{sup=\yshow[\preinf]}
  \text{max=\premin=6?\non:\sup}
 }
}

\text{vlist=wims(listuniq \xshow,\yshow)}
\text{bracks=\leftbrack,\rightbrack}
\text{lbr=\min issametext \non?\bracks[2]:\bracks[1]}
\text{rbr=\max issametext \non?\bracks[1]:\bracks[2]}

\statement{\intro

#include "table.inc"

#if defined TARGET_image || defined TARGET_image3
 \name_question \(f\) ?
<div class="wimscenter">
 \embed{reply1,\size}\embed{reply2,\size},\embed{reply3,\size}\embed{reply4,\size}
</div>

}

\answer{Crochet à gauche}{\lbr;\bracks}{type=clickfill}
\answer{Inf(f)}{\inf;\vlist}{type=clickfill}
\answer{Sup(f)}{\sup}{type=clickfill}
\answer{Crochet à droite}{\rbr;\bracks}{type=clickfill}
#endif

#if defined TARGET_minmax  || defined TARGET_minmax3
 \name_question:
<div class="wimscenter">Inf(\(f\)) = \embed{r1,\size}&nbsp;&nbsp;&nbsp;
Sup(\(f\)) = \embed{r2,\size}<br>
Min(\(f\)) = \embed{r3,\size}&nbsp;&nbsp;&nbsp;
Max(\(f\)) = \embed{r4,\size}
</div>
}

\answer{Inf(\(f\))}{\inf;\vlist,\non}{type=clickfill}
\answer{Sup(\(f\))}{\sup}{type=clickfill}
\answer{Min(\(f\))}{\min}{type=clickfill}
\answer{Max(\(f\))}{\max}{type=clickfill}

\feedback{(\reply3 notitemof \yshow and \reply3 isitemof \xshow) or
	  (\reply4 notitemof \yshow and \reply4 isitemof \xshow)}{
 Min(\(f\)) et Max(\(f\)) sont des valeurs de \(f(x)\), mais pas de \(x\) !
}

\feedback{\min issametext \non and \reply3 issametext \inf}{
 La valeur \inf n'est qu'une limite de \(f(x)\) quand \(x\)
 tend vers l'infini. Elle ne peut pas être atteinte par une valeur
 finie de \(x\). Donc Min(\(f\)) n'existe pas.
}
\feedback{\max issametext \non and \reply4 issametext \sup}{
 La valeur Sup(\(f\)) = \sup n'est qu'une limite de \(f(x)\) quand \(x\)
 tend vers l'infini. Elle ne peut pas être atteinte par une valeur
 finie de \(x\). Donc Max(\(f\)) n'existe pas.
}

#endif

