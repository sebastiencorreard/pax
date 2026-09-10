target=interpret arbre1 arbre2

#include "header.inc"

\precision{100}
\keywords{contingency_table,conditional_frequency}

#if defined TARGET_arbre1
#define NUM 1
#endif
#if defined TARGET_arbre2
#define NUM 2
#endif

#include "lang_titles.inc"

\integer{choix=randint(1..4)}
\integer{n=randint(1..20)}
\integer{coef=100}
\text{type=personnes}

#include "lang.inc"

#if defined TARGET_arbre1
\text{liba=\name_classeA1[\choix]}
\text{libb=\name_classeA2[\choix]}
\text{lib1=\name_classeB1[\choix]}
\text{lib2=\name_classeB2[\choix]}
#endif

#if defined TARGET_arbre2
\text{lib1=\name_classeA1[\choix]}
\text{lib2=\name_classeA2[\choix]}
\text{liba=\name_classeB1[\choix]}
\text{libb=\name_classeB2[\choix]}
#endif

\integer{total=100}
\integer{totalA1=randint(\total/2..\total-1)}
\integer{totalA2=\total - \totalA1}
\text{l=\totalA1,\totalA2}
\text{ind=shuffle(2)}
\integer{totalA1=\l[\ind[1]]}
\integer{totalA2=\l[\ind[2]]}
\integer{nba1b1=randint(\totalA1 /2..\totalA1-1)}
\integer{nba1b2=\totalA1-\nba1b1}
\integer{nba2b1=randint(\totalA2 /2..\totalA2-1)}
\integer{nba2b2=\totalA2-\nba2b1}
\integer{totalB1=\nba1b1+\nba2b1}
\integer{totalB2=\nba1b2+\nba2b2}

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
\real{margeA1b2= \coef*\nba1b2 / \totalA1}
\real{margeA2b1= \coef*\nba2b1 / \totalA2}
\real{margeA2b2= \coef*\nba2b2 / \totalA2}
\real{margea1B1= \coef*\nba1b1 / \totalB1}
\real{margea1B2= \coef*\nba1b2 / \totalB2}
\real{margea2B1= \coef*\nba2b1 / \totalB1}
\real{margea2B2= \coef*\nba2b2 / \totalB2}
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
\margeA1b1,\margeA1b2,\margeA2b1,\margeA2b2,
\margea1B1,\margea1B2,\margea2B1,\margea2B2,
\pcttotalA1,\pcttotalA2,\pcttotalB1,\pcttotalB2}
\text{infoar=}
\for{i=1 to 25}{
 \integer{x=\info[\i]*100}
 \integer{x=\x/100}
 \text{infoar=wims(append item \x to \infoar)}
}
\text{info=\infoar}

\text{dessinarbre=
 xrange 0,10
 yrange -10,10
 text black,0,0,medium,*

 arrow 1,1,4,4,5,black
 text blue,3,5,medium,\lib1

 arrow 5,4.5,6.5,7,5,black
 text red,7,8,medium,\liba
 arrow 5,4.5,6.5,2,5,black
 text gray,7,2.5,medium,\libb

 arrow 1,-1,4,-4,5,black
 text green,3,-4,medium,\lib2

 arrow 5,-4.5,6.5,-7,5,black
 text gray,7,-6.5,medium,\libb
 arrow 5,-4.5,6.5,-2,5,black
 text red,7,-1,medium,\liba

 }
\text{dessin=draw(300,300
\dessinarbre)}
\text{pos_m=r1,60 x 100;r2,60 x 180;r3,150 x 50;r4,150 x 90;r5,150 x 190;r6,150 x 230}

\statement{
#if defined TARGET_interpret
<p>
\name_groupe[\choix] \name_statement[1] \total \name_individu[\choix] \name_statement[2]:
</p>
<table class="wimsborder wimscenter"><caption>\name_caption</caption>
<tr><th> &nbsp;</th><th>\name_classeA1[\choix]</th><th>\name_classeA2[\choix]</th><th>\name_total</th></tr>
<tr><th> \name_classeB1[\choix]</th><td>\nba1b1</td><td>\nba2b1</td><td>\totalB1</td></tr>
<tr><th> \name_classeB2[\choix]</th><td>\nba1b2</td><td>\nba2b2</td><td>\totalB2</td></tr>
<tr><th> \name_total</th><td>\totalA1</td><td>\totalA2</td><td>\total</td></tr>
</table>
\name_consigne:
<ol>
<li>\embed{reply1,4}% \name_of \name_individu[\choix] \name_cond1 \name_classeB1[\choix].</li>
<li>\name_cond2 \name_classeB1[\choix],\embed{reply2,4} % \name_cond1 \name_classeA2[\choix].</li>
<li>\embed{reply3,4} % \name_of \name_classeA2[\choix] \name_cond1 \name_classeB2[\choix].</li>
<li>\embed{reply4,4} % \name_of \name_individu[\choix] \name_cond1 \name_classeA1[\choix] \name_classeB2[\choix].</li>
</ol>
}
\answer{\name_reply 1}{\info[\ipcttotalB1]}{type=numeric}
\answer{\name_reply 2}{\info[\imrga2B1]}{type=numeric}
\answer{\name_reply 3}{\info[\imrgA2b2]}{type=numeric}
\answer{\name_reply 4}{\info[\ipcta1b2]}{type=numeric}
\feedback{\reply1<>\info[\ipcttotalB1]}{\name_feedback[1] 1, \name_feedback[2] \total
\name_feedback[3] \totalB1, \name_feedback[4] \(\frac{\totalB1}{\total}\times 100\) %}
\feedback{\reply2<>\info[\imrga2B1]}{\name_feedback[1] 2, \name_feedback[2] \totalB1
\name_feedback[3] \nba2b1, \name_feedback[4] \(\frac{\nba2b1}{\totalB1}\times 100\) %}
\feedback{\reply3<>\info[\imrgA2b2]}{\name_feedback[1] 3, \name_feedback[2] \totalA2
\name_feedback[3] \nba2b2, \name_feedback[4] \(\frac{\nba2b2}{\totalA2}\times 100\) %}
\feedback{\reply4<>\info[\ipcta1b2]}{\name_feedback[1] 4, \name_feedback[2] \total
\name_feedback[3] \nba1b2, \name_feedback[4] \(\frac{\nba1b2}{\total}\times 100\) %}
#else
<div class="wims_columns">
 <div class="medium_size img_col">\special{imagefill \dessin,300 x 300, 45x25
\pos_m
}</div>
 <div class="medium_size text_col">
\name_groupe[\choix] \name_statement[1] \total \name_individu[\choix] \name_statement[2]:
<table class="wimsborder wimscenter"><caption>\name_caption</caption>
<thead><tr><td> &nbsp;</td><th>\name_classeA1[\choix]</th><th>\name_classeA2[\choix]</th><th>\name_total</th></tr></thead>
<tbody><tr><th>\name_classeB1[\choix]</th><td>\nba1b1</td><td>\nba2b1</td><td>\totalB1</td></tr>
<tr><th>\name_classeB2[\choix]</th><td>\nba1b2</td><td>\nba2b2</td><td>\totalB2</td></tr>
<tr><th>\name_total</th><td>\totalA1</td><td>\totalA2</td><td>\total</td></tr>
</tbody>
</table>
 </div>
</div>
<p>
\name_consigne
</p>
}
#if defined TARGET_arbre1
\answer{\name_reply 1}{\info[\ipcttotalB1];\info}{type=clickfill}
\answer{\name_reply 2}{\info[\ipcttotalB2]}{type=clickfill}
\answer{\name_reply 3}{\info[\imrga1B1]}{type=clickfill}
\answer{\name_reply 4}{\info[\imrga2B1]}{type=clickfill}
\answer{\name_reply 5}{\info[\imrga1B2]}{type=clickfill}
\answer{\name_reply 6}{\info[\imrga2B2]}{type=clickfill}

#else
\answer{\name_reply 1}{\info[\ipcttotalA1];\info}{type=clickfill}
\answer{\name_reply 2}{\info[\ipcttotalA2]}{type=clickfill}
\answer{\name_reply 3}{\info[\imrgA1b1]}{type=clickfill}
\answer{\name_reply 4}{\info[\imrgA1b2]}{type=clickfill}
\answer{\name_reply 5}{\info[\imrgA2b1]}{type=clickfill}
\answer{\name_reply 6}{\info[\imrgA2b2]}{type=clickfill}

#endif
#endif
