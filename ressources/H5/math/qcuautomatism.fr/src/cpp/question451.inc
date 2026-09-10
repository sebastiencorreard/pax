\title{Question 451 NS coefficient multiplicateur}
\keywords{quizz,percentage,percents}
%% CD %%
\observation{Question du sujet zéro sujet-specifique-3.pdf publié sur EDUSCOL en juin 2025 }
\real{p=randint(11..79)/10}
\integer{typevol=randitem(1,1,1,2)}
\text{mot1=\typevol=1?diminue:augmente}
\text{enonce=Par combien faut-il multiplier une quantité positive pour que celle-ci \mot1 de \(\p \%\)&nbsp;&#58;}
\real{good=(\typevol==1)? 1-\p/100:1+\p/100}
\real{bad1=(\typevol==1)? 1-\p/10:1+\p/10}
\real{bad2=(\typevol==2)? 1-\p/100:1+\p/100}
\real{bad3=(\typevol==2)? 1-\p/10:1+\p/10}
\text{bads=\bad1,\bad2,\bad3}
\text{endfeed=(\typevol==1)?\( 1-\frac{\p}{100}\): \( 1+\frac{\p}{100}\)}
\text{feedback= La bonne réponse est  \good  puisque le coefficient multiplicateur est égal à \endfeed. }
  
