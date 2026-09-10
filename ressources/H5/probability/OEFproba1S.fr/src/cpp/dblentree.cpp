target=tableau1 tableau2 tableau3 tableau4 tableau5 tableau6

#include "header.inc"

\precision{400}

#if defined TARGET_tableau1
# define NUM 1
#endif
#if defined TARGET_tableau2
# define NUM 2
#endif
#if defined TARGET_tableau3
#define NUM 3
#endif
#if defined TARGET_tableau4
# define NUM 4
#endif
#if defined TARGET_tableau5
# define NUM 5
#endif
#if defined TARGET_tableau6
# define NUM 6
#endif

#include "lang_titles.inc"
\integer{choix=randint(1..4)}
\integer{k=randitem(1,2)}
#if defined TARGET_tableau1
\keywords{contingency_table}
\integer{n=1}
\integer{coef=100}
\text{type=personnes}
#endif
#if defined TARGET_tableau2
\keywords{contingency_table,conditional_frequency}
\integer{n=randint(1..10)}
\integer{coef=100}
\text{type=personnes}
#endif
#if defined TARGET_tableau3
\keywords{contingency_table,conditional_frequency}
\integer{n=randint(1..10)}
\integer{coef=100}
\text{type=%}
#endif
#if defined TARGET_tableau4
\keywords{contingency_table,conditional_frequency}
\integer{n=randint(1..10)}
\integer{coef=100}
#endif
#if defined TARGET_tableau5
\keywords{contingency_table,conditional_frequency}
\integer{n=randint(1..10)}
\integer{coef=100}
#endif
#if defined TARGET_tableau6
\keywords{contingency_table,conditional_frequency}
\integer{n=randint(1..10)}
\integer{coef=100}
#endif

#include "lang.inc"

\integer{total=100}
integer{totalA1=randint(\total/2..\total-1)}
integer{totalA2=\total - \totalA1}
text{l=\totalA1,\totalA2}
text{ind=shuffle(2)}
integer{totalA1=\l[\ind[1]]}
integer{totalA2=\l[\ind[2]]}
integer{nba1b1=randint(\totalA1 /2..\totalA1-1)}
integer{nba1b2=\totalA1-\nba1b1}
integer{nba2b1=randint(\totalA2 /2..\totalA2-1)}
integer{nba2b2=\totalA2-\nba2b1}
integer{totalB1=\nba1b1+\nba2b1}
integer{totalB2=\nba1b2+\nba2b2}
Tirage des effectifs de chaque classe lorsque total=100 pour avoir au moins 2 pourcentages entiers
\text{listeff=4,5,8,10,16,20,25,32,40}
\text{v=slib(data/random 2,item,\listeff)}
\if{random(0,1)=1}{
  \integer{totalA1=\v[1]}
  \integer{totalB1=\v[2]}
  \integer{totalA2=\total - \totalA1}
  \integer{totalB2=\total - \totalB1}
  \text{l=\totalA1,\totalA2}
  \integer{mineff=\total+1-(\totalA1+\totalB1)}
  \integer{maxeff=\total-max(\totalA1,\totalB1)-1}
  \integer{nba2b2=randint(\mineff..\maxeff)}
  \integer{nba1b1=\totalA1+\totalB1+\nba2b2-\total}
  \integer{nba1b2=\totalA1-\nba1b1}
  \integer{nba2b1=\totalA2-\nba2b2}
  }
  {
  \integer{totalA2=\v[1]}
  \integer{totalB2=\v[2]}
  \integer{totalA1=\total - \totalA2}
  \integer{totalB1=\total - \totalB2}
  \integer{mineff=\total+1-(\totalA2+\totalB2)}
  \integer{maxeff=\total-max(\totalA2,\totalB2)-1}
  \integer{nba1b1=randint(\mineff..\maxeff)}
  \integer{nba2b2=\totalA2+\totalB2+\nba1b1-\total}
  \integer{nba2b1=\totalA2-\nba2b2}
  \integer{nba1b2=\totalA1-\nba1b1}
  }

\text{info=\total,\totalA1,\totalA2,\totalB1,\totalB2,\nba1b1, \nba1b2,\nba2b1,\nba2b2}
\integer{itotal=1}
\integer{itotalA1=2}
\integer{itotalA2=3}
\integer{itotalB1=4}
\integer{itotalB2=5}
\integer{inba1b1=6}
\integer{inba1b2=7}
\integer{inba2b1=8}
\integer{inba2b2=9}
\integer{ipcta1b1=10}
\integer{ipcta1b2=11}
\integer{ipcta2b1=12}
\integer{ipcta2b2=13}
\integer{imrgA1b1=14}
\integer{imrgA1b2=15}
\integer{imrgA2b1=16}
\integer{imrgA2b2=17}
\integer{imrga1B1=18}
\integer{imrga1B2=19}
\integer{imrga2B1=20}
\integer{imrga2B2=21}
\integer{ipcttotalA1=22}
\integer{ipcttotalA2=23}
\integer{ipcttotalB1=24}
\integer{ipcttotalB2=25}

\rational{pcttotal=100}
\rational{pcttotalA1=\totalA1 }
\rational{pcttotalA2=\totalA2 }
\rational{pcttotalB1=\totalB1 }
\rational{pcttotalB2=\totalB2 }
\rational{pctnba1b1=\nba1b1 }
\rational{pctnba1b2=\nba1b2 }
\rational{pctnba2b1=\nba2b1 }
\rational{pctnba2b2=\nba2b2 }
\real{margeA1b1= \coef*\nba1b1 / \totalA1}
\real{margeA1b1arr= round(\margeA1b1*1000)/1000}
\text{apprA1b1=abs(\margeA1b1arr-\margeA1b1)>0.0001?\name_approx}
\real{margeA1b2= \coef*\nba1b2 / \totalA1}
\real{margeA1b2arr= \coef - \margeA1b1arr}
\real{margeA2b1= \coef*\nba2b1 / \totalA2}
\real{margeA2b1arr= round(\margeA2b1*1000)/1000}
\real{margeA2b2= \coef*\nba2b2 / \totalA2}
\real{margeA2b2arr= \coef - \margeA2b1arr}
\real{margea1B1= \coef*\nba1b1 / \totalB1}
\real{margea1B1arr= round(\margea1B1*1000)/1000}
\text{appra1B1=abs(\margea1B1arr-\margea1B1)>0.0001?\name_approx}
\real{margea1B2= \coef*\nba1b2 / \totalB2}
\real{margea1B2arr=round(\margea1B2*1000)/1000}
\text{appra1B2=abs(\margea1B2arr-\margea1B2)>0.0001?\name_approx}
\real{margea2B1= \coef*\nba2b1 / \totalB1}
\real{margea2B2= \coef*\nba2b2 / \totalB2}
\real{margea2B1arr= \coef - \margea1B1arr}
\real{margea2B2arr= \coef - \margea1B2arr}
\rational{total=\total * \n}
\rational{totalA1=\totalA1 * \n}
\rational{totalA2=\totalA2 * \n}
\rational{totalB1=\totalB1 * \n}
\rational{totalB2=\totalB2 * \n}
\rational{nba1b1=\nba1b1 * \n}
\rational{nba1b2=\nba1b2 * \n}
\rational{nba2b1=\nba2b1 * \n}
\rational{nba2b2=\nba2b2 * \n}

\text{info=\total,\totalA1,\totalA2,\totalB1,\totalB2,
\nba1b1, \nba1b2,\nba2b1,\nba2b2,
\pctnba1b1,\pctnba1b2,\pctnba2b1,\pctnba2b2,
\margeA1b1arr,\margeA1b2arr,\margeA2b1arr,\margeA2b2arr,
\margea1B1arr,\margea1B2arr,\margea2B1arr,\margea2B2arr,
\pcttotalA1,\pcttotalA2,\pcttotalB1,\pcttotalB2}

#if (defined TARGET_tableau1  || defined TARGET_tableau2  || defined TARGET_tableau3 )
\if{\k=1}{
\integer{pluriel=\info[\inba2b2]>1?1:2}
\text{tintro=
\name_intro1 \info[\itotal] \name_intro2 \name_classeA1[\choix+4]\name_classeA1[\choix] \name_and \name_classeA2[\choix+4]\name_classeA2[\choix].

\name_intro3 \info[\itotalA1] \name_classeA1[\choix], \name_intro4 \apprA1b1 \info[\imrgA1b1] % \name_intro5[1] \name_classeB1[\choix+4]\name_classeB1[\choix]
 \name_and \info[\inba2b2] \name_intro6[\pluriel] \name_classeA2[\choix] \name_classeB2[\choix].
}}
\if{\k=2}{
\integer{pluriel=\info[\inba1b1]>1?1:2}
\text{tintro=
\name_intro1 \info[\itotal] \name_intro2 \name_classeA1[\choix+4]\name_classeA1[\choix] \name_and \name_classeA2[\choix+4]\name_classeA2[\choix].
\name_intro3 \info[\itotalB2] \name_classeB2[\choix], \name_intro4 \appra1B2 \info[\imrga1B2] % \name_intro5[1] \name_classeA1[\choix+4]\name_classeA1[\choix]
 \name_and \info[\inba1b1] \name_intro5[\pluriel] \name_classeA1[\choix] \name_classeB1[\choix].
}}
#endif

#if defined TARGET_tableau4
\integer{pluriel=\info[\inba1b2]>1?1:2}
\text{tintro=
\name_intro1 \name_classeB1[\choix+4]\name_classeB1[\choix] \name_and \name_classeB2[\choix+4]\name_classeB2[\choix].
\name_intro2 \info[\itotalB1] \name_classeB1[\choix], \name_intro3 \appra1B1 \info[\imrga1B1] % \name_classeA1[\choix+4]\name_classeA1[\choix]
 \name_intro4 \info[\ipcttotalB2]% \name_classeB2[\choix+4]\name_classeB2[\choix], \name_intro3 \info[\inba1b2] \name_intro5[\pluriel] \name_classeA1[\choix].
}
#endif

#if defined TARGET_tableau5
\integer{pluriel=\info[\inba1b1]>1?1:2}
\text{tintro=
\name_intro1 \name_classeA1[\choix+4]\name_classeA1[\choix] \name_and \name_classeA2[\choix+4]\name_classeA2[\choix].
\name_intro2 \info[\itotalA1] \name_classeA1[\choix], \name_intro3 \apprA1b1 \info[\imrgA1b1] % \name_classeB1[\choix+4]\name_classeB1[\choix]
 \name_intro4 \info[\ipcttotalA2]% \name_classeA2[\choix+4]\name_classeA2[\choix], \name_intro3 \info[\inba2b1] \name_intro5[\pluriel] \name_classeB1[\choix].
}
#endif
#if defined TARGET_tableau6
\integer{pluriel=\info[\inba2b1]>1?1:2}
 \text{tintro=
\name_intro1 \name_classeA1[\choix+4]\name_classeA1[\choix] \name_and \name_classeA2[\choix+4]\name_classeA2[\choix].
\name_intro2 \info[\itotalA1] \name_classeA1[\choix], \name_intro3 \apprA1b1 \info[\imrgA1b1] % \name_classeB1[\choix+4]\name_classeB1[\choix]
 \name_intro4 \info[\ipcttotalA2]% \name_classeA2[\choix+4]\name_classeA2[\choix], \name_intro3 \info[\inba2b1]  \name_intro5[\pluriel] \name_classeB1[\choix].
}
#endif
#if defined TARGET_tableau1
\statement{
<p>
\tintro
</p><p>
\name_statement
</p>
<table class="wimscenter wimsborder"><caption>\name_caption</caption>
<tr><th> &nbsp;</th><th>\name_classeA1[\choix]</th><th>\name_classeA2[\choix]</th><th>\name_total</th></tr>
<tr><th> \name_classeB1[\choix]</th><td>\embed{reply1,4}</td><td>\embed{reply2,4}</td><td>\embed{reply3,4}</td></tr>
<tr><th> \name_classeB2[\choix]</th><td>\embed{reply4,4}</td><td>\embed{reply5,4}</td><td>\embed{reply6,4}</td></tr>
<tr><th> \name_total</th><td>\embed{reply7,4}</td><td>\embed{reply8,4}</td><td>\embed{reply9,4}</td></tr>
</table>
}
\answer{\name_reply 1}{\info[\inba1b1]}{type=numeric}{option=absolute}
\answer{\name_reply 2}{\info[\inba2b1]}{type=numeric}{option=absolute}
\answer{\name_reply 3}{\info[\itotalB1]}{type=numeric}{option=absolute}
\answer{\name_reply 4}{\info[\inba1b2]}{type=numeric}{option=absolute}
\answer{\name_reply 5}{\info[\inba2b2]}{type=numeric}{option=absolute}
\answer{\name_reply 6}{\info[\itotalB2]}{type=numeric}{option=absolute}
\answer{\name_reply 7}{\info[\itotalA1]}{type=numeric}{option=absolute}
\answer{\name_reply 8}{\info[\itotalA2]}{type=numeric}{option=absolute}
\answer{\name_reply 9}{\info[\itotal]}{type=numeric}{option=absolute}

#endif

#if (defined TARGET_tableau2 || defined TARGET_tableau4 )

\statement{
<p>
\tintro
</p><p>
\name_statement
</p>
<table class="wimscenter wimsborder"><caption>\name_caption</caption>
<tr><th> &nbsp;</th><th>\name_classeA1[\choix]</th><th>\name_classeA2[\choix]</th><th>\name_total</th></tr>
<tr><th> \name_classeB1[\choix]</th><td>\embed{reply1,4}</td><td>\embed{reply2,4}</td><td>\embed{reply3,4}</td></tr>
<tr><th> \name_classeB2[\choix]</th><td>\embed{reply4,4}</td><td>\embed{reply5,4}</td><td>\embed{reply6,4}</td></tr>
<tr><th> \name_total</th><td>\embed{reply7,4}</td><td>\embed{reply8,4}</td><td>\embed{reply9,4}</td></tr>
</table>
<table class="wimscenter wimsborder"><caption>\name_caption1</caption>
<tr><th> &nbsp;</th><th>\name_classeA1[\choix]</th><th>\name_classeA2[\choix]</th><th>\name_total</th></tr>
<tr><th> \name_classeB1[\choix]</th><td>\embed{reply10,4}</td><td>\embed{reply11,4}</td><td>100%</td></tr>
<tr><th> \name_classeB2[\choix]</th><td>\embed{reply12,4}</td><td>\embed{reply13,4}</td><td>100%</td></tr>
</table>
<div class="wims_instruction">\name_consig</div>
}
\answer{\name_reply 1}{\info[\inba1b1]}{type=numeric}{option=absolute}
\answer{\name_reply 2}{\info[\inba2b1]}{type=numeric}{option=absolute}
\answer{\name_reply 3}{\info[\itotalB1]}{type=numeric}{option=absolute}
\answer{\name_reply 4}{\info[\inba1b2]}{type=numeric}{option=absolute}
\answer{\name_reply 5}{\info[\inba2b2]}{type=numeric}{option=absolute}
\answer{\name_reply 6}{\info[\itotalB2]}{type=numeric}{option=absolute}
\answer{\name_reply 7}{\info[\itotalA1]}{type=numeric}{option=absolute}
\answer{\name_reply 8}{\info[\itotalA2]}{type=numeric}{option=absolute}
\answer{\name_reply 9}{\info[\itotal]}{type=numeric}{option=absolute}
\answer{\name_reply 10}{\info[\imrga1B1]}{type=numeric}{option=absolute}
\answer{\name_reply 11}{\info[\imrga2B1]}{type=numeric}{option=absolute}
\answer{\name_reply 12}{\info[\imrga1B2]}{type=numeric}{option=absolute}
\answer{\name_reply 13}{\info[\imrga2B2]}{type=numeric}{option=absolute}

#endif
#if (defined TARGET_tableau3 || defined TARGET_tableau5 )

\statement{
\tintro
<p>
\name_statement
</p>
<table class="wimscenter wimsborder"><caption>\name_caption</caption>
<tr><th> &nbsp;</th><th>\name_classeA1[\choix]</th><th>\name_classeA2[\choix]</th><th>\name_total</th></tr>
<tr><th> \name_classeB1[\choix]</th><td>\embed{reply1,4}</td><td>\embed{reply2,4}</td><td>\embed{reply3,4}</td></tr>
<tr><th> \name_classeB2[\choix]</th><td>\embed{reply4,4}</td><td>\embed{reply5,4}</td><td>\embed{reply6,4}</td></tr>
<tr><th> \name_total</th><td>\embed{reply7,4}</td><td>\embed{reply8,4}</td><td>\embed{reply9,4}</td></tr>
</table>
<table class="wimscenter wimsborder"><caption>\name_caption1</caption>
<tr><th> &nbsp;</th><th>\name_classeA1[\choix]</th><th>\name_classeA2[\choix]</th></tr>
<tr><th> \name_classeB1[\choix]</th><td>\embed{reply10,4}</td><td>\embed{reply11,4}</td></tr>
<tr><th> \name_classeB2[\choix]</th><td>\embed{reply12,4}</td><td>\embed{reply13,4}</td></tr>
<tr><th> \name_total</th><td>100%</td><td>100%</td></tr>
</table>
<div class="wims_instruction">\name_consig</div>
}
\answer{\name_reply 1}{\info[\inba1b1]}{type=numeric}{option=absolute}
\answer{\name_reply 2}{\info[\inba2b1]}{type=numeric}{option=absolute}
\answer{\name_reply 3}{\info[\itotalB1]}{type=numeric}{option=absolute}
\answer{\name_reply 4}{\info[\inba1b2]}{type=numeric}{option=absolute}
\answer{\name_reply 5}{\info[\inba2b2]}{type=numeric}{option=absolute}
\answer{\name_reply 6}{\info[\itotalB2]}{type=numeric}{option=absolute}
\answer{\name_reply 7}{\info[\itotalA1]}{type=numeric}{option=absolute}
\answer{\name_reply 8}{\info[\itotalA2]}{type=numeric}{option=absolute}
\answer{\name_reply 9}{\info[\itotal]}{type=numeric}{option=absolute}
\answer{\name_reply 10}{\info[\imrgA1b1]}{type=numeric}{option=absolute}
\answer{\name_reply 11}{\info[\imrgA2b1]}{type=numeric}{option=absolute}
\answer{\name_reply 12}{\info[\imrgA1b2]}{type=numeric}{option=absolute}
\answer{\name_reply 13}{\info[\imrgA2b2]}{type=numeric}{option=absolute}

#endif

#if defined TARGET_tableau6
\statement{
\tintro
<p>
\name_statement
</p>

<table class="wimscenter wimsborder"><caption>\name_caption</caption>
<tr><th> &nbsp;</th><th>\name_classeA1[\choix]</th><th>\name_classeA2[\choix]</th><th>\name_total</th></tr>
<tr><th> \name_classeB1[\choix]</th><td>\embed{reply1,4}</td><td>\embed{reply2,4}</td><td>\embed{reply3,4}</td></tr>
<tr><th> \name_classeB2[\choix]</th><td>\embed{reply4,4}</td><td>\embed{reply5,4}</td><td>\embed{reply6,4}</td></tr>
<tr><th> \name_total</th><td>\embed{reply7,4}</td><td>\embed{reply8,4}</td><td>\embed{reply9,4}</td></tr>
</table>
<table class="wimscenter wimsborder"><caption>\name_caption1</caption>
<tr><th> &nbsp;</th><th>\name_classeA1[\choix]</th><th>\name_classeA2[\choix]</th><th>\name_total</th></tr>
<tr><th> \name_classeB1[\choix]</th><td>\embed{reply10,4}</td><td>\embed{reply11,4}</td><td>100%</td></tr>
<tr><th> \name_classeB2[\choix]</th><td>\embed{reply12,4}</td><td>\embed{reply13,4}</td><td>100%</td></tr>
</table>
<table class="wimscenter wimsborder"><caption>\name_caption1</caption>
<tr><th> &nbsp;</th><th>\name_classeA1[\choix]</th><th>\name_classeA2[\choix]</th></tr>
<tr><th> \name_classeB1[\choix]</th><td>\embed{reply14,4}</td><td>\embed{reply15,4}</td></tr>
<tr><th> \name_classeB2[\choix]</th><td>\embed{reply16,4}</td><td>\embed{reply17,4}</td></tr>
<tr><th>\name_total</th><td>100%</td><td>100%</td></tr>
</table>

<ol>
<li>\name_intro2 \name_classeA1[\choix], \name_intro6 \name_classeB2[\choix] ? \embed{reply18,5} %</li>
<li>\name_intro2 \name_classeB1[\choix], \name_intro6 \name_classeA2[\choix] ? \embed{reply19,5} %</li>
<li>\name_intro7 \name_classeB1[\choix] \name_classeA1[\choix] ?\embed{reply20,5} %</li>
</ol>
<div class="wims_instruction">\name_consig</div>
}
\answer{\name_reply 1}{\info[\inba1b1]}{type=numeric}{option=absolute}
\answer{\name_reply 2}{\info[\inba2b1]}{type=numeric}{option=absolute}
\answer{\name_reply 3}{\info[\itotalB1]}{type=numeric}{option=absolute}
\answer{\name_reply 4}{\info[\inba1b2]}{type=numeric}{option=absolute}
\answer{\name_reply 5}{\info[\inba2b2]}{type=numeric}{option=absolute}
\answer{\name_reply 6}{\info[\itotalB2]}{type=numeric}{option=absolute}
\answer{\name_reply 7}{\info[\itotalA1]}{type=numeric}{option=absolute}
\answer{\name_reply 8}{\info[\itotalA2]}{type=numeric}{option=absolute}
\answer{\name_reply 9}{\info[\itotal]}{type=numeric}{option=absolute}
\answer{\name_reply 10}{\info[\imrga1B1]}{type=numeric}{option=absolute}
\answer{\name_reply 11}{\info[\imrga2B1]}{type=numeric}{option=absolute}
\answer{\name_reply 12}{\info[\imrga1B2]}{type=numeric}{option=absolute}
\answer{\name_reply 13}{\info[\imrga2B2]}{type=numeric}{option=absolute}
\answer{\name_reply 14}{\info[\imrgA1b1]}{type=numeric}{option=absolute}
\answer{\name_reply 15}{\info[\imrgA2b1]}{type=numeric}{option=absolute}
\answer{\name_reply 16}{\info[\imrgA1b2]}{type=numeric}{option=absolute}
\answer{\name_reply 17}{\info[\imrgA2b2]}{type=numeric}{option=absolute}
\answer{}{\info[\imrgA1b2]}{type=numeric}{option=absolute}
\answer{}{\info[\imrga2B1]}{type=numeric}{option=absolute}
\answer{}{\info[\ipcta1b1]}{type=numeric}{option=absolute}
#endif
