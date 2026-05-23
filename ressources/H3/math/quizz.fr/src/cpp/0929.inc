\title{Question 0929 Développer et simplifier}
\keywords{mental_calculation,literal_calculation,multiplication}
\text{liste14=shuffle(2,3,5,6,4)}
\integer{a14=\liste14[1]}
\integer{b14=\liste14[2]}
\integer{c14=random(-1,1)}
\text{x14=random(a,x,y,n,b,m,p)}
\integer{temp141=\a14*\b14}
\text{d14=\c14<1?\c14:{}+\c14}
\integer{cb14=\c14*\a14}

\text{rep=pari(\temp141*\x14^2+\cb14*\x14)}
\text{enonce= Développe et simplifie : \( \a14 \x14(\b14 \x14 \d14)={} \) }
\text{enonceb=}
\text{feedback=La forme développée : \( \a14 \x14(\b14 \x14 \d14)=\a14 \x14 \times \b14 \x14 \d14 \times \a14 \x14\), il suffit de réduire.}
