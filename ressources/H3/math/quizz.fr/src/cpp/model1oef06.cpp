target=0601 0602 0603 0604 0605 0606 0607 0608 0609 0610 0611 0612 0613 0614 0615 0616 0617 0618 0619 0620 0621 0622 0623 0624 0625 0626 0627 0628 0629 0630
\author{Bruno,Mifsud}
\email{communaute.mutuwims@laposte.net}
\observation{Le numéro de la question s'interprète comme suit : <br>Question XXYY est la question YY du niveau XX}
%%%%% variable ANSTYPE : 0 pour numéric (par défaut)
%%%%%%%%%%%%%%%%%%%%%%%% 1 pour menu {1;\rep,\bad1,\bad2}{type=menu}{option=shuffle default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 11 Pour Menu VRAI FAUX{\rep;VRAI,FAUX}{type=menu}{option=default=\bads[1]}
%%%%%%%%%%%%%%%%%%%%%%%% 12 pour menu {\rep;Figure 1,Figure 2, Figure 3}{type=menu}{option= default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 13 pour checkbox {\rep;\prop}{type=checkbox}
%%%%%%%%%%%%%%%%%%%%%%%% 14 pour mark {\rep;\prop}{type=mark}
%%%%%%%%%%%%%%%%%%%%%%%% 2 pour formal
%%%%%%%%%%%%%%%%%%%%%%%% 3 pour algexp
%%%%%%%%%%%%%%%%%%%%%%%% 4 pour click
%%%%%%%%%%%%%%%%%%%%%%%% 5 pour numexpFormat :{\rep}{type=numexp}{option=noreduction default=0}
%%%%%%%%%%%%%%%%%%%%%%%% 6 pour condition : %answer{}{\reponse}{type=numeric}
%%%%%%%%%%%%%%%%%%%%%%%%       %condition{}{\reponse isitemof \rep}

%%%%% variable LATEXVERSION : 1 : a une version latext; 0: n'a pas une version latex
#define VERSIONLATEX 1
#define ANSTYPE 0
#include "instruction_cycle4.inc"

\integer{taille=6}

#if defined TARGET_0601
# include "0601.inc"
#endif
#if defined TARGET_0602
# include "0602.inc"
#endif
#if defined TARGET_0603
# include "0603.inc"
#endif
#if defined TARGET_0604
# include "0604.inc"
#endif
#if defined TARGET_0605
# include "0605.inc"
#endif
#if defined TARGET_0606
# include "0606.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0607
# include "0607.inc"
#endif
#if defined TARGET_0608
# include "0608.inc"
#define ANSTYPE 13
#define VERSIONLATEX 0
#endif
#if defined TARGET_0609
# include "0609.inc"
#endif
#if defined TARGET_0610
# include "0610.inc"
#endif
#if defined TARGET_0611
# include "0611.inc"
#endif
#if defined TARGET_0612
# include "0612.inc"
#define VERSIONLATEX 0
\integer{taille=4}
#endif
#if defined TARGET_0613
# include "0613.inc"
#endif
#if defined TARGET_0614
# include "0614.inc"
#define VERSIONLATEX 0
\integer{taille=4}
#endif
#if defined TARGET_0615
# include "0615.inc"
#endif
#if defined TARGET_0616
# include "0616.inc"
#endif
#if defined TARGET_0617
# include "0617.inc"
#endif
#if defined TARGET_0618
# include "0618.inc"
#endif
#if defined TARGET_0619
# include "0619.inc"
#endif
#if defined TARGET_0620
# include "0620.inc"
# define VERSIONLATEX 0
#endif
#if defined TARGET_0621
# include "0621.inc"
#endif
#if defined TARGET_0622
# include "0622.inc"
#endif
#if defined TARGET_0623
# include "0623.inc"
#endif
#if defined TARGET_0624
# include "0624.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0625
# include "0625.inc"
# define VERSIONLATEX 0
#endif
#if defined TARGET_0626
# include "0626.inc"
#define ANSTYPE 14
#define VERSIONLATEX 0
#endif
#if defined TARGET_0627
# include "0627.inc"
#endif
#if defined TARGET_0628
# include "0628.inc"
#endif
#if defined TARGET_0629
# include "0629.inc"
#endif
#if defined TARGET_0630
# include "0630.inc"
# define VERSIONLATEX 0
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
  \enonce \embed{r1,\taille
    autofocus} \enonceb
#if (defined TARGET_0612||defined TARGET_0614)
\embed{r2,\taille} \enoncec
#endif
  </div>
}
#if ANSTYPE==0
\answer{}{\rep}{type=numeric}{option=comma default=0}
#if (defined TARGET_0612||defined TARGET_0614)
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
