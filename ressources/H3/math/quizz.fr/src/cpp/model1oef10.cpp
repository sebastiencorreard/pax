target= 1001 1002 1003 1004 1005 1006 1007 1008 1009 1010 1011 1012 1013 1014 1015 1016 1017 1018 1019 1020 1021 1022 1023 1024 1025 1026 1027 1028 1029 1030
\author{Paul,Byache}
\email{paul@byache.fr}

\observation{Le numéro de la question s'interprête comme suit : <br>Question XXYY est la question YY du niveau XX}
%%%%rq auteurs : Julien Lyotard pour la slib de la question 1030
%%%%% variable ANSTYPE : 0 pour numéric (par défaut)
%%%%%%%%%%%%%%%%%%%%%%%% 1 pour menu {1;\rep,\bads}{type=menu}{option=shuffle default=\bads[1]}
%%%%%%%%%%%%%%%%%%%%%%%% 11 Pour Menu VRAI FAUX %% Format answer{\rep;VRAI,FAUX}{type=menu}{option=default=\bads[1]}
%%%%%%%%%%%%%%%%%%%%%%%% 2 pour formal
%%%%%%%%%%%%%%%%%%%%%%%% 3 pour algexp
%%%%%%%%%%%%%%%%%%%%%%%% 31 pour litexp polyn developpé  answer{}{\rep3}{type=litexp}{option=\confparm2 polexpand default=0 weight=3}
%%%%%%%%%%%%%%%%%%%%%%%% 4 pour click
%%%%%%%%%%%%%%%%%%%%%%%% 5 pour numexp  %%%%%%%%%% Format answer{\rep}{type=numexp}{option=noreduction default=0}
%%%%%%%%%%%%%%%%%%%%%%%% 7 atext option symtext %% Format answer{}{\rep}{option=symtext default=0}

#define ANSTYPE 0

%%%%% variable VERSIONLATEX : 1 : a une version latext; 0: n'a aps une version latex
#define VERSIONLATEX 1

#include "instruction.inc"


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Level 10
#if defined TARGET_1001
# include "1001.inc"
#endif
#if defined TARGET_1002
# include "1002.inc"
#endif
#if defined TARGET_1003
# include "1003.inc"
#define ANSTYPE 31
#endif
#if defined TARGET_1004
# include "1004.inc"
#endif
#if defined TARGET_1005
# include "1005.inc"
#endif
#if defined TARGET_1006
# include "1006.inc"
#endif
#if defined TARGET_1007
# include "1007.inc"
#define ANSTYPE 5
#endif
#if defined TARGET_1008
# include "1008.inc"
#endif
#if defined TARGET_1009
# include "1009.inc"
#endif
#if defined TARGET_1010
# include "1010.inc"
#endif
#if defined TARGET_1011
# include "1011.inc"
#define ANSTYPE 3
#endif
#if defined TARGET_1012
# include "1012.inc"
#endif
#if defined TARGET_1013
# include "1013.inc"
#endif
#if defined TARGET_1014
# include "1014.inc"
\text{bads=\bad1}
#define ANSTYPE 11
#endif
#if defined TARGET_1015
# include "1015.inc"
#define ANSTYPE 3
#endif
#if defined TARGET_1016
# include "1016.inc"
#endif
#if defined TARGET_1017
# include "1017.inc"
#endif
#if defined TARGET_1018
# include "1018.inc"
#endif
#if defined TARGET_1019
# include "1019.inc"
#endif
#if defined TARGET_1020
# include "1020.inc"
#endif
#if defined TARGET_1021
# include "1021.inc"
#define VERSIONLATEX 0
#define ANSTYPE 3
#endif
#if defined TARGET_1022
# include "1022.inc"
#endif
#if defined TARGET_1023
# include "1023.inc"
#endif
#if defined TARGET_1024
# include "1024.inc"
#define ANSTYPE 7
#endif
#if defined TARGET_1025
# include "1025.inc"
#define ANSTYPE 3
#endif
#if defined TARGET_1026
# include "1026.inc"
#endif
#if defined TARGET_1027
# include "1027.inc"
#define ANSTYPE 3
#endif
#if defined TARGET_1028
# include "1028.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_1029
# include "1029.inc"
#endif
#if defined TARGET_1030
# include "1030.inc"
#define VERSIONLATEX 0
#endif
/*%%% version latex %%%%%%%%%%%%%%%%%%%%%%*/
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
#if ANSTYPE==11
\text{latexversion=\latexversion
    \item
    \enonce
    \begin{radio}
    \item VRAI
    \item FAUX
    \end{radio}}
#endif
\text{latexversion=\latexversion\end{enumerate}}
#endif
%%% fin version latex %%%%%%%%%%%

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
\answer{}{1;\rep,\bads}{type=menu}{option=shuffle default=\bads[1]}
#endif
#if ANSTYPE==11
\answer{}{\rep;VRAI,FAUX}{type=menu}{option=default=\bads[1]}
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
#if ANSTYPE==5
\answer{}{\rep}{type=numexp}{option=noreduction default=0}
#endif
#if ANSTYPE==7
\answer{}{\rep}{type=case}{option=symtext default=0}
#endif

\feedback{\sc_reply1<1 and \feedback!=}{
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
