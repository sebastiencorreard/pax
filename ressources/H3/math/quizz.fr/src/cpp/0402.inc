\title{Question 0402 Tiers et quarts}
\keywords{mental_calculation,division,fraction}

%%%%%%%%%%%%%%% question 1 %%%%%
\text{cas=random(tiers,quart)}
\integer{a1=\cas issametext tiers ?random(4..9)*3:randint(4..9)*4}
\integer{rep=\cas issametext tiers ? \a1/3: \a1/4}
\text{enonce= \cas issametext tiers ? Le tiers de \(\a1\) &#58;:Le quart  de \(\a1\) &#58; }
\text{enonceb=}
\text{temp0402=\cas issametext tiers ? 3 : 4}
\text{feedback=Le \cas de \a1 s'obtient en divisant \a1 par \temp0402.  }
