target=tirages
\title{D. Tirage et dénombrement}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\keywords{combinatorics, permutation, combination}
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


\text{data=le nb de tirages <strong> simultanés</strong> de \(p\) boules parmi \(n\), le nb de combinaisons de \(p\) éléments parmi \(n\), \combEF,
le nb de tirages <strong> successifs avec remise</strong> de \(p\) boules parmi \(n\),le nb de \(p\)-listes de \(p\) éléments parmi \(n\), \appEF,
le nb de tirages <strong> successifs sans remise</strong> de \(p\) boules parmi \(n\), le nb d'arrangements de \(p\) éléments parmi \(n\), \injEF,
le nb de tirages <strong> successifs sans remise</strong> de \(n\) boules parmi \(n\), le nb de permutations de \(n\) éléments, \bijF,
}
\integer{k=randint(1..3)}
\if{\k=1}{
  \integer{ind1=1}
  \integer{ind2=2}
}
\if{\k=2}{
  \integer{ind1=1}
  \integer{ind2=3}
}
\if{\k=3}{
  \integer{ind1=2}
  \integer{ind2=3}
}

\text{liste1=}
\text{liste2=}
\for{i=1 to 4}{
  \text{cedata=row(\i,\data)}
  \text{liste1=wims(append item \cedata[\ind1] to \liste1)}
  \text{liste2=wims(append item \cedata[\ind2] to \liste2)}
}
\text{size=100x200x200}
\text{explain=Soit \(n\) et \(p\) deux entiers strictement positifs tels que \(n\geq p\). 
 Mettre en correspondance&nbsp;}
/* pour la version latex */
\text{shuf1=shuffle(4)}
\text{shuf2=shuffle(4)}
\text{latexdatal=\liste1[\shuf1]}
\text{latexdatar=\liste2[\shuf2]}
\text{latexrep=\liste2[\shuf1]}
\real{latexsizel=7}
\real{latexsizer=7}
\text{latexsrc=\begin{tabular}{p{\latexsizel cm}lp{1cm}lp{\latexsizer cm}}}
\for{lk=1 to 4}{
  \text{latexsrc=\latexsrc \latexdatal[\lk] &\(\bullet\) &&\(\bullet\) & \latexdatar[\lk]\\\ }
}
\text{latexsrc=\latexsrc \end{tabular}}
\text{latexsol=\begin{tabular}{p{\latexsizel cm}lp{\latexsizer cm}}}
\for{lk=1 to 4}{
  \text{latexsol=\latexsol \latexdatal[\lk] &\(\longleftrightarrow \)& \latexrep[\lk]\\\ }
}
\text{latexsol=\latexsol \end{tabular}}
\statement{
 \explain:
<div class="wimscenter">
 \embed{reply1,\size}
</div>
}
\answer{Réponse}{\liste1;\liste2}{type=correspond}
\latex{
\begin{statement}
\explain
\begin{center}
\latexsrc
\end{center}
\end{statement}
\begin{solution}\

 \begin{center}
 \latexsol
 \end{center}
\end{solution}
}
