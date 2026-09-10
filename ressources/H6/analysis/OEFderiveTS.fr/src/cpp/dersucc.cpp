target=dersucc1 dersucc2 dersucc3
\author{Régine, Mangeard}
\email{regine@mangeard.Fr}
\format{html}
\precision{100}
\computeanswer{yes}
#if defined TARGET_dersucc1
# define NUM 1
#endif
#if defined TARGET_dersucc2
# define NUM 2
#endif
#if defined TARGET_dersucc3
# define NUM 3
#endif
#include "lang_titles.inc"
#if defined TARGET_dersucc1
\integer{a=randint(1..5)}
\integer{b=randint(1..5)}
\integer{n=randint(1..5)}

\text{data=(\a*x+\b)^\n,(-\a*x+\b)^\n,1/(\a*x+\b)^\n,sqrt(\a*x+\b),cos(\a*x+\b),sin(\a*x+\b)}
\text{f=randitem(\data)}
\text{ft=texmath(maxima(\f))}
\function{fder1=diff(\f,x)}
\function{fder2=diff(\fder1,x)}
\function{fder3=diff(\fder2,x)}

\statement{<p>
  On considère la fonction \(f) définie par</p>
  <div class="wimscenter">\(f(x)=\ft).</div>
  Calculer \(f'(x), f^{(2)}(x)) et \(f^{(3)}(x)):
  <div class="wims_question">
  <ul><li>
  <label for="reply1">\(f'(x)=)</label> \embed{reply1}
  </li><li>
  <label for="reply2">\(f^{(2)}(x)=)</label> \embed{reply2}
  </li><li><label for="reply3">\(f^{(3)}(x)=)</label> \embed{reply3}
  </li></ul>
  </div>
  <div class="wims_instruction">
  Taper <span class="tt">sqrt(x)</span> pour \(\sqrt{x}).
  </div>
}
\answer{fonction dérivée}{\fder1}{type=formal}
\answer{fonction dérivée seconde}{\fder2}{type=formal}
\answer{fonction dérivée troisième}{\fder3}{type=formal}
#endif
#if defined TARGET_dersucc2
\integer{n=randint(3..6)}
\integer{N=randint(2..5)+\n}
\integer{n1=\N-\n}
\text{quest=random(nul,constant)}
\integer{n2=\quest issametext nul?\N+1:\N}
\statement{<p>
  On considère une fonction polynôme \(P) de degré \N.</p>
  <div class="wims_question">
  <ol>
  <li>
  <label for="reply1">
  Quel est le degré du polynome \(P^{(\n)}), dérivé de \(P) à l'ordre \n?</label>
  \embed{reply1,4}</li>
  <li>
  <label for="reply2">\if{\quest issametext nul}
  {À partir de quel rang \(N) le polynôme \(P^{(N)}), dérivé de \(P) à l'ordre \(N\) est-il nul?}
  {À quel rang \(N) le polynôme \(P^{(N)}), dérivé de \(P) à l'ordre \(N\) est-il constant?}
  </label>
   \embed{reply2} </li>
  </ol>
  </div>
}
\answer{degré de \(P{(\n)})}{\n1}{type=numeric}
\answer{N}{\n2}{type=numeric}
#endif
#if defined TARGET_dersucc3
\integer{a=randint(1..5)}
\text{data=cos(\a*x),sin(\a*x),cos(-\a*x),sin(-\a*x)}
\text{datan=(\a)^n*cos(\a*x+n*pi/2),(\a)^n*sin(\a*x+n*pi/2),(\a)^n*cos(\a*x+n*pi/2),-(\a)^n*sin(\a*x+n*pi/2)}
\integer{i=randint(1..4)}
\text{f=item(\i,\data)}
\text{ft=texmath(\f)}
\function{fder1=diff(\f,x)}
\function{fder2=diff(\fder1,x)}
\function{fder3=diff(\fder2,x)}
\function{fder4=diff(\fder3,x)}
\text{fdern=item(\i,\datan)}
\statement{<p>
On considère la fonction \(f) définie par
</p>
<div class="wimscenter"> \(f(x)=\ft).</div>
<ol><li>
<div class="wims_question">Calculer \(f'(x)\), \(f^{(2)}(x)\), \(f^{(3)}(x)) et \(f^{(4)}(x)):
<ul><li><label for="reply1">\(f'(x)=)</label> \embed{reply1}
</li><li><label for="reply2">\(f^{(2)}(x)=)</label> \embed{reply2}
</li><li><label for="reply3">\(f^{(3)}(x)=)</label> \embed{reply3}
</li><li><label for="reply4">\(f^{(4)}(x)=)</label> \embed{reply4}
</li></ul>
</div>
</li><li>On rappelle que pour tout \(x), \(\cos(x)=-\sin(x-\frac{\pi}{2})) et \(\sin(x)=\cos(x-\frac{\pi}{2})).
<div class="wims_question">Conjecturer la formule donnant \(f^{(n)}(x)) en fonction de \(n)
<strong>qui pourrait être démontrée par récurrence.</strong>
<div class="wimscenter">
<label for="reply5">\(f^{(n)}(x)=)</label> \embed{reply5}</div>
</div>
</li></ol>
}
\answer{fonction dérivée}{\fder1}{type=formal}
\answer{fonction dérivée seconde}{\fder2}{type=formal}
\answer{fonction dérivée troisième}{\fder3}{type=formal}
\answer{fonction dérivée quatrième}{\fder4}{type=formal}
\answer{fonction dérivée nième,}{\fdern,n=[0,1,2,4,7,9,17,35,42,51,60]}{type=function}
#endif
