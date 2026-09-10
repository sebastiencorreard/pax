target=pscalcul6, pscalcul7
#define TITLE Calcul 

\author{Cyrille,Douriez}
\email{cyrille.douriez@ac-amiens.fr}
\format{html}

\integer{a=randint(4..7)}
\integer{b=randint(3..8)}
\integer{s=randint(2..(\a+\b-1))}

\matrix{vec=AB,BC,AC,\a,\s,\b,BA
AC,CB,AB,\s,\a,\b,CA
BA,AC,BC,\a,\b,\s,AB
BC,CA,BA,\s,\a,\b,CB
CA,AB,CB,\a,\b,\s,AC
CB,BA,CA,\a,\s,\b,BC}


#if defined TARGET_pscalcul6
\title{TITLE avec les normes 1}
\integer{choix=randitem(1,1,2,2,3,3,4,5,6)}
\text{vecu=\overrightarrow{ \vec[\choix;1]}}
\text{vecv=\overrightarrow{ \vec[\choix;2]}}
\text{vecs=\overrightarrow{ \vec[\choix;3]}}
\real{ps=0.5*(\s^2-\a^2-\b^2)}
<!-- pour le corrigé-->
\real{corr=\ps}
\text{vecc=\overrightarrow{ \vec[\choix;1]}}
#endif

#if defined TARGET_pscalcul7
\title{TITLE avec les normes 2}
\integer{choix=randitem(1,1,2,2,3,3,3,3)}
\text{vecu=\overrightarrow{ \vec[\choix;7]}}
\text{vecv=\overrightarrow{ \vec[\choix;2]}}
\text{vecs=\overrightarrow{ \vec[\choix;3]}}
\text{vecc=\overrightarrow{ \vec[\choix;1]}}
\real{ps=-0.5*(\s^2-\a^2-\b^2)}
<!-- pour le corrigé-->
\real{corr=-\ps}
\text{corrige71=\(\vecu.\vecv=\left (-\overrightarrow{ \vec[\choix;1]}\right ).\vecv=-\left (\overrightarrow{ \vec[\choix;1]}.\vecv\right )).}
\text{corrige72=On en déduit que \(\vecu.\vecv=\ps).}
#endif
<!-- les longueurs des côtés-->
\integer{l1=\vec[\choix;4]}
\integer{l2=\vec[\choix;5]}
\integer{l3=\vec[\choix;6]}


\statement{Dans un triangle \(ABC), on donne \(AB=\l1), \(AC=\l2) et \(BC=\l3).
<div class="wims_question">Calculer \(\vecu.\vecv).</div>
\(\vecu.\vecv=) \embed{r1,4}
}
\answer{}{\ps}{type=numeric}

\solution{\corrige71
<table><tr><td valign="top">\(\vecc.\vecv)</td><td valign="top">\(=\frac{1}{2}\left ( \|| \vecc+\vecv||^2-\||\vecc\||^2-\||\vecv\||^2\right))</td></tr>
<tr><td></td><td>\(=\frac{1}{2}\left ( || \vecs||^2-\||\vecc\||^2-\||\vecv\||^2\right))</td></tr>
<tr><td></td><td>\(=\frac{1}{2}\left ( \vec[\choix;3]^2-\vec[\choix;1]^2-\vec[\choix;2]^2 \right))</td></tr>
<tr><td></td><td>\(=\frac{1}{2}\left ( \s^2-\a^2-\b^2 \right)=\corr).</td></tr></table>
\corrige72

}
