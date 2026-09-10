target=derquot1 derquot2 derquot3 derquot4 derquot5
\author{Maguy, Bruno ; Régine, Mangeard}
\email{regine@mangeard.Fr}
\format{html}
\precision{100}
\computeanswer{yes}
#define TITRE Dérivée d'un quotient
\integer{k=randint(-6..6)}
\text{ta=\a}
#if defined TARGET_derquot1
\title{TITRE 1}
\integer{a=randint(1..9)}
\integer{b=randint(1..9)}
\integer{a2=2*\a}
\integer{a3=3*\a}
\function{f=sqrt(x)/(\a*x^2+\b)}
\text{td=texmath(\a*x^2+\b)}
\text{tn6=texmath(\b-\a3*x^2)}
\text{tf=\frac{\sqrt{x}}{\td}}
\text{f1=random(\(f) est définie sur \(\lbrack 0; +\infty \lbrack),\(f) est définie en 0)}
\text{f2=random(\(f) est dérivable sur \(\lbrack 0; +\infty \lbrack),\(f) est dérivable en 0)}
\text{f3=\(f'(x)=\frac{\frac{1}{2\sqrt{x}}}{\a2 x})}
\text{f4=\(f'(x)=\frac{\a2 x\sqrt{x}-\frac{1}{2\sqrt{x}}(\td)}{(\td)^2})}
\text{f5=\(f'(x)=\frac{\frac{1}{2\sqrt{x}}(\td)-\a2 x\sqrt{x}}{(\td)^2})}
\text{f6=\(f'(x)=\frac{\tn6}{2\sqrt{x}(\td)^2})}
\text{lstrep=\f3,\f4,\f5,\f6}
\text{ind=shuffle(4)}
\text{lstrep=\f1,\f2,\lstrep[\ind[1]],\lstrep[\ind[2]],\lstrep[\ind[3]],\lstrep[\ind[4]]}
\integer{i5=position(3,\ind)+2}
\integer{i6=position(4,\ind)+2}
\statement{
   Soit \(f) la fonction définie sur \(\ \RR) par
<div class="wimscenter"> \(f(x)=\tf)</div>
   Cocher les bonnes réponses&nbsp;:
<ul>
 <li>\embed{reply1,1}</li>
 <li>\embed{reply1,2}</li>
 <li>\embed{reply1,3}</li>
 <li>\embed{reply1,4}</li>
 <li>\embed{reply1,5}</li>
 <li>\embed{reply1,6}</li>
</ul>
}
\answer{}{1,\i5,\i6;\lstrep}{type=checkbox}
#endif

#if defined TARGET_derquot2
\title{TITRE 2}
\integer{a=randint(2,3,5,6,7,9)}
\integer{b=randint(1..10)}
\text{f1=\frac{\a x^2}{x+\b}}
\text{f2=\frac{\sqrt{\a}}{x+\b}}
\text{f3=\frac{1}{x+\b}}
\text{f4=\frac{\cos{\theta}}{x+\b}}
\text{lstrep=\(f(x)=\f1),\(f(x)=\f2),\(f(x)=\f3),\(f(x)=\f4)}

\statement{<p>
   Dans quels cas peut-on utiliser la formule \(\left ( \frac{1}{u} \right ) ' = -\frac{u'}{u^2})?</p>
<ul>
 <li>\embed{reply1,1}</li>
 <li>\embed{reply1,2}</li>
 <li>\embed{reply1,3}</li>
 <li>\embed{reply1,4}</li>
</ul>
}
\answer{}{2,3,4;\lstrep}{type=checkbox}{option=shuffle}

#endif
#if (defined TARGET_derquot3 || defined TARGET_derquot4 )
\text{val=wims(makelist x,-x for x=1 to 5)}
\text{val=shuffle(\val)}

\integer{n=randint(1,2)}
\integer{p=\n=1?2:1}
\integer{a=\val[1]}
\integer{c=\val[2]}
\integer{d=\val[3]}
\integer{b=randint(-5..5)}

#if defined TARGET_derquot3
\title{TITRE 3}
\function{f=(\b+\a*x)/(\c*x+\d)}
\text{tf=\frac{texmath(maxima(\a*x+\b))}{texmath(maxima(\c*x+\d))}}
#endif
#if defined TARGET_derquot4
\title{TITRE 4}
\function{f=(\b+\a*x^\n)/(\c*x^\p+\d)}
\text{tf=\frac{texmath(maxima(\a*x^\n+\b))}{texmath(maxima(\c*x^\p+\d))}}
#endif
\function{fder=diff(\f,x)}
\statement{
   Calculer \(f'(x)) pour \(f(x)=\tf)
<div class="wimscenter"><label for="reply1">\(f'(x)=)</label> \embed{reply1}.</div>
}
\answer{}{\fder}{type=formal}
#endif
#if defined TARGET_derquot5
\title{TITRE 5}
\text{val=wims(makelist x,-x for x=1 to 5)}
\text{val=shuffle(\val)}

\integer{n=randint(1,2)}
\integer{p=\n=1?2:1}
\integer{a=\val[1]}
\integer{b=\val[2]}
\integer{c=\val[3]}
\integer{m=\val[4]}
\integer{p=\val[5]}
\integer{a2=\a*\m}
\integer{b2=\a*\p+\b*\m}
\integer{c2=\b*\p+\c}
\function{f=(\a2*x^2+\b2*x+\c2)/(\m*x+\p)}
\text{tf=\frac{texmath(maxima(\a2*x^2+\b2*x+\c2))}{texmath(maxima(\m*x+\p))}}
\function{nd=(2*\a2*x+\b2)*(\m*x+\p)-\m*(\a2*x^2+\b2*x+\c2)}
\rational{s=simplify(-\p/\m)}
\text{ts=texmath(\s)}
\function{fp=diff(\f,x)}
\text{td=texmath(\m*x+\p)}
\text{td2=texmath((\m*x+\p)^2)}
\integer{nc=-\m*\c}
\statement{
   Soit la fonction \(f) définie sur \(\RR \setminus \{ \ts \} ) par
<div class="wimscenter"> \(f(x)=\tf)</div>
<ol>
<li> Calculer \(f'(x))&nbsp;:

<table class="wimscenter">
<tr>
  <td rowspan="3"> \(f'(x) =)</td>
  <td>\embed{reply1}</td>
</tr>
<tr><td><hr></td></tr>
<tr>
  <td> \(\td2)</td>
</tr></table>
</li><li>
  Vérifier que pour tout \(x \not = \ts), \(f(x)=a x+b+\frac{c}{\td}).
  Déterminer les réels \(a,b) et \(c)&nbsp;:
<ul><li><label for="reply2">\(a=)</label> \embed{reply2,3} </li>
<li><label for="reply3">\(b=)</label> \embed{reply3,3} </li>
<li><label for="reply4">\(c=)</label> \embed{reply4,3} </li>
</ul>
</li><li>
   Calculer \(f'(x)) à partir de cette nouvelle écriture de \(f(x))&nbsp;:

\special{mathmlinput [f'(x) = reply5  + \frac{ reply6}{\td2}], 7
reply 5
reply 6
}
</li>
</ol>
}
\answer{\(f'(x))}{\nd}{type=formal}
\answer{a}{\a}{type=numeric}
\answer{b}{\b}{type=numeric}
\answer{c}{\c}{type=numeric}
\answer{partie entière}{\a}{type=numeric}
\answer{partie fractionnaire}{\nc}{type=numeric}
#endif
