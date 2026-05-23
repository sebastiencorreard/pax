\title{Question 0320 Lire l'heure}
\keywords{mental_calculation,clock}
\integer{h=random(8..11)}
\integer{h1=\h-1}
\integer{h2=\h1-1}
\integer{minutes=random(15,-15,-15)}
\text{phrase= \minutes <0 ? moins le : et }
\text{enoncetemp= \h heures \phrase quart}
\integer{minutes1=\minutes=15?-15:15}
\matrix{quest=\h,\minutes;\h,\minutes1;\h1,\minutes}
\text{temp=\minutes <0 ? \h1 h 45 min:\h h \minutes min}
\text{temp=\minutes1 <0? wims(append item \h1 h 45 min to \temp):wims(append item \h h \minutes1 min to \temp)}
\text{temp=\minutes <0? wims(append item \h2 h 45 min to \temp):wims(append item \h1 h \minutes min to \temp)}
%%%% shuffle %%%%%
\text{k=shuffle(3)}
\text{A1=slib(draw/clock \quest[\k[1];1]:\quest[\k[1];2]:00,120,1,html)}
\text{A2=slib(draw/clock \quest[\k[2];1]:\quest[\k[2];2]:00,120,1,html)}
\text{A3=slib(draw/clock \quest[\k[3];1]:\quest[\k[3];2]:00,120,1,html)}
\integer{rep=position(1,\k)}
\integer{bad1=(\rep +1)%3}
\text{bad1=Figure \bad1}
\text{enonce=Figure 1 : \A1   Figure 2 : \A2  Figure 3 : \A3<br>Quelle pendule indique \enoncetemp.}
\text{enonceb=}
\text{feedback=Les réponses : <br> \temp[\k[1]] : \A1 <br>\temp[\k[2]] : \A2 <br>\temp[\k[3]] : \A3}
