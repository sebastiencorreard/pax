\title{Question 0818 Distance temps et vitesse}
\keywords{mental_calculation,velocity,time,proportionality}
\integer{t0818=randint(1..3)}
\text{divi=3,4,6}

\integer{a0818=item(\t0818,3,4,6)} %%% division de l'heure
\integer{b0818=60/\a0818} %%% temps de parcours
\integer{vit=item(\t0818,27,28,24)}
\integer{rep=\vit*\b0818/60}
\text{enonce=Une trotinette électrique roule à \vit km/h.<br><STRONG>Quelle distance parcourt-elle en \b0818 minutes &#63;</STRONG><br> }
\text{enonceb=km}
\text{feedback=\(\b0818\) min correspond à \(\frac{1}{\a0818}\) d'une heure. <br>La bonne réponse est donc \(\vit \div \a0818\).}
