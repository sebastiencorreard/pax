target=ineqParticuliere
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a = randint(1,-1)*random(1..10)}
\integer{b = randint(1,-1)*random(1..10)}
\integer{k = randint(1,-1)*random(1..10)}
\integer{signk=\k<0?1:3}
\integer{signku2=\k<0?2:4}
\integer{k1=random(1..10)}
\integer{k2=random(1..10)}
\integer{n=random(2,4)}
\rational{zero=-\b/\a}
\function{u=\a*x + \b}
\function{u=\a==1?x + \b}
\function{u=\a==-1?-x + \b}

/** expression de signe evident constant **/
\text{ff=\k*(\u)^\n,\k1*(\u)^\n + \k2,-\k1*(\u)^\n - \k2}
\integer{cas=random(1..3)}

\text{f=item(\cas,\ff)}
\text{tf=texmath(\f)}
\text{u=texmath(\u)}

\text{ensR=\(\RR\;)}
\text{empt=\(\emptyset\;)}
\text{Rminus=\(\RR\setminus\{\zero\})}
\text{single=\(\{\zero\})}
\text{choix=\ensR,\empt,\Rminus,\single}

/** "rep" : codage des signes de \f**/
/** 1: strictement négative**/
/** 2 : négative ou nulle**/
/** 3 : strictement positive**/
/** 4 : positive ou nulle**/
\text{reps=\signku2,3,1}
\text{rep=item(\cas,\reps)}

/** codage du symbole d'inégalité de l'inéquation */
\text{ineg=randint(1..4)}
\text{symb=item(\ineg,<,\leq,>,\geq)}

/** codage du numéro i de la bonne réponse dans la liste de choix **/

\if{\rep==1}{\integer{i=\ineg<3?1:2}}
\if{\rep==3}{\integer{i=\ineg<3?2:1}}
\if{\rep==2}{
\integer{i=\ineg==1?3}
\integer{i=\ineg==2?1}
\integer{i=\ineg==3?2}
\integer{i=\ineg==4?4}
}
\if{\rep==4}{
\integer{i=\ineg==1?2}
\integer{i=\ineg==2?4}
\integer{i=\ineg==3?3}
\integer{i=\ineg==4?1}
}

\statement{
  <div class="wims_question">
  <p>\name_question[1;] &nbsp;\(\tf \symb 0 \)&nbsp;
  \name_question[2;1] \(\tf\) \name_question[2;2]
  </p><p>
  \name_question[3;] :</p>
  <div class="wimscenter">\embed{reply1}.</div>
  </div>
}

\answer{}{\i ; \choix}{type=radio}

/** feedback en cas de mauvaises réponses **/

\feedback{\reply1 notsametext item(\i,\choix)}{
<div class="macorrection">
<strong>\name_explanation :</strong>
<br>
\if{\cas==1 and \k>1}{\name_question1[1] \((\u)^\n \geq 0 \) \name_question1[2] \(x\).<br>
\name_so \name_question1[3] \(k\) \name_question1[4], \(\k(\u)^\n \geq 0 \).<br>
}
\if{\cas==1 and \k<-1}{\name_question1[1] \((\u)^\n \geq 0 \) \name_question1[2] \(x\).<br>
\name_so \name_question1[3] \(\k\) \name_question1[5], \(\k(\u)^\n \leq 0 \).<br>
 }
\if{\cas==1 and \k==-1}{\name_question1[1] \((\u)^\n \geq 0 \) \name_question1[2] \(x\)
\name_so \(-(\u)^\n \leq 0 \).<br>
 }
\if{\cas==1 and \k==1}{\name_question1[1] \((\u)^\n \geq 0 \) \name_question1[2] \(x\)<br>.
 }

\if{\cas==2}{\name_question1[1] \(\k1(\u)^\n \geq 0\) \name_question1[2] \(x\).<br>
\name_as \(\k2 > 0 \), \name_onehas
\( \k1(\u)^\n + \k2 > 0 \) \name_question1[2] \(x\).<br>
}
\if{\cas==3}{ \name_question1[1] \((\u)^\n \geq 0\) \name_question1[2] \(x\).<br>
 \name_so \(-\k1(\u)^\n \leq 0\).
 \name_as \(-\k2 < 0\) alors \( -\k1(\u)^\n -\k2 < 0\) \name_question1[2] \(x\).
}
\if{\i==1}{<br>\name_conclusion[1] \(\tf\symb 0\).}
\if{\i==2}{<br>\name_conclusion[2] \(\tf\symb 0\).}
\if{\i==3}{<br>\name_feed[1] \({}x = \zero\) \name_onehas \(\tf = 0\),
  <br>\name_feed[2] \({}\zero) \name_feed[3] \(\tf\symb 0\). }
\if{\i==4}{<br>
  \name_feed[1] \({}x = \zero\) \name_onehas \(\tf = 0\),
  <br>\name_feed[4] \({}x = \zero\) \name_feed[3] \(\tf\symb 0\).}
</div>
}
