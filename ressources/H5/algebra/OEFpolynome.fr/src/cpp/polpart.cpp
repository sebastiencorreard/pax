target=polpart1 polpart2
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{100}

 \integer{a2=randint(1..9)*randint(1,-1)}
 \integer{b2=randint(1..9)*randint(1,-1)}
 \integer{d=gcd(\a2,\b2)}
 \integer{a=\a2 / \d}
 \integer{b=\b2 / \d}
\integer{k=randint(1,2)}
\integer{k=2}
\if{\k=1}
 {
 \text{eqx=texmath(\a*x^2+\b*x)}
 \text{eqrx=\a*x^2+\b*x}
 \integer{rep1=1}
 \rational{xrep2=simplify(-\b / \a)}
 \text{sol=\xrep2>0?0,\xrep2:\xrep2,0}
 \text{mstep=r1
     r2,r3}
 \text{eqfx=texmath(x*(\a*x+\b))}
 }
 {
 \text{eqx=texmath(\a*x^2+\b)}
 \text{eqrx=\a*x^2+\b}
 \integer{rep1=\a*\b>0?2:1}
 \if{\rep1=1}
  {
  \real{xrep2=sqrt(-\b / \a)}
  \real{xrep3=-\xrep2}
  \text{sol=\xrep2<0?\xrep2,\xrep3:\xrep3,\xrep2}
  \text{mstep=r1
    r2,r3}
 \text{eqfx=\a>0?texmath((sqrt(\a)*x-sqrt(-\b))*(sqrt(\a)*x+sqrt(-\b))):texmath((-sqrt(-\a)*x+sqrt(\b))*(sqrt(-\a)*x+sqrt(\b)))}
  }
  {
   \text{mstep=r1}
  }
  }
#if defined TARGET_polpart1
\title{Factorisation de polynômes particuliers}
\text{intro=Le polynôme \(P(x)=\eqx) peut-il se factoriser}
\text{intro2=Factoriser \(P(x)=\eqx)}
text{eqfx=maxima(factor(\eqrx))}
\text{indcond=\k=1 or (\k=2 and \rep1=1)?1}
#endif

#if defined TARGET_polpart2
\title{Equations particulières}
\text{intro=L'équation \(\eqx=0) a-t-elle des solutions}
\text{intro2=Résoudre \(\eqx=0)}
\text{rep2=\sol[1]}
\text{rep3=\sol[2]}
\text{indcond=}
#endif
  \conditions{\indcond}
\steps{\mstep}
\statement{
\if{\step=1}
 {
 \intro
 <div class="wimscenter">\embed{reply1}</div>
 }
 {
 \intro2
#if defined TARGET_polpart2
 <div class="wimscenter">\(S=)&#123;\embed{reply2,5},\embed{reply3,5}&#125;</div>
<div class="wims_instruction"> Ordonner les solutions dans l'ordre croissant;<br>
Taper <span class="tt">sqrt(a)</span> pour \(\sqrt{a}).</div>
 }
}
\answer{}{\rep1;Oui,Non}{type=radio}
\answer{}{\rep2}{type=function}
\answer{}{\rep3}{type=function}
#else
 <div class="wimscenter">\(P(x)=)(\embed{reply2,7})\(\times)(\embed{reply3,7})</div>
<div class="wims_instruction">Taper <span class="tt">sqrt(a)</span>
pour \(\sqrt{a}\).</div>
 }
}
\answer{}{\rep1;Oui,Non}{type=radio}
\answer{}{\rep2}{type=function}
\answer{}{\rep3}{type=function}
\function{solexp=(\reply2)*(\reply3)}
\real{w0=evalue(\solexp,x=0)}
\real{w1=evalue(\solexp,x=1)}
\real{w2=evalue(\solexp,x=2)}
\real{v0=evalue(\eqrx,x=0)}
\real{v1=evalue(\eqrx,x=1)}
\real{v2=evalue(\eqrx,x=2)}
\text{condx1=wims(position char x  in \reply2)}
\text{condx2=wims(position char x in \reply3)}
\integer{goodcond=\v0=\w0 and \v1=\w1 and \v2=\w2 and \condx1>0 and \condx2>0?1:0}
\condition{\goodcond=1}
\feedback{\goodcond=0 and \rep1=1}{La factorisation de \(P(x)) est \(\eqfx).
}
#endif
