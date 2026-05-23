target=1201 1202 1203 1204 1205 1206 1207 1208 1209 1210 1211 1212 1213 1214 1215 1216 1217 1218 1219 1220 1221 1222 1223 1224 1225 1226 1227 1228 1229 1230
\author{Bruno,Mifsud}
\email{communaute.mutuwims@laposte.net}
\observation{Le numéro de la question s'interprète comme suit : <br>Question XXYY est la question YY du niveau XX}
%%%%% variable ANSTYPE : 0 pour numéric (par défaut)
%%%%%%%%%%%%%%%%%%%%%%%% 1 pour menu {1;\rep,\bad1,\bad2}{type=menu}{option=shuffle default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 11 Pour Menu VRAI FAUX{\rep;VRAI,FAUX}{type=menu}{option=default=\bads[1]}
%%%%%%%%%%%%%%%%%%%%%%%% 12 pour menu {\rep;Figure 1,Figure 2, Figure 3}{type=menu}{option= default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 2 pour formal
%%%%%%%%%%%%%%%%%%%%%%%% 3 pour algexp
%%%%%%%%%%%%%%%%%%%%%%%% 31 pour litexp polyn developpé  answer{}{\rep3}{type=litexp}{option=\confparm2 polexpand default=0 weight=3}
%%%%%%%%%%%%%%%%%%%%%%%% 4 pour click
%%%%%%%%%%%%%%%%%%%%%%%% 5 pour numexpFormat :{\rep}{type=numexp}{option=noreduction default=0}
%%%%%%%%%%%%%%%%%%%%%%%% 6 pour condition : %answer{}{\reponse}{type=numeric}
%%%%%%%%%%%%%%%%%%%%%%%%       %condition{}{\reponse isitemof \rep}
%%%%%%%%%%%%%%%%%%%%%%%% 7 atext option symtext %% Format answer{}{\rep}{type=atext}{option=symtext default=0}
%%%%%%%%%%%%%%%%%%%%%%%% 8 sfet  type=fset option=defaut=12345
%%%%%%%%%%%%%%%%%%%%%%%% 9 equation

%%%%% variable LATEXVERSION : 1 : a une version latext; 0: n'a aps une version latex
#define VERSIONLATEX 1


#define ANSTYPE 0

#include "instruction.inc"

#if defined TARGET_1201
# include "1201.inc"
#endif
#if defined TARGET_1202
# include "1202.inc"
#endif
#if defined TARGET_1203
# include "1203.inc"
#define ANSTYPE 31
#endif
#if defined TARGET_1204
# include "1204.inc"
#endif
#if defined TARGET_1205
# include "1205.inc"
#endif
#if defined TARGET_1206
# include "1206.inc"
#endif
#if defined TARGET_1207
# include "1207.inc"
#endif
#if defined TARGET_1208
# include "1208.inc"
#endif
#if defined TARGET_1209
# include "1209.inc"
#endif
#if defined TARGET_1210
# include "1210.inc"
#endif
#if defined TARGET_1211
# include "1211.inc"
#endif
#if defined TARGET_1212
# include "1212.inc"
#define ANSTYPE 8
#endif
#if defined TARGET_1213
# include "1213.inc"
#endif
#if defined TARGET_1214
# include "1214.inc"
#endif
#if defined TARGET_1215
# include "1215.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1216
# include "1216.inc"
%%%%% deux champs de réponse
#define VERSIONLATEX 0
#endif
#if defined TARGET_1217
# include "1217.inc"
#endif
#if defined TARGET_1218
# include "1218.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1219
# include "1219.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1220
# include "1220.inc"
#endif
#if defined TARGET_1221
# include "1221.inc"
#endif
#if defined TARGET_1222
# include "1222.inc"
#endif
#if defined TARGET_1223
# include "1223.inc"
#define ANSTYPE 2
#endif
#if defined TARGET_1224
# include "1224.inc"
#endif
#if defined TARGET_1225
# include "1225.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1226
# include "1226.inc"
#endif
#if defined TARGET_1227
# include "1227.inc"
#endif
#if defined TARGET_1228
# include "1228.inc"
#define ANSTYPE 2
#endif
#if defined TARGET_1229
# include "1229.inc"
#endif
#if defined TARGET_1230
# include "1230.inc"
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
  \enonce \embed{r1,10
    autofocus} \enonceb
#if defined TARGET_1216
\embed{r2,10}
\enoncec
#endif 
#if defined TARGET_1225
\embed{r2,10}
#endif 
#if defined TARGET_1230
\embed{r2,10} \enoncec
\embed{r3,10} \enonced
#endif 
  </div>
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
#if ANSTYPE==31
\answer{}{\rep}{type=litexp}{option=polexpand default=0}
#endif
#if ANSTYPE==7
\answer{}{\rep}{type=atext}{option=symtext default=}
#endif
#if ANSTYPE==8
\answer{}{\rep}{type=fset}{option=default=12345}
#endif
#if ANSTYPE==9
\answer{}{\rep}{type=equation}{option=default=y=12345x}
#endif
#if defined TARGET_1216
\answer{}{\repb}{type=numeric}{option=comma default=0}
#endif
#if defined TARGET_1225
\answer{}{\repb}{type=numeric}{option=comma default=0}
#endif
#if defined TARGET_1230
\answer{}{\repb}{type=numeric}{option=comma default=0}
\answer{}{\repc}{type=numeric}{option=comma default=0}
#endif
\feedback{(\sc_reply1<1) and (\feedback!=)}{
  <style>.feedmutu {
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
