target=logequ1 logequ2
\author{Cyrille, Douriez}
\email{cyrille.douriez@ac-amiens.fr}
\format{html}
\language{fr}
\range{-5..5}
\computeanswer{no}
\precision{100}
#define TITRE Equation avec un logarithme décimal
\integer{n=randint(-2..9)}
\rational{sol=10^(\n)}

#if defined TARGET_logequ1
\title{TITRE 1}
\text{equat=log(x)=\n}
\text{corrige=\(log(x)=\n) &hArr;  \(x=10^{\n}).}
#endif
#if defined TARGET_logequ2
\title{TITRE 2}
\integer{a=randint(1..8)*randitem(1,1,-1)}
\integer{b=randint(1..10)*randitem(-1,1)}
\integer{m=\n*\a+\b}
\function{f=maxima(\a*log(x)+\b)}
\text{f=texmath(\f)}
\text{equat=\f=\m}
\integer{k=\m-\b}
\text{corrige=\(\f=\m\) &hArr; \(\a log(x)=\k\) &hArr; \(log(x)=\n\) &hArr; \(x=10^{\n}\).}
#endif
\statement{<div class="wims_question">Résoudre dans \(\mathbb{R}\) l'équation :
\( \equat \)</div>
La solution est \embed{reply1,8}.}
\answer{La solution est }{\sol}{type=formal}
\solution{\corrige}
