target=sddescrcourbe1, sddescrcourbe2, sddescrcourbe3
#define TITLE Description de courbe

\author{Cyrille,Douriez}
\email{cyrille.douriez@ac-amiens.fr}
\format{html}
\language{fr}
\range{-5..5}
\computeanswer{no}

\integer{a=randint(1..6)*randint(-1,1)}
\integer{b=randint(-10..10)}
\integer{x1=randint(-9..1)}
\integer{x2=\x1+randint(1..9)}
\integer{orient=(\a>0)? 2:1}

#if defined TARGET_sddescrcourbe1
\title{TITLE 1}
\function{f=maxima(\a*x^2+\b)}
\real{x=0}
\text{corrige=La parabole est symétrique par rapport à la droite d'équation \(x=\x\)}
#endif

#if defined TARGET_sddescrcourbe2
\title{TITLE 2}
\function{f=maxima(\a*(x-\x1)*(x-\x2))}
\function{f1=maxima(x-\x1)}
\function{f2=maxima(x-\x2)}
\real{x=(\x1+\x2)/2}
\text{corrige2=(\x2>0)? \frac{\x1+\x2}{2}=\x:\frac{\x1+(\x2)}{2}=\x}
\text{corrige=Les racines de \(f) sont \(\x1) et \(\x2) (en effet, \(f(x)=0) &hArr; \(\f1=0) ou \(\f2=0) &hArr; \(x=\x1) ou \(x=\x2)) donc la parabole est symétrique par rapport à la droite d'équation 
\(x=\corrige2\)}

#endif

#if defined TARGET_sddescrcourbe3
\title{TITLE 3}
\integer{a1=randint(1..5)}
\integer{b=-\a1*\x1}
\integer{c=randint(1..5)*randint(-1,1)}
\integer{d=-\c*\x2}
\function{f1=maxima(\a1*x+\b)}
\function{f2=maxima(\c*x+\d)}
\integer{a=\a1*\c}
\function{f=maxima((\f1)*(\f2))}
\rational{x=(\x1+\x2)/2}
\integer{orient=(\a>0)? 2:1}
\text{corrige2=(\x2>0)? \frac{\x1+\x2}{2}=\x:\frac{\x1+(\x2)}{2}=\x}
\text{corrige=Les racines de \(f) sont \(\x1) et \(\x2) (en effet, \(f(x)=0) &hArr; \(\f1=0) ou \(\f2=0) &hArr; \(x=\x1) ou \(x=\x2)) donc la parabole est symétrique par rapport à la droite d'équation 
\(x=\corrige2\)}
#endif


\rational{y=evaluate(\f,x=\x)}
\text{f=texmath(\f)}


\statement{Soit \(f\) la fonction du second degré d'expression : \(f(x)=\f\).<br> 
La courbe représentative de \(f\) est une \embed{r1,7} orientée vers \embed{r2}, symétrique par rapport à la droite d'équation
\embed{r3,2} et de sommet S(\embed{r4,3} ; \embed{r5,3}).}

\answer{}{parabole}{type=atext}
\answer{}{\orient;le bas,le haut}{type=menu}
\answer{}{x=\x}{type=equation}
\answer{}{\x}{type=formal}
\answer{}{\y}{type=formal}


\solution{\(f) étant une fonction du second degré, sa courbe est une parabole. Comme  le coefficient de \(x^2\) dans \(f(x)\) est \if{\orient==2}{\(\a>0),}{\(\a<0),} cette parabole est orientée vers 
le \if{\orient==2}{haut.}{bas.} \corrige. Le sommet de cette parabole a pour coordonnées 
\((\x ; f(\x))) c'est à dire \((\x; \y)).
}
