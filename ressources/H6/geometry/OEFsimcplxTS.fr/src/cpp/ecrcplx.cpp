target=ecrcplx1 ecrcplx2 ecrcplx3 ecrcplx4
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\computeanswer{yes}

\text{lsta=0,1/6,1/4,1/3,1/2,2/3,3/4,5/6,1,-5/6,-3/4,-2/3,-1/2,-1/3,-1/4,-1/6}
\text{lstc=1,sqrt(3)/2,sqrt(2)/2,1/2,0,-1/2,-sqrt(2)/2,-sqrt(3)/2,-1,-sqrt(3)/2,-sqrt(2)/2,-1/2,0,1/2,sqrt(2)/2,sqrt(3)/2}
\text{lsts=0,1/2,sqrt(2)/2,sqrt(3)/2,1,sqrt(3)/2,sqrt(2)/2,1/2,0,-1/2,-sqrt(2)/2,-sqrt(3)/2,-1,-sqrt(3)/2,-sqrt(2)/2,-1/2}
\text{lsttc=1,\frac{\sqrt{3}}{2},\frac{\sqrt{2}}{2},\frac{1}{2},,-\frac{1}{2},-\frac{\sqrt{2}}{2},-\frac{\sqrt{3}}{2},-1,-\frac{\sqrt{3}}{2},-\frac{\sqrt{2}}{2},-\frac{1}{2},,\frac{1}{2},\frac{\sqrt{2}}{2},\frac{\sqrt{3}}{2}}
\text{lstts=0,\frac{1}{2},\frac{\sqrt{2}}{2},\frac{\sqrt{3}}{2},1,\frac{\sqrt{3}}{2},\frac{\sqrt{2}}{2},\frac{1}{2},0,-\frac{1}{2},-\frac{\sqrt{2}}{2},-\frac{\sqrt{3}}{2},-1,-\frac{\sqrt{3}}{2},-\frac{\sqrt{2}}{2},-\frac{1}{2}}

#if defined TARGET_ecrcplx1
\title{Ecriture complexe 1}
\integer{wx=randint(-5..5)}
\integer{wy=\wx=0?randint(1..5)*randint(1,-1):randint(-5..5)}
\integer{cw=randint(1..3)}
\if{\cw=1}
  {
  \integer{wx=randint(1..3)}
  \integer{wy=0}
  }
\if{\cw=2}
  {
  \integer{wy=randint(1..3)}
  \integer{wx=0}
  }
\if{\cw=3}
  {
  \integer{wx=randint(1..3)}
  \integer{wy=\wx*randint(1,-1)}
  }

\rational{rap=randitem(1,2,3,1/2,2/3,1/4)}
\rational{rap=randitem(1,2,3,1/2)}
\text{trap=texmath(\rap)}
\integer{ia=randint(1..items(\lsta))}
\rational{ang=\lsta[\ia]}
\text{tangle=texmath(maxima(\ang*x))}
\text{tangle=wims(replace internal x by \pi in \tangle)}
\complex{w=\wx+i*\wy}
\text{tw=texmath(\w)}
\text{zp=\rap*(\lstc[\ia]+i*\lsts[\ia])*(z-(\w))+\w}
\text{a=\rap*(\lstc[\ia]+i*\lsts[\ia])}
\complex{b=(\w)*(1-\rap*(\lstc[\ia]+i*\lsts[\ia]))}
\text{tzp=\rap*(\lsttc[\ia]+i*\lstts[\ia])*(z-(\w))+\w}
\statement{<p>
Déterminer l'écriture complexe de la similitude directe de centre \(\Omega(\tw)),
de rapport \(\trap) et d'angle \(\tangle).
</p>
<div class="wimscenter"> \(z'=a z+b) avec \(a=) \embed{reply1} et \(b=) \embed{reply2}</div>
}
\answer{a}{\a}{type=complex}
\answer{b}{\b}{type=complex}
#endif

#if defined TARGET_ecrcplx2
\title{Ecriture complexe 2}
\integer{cas=randint(1..3)}
integer{cas=3}
\if{\cas=1}
  {
  \integer{ux=randint(-5..5)}
  \integer{uy=\ux=0?randint(1..5)*randint(1,-1):randint(-5..5)}
  \complex{u=\ux+i*\uy}
  \text{eqz=texmath(z+\u)}
  \integer{nat=1}
  }
\if{\cas=2}
  {
  \rational{k=simplify(randint(1..5)/randint(1,1,1,2,3))*randint(1,-1)}
  \rational{rap=abs(\k)}
  \integer{ang=\k<0?1:0}
  \integer{wx=randint(-5..5)}
  \integer{wy=\wx=0?randint(1..5)*randint(1,-1):randint(-5..5)}
  \complex{w=\wx+i*\wy}
  \rational{k2=simplify(1-\k)}
  \complex{ww=\k2*(\w)}
  \complex{eqz=maxima(\k*z+\ww)}
  \text{eqz=texmath(\eqz)}
  \integer{nat=2}
  }
\if{\cas=3}
  {
  \rational{k=simplify(randint(1..5)/randint(1,1,1,2,3))*randint(1,-1)}
  \rational{rap=abs(\k)}
  \integer{wx=randint(-5..5)}
  \integer{wy=\wx=0?randint(1..5)*randint(1,-1):randint(-5..5)}
  \complex{w=\wx+i*\wy}
  \text{lstang=1/2,-1/2,1/4,3/4,-1/4,-3/4}
  \integer{ia=randint(1..6)}
  \rational{ang=\lstang[\ia]}
  \integer{ez=randint(1..3)}
  \integer{ex=\ia<3?0:\ez}
  \integer{ex=\ia=4 or \ia=6?-\ez}
  \integer{ey=\ia<5?\ez:-\ez}
  \complex{e=\ex+i*\ey}
  \real{rap=sqrt((\ex)^2+(\ey)^2)}
  \complex{eqz=maxima((\e)*z-(\e)*(\w)+(\w))}
  \text{eqz=texmath(\eqz)}
  \integer{nat=2}
  }
\text{mstep=\cas=1?r1
r2:r1
r3,r4,r5}
\steps{\mstep}
\statement{<p>
On considère la similitude directe d'écriture complexe \(z'=\eqz).
</p>
\if{\step=1}
 {Déterminer la nature de cette similitude:<p>
Cette similitude est une \embed{reply1}.
</p>
 }
 {
\if{\cas=1}
   { Il s'agit en effet d'une translation de vecteur \(\vec{u}).<p>
    Déterminer l'affixe du vecteur \(\vec{u}): \embed{reply2}
    </p>
   }
   { Il s'agit en effet d'une similitude à centre \(\Omega).<p>
   Déterminer l'affixe du centre : \embed{reply3}<br>
   Déterminer le rapport de similitude: \embed{reply4}<br>
   Déterminer l'angle de similitude: \embed{reply5}\pi
   </p>
   }
 }
}
\answer{nature}{\nat;translation,similitude à centre, identité}{type=radio}
\answer{vecteur de translation}{\u}{type=complex}
\answer{centre}{\w}{type=complex}
\answer{rapport}{\rap}{type=numeric}
\answer{angle}{\ang}{type=numexp}
#endif

#if defined TARGET_ecrcplx3
\title{Ecriture complexe 3}
  \integer{ex=randint(-5..5)}
  \integer{ey=\ex=0?randint(1..5)*randint(1,-1):randint(-5..5)}
  \integer{dx=randint(-5..5)}
  \integer{dy=randint(-5..5)}
  \text{eqz=texmath(maxima((\ex+i*\ey)*z+\dx+i*\dy))}
  \real{rap=sqrt((\ex)^2+(\ey)^2)}
  \complex{w=(\dx+\dy*i)/(1-\ex-i*\ey)}
\statement{<p>
On considère la similitude directe d'écriture complexe \(z'=\eqz).
</p><p>
 Il s'agit d'une similitude de centre \(\Omega).
 </p>
   Déterminer l'affixe du centre : \embed{reply1}<br>
   Déterminer le rapport de similitude: \embed{reply2}
}
\answer{centre}{\w}{type=complex}
\answer{rapport}{\rap}{type=numeric}
#endif

#if defined TARGET_ecrcplx4
\title{Ecriture complexe 4}
 \text{xl=wims(makelist x for x=-5 to 5)}
 \text{xl=shuffle( \xl)}
 \complex{za=\xl[1]+randint(-5..5)*i}
 \complex{zb=\xl[2]+randint(-5..5)*i}
 \complex{zc=\xl[3]+randint(-5..5)*i}
 \complex{zd=\xl[4]+randint(-5..5)*i}
 \complex{a=((\zb)-(\zd))/((\za)-(\zc))}
 \complex{b=((\za)*(\zd)-(\zc)*(\zb))/((\za)-(\zc))}

\statement{<p>
Déterminer les nombres complexes \(a) et \(b) tels que
la similitude directe d'écriture complexe \(z'=a z+b)
envoie le point \(A(\za)) sur le point \(B(\zb))
et le point \(C(\zc)) sur le point \(D(\zd)).
</p>
<div class="wimscenter"> \(a=) \embed{reply1} et \(b=) \embed{reply2}</div>
}
\answer{a}{\a}{type=complex}
\answer{b}{\b}{type=complex}
#endif
