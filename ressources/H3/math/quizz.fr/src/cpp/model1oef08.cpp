target=0801 0802 0803 0804 0805 0806 0807 0808 0809 0810 0811 0812 0813 0814 0815 0816 0817 0818 0819 0820 0821 0822 0823 0824 0825 0826 0827 0828 0829 0830
\author{Bruno, Mifsud}
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


%%%%% variable LATEXVERSION : 1 : a une version latext; 0: n'a aps une version latex
#define VERSIONLATEX 1
#define ANSTYPE 0


#include "instruction.inc"

#if defined TARGET_0801
# include "0801.inc"
#endif
#if defined TARGET_0802
# include "0802.inc"
#endif
#if defined TARGET_0803
# include "0803.inc"
#endif
#if defined TARGET_0804
# include "0804.inc"
#endif
#if defined TARGET_0805
# include "0805.inc"
#endif
#if defined TARGET_0806
# include "0806.inc"
#endif
#if defined TARGET_0807
# include "0807.inc"
#endif
#if defined TARGET_0808
# include "0808.inc"
#endif
#if defined TARGET_0809
# include "0809.inc"
#define ANSTYPE 1
#endif
#if defined TARGET_0810
# include "0810.inc"
#endif
#if defined TARGET_0811
# include "0811.inc"
#endif
#if defined TARGET_0812
# include "0812.inc"
#define ANSTYPE 70
#endif
#if defined TARGET_0813
# include "0813.inc"
#endif
#if defined TARGET_0814
# include "0814.inc"
#endif
#if defined TARGET_0815
# include "0815.inc"
#endif
#if defined TARGET_0816
# include "0816.inc"
#endif
#if defined TARGET_0817
# include "0817.inc"
#endif
#if defined TARGET_0818
# include "0818.inc"
#endif
#if defined TARGET_0819
# include "0819.inc"
#endif
#if defined TARGET_0820
# include "0820.inc"
#endif
#if defined TARGET_0821
# include "0821.inc"
#endif
#if defined TARGET_0822
# include "0822.inc"
#endif
#if defined TARGET_0823
# include "0823.inc"
#endif
#if defined TARGET_0824
# include "0824.inc"
#define ANSTYPE 70
#endif
#if defined TARGET_0825
# include "0825.inc"
#endif
#if defined TARGET_0826
# include "0826.inc"
#endif
#if defined TARGET_0827
# include "0827.inc"
#endif
#if defined TARGET_0828
# include "0828.inc"
#define VERSIONLATEX 0
#define ANSTYPE 3
#endif
#if defined TARGET_0829
# include "0829.inc"
#endif
#if defined TARGET_0830
# include "0830.inc"
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
  \enonce \embed{r1,10
    autofocus} \enonceb</div>
}
#if ANSTYPE==0
\answer{}{\rep}{type=numeric}{option=comma default=0}
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
