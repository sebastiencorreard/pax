%%%  Codé par LSD
\title{Question 105 Résolution d'une équation}
\keywords{quizz,equations}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-b-mathematiques.pdf du DNB publié sur éduscol en décembre 2025}

\integer{a=randint(2..10)*randint(-1,1)}
\integer{b=randint(2..10)*randint(-1,1)}
\integer{c=randint(11..20)*randint(-1,1)}
%%% MB pour éviter les --2 ou 2*-2
\text{abis=\a<0?(\a):\a}   
\text{bbis=\b<0?(\b):\b}
\text{cbis=\c<0?(\c):\c} 

\text{eq1=\(\a x=\c\)}
\text{eq2=\(x+\b=\c\)}
\text{eq3=\(\a x+\b=\c\)}
\text{typeeq=randomitem(eq1,eq2,eq3,eq3,eq3)} (MB) pour avoir plus de questions comme le sujet zéro

\if{\typeeq issametext eq1}{
    \text{enonce=Pour résoudre l’équation \eq1&#44; on effectue le calcul&nbsp;&#58;}
    \text{enonceb=}
    \text{bad1=\(x=\c+\a\)}
    \text{bad2=\(x=\c-\a\)}
    \text{bad3=\(x=-\c+\a\)}
    
    \text{bad4=\(x=\a-\c\)}
    \text{bad5=\(x=\a+\c\)}
    \text{bad6=\(x=-\a+\c\)}
         
    \text{bad7=\(x=\a/\c\)}
    \text{bad8=\(x=-\a/\c\)}
    \text{bad9=\(x=\a/-\c\)}
    
    \text{good=\(x=\c/\a\)} 
    \text{feedback= La bonne réponse est&nbsp;&#58 <span style="nowrap">\good.</span><ul class="wims_nopuce"><li> \(\a x=\c\) </li><li> \(\frac{\a x}{\a}=\frac{\c}{\a}) </li><li> \good</li></ul>}
    }

\if{\typeeq issametext eq2}{
    \text{enonce=Pour résoudre l’équation \eq2&#44; on effectue le calcul&nbsp;&#58;}
    \text{enonceb=}
    \text{bad1=\(x=\c/\b)}
    \text{bad2=\(x=-\c/\b)}
    \text{bad3=\(x=\c/-\b)}
    
    \text{bad4=\(x=\b+\c\)}
    \text{bad5=\(x=\b-\c\)}
    \text{bad6=\(x=-\b+\c\)}
         
    \text{bad7=\(x=\b/\c\)}
    \text{bad8=\(x=-\b/\c\)}
    \text{bad9=\(x=\b/-\c\)}
    
    \text{good=\(x=\c-\b)} 
    \text{feedback=La bonne réponse est&nbsp;&#58 <span style="nowrap">\good.</span><ul class="wims_nopuce"><li> \(x+\b=\c\) </li><li> \(x+\b-\b=\c-\b) </li><li> \(x=\c-\b)</li></ul>}
    }

\if{\typeeq issametext eq3}{
    \text{enonce=Pour résoudre l’équation \eq3&#44; on effectue le calcul&nbsp;&#58;}
    \text{enonceb=}
    \text{bad1=\(x=(\c/\a)+\b\)}
    \text{bad2=\(x=(\c/\a)-\b\)}
    \text{bad3=\(x=(\c/-\a)-\b\)}
    
    \text{bad4=\(x=(\c-\a)+\b\)}
    \text{bad5=\(x=(\c+\a)+\b\)}
    \text{bad6=\(x=(\c-\a)-\b\)}
    \integer{c2=-\c} 
    \text{bad7=\(x=(\c\times\abis)+\b\)}  %%%bug affichage (corrigé) si a est négatif, il fait disparaitre le multiplier. N'a pas d'impact sur l'exo
    \text{bad8=\(x=(\c\times\abis)-\b\)}  %%%bug affichage (corrigé)si a est négatif, il fait disparaitre le multiplier. N'a pas d'impact sur l'exo
    \text{bad9=\(x=(\c2\times\abis)+\b\)} %%%bug affichage (corrigé)si a est négatif, il fait disparaitre le multiplier. N'a pas d'impact sur l'exo
    %%% MB
    \integer{b2=-\b}
    \text{b2=\b2<0?\b2:+\b2}
    \text{good=\(x=\frac{\c \b2}{\a}\)}
    \text{feedback=La bonne réponse est&nbsp;&#58 <span style="nowrap">\good.</span> <ul class="wims_nopuce"><li> \(\a x+\b=\c\) </li><li> \(\a x+\b \b2=\c \b2\) </li><li> \(\a x=\c \b2\) </li><li> \(\frac{\a x}{\a}=\frac{\c \b2}{\a}\) </li><li> \good</li></ul>} 
    }

\text{bads=randomitem(\bad1,\bad2,\bad3),randomitem(\bad4,\bad5,\bad6),randomitem(\bad7,\bad8,\bad9)}
