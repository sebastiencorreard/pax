target=calcden1 calcden1b calcden2 calcden3 calcden4 calcden5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{1000}
\keywords{combinatorics}
#define TITRE Calcul de dénombrement
#if defined TARGET_calcden1
# define NUM 1
#endif
#if defined TARGET_calcden1b
# define NUM 1 bis
#endif
#if defined TARGET_calcden2
# define NUM 2
#endif
#if defined TARGET_calcden3
# define NUM 3
#endif
#if defined TARGET_calcden4
# define NUM 4
#endif
#if defined TARGET_calcden5
# define NUM 5
#endif
\title{E. TITRE NUM}
#if defined TARGET_calcden1||defined TARGET_calcden1b
\description{Dénombrement d'entiers ayant des propriétés particulières}
\integer{p=randint(3..5)}
\integer{n=randint(\p..9)}
\text{liste=shuffle(1,2,3,4,5,6,7,8,9)}
\text{liste=item(1..\n,\liste)}
\text{liste=wims(sort list \liste)}
\integer{cmin=\liste[1]}
\integer{cmax=\liste[-1]}
\integer{idiv=randint(1,2)}
\text{critdiv=\idiv=1?pairs:multiples de 5}
\if{\idiv=1}{
  \text{lp=0,2,4,6,8}
  }{
  \text{lp=0,5}
  }
\text{cp=wims(listintersect \lp and \liste)}
\integer{j=items(\cp)}
\integer{cborne=randint(\cmin+1..\cmax-1)}
\integer{ib=randint(1,2)}
\integer{\borne=\cborne*10^(\p-1)}
\text{critborne=\ib=1?supérieurs à \borne:inférieurs à \borne}
\integer{nb=0}
\if{\ib=1}{
  \for{jb=1 to \n}{
    \integer{nb=\liste[\jb]>=\cborne?\nb+1}
    }
  }{
  \for{jb=1 to \n}{
    \integer{nb=\liste[\jb]<\cborne?\nb+1}
    }
  }
#endif
#if defined TARGET_calcden1
  \text{name_chiff=chiffres}
  \text{exnb1=\liste[1..\p-1]}
  \text{exnb1=shuffle(\exnb1, \exnb1[1])}
  \integer{rep1=\n^\p}
  \integer{rep2=(\n)^(\p-1)*\j}
  \integer{rep3=(\n)^(\p-1)*\nb}
#endif
  
#if defined TARGET_calcden1b 
  \text{name_chiff=chiffres distincts}
  \text{exnb1=\liste[1..\p]}
  \text{exnb1=shuffle(\exnb1)}
  \integer{rep1=(\n!)/((\n-\p)!)}
  \integer{rep2=((\n-1)!)/((\n-\p)!)*\j}
  \integer{rep3=((\n-1)!)/((\n-\p)!)*\nb}
#endif  
#if defined TARGET_calcden1||defined TARGET_calcden1b  
\text{exnb1=wims(replace internal , by in \exnb1)} 
\text{name_quest1=Combien de nombres de, peut-on former avec les chiffres}
\text{name_quest2=Parmi ces nombres,combien sont}
\text{name_ex=Exemple}
\text{name_ind=est un nombre formé de} 
\text{name_sol1=On peut former \rep1 nombres de \(\p\) \name_chiff avec les chiffres \liste.}
\text{name_sol2=\name_quest2[1], \rep2 sont \critdiv et \rep3 sont \critborne.}
/* pour la version latex*/
\text{enonce1=\name_quest1[1] \p \name_chiff  \name_quest1[2] \liste}
\text{latexenonce2=\name_quest2[1] \begin{itemize} \item \name_quest2[2] \critdiv}
\text{latexenonce3= \item \name_quest2[2] \critborne}
\statement{
<div class="wims_question">
<ul class="wims_nopuce">
 <li><label for="reply1">  
 \name_quest1[1] \p \name_chiff  \name_quest1[2] \liste ?</label>
 \embed{reply1,6} </li>
 <li> \name_quest2[1],
 <ul class="spacer">
  <li><label for="reply2">\name_quest2[2] \critdiv ?</label>
  \embed{reply2,6}
  </li><li><label for="reply3">\name_quest2[2] \critborne ?</label>
  \embed{reply3,6} 
  </li>
  </ul>
</ul>
</div>
}
\answer{question 1}{\rep1}{type=numexp}
\answer{question 2}{\rep2}{type=numexp}
\answer{question 3}{\rep3}{type=numexp}
\hint{\name_ex : \exnb1 \name_ind \p \name_chiff. }
\solution{\name_sol1<br/> \name_sol2}
\latex{
\begin{statement}
\enonce1 ?\newline
\latexenonce2 ?
\latexenonce3 ?
\end{itemize}
\end{statement}
\begin{solution}
\name_sol1\newline \name_sol2
\end{solution}
}
#endif

#if defined TARGET_calcden2
\description{Dénombrement des anagrammes d'un mot}
\text{lstmots=SPORT,5
TABLE,5
COURSE,6
DEPART,6
ROUGE,5
TRAIN,5
LECON,5
JOIE,4
SURF,4
VIRUS,5
ESPOIR,6
CRISTAL,7
}
\text{cemots=randomrow(\lstmots)}
\text{mots=\cemots[1]}
\integer{ns=\cemots[2]!}
\text{nsols=texmath(\cemots[2]!)}
\integer{nliste=\cemots[2]^\cemots[2]}

\text{lstmotd=TASSE,5!,2,il y une lettre en double
TOIT,4!,2, il y a une lettre en double
SPORTS,6!,2, il y a une lettre en double
PARABOLE,8!,2, il y a une lettre en double
COUCOU,6!,(2!*2!*2!), il y a trois lettres en double
ARTISTES, 8!,(2!*2!), il y a deux lettres en double
BALLE,5!,2,il y a une lettre en double
IRIS,4!,2!,il y a une lettre en double 
MEDECIN,7!,2!, il y a une lettre en double 
VACCIN,6!,2!,il y a une lettre en double 
ENTETE,6!,(3!*2!), il y a une lettre en double et une lettre en triple
ACACIA, 6!,(3!*2!), il y a une lettre en double et une lettre en triple
RASSURER, 8!,(3!*2!),il y a une lettre en double et une lettre en triple
MALARIA, 7!,3!, il y a une lettre en triple
MANGA,5!,2!, il y a une lettre en double 
EXEMPLE,7!,3!, il y a une lettre en triple
AVATAR,6!,3!, il y a une lettre en triple 
TERROIR,7!,3!,il y a une lettre en triple
}
\text{cemotd=randomrow(\lstmotd)}
\text{motd=\cemotd[1]}
\integer{nd=\cemotd[2]/\cemotd[3]}
\text{nsold=texmath(\cemotd[2])}
integer{i=randint(1,2)}
\integer{i=1}
\if{\i=1}{
 \text{mot1=\mots}
 \integer{rep1=\ns}
 \text{nsol1=\nsols}
 \text{mot2=\motd}
 \integer{rep2=\nd}
 \text{nsol2=\nsold}
 \text{raison1=car il y a \cemots[2] lettres distinctes}
 \text{raison2=car \cemotd[4]}
}
\if{\i=2}{
 \text{mot2=\mots}
 \integer{rep2=\ns}
 \text{nsol2=\nsols}
 \text{mot1=\motd}
 \integer{rep1=\nd}
 \text{nsol1=\nsold}
 \text{raison2=car il y a \cemots[2] lettres distinctes}
 \text{raison1=car \cemotd[4]}
}
\text{name_quest= De combien de façons différentes peut-on ordonner les lettres du mot} 
\text{name_il=il y a}
\text{name_sol=façons différentes d'ordonner les lettres du mot}
\text{name_sol1=Le mot \mot1 comporte \cemots[2] lettres toutes différentes, on peut donc 
voir une suite constituée avec les lettres de ce mot comme une permutation d'un ensemble ayant  \cemots[2]  éléments.}
\text{name_sol2=Si on distingue les lettres qui apparaissent plusieurs fois dans \mot2 en leur ajoutant un numéro, 
il y aurait \(\cemotd[2]\) façons différentes d'ordonner 
les lettres de ce mot. Il suffit ensuite de déterminer combien de fois  on peut changer l'ordre des numéros des  lettres 
qui sont en plusieurs exemplaires, pour savoir combien de suites sont réellement différentes si on oublie les numéros attribués 
à certaines lettres. }
\text{name_donc=Donc}
\steps{reply1
reply2}
\statement{<ol>
<li>
\if{\step=1}{<label for="reply1">\name_quest \mot1 ?</label>
 \embed{reply1,7}
 }{\name_quest \mot1 ? <span class="oef_indgood">\reply1</span>}
</li>\if{\step>=2}{<li>
<label for="reply2">\name_quest  \mot2 ?</label>  \embed{reply2,7}
</li>}
</ol>
}
\answer{\mot1}{\rep1}{type=numexp}
\answer{\mot2}{\rep2}{type=numexp}

\feedback{\reply1 <\rep1}{Il y a plus de façons différentes d'ordonner les  \cemots[2] lettres de ce mot.}
\feedback{\reply1 =\nliste}{Le nombre que vous avez donné correspond au nombre de suite de lettres que l'on peut 
constituer si on disposait d'autant d'exemplaires des lettres du mot \mot1 que nécessaire.}
\feedback{\sc_reply1=1 and \sc_reply2 < 1}{A la différence du \mot1, remarquez que certaines  lettres du mot \mot2 apparaissent plusieurs fois.}

\solution{<b>Indications</b>
<p>\name_sol1 </p>
\if{\sc_reply1=1}{<p>\name_sol2</p>  }
}
\latex{
\begin{statement}
\begin{enumerate}
\item \name_quest \mot1 ? 
\item \name_quest \mot2 ? 
\end{enumerate}
\end{statement}
\begin{solution}
\begin{enumerate}
\item \name_sol1 \name_donc, \name_il \rep1 \name_sol \mot1.
\item \name_sol2 \name_donc, \name_il \rep2 \name_sol \mot2.
\end{enumerate}
\end{solution}
}
#endif

#if defined TARGET_calcden3||defined TARGET_calcden4||defined TARGET_calcden5
\description{Dénombrement pour trois types de tirages}
\text{name_enonce=Dans chacun des cas suivants, dénombrer les façons de tirer}
\text{name_context=Une urne contient,  indiscernables au toucher numérotées de 1 à}
\text{quest=successivement et avec remise,successivement et sans remise,simultanément}
\text{name_boule=boules}
\text{name_feed=Il y a,  façons de tirer, dans cette urne}
#endif
#if defined TARGET_calcden4||defined TARGET_calcden5
\text{name_coul=boules noires, boules blanches}
\text{name_ind=On est dans la même situation que si on avait}
\text{name_and=et}
#endif
#if defined TARGET_calcden3
\integer{n=randint(10..20)}
\integer{p=randint(2..5)}
\integer{cnp=binomial(\n,\p)}
\integer{anp=pari((\n!)/((\n-\p)!))}
\integer{pownp=\n^\p}
\text{rep=\pownp,\anp,\cnp}
\text{tfeed=\(\n^\p\),\(\frac{\n!}{(\n-\p)!}\),\(\frac{\n!}{\p!(\n-\p)!}\)}
\text{ind=shuffle(3)}
\text{context= \name_context[1] \n \name_boule \name_context[2]  \n.}

#endif

#if defined TARGET_calcden4
\integer{n1=randint(5..10)}
\integer{n=2*\n1}
\integer{p=randint(2..5)}

\integer{cnp=binomial(\n,\p)}
\text{rep=pari(\n^\p),pari((\n!)/((\n-\p)!)),\cnp}
\text{ind=shuffle(3)}
\text{context=\name_context[1] \n1 \name_coul[1] \name_context[2] \n1 \name_and \n1
  \name_coul[2] \name_context[2] \n1.}
#endif

#if defined TARGET_calcden5
\integer{n1=randint(5..10)}
\integer{n2=randint(5..10)}
\integer{n=\n1+\n2}
\integer{p=randint(2..5)}

\integer{cnp=binomial(\n,\p)}
\text{rep=pari(\n^\p),pari((\n!)/((\n-\p)!)),\cnp}
\text{ind=shuffle(3)}
\text{context=\name_context[1] \n1 \name_coul[1] \name_context[2] \n1
  \name_and \n2 \name_coul[2] \name_context[2] \n2.}
#endif  
#if defined TARGET_calcden3||defined TARGET_calcden4||defined TARGET_calcden5 
/*pour la version latex*/
\text{latexquest=\begin{enumerate}
 \item \quest[\ind[1]] 
 \item \quest[\ind[2]] 
 \item \quest[\ind[3]] 
 \end{enumerate} }
 \text{latexans=\name_feed[1] \begin{enumerate} 
 \item \rep[\ind[1]] \name_feed[2] \quest[\ind[1]] \p \name_boule \name_feed[3]. 
 \item \rep[\ind[2]] \name_feed[2] \quest[\ind[2]] \p \name_boule \name_feed[3]. 
 \item \rep[\ind[3]] \name_feed[2] \quest[\ind[3]] \p \name_boule \name_feed[3]. 
 \end{enumerate} }
 
\statement{
 \context
<div class="wims_question">
  \name_enonce \p \name_boule 
<ol class="spacer">
<li><label for="reply1">\quest[\ind[1]] :</label> \embed{reply1,7}</li>
<li><label for="reply2">\quest[\ind[2]] :</label> \embed{reply2,7}</li>
<li><label for="reply3">\quest[\ind[3]] :</label>\embed{reply3,7}</li>
</ol>
</div>
}
\answer{\quest[\ind[1]]}{\rep[\ind[1]]}{type=numexp}
\answer{\quest[\ind[2]]}{\rep[\ind[2]]}{type=numexp}
\answer{\quest[\ind[3]]}{\rep[\ind[3]]}{type=numexp}
\latex{
\begin{statement}
 \context\newline
 \name_enonce \p \name_boule 
 \latexquest
\end{statement}
\begin{solution}
\latexans
\end{solution}
}
#endif
#if defined TARGET_calcden3
\feedback{\sc_reply1 < 1}{<div>\name_feed[1] \tfeed[\ind[1]] \name_feed[2] \p \name_boule  \quest[\ind[1]] \name_feed[3].</div>}
\feedback{\sc_reply2 < 1}{<div>\name_feed[1] \tfeed[\ind[2]] \name_feed[2] \p \name_boule  \quest[\ind[2]] \name_feed[3].</div>}
\feedback{\sc_reply3 < 1}{<div>\name_feed[1] \tfeed[\ind[3]] \name_feed[2] \p \name_boule  \quest[\ind[3]] \name_feed[3].</div>}
#endif
#if defined TARGET_calcden4||defined TARGET_calcden5
\solution{\name_ind \n \name_boule \name_context[2] \n.}
#endif
