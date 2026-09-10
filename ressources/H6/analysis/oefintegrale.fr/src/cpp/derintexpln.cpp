target=formules8 formules8b
\*variantes avec des logarithmes de l'exercice formules5*\

\author {Sophie, Lemaire}
\email  {sophie.lemaire@math.u-psud.fr}
\format {html}

\text{confparm2 = \confparm2 = ? X : \confparm2}
\text{var = \confparm2 issametext X ? x}
\text{var = \confparm2 issametext T ? t}
\text{var = \confparm2 issametext XT ?randitem(x,t)}

\integer{k=random(1..8)*random(-1,1)}
\integer{a1=random(1..5)*random(-1,1)}
\integer{a2=random(1..5)*random(-1,1)}
\integer{a3=random(1..5)*random(-1,1)}
\integer{a4=random(1..5)*random(-1,1)}
\integer{a5=random(1..5)*random(-1,1)}
\integer{a6=random(1..5)*random(-1,1)}
\integer{a7=random(1..5)}\integer{a8=random(1..5)}
\integer{n=randint(2..6)}
\rational{u5=simplify(-(\a6)/(\a5))}
\text{liste1 = \a3*\var,\a3*\var^2,\a3}
\text{dliste1 = \a3,2*\a3*\var,0}
\text{Fliste1 = \a3/2*\var^2, \a3/3*\var^3,\a3*\var}
\text{liste2 = (\a3)*log(\a5*\var+(\a6)), (\a4)*log(\a5*\var+(\a6)), \var * log(\a5*\var+(\a6)), (\a4*\var+(\a5))*log(\var)}
\text{doma5= \a5>0 ?\left\rbrack\u5;+\infty\right\lbrack :\left\rbrack-\infty;\u5\right\lbrack }
\text{domaine2 = \doma5, \doma5,\doma5,{\RR^{*}_{+}}}
\text{dliste2 = (\a3)*(\a5)/(\a5*\var+(\a6)),(\a4)*(\a5)/(\a5*\var+(\a6)),(\a5)*\var/(\a5*\var+(\a6))+log(\a5*\var+(\a6)),\a4 + (\a5)/\var + (\a4)*log(\var)}
\text{Fliste2 = (\a3)*((\a5*\var+(\a6))*log(\a5*\var+(\a6))-(\a5)*\var-(\a6))/(\a5),(\a4)*((\a5*\var+(\a6))*log(\a5*\var+(\a6))-(\a5)*\var-(\a6))/(\a5)}
\text{v1 = shuffle(3)}\text{v2 = shuffle(2)}\text{v22 = shuffle(3,4)}

\text{liste3 = (\a2)*exp(\a1*\var),exp(\a1*\var+(\a2)),(\k)*exp(\a1*\var+(\a2)), (\a4)/(\a8+(\a7)*exp(\var)),exp(\a3*\var^2) }
\text{domexp5=\a5>0 ? \(\var > \log(\u5)\):\(\var < \log(\u5)\)}
\text{dliste3 =simplify((\a1)*(\a2)* exp(\a1*\var)), simplify(\a1* exp(\a1*\var+(\a2))),simplify((\k)*(\a1)*exp(\a1*\var+(\a2))),simplify(-(\a4)*(\a7)*exp( \var )/((\a7* exp(\var)+(\a8))^2)),simplify(2*(\a3))* \var *exp(\a3*\var^2) }
\text{Fliste3 = (\a2)* exp(\a1*\var)/(\a1),exp(\a1*\var+(\a2))/(\a1),(\k)*exp(\a1*\var+(\a2))/(\a1)}
\text{v3 = shuffle(3)}\text{v33 = shuffle(4,5)}

\text{liste4=(\a1)/\var,1/(\a1*\var),(\a2)/(\var^\n),1/(\a2*\var^\n)}
\text{Fliste4=(\a1)*log(\var), log(\var)/(\a1), -(\a2)/((\n-1)*\var^(\n-1)),-1/(\a2*(\n-1)*\var^(\n-1))}
\text{v4 = shuffle(2)}\text{v44 = shuffle(3,4)}

\text{f1 = \liste1[\v1[1]]+\liste2[\v2[1]]}
\text{df1 = simplify(\dliste1[\v1[1]])+simplify(\dliste2[\v2[1]])}
\text{hyp1 = \domaine2[\v2[1]]}

\text{f2 = \liste3[\v3[1]]+\liste2[\v22[1]]}
\text{df2 = \dliste3[\v3[1]] + (maxima(\dliste2[\v22[1]]))}
\text{hyp2 = \domaine2[\v22[1]]}
\text{f3 = \liste1[\v2[2]]+\liste3[\v33[1]]}
\text{df3 = simplify(\dliste1[\v2[2]])+(\dliste3[\v33[1]])}

\text{f4 = \liste1[\v1[3]]+\liste3[\v3[2]]}
\text{F4 = \Fliste1[\v1[3]]+simplify(\Fliste3[\v3[2]])}

#if defined TARGET_formules8
\title  {Formules de dérivées et primitives 8 (exp et ln)}
\text{f5 = \a3*log(\var) + \liste4[\v4[1]]}
\text{F5 = \a3*\var*(log(\var)-1) + simplify(\Fliste4[\v4[1]])}
\text{hyp5=\RR^{*}_{+}}
#else
 \title {Formules de dérivées et primitives 8b (dérivées exp et ln ; primitives exp)}
 \text{liste5=(\a1)/\var,1/(\a1 * \var),1/((\a5)*\var + (\a6))}
 \text{Fliste5=(\a1)*log(\var), log(\var)/(\a1), log((\a5)*\var+(\a6))/(\a5)}
 \text{v5 = shuffle(3)}
 \text{f5 =  simplify(\liste5[\v5[1]])}
 \text{F5 =  \Fliste5[\v5[1]]}
 \text{hyp5=\v5[1]<3?\RR^{*}_{+}:\rbracket \u5; +\infty \lbracket}
#endif



\text{f6 = \a4*\var * exp(\a5*\var^2) + simplify(\liste4[\v44[1]])}
\text{F6 = simplify(\a4/(2*(\a5))*exp(\a5*\var^2))+simplify(\Fliste4[\v44[1]])}

\text{f1t = texmath(\f1)}
\text{f1t = wims(replace internal log by ln in \f1t)}
\text{f2t = texmath(\f2)}
\text{f2t = wims(replace internal log by ln in \f2t)}
\text{f3t = texmath(\f3)}
\text{f4t = texmath(\f4)}
\text{f5t = texmath(\f5)}
\text{f5t = wims(replace internal log by ln in \f5t)}
\text{f6t = texmath(\f6)}
\text{df1t = texmath(\df1)}
\text{df1t = wims(replace internal log by ln in \df1t)}
\text{df2t = texmath(\df2)}
\text{df2t = wims(replace internal log by ln in \df2t)}
\text{df3t = texmath(\df3)}
\text{F4t = texmath(\F4)}
\text{F5t = texmath(\F5)}
\text{F5t = wims(replace internal log by ln in \F5t)}
\text{F6t = texmath(\F6)}
\text{F6t = wims(replace internal log by ln in \F6t)}



\statement{
<ol><li><label for="reply1"> La dérivée de \( \var \mapsto \f1t\) sur \(\hyp1\) est la fonction \(\var \mapsto \)</label>  \embed{reply1,28}</li>
<li><label for="reply2"> La dérivée de \(\var\mapsto\f2t\) sur \(\hyp2\) est la fonction \(\var \mapsto \) </label> \embed{reply2,28}</li>
<li><label for="reply3"> La dérivée de \(\var\mapsto \f3t\) sur \({\RR}\) est la fonction \(\var \mapsto \)</label>  \embed{reply3,28}</li>

<li>La fonction \(\var\mapsto \) \embed{reply4,28} est <label for="reply4">une primitive  de \(\var \mapsto \f4t\) sur \({\RR}\). </label>  </li>
<li>La fonction  \(\var\mapsto \) \embed{reply5,28} est <label for="reply5">une primitive de \(\var \mapsto \f5t\) sur \(\hyp5\).  </label> </li>
<li>La fonction  \(\var\mapsto \) \embed{reply6,28} est <label for="reply6">une primitive de \(\var\mapsto \f6t\) sur \(\RR_{+}^*\). </label> </li>
</ol>


}

\answer{Dérivée de \(\f1)}{\df1}{type=formal}
\answer{Dérivée de \(\f2)}{\df2}{type=formal}
\answer{Dérivée de \(\f3)}{\df3}{type=formal}
\answer{Primitive de \(\f4)}{\good4}{type=function}
\answer{Primitive de \(\f5)}{\good5}{type=function}
\answer{Primitive de \(\f6)}{\good6}{type=function}

\text{test4=maxima(if constantp(fullratsimp((\good4)-(\F4)))  then 1 else 0;)}
\text{good = wims(replace internal ln by log in \good5)}
\function{verif5=diff((\good5)-(\F5))}
\integer{test5=simplify(\verif5)}
\text{test6=maxima(if constantp(fullratsimp((\good6)-(\F6)))  then 1 else 0;)}

\condition{La réponse est bonne}{\test4=1}
\condition{La réponse est bonne}{\test5=0}
\condition{La réponse est bonne}{\test6=1}
\solution{<ol><li>
  La dérivée de \(\var\mapsto \f1t\) en tout point \(\hyp1\) est  \(\var\mapsto\) \(\df1t).</li>
<li>La dérivée de \(\var\mapsto \f2t\) en tout point \(\hyp2\) est  \(\var\mapsto\)  \(\df2t\).</li>
<li>La dérivée de \(\var\mapsto \f3t) en tout réel est la fonction \(\var\mapsto\) \(\df3t\).</li>
<li> La fonction \(\var\mapsto \F4t\) est une primitive de \(\var\mapsto \f4t\) sur \(\RR\).</li>
<li> La fonction\(\var\mapsto \F5t\) est une primitive de \(\var\mapsto \f5t\) sur \(\hyp5\).</li>
<li>La fonction\(\var\mapsto \F6t\) est une primitive de \(\var\mapsto \f6t\) sur \(\RR_{+}^*\).</li>
</ol>
Les autres primitives s'obtiennent à partir de celles-ci en ajoutant une constante.}
