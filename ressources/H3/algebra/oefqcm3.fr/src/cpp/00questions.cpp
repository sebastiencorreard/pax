target=q100 q101 q102 q103 q104 q105 q106 q107 q200 q201 q202 q203 q204 q205 q300 q301 q400 q500 q501 q502

%%%%% variable LATEXVERSION : 1 : a une version latext; 0: n'a pas une version latex
%%% Par défaut il y a uune version latex
#define VERSIONLATEX 1
#define TYPEQUEST 0
%%% 0 : réponse libre 
%%%%1 : QCU
%%% par défaut c'est une question libre

#include "cssmutu.inc"
#include "instructions.inc"
\computeanswer{no}
\precision{10000000}


#if defined TARGET_q100
#include "author_mb.inc"
#include "question100.inc"
#endif

#if defined TARGET_q101
#include "author_sco.inc"
#include "question101.inc"
#endif

#if defined TARGET_q102
#include "question102.inc"
#define VERSIONLATEX 0
#endif

#if defined TARGET_q103
#include "author_mb.inc"
#include "question103.inc"
#endif

#if defined TARGET_q104
#include "author_mb.inc"
#include "question104.inc"
#endif

#if defined TARGET_q105
#define TYPEQUEST 1
#include "author_mb.inc"
#include "question105.inc"
#endif

#if defined TARGET_q106
#define TYPEQUEST 1
#define VERSIONLATEX 0
#include "author_sp.inc"
#include "question106.inc"
#endif

#if defined TARGET_q107
#include "author_sp.inc"
#define TYPEQUEST 1
#include "question107.inc"
#endif

#if defined TARGET_q200
#include "question200.inc"
#define TYPEQUEST 2
#define VERSIONLATEX 0
#endif

#if defined TARGET_q201
#include "author_mb.inc"
#include "question201.inc"
#endif

#if defined TARGET_q202
#include "author_sp.inc"
#include "question202.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_q203
#include "author_sp.inc"
#include "question203.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_q204
#include "author_mb.inc"
#include "question204.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_q205
#include "author_sp.inc"
#include "question205.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_q300
#include "author_mb.inc"
#include "question300.inc"
#endif
#if defined TARGET_q301
#define TYPEQUEST 1
#include "author_mb.inc"
#include "question301.inc"
#endif
#if defined TARGET_q400
#include "author_mb.inc"
#include "question400.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_q500
#include "author_sco.inc"
#include "question500.inc"
#define TYPEQUEST 1
#define VERSIONLATEX 0
%%%% question particulière deux colonnes pour les réponses.
#endif
#if defined TARGET_q501
#include "author_sco.inc"
#include "question501.inc"
#define VERSIONLATEX 0
#endif
#if defined TARGET_q502
#include "author_mb.inc"
#include "question502.inc"
#define VERSIONLATEX 0
#endif

#if VERSIONLATEX==1 
#if TYPEQUEST==1
\text{latexversion=\latexversion
    \item
    \enonce
    \begin{radio}
    \item \ttrep[1]
    \item \ttrep[2]
    \item \ttrep[3]
    \item \ttrep[4]   
    \end{radio}}
#endif
#if TYPEQUEST==0
\text{latexversion=\latexversion
    \item
    \enonce
    \newline Réponse : \hspace{4em}    \enonceb
    }
#endif
\text{latexversion=\latexversion \end{enumerate}}
#endif

#if TYPEQUEST==0
\statement{<div class="wims_instruction">\instruction</div>
<div class="wims_question">
  \enonce 
 <br><label for="reply1"> Réponse&nbsp;&#58;</label> \embed{r1,10
 autofocus}
  \enonceb
</div>}

\answer{}{\rep}{type=\typerep}{option=nolegend noanalyzeprint }
#endif
#if TYPEQUEST==1
%%% Mélange les questions
%%% modif au 22/12/25 ancien ne fonctionnant pas avec q404
\text{ttrep=\good,\bads}
\text{mel=shuffle(4)}
\text{ttrep=\ttrep[\mel[1]],\ttrep[\mel[2]],\ttrep[\mel[3]],\ttrep[\mel[4]]}
\integer{nrep=position(1,\mel)}
#if TARGET_q200
%%% pour affichage conditionnel du feedback
\text{test=0}
#endif
\statement{<div class="wims_instruction">\instruction</div>
<div class="wims_question">
  \enonce 
  <div class="wimscenter wims_scrollable">
  <table class="wimsborder">
#if TARGET_q500
<tr><th>  A. </th><th>B. </th></tr>
<tr><td>\ttrep[1] </td><td>\ttrep[2] </td></tr>
<tr><td> C.</td><td> D.</td></tr>
<tr><td>\ttrep[3] </td><td>\ttrep[4] </td></tr>
#else
<tr><th>
  A. </th><th>B. </th><th> C.</th><th> D.
  </th></tr>
  <tr><td>\ttrep[1] </td><td>\ttrep[2] </td><td>\ttrep[3] </td><td>\ttrep[4] </td></tr>
#endif  
  </table>
  </div>
  <div class="wimscenter">
  <b> \embed{r1} </b>
  </div>
</div>}
%%% answer
\answer{}{\nrep;Réponse A, Réponse B, Réponse C, Réponse D}{type=radio}{option=nolegend noanalyzeprint}
#endif


#if TYPEQUEST==2
%% 4 champs de réponses type "thales"
\statement{<div class="wims_instruction">\instruction</div>
<div class="wims_question">
  \enonce 
 <br>Réponse&nbsp;&#58; <table class="wimscenter wimsnoborder">
<tr><td>\embed{reply 1,\size}</td><td></td><td>\embed{reply 2,\size}</td>
</tr><tr>
<td><hr></td><td>=</td>
<td><hr></td>
</tr><tr>
<td>\embed{reply 3,\size}</td><td></td><td> \embed{reply 4,\size}</td>
</tr></table>
  \enonceb
</div>}

\answer{}{\rep1}{type=\typerep}
\answer{}{\rep2}{type=\typerep}
\answer{}{\rep3}{type=\typerep}
\answer{}{\rep4}{type=\typerep}
\if{(\rep1 issametext \A\B or \rep1 issametext \B\A) and \rep3*\rep2/\rep4=\t*\s/\q or (\rep2 issametext \A\B or \rep2 issametext \B\A) and \rep1*\rep4/\rep3=\t*\s/\q or (\rep3 issametext \A\B or \rep3 issametext \B\A) and \rep1*\rep4/\rep2=\t*\s/\q or (\rep4 issametext \A\B or \rep4 issametext \B\A)  and \rep2*\rep3/\rep1=\t*\s/\q}{
\text{test=1}}{\text{test=0}}
\condition{\textcond}{(\rep1 issametext \A\B or \rep1 issametext \B\A) and \rep3*\rep2/\rep4=\t*\s/\q or (\rep2 issametext \A\B or \rep2 issametext \B\A) and \rep1*\rep4/\rep3=\t*\s/\q or (\rep3 issametext \A\B or \rep3 issametext \B\A) and \rep1*\rep4/\rep2=\t*\s/\q or (\rep4 issametext \A\B or \rep4 issametext \B\A)  and \rep2*\rep3/\rep1=\t*\s/\q}
#endif
#if TARGET_q200
\feedback{\test=0}{
<div class="feedmutu">\feedback</div>}
#else
\feedback{(\sc_reply1<1) and (\feedback!=)}{
  <div class="feedmutu">\feedback</div>}
#endif

#if VERSIONLATEX==1
\latex{
\begin{statement}
\latexversion
\end{statement}
\begin{solution}
\end{solution}
}
#endif
