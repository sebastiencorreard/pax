target=conddef1 conddef2 conddef3
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\precision{199}
\format{html}
\description{Pour se familiariser avec la définition de probabilité conditionnelle}
#define TITRE Probabilité conditionnelle : définition
#if defined TARGET_conddef1
# define NUM 1
#endif
#if defined TARGET_conddef2
# define NUM 2
#endif
#if defined TARGET_conddef3
# define NUM 3
#endif
\title{G. TITRE NUM}
#if defined TARGET_conddef1||TARGET_conddef2
\keywords{conditional_probability,independent_events}
\real{pA=randint(10..80)/100}
\real{pB=randint(10..80)/100}
\real{pC=\pB-randint(1..9)/100}
\integer{cas=randint(1,2)}
\integer{ind=randint(1,2)}
\text{quest=\cas=1?\(P_B(A)\):\(P_A(B)\)}
\text{name_enonce= On considère deux événements \(A\) et \(B\).}
\text{name_hyp= On connaît les probabilités suivantes}

\text{name_quest1=Calculer}
\text{name_quest2=Les événements \(A\) et \(B\) sont-ils indépendants }
\text{name_indep=Indépendance de \(A\) et \(B\)}
\text{name_choix=Oui,Non}
\text{latexradio=\begin{radio}\item \name_choix[1] \item \name_choix[2]\end{radio}}
\text{latexans=\name_choix[\ind]}
#endif
#if defined TARGET_conddef1
\real{pAnB=\ind=1?\pA*\pB:\pA*\pC}
\real{rep=\cas=1?\pAnB/\pB:\pAnB/\pA}
\real{reparr=round(100*\rep)/100}
\if{\rep=\reparr}{\text{sol=\(=\rep\)}}{\text{sol=\(\simeq \reparr\)}}
\text{name_consig=Donner le résultat avec au moins 2 chiffres significatifs.}
\text{hyp3=\(P(A\cap B)=\pAnB\).}
#endif
#if defined TARGET_conddef2
\text{info=\cas=2?P_B(A):P_A(B)}
\real{pAnB=\ind=1?\pA*\pB:\pA*\pC}
\real{pdata=\cas=2?\pAnB/\pB:\pAnB/\pA}
\real{pdata=round(\pdata*100)/100}
\real{rep=\cas=1?\pdata*\pA/\pB:\pdata*\pB/\pA}
\real{reparr=round(\rep*100)/100}
\if{\rep=\reparr}{\text{sol=\(=\rep\)}}{\text{sol=\(\simeq \reparr\)}}
\text{name_consig=Arrondir à \(10^{-2}\).}
\text{hyp3=\(\info=\pdata\).}
#endif
#if defined TARGET_conddef1||TARGET_conddef2
\statement{
  \name_enonce \name_hyp :
<ul class="inline">
<li class="spacer">
 \(P(A)=\pA\)
</li><li class="spacer">
 \(P(B)=\pB\)
</li><li class="spacer">
\hyp3
</li></ul>
<div class="wims_question">
<ol>
<li>\name_quest1 \quest : 
<div class="wimscenter"><label for="reply1">\quest = </label>\embed{reply1,5}</div>
<div class="wims_instruction">\name_consig</div>
</li><li>\name_quest2 ?
\embed{reply2}</li>
</ol>
</div>
}
\latex{
\begin{statement}
\name_enonce \name_hyp : 
\[P(A)=\pA\quad P(B)=\pB \text{ et }P(A\cap B)=\pAnB.\]
\begin{enumerate}
 \item \name_quest1 \quest (\emph{\small \name_consig})
 \item \name_quest2 ? \latexradio
\end{enumerate} 
\end{statement}
\begin{solution}
\begin{enumerate}
 \item \quest \sol.
 \item \name_quest2 ? \latexans
\end{enumerate}  
\end{solution}
}
#endif
#if defined TARGET_conddef1
\answer{\quest}{\reparr}{type=numeric}{option=absolute noanalyzeprint}
\answer{\name_indep}{\ind;\name_choix}{type=radio}
\feedback{1=1}{\quest \sol. }
#endif
#if defined TARGET_conddef2
\answer{\quest}{\reparr}{type=numeric}{option=absolute}
\answer{\name_indep}{\ind;\name_choix}{type=radio}
#endif

#if defined TARGET_conddef3
\keywords{conditional_probability}
\observation{cas où A est inclus dans B ou l'inverse}
\integer{casinc=randint(1,2)}
\text{inclu=\casinc=1?\(A \subset B\):\(B \subset A\)}
\integer{cas=randint(1,2)}
\text{quest=\cas=1?\(P_B(A)\):\(P_A(B)\)}
\if{\casinc=1}{
  \text{rep=\cas=1?P(A)/P(B):1}
  }{
  \text{rep=\cas=2?P(B)/P(A):1}
}
\text{name_enonce= On considère deux événements \(A\) et \(B\) de probabilité non nulle, tels que}
\text{name_quest=Exprimer}
\text{name_instr=en fonction de \(P(A)\) et de \(P(B)\)}
\statement{\name_enonce
\inclu.
<div class="wims_question">
  \name_quest \quest \name_instr :
<div class="wimscenter"><label for="reply1">\quest =</label> \embed{reply1,10}.</div>
</div>
}
\answer{ \quest}{\rep}{type=formal}
\latex{
\begin{statement}
\name_enonce \inclu.\newline
 \name_quest \quest \name_instr.
\end{statement}
\begin{solution}
\quest = \rep
\end{solution}
}
#endif
