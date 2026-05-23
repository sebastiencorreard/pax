target=0401 0402 0403 0404 0405 0406 0407 0408 0409 0410 0411 0412 0413 0414 0415 0416 0417 0418 0419 0420 0421 0422 0423 0424 0425 0426 0427 0428 0429 0430
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
%%%%%%%%%%%%%%%%%%%%%%%% 30 pour litexp polyn factorisé  answer{}{\rep}{type=litexp}{option= polfactor default=0 weight=3}
%%%%%%%%%%%%%%%%%%%%%%%% 31 pour litexp polyn developpé  answer{}{\rep}{type=litexp}{option=\confparm2 polexpand default=0 weight=3}
%%%%%%%%%%%%%%%%%%%%%%%% 32 pour equation {\rep,x,y}
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

#if defined TARGET_0401
# include "0401.inc"
#endif
#if defined TARGET_0402
# include "0402.inc"
#endif
#if defined TARGET_0403
# include "0403.inc"
#define ANSTYPE 3
#endif
#if defined TARGET_0404
# include "0404.inc"
#endif
#if defined TARGET_0405
# include "0405.inc"
#endif
#if defined TARGET_0406
# include "0406.inc"
#endif
#if defined TARGET_0407
# include "0407.inc"
#endif
#if defined TARGET_0408
# include "0408.inc"
#define ANSTYPE 13
#define VERSIONLATEX 0
#endif
#if defined TARGET_0409
# include "0409.inc"
#endif
#if defined TARGET_0410
# include "0410.inc"
#endif
#if defined TARGET_0411
# include "0411.inc"
#endif
#if defined TARGET_0412
# include "0412.inc"
#define ANSTYPE 6
#endif
#if defined TARGET_0413
# include "0413.inc"
#endif
#if defined TARGET_0414
# include "0414.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0415
# include "0415.inc"
#endif
#if defined TARGET_0416
# include "0416.inc"
#endif
#if defined TARGET_0417
# include "0417.inc"
#endif
#if defined TARGET_0418
# include "0418.inc"
#endif
#if defined TARGET_0419
# include "0419.inc"
#endif
#if defined TARGET_0420
# include "0420.inc"
#define ANSTYPE 41
#define VERSIONLATEX 1
#endif
#if defined TARGET_0421
# include "0421.inc"
#endif
#if defined TARGET_0422
# include "0422.inc"
#endif
#if defined TARGET_0423
# include "0423.inc"
#endif
#if defined TARGET_0424
# include "0424.inc"
#endif
#if defined TARGET_0425
# include "0425.inc"
#endif
#if defined TARGET_0426
# include "0426.inc"
#define ANSTYPE 14
#define VERSIONLATEX 0
#endif
#if defined TARGET_0427
# include "0427.inc"
#endif
#if defined TARGET_0428
# include "0428.inc"
#endif
#if defined TARGET_0429
# include "0429.inc"
#endif
#if defined TARGET_0430
# include "0430.inc"
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
#if defined TARGET_0420
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
#if defined TARGET_0414
\embed{r2,10} \enoncec
#endif  
#endif
  </div>
}
#if ANSTYPE==0
\answer{}{\rep}{type=numeric}{option=comma default=0}
#if defined TARGET_0414
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
\answer{}{\rep}{type=equation}
#endif
#if ANSTYPE==41
\answer{Construction}{\sol0420}{type=jsxgraph}{option=noanalyzeprint}
#endif
#if ANSTYPE==6 && TARGET_0412
\answer{}{\reponse}{type=numeric}{option=defaut=0}
\condition{Le nombre est égal à \(\frac{\a}{\b}\) ?}{\reponse=\a/\b}
\condition{L'écriture est différente ?}{\reponse notsametext \a/\b}
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
\feedback{(\sc_reply1<1) and (\feedback!=)}{<div class="feedback">\feedback</div>}

#if VERSIONLATEX==1
\latex{
\begin{statement}
\latexversion
\end{statement}
\begin{solution}
\end{solution}
}
#endif
