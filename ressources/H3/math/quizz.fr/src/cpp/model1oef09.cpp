target=0901 0902 0903 0904 0905 0906 0907 0908 0909 0910 0911 0912 0913 0914 0915 0916 0917 0918 0919 0920 0921 0922 0923 0924 0925 0926 0927 0928 0929 0930
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

%%%%% variable LATEXVERSION : 1 : a une version latext; 0: n'a aps une version latex
#define VERSIONLATEX 1


#define ANSTYPE 0

#include "instruction.inc"

#if defined TARGET_0901
# include "0901.inc"
#endif
#if defined TARGET_0902
# include "0902.inc"
#define ANSTYPE 2
#endif
#if defined TARGET_0903
# include "0903.inc"
#endif
#if defined TARGET_0904
# include "0904.inc"
#endif
#if defined TARGET_0905
# include "0905.inc"
#endif
#if defined TARGET_0906
# include "0906.inc"
#endif
#if defined TARGET_0907
# include "0907.inc"
#endif
#if defined TARGET_0908
# include "0908.inc"
#endif
#if defined TARGET_0909
# include "0909.inc"
#define ANSTYPE 1
#endif
#if defined TARGET_0910
# include "0910.inc"
#endif
#if defined TARGET_0911
# include "0911.inc"
#define ANSTYPE 2
#endif
#if defined TARGET_0912
# include "0912.inc"
#endif
#if defined TARGET_0913
# include "0913.inc"
#endif
#if defined TARGET_0914
# include "0914.inc"
#endif
#if defined TARGET_0915
# include "0915.inc"
#endif
#if defined TARGET_0916
# include "0916.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0917
# include "0917.inc"
#endif
#if defined TARGET_0918
# include "0918.inc"
#endif
#if defined TARGET_0919
# include "0919.inc"
#endif
#if defined TARGET_0920
# include "0920.inc"
#endif
#if defined TARGET_0921
# include "0921.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0922
# include "0922.inc"
#endif
#if defined TARGET_0923
# include "0923.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0924
# include "0924.inc"
#endif
#if defined TARGET_0925
# include "0925.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_0926
# include "0926.inc"
#endif
#if defined TARGET_0927
# include "0927.inc"
#define ANSTYPE 2
#endif
#if defined TARGET_0928
# include "0928.inc"
#endif
#if defined TARGET_0929
# include "0929.inc"
#define ANSTYPE 3
#endif
#if defined TARGET_0930
# include "0930.inc"
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
