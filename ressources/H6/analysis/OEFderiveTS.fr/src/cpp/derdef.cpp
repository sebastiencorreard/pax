target=derdef1 derdef2
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\computeanswer{yes}
#if defined TARGET_derdef1
# define NUM 1
#endif
#if defined TARGET_derdef2
# define NUM 2
#endif
#include "lang_titles.inc"
#if defined TARGET_derdef1
\text{name_good=Bonne réponse}
\integer{a=randint(2..5)}
\integer{a2=\a^2}
\integer{a3=\a^3}
\text{data=sqrt(x^3-\a3),\a,2
sqrt(x^2-\a2),\a,2
sqrt(x^2+\a2),\a,1
sqrt(x^3-\a),\a,1
(x-\a)*sqrt(x-\a),\a,1
sin(\a*x),0,1
tan(\a*x),0,1
}
\integer{i=randint(1..rows(\data))}
\text{cedata=row(\i,\data)}
\text{f=\cedata[1]}
\text{ft=texmath(\f)}
\integer{x0=\cedata[2]}
\integer{rep=\cedata[3]}
\text{y0=evalue(\f,x=\x0)}
\function{fl=(\f-\y0)/(x-\x0)}
\text{num = texmath(maxima(\f - \y0))}
\text{den = texmath(maxima(x - \x0))}
\text{taux= \dfrac{\num}{\den}}
\if{\rep=1}{
\function{fder=diff(\f,x)}
\real{nder=evalue(\fder,x=\x0)}
\text{mstep=r1,r2
r3}
 }{
 \text{mstep=r1,r2}
 }
\steps{\mstep}

\statement{<div class="wims_smallhelp">Cet exercice comporte une ou plusieurs étapes.</div>
<p>
On veut étudier la dérivabilité en \(x=\x0) de la fonction \(f) définie par :</p>
<div class="wimscenter">\(f(x)=\ft).</div>
<div class="wims_question">
\if{\step=1}{
<ol>
<li>Écrire la limite dont on doit vérifier l'existence pour conclure :
<div class="wimscenter"><label for="reply1">\(\displaystyle\lim_{x \rightarrow \x0})</label>\embed{reply1}.</div>
</li><li>
  Cette limite existe-t-elle ? \embed{reply2}.</li>
</ol></div>
<div class="wims_instruction">Pour écrire \(\sqrt{5}\) taper
<span class="tt">sqrt(5)</span>.
}{
<span class="oef_indgood">\name_good.</span>
  Le taux d'accroissement est \(\taux\).
<ol start="3">
<li>
 <label for="reply3">Le nombre dérivé de \( f \) en \( \x0 \) vaut \(f'(\x0) =\) </label> \embed{reply3}.
</li>
</ol>
}
</div>
}
\answer{expression de la limite}{\fl}{type=formal}
\answer{existence}{\rep;Oui,Non}{type=radio}
\answer{nombre dérivé}{\nder}{type=numexp}
#endif

#if defined TARGET_derdef2
\integer{x0=randint(-2..2)}
\integer{x1=\x0+randint(1..5)}
\integer{c=randint(1..3)*randint(1,-1)}
\integer{d=randint(1..5)*randint(1,-1)}
\integer{e=randint(1..5)*randint(1,-1)}

% Données de data: fonction de gauche, inégalité de gauche, fonction de droite, inégalité de droite, coefficient a, coefficient b , ensemble de défintion

\text{data=a*x+b,\(x \leq \x0),\c*x^2+\d*x+\e,\({x > \x0}),2*\c*\x0+\d,-\c*(\x0)^2+\e, \mathbb{R}
a*x+b,\(x \leq \x0),\c/(x-\x1),\({x > \x0}),-\c/(\x0-\x1)^2,\c*(2*\x0-\x1)/(\x0-\x1)^2, \mathbb{R} \setminus \lbrace \x1 \rbrace
x^2+a*x+b,\(x \leq \x0),\c*x^2+\d*x+\e,\({x > \x0}),2(\c-1)*\x0+\d,-(\c-1)*(\x0)^2+\e, \mathbb{R}
-x^2+a*x+b,\(x \leq \x0),\c*x^2+\d*x+\e,\({x > \x0}),2*(\c+1)*\x0+\d,-(\c+1)*(\x0)^2+\e, \mathbb{R}
x^2+a*x+b,\(x \leq \x0),\c/(x-\x1)+\d,\({x > \x0}),-\c/(\x0-\x1)^2 -2*\x0,\c*(2*\x0-\x1)/(\x0-\x1)^2 +(\x0)^2 +\d, \mathbb{R} \setminus \lbrace \x1 \rbrace
}
\integer{i=randint(1..rows(\data))}
integer{i=1}
\text{cedata=row(\i,\data)}
\text{def1=texmath(maxima(\cedata[1]))}
\text{def2=texmath(maxima(\cedata[3]))}
\text{defin=\(f(x)=\def1) pour \cedata[2] et \(f(x)=\def2) pour \cedata[4]}
\rational{a=\cedata[5]}
\rational{b=\cedata[6]}

\statement{<div>
Trouver les valeurs de \(a) et de \(b) pour que la fonction définie sur \(\cedata[7]\) par
<div class="wimscenter">\defin</div>
soit continue et dérivable sur \(\RR\;\).
</div>
<div class="wims_question">
<ul class="wims_nopuce"><li>
<label for="reply1">Valeur de \(a) =</label> \embed{reply1,7}
</li><li>
<label for="reply2">Valeur de \(b) =</label> \embed{reply2,7}
</li></ul>
</div>
}
\answer{\(a)}{\a}{type=numexp}
\answer{\(b)}{\b}{type=numexp}
#endif
