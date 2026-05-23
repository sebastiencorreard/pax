target= csgb

\text{confparm1=\confparm1=?1,2,3,4,5,6,7,8,9:\confparm1}
\computeanswer{no}
\precision{100000}
#include "authors.inc"
#include "cssmutu.inc"
%%%%% confparm2 
\text{confparm2=\confparm2 issametext ?1:\confparm2}
%%%%% step  stop 1 sinon 2
\text{confparm3=\confparm3 issametext ?1:\confparm3}
\text{confparm3=\confparm3=2 and \confparm2=1?nonstop:}

#include "instructions.inc"
%%%%% Mots clefs
#define KEYWORD quizz,percentage,equations,algorithmics,calculation,graphing,functions,proportionality,thales,angles,périmètre,mean
%%%%%%  toutes les questions
#include "question201.inc"                                  
\text{qen1=\enonce}
\text{qenb1=\enonceb}
%%%% si QCU mélange et initialisation
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                              %%% mélange des réponses
\integer{ng1=position(1,\t)}                     %%% position de la bonne réponse
\text{repA1=\qrep[\t[1]]} 
\text{repB1=\qrep[\t[2]]}
\text{repC1=\qrep[\t[3]]} 
\text{repD1=\qrep[\t[4]]} 
%%%% si question libre
\text{rep1=\rep}
\text{trep1=\typerep}
\text{size1=5}
%%%%              
\text{qf1=\feedback}
\text{nq=201} 
\text{vlatex=1}
\text{qcu=0}
#include "question301.inc"
\text{qen2=\enonce}
\text{qenb2=\enonceb}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng2=position(1,\t)}                     
\text{repA2=\qrep[\t[1]]} 
\text{repB2=\qrep[\t[2]]}
\text{repC2=\qrep[\t[3]]} 
\text{repD2=\qrep[\t[4]]} 
%%%% si question libre
\text{rep2=\rep}
\text{trep2=\typerep}
\text{size2=8}
%%%% 
\text{qf2=\feedback}
\text{nq=\nq,301}
\text{vlatex=\vlatex,1}
\text{qcu=\qcu,0}
#include "question104.inc"
\text{qen3=\enonce}
\text{qenb3=\enonceb}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng3=position(1,\t)}                     
\text{repA3=\qrep[\t[1]]} 
\text{repB3=\qrep[\t[2]]}
\text{repC3=\qrep[\t[3]]} 
\text{repD3=\qrep[\t[4]]} 
%%%% si question libre
\text{rep3=\rep}
\text{trep3=\typerep}
\text{size3=8}
%%%% 
\text{qf3=\feedback}
\text{nq=\nq,104}
\text{vlatex=\vlatex,1}
\text{qcu=\qcu,0}
#include "question400.inc"
\text{qen4=\enonce}
\text{qenb4=\enonceb}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng4=position(1,\t)}                     
\text{repA4=\qrep[\t[1]]} 
\text{repB4=\qrep[\t[2]]}
\text{repC4=\qrep[\t[3]]} 
\text{repD4=\qrep[\t[4]]}
%%%% si question libre
\text{rep4=\rep}
\text{trep4=\typerep}
\text{size4=8}
%%%%  
\text{qf4=\feedback}
\text{nq=\nq,400}
\text{vlatex=\vlatex,0}
\text{qcu=\qcu,0}
#include "question107.inc"
\text{qen5=\enonce}
\text{qenb5=\enonceb}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng5=position(1,\t)}                     
\text{repA5=\qrep[\t[1]]} 
\text{repB5=\qrep[\t[2]]}
\text{repC5=\qrep[\t[3]]} 
\text{repD5=\qrep[\t[4]]} 
%%%% si question libre
\text{rep5=\rep}
\text{trep5=\typerep}
\text{size5=8}
%%%% 
\text{qf5=\feedback}
\text{nq=\nq,107}
\text{vlatex=\vlatex,1}
\text{qcu=\qcu,1}
#include "question205.inc"
\text{qen6=\enonce}
\text{qenb6=\enonceb}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng6=position(1,\t)}                     
\text{repA6=\qrep[\t[1]]} 
\text{repB6=\qrep[\t[2]]}
\text{repC6=\qrep[\t[3]]} 
\text{repD6=\qrep[\t[4]]} 
%%%% si question libre
\text{rep6=\rep}
\text{trep6=\typerep}
\text{size6=8}
%%%% 
\text{qf6=\feedback}
\text{nq=\nq,205}
\text{vlatex=\vlatex,0}
\text{qcu=\qcu,0}
#include "question105.inc"
\text{qen7=\enonce}
\text{qenb7=\enonceb}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng7=position(1,\t)}                     
\text{repA7=\qrep[\t[1]]} 
\text{repB7=\qrep[\t[2]]}
\text{repC7=\qrep[\t[3]]} 
\text{repD7=\qrep[\t[4]]} 
%%%% si question libre
\text{rep7=\rep}
\text{trep7=\typerep}
\text{size7=8}
%%%% 
\text{qf7=\feedback}
\text{nq=\nq,105}
\text{vlatex=\vlatex,1}
\text{qcu=\qcu,1}
#include "question200.inc"
\text{qen8=\enonce}
\text{qenb8=\enonceb}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
%%% question avec condition création des variables nécessaires
\text{nomlong1=\A\B}
\text{nomlong2=\B\A}
\text{t200=\t}
\text{s200=\s}
\text{q200=\q}
%%%% 
\text{t=shuffle(4)}                             
\integer{ng8=position(1,\t)}                     
\text{repA8=\qrep[\t[1]]} 
\text{repB8=\qrep[\t[2]]}
\text{repC8=\qrep[\t[3]]} 
\text{repD8=\qrep[\t[4]]} 
%%%% si question libre
\text{rep8=\rep}
\text{trep8=\typerep}
\text{size8=8}
%%%%%

\text{qf8=\feedback}
\text{nq=\nq,200}
\text{vlatex=\vlatex,0}
\text{qcu=\qcu,0}
#include "question501.inc"
\text{qen9=\enonce}
\text{qenb9=\enonceb}
\text{qrep=\good,\bads[1],\bads[2],\bads[3]}
\text{t=shuffle(4)}                             
\integer{ng9=position(1,\t)}                     
\text{repA9=\qrep[\t[1]]} 
\text{repB9=\qrep[\t[2]]}
\text{repC9=\qrep[\t[3]]} 
\text{repD9=\qrep[\t[4]]}
%%%% si question libre
\text{rep9=\rep}
\text{trep9=\typerep}
\text{size9=8}
%%%%  
\text{qf9=\feedback}
\text{nq=\nq,501}
\text{vlatex=\vlatex,0}
\text{qcu=\qcu,0}
%%%%%%% 
\text{enonce=\qen1,\qen2,\qen3,\qen4,\qen5,\qen6,\qen7,\qen8,\qen9}
\text{enonceb=\qenb1,\qenb2,\qenb3,\qenb4,\qenb5,\qenb6,\qenb7,\qenb8,\qenb9}
\text{repA=\repA1,\repA2,\repA3,\repA4,\repA5,\repA6,\repA7,\repA8,\repA9}
\text{repB=\repB1,\repB2,\repB3,\repB4,\repB5,\repB6,\repB7,\repB8,\repB9}
\text{repC=\repC1,\repC2,\repC3,\repC4,\repC5,\repC6,\repC7,\repC8,\repC9}
\text{repD=\repD1,\repD2,\repD3,\repD4,\repD5,\repD6,\repD7,\repD8,\repD9}
\text{feed=\qf1,\qf2,\qf3,\qf4,\qf5,\qf6,\qf7,\qf8,\qf9}
\text{sizes=\size1,\size2,\size3,\size4,\size5,\size6,\size7,\size8,\size9}


%%%% nombre de questions maximum
\integer{nbqap=items(\confparm1)} %%%%%% nombre de questions à poser
%%%%%%%%% mélange au hasard des questions %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%% ne pas mettre avant car il y a tt les titres des fichiers .inc

\title{Course d'automates DNB SG B}
\observation{codé à partir du sujet zéro sujet-zero-dnb-serie-generale-b-mathematiques.pdf du DNB publié sur éduscol en décembre 2025}
\keywords{#KEYWORD}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\text{choix=\confparm1= ? wims(makelist x for x=1 to 9): \confparm1}
\matrix{STEP= wims(makelist reply x for x in \choix)}

\if{\confparm2=1}{\matrix{STEP=wims(replace internal , by ; in \STEP)}}
%%% question n°8 q200
\if{8 isitemof \choix}{\matrix{STEP=wims(replace internal reply 8 by reply 10,reply 11,reply 12,reply 13 in \STEP)}}
\text{test200=} %% pour feedback
\text{list_cond=8 isitemof \choix and position(8,\choix)=1?1:}
\conditions{\list_cond} %%% initialisation des conditions pour le premier passage, elles sont redéfinies ensuite.
%%%fin question 8
\steps{\STEP}

%%%%%%%%%%%%%%%%
\statement{
\if{\confparm2=2}{<div class="wims_instruction">\instruction</div>
\for{ii=1 to \nbqap}{
  <h2>Question \nq[\choix[\ii]]</h2>
  <div class="wims_question">
    \enonce[\choix[\ii]]
    \if{\qcu[\choix[\ii]]=1}{
      <div class="wimscenter wims_scrollable">
      <table class="wimsborder"><tr><th>
        A. </th><th>B. </th><th> C.</th><th> D.
      </th></tr>
      <tr><td>\repA[\choix[\ii]] </td><td>\repB[\choix[\ii]]</td><td>\repC[\choix[\ii]]</td><td>\repD[\choix[\ii]]</td></tr>
      </table>
      </div>
       <div class="wimscenter">
      <b> \embed{reply \choix[\ii],\sizes[\choix[\ii]]} </b>
      </div>
    }{<br>
    \if{\nq[\choix[\ii]]=200}{
        Réponse&nbsp;: <table class="wimscenter wimsnoborder">
        <tr><td>\embed{reply 10,\size}</td><td></td><td>\embed{reply 11,\size}</td>
        </tr><tr>
        <td><hr></td><td>=</td>
        <td><hr></td>
        </tr><tr>
        <td>\embed{reply 12,\size}</td><td></td><td> \embed{reply 13,\size}</td>
        </tr></table>
        }{
        <label for="reply\choix[\ii]">Réponse&nbsp;&#58;</label> \embed{reply \choix[\ii]}
       \enonceb[\choix[\ii]]
       }
    }
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
    \if{\qcu[\choix[\ii]]=1}{
      <div class="wimscenter wims_scrollable">
      <table class="wimsborder"><tr><th>
      A. </th><th>B. </th><th> C.</th><th> D.
      </th></tr>
      <tr><td>\repA[\choix[\ii]] </td><td>\repB[\choix[\ii]]</td><td>\repC[\choix[\ii]]</td><td>\repD[\choix[\ii]]</td></tr>
      </table>
      </div>
      <div class="wimscenter"><b> \embed{reply\choix[\ii],\sizes[\choix[\ii]]} </b></div>
      }{<br>
      \if{\nq[\choix[\ii]]=200}{
        Réponse&nbsp;: <table class="wimscenter wimsnoborder">
        <tr><td>\embed{reply 10,\size}</td><td></td><td>\embed{reply 11,\size}</td>
        </tr><tr>
        <td><hr></td><td>=</td>
        <td><hr></td>
        </tr><tr>
        <td>\embed{reply 12,\size}</td><td></td><td> \embed{reply 13,\size}</td>
        </tr></table>
        }{<label for="reply\choix[\ii]">Réponse&nbsp;&#58; \embed{reply\choix[\ii],\sizes[\choix[\ii]]
      autofocus}\enonceb[\choix[\ii]]}
      }
  </div>
  }
}
}
}
%%%% 

\text{list_cond=\step>=\affstep8 ?1:}
\conditions{\list_cond}
\answer{}{\rep1}{type=\trep1}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\rep2}{type=\trep2}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\rep3}{type=\trep3}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\rep4}{type=\trep4}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng5;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\rep6}{type=\trep6}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\ng7;Réponse A,Réponse B,Réponse C,Réponse D}{type=radio}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\rep8}{type=\trep8}{option=\confparm3 }
\answer{}{\rep9}{type=\trep9}{option=\confparm3 nolegend noanalyzeprint}
\answer{}{\rep10}{type=\trep8}{option=\confparm3 default=1 }
\answer{}{\rep11}{type=\trep8}{option=\confparm3 default=1 }
\answer{}{\rep12}{type=\trep8}{option=\confparm3 default=1 }
\answer{}{\rep13}{type=\trep8}{option=\confparm3 default=1 }
%%%%% question 200 conditions
\if{\step>=\affstep8}{
  \if{(\rep10 issametext \nomlong1 or \rep10 issametext \nomlong2) and \rep12*\rep11/\rep13=\t200*\s200/\q200  or (\rep11 issametext \nomlong1 or \rep11 issametext \nomlong2) and \rep10*\rep13/\rep12=\t200*\s200/\q200 or (\rep12 issametext \nomlong1 or \rep12 issametext \nomlong2) and \rep10*\rep13/\rep11=\t200*\s200/\q200 or (\rep13 issametext \nomlong1 or \rep13 issametext \nomlong2)  and \rep11*\rep12/\rep10=\t200*\s200/\q200}{
  \text{test200=1}}{\text{test200=0}}
  }
  
\condition{Les rapports sont corrects}{(\rep10 issametext \nomlong1 or \rep10 issametext \nomlong2) and \rep12*\rep11/\rep13=\t200*\s200/\q200  or (\rep11 issametext \nomlong1 or \rep11 issametext \nomlong2) and \rep10*\rep13/\rep12=\t200*\s200/\q200 or (\rep12 issametext \nomlong1 or \rep12 issametext \nomlong2) and \rep10*\rep13/\rep11=\t200*\s200/\q200 or (\rep13 issametext \nomlong1 or \rep13 issametext \nomlong2)  and \rep11*\rep12/\rep10=\t200*\s200/\q200}
%%% question 200

\text{screp=\sc_reply1,\sc_reply2,\sc_reply3,\sc_reply4,\sc_reply5,\sc_reply6,\sc_reply7,
\test200,\sc_reply9}
%%% test200 : question avec condition \sc_reply est vide

%%%% version step+stop
\feedback{\confparm2=1 and \confparm3= }{ les reps : \rep10; \rep11; \rep12; \rep13;
<br>nomlong : \nomlong1 ;\nomlong2
<br>coeff= \t200*\s200/\q200
  \for{tt=1 to \nbqap}{
    \if{\screp[\choix[\tt]]!=\empty and \screp[\choix[\tt]]!=1 }{
      <style>.feedmutu {
    border: 1px solid;
    border-radius: 5px;
    padding: .5em;}
    </style>
      <div class="feedmutu">\feed[\choix[\tt]]</div>
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
      \if{qcu[\chn0]=1}{
      <div class="wimscenter wims_scrollable">
      <table class="wimsborder"><tr>
      <th>A. <br>\repA[\chn0]</th>
      <th>B. <br>\repB[\chn0]</th>
      <th>C. <br>\repC[\chn0]</th>
      <th>D. <br>\repD[\chn0]</th>
      </tr>
      </table>
      </div>}
      <p><u>Indication pour trouver la bonne réponse&nbsp:</u></p>
      <p>\feed[\chn0]</p>
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
    \if{\qcu[\h]=1}{
      \begin{radio}
      \item \repA[\choix[\h]]
      \item \repB[\choix[\h]]
      \item \repC[\choix[\h]]
      \item \repD[\choix[\h]]
      \end{radio}}}}
    }
\text{latexversion=\latexversion \end{enumerate}}
%%%%%%%%%%% fin version latex
