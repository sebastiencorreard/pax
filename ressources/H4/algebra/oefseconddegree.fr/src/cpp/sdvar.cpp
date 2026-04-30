target=sdvar1, sdvar2, sdvar3, sdvar4, sdvar5, sdvar6, sdvar7, sdvar8
#define TITLE Variations d'une fonction du second degré


\author{David, Rousseau}##Fichier cpp par Cyrille Douriez##
\email{cyrille.douriez@ac-amiens.fr}
\format{html}
\language{fr}
\range{-5..5}
\computeanswer{no}
\precision{100}

\integer{a=randint(2..6)}
\integer{signe=randitem(-1,1)}
\integer{a1=\a*\signe}
\integer{q2=(\signe=-1)? 1:2}
\text{q3=(\signe=-1)? 1:2}
\text{q4=(\signe=-1)? 2:1}

#if defined TARGET_sdvar1
\title{TITLE de la forme ax²}
\function{f=maxima( \a1 * x^2)}
\text{corrige=f(x)=a x^2,0,}
#endif

#if defined TARGET_sdvar2
\title{TITLE sous forme développée ax²+c}
\integer{c=randint(1..10)*randitem(1,-1)}
\function{f=maxima( \a1 * x^2+\c)}
\text{corrige=f(x)=a x^2+c,0,}
#endif

#if defined TARGET_sdvar3
\title{TITLE sous forme canonique (cas simple)}
\integer{c=randint(1..8)}
\real{alpha1=randint(1..9)}
\function{f=\a1*( x - \alpha1 )^2+\c}
\text{corrige=f(x)=a \left ( x-\alpha \right )^2+b,\alpha,\alpha1}
#endif

#if defined TARGET_sdvar4
\title{TITLE sous forme canonique }
\integer{c=randint(1..8)}
\real{alpha1=randint(1..9)*randitem(1,-1)}
\function{f=maxima(\a1*( x - \alpha1 )^2+\c)}
\text{f=texmath(\f)}
\text{corrige=f(x)=a \left ( x-\alpha \right )^2+b,\alpha,\alpha1}
#endif

#if defined TARGET_sdvar5
\title{TITLE sous forme développée}
\integer{b=randint(1..10)*randitem(1,1,-1)}
\integer{c=randint(-15..15)}
\function{f= \a1 x^2+\b x+\c}
\rational{alpha=-\b/(2*\a1)}
##Pour le corrigé##
\text{num=(\b>0)? -\b:-(\b)}
\text{den=(\a1>0)? 2\times \a1:2\times(\a1)}
\text{corrige=f(x)=a x^2+b x+c,\frac{-b}{2a},\frac{\num}{\den  } =\alpha}
#endif

#if defined TARGET_sdvar6
\title{TITLE sous forme factorisée a(x-x1)(x-x2) 1}
\integer{x1=randint(1..8)}
\integer{x2=\x1+randint(1..7)}
\function{f= \a1 (x-\x1)(x-\x2)}
\rational{alpha=(\x1+\x2)/2}
\text{corrige=f(x)=a (x-x_1)(x-x_2),\frac{x_1+x_2}{2},\frac{\x1+\x2}{2} =\alpha}
#endif

#if defined TARGET_sdvar7
\title{TITLE sous forme factorisée a(x-x1)(x-x2) 2 }
\integer{x1=randint(1..6)*randitem(-1,1)}
\integer{x2=(\x1+randint(1..6))*randitem(-1,1)}
\function{f= \a1* (x-\x1)(x-\x2)}
\rational{alpha=(\x1+\x2)/2}
\text{corrige=(\x2>0)? f(x)=a (x-x_1)(x-x_2),\frac{x_1+x_2}{2},\frac{\x1+\x2}{2} =\alpha:f(x)=a (x-x_1)(x-x_2),\frac{x_1+(x_2)}{2},\frac{\x1+\x2}{2} =\alpha}
#endif

#if defined TARGET_sdvar8
\title{TITLE sous forme factorisée (ax+b)(cx+d)}
##
\integer{x1=randint(1..6)}
\integer{x2=(\x1+randint(1..6))*randitem(-1,1)}
\integer{x1=randint(1..6)*randitem(-1,1)}
\integer{a=randint(2..8)*randitem(-1,1)}
\integer{c=(\a*\signe>0)? randint(1..8):randint(-8..-1)}
\integer{b=-\x1*\a}
\integer{d=-\x2*\c}
\integer{a1=\a*\c}
\function{f=maxima( (\a*x+\b)*(\c*x+\d))}
\rational{alpha=(\x1+\x2)/2}
\text{corrige=(\x2>0)? f(x)=(ax+b)(cx+d),\frac{x_1+x_2}{2},\frac{\x1+\x2}{2} =\alpha:f(x)=(ax+b)(cx+d),\frac{x_1+x_2}{2},\frac{x_1+(x_2)}{2}=\alpha}
#endif

\text{etapes=r1
r2
r3,r4}
\steps{\etapes}

\statement{On considère la fonction \(f\) définie sur \(\mathbb{R}\) par \(f(x)= \f\).<br>
\if{\step=1}{
Quelle est l'abscisse du sommet de la parabole représentant \(f\) ? \embed{r1,4} 
#if defined TARGET_sdvar5||TARGET_sdvar6||TARGET_sdvar7
<div class="wims_instruction"> Pour un nombre rationnel, écrire 3/7 par exemple. Simplifier si besoin pour avoir un dénominateur positif.</div>
#endif



}

\if{\step=2}{Quel le signe du terme de plus haut degré de \(f(x)\) ? \embed{r2} }
\if{\step=3}{\(f\) est d'abord \embed{r3} sur &#93;\(-\infty ; \alpha)&#93; puis \embed{r4} sur &#91;\( \alpha; +\infty )&#91;.}
}

\answer{réponse }{ \alpha}{type=auto}{option=nonstop}
\answer{son signe est}{\q2;négatif,positif}{type=menu}
\answer{}{\q3;croissante,décroissante}{type=menu}
\answer{}{\q4;croissante,décroissante}{type=menu}

\solution{<p>Pour une fonction du second degré \(f\) d'expression \(\corrige[1]\), le sommet de la parabole représentative a pour abscisse \(\corrige[2]\)
#if defined TARGET_sdvar8 
avec \(x_1\) et \(x_2\) racines de \(f(x)\) 
#endif
.
#if defined TARGET_sdvar5||TARGET_sdvar6||TARGET_sdvar7||TARGET_sdvar8
Ici le sommet a donc pour abscisse \(\corrige[3]\).
#endif</p>
<p>Le coefficient de \(x^2\) dans \(f(x)\) est \(\a1\), il est donc \if{\a1>0}{positif}{négatif}. On en déduit que \(f\) est 
\if{\a1>0}{décroissante}{croissante} sur &#93;\(-\infty ; \alpha)&#93; et \if{\a1>0}{croissante}{décroissante} sur &#91;\( \alpha; +\infty )&#91; (parabole représentative orientée vers le \if{\a1>0}{haut}{bas}). }
