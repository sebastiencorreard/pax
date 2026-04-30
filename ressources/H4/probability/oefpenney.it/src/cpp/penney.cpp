target=partita giocatore computer

#include "observation.inc"
#include "lang_titles.inc"
#include "header.inc"

#include "setup.inc"

#include "lang.inc"

\text{firstpl=nostart}

#if defined TARGET_partita
\integer{displayistru=1}
\if{\confparm3=0}{
  \integer{displayistru=0}
}
#endif
#if defined TARGET_giocatore || defined TARGET_computer
\integer{displaylog=1}
\if{\confparm2=0}{
  \integer{displaylog=1}
}
#endif


#if defined TARGET_computer
\text{seconpl=shuffle(\longlist)}
\text{seconpl=item(1..3,\seconpl)}
\text{imgsec=wims(makelist \leftstr/t\midstr t\rightstr for t in \seconpl)}
\text{imgsec=wims(items2words \imgsec)}
\text{seconpl=wims(items2words \seconpl)}
\text{seconpl=wims(nospace \seconpl)}
#else
\text{seconpl=}
\text{imgsec=}
#endif

\text{coincnt=}

\text{debug=}

\text{faipassi=r1}
\nextstep{\faipassi}
\text{faicond=1}
\conditions{\faicond}
\text{testcond=0}
#if defined TARGET_partita
\text{testcondA=0}
#endif
\text{checkwin=0}
#if defined TARGET_computer
\integer{checkdiff=0}
#endif

\if{\confparm1>0}{
  \integer{rounds=\confparm1}
}{
  \integer{rounds=20}
}

#if defined TARGET_giocatore || defined TARGET_computer
\integer{fscore=0}
\integer{sscore=0}
#endif
\text{estrazione=}
\matrix{allestr=}
\text{imgestr=}
\text{displayestr=}
\text{displayrep=}

\text{first=}
\text{secon=}

\integer{nn=0}

#if defined TARGET_partita
\integer{found=0}
#endif
\integer{waiting=0}

\text{List=wims(makelist \leftstr/t\midstr t\rightstr for t in \llist)}

\integer{nf=0}
\integer{ns=0}


\statement{<div>\name_intro1
#if defined TARGET_giocatore || defined TARGET_computer
    \name_intro2[1] <span class="wims_emph">\rounds</span> \name_intro2[2]
#endif
   </div>

  \if{\step=1}{
#if defined TARGET_giocatore || defined TARGET_partita
    <div class="wims_question">
      \name_intro3
    \embed{r1,35 x 35 x 3}
    </div>
#endif    
#if defined TARGET_computer
    <div class="wims_question">
    \name_choice_list[2] \imgsec.
    \name_intro3
    \embed{r1,35 x 35 x 3}
    </div>
#endif
  }{
    <div class="wimscenter">
#if defined TARGET_computer
    \name_choice_list[2]: \imgsec.
    \if{\coincnt=3}{
      \name_choice_list[1]: \displayrep.
    }
#else
    \name_choice_list[1]: \displayrep.
    \if{\step>1 and \coincnt=3}{
      \name_choice_list[2]: \imgsec.
    }
#endif
    </div>
  }

#if defined TARGET_giocatore
  \if{\step>1 and \coincnt=3}{
#endif  
#if defined TARGET_computer  
  \if{\step>1 and \coincnt=3 and \checkdiff=0}{
#endif  
#if defined TARGET_partita
  \if{\step>1 and \found=0 and \coincnt=3}{
#endif
  
    <div class="spacer">\name_estrazione \nn: \displayestr</div>

#if defined TARGET_partita
    <div>
    <span class="wims_button wims_secondary_button">\embed{reply 2,1}
    </span>
    <span class="wims_button wims_secondary_button">\embed{reply 2,2}
    </span>
    <span class="wims_button oef_exo_renew">\embed{reply 2,3}
    </span>
    </div>
#endif
#if defined TARGET_giocatore || defined TARGET_computer
    <div class="wims_question">
    \if{\nf>\ns}{
      \name_whoscore_list[1]!
    }{
      \name_whoscore_list[2]! 
    }
    <br>
    \name_punteggio: \name_player_list[1] \fscore, \name_player_list[2] \sscore.
    <span class="wims_button oef_exo_renew">\embed{reply 2,1}
    </span>
    <span class="wims_button wims_secondary_button">\embed{reply 2,2}
    </span>
    </div>
#endif
  }
#if defined TARGET_partita
  \if{\step>1 and \waiting>0 and \coincnt=3}{
    <div class="spacer">\name_estrazione \nn: \displayestr</div>
    <div>
    <span class="wims_button wims_secondary_button">\embed{reply 3,1}
    </span>
    <span class="wims_button wims_secondary_button">\embed{reply 3,2}
    </span>
    <span class="wims_button oef_exo_renew">\embed{reply 3,3}
    </span>
    </div>
    }
  \if{\displayistru=1 and \step>1}{
  <div class="wims_instruction spacer">\name_instruction</div>  
  }
#endif
}

\answer{}{\rep;\List}{type=clickfill}{options=default="&nbsp;",align="center",noanalyzeprint}
\answer{AAA}{\avanti;\name_avanti}{type=click}{option=noanalyzeprint,nolegend,nolabel}
#if defined TARGET_partita
\answer{\name_answer}{\analizza;\name_avanti}{type=click}{option=noanalyzeprint,nolegend,nolabel}
#endif

\text{displayrep=wims(items2words \rep)}  
\text{tmpr=wims(replace internal \leftstr/ by in \rep)}
\text{tmpr=wims(replace internal \midstr by in \tmpr)}
\text{tmpr=wims(replace internal \rightstr by in \tmpr)}
\text{tmpr=wims(nonempty items \tmpr)}
\integer{coincnt=items(\tmpr)}
\integer{kk=1}
\text{\r=}
\while{\kk<=\coincnt}{
  \text{tmpstr=}
  \text{r=\r,wims(char 1 of \tmpr[\kk])}
  \integer{kk=\kk+1}
}
\text{r=wims(nonempty items \r)}

#if defined TARGET_giocatore || defined TARGET_computer 
\if{\step<=\rounds}{
  \text{faipassi=r2}
  \text{faicond=1}
}
#endif

\text{firstpl=wims(items2words \r)}
\text{firstpl=wims(nospace \firstpl)}

#if defined TARGET_giocatore || defined TARGET_partita
se si scelgono numeri di monete diverse da 3 punteggio zero
\condition{\name_condition1}{\coincnt=3}{weight=100000}
#else
se si scelgono numeri di monete diverse da 3 o una terna uguale a quella del computer
\text{provaprova=wims(positionof \firstpl in \seconpl)}
\if{\firstpl=\seconpl}{
\integer{checkdiff=1}
}
\condition{\name_condition1}{((\coincnt=3) and (\checkdiff!=1))}{weight=100000}
#endif

#if defined TARGET_giocatore || defined TARGET_computer
\text{testcond=wims(positionof item \avanti in \name_avanti)}
\integer{checkwin=max(\fscore,\sscore)}
\integer{checkwin=2*\checkwin}
\condition{\name_condition2}{\testcond=2 and \checkwin>\rounds}{weight=100000}
\if{\testcond>1}{
  \text{faipassi=}
  \text{faicond=1,2}
  \integer{waiting=1}
}
#endif

So for the first player's choice of 1-2-3
the second player must choose (not-2)-1-2

#if defined TARGET_giocatore || defined TARGET_partita
\text{seconpl=wims(listcomplement \r[2] in \llist)}
\text{imgsec=\leftstr/\seconpl\midstr\seconpl\rightstr,\leftstr/\r[1]\midstr/\r[1]\rightstr,\leftstr/\r[2]\midstr\r[2]\rightstr}
\text{imgsec=wims(items2words \imgsec)}
\text{seconpl=\seconpl \r[1] \r[2]}
\text{seconpl=wims(nospace \seconpl)}
#endif

#if defined TARGET_partita
\text{testcondA=wims(positionof item \avanti in \name_avanti)}
\if{\testcondA=1 or \testcondA=2}{
\integer{waiting=\waiting+1}
\integer{found=2}
}
#endif

#if defined TARGET_partita
\if{\waiting=0}{
  \text{tmp=randitem(\longlist)}
  \text{imgestr=\imgestr,\leftstr/\tmp\midstr\tmp\rightstr}
  \text{estrazione=wims(append word \tmp to \estrazione)}
  \text{estrazione=wims(nospace \estrazione)}
}
#endif
#if defined TARGET_giocatore || defined TARGET_computer
\if{\waiting=0}{
  \integer{found=0}
  \text{estrazione=}
  \text{imgestr=}
  \while{\found=0 and \coincnt=3}{
    \text{tmp=randitem(\longlist)}
    \text{imgestr=\imgestr,\leftstr/\tmp\midstr\tmp\rightstr}
    \text{estrazione=wims(append word \tmp to \estrazione)}
    \text{estrazione=wims(nospace \estrazione)}
#endif

    \text{first=wims(positionof \firstpl in \estrazione)}
    \text{secon=wims(positionof \seconpl in \estrazione)}
    \integer{nf=wims(itemcnt \first)}
    \integer{ns=wims(itemcnt \secon)}
    \integer{found=\nf+\ns}
#if defined TARGET_giocatore || defined TARGET_computer  
  }
  \text{listestr=wims(replace internal \testa by \testa, in \estrazione)}
  \text{listestr=wims(replace internal \croce by \croce, in \listestr)}
  \text{listestr=wims(nonempty items \listestr)}
  \if{\rounds<21}{
    with more than 20 rounds this variable can cause overflow
    \text{listestr=wims(makelist \leftstr/t\midstr t\rightstr for t in \listestr)}
  }
}
\matrix{allestr=wims(append line \listestr to \allestr)}
#endif


#if defined TARGET_partita
\condition{\name_answer}{\testcondA!=1 and \testcondA!=2}

\text{testcond=wims(positionof item \analizza in \name_avanti)}
\condition{\name_answer}{(\nf=1 and \testcond=1) or (\ns=1 and \testcond=2)}{weight=100000}

\if{\found=0}{
\text{faipassi=r2}
\text{faicond=2}
}{
\integer{waiting=\waiting+1}
\text{faipassi=r3}
}
\if{\testcondA=1 or \testcondA=2}
{
\text{faipassi=}
\integer{waiting=\waiting+1}
\integer{found=2}
}
\if{\waiting>1}{
\text{faipassi=}
\text{faicond=3}
}{
\integer{nn=\nn+1}
}
#endif 

#if defined TARGET_giocatore || defined TARGET_computer 

\if{\waiting<1}{
  \integer{nn=\nn+1}
  \if{\nf>\ns}{
    \integer{fscore=\fscore+1}
  }{
    \integer{sscore=\sscore+1}
  }
}
#endif

#if defined TARGET_giocatore || defined TARGET_partita 
\if{\coincnt!=3}{
  \text{faipassi=}
  \text{faicond=1}
}
#endif
#if defined TARGET_computer
\if{\coincnt!=3 or \firstpl=\seconpl}{
  \text{faipassi=}
  \text{faicond=1}
}
#endif

\text{imgestr=wims(nonempty items \imgestr)}
\text{displayestr=wims(items2words \imgestr)}

\help{\name_help}

#if defined TARGET_giocatore || defined TARGET_computer
\text{printallestr=wims(replace internal ; by <br> in \allestr)}
\text{printallestr=wims(replace internal , by  in \printallestr)}
verificare la condizione step
\feedback{\displaylog=1 and \step>2}{<div>\name_feedback_log[1] \nn \name_feedback_log[2]:<div class="spacer">\printallestr</div></div>}
#endif
