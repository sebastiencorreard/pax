target=angle1 angle2 angle3 angle4

#include "author.inc"
#include "lang_titles.inc"
#if (defined TARGET_angle1  || defined TARGET_angle2 )
\rational{k=random(2,3,4,5,1/2,2/3,3/4,1/4,1/3)*randint(1,-1,-1,-1)}
\text{tk=texmath(\k)}
\integer{fracang=randint(2,3,4,6)}
\integer{numang=randint(1..\fracang-1)*randint(1,-1)}
\rational{ang=simplify(\numang/\fracang)}
\text{ta=\ang}
\text{ta=wims(replace internal / by , in \ta)}
\text{numang=\ta[1]=1?:\ta[1]}
\text{numang=\ta[1]=-1?-}

\integer{fracang=\ta[2]}

#if defined TARGET_angle1
\integer{cas=randint(1,2)}
\text{quest1=\cas=1? d'une homothétie de rapport \(\tk):d'une rotation d'angle \(\frac{\numang \pi}{\fracang})}
\text{quest2=\cas=2? d'une homothétie de rapport \(\tk):d'une rotation d'angle \(\frac{\numang \pi}{\fracang})}
\rational{ang=\k>0?\ang:simplify(\ang+1)}
\rational{ang=\ang>1?simplify(\ang-2)}
\text{rec=}
#endif

#if defined TARGET_angle2
\integer{cas=randint(1,2)}
\text{quest1=\cas=1? d'une homothétie de rapport \(\tk):d'une rotation d'angle \(\frac{\numang \pi}{\fracang})}
\text{quest2=\cas=2? d'une homothétie de rapport \(\tk):d'une rotation d'angle \(\frac{\numang \pi}{\fracang})}
\if{\cas=1}{
  \rational{ang=\k>0?-\ang:simplify(-\ang+1)}
  \rational{ang=\ang>1?simplify(\ang-2)}
  }{
  \rational{ang=\k>0?\ang:simplify(\ang+1)}
  \rational{ang=\ang>1?simplify(\ang-2)}
  }
\text{rec=de la réciproque }
#endif

\statement{<p>
Quel est l'angle de la similitude directe composée \quest1 et \rec \quest2 ?
</p>
<div class="wimscenter"><label for="reply1">angle de similitude =</label>\embed{reply1,4}\(\pi)</div>
}
\answer{angle}{\ang}{type=numexp}
#endif

#if defined TARGET_angle3
\text{lstang=1/2,1/3,1/4,1/5,1/6,2/5,3/5}
\rational{angAOB=randitem(\lstang)}
\rational{angOBA=randitem(\lstang)}
\rational{somme=\angAOB+\angOBA}
\rational{angOBA=\somme>=1?(\angOBA)/2}
\rational{somme=\angAOB+\angOBA}
\rational{angBAO=simplify(1-\somme)}
\text{tAOB=texmath(\angAOB*x)}
\text{tBOA=texmath(-\angAOB*x)}
\text{tOBA=texmath(\angOBA*x)}
\text{tABO=texmath(-\angOBA*x)}
\text{tBAO=texmath(\angBAO*x)}
\text{tOAB=texmath(-\angBAO*x)}
\text{tAOB=wims(replace internal x by \pi in \tAOB)}
\text{tBOA=wims(replace internal x by \pi in \tBOA)}
\text{tOBA=wims(replace internal x by \pi in \tOBA)}
\text{tABO=wims(replace internal x by \pi in \tABO)}
\text{tBAO=wims(replace internal x by \pi in \tBAO)}
\text{tOAB=wims(replace internal x by \pi in \tOAB)}
\text{l1=\((\overrightarrow{OA},\overrightarrow{OB})=\tAOB),\((\overrightarrow{OB},\overrightarrow{OA})=\tBOA),\((\overrightarrow{AO},\overrightarrow{BO})=\tAOB),\((\overrightarrow{BO},\overrightarrow{AO})=\tBOA)}
\text{l2=\((\overrightarrow{BO},\overrightarrow{BA})=\tOBA),\((\overrightarrow{BA},\overrightarrow{BO})=\tABO),\((\overrightarrow{OB},\overrightarrow{AB})=\tOBA),\((\overrightarrow{AB},\overrightarrow{OB})=\tABO)}
\text{l3=\((\overrightarrow{AO},\overrightarrow{AB})=\tOAB),\((\overrightarrow{AB},\overrightarrow{AO})=\tBAO),\((\overrightarrow{OA},\overrightarrow{BA})=\tOAB),\((\overrightarrow{BA},\overrightarrow{OA})=\tBAO)}
\integer{cas=randint(1..3)}
\if{\cas=1}{
 \text{info1=randitem(\l1)}
 \text{info2=randitem(\l2)}
}
\if{\cas=2}{
 \text{info1=randitem(\l2)}
 \text{info2=randitem(\l3)}
}
\if{\cas=3}{
 \text{info1=randitem(\l3)}
 \text{info2=randitem(\l1)}
}


\statement{<p>
On considère 3 points \(O,A) et \(B) du plan tels que:
</p>
<div class="wimscenter"> \info1 et \info2</div>
Quel est l'angle de la similitude directe de centre O qui envoie \(A) sur \(B)?
<div class="wimscenter"><label for="reply1">angle de similitude =</label> \embed{reply1,4}\(\pi)</div>
}
\answer{angle}{\angAOB}{type=numexp}
#endif
#if defined TARGET_angle4
\text{lstang=shuffle(1/2,1/3,1/4,1/5,1/6,2/5,3/5)}
\rational{good=\lstang[1]*randint(1,-1)}
\rational{bad=\lstang[2]*randint(1,-1)}
\text{tgood=texmath(\good*x)}
\text{tmgood=texmath(-\good*x)}
\text{tbad=texmath(\bad*x)}
\text{tgood=wims(replace internal x by \pi in \tgood)}
\text{tmgood=wims(replace internal x by \pi in \tmgood)}
\text{tbad=wims(replace internal x by \pi in \tbad)}
\text{l1=\((\overrightarrow{AB},\overrightarrow{CD})=\tgood),\((\overrightarrow{BA},\overrightarrow{DC})=\tgood),\((\overrightarrow{CD},\overrightarrow{AB})=\tmgood),\((\overrightarrow{DC},\overrightarrow{BA})=\tmgood)}
\text{l2=\((\overrightarrow{AC},\overrightarrow{BD})=\tbad),\((\overrightarrow{CA},\overrightarrow{DB})=\tbad),\((\overrightarrow{AD},\overrightarrow{BC})=\tbad),\((\overrightarrow{DA},\overrightarrow{BC})=\tbad)}
\integer{cas=randint(1,2)}
\if{\cas=1}{
 \text{info1=randitem(\l1)}
 \text{info2=randitem(\l2)}
 }
\if{\cas=2}{
 \text{info1=randitem(\l2)}
 \text{info2=randitem(\l1)}
 }

\statement{<p>
On considère 4 points \(A,B,C) et \(D) du plan tels que:
</p>
<div class="wimscenter"> \info1 et \info2</div>
Quel est l'angle de la similitude directe qui envoie \(A) sur \(C) et \(B) sur \(D)?
<div class="wimscenter"><label for="reply1">angle de similitude =</label> \embed{reply1,4}\(\pi)</div>
}
\answer{angle}{\good}{type=numexp}
#endif
