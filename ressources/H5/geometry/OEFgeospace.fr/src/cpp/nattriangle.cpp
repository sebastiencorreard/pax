target=nattriangle
#include "author.inc"
\precision{10000}
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{liste=\name_liste}
** donnée de trois vecteurs indépendants
\matrix{V=slib(matrix/orthogonal 3,3)}
\matrix{u=\V[1;]}
\rational{nu=(\u[1])^2+(\u[2])^2+(\u[3])^2}
\matrix{v=\V[2;]}
\rational{nv=(\v[1])^2+(\v[2])^2+(\v[3])^2}

%% coordonnées de A: matrice m
\matrix{a=slib(matrix/random 1,3,5)}
\integer{x=random(2..10)}
\integer{y=random(2..10)}
\integer{z=random(2..10)}

%% k=1 isocèle en A, k=2 equilatéral, k=3 rectangle, k=4 isocèle rectangle, k=5 quelconque
\integer{k=randint(1..4)}

\if{\k=2}{
%% equilatéral
\integer{s1=randitem(1,-1)}
\integer{s2=randitem(1,-1)}
\integer{s3=randitem(1,-1)}
\integer{ms3=\s3*(-1)}
\rational{b1=\a[1]+(\s1)*(\x)}
\rational{b2=\a[2]}
\rational{b3=\a[3]+(\s3)*(\x)}
\matrix{b=\b1,\b2,\b3}
\rational{c1=\a[1]}
\rational{c2=\a[2]+\s2*\x}
\rational{c3=\a[3]+\s3*\x}
\matrix{c=\c1,\c2,\c3}
\text{rep=\liste[2]}
}
\if{\k=1}{
%% isocèle
\integer{s1=randitem(1,-1)}
\integer{s2=randitem(1,-1)}
\integer{s3=randitem(1,-1)}
\integer{ms3=\s3*(-1)}
\rational{b1=\a[1]+(\s1)*\x}
\rational{b2=\a[2]+(\s2)*\y}
\rational{b3=\a[3]+(\s3)*\z}
\matrix{b=\b1,\b2,\b3}
\rational{c1=\a[1]+(\s3)*\y}
\rational{c2=\a[2]+(\s1)*\z}
\rational{c3=\a[3]+(\s2)*\x}
\matrix{c=\c1,\c2,\c3}
\text{rep=\liste[1]}
%% verifier qu'il n'est pas equilatéral
\rational{distbc=((\s3)*(\y)-(\s1)*\x)^2+((\s1)*\z-(\s2)*\y)^2+((\s2)*\x-(\s3)*\z)^2}
\rational{distab=(\x)^2+(\y)^2+(\z)^2}
\text{rep=\distbc=\distab?\liste[2]:\liste[1]}
%% vérifier s'il est  rectangle
\rational{distab=2*\distab}
\text{rep=\distbc=\distab2?\liste[4]}
}

\if{\k=3}{
%% rectangle
\matrix{b=pari(print([\a]+[\u]))}
\matrix{c=pari(print([\a]+[\v]))}

%% vérifier qu"il n'est pas isocèle
\text{rep=\nu=\nv?\liste[4]:\liste[3]}
}
\if{\k=4 or \k=5}{
%% rectangle
\integer{j1=\k=5?1:random(1..3)}
\integer{j2=\k=5?1:\j1+random(1..3)}
\matrix{b=pari(print([\a]+[\u]*\j1))}
\matrix{c=pari(print([\a]+[\v]*\j2))}
\text{rep=\k=5?\liste[4]:\liste[3]}
}

%% préparation de la solution à afficher
\rational{ab1=\b[1]-\a[1]}
\rational{ab2=\b[2]-\a[2]}
\rational{ab3=\b[3]-\a[3]}
\rational{ac1=\c[1]-\a[1]}
\rational{ac2=\c[2]-\a[2]}
\rational{ac3=\c[3]-\a[3]}
\rational{bc1=\c[1]-\b[1]}
\rational{bc2=\c[2]-\b[2]}
\rational{bc3=\c[3]-\b[3]}
\rational{nab=(\ab1)^2+(\ab2)^2+(\ab3)^2}
\rational{nac=(\ac1)^2+(\ac2)^2+(\ac3)^2}
\rational{nbc=(\bc1)^2+(\bc2)^2+(\bc3)^2}

\text{size=confparm1=1 ? :x-large}

\text{latextxt=\begin{radio}}
\for{h=1 to 5}{
\text{latextxt=\latextxt
\item \liste[\h]}
}
\text{latextxt=\latextxt
\end{radio}}
\statement{
<div class="\style1">
<p>
\name_instruction
</p>
<p class="wimscenter">
 \(A(\a[1];\a[2];\a[3])\), \(B(\b[1];\b[2];\b[3])\), \(C(\c[1];\c[2];\c[3])\).
</p><p>
\name_question \(A B C\).
</p>
</div>
<div class="\style2">
 \name_answer \embed{choice1,\size}.
</div>
}

\choice{}{\rep}{\liste}
\hint{Calculer les distances \(A B\), \(A C\) et \(B C\).}

\solution{Calculons les composantes des vecteurs \(\overrightarrow{A B}\), \(\overrightarrow{A C}\) et \(\overrightarrow{B C}\):<br>
<ul class="wims_nopuce">
  <li>\name_calcul \(\overrightarrow{A B}\): \(\left(\begin{array}{c}\b[1]- (\a[1]) \\ \b[2]-(\a[2]) \\ \b[3]-(\a[3])\end{array}\right)\)
    = \(\left(\begin{array}{c} \ab1 \\ \ab2 \\ \ab3 \end{array}\right)\)
  </li><li>
    \name_calcul \(\overrightarrow{A C}\): \(\left(\begin{array}{c}\c[1]- (\a[1]) \\ \c[2]-(\a[2]) \\ \c[3]-(\a[3])\end{array}\right)\)
    = \(\left(\begin{array}{c} \ac1 \\ \ac2 \\ \ac3 \end{array}\right)\)
  </li><li>
    \name_calcul \(\overrightarrow{B C}\): \(\left(\begin{array}{c}\c[1]- (\b[1]) \\ \c[2]-(\b[2]) \\ \c[3]-(\b[3])\end{array}\right)\)
    = \(\left(\begin{array}{c} \bc1 \\ \bc2 \\ \bc3 \end{array}\right)\)
</ul>
Donc \(A B^2 =\nab\), \(A C^2 = \nac\), \(B C^2 = \nbc\).
\textsol \rep.
}
\latex{
\begin{statement}
\name_instruction
<p class="wimscenter">
 \(A(\a[1];\a[2];\a[3])\), \(B(\b[1];\b[2];\b[3])\), \(C(\c[1];\c[2];\c[3])\).
</p><p>
\name_question \(A B C\).
</p>
\name_answer
\latextxt
\end{statement}
\begin{solution}
\name_solution
\par
\begin{itemize}
\item
\(\overrightarrow{A B}\): \(\left(\begin{array}{c}\b[1]- (\a[1]) \\ \b[2]-(\a[2]) \\ \b[3]-(\a[3])\end{array}\right)\) = \(\left(\begin{array}{c} \ab1 \\ \ab2 \\ \ab3 \end{array}\right)\)
\item
\(\overrightarrow{A C}\): \(\left(\begin{array}{c}\c[1]- (\a[1]) \\ \c[2]-(\a[2]) \\ \c[3]-(\a[3])\end{array}\right)\) = \(\left(\begin{array}{c} \ac1 \\ \ac2 \\ \ac3 \end{array}\right)\)
\item
\(\overrightarrow{B C}\): \(\left(\begin{array}{c}\c[1]- (\b[1]) \\ \c[2]-(\b[2]) \\ \c[3]-(\b[3])\end{array}\right)\) = \(\left(\begin{array}{c} \bc1 \\ \bc2 \\ \bc3 \end{array}\right)\)
\end{itemize}
\(A B^2 =\nab\), \(A C^2 = \nac\), \(B C^2 = \nbc\).
\textsol \rep.
\end{solution}
}
