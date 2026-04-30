target= ineqinterv1 ineqlin1 ineqlin2 ineqlin3
#if defined TARGET_ineqinterv1
\title{Traduction inégalité vers intervalle}
#endif
#if defined TARGET_ineqlin1
\title{Inéquation linéaire 1}
#endif
#if defined TARGET_ineqlin2
\title{Inéquation linéaire 2}
#endif
#if defined TARGET_ineqlin3
\title{Inéquation linéaire 3}
#endif
\language{fr}
\author{David Doyen}
\email{david.doyen@u-pem.fr}

\text{x=x}
\text{lsymb={<},\leq,{>},\geq}
\text{lnsymb={>},\geq,{<},\leq}
\text{lcr=\(\lbrack\),\(\rbrack\)}

#if defined TARGET_ineqinterv1
\integer{val=randitem(-1,1)*randint(1..6)}
\text{type=randint(1..4)}
\text{symb=\lsymb[\type]}
\text{nsymb=\lnsymb[\type]}
\text{ineq=randitem(\x\symb \val,\val \nsymb \x)}
#endif

#if defined TARGET_ineqlin1
\text{cas=randint(1..2)}
\text{type=randint(1..4)}
\integer{p=randitem(-1,1)*randint(1..6)}
\integer{r=randitem(-1,1)*randint(1..6)}
\text{px=texmath(\p*\x)}
\rational{rp=(\r)/(\p)}
\text{val=\rp}
\if{\p>0}{
\text{symb=\lsymb[\type]}
\text{nsymb=\lnsymb[\type]}
\text{ineq=randitem(\px \symb \r,\r \nsymb \px)}
\text{corr1=\(\ineq \Leftrightarrow \x \symb \rp\) <br>}
}{
\text{symb=\lnsymb[\type]}
\text{nsymb=\lsymb[\type]}
\text{ineq=randitem(\px \symb \r,\r \nsymb \px)}
\text{corr1=\(\ineq \Leftrightarrow \x \nsymb \rp\) <br>}
}
#endif

#if defined TARGET_ineqlin2
\text{cas=randint(1..2)}
\text{type=randint(1..4)}
\integer{p=randitem(-1,1)*randint(2..6)}
\integer{q=randitem(-1,1)*randint(1..6)}
\integer{r=randitem(-1,1)*randint(1..6)}
\text{pxq=randitem(\p*\x+\q,\q+\p*\x)}
\text{pxq=texmath(\pxq)}
\text{px=texmath(\p*\x)}
\integer{rmq=\r-\q}
\rational{rmqp=(\r-\q)/(\p)}
\text{val=\rmqp}
\if{\p>0}{
\text{symb=\lsymb[\type]}
\text{nsymb=\lnsymb[\type]}
}{
\text{symb=\lnsymb[\type]}
\text{nsymb=\lsymb[\type]}
}
\if{\p>0}{
\if{randitem(1,2)=1}{
\text{ineq=\pxq \symb \r}
\text{corr1=\(\pxq \symb \r\) <br>
\(\Leftrightarrow \px \symb \rmq\) <br>
\(\Leftrightarrow \x \symb \rmqp\) <br>}
}{
\text{ineq=\r \nsymb \pxq}
\text{corr1=\(\r \nsymb \pxq\) <br>
\(\Leftrightarrow \rmq \nsymb \px\) <br>
\(\Leftrightarrow \rmqp \nsymb \x\) <br>}
}
}{
\if{randitem(1,2)=1}{
\text{ineq=\pxq \symb \r}
\text{corr1= \(\pxq \symb \r\) <br>
\(\Leftrightarrow \px \symb \rmq\) <br>
\(\Leftrightarrow \x \nsymb \rmqp\) <br>}
}{
\text{ineq=\r \nsymb \pxq}
\text{corr1=\(\r \nsymb \pxq\) <br>
\(\Leftrightarrow \rmq \nsymb \px\) <br>
\(\Leftrightarrow \rmqp \symb \x\) <br>}
}
}
#endif

#if defined TARGET_ineqlin3
\text{s=shuffle(-6,-5,-4,-3,-2,-1,1,2,3,4,5,6)}
\integer{p1=\s[1]}
\integer{q1=randitem(-1,1)*randint(1..6)}
\integer{p2=\s[2]}
\integer{q2=randitem(-1,1)*randint(1..6)}
\text{pxq1=texmath(\p1*\x+\q1)}
\text{pxq2=texmath(\p2*\x+\q2)}
\text{type=randint(1..4)}
\if{\p1>\p2}{
\text{symb=\lsymb[\type]}
\text{ineq=\pxq1 \symb \pxq2}
\integer{p=\p1-\p2}
\integer{r=\q2-\q1}
\text{px=texmath(\p*\x)}
\rational{rp=\r/\p}
\text{corr1=\(\pxq1 \symb \pxq2\) <br>
\(\Leftrightarrow \px \symb \r\) <br>
\(\Leftrightarrow \x \symb \rp\) <br>}
}{
\text{symb=\lnsymb[\type]}
\text{ineq=\pxq1 \symb \pxq2}
\integer{p=\p2-\p1}
\integer{r=\q1-\q2}
\text{px=texmath(\p*\x)}
\rational{rp=\r/\p}
\text{corr1=\(\pxq1 \symb \pxq2\) <br>
\(\Leftrightarrow \r \symb \px\) <br>
\(\Leftrightarrow \rp \symb \x\) <br>}
}
\text{val=\rp}
#endif

% Les quatre types de réponses possibles
% type 1 : \rbrack -inf,f \lbrack
% type 2 : \rbrack -inf,f \rbrack
% type 3 : \rbrack e,+inf \lbrack
% type 4 : \lbrack e,+inf \lbrack

\if{\type<=2}{
\text{ee=\rbrack}
\text{e=-inf}
\text{f=\val}
\if{\type=1}{
\text{ff=\lbrack}
}{
\text{ff=\rbrack}
}
\text{intsol=\ee -\infty, \f \ff}
}
\if{\type>=3}{
\if{\type=3}{
\text{ee=\rbrack}
}{
\text{ee=\lbrack}
}
\text{e=\val}
\text{f=+inf}
\text{ff=\lbrack}
\text{intsol=\ee \e, +\infty \ff}
}

\text{eee=\(\ee\)}
\text{fff=\(\ff\)}

% Enoncé

\statement{
#if defined TARGET_ineqlin1 || TARGET_ineqlin2 || TARGET_ineqlin3
Déterminer l'ensemble des réels \(x\) tels que \(\ineq\). Ecrire cet ensemble sous la forme d'un intervalle.<br class="spacer">
#endif
#if defined TARGET_ineqinterv1
Ecrire l'ensemble des réels \(x\) tels que \(\ineq\) sous la forme d'un intervalle.<br class="spacer">
#endif
<table><tr><td>\embed{reply1,20x30x1}</td><td>\embed{reply2,3}</td><td>,</td><td>\embed{reply3,3}</td><td>\embed{reply4,20x30x1}</td></td></tr></table><br class="spacer">

<div class="wims_instruction"> Pour une borne égale à \(+\infty\), écrire <span class="tt">+inf</span> dans le champ de réponse correspondant. Pour une borne égale à \(-\infty\), écrire <span class="tt">-inf</span>.</div>
}

% Analyse de la réponse

\answer{}{\eeer;\lcr}{type=clickfill}{option=noanalyzeprint}
\answer{}{\er}{type=formal}{option=noanalyzeprint}
\answer{}{\fr}{type=formal}{option=noanalyzeprint}
\answer{}{\fffr;\lcr}{type=clickfill}{option=noanalyzeprint}

\text{diffe=simplify(\er-\e)}
\text{difff=simplify(\fr-\f)}
\if{(\eee issametext \eeer) and (\diffe=0) and (\difff=0) and (\fff issametext \fffr)}{\text{ok=1}}

\condition{Bonne réponse}{\ok=1}

% Corrigé

#if defined TARGET_ineqlin1 || TARGET_ineqlin2 || TARGET_ineqlin3
\feedback{1=1}{<br><div class="bold" style="color:gray">Correction</div>
\corr1
L'ensemble des réels \(x\) tels que \(\ineq\) est donc l'intervalle \(\intsol\).}
#endif
#if defined TARGET_ineqinterv1
\feedback{1=1}{<br><div class="bold" style="color:gray">Correction</div>
L'ensemble des réels \(x\) tels que \(\ineq\) est l'intervalle \(\intsol\).}
#endif
