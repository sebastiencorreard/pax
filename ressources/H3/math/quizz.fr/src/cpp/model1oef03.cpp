target= 0301 0302 0303 0304 0305 0306 0307 0308 0309 0310 0311 0312 0313 0314 0315 0316 0317 0318 0319 0320
\author{Bruno,Mifsud}
\email{communaute.mutuwims@laposte.net}
\observation{Le numéro de la question s'interprête comme suit : <br>Question XXYY est la question YY du niveau XX}
%%%%% variable ANSTYPE : 0 pour numéric (par défaut)
%%%%%%%%%%%%%%%%%%%%%%%% 1 pour menu {1;\rep,\bad1,\bad2}{type=menu}{option=shuffle default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 11 Pour Menu VRAI FAUX{\rep;VRAI,FAUX}{type=menu}{option=default=\bads[1]}
%%%%%%%%%%%%%%%%%%%%%%%% 12 pour menu {\rep;Figure 1,Figure 2, Figure 3}{type=menu}{option= default=\bad1}
%%%%%%%%%%%%%%%%%%%%%%%% 2 pour formal
%%%%%%%%%%%%%%%%%%%%%%%% 3 pour algexp
%%%%%%%%%%%%%%%%%%%%%%%% 4 pour click
%%%%%%%%%%%%%%%%%%%%%%%% 5 pour numexpFormat :{\rep}{type=numexp}{option=noreduction default=0}
%%%%%%%%%%%%%%%%%%%%%%%% 6 pour condition : %answer{}{\reponse}{type=numeric}


#define ANSTYPE 0
%%%%% variable LATEXVERSION : 1 : a une version latext; 0: n'a aps une version latex
#define LATEXVERSION 1

#include "instruction_primaire.inc"

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% course 3
#if defined TARGET_0301
# include "0301.inc"
#endif
#if defined TARGET_0302
# include "0302.inc"
#define LATEXVERSION 0
#endif
#if defined TARGET_0303
# include "0303.inc"
#endif
#if defined TARGET_0304
# include "0304.inc"
#define ANSTYPE 12
#define LATEXVERSION 0
#endif
#if defined TARGET_0305
# include "0305.inc"
#endif
#if defined TARGET_0306
# include "0306.inc"
#define ANSTYPE 6
#endif
#if defined TARGET_0307
# include "0307.inc"
#endif
#if defined TARGET_0308
# include "0308.inc"
#define ANSTYPE 1
#endif
#if defined TARGET_0309
# include "0309.inc"
#endif
#if defined TARGET_0310
# include "0310.inc"
#endif
#if defined TARGET_0311
# include "0311.inc"
#define ANSTYPE 1
#endif
#if defined TARGET_0312
# include "0312.inc"
#endif
#if defined TARGET_0313
# include "0313.inc"
#define ANSTYPE 1
#endif
#if defined TARGET_0314
# include "0314.inc"
#endif
#if defined TARGET_0315
# include "0315.inc"
#define ANSTYPE 6
#endif
#if defined TARGET_0316
# include "0316.inc"
#endif
#if defined TARGET_0317
# include "0317.inc"
#endif
#if defined TARGET_0318
# include "0318.inc"
#endif
#if defined TARGET_0319
# include "0319.inc"
#endif
#if defined TARGET_0320
# include "0320.inc"
#define ANSTYPE 12
#define VERSIONLATEX 0
#endif
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%fin course 3
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
#if ANSTYPE==11
\text{latexversion=\latexversion
    \item
    \enonce
    \begin{radio}
    \item VRAI
    \item FAUX
    \end{radio}}
#endif
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
#if defined TARGET0306

#endif

#if ANSTYPE==0
\answer{}{\rep}{type=numeric}{option=comma default=0}
#endif
#if ANSTYPE==1
\answer{}{1;\rep,\bad1,\bad2}{type=menu}{option=shuffle default=\bad1 weight=2}
#endif
#if ANSTYPE==12
\answer{}{\rep;Figure 1,Figure 2, Figure 3}{type=menu}{option= default=\bad1}
#endif
#if ANSTYPE==2
\answer{}{\rep}{type=formal}{option=comma default=0}
#endif
#if ANSTYPE==3
\answer{}{\rep}{type=algexp}{option=comma default=0}
#endif
#if ANSTYPE==4
\answer{}{1;<img src="\rep">,<img src="\bad1">,<img src="\bad2">}{type=click}{option=default=<img src="\bad2"> shuffle }
#endif
#if ANSTYPE==6 && TARGET_0306
\answer{}{\reponse}{type=numeric}{option=defaut=0}
\condition{Le nombre est plus grand que 999 ?}{\reponse>999}
\text{mot1=wims(text expand \reponse using 01)}
\text{mot1=wims(words2items \mot1)}
\text{reponse2=wims(words2items \mot1)}
\text{cntreponse=items(\reponse2)}
\integer{somme1=0}
\for{k=1 to \cntreponse}{\integer{somme1=\somme1+\reponse2[\k]}}
\integer{somme0=\cntreponse*\chiffre}
\condition{Le nombre s'écrit qu'avec des \chiffre ?}{\somme0 issametext \somme1}
#endif

#if ANSTYPE==6 && TARGET_0315
\answer{}{\reponse}{type=numeric}{option=defaut=0}
\text{mot1=wims(text expand \reponse using 01)}
\text{mot1=wims(words2items \mot1)}
\text{reponse2=wims(words2items \mot1)}
\text{cntreponse=items(\reponse2)}
\integer{nbcentaine=\cntreponse<3?0:\reponse2[\cntreponse-2]}
%%% cas où le chiffre des centaines est nul, mais celui des centaines de millier non
\if{\nbcentaine==0}{\integer{nbcentaine=\cntreponse<6?0:\reponse2[\cntreponse-5]}}
%%%%% traiter les cas où on entend et le chiffre des milliers aussi
\integer{nbmillier=\cntreponse<4?0:\reponse2[\cntreponse-3]\reponse2[\cntreponse-4]\reponse2[\cntreponse-5]}
\condition{Dans \reponse on entend "cent" ?}{\nbcentaine!=0}
\condition{Dans \reponse on entend "mille" ?}{\nbmillier!=0}
#endif

\feedback{\sc_reply1 < 1 and \feedback!=}{
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
