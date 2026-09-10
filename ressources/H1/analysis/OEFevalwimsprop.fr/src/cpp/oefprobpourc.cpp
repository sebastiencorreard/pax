target=oefprobpourc1 oefprobpourc2 oefprobpourc3 oefprobpourc4 oefprobpourc5

#include "author.inc"
\keywords{percents}
\format{html}
\precision{100000}
#if defined TARGET_oefprobpourc1
# define NUM 1
#endif
#if defined TARGET_oefprobpourc2
# define NUM 2
#endif
#if defined TARGET_oefprobpourc3
# define NUM 3
#endif
#if defined TARGET_oefprobpourc4
# define NUM 4
#endif
#if defined TARGET_oefprobpourc5
# define NUM 5
#endif

#include "lang_titles.inc"
#include "lang.inc"

\integer{a=randint(1..5)}
\text{m=row(\a,\name_m)}
\text{m=randomitem(\m)}

#if defined TARGET_oefprobpourc1
\integer{n=randint(30..80)*10}
\integer{p=randint(10,50)}
\integer{rep=\n*\p/100}
\if{\p=10}{\text{sol=\(10 \%=\frac{10}{100}=\frac{1}{10}\), un dixième...on divise par 10.
<p>Pour trouver \(10 \% \) d'un nombre, on divise le nombre par 10.</p>
\(\n \div 10 = \rep\)}}
\if{\p=50}{\text{sol=\(50 \%=\frac{50}{100}=\frac{1}{2}\), un demi...on divise par 2.<p>
Pour trouver \(50 \%\) d'un nombre, on divise le nombre par 2.</p>
\(\n \div 2 = \rep\)}</p>}
#endif

#if defined TARGET_oefprobpourc2
\integer{n=randint(8..20)*40}
\integer{p=randint(25,20)}
\integer{rep=\n*\p/100}
\if{\p=25}{\text{sol=\(25 \%=\frac{25}{100}=\frac{1}{4}\), un quart...on divise par 4.<p>
Pour trouver \(25 \% \) d'un nombre, on divise le nombre par 4.<p>
\(\n \div 4 = \rep\)}}
\if{\p=20}{\text{sol=\(20 \%=\frac{20}{100}=\frac{1}{5}\), un cinquième...on divise par 5.
Pour trouver \(20 \%\) d'un nombre, on divise le nombre par 5.<p>
\(\n \div 5 = \rep\)}}
#endif

#if defined TARGET_oefprobpourc3
\integer{n=randint(8..20)*40}
\integer{p=75}
\integer{rep=\n*\p/100}
\integer{tmp=\n/4}
\text{sol=\(75 \%=\frac{75}{100}=\frac{3}{4}\), les trois quarts...on divise par 4 puis on multiplie par 3.<p>
Pour trouver \(75 \% \) d'un nombre, on divise le nombre par 4 puis on multiplie le résultat par 3.</p>
\((\n \div 4) \times 3 = \tmp \times 3 = \rep\)}
#endif

#if defined TARGET_oefprobpourc4
\integer{n=randint(30..80)*10}
\integer{p=randint(30,40,60,70,80,90)}
\integer{rep=\n*\p/100}
\integer{tmp=\n*\p}
\text{sol=\(\frac{x}{\n}=\frac{\p}{100}\)<p>
On utilise l'égalité des produits en croix.</p>
<ul class="wims_nopuce">
<li>\(x \times 100 = \n \times \p\)</li><li>
\(x \times 100 = \tmp\)</li><li>
\(x = \frac{\tmp}{100}\)</li><li>
\(x = \rep\)</li></ul>}
#endif

#if defined TARGET_oefprobpourc5
\integer{p=randint(1..8)*10 + randint(1..9)}
\integer{rep=randint(3..8)*\p}
\integer{n=\rep*100/\p}
\integer{tmp=\n*\p}
\text{sol=\(\frac{x}{\n}=\frac{\p}{100}\)<p>
On utilise l'égalité des produits en croix.<p>
\(x \times 100 = \n \times \p\)<p>
\(x \times 100 = \tmp\)<p>
\(x = \frac{\tmp}{100}\)<p>
\(x = \rep\)}
#endif
\statement{
<div class="wims_question">
\name_instruction[1] \n \name_instruction[3]
<p>\name_instruction[2] \p % \name_instruction[4] \m.</p>
<p>\name_instruction[5] \m ?</p>
</div>
<div class="spacer"><label for="reply1">\name_instruction[6]</label> \embed{r1,5}
\name_instruction[7] \m.</div>
}
\answer{}{\rep}{type=numeric}
\solution{\sol<p>
\name_instruction[6] \rep \name_instruction[7] \m.}
\latex{
\begin{statement}
\name_instruction[1] \n \name_instruction[3]
\name_instruction[2] \p \% \name_instruction[4] \m. \name_instruction[5] \m ?

\par \name_instruction[6] \dotfill \name_instruction[7] \m.
\end{statement}

\begin{solution}
\name_instruction[6] \rep \name_instruction[7] \m.
\end{solution}
}
