target=T1101 T1102 T1103 T1104 T1105 T1106 T1107 T1108 T1109 T1110 T1111 T1112 T1113 T1114 T1115 T1116 T1117 T1119 T1120 T1121 T1122 T1123 T1124 T1125 T1127 T1128 T1129 T1130
\author{Cyrille,Douriez}
\email{cyrille.douriez@ac-amiens.fr}
\observation{Course 1er Technologique. Le numéro de la question s'interprète comme suit : <br>Question XXYY est la question YY du niveau XX}
%%%%% variable ANSTYPE : 0 pour numéric (par défaut)
%%%%%%%%%%%%%%%%%%%%%%%% 1 pour menu {1;\rep,\bad1,\bad2}{type=menu}{option=shuffle default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 11 Pour Menu VRAI FAUX{\rep;VRAI,FAUX}{type=menu}{option=default=\bads[1]}
%%%%%%%%%%%%%%%%%%%%%%%% 12 pour menu {\rep;Figure 1,Figure 2, Figure 3}{type=menu}{option= default=\bad1}
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


%%%%% variable LATEXVERSION : 1 : a une version latext; 0: n'a pas une version latex
#define VERSIONLATEX 1


#define ANSTYPE 0
#include "instruction.inc"
\integer{size=10}

#if defined TARGET_T1101
# include "T1101.inc"
#endif
#if defined TARGET_T1102
# include "T1102.inc"
#endif
#if defined TARGET_T1103
# include "T1103.inc"
#define ANSTYPE 3
#endif
#if defined TARGET_T1104
# include "T1104.inc"
#endif
#if defined TARGET_T1105
# include "T1105.inc"
#endif
#if defined TARGET_T1106
# include "T1106.inc"
#endif
#if defined TARGET_T1107
# include "T1107.inc"
#endif
#if defined TARGET_T1108
# include "T1108.inc"
#endif
#if defined TARGET_T1109
# include "T1109.inc"
#endif
#if defined TARGET_T1110
# include "T1110.inc"
#define ANSTYPE 30
#endif
#if defined TARGET_T1111
# include "T1111.inc"
#endif
#if defined TARGET_T1112
# include "T1112.inc"
#endif
#if defined TARGET_T1113
# include "T1113.inc"
#endif
#if defined TARGET_T1114
# include "T1114.inc"
#define LATEXVERSION 0
#define ANSTYPE 2
#endif
#if defined TARGET_T1115
# include "T1115.inc"
#define LATEXVERSION 0
#endif
#if defined TARGET_T1116
# include "T1116.inc"
#define VERSIONLATEX 0
#define ANSTYPE 9
#endif
#if defined TARGET_T1117
# include "T1117.inc"
#define ANSTYPE 8
#define VERSIONLATEX 0
#endif
#if defined TARGET_T1118
# include "T1118.inc"
#define ANSTYPE 32
#define VERSIONLATEX 0
#endif
#if defined TARGET_T1119
# include "T1119.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_T1120
# include "T1120.inc"
# define ANSTYPE 3
#endif
#if defined TARGET_T1121
# include "T1121.inc"
# define ANSTYPE 8
#endif
#if defined TARGET_T1122
# include "T1122.inc"
#endif
#if defined TARGET_T1123
# include "T1123.inc"
#endif
#if defined TARGET_T1124
# include "T1124.inc"
# define ANSTYPE 9
#endif
#if defined TARGET_T1125
# include "T1125.inc"
#define ANSTYPE 7
#endif
#if defined TARGET_T1126
# include "T1126.inc"
#endif
#if defined TARGET_T1127
# include "T1127.inc"
#define ANSTYPE 2
#endif
#if defined TARGET_T1128
# include "T1128.inc"
#endif
#if defined TARGET_T1129
# include "T1129.inc"
#endif
#if defined TARGET_T1130
# include "T1130.inc"
#define ANSTYPE 2
#define VERSIONLATEX 0
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
  \enonce \embed{r1,\size
    autofocus} \enonceb
#if defined TARGET_T1129
\embed{r2,\size} \enoncec
#endif
  </div>
}
#if ANSTYPE==0
\answer{}{\rep}{type=numeric}{option=comma default=0}
#if defined TARGET_T1129
\answer{}{\repb}{type=numeric}{option=comma default=0 weight=3}
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
\answer{}{\rep}{type=equations}
#endif
#if ANSTYPE==6
\answer{}{\reponse}{type=fset}{option=default=0}
\condition{\condtexte}{\cond}
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
