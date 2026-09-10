target=axecentresym1 axecentresym2 axecentresym3 axecentresym4 axecentresym5
#include "author.inc"
\precision{1000}
#include "lang.inc"
#include "lang_titles.inc"
#if defined TARGET_axecentresym1
\integer{a=randint(1..10)}
\integer{n=randint(1..5)}
\integer{b=\a+\n}
\integer{k1=randint(1,2)}
\if{\k1=1}{
\text{quest1=Soit \(f) une fonction définie sur \(\RR).<br>
 Si \(f(\a)) et \(f(-\a)) sont des nombres opposés, alors on peut en déduire
  que la courbe de \(f) est symétrique par rapport à l'origine du repère}
\integer{rep1=2}
}{
\text{quest1=Soit \(f) une fonction définie sur \(\RR).<br>
 Si \(f(\a)) et \(f(-\a)) ne sont pas des nombres opposés, alors on peut en déduire
  que la courbe de \(f) n'est pas symétrique par rapport à l'origine du repère}
\integer{rep1=1}
}
\integer{k2=randint(1,2)}
\if{\k2=1}{
\text{quest2=Soit \(f) une fonction définie sur &#91; -\a;\b &#93;.<br>
 Sa courbe représentative ne sera jamais symétrique par rapport à l'axe des ordonnées}
\integer{rep2=1}
}{
\text{quest2=Soit \(f) une fonction définie sur &#91; -\a;\b &#93;.<br>
 Sa courbe représentative peut être symétrique par rapport à l'axe des ordonnées}
\integer{rep2=2}
}
\integer{k3=randint(1,2)}
\rational{nd=simplify(\n/2)}
\text{tnd=\(texmath(\nd))}
\rational{bd=simplify(\b/2)}
\text{tbd=\(texmath(\bd))}
\if{\k3=1}{
  \text{quest3=Soit \(f) une fonction définie sur &#91; -\a;\b &#93;.<br>
  Sa courbe représentative peut être symétrique par rapport à un point d'abscisse \tnd.}
  \integer{rep3=1}
}{
\text{quest3=Soit \(f) une fonction définie sur &#91; -\a;\b &#93;.<br>
 Sa courbe représentative peut être symétrique par rapport à un point d'abscisse \tbd.}
\integer{rep3=2}
}
\statement{
  Vrai ou Faux:
<ol>
<li> \quest1: \embed{reply1} </li>
<li> \quest2: \embed{reply2} </li>
<li> \quest3: \embed{reply3} </li>
</ol>
}
\answer{\quest1}{\rep1;Vrai, Faux}{type=radio}
\answer{\quest2}{\rep2;Vrai, Faux}{type=radio}
\answer{\quest3}{\rep3;Vrai, Faux}{type=radio}
#endif
#if defined TARGET_axecentresym2
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)*randint(1,-1)}
\integer{n=randint(2..5)*2}
\integer{p=randint(1..\n-1)*2}
\integer{q=randint(1..\n-1)*2+1}
\text{flist=texmath(\a*x^\n+\b*x^\p+\c),\RR,2,2
texmath(\b*x-\c/x),\RR^*,1,1
texmath(\b*x^\q-\c*x),\RR,1,1
texmath(\a*x^\n-\c*cos(x)),\RR,2,2
texmath(\a*x^\q+\c*sin(x)),\RR,1,1}
\text{ind=shuffle(5)}
\text{data1=row(\ind[1],\flist)}
\text{f1=\data1[1]}
\text{D1=\data1[2]}
\integer{rep1=\data1[3]}
\integer{rep2=\data1[4]}
\text{data2=row(\ind[2],\flist)}
\text{f2=\data2[1]}
\text{D2=\data2[2]}
\integer{rep3=\data2[3]}
\integer{rep4=\data2[4]}
\text{lstrep1=\(f(-x)=-f(x)),\(f(-x)=f(x))}
\text{lstrep2=La courbe de \(f) est symétrique par rapport à l'origine du repère,La courbe de \(f) est symétrique par rapport à l'axe des ordonnées}
\statement{
  Comparer \(f(x)) et \(f(-x)) pour tout \(x) de \(\mathcal{D}) et
  interpréter graphiquement:
<ul>
<li>\(f(x)=\f1) et \(\mathcal{D}=\D1) :
  <ol>
  <li>\embed{reply1}</li>
  <li>\embed{reply2,1}<br>\embed{reply2,2}</li>
 </ol>
</li>
<li>\(f(x)=\f2) et \(\mathcal{D}=\D2) :
  <ol>
 <li>\embed{reply3}</li>
 <li>\embed{reply4,1}<br>\embed{reply4,2}</li>
 </ol>
</li>
</ul>
}
\answer{}{\rep1;\lstrep1}{type=radio}{option=shuffle}
\answer{}{\rep2;\lstrep2}{type=radio}{option=shuffle}
\answer{}{\rep3;\lstrep1}{type=radio}{option=shuffle}
\answer{}{\rep4;\lstrep2}{type=radio}{option=shuffle}
#endif
#if (defined TARGET_axecentresym3  || defined TARGET_axecentresym4 )
\integer{a=randint(1..10)*randint(1,-1)}
\integer{b=randint(1..10)*randint(1,-1)}
\integer{a2=\a*2}
\integer{b2=\b*2}
#if defined TARGET_axecentresym3
\text{lstrep=Pour tout \(x)&#44; \(f(\a+x)+f(\a-x)=\b2),Pour tout \(x)&#44; \(f(-x)=-f(x)),Pour tout \(x)&#44; \(f(\a2-x)+f(x)=\b2),Pour tout \(x)&#44; \(f(\a2-x)=f(x)),Pour tout \(x)&#44; \(f(-x)=f(x)),Pour tout \(x)&#44; \(f(\a-x)=f(\a+x))}
\text{rep=1,3}
\text{tsym=au point \(I(\a;\b))}
#else
\text{lstrep=Pour tout \(x)&#44; \(f(\a+x)=f(\a-x)),Pour tout \(x)&#44; \(f(-x)=f(x)),Pour tout \(x)&#44; \(f(\a2-x)+f(x)=0),Pour tout \(x)&#44; \(f(\a2-x)=f(x)),Pour tout \(x)&#44; \(f(-x)=-f(x)),Pour tout \(x)&#44; \(f(\a-x)-f(\a+x)=0)}
\text{rep=1,4,6}
\text{tsym=à la droite d'équation \(x=\a)}
#endif
\statement{
  On sait qu'une fonction \(f) est définie sur \(\RR) et que sa courbe représentative est symétrique par rapport \tsym.
  <p>
  Cela se traduit par:
  </p>
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
<li>\embed{reply1,6}</li>
</ul>
<div class="wims_instruction">Cocher toutes les bonnes réponses.</div>
}
\answer{}{\rep;\lstrep}{type=checkbox}{option=shuffle}
#endif
#if defined TARGET_axecentresym5
\text{lval=wims(makelist x,-x for x=1 to 5)}
\text{lval=shuffle(\lval)}
\integer{a=\lval[1]}
\integer{ma=-\lval[1]}
\integer{b=\lval[2]}
\integer{mb=-\lval[2]}
\integer{c=\lval[3]}
\integer{mc=-\lval[3]}
\integer{k=\lval[4]}
\integer{mk=-\lval[4]}
\integer{yw=\a*\k+\b}
\integer{yw2=2*\yw}
\text{g=texmath(\a*x+\b+\c/(x-\k))}
\text{lstrep=\a,\b,\c,\k,\ma,\mb,\mc,\mk,\yw}
\text{lstrep=wims(listuniq \lstrep)}
\statement{
  Soit \(g) la fonction définie sur \(\RR \setminus \{\k\}) par:
<div class="wimscenter">\(g(x)=\g)</div>
  On sait que la courbe de \(g) possède un centre de symétrie \(\Omega).
<ul>
<li> Quelle est l'abscisse \(\omega) de \(\Omega) ? \embed{reply1} </li>
<li> Calculer
\(g(\omega +x)+g(\omega -x)) pour \(\omega+x) et \(\omega-x) différents de \k.<br>
<label for="reply2">\(g(\omega +x)+g(\omega -x))=</label>\embed{reply2,4}</li>
<li> En déduire l'ordonnée de \(\Omega): \embed{reply3}</li>
</ul>
}
\answer{abscisse}{4;\lstrep}{type=radio}{option=shuffle}
\answer{}{\yw2}{type=numeric}
\answer{ordonnée}{9;\lstrep}{type=radio}{option=shuffle}
#endif
