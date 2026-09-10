target=cnp1 cnp2 cnp3
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{1000}

#if defined TARGET_cnp1 || defined TARGET_cnp2
#define TITRE B. Coefficients binomiaux
# if defined TARGET_cnp1
#   define NUM 1
# else
#   define NUM 2
#endif
#endif
#if defined TARGET_cnp3
#define TITRE A. Simplification avec factorielle
# define NUM
#endif
\title{TITRE NUM}
#if defined TARGET_cnp1
\keywords{combination}
\integer{p=randint(0..5)}
\integer{n=randint(\p..\p+10)}
\integer{rep=binomial(\n,\p)}
\text{name_quest=Calculer le coefficient binomial&nbsp;}
\statement{
  \name_quest \(\left ( \begin{array}{c}\n \\ \p \end{array} \right )\). 
  <div class="wimscenter">
 <label for="reply1">\(\left ( \begin{array}{c}\n \\ \p \end{array} \right )=\)</label>\embed{reply1}
 </div>
}
\answer{}{\rep}{type=numexp}
\latex{
\begin{statement}
 \name_quest \(\left ( \begin{array}{c}\n \\ \p \end{array} \right )\). 
\end{statement}
\begin{solution}
\(\left ( \begin{array}{c}\n \\ \p \end{array} \right) =\rep.\)
\end{solution}
}
#endif

#if defined TARGET_cnp2
\keywords{combination}
\integer{p=randint(0..5)}
\integer{d=randint(-2..2)}
\integer{n0=\p-(\d)}
\text{tn=maxima(n+\d)}
\text{con=\n0>0? supérieur ou égal à \(\n0\).:positif.}
\if{\p=0}{\function{rep=1}}
   {\if{\p=1}{\function{rep=\tn}}
       {
        \function{rep=1/(\p!)}

        \for{j=0 to \p-1}
            { \function{rep=\rep *(maxima(n+\d-\j))}
            }
       }
    }
\text{reptex=texmath(\rep)}
\text{name_intro=Soit \(n\) un entier}
\text{name_quest=Exprimer le coefficient binomial} 
\text{name_n= en fonction de \(n\)&nbsp;} 
    
\statement{\name_intro \con
<div class="wims_question">
  \name_quest \(\left ( \begin{array}{c}\tn \\ \p \end{array} \right )\)
  \name_n:
<div class="wimscenter"><label for="reply1">\(\left ( \begin{array}{c}\tn \\ \p \end{array} \right )\)=</label>\embed{reply1}.</div>
</div>
}
\answer{}{\rep}{type=formal}{option=noanalyzeprint}
\feedback{1=1}{\(\left ( \begin{array}{c}\tn \\ \p \end{array} \right )=\reptex\)}

\latex{
\begin{statement}
\name_intro \con
 \name_quest \(\left ( \begin{array}{c}\tn \\ \p \end{array} \right )\). 
\end{statement}
\begin{solution}
\(\left ( \begin{array}{c}\tn \\ \p \end{array} \right ) =\reptex.\)
\end{solution}
}
#endif
#if defined TARGET_cnp1||defined TARGET_cnp2
\description{Pour se familiariser avec l'expression des coefficients binomiaux}
\solution{Si \(n\) et \(k\) désignent des entiers positifs tels que \(k\leq n\) alors 
\(\left ( \begin{array}{c}n \\ k \end{array} \right )=\frac{n!}{k!\times(n-k)!}\).}
#endif
#if defined TARGET_cnp3
\keywords{factorial}
\description{Pour se familiariser la définition de la factorielle d'un entier}
\integer{i=randint(1,2)}
\integer{d=randint(2..4)}
\integer{p1=randint(0..5)}
\integer{p2=\p1-\d}
\integer{absp2=abs(\p2)}
\text{hyp=\p2<0?strictement supérieur à \absp2:strictement positif}
\integer{cas=randint(1,2)}
\if{\cas=1}{
  \text{num=maxima(n+\p1)}
  \text{den=maxima(n+\p2)}
  \text{rep=}
  \for{j=0 to \d-1}{ \function{rep=\j=0?(maxima(n+\p1)):\rep *(maxima(n+\p1-\j))}}
}{
  \text{den=maxima(n+\p1)}
  \text{num=maxima(n+\p2)}
  \text{rep=}
  \for{j=0 to \d-1}{\text{rep=\j=0?(maxima(n+\p1)):\rep *(maxima(n+\p1-\j))}}
  \function{rep=1/(\rep)}
}
\text{reptex=texmath(\rep)}
\text{name_intro=Soit \(n\) un entier}
\text{name_quest=Simplifier l'expression}

\statement{\name_intro \hyp.
<div class="wims_question">
  \name_quest \(\frac{(\num)!}{(\den)!}\). 
  <div class="wimscenter">
  <label for="reply1">\(\frac{(\num)!}{(\den)!}\)=</label>\embed{reply1}.
  </div>
</div>
}
\answer{}{\rep}{type=formal}

\latex{
\begin{statement}
 \name_intro \hyp.\newline
 \name_quest \(\frac{(\num)!}{(\den)!}\). 
\end{statement}
\begin{solution}
\(\frac{(\num)!}{(\den)!}=\reptex.\)
\end{solution}
}
#endif
