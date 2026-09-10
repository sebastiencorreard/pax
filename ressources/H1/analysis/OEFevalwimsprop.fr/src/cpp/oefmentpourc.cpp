target=oefmentpourc1 oefmentpourc2 oefmentpourc3 oefmentpourc4 oefmentpourc5
#include "author.inc"
\keywords{percents, mental_calculation}
\precision{100000}
#if defined TARGET_oefmentpourc1
# define NUM 1
\integer{n=randint(10..100)*10}
\integer{p=10}
\integer{rep=\n*\p/100}
\text{sol=\(10\%=\frac{10}{100}=\frac{1}{10}\)  un dixième, on divise par 10.<p>
\( 10 \%\) de \(\n\) font \(\n \div 10 = \rep\)}
#endif
#if defined TARGET_oefmentpourc2
# define NUM 2
\integer{n=randint(6..49)*2}
\integer{p=50}
\integer{rep=\n*\p/100}
\text{sol=\(50 \%=\frac{50}{100}=\frac{1}{2}\)  la moitié  on divise par 2.<p>
\(\p \%\) de \(\n\) font \(\n \div 2 = \rep\)}
#endif
#if defined TARGET_oefmentpourc3
# define NUM 3
\integer{n=randint(3..24)*4}
\integer{p=randint(5,25)}
\if{\p=5}{\integer{n=\n*10}}
\integer{rep=\n*\p/100}
\if{\p=5}{\text{sol=\(5\%\) est la moitié de \(10\%\).<p>
Pour calculer \(5\%\), on commence par calculer \(10\%\) en divisant par 10 puis on divise le résultat par 2.<p>
\(5\%\) de \(\n\) font \(\n \div 10 \div 2=\rep\)}}{
\text{sol=\(25\%=\frac{25}{100}=\frac{1}{4}\)  le quart  on divise par 4.<p>
\(\p\%\) de \(\n\) font \(\n \div 4 = \rep\)}}
#endif
#if defined TARGET_oefmentpourc4
# define NUM 4
\integer{n=randint(10..99)}
\integer{p=1}
\real{rep=\n*\p/100}
\text{sol=\(1\%=\frac{1}{100}\)  un centième  on divise par 100.<p>
\(p\%\) de \(\n\) fait \(\n \div 100 = \rep\)}
#endif
#if defined TARGET_oefmentpourc5
# define NUM 5
\integer{n=randint(6..49)*2}
\integer{p=randint(5,10,50)}
\if{\p=50}{\integer{n=\n+1}}
\real{rep=\n*\p/100}
\if{\p=5}{\text{sol=\(5\%\) est la moitié de \(10\%\).<p>
Pour calculer \(5\%\), on commence par calculer \(10\%\) en divisant par 10 puis on divise le résultat par 2.<p>
\(5\%\) de \(\n\) font \(\n \div 10 \div 2=\rep\)}}
\if{\p=10}{\text{sol=\(10\%=\frac{10}{100}=\frac{1}{10}\)  un dixième  on divise par 10.<p>
\(10\%\) de \(\n\) font \(\n \div 10 = \rep\)}}
\if{\p=50}{\text{sol=\(50\%=\frac{50}{100}=\frac{1}{2}\)  la moitié  on divise par 2.<p>
\(50 \%\) de \(\n\) font \(\n \div 2 = \rep\)}}
#endif
#include "lang_titles.inc"
#include "lang.inc"

\statement{
\name_instruction[1]
<div class="wims_question"><label for="reply1">\name_instruction[2] \p % \name_instruction[3] \n </label>: \embed{r1,5}.</div>
}
\answer{}{\rep}{type=numeric}
\hint{Pourcentages avec lesquels il est facile de calculer :
<ul class="wims_nopuce">
<li>0% d'un nombre ..... 0<p>
<li>1% d'un nombre ...... \(1\%=\frac{1}{100}\) un centième...on divise le nombre par 100.</li>
<li>10% d'un nombre ...... \(10\%=\frac{1}{10}\) un dixième...on divise le nombre par 10.</li>
<li>25% d'un nombre ......\(25\%=\frac{25}{100}=\frac{1}{4}\) un quart...on divise le nombre par 4.</li>
<li>50% d'un nombre ......\(50\%=\frac{50}{100}=\frac{1}{2}\) la moitié...on divise le nombre par 2.</li>
</ul>
Penser aussi que \(5\%\) est la moitié de \(10\%\) ou que \(75\%\) est le triple de \(25\%\).}
\solution{\sol}
\latex{
\begin{statement}
\name_instruction[2] \p \% \name_instruction[3] \n ? : \dotfill
\end{statement}

\begin{solution}
\name_instruction[4] \p \% \name_instruction[5] \n \name_instruction[6] \rep
\end{solution}
}
