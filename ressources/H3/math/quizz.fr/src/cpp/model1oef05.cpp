target=0501 0502 0503 0504 0505 0506 0507 0508 0509 0510 0511 0512 0513 0514 0515 0516 0517 0518 0519 0520 0521 0522 0523 0524 0525 0526 0527 0528 0529 0530
\author{Bruno,Mifsud}
\email{communaute.mutuwims@laposte.net}
\observation{Le numéro de la question s'interprète comme suit : <br>Question XXYY est la question YY du niveau XX}
%%%%% variable ANSTYPE : 0 pour numéric (par défaut)
%%%%%%%%%%%%%%%%%%%%%%%% 1 pour menu {1;\rep,\bad1,\bad2}{type=menu}{option=shuffle default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 11 Pour Menu VRAI FAUX{\rep;VRAI,FAUX}{type=menu}{option=default=\bads[1]}
%%%%%%%%%%%%%%%%%%%%%%%% 12 pour menu {\rep;Figure 1,Figure 2, Figure 3}{type=menu}{option= default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 13 pour checkbox {\rep;\prop}{type=checkbox}
%%%%%%%%%%%%%%%%%%%%%%%% 2 pour formal
%%%%%%%%%%%%%%%%%%%%%%%% 3 pour algexp
%%%%%%%%%%%%%%%%%%%%%%%% 30 pour litexp polyn factorisé  answer{}{\rep}{type=litexp}{option= polfactor default=0 weight=3}
%%%%%%%%%%%%%%%%%%%%%%%% 31 pour litexp polyn developpé  answer{}{\rep}{type=litexp}{option=\confparm2 polexpand default=0 weight=3}
%%%%%%%%%%%%%%%%%%%%%%%% 32 pour equations {\rep,x,y}
%%%%%%%%%%%%%%%%%%%%%%%% 4 pour click
%%%%%%%%%%%%%%%%%%%%%%%% 5 pour numexpFormat :{\rep}{type=numexp}{option=noreduction default=0}
%%%%%%%%%%%%%%%%%%%%%%%% 6 pour condition : %answer{}{\reponse}{type=numeric}
%%%%%%%%%%%%%%%%%%%%%%%%       %condition{}{\cond}
%%%%%%%%%%%%%%%%%%%%%%%% 7 pour nocase {\rep}{type=nocase}
%%%%%%%%%%%%%%%%%%%%%%%% 8 pour clickfill {\rep}{type=clickfill}{option=shuffle}
%%%%%%%%%%%%%%%%%%%%%%%% 9 pour fset {\rep}{type=fset}
%%%%%%%%%%%%%%%%%%%%%%%% 41 pour jsxgraph answer{Construction}{\sol}{type=jsxgraph}{option=noanalyzeprint}

%%%%% variable LATEXVERSION : 1 : a une version latext; 0: n'a aps une version latex
#define VERSIONLATEX 1


#define ANSTYPE 0

#include "instruction_cycle4.inc"

#if defined TARGET_0501
# include "0501.inc"
#endif
#if defined TARGET_0502
# include "0502.inc"
#endif
#if defined TARGET_0503
# include "0503.inc"
#define ANSTYPE 3
#endif
#if defined TARGET_0504
# include "0504.inc"
#endif
#if defined TARGET_0505
# include "0505.inc"
#endif
#if defined TARGET_0506
# include "0506.inc"
#endif
#if defined TARGET_0507
# include "0507.inc"
#endif
#if defined TARGET_0508
# include "0508.inc"
#define ANSTYPE 13
#define VERSIONLATEX 0
#endif
#if defined TARGET_0509
# include "0509.inc"
#endif
#if defined TARGET_0510
# include "0510.inc"
#endif
#if defined TARGET_0511
# include "0511.inc"
#endif
#if defined TARGET_0512
# include "0512.inc"
#define ANSTYPE 6
#endif
#if defined TARGET_0513
# include "0513.inc"
#endif
#if defined TARGET_0514
# include "0514.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0515
# include "0515.inc"
#endif
#if defined TARGET_0516
# include "0516.inc"
#endif
#if defined TARGET_0517
# include "0517.inc"
#endif
#if defined TARGET_0518
# include "0518.inc"
#endif
#if defined TARGET_0519
# include "0519.inc"
#endif
#if defined TARGET_0520
# include "0520.inc"
#define ANSTYPE 41
#define VERSIONLATEX 0
#endif
#if defined TARGET_0521
# include "0521.inc"
#endif
#if defined TARGET_0522
# include "0522.inc"
#endif
#if defined TARGET_0523
# include "0523.inc"
#endif
#if defined TARGET_0524
# include "0524.inc"
#endif
#if defined TARGET_0525
# include "0525.inc"
#endif
#if defined TARGET_0526
# include "0526.inc"
#define ANSTYPE 14
#define VERSIONLATEX 0
#endif
#if defined TARGET_0527
# include "0527.inc"
#endif
#if defined TARGET_0528
# include "0528.inc"
#endif
#if defined TARGET_0529
# include "0529.inc"
#endif
#if defined TARGET_0530
# include "0530.inc"
#endif
%%% version latex %%%%
#if VERSIONLATEX==1 
\text{latexversion=\begin{enumerate}}
#if ANSTYPE==0
\text{latexversion=\latexversion
    \item
    \enonce
    \dots \enonceb
  }
#endif
#if ANSTYPE==1
\text{latexversion=\latexversion
    \item
    \enonce
    \begin{radio}
    \item \rep
    \item \bad1
    \item \bad2
    \end{radio}}
#endif
\text{latexversion=\latexversion \end{enumerate}}
#endif
%%%%%%%%%%%%%%%%%%%%%%%%%%%%% fin version latex %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\statement{
\if{\instruction!=}{
<div class="wims_instruction">\instruction</div>
}
<div class="wims_question">
#if defined TARGET_0520
\enonce
<div>
\embed{r1,400x200
id1 brd [responsive center min=250px max=400px scroll]
\jsxscript
}

</div>
#else
  \enonce \embed{r1,10
    autofocus} \enonceb
#if defined TARGET_0512
 et \embed{r2,10} \enoncec
#endif  
#if defined TARGET_0514
 et \embed{r2,10} \enoncec
#endif 
#endif
  </div>
}
#if ANSTYPE==0
\answer{}{\rep}{type=numeric}{option=comma default=0}
#if defined TARGET_0514
\answer{}{\repb}{type=numeric}{option=comma default=0}
#endif
#endif

#if ANSTYPE==1
\answer{}{1;\rep,\bad1,\bad2}{type=menu}{option=shuffle default=\bad1 weight=2}
#endif
#if ANSTYPE==13
\answer{}{\rep;\prop}{type=checkbox}
#endif
#if ANSTYPE==14
\answer{}{\rep;\prop}{type=mark}
#endif
#if ANSTYPE==2
\answer{}{\rep}{type=formal}{option=comma default=0}
#endif
#if ANSTYPE==3
\answer{}{\rep}{type=algexp}{option=comma default=0}
#endif
#if ANSTYPE==30
\answer{}{\rep}{type=litexp}{option=polfactor default=0}
#endif
#if ANSTYPE==31
\answer{}{\rep}{type=litexp}{option=polexpand default=0}
#endif
#if ANSTYPE==32
\answer{}{\rep}{type=equations}
#endif
#if ANSTYPE==41
\answer{Construction}{\sol0420}{type=jsxgraph}{option=noanalyzeprint}
#endif
#if ANSTYPE==6 && TARGET_0512
\answer{}{\reponse1}{type=numeric}{option=defaut=0}
\answer{}{\reponse2}{type=numeric}{option=defaut=0}
\condition{Bonnes réponses ?}{(\reponse1=\a0512/\b0512) and (\reponse2=\a0512/\b0512) and (\reponse1 notsametext \a0512/\b0512) and (\reponse2 notsametext \a0512/\b0512) and (\reponse1 notsametext \reponse2)}
#endif
#if ANSTYPE==7
\answer{}{\rep}{type=nocase}
#endif
#if ANSTYPE==8
\answer{}{\rep}{type=clickfill}{option=shuffle}
#endif
#if ANSTYPE==9
\answer{}{\rep}{type=fset}
#endif
\feedback{(\sc_reply1<1) and (\feedback!=)}{<style>.feedmutu {
    border: 1px solid;
    border-radius: 5px;
    padding: .5em;}
</style>
  <div class="feedmutu">\feedback</div>}


#if VERSIONLATEX==1
\latex{
\begin{statement}
\latexversion
\end{statement}
\begin{solution}
\end{solution}
}
#endif
