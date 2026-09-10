target= coursespe1

\text{confparm1=\confparm1=?1,2,3,4,5,6,7,8,9,10,11,12:\confparm1}
#include "authors.inc"
#include "cssmutu.inc"
%%%%% confparm2 
\text{confparm2=\confparm2 issametext ?1:\confparm2}
%%%%% step  stop 1 sinon 2
\text{confparm3=\confparm3 issametext ?1:\confparm3}
\text{confparm3=\confparm3=2 and \confparm2=1?nonstop:}

#include "instruction.inc"
%%%%% Mots clefs
#define KEYWORD quizz,skill_calculate,calculation,fraction,percentage,percents,decimals,probability,literal_calculation,equations,graphing,functions,affine_function,inequations,mean
%%%%%%  toutes les questions
#include "question105.inc"                                  
\text{qen1=\enonce}
%%%% mélange et initialisation
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             %%% mélange des réponses
\integer{ng1=position(1,\t)}                     %%% position de la bonne réponse
\text{repA1=\qrep[\t[1]]} 
\text{repB1=\qrep[\t[2]]}
\text{repC1=\qrep[\t[3]]} 
\text{repD1=\qrep[\t[4]]}               
\text{qf1=\feedback}
\text{nq=105} 
\text{vlatex=1}
#include "question109.inc"
\text{qen2=\enonce}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng2=position(1,\t)}                     
\text{repA2=\qrep[\t[1]]} 
\text{repB2=\qrep[\t[2]]}
\text{repC2=\qrep[\t[3]]} 
\text{repD2=\qrep[\t[4]]} 
\text{qf2=\feedback}
\text{nq=\nq,109}
\text{vlatex=\vlatex,1}
#include "question501.inc"
\text{qen3=\enonce}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng3=position(1,\t)}                     
\text{repA3=\qrep[\t[1]]} 
\text{repB3=\qrep[\t[2]]}
\text{repC3=\qrep[\t[3]]} 
\text{repD3=\qrep[\t[4]]} 
\text{qf3=\feedback}
\text{nq=\nq,501}
\text{vlatex=\vlatex,1}
#include "question555.inc"
\text{qen4=\enonce}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng4=position(1,\t)}                     
\text{repA4=\qrep[\t[1]]} 
\text{repB4=\qrep[\t[2]]}
\text{repC4=\qrep[\t[3]]} 
\text{repD4=\qrep[\t[4]]} 
\text{qf4=\feedback}
\text{nq=\nq,555}
\text{vlatex=\vlatex,1}
#include "question800.inc"
\text{qen5=\enonce}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng5=position(1,\t)}                     
\text{repA5=\qrep[\t[1]]} 
\text{repB5=\qrep[\t[2]]}
\text{repC5=\qrep[\t[3]]} 
\text{repD5=\qrep[\t[4]]} 
\text{qf5=\feedback}
\text{nq=\nq,800}
\text{vlatex=\vlatex,1}
#include "question207.inc"
\text{qen6=\enonce}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng6=position(1,\t)}                     
\text{repA6=\qrep[\t[1]]} 
\text{repB6=\qrep[\t[2]]}
\text{repC6=\qrep[\t[3]]} 
\text{repD6=\qrep[\t[4]]} 
\text{qf6=\feedback}
\text{nq=\nq,207}
\text{vlatex=\vlatex,1}
#include "question302.inc"
\text{qen7=\enonce}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng7=position(1,\t)}                     
\text{repA7=\qrep[\t[1]]} 
\text{repB7=\qrep[\t[2]]}
\text{repC7=\qrep[\t[3]]} 
\text{repD7=\qrep[\t[4]]} 
\text{qf7=\feedback}
\text{nq=\nq,302}
\text{vlatex=\vlatex,1}
#include "question601.inc"
\text{qen8=\enonce}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng8=position(1,\t)}                     
\text{repA8=\qrep[\t[1]]} 
\text{repB8=\qrep[\t[2]]}
\text{repC8=\qrep[\t[3]]} 
\text{repD8=\qrep[\t[4]]} 
\text{qf8=\feedback}
\text{nq=\nq,601}
\text{vlatex=\vlatex,1}
#include "question303.inc"
\text{qen9=\enonce}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng9=position(1,\t)}                     
\text{repA9=\qrep[\t[1]]} 
\text{repB9=\qrep[\t[2]]}
\text{repC9=\qrep[\t[3]]} 
\text{repD9=\qrep[\t[4]]} 
\text{qf9=\feedback}
\text{nq=\nq,303}
\text{vlatex=\vlatex,1}
#include "question304.inc"
\text{qen10=\enonce}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng10=position(1,\t)}                     
\text{repA10=\qrep[\t[1]]} 
\text{repB10=\qrep[\t[2]]}
\text{repC10=\qrep[\t[3]]} 
\text{repD10=\qrep[\t[4]]} 
\text{qf10=\feedback}
\text{nq=\nq,304}
\text{vlatex=\vlatex,1}
#include "question651.inc"
\text{qen11=\enonce}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng11=position(1,\t)}                     
\text{repA11=\qrep[\t[1]]} 
\text{repB11=\qrep[\t[2]]}
\text{repC11=\qrep[\t[3]]} 
\text{repD11=\qrep[\t[4]]} 
\text{qf11=\feedback}
\text{nq=\nq,651}
\text{vlatex=\vlatex,1}
#include "question205.inc"
\text{qen12=\enonce}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng12=position(1,\t)}                     
\text{repA12=\qrep[\t[1]]} 
\text{repB12=\qrep[\t[2]]}
\text{repC12=\qrep[\t[3]]} 
\text{repD12=\qrep[\t[4]]} 
\text{qf12=\feedback}
\text{nq=\nq,205}
\text{vlatex=\vlatex,1}
%%%%%%% 
\text{enonce=\qen1,\qen2,\qen3,\qen4,\qen5,\qen6,\qen7,\qen8,\qen9,\qen10,\qen11,\qen12}
\text{repA=\repA1,\repA2,\repA3,\repA4,\repA5,\repA6,\repA7,\repA8,\repA9,\repA10,\repA11,\repA12},
\text{repB=\repB1,\repB2,\repB3,\repB4,\repB5,\repB6,\repB7,\repB8,\repB9,\repB10,\repB11,\repB12}
\text{repC=\repC1,\repC2,\repC3,\repC4,\repC5,\repC6,\repC7,\repC8,\repC9,\repC10,\repC11,\repC12}
\text{repD=\repD1,\repD2,\repD3,\repD4,\repD5,\repD6,\repD7,\repD8,\repD9,\repD10,\repD11,\repD12}
\text{feed=\qf1,\qf2,\qf3,\qf4,\qf5,\qf6,\qf7,\qf8,\qf9,\qf10,\qf11,\qf12},

%%%% nombre de questions maximum
\integer{nbqap=items(\confparm1)} %%%%%% nombre de questions à poser
%%%%%%%%% mélange au hasard des questions %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%% ne pas mettre avant car il y a tt les titres des fichiers .inc

\title{Course d'automates S 1}
\observation{codé à partir du sujet zéro sujet-specialite-1.pdf publié en 2025 sur Eduscol}
\keywords{#KEYWORD}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\text{choix=\confparm1= ? wims(makelist x for x=1 to 12): \confparm1}
\matrix{STEP= wims(makelist reply x for x in \choix)}
\if{\confparm2=1}{\matrix{STEP=wims(replace internal , by ; in \STEP)}}
\steps{\STEP}
%%%%%%%%%%%%%%%%
\statement{
\if{\confparm2=2}{
\for{ii=1 to \nbqap}{
  <h2>Question \nq[\choix[\ii]]</h2>
  <div class="wims_instruction">\instruction</div>
  <div class="wims_question">
    \enonce[\choix[\ii]]
    <div class="wimscenter wims_scrollable">
  <table class="wimsborder"><tr><th>
  A. </th><th>B. </th><th> C.</th><th> D.
  </th></tr>
  <tr><td>\repA[\choix[\ii]] </td><td>\repB[\choix[\ii]]</td><td>\repC[\choix[\ii]]</td><td>\repD[\choix[\ii]]</td></tr>
  </table>
  </div>
   <div class="wimscenter">
    <b> \embed{reply \choix[\ii]} </b>
    </div>
  </div>
  }
}{
<div class="wimscenter">
<div class="wims_score_bar">
<div class="inline">
    \for{j=1 to \step-1}{
    <div class="inline wims_seed_item" style="background-color:blue" title="done"></div>
  }
  \for{j=\step to \nbqap}{
    <div class="inline wims_seed_item" style="background-color:#FFF" title="todo"></div>
  }
</div>
</div>
</div>
\for{ii=1 to \nbqap}{
  \if{\step=\ii}{ 
  <h2>Question \nq[\choix[\ii]]</h2>
      <div class="wims_instruction">\instruction</div>
  <div class="wims_question">
  \enonce[\choix[\ii]]
    <div class="wimscenter wims_scrollable">
  <table class="wimsborder"><tr><th>
  A. </th><th>B. </th><th> C.</th><th> D.
  </th></tr>
  <tr><td>\repA[\choix[\ii]] </td><td>\repB[\choix[\ii]]</td><td>\repC[\choix[\ii]]</td><td>\repD[\choix[\ii]]</td></tr>
  </table>
  </div>
    <div class="wimscenter">
    <b> \embed{reply\choix[\ii]} </b>
    </div>
  </div>
  }
}
}
}

\answer{}{\ng1;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng2;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng3;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng4;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng5;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng6;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng7;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng8;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng9;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng10;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng11;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng12;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}

\text{screp=\sc_reply1,\sc_reply2,\sc_reply3,\sc_reply4,\sc_reply5,\sc_reply6,\sc_reply7,
\sc_reply8,\sc_reply9,\sc_reply10,\sc_reply11,\sc_reply12}

%%%% version step+laisser finir
\feedback{\confparm2=1 and \confparm3= }{
  \for{tt=1 to \nbqap}{
    \if{\screp[\choix[\tt]]!=\empty and \screp[\choix[\tt]]!=1 }{
      <div class="feedmutu">\feed[\choix[\tt]]
      \if{\choix[\tt]=6}{\special{glossary mathematics/algebra/fr/inverse_number,content=[5]}}</div>
    }
  }
}
%%%% feedback version non step ou (step+laisser finir)
\if{\confparm2=2 or (\confparm2=1 and \confparm3 issametext nonstop)}{
  \text{temp=position(0,\screp)}
  \if{items(\temp)=1}{
    \integer{n1=\temp}
    }
    {
    \integer{n1=item(1,\temp)} %%% il ne peut y avoir que des zéros et des 1 dans les score
    }
    
  \integer{n0=position(\n1,\choix)}  
  \integer{chn0=\choix[\n0]}
  %%%%% test si tout est juste
  \text{screpttjuste=wims(replace internal 0 by 1 in \screp)}
  }
%%%% fin  du test
\feedback{\confparm2=2 or (\confparm2=1 and \confparm3 issametext nonstop)}{
  \if{\screpttjuste notsametext \screp and \screp[\n0]<1 and \feed[\choix[\n0]]!=}{
      <div class="feedmutu"><p><u>Première erreur sur la question&nbsp:</u></p>
      <p>\enonce[\chn0]</p>
      <div class="wimscenter wims_scrollable">
      <table class="wimsborder"><tr>
      <th>A. <br>\repA[\chn0]</th>
      <th>B. <br>\repB[\chn0]</th>
      <th>C. <br>\repC[\chn0]</th>
      <th>D. <br>\repD[\chn0]</th>
      </tr>
      </table>
      </div>
      <p><u>Indication pour trouver la bonne réponse&nbsp:</u></p>
      <p>\feed[\chn0]</p>
      \if{\chn0=6}{\special{glossary mathematics/algebra/fr/inverse_number,content=[5]}}
    </div>
    }
  }

%%%%%%%%%%%%%%% version latex
\text{latexversion=\begin{enumerate}}
\for{h=1 to \nbqap}{
%%%% exclure les version non latex
  \if{\vlatex[\h] =1}{
    \text{latexversion=\latexversion
    \item
    \enonce[\choix[\h]]
    \begin{radio}
    \item \repA[\choix[\h]]
    \item \repB[\choix[\h]]
    \item \repC[\choix[\h]]
    \item \repD[\choix[\h]]
    \end{radio}}}
    }
\text{latexversion=\latexversion \end{enumerate}}
%%%%%%%%%%% fin version latex
