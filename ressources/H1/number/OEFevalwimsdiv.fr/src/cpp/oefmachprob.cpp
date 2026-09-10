target=oefmachprob1 oefmachprob2 oefmachprob3 oefmachprob4 oefmachprob5

\keywords{division,pbsolving}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"

\precision(1000000)

\integer{a=randint(1..2)}
\integer{b=randint(1..2)}
\text{sex=boy,girl}
\text{z=0}
\text{nom1=slib(lang/fname fr,\sex[\a])}
\text{nom2=slib(lang/fname fr,\sex[\b])}
\text{nom3=slib(lang/fname fr,girl)}
\if{\a=1}{\text{ar1=il}}{\text{ar1=elle}}
\if{\a=1}{\text{art1=Il}}{\text{art1=Elle}}
\if{\b=1}{\text{ar2=il}}{\text{ar2=elle}}
\if{\b=1}{\text{art2=Il}}{\text{art2=Elle}}
\text{\text{ar3=elle}}
\text{\text{art3=Elle}}
\text{tvres=}
\text{listeuro=1,3,5,6,8,9,10,11,12,15,16,17,21,22,24}

#if defined TARGET_oefmachprob1
\integer{ch=randint(1..4)}
\matrix{prob=wims(record \ch of src/problemes)}
\text{enonc=row(2,\prob)}
\text{question=row(3,\prob)}
\text{d1=row(4,\prob)}
\text{d2=row(5,\prob)}
\integer{v1=\d1[1]+\d1[2]*randint(1..\d1[3])}
\integer{v2=\d2[1]+\d2[2]*randint(1..\d2[3])}
\text{u=\d1[4]}
\text{op=row(6,\prob)}
\if{\op[1]=/}{\integer{res=\v2}
              \integer{v2=\v1 * \v2}}
               {\integer{res=abs(\v1 \op[1] \v2)}}              
\text{v1=slib(numeration/ecriturenombre \v1,comma tex)}
\text{v2=slib(numeration/ecriturenombre \v2,comma tex)}
\text{enonc=wims(replace internal v1 by \(\v1\) in \enonc)}
\text{enonc=wims(replace internal v2 by \(\v2\) in \enonc)}
\integer{l=10}
\real{vres=\res}
#endif

#if defined TARGET_oefmachprob2
\integer{ch=randint(5..13)}
\matrix{prob=wims(record \ch of src/problemes)}
\text{enonc=row(2,\prob)}
\text{question=row(3,\prob)}
\text{d1=row(4,\prob)}
\text{d2=row(5,\prob)}
\real{v1=\d1[1]+\d1[2]*randint(1..\d1[3])}
\real{v2=\d2[1]+\d2[2]*randint(1..\d2[3])}
\text{u=\d1[4]}
\text{op=row(6,\prob)}
\if{\op[1]=/}{\real{res=\v2}
              \real{v2=\v1 * \v2}}
               {\real{res=abs(\v1 \op[1] \v2)}
               }
\real{vres=\res}

\text{tv1=\v1}
\text{tv2=\v2}    
\text{tv1=slib(numeration/ecriturenombre \tv1,comma tex)}
\text{tv2=slib(numeration/ecriturenombre \tv2,comma tex)}
\text{enonc=wims(replace internal v1 by \(\tv1\) in \enonc)}
\text{enonc=wims(replace internal v2 by \(\tv2\) in \enonc)}
\integer{l=10}
#endif

#if defined TARGET_oefmachprob3
\integer{ch=randint(5..13)}
\matrix{prob=wims(record \ch of src/problemes)}
\text{enonc=row(2,\prob)}
\text{question=row(3,\prob)}
\text{d1=row(7,\prob)}
\text{d2=row(8,\prob)}
\real{v1=\d1[1]+\d1[2]*randint(1..\d1[3])}
\real{v2=\d2[1]+\d2[2]*randint(1..\d2[3])}
\text{u=\d1[4]}
\text{op=row(6,\prob)}
\if{\op[1]=/}{\real{res=\v2}
              \real{v2=\v1 * \v2}
              }
             {\real{res=abs(\v1 \op[1] \v2)}
              }
\real{vres=\res}                    
\real{testv1=abs(pari(\v1-floor(\v1)))}
\if{\testv1>0 and \ch isin \listeuro}{\text{tv1=wims(exec moneyprint \v1)}
               }{
               \text{tv1=\v1}
               }
\real{testv2=abs(pari(\v2-floor(\v2)))}
\if{\testv2>0 and \ch isin \listeuro}{\text{tv2=wims(exec moneyprint \v2)}
               }{
               \text{tv2=\v2}
               }
\text{v1=slib(numeration/ecriturenombre \v1,comma tex)}
\text{v2=slib(numeration/ecriturenombre \v2,comma tex)}                                          
\text{tv1=slib(numeration/ecriturenombre \tv1,comma tex)}
\text{tv2=slib(numeration/ecriturenombre \tv2,comma tex)}
\text{enonc=wims(replace internal v1 by \(\tv1\) in \enonc)}
\text{enonc=wims(replace internal v2 by \(\tv2\) in \enonc)}
\integer{l=10}
#endif

#if defined TARGET_oefmachprob4
\integer{ch=randint(14..21)}
\matrix{prob=wims(record \ch of src/problemes)}
\text{enonc=row(2,\prob)}
\text{question=row(3,\prob)}
\text{d1=row(4,\prob)}
\text{d2=row(5,\prob)}
\text{d3=row(6,\prob)}
\real{v1=\d1[1]+\d1[2]*randint(1..\d1[3])}
\real{v2=\d2[1]+\d2[2]*randint(1..\d2[3])}
\real{v3=\d3[1]+\d3[2]*randint(1..\d3[3])}
\if{\ch=14 or \ch=15 or \ch=21}{\real{temp=\v1 + \v2}}
\if{\ch=16 or \ch=17}{\real{temp=\v1*\v2}}
\if{\ch=18}{\real{temp=\v2*\v3}}
\if{\ch=19}{\real{temp=\v1+\v3}}
\if{\ch=20}{\real{temp=\v1/\v2}}
\if{\ch=21}{\real{temp=\v1 + \v3}}
\text{u=\d1[4]}
\text{op=row(7,\prob)}
\real{res=abs(\v1 \op[1] \v2 \op[2] \v3)}
\real{vres=\res}
\real{testv1=abs(pari(\v1-floor(\v1)))}
\if{\testv1>0 and \ch isin \listeuro}{\text{tv1=wims(exec moneyprint \v1)}
               }{
               \text{tv1=\v1}
               }
\real{testv2=abs(pari(\v2-floor(\v2)))}
\if{\testv2>0 and \ch isin \listeuro}{\text{tv2=wims(exec moneyprint \v2)}
               }{
               \text{tv2=\v2}
               }
\real{testv3=abs(pari(\v3-floor(\v3)))}
\if{\testv3>0 and \ch isin \listeuro}{\text{tv3=wims(exec moneyprint \v3)}
               }{
               \text{tv3=\v3}
               }               
\text{v1=slib(numeration/ecriturenombre \v1,comma tex)}
\text{v2=slib(numeration/ecriturenombre \v2,comma tex)}
\text{v3=slib(numeration/ecriturenombre \v3,comma tex)}
\text{temp=slib(numeration/ecriturenombre \temp,comma tex)}
\text{tv1=slib(numeration/ecriturenombre \tv1,comma tex)}
\text{tv2=slib(numeration/ecriturenombre \tv2,comma tex)}
\text{tv3=slib(numeration/ecriturenombre \tv3,comma tex)}
\text{enonc=wims(replace internal v1 by \(\tv1\) in \enonc)}
\text{enonc=wims(replace internal v2 by \(\tv2\) in \enonc)}
\text{enonc=wims(replace internal v3 by \(\tv3\) in \enonc)}
\integer{l=10}
#endif

#if defined TARGET_oefmachprob5
\integer{ch=randint(22..24)}
\matrix{prob=wims(record \ch of src/problemes)}
\text{enonc=row(2,\prob)}
\text{question=row(3,\prob)}
\text{d1=row(4,\prob)}
\text{d2=row(5,\prob)}
\text{d3=row(6,\prob)}
\text{d4=row(7,\prob)}
\real{v1=\d1[1]+\d1[2]*randint(1..\d1[3])}
\real{v2=\d2[1]+\d2[2]*randint(1..\d2[3])}
\real{v3=\d3[1]+\d3[2]*randint(1..\d3[3])}
\real{v4=\d4[1]+\d4[2]*randint(1..\d4[3])}
\text{u=\d1[4]}
\text{op=row(8,\prob)}
\real{testv1=abs(pari(\v1-floor(\v1)))}
\if{\testv1>0 and \ch isin \listeuro}{\text{tv1=wims(exec moneyprint \v1)}
               }{
               \text{tv1=\v1}
               }
\real{testv2=abs(pari(\v2-floor(\v2)))}
\if{\testv2>0 and \ch isin \listeuro}{\text{tv2=wims(exec moneyprint \v2)}
               }{
               \text{tv2=\v2}
               }
\real{testv3=abs(pari(\v3-floor(\v3)))}
\if{\testv3>0 and \ch isin \listeuro}{\text{tv3=wims(exec moneyprint \v3)}
               }{
               \text{tv3=\v3}
               }  
\real{testv4=abs(pari(\v4-floor(\v4)))}
\if{\testv4>0 and \ch isin \listeuro}{\text{tv4=wims(exec moneyprint \v4)}
               }{
               \text{tv4=\v4}
               } 
\if{\ch=22}{\real{temp1=\v1*\v2}
            \real{vres1=\temp1+\v3}
            \real{testvres1=abs(pari(\vres1-floor(\vres1)))}
            \if{\testvres1>0}{\text{tres1=wims(exec moneyprint \vres1)}
               }{
               \text{tres1=\vres1}
               } 
            \text{tres1=slib(numeration/ecriturenombre \tres1,comma tex)}   
            \real{vres2=\v1*\v4}
            \text{tvres2=slib(numeration/ecriturenombre \vres2,comma tex)} 
            \integer{tvres3=pari(floor(\vres2))}
            \text{tvres3=slib(numeration/ecriturenombre \tvres3,comma tex)} 
            \real{res=(\v1 \op[1] \v2 \op[2] \v3) \op[3] \v4 \op[4] \v1}
            \text{tres=slib(numeration/ecriturenombre \res,comma tex)}
            \real{testtres=abs(pari(\res-floor(\res)))}
            \if{\testtres>0}{\text{tvres=wims(exec moneyprint \tres)}}            
            }
\if{\ch=23}{\real{res=ceil(\v2 \op[2] \v1)*\v1-\v2 + ceil(\v3 \op[2] \v1)*\v1-\v3}
            \integer{temp1=pari(floor(\v2/\v1))}
            \integer{r1=\v2-\temp1*\v1}
            \integer{temp2=\v1-\r1}
            \integer{temp3=pari(floor(\v3/\v1))}
            \integer{r2=\v3-\temp3*\v1}
            \integer{temp4=\v1-\r2}
            }
\if{\ch=24}{\real{temp1=\v2+\v3}
            \real{temp2=\v1*\temp1}         
            \real{res=\v1 \op[1] (\v2 \op[2] \v3) \op[3] \v4}
            \text{tvtemp1=slib(numeration/ecriturenombre \temp1,comma tex)}
            \text{tvtemp2=slib(numeration/ecriturenombre \temp2,comma tex)}          
            }
\real{vres=\res}
\text{tv1=slib(numeration/ecriturenombre \tv1,comma tex)}
\text{tv2=slib(numeration/ecriturenombre \tv2,comma tex)}
\text{tv3=slib(numeration/ecriturenombre \tv3,comma tex)}
\text{tv4=slib(numeration/ecriturenombre \tv4,comma tex)}
\text{enonc=wims(replace internal v1 by \(\tv1\) in \enonc)}
\text{enonc=wims(replace internal v2 by \(\tv2\) in \enonc)}
\text{enonc=wims(replace internal v3 by \(\tv3\) in \enonc)}
\text{enonc=wims(replace internal v4 by \(\tv4\) in \enonc)}
\text{tvv1=slib(numeration/ecriturenombre \v1,comma tex)}
\text{tvv2=slib(numeration/ecriturenombre \v2,comma tex)}
\text{tvv3=slib(numeration/ecriturenombre \v3,comma tex)}
\text{tvv4=slib(numeration/ecriturenombre \v4,comma tex)}
\text{tvtemp1=slib(numeration/ecriturenombre \temp1,comma tex)}
\text{tvres1=slib(numeration/ecriturenombre \vres1,comma tex)}
\integer{l=10}
#endif
\text{enonc=wims(replace internal nom1 by \nom1 in \enonc)}
\text{enonc=wims(replace internal nom2 by \nom2 in \enonc)}
\text{enonc=wims(replace internal nom3 by \nom3 in \enonc)}
\text{enonc=wims(replace internal ar1 by \ar1 in \enonc)}
\text{enonc=wims(replace internal art1 by \art1 in \enonc)}
\text{question=wims(replace internal nom1 by \nom1 in \question)}
\text{question=wims(replace internal nom2 by \nom2 in \question)}
\text{question=wims(replace internal nom3 by \nom3 in \question)}
\text{question=wims(replace internal ar1 by \ar1 in \question)}
\text{question=wims(replace internal art1 by \art1 in \question)}
\if{\tvres=}{\text{tvres=\vres}}
\text{tvres=slib(numeration/ecriturenombre \vres,comma tex)}
\if{\ch isin \listeuro}{\real{testres=abs(pari(\vres-floor(\vres)))}
                        \if{\testres>0}{\text{tres=wims(exec moneyprint \res)}}
                                        {\text{tres=\res}}
                       }{
                       \text{tres=\res}
                       }
\text{tres=slib(numeration/ecriturenombre \tres,comma tex)}
\text{reply_class=euler_quest_nobg}
#include "probsol.inc"

#if TARGET_oefmachprob5
\real{test=1-abs(\ch-23)} 
\if{\test>0}{\text{name_sol=<ul><li>\name_sol1</li>
            <li>\name_sol2</li>
            <li>\name_sol3</li>
            </ul>}
            }
#endif

\statement{
\enonc
<div class="\reply_class">
    <div class="spacer">\question</div>
    <label for="reply1">\name_ans</label> \embed{r1,\l}  \u. </div>
}

\answer{}{\repel}
\text{repel=wims(replace internal * by in \repel)}
\text{repel=wims(replace internal , by . in \repel)}
\real{repel=pari(\repel)}
\condition{\name_cond}{\repel=\res}
\if{\repel=\res}{\text{reply_class=euler_rep_good_nobg tick}}{\text{reply_class=euler_rep_bad_nobg cross"}}


\solution{\name_sol}
