\title{Question 453 NS Evolutions successives identiques}
\keywords{quizz,percents}
%% CD %%
\observation{Question du sujet zéro sujet-specifique-1.pdf publié sur EDUSCOL en juin 2025 }
\integer{typ=randitem(1,1,-1)}
\integer{p=10*randint(1..4)}
\text{evol=(\typ==1)? augmente:diminue}
\text{evol2=(\typ==1)? augmentations:diminutions}
\text{evol3=(\typ==1)? augmenté:diminué}



\text{enonce=Un article \evol de \p% puis il \evol encore de \p%. Après ces deux
\evol2 il a \evol3 de&nbsp;&#58;}
\real{cm=(1+\typ*\p/100)^2}
\integer{g=abs(\cm-1)*100}
\text{good=\(\g\%\)}
\integer{bad1=2*\p}
\integer{bad2=(\typ==1)? \g+1:\g-1}
\text{bads=\((\p\%)^2 \),\(\bad2\%\),\(\bad1\%\)} 
\real{pdeci=\p/100}
\text{feed=(\typ==1)? En effet&#44; \(\left ( 1+\frac{\p}{100}\right )\times \left ( 1+\frac{\p}{100}\right )=\cm=1+\frac{\g}{100}\).:En effet&#44; \(\left ( 1-\frac{\p}{100}\right )\times \left ( 1-\frac{\p}{100}\right )=\cm=1-\frac{\g}{100}\). }
\text{feed2= \({}\):\({}=1-\frac{\g}{100}\)}
\text{feedback=La bonne réponse est \good.<br> \feed}
