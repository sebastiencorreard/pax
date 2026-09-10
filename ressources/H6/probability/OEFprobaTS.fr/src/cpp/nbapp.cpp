target=nbapp
\title{D. Dénombrement}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\keywords{combinatorics}
\description{Dénombrement d'ensembles classiques}
\text{appEF=\( n^p\)}
\text{appFE=\( p^n\)}
\text{cardEF=\(p \times n\)}
\text{injEF=\(\frac{n!}{(n-p)!}\)}
\text{combEF=\(\frac{n!}{(n-p)!\times p!}\)}
\text{bijE=\(p!\)}
\text{bijF=\(n!\)}
\text{pE=\(2^p\)}
\text{pF=\(2^n\)}


\text{data=Le nombre d'applications de \(E\) dans \(F\), \appEF,
Le nombre d'applications injectives de \(E\) dans \(F\), \injEF,
Le nombre d'applications bijectives de \(E\) dans  \(E\),\bijE,
Le nombre d'applications bijectives de \(F\) dans \(F\),\bijF,
Le nombre de \(p\)-listes de \(F\), \appEF,
Le nombre d'arrangements de \(p\) éléments parmi \(n\), \injEF,
Le nombre de combinaisons de \(p\) éléments parmi \(n\), \combEF,
Le nombre de permutations de \(n\) éléments, \bijF,
Le nombre de parties de \(E\),\pE,
Le cardinal de \(E \times F\),\cardEF,
Le nombre de parties de \(F\),\pF,
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\text{rep=\cedata[2]}
\text{replst=\appEF,\appFE,\injEF,\bijE,\bijF,\pE,\pF,\cardEF,\combEF}
\text{size=110x50x1}
\text{name_enonce= On considère un ensemble \(E\) de cardinal \(p\) et un ensemble \(F\) de cardinal \(n \geq p\).}
\text{name_instr=Compléter}
\text{name_instr2= en choisissant la bonne formule.}
\text{name_eq=est égal à}
/*Pour la version latex*/
\text{name_instr3=en entourant la bonne formule}
\text{L=shuffle(9)}
\text{latexchoix= \replst[\L[1]]}
\for{i=2 to 9}{
  \text{latexchoix=\latexchoix \quad \replst[\L[\i]] }
}
\statement{
 \name_enonce
<div class="wims_question">
  \name_instr \name_instr2<br/>
<label for="reply1">\quest  \name_eq </label> \embed{reply1,\size}
</div>
}
\answer{Réponse}{\rep;\replst}{type=clickfill}
\latex{
\begin{statement}
 \name_enonce\newline
 \name_instr \name_instr3. \newline 
\quest  \name_eq 
\begin{center}\latexchoix \end{center}
\end{statement}
\begin{solution}
\quest \name_eq \rep.
\end{solution}
}
