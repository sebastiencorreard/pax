\title{Question 406 NS prix initial}
\keywords{quizz,percentage,percents}
\observation{Question du sujet zéro sujet-specifique-2_0.pdf publié sur EDUSCOL en juin 2025 }

%%CD : piste de modification : voir si on laisse la base 100 ou non%%


\integer{typevol=randitem(1,1,1,-1)}
\integer{vf=(\typevol==1)? randitem(110,120,130,140,160):randitem(90,80,70,60)}
\integer{p=abs(\vf-100)}
\text{evol=(\typevol==1)? augmentation:réduction}

%%les réponses%%
\text{evoln=(\typevol==1)? l'augmentation:la réduction}
\text{evolpp=(\typevol==1)? augmenté:diminué}
\integer{b1=\vf*\p/100}
\real{b2=\vf*(1-\p/100)}
\real{b3=\vf*(1+\p/100)}
\text{evolpp2=(\typevol==1)? diminué:augmenté}
%%pour le feedback%%
\real{cm=(\typevol==1)? 1+\p/100:1-\p/100}


\matrix{tabrep=le prix de l’article avant \evoln était égal à 100 euros,le prix de l’article avant \evoln était égal à \b2 euros,le prix a \evolpp de \b1 euros,le prix a \evolpp2 de \b1 euros
le prix a \evolpp de \p euros,le prix a \evolpp de \b1 euros,le prix de l’article avant \evoln était égal à \b2 euros,le prix de l’article avant \evoln était égal à \b3 euros}
\text{listerep=randomrow(\tabrep)}

\text{enonce=A l’issue d’une \evol de \p %&#44; un article coûte \vf euros.<br>
Laquelle des quatre propositions suivantes est vraie &nbsp;&#63;}

\text{good=\listerep[1]}
\text{bads=\listerep[2],\listerep[3],\listerep[4]}
\text{feedback=La bonne réponse est&nbsp;&#58; \good. En effet&#44; le prix initial de l'article est \(\frac{\vf}{\cm}=100\). }
