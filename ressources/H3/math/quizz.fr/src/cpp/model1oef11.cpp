target=1101 1102 1103 1104 1105 1106 1107 1108 1109 1110 1111 1112 1113 1114 1115 1116 1117 1118 1119 1120 1121 1122 1123 1124 1125 1126 1127 1128 1129 1130
\author{Bruno,Mifsud}
\email{communaute.mutuwims@laposte.net}
\observation{Le numéro de la question s'interprète comme suit : <br>Question XXYY est la question YY du niveau XX}
%%%%% variable ANSTYPE : 0 pour numéric (par défaut)
%%%%%%%%%%%%%%%%%%%%%%%% 1 pour menu {1;\rep,\bad1,\bad2}{type=menu}{option=shuffle default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 11 Pour Menu VRAI FAUX{\rep;VRAI,FAUX}{type=menu}{option=default=\bads[1]}
%%%%%%%%%%%%%%%%%%%%%%%% 12 pour menu {\rep;Figure 1,Figure 2, Figure 3}{type=menu}{option= default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 2 pour formal
%%%%%%%%%%%%%%%%%%%%%%%% 3 pour algexp
%%%%%%%%%%%%%%%%%%%%%%%% 4 pour click
%%%%%%%%%%%%%%%%%%%%%%%% 5 pour numexpFormat :{\rep}{type=numexp}{option=noreduction default=0}
%%%%%%%%%%%%%%%%%%%%%%%% 6 pour condition : %answer{}{\reponse}{type=numeric}
%%%%%%%%%%%%%%%%%%%%%%%%       %condition{}{\reponse isitemof \rep}

%%%%% variable LATEXVERSION : 1 : a une version latext; 0: n'a pas une version latex
#define VERSIONLATEX 1


#define ANSTYPE 0

#include "instruction.inc"

#if defined TARGET_1101
# include "1101.inc"
#endif
#if defined TARGET_1102
# include "1102.inc"
#endif
#if defined TARGET_1103
# include "1103.inc"
#define ANSTYPE 3
#endif
#if defined TARGET_1104
# include "1104.inc"
#endif
#if defined TARGET_1105
# include "1105.inc"
#endif
#if defined TARGET_1106
# include "1106.inc"
#endif
#if defined TARGET_1107
# include "1107.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1108
# include "1108.inc"
#endif
#if defined TARGET_1109
# include "1109.inc"
#endif
#if defined TARGET_1110
# include "1110.inc"
#endif
#if defined TARGET_1111
# include "1111.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1112
# include "1112.inc"
#endif
#if defined TARGET_1113
# include "1113.inc"
#endif
#if defined TARGET_1114
# include "1114.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1115
# include "1115.inc"
#endif
#if defined TARGET_1116
# include "1116.inc"
#endif
#if defined TARGET_1117
# include "1117.inc"
#endif
#if defined TARGET_1118
# include "1118.inc"
#endif
#if defined TARGET_1119
# include "1119.inc"
#endif
#if defined TARGET_1120
# include "1120.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1121
# include "1121.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1122
# include "1122.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1123
# include "1123.inc"
#endif
#if defined TARGET_1124
# include "1124.inc"
#define ANSTYPE 3
#endif
#if defined TARGET_1125
# include "1125.inc"
#endif
#if defined TARGET_1126
# include "1126.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1127
# include "1127.inc"
#define ANSTYPE 2
#define VERSIONLATEX 0
#endif
#if defined TARGET_1128
# include "1128.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1129
# include "1129.inc"
#endif
#if defined TARGET_1130
# include "1130.inc"
#endif
%%% version latex %%%%
#if VERSIONLATEX==1 
\text{latexversion=\begin{enumerate}}
#if ANSTYPE==0
\text{latexversion=\latexversion
    \item
    \enonce
    \dots \enonceb
#if defined TARGET_1119
    \dots \enoncec
#endif
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
    autofocus} \enonceb
#if defined TARGET_1119
\embed{r2,10} \enoncec
#endif
  </div>
}
#if ANSTYPE==0
\answer{}{\rep}{type=numeric}{option=comma default=0}
#if defined TARGET_1119
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
