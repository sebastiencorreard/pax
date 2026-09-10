target=rapport1 rapport2 rapport3 rapport4
#include "author.inc"
#include "lang_titles.inc"
#if defined TARGET_rapport1
\rational{k=random(2,3,4,5,1/2,2/3,3/4,1/4,1/3)*randint(1,-1,-1,-1)}
\text{tk=texmath(\k)}
\integer{fracang=randint(2,3,4,6)}
\text{data=d'une homothétie de rapport \(\tk),abs(\k)
d'une rotation d'angle \(\frac{\pi}{\fracang}),1
d'une symétrie axiale,1
d'une translation,1}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\rational{rap=\cedata[2]}
\statement{<p>
Quel est le rapport de similitude \quest ?
</p>
<div class="wimscenter"> <label for="reply1">rapport de similitude =</label> \embed{reply1,4}</div>
}
\answer{rapport}{\rap}{type=numexp}
#endif
#if (defined TARGET_rapport2  || defined TARGET_rapport3 )
\rational{k=random(2,3,4,5,1/2,2/3,3/4,1/4,1/3)*randint(1,-1,-1,-1)}
\text{tk=texmath(\k)}
\rational{k2=random(2,3,4,5,1/2,2/3,3/4,1/4,1/3)*randint(1,-1,-1,-1)}
\text{tk2=texmath(\k2)}
\integer{fracang=randint(2,3,4,6)}
\integer{fracang2=randint(2,3,4,6)}
\text{data=d'une homothétie de rapport \(\tk),abs(\k)
d'une homothétie de rapport \(\tk2),abs(\k2)
d'une rotation d'angle \(\frac{\pi}{\fracang}),1
d'une rotation d'angle \(-\frac{\pi}{\fracang2}),1
d'une symétrie axiale,1
d'une translation,1
}
\text{ind=shuffle(rows(\data)-1)}
\text{cedata=row(\ind[1]+1,\data)}
\text{quest=\cedata[1]}
\rational{rap=\cedata[2]}
\text{cedata=row(1,\data)}
\text{quest2=\cedata[1]}
\rational{rap2=\cedata[2]}
\text{ql=\quest,\quest2}
\integer{i=randint(1,2)}
# if defined TARGET_rapport2
\rational{rap=\rap*\rap2}
\text{rec=}
# else
\text{rec=de la réciproque }
\text{rl=\rap,\rap2}
\rational{rap=(\rl[\i])/(\rl[3-\i])}
# endif
\statement{<p>
Quel est le rapport de similitude de la composée \ql[\i] et \rec \ql[3-\i] ?
</p>
<div class="wimscenter"><label for="reply1">rapport de similitude =</label> \embed{reply1,4}</div>
}
\answer{rapport}{\rap}{type=numexp}
#endif
#if defined TARGET_rapport4
\rational{a=randint(1..5)/randint(1..5)*randint(1,-1)}
\integer{p=randint(-3..3)}
\integer{xa=randint(-5..5)}
\integer{xb=\xa+randint(1..5)*randint(1,-1)}
\rational{ya=\a*\xa+\p}
\rational{yb=\a*\xb+\p}
\integer{p2=randint(-3..3)}
\integer{xc=randint(-5..5)}
\integer{xd=\xc+randint(1..5)*randint(1,-1)}
\rational{yc=-\xc/\a+\p2}
\rational{yd=-\xd/\a+\p2}
\rational{rap=abs((\xd-\xc)/(\a*(\xb-\xa)))}
\statement{<p>
Le plan est muni d'un repère orthonormé \((O;\vec{i},\vec{j})).</p>
Quel est le rapport de la similitude qui transforme le point \(A(\xa;\ya))
en \(C(\xc;\yc)) et le point \(B(\xb;\yb)) en \(D(\xd;\yd))?
<div class="wimscenter"><label for="reply1">rapport de similitude =</label> \embed{reply1,4}</div>
}
\answer{rapport}{\rap}{type=numexp}
#endif
