target=ptecar1 ptecar2 ptecar3 ptecar4 ptecar5
#if defined TARGET_ptecar1
# define NUM 1
#endif
#if defined TARGET_ptecar2
# define NUM 2
#endif
#if defined TARGET_ptecar3
# define NUM 3
#endif
#if defined TARGET_ptecar4
# define NUM 4
#endif
#if defined TARGET_ptecar5
# define NUM 5
#endif
#include "lang_titles.inc"
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\text{xl=wims(makelist x,-x for x=1 to 20)}
\text{ind=shuffle(40)}
\integer{x1=\xl[\ind[1]]}
\integer{x2=\xl[\ind[2]]}
\integer{x3=\xl[\ind[3]]}
\rational{a=simplify(randint(1..9)*randint(1,-1)/random(1,2,4,5))}
\rational{b=simplify(randint(1..9)*randint(1,-1)/random(1,2,4,5))}
\rational{y1=\a*\x1+\b}
\rational{y2=\a*\x2+\b}
\rational{y3=\a*\x3+\b}
\text{f=\b=0?texmath(\a*x):texmath(\a*x+\b)}

#if defined TARGET_ptecar1
\text{lstrep=\(\frac{f(x_1)-f(x_2)}{x_1-x_2}),\((f(x_1)-f(x_2))*(x_1-x_2)),\(f(x_1)-f(x_2)),\(\frac{f(x_1)+f(x_2)}{x_1+x_2})}
\text{rep=\b=0?texmath(\a*x):texmath(\a*x+\b)}
\statement{
  Quelle est la quantité constante qui caractérise une fonction affine&nbsp;?
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{1;\lstrep}{type=radio}{option=shuffle}
#endif
#if defined TARGET_ptecar2
\title{TITRE 2}
\integer{k=randint(1,2)}
\rational{y3=\k=2?\y3+randint(1..5)*randint(1,-1)}
\statement{
  On considère une fonction \(f) telle que
<div class="wimscenter">\(f(\x1)=\y1), \(f(\x2)=\y2) et \(f(\x3)=\y3)</div>
  La fonction \(f) peut-elle être une fonction affine&nbsp;?
<div class="wimscenter">\embed{reply1,7}</div>
}
\answer{affine?}{\k;Oui,Non}{type=radio}
\feedback{\k=1}{\(f(x)=\f)}
#endif

#if (defined TARGET_ptecar3  || defined TARGET_ptecar4  || defined TARGET_ptecar5 )
#if defined TARGET_ptecar3
\title{TITRE 3}
\text{textcond=Si \(f(\x1)=\y1) et \(f(\x2)=\y2) &#44;}
\text{textquest=Que vaut \(f(\x3))&nbsp;?}
\text{quest=\(f(\x3))}
\rational{rep=\y3}
#endif
#if defined TARGET_ptecar4
\title{TITRE 4}
\text{quest=le coefficient directeur de \(f) vaut \(\a) et \(f(\x1)=\y1)}
\rational{dy=\y1-\y2}
\text{textcond=Si \(f(\x1)-f(\x2))=\dy &#44;}
\text{textquest=Que vaut son coefficient directeur&nbsp;?}
\text{quest=\(a)}
\rational{rep=\a}
#endif
#if defined TARGET_ptecar5
\title{TITRE 5}
\text{textcond=Si son coefficient directeur vaut \a&#44;}
\text{textquest=Que vaut \(f(\x1)-f(\x2))&nbsp;?}
\text{quest=\(f(\x1)-f(\x2))}
\rational{rep=\y1-\y2}
#endif
\statement{
  On considère une fonction affine \(f)
<div class="wimscenter">\textcond</div>
\textquest&nbsp;:
<div class="wimscenter">\quest=\embed{reply1,7}</div>
}
\answer{\(f(x))}{\rep}{type=algexp}
#if defined TARGET_ptecar3
\feedback{1=1}{\(f(x)=\f)}
#endif
#endif
