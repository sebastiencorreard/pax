target=tabprop2
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\computeanswer{yes}
\format{html}
\precision{10000}
\integer{prop= randint(2..9)}
\text{tout=shuffle(1,2,3,4,5,6,7,8,9)}
\integer{a=\tout[1]}
\integer{b=\tout[2]}
\integer{c=\tout[3]}
\integer{aa=\a*\prop}
\integer{bb=\b*\prop}
\integer{cc=\c*\prop}
\integer{dd=\d*\prop}
\integer{ee=\e*\prop}
\integer{ff=\f*\prop}
\integer{faux=random(0,0,1,2,3)}
\integer{aa=\faux=1 ? 2*\aa}
\integer{bb=\faux=2 ? \bb+2}
\integer{cc=\faux=3? 2*\bb-2}

\text{rep=\faux=0? \ouinon[1]:\ouinon[2]}
\steps{choice 1
reply 1}
\statement{\if{\step=1}{\name_question1?}
<table class="wimscenter wimsborder">
<tr><td>\a</td><td>\b</td><td>\c</td></tr>
<tr><td>\aa</td><td>\bb</td>
<td>\cc</td>
</tr>
</table>
\if{\step=2}{\if{\faux=0}{\name_question2[1;] \name_question2[2;]? }
  {\name_question2[3;]: \name_question2[4;]}
}
}
\choice{}{\rep}{\ouinon[1],\ouinon[2]}
\answer{}{\proport}{type=nocase}
\text{reponse=wims(replace internal et by $ $ in \proport)}
\text{reponse=wims(replace internal
 by $ $ in \reponse)}
\text{reponse=wims(replace internal er by $ $ in \reponse)}
\text{reponse=wims(replace internal ère by $ $ in \reponse)}
\text{reponse=wims(replace internal ere by $ $ in \reponse)}
\text{reponse=wims(replace internal eme by $ $ in \reponse)}
\text{reponse=wims(replace internal ème by $ $ in \reponse)}
\text{reponse=wims(replace internal - by $ $ in \reponse)}
\text{reponse=wims(replace internal & by $ $ in \reponse)}
\text{reponse=wims(items2words \reponse)}
\text{reponse=wims(nospace \reponse)}
\text{n=wims(charcnt \reponse)}
\condition{}{(\faux=0 and \proport=\prop) or (\faux<>0 and \faux isin \proport
and \n=2)}
\feedback{\n=1 and \faux<>0}{\name_feed[1;] }
\feedback{\n=3 and \faux<>0}{\name_feed[2;]}
\feedback{\n=2 and \faux<>0 and \faux notin \proport}{\name_feed[3;]
\if{\faux=1}{ \(\frac{\bb}{\b}=\frac{\cc}{\c}).}
\if{\faux=2}{ \(\frac{\aa}{\a}=\frac{\cc}{\c}).}
\if{\faux=3}{ \(\frac{\aa}{\a}=\frac{\bb}{\b}).}
\name_feed2 }
