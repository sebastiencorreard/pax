target=formules1 formules2 formules3 formules4 formules5



#if defined TARGET_formules1
\title  {Formules de dérivées et primitives 1}
#endif
#if defined TARGET_formules2
\title  {Formules de dérivées et primitives 2}
#endif
#if defined TARGET_formules3
\title  {Formules de dérivées et primitives 3}
#endif
#if defined TARGET_formules4
\title  {Formules de dérivées et primitives 4}
#endif
#if defined TARGET_formules5
\title  {Formules de dérivées et primitives 5}
#endif


\author {Chantal,Causse}
\email  {Chantal.Causse@noos.fr}
\format {html}

\text{confparm2 = \confparm2 = ? X : \confparm2}
\text{var = \confparm2 issametext X ? x}
\text{var = \confparm2 issametext T ? t}
\text{var = \confparm2 issametext XT ?randitem(x,t)}


\text{confparm1 = \confparm1 = ? S : \confparm1}
\text{rig1 = \confparm1 issametext S ? : \(\var\mapsto \) }
\text{rig2 = \confparm1 issametext S ? : sur}
\text{rig3 = \confparm1 issametext S ? : la fonction \(\var \mapsto \)}
\text{rig4 =  \confparm1 issametext S ? : La fonction \(\var \mapsto \)}



\integer{k=random(1..8)*random(-1,1)}
\integer{a1=random(1..5)*random(-1,1)}
\integer{a2=random(1..5)*random(-1,1)}
\integer{a3=random(1..5)*random(-1,1)}
\integer{a4=random(1..5)*random(-1,1)}
\integer{a5=random(1..5)*random(-1,1)}


#if defined TARGET_formules1
\text{liste = \k,\var,\var^2,\var^3,\var^4}
#endif
#if defined TARGET_formules2
\text{liste = \k,\a1*\var,\a2*\var^2,\a3*\var^3,\a4*\var^4}
#endif
#if defined TARGET_formules3
\text{liste = \k,\a1*\var,\a2*\var^2,\a3*\var^3,\a4*\var^4,-\var/\a1,-\var^2/\a2,-\var^3/\a3,-\var^4/\a4}
#endif
#if defined TARGET_formules4
\text{liste = random(\k,1/\k),random(\a1*\var,\a1*\var,\var/\a1),random(\a2*\var^2,\a2*\var^2,\var^2/\a2),random(\a3*\var^3,\a3*\var^3,\var^3/\a3),random(\a4*\var^4,\a4*\var^4,\var^4/\a4)}
#endif
#if defined TARGET_formules5
\text{liste1 = \a3*\var+\a4,\a3*\var^2 + \a4*\var+\a5,\a3}
\text{liste1 = shuffle(\liste1)}
\text{liste2 = \a2*e^(\a1*\var),e^(\a1*\var+\a2),\k*e^(\a1*\var+\a2) }
\text{liste3 = shuffle(\liste2,e^(\a1*\var^2))}
#endif

#if (defined TARGET_formules1||defined TARGET_formules2||defined TARGET_formules3)
\text{s = shuffle(items(\liste))}
\text{f1 = \liste[\s[1]]}
\text{f2 = \liste[\s[2]]}
\text{f3 = \liste[\s[3]]}
#endif
#if defined TARGET_formules4
\text{liste = shuffle(\liste)}
\text{f1 = \liste[1]+\liste[4]}
\text{f2 = \liste[2]+\liste[5]}
\text{f3 = \liste[3]+\liste[1]}
#endif
#if defined TARGET_formules5
\text{f1 = \liste1[1]+\liste3[1]}
\text{f2 = \liste3[2]+\liste1[2]}
\text{f3 = \liste1[3]+\liste3[3]}
#endif
\text{dom1 =  \confparm1 issametext S ? : \({\RR}\)}
\text{dom2 =  \confparm1 issametext S ? : \({\RR}\)}
\text{dom3 =  \confparm1 issametext S ? : \({\RR}\)}

#if (defined TARGET_formules1||defined TARGET_formules2||defined TARGET_formules3)
\text{Liste = 1/\var^2,\liste}
\text{S = shuffle(items(\Liste))}
\text{f4 = \Liste[\S[1]]}
\text{f5 = \Liste[\S[2]]}
\text{f6 = \Liste[\S[3]]}
\text{Dom1 =  \S[1]=1 ? random(\({\RR^{*}_{+}}\),\({\RR^{*}_{-}}\)): \({\RR}\)}
\text{Dom2 =  \S[2]=1 ? random(\({\RR^{*}_{+}}\),\({\RR^{*}_{-}}\)): \({\RR}\)}
\text{Dom3 = \S[3]=1 ? random(\({\RR^{*}_{+}}\),\({\RR^{*}_{-}}\)): \({\RR}\)}
#endif
#if defined TARGET_formules4
\text{Liste = random(\a5/\var^2,\a5/\var^2,1/(\a5*\var^2)),\liste}
\text{S = shuffle(items(\Liste))}
\text{f4 = \Liste[\S[1]]+\Liste[\S[4]]}
\text{f5 = \Liste[\S[2]]+\Liste[\S[5]]}
\text{f6 = \Liste[\S[3]]+\Liste[\S[6]]}
\text{Dom1 =  \S[1]=1 or \S[4]=1 ? random(\({\RR^{*}_{+}}\),\({\RR^{*}_{-}}\)): \({\RR}\)}
\text{Dom2 =  \S[2]=1 or \S[5]=1? random(\({\RR^{*}_{+}}\),\({\RR^{*}_{-}}\)): \({\RR}\)}
\text{Dom3 = \S[3]=1 or \S[6]=1? random(\({\RR^{*}_{+}}\),\({\RR^{*}_{-}}\)): \({\RR}\)}
#endif
#if defined TARGET_formules5
\text{Liste1 =\a5/\var^2, \liste1}
\text{S = shuffle(items(\Liste1))}
\text{Liste2 = shuffle(\liste2)}
\text{f4 = \Liste1[\S[1]]+\Liste2[1]}
\text{f5 = \Liste2[2]+\Liste1[\S[2]]}
\text{f6 = \Liste1[\S[3]]+\Liste2[3]}
\text{Dom1 =  \S[1]=1 ? random(\({\RR^{*}_{+}}\),\({\RR^{*}_{-}}\)): \({\RR}\)}
\text{Dom2 =  \S[2]=1 ? random(\({\RR^{*}_{+}}\),\({\RR^{*}_{-}}\)): \({\RR}\)}
\text{Dom3 = \S[3]=1 ? random(\({\RR^{*}_{+}}\),\({\RR^{*}_{-}}\)): \({\RR}\)}
#endif

\text{Dom1 =  \confparm1 issametext S ? : \Dom1}
\text{Dom2 =  \confparm1 issametext S ? : \Dom2}
\text{Dom3 =  \confparm1 issametext S ? : \Dom3}

\function{d1 = diff(\f1,\var)}
\function{d2 = diff(\f2,\var)}
\function{d3 = diff(\f3,\var)}
\function{F4=integrate(\f4,\var)}
\function{F5=integrate(\f5,\var)}
\function{F6=integrate(\f6,\var)}

\text{V =  La variable est \(\var\).}

\statement{
<ul>
<li><label for="reply1">La dérivée de \rig1 \(\f1) \rig2 \dom1 est \rig3</label> \embed{reply1,15}</li>
<li><label for="reply2">La dérivée de \rig1 \(\f2) \rig2 \dom2 est \rig3</label> \embed{reply2,15}</li>
<li><label for="reply3">La dérivée de \rig1 \(\f3) \rig2 \dom3 est \rig3</label> \embed{reply3,15}</li>
<li><label for="reply4">\rig4 \embed{reply4,15} est une primitive de \rig1 \(\f4) \rig2 \Dom1 </label></li>
<li><label for="reply5">\rig4 \embed{reply5,15} est une primitive de \rig1 \(\f5) \rig2 \Dom2 </label> </li>
<li><label for="reply6">\rig4 \embed{reply6,15} est une primitive de \rig1 \(\f6) \rig2 \Dom3</label></li>
</ul>
\if{\confparm1 issametext S}{
<p class="wims_instruction">\V</p>
}
}

\answer{Dérivée de \(\f1)}{\d1}{type=formal}
\answer{Dérivée de \(\f2)}{\d2}{type=formal}
\answer{Dérivée de \(\f3)}{\d3}{type=formal}
\answer{Primitive de \(\f4)}{\good4}{type=function}
\answer{Primitive de \(\f5)}{\good5}{type=function}
\answer{Primitive de \(\f6)}{\good6}{type=function}

\text{test4=maxima(if constantp(fullratsimp((\good4)-(\F4)))  then 1 else 0;)}
\text{test5=maxima(if constantp(fullratsimp((\good5)-(\F5)))  then 1 else 0;)}
\text{test6=maxima(if constantp(fullratsimp((\good6)-(\F6)))  then 1 else 0;)}

\condition{La réponse est bonne}{\test4=1}
\condition{La réponse est bonne}{\test5=1}
\condition{La réponse est bonne}{\test6=1}

\solution{<p>La dérivée de \rig1 \(\f1) \rig2 \dom1 est \rig3 \(\d1).
<br>
La dérivée de \rig1 \(\f2) \rig2 \dom2 est \rig3 \(\d2).
<br>
La dérivée de\rig1 \(\f3) \rig2 \dom3 est \rig3 \(\d3).
</p><p>
\rig4 \(\F4) est une primitive de \rig1 \(\f4) \rig2 \Dom1 .
<br>
\rig4 \(\F5) est une primitive de \rig1 \(\f5) \rig2 \Dom2 .
<br>
\rig4 \(\F6) est une primitive de \rig1 \(\f6) \rig2 \Dom3</p>
Les autres primitives s'obtiennent à partir de celles-ci en ajoutant une constante.}

\hint{<p>La dérivée de \rig1 \(\var^{n}) \rig2 \dom1 est \rig3\(n \var^{n-1}).</p><p>
Une primitive \rig2 \dom1 de \rig1 \(\var^{n}) est \rig3 \(\frac{\var^{n+1}}{n+1}).</p><p>
Si \(n\neq 1),une primitive \rig2 
\if{\confparm1 issametext R}{\({\RR^{*}_{+}}\) ou \({\RR^{*}_{-}}\)}
 de \rig1 \(1/\var^{n}) est \rig3 \(\frac{-1}{(n-1)\var^{n-1}}).</p>
}
