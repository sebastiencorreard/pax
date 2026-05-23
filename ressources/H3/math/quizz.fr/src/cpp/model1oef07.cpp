target=0701 0702 0703 0704 0705 0706 0707 0708 0709 0710 0711 0712 0713 0714 0715 0716 0717 0718 0719 0720 0721 0722 0723 0724 0725 0726 0727 0728 0729 0730
\author{Bruno,Mifsud}
\email{communaute.mutuwims@laposte.net}
\observation{Le numéro de la question s'interprète comme suit : <br>Question XXYY est la question YY du niveau XX}
%%%%% variable ANSTYPE : 0 pour numéric (par défaut)
%%%%%%%%%%%%%%%%%%%%%%%% 1 pour menu {1;\rep,\bad1,\bad2}{type=menu}{option=shuffle default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 11 Pour Menu VRAI FAUX{\rep;VRAI,FAUX}{type=menu}{option=default=\bads[1]}
%%%%%%%%%%%%%%%%%%%%%%%% 12 pour menu {\rep;Figure 1,Figure 2, Figure 3}{type=menu}{option= default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 2 pour formal
%%%%%%%%%%%%%%%%%%%%%%%% 3 pour algexp
%%%%%%%%%%%%%%%%%%%%%%%% 30 pour litexp polyn factorisé  answer{}{\rep}{type=litexp}{option= polfactor default=0 weight=3}
%%%%%%%%%%%%%%%%%%%%%%%% 31 pour litexp polyn developpé  answer{}{\rep}{type=litexp}{option=\confparm2 polexpand default=0 weight=3}
%%%%%%%%%%%%%%%%%%%%%%%% 32 pour equation {\rep,x,y}
%%%%%%%%%%%%%%%%%%%%%%%% 4 pour click
%%%%%%%%%%%%%%%%%%%%%%%% 5 pour numexpFormat :{\rep}{type=numexp}{option=noreduction default=0}
%%%%%%%%%%%%%%%%%%%%%%%% 6 pour condition : %answer{}{\reponse}{type=fset}{option=default=0}
%%%%%%%%%%%%%%%%%%%%%%%%        %condition{\condtexte}{\cond}
%%%%%%%%%%%%%%%%%%%%%%%% 60 pour condition : %answer{}{\reponse}{type=numeric}
%%%%%%%%%%%%%%%%%%%%%%%%       %condition{}{\reponse issametext \rep}
%%%%%%%%%%%%%%%%%%%%%%%% 70 pour case {\rep}{type=case}
%%%%%%%%%%%%%%%%%%%%%%%% 7 pour nocase {\rep}{type=nocase}
%%%%%%%%%%%%%%%%%%%%%%%% 8 pour clickfill {\rep}{type=clickfill}{option=shuffle}
%%%%%%%%%%%%%%%%%%%%%%%% 9 pour fset {\rep}{type=fset}
%%%%%%%%%%%%%%%%%%%%%%%%       %condition{}{\reponse isitemof \rep}

%%%%% variable LATEXVERSION : 1 : a une version latext; 0: n'a pas une version latex
#define VERSIONLATEX 1
#define ANSTYPE 0
#include "instruction_cycle4.inc"

\integer{taille=6}

#if defined TARGET_0701
#include "0701.inc"
#endif
#if defined TARGET_0702
#include "0702.inc"
#endif
#if defined TARGET_0703
#include "0703.inc"
#endif
#if defined TARGET_0704
#include "0704.inc"
#endif
#if defined TARGET_0705
# include "0705.inc"
#endif
#if defined TARGET_0706
# include "0706.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0707
# include "0707.inc"
#endif
#if defined TARGET_0708
# include "0708.inc"
#endif
#if defined TARGET_0709
# include "0709.inc"
#define ANSTYPE 1
#endif
#if defined TARGET_0710
# include "0710.inc"
#endif
#if defined TARGET_0711
# include "0711.inc"
#endif
#if defined TARGET_0712
# include "0712.inc"
#endif
#if defined TARGET_0713
# include "0713.inc"
#endif
#if defined TARGET_0714
# include "0714.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0715
# include "0715.inc"
#endif
#if defined TARGET_0716
# include "0716.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0717
# include "0717.inc"
#endif
#if defined TARGET_0718
# include "0718.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0719
# include "0719.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0720
# include "0720.inc"
# define VERSIONLATEX 0
#endif
#if defined TARGET_0721
# include "0721.inc"
#endif
#if defined TARGET_0722
# include "0722.inc"
#endif
#if defined TARGET_0723
# include "0723.inc"
#endif
#if defined TARGET_0724
# include "0724.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0725
# include "0725.inc"
#endif
#if defined TARGET_0726
# include "0726.inc"
#endif
#if defined TARGET_0727
# include "0727.inc"
#endif
#if defined TARGET_0728
# include "0728.inc"
#endif
#if defined TARGET_0729
# include "0729.inc"
#endif
#if defined TARGET_0730
# include "0730.inc"
#define ANSTYPE 70
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
#if defined TARGET_0712
\embed{r2,\taille} \enoncec
#endif
  </div>
}
#if ANSTYPE==0
\answer{}{\rep}{type=numeric}{option=comma default=0}
#if defined TARGET_0712
\answer{}{\repb}{type=numeric}{option=comma default=0}
#endif

#endif
#if ANSTYPE==1
\answer{}{1;\rep,\bad1,\bad2}{type=menu}{option=shuffle default=\bad1 weight=2}
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
\answer{}{\rep}{type=equation}
#endif
#if ANSTYPE==6
\answer{}{\reponse}{type=fset}{option=default=0}
\condition{\condtexte}{\cond}
#endif
#if ANSTYPE==60
\answer{}{\reponse}{type=numeric}{option=default=0}
\condition{Bonne réponse ?}{\reponse issametext \rep}
#endif
#if ANSTYPE==7
\answer{}{\rep}{type=nocase}
#endif
#if ANSTYPE==70
\answer{}{\rep}{type=case}
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
