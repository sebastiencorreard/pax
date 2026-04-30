target=compare1 compare2 compare3 compare4 compare5

#define TITRE Comparaison de nombres
#include "author.inc"
#if defined TARGET_compare1
\title{TITRE 1}
\integer{a=randint(15..19)}
\integer{b=randint(21..29)}
\rational{p=\a/\b}
\rational{q=\a / (\b+1)}
\rational{s=(\a+1)/ (\b+1)}
\rational{t=(\a+2)/(\b+2)}
\text{liste=\(\q),\(\p),\(\s),\(\t)}
\text{size=60x60x4}
\statement{
<span class="wims_warning">À faire sans calculatrice&nbsp;!</span><p>
  Classez les fractions de la plus petite à la plus grande&nbsp;:</p>
<div>\embed{reply1,\size}</div>
}
\answer{}{\liste;\liste}{type=clickfill}{option=shuffle}
#endif
#if defined TARGET_compare2
\title{TITRE 2}
\statement{
<ol>
<li>Donner un exemple de deux entiers \(a\) et \(b\) tels que \(\frac{a+1}{b} < \frac{a+2}{b+2}\)<p>
<label for="reply1">\(a=\)</label>\embed{reply1,3};<label for="reply2">\(b=\)</label>\embed{reply2,3}</p></li>
<li>Donner un exemple de deux entiers \(c\) et \(d\) tels que \(\frac{c+1}{d} > \frac{c+2}{d+2}\)<p>
<label for="reply3">\(c=\)</label>\embed{reply3,3};<label for="reply4">\(d=\)</label>\embed{reply4,3}</p></li>
<li>Donner un exemple de deux entiers \(e\) et \(f\) tels que \(\frac{e+1}{f} = \frac{e+2}{f+2}\)<p>
<label for="reply5">\(e=\)</label>\embed{reply5,3};<label for="reply6">\(f=\)</label>\embed{reply6,3}</p></li>

</ol>
}
\answer{a}{\a}{type=numeric}
\answer{b}{\b}{type=numeric}
\answer{c}{\c}{type=numeric}
\answer{d}{\d}{type=numeric}
\answer{e}{\e}{type=numeric}
\answer{f}{\f}{type=numeric}
\condition{valeurs a et b}{2*\a < \b -2}
\condition{valeurs c et d}{2*\c > \d -2}
\condition{valeurs e et f}{2*\e=\f-2}
#endif
#if defined TARGET_compare3
\title{TITRE 3}
\text{lstrep=<,>}
\statement{
  Sachant que \(a\) et \(b\) sont deux entiers tels que \( a > b > 0 \),
<ol>
<li><label for="reply1">Comparer</label>\(p=\sqrt{a^2+b^2}\) \embed{reply1} \(q=a+b\)</li>
<li><label for="reply2">Comparer</label>\(r=\sqrt{a^2-b^2}\) \embed{reply2} \(s=a-b\)</li>
<li><label for="reply3">Comparer</label>\(u=\sqrt{a^2+b}\) \embed{reply3} \(v=a+\sqrt{b}\)</li>
<li>Donner un exemple, avec <span class="nowrap">\(a=b+1\),</span> tel que <span class="nowrap">\(v > p\) :</span>
<br><label for="reply4">Valeur de \(a=\)</label>\embed{reply4,3}</li>
<li>Donner un exemple, avec <span class="nowrap">\(a=b+1\),</span> tel que <span class="nowrap">\(v < p\) :</span>
<br><label for="reply5">Valeur de \(a=\)</label>\embed{reply5,3}</li>
</ol>
}
\answer{p et q}{1;\lstrep}{type=menu}
\answer{r et s}{2;\lstrep}{type=menu}
\answer{u et v}{1;\lstrep}{type=menu}
\answer{ a pour v<p}{\a1}{type=numeric}
\answer{ a pour v>p}{\a2}{type=numeric}
\condition{a pour v>p}{\a1<8}
\condition{a pour v<p}{\a2>=8}
#endif
#if defined TARGET_compare4
\title{TITRE 4}
\integer{c=randint(10..20)}
\rational{a=1/ \c}
\text{a_aff=texmath(\a)}
\rational{b=(2-\a)^2/(4*\a)}
\integer{k=randint(1,2)}
\integer{b=\k=2?floor(\b):floor(\b)+1}
\integer{b2=\b+2}
\text{lstrep=<,>}
\statement{
<span class="wims_warning">À faire sans calculatrice !
</span>
<div>
  <label for="reply1">Comparer :</label> \(\sqrt{\b2}-\sqrt{\b}\) \embed{reply1} \(\sqrt{\a_aff}\)
</div>
}
\answer{x et y}{\k;\lstrep}{type=menu}
#endif
#if defined TARGET_compare5
\title{TITRE 5}
\integer{a=randint(4..9)}
\integer{b=\a+1}
\integer{c=\a-1}
\integer{d=2*\a}
\rational{e=0.0001}
\integer{f=randint(-10..-7)}
\integer{valz=(-c)^{\d}}
\integer{valt=\e^{\f}}
\text{x=\(\a^{\b})}
\text{y=\(\b^\a)}
\text{z=\((-\c)^{\d})}
\text{t=\(\e^{\f})}
\text{size=120x60x4}
\text{liste=\valz>\valt?\y,\x,\t,\z:\y,\x,\z,\t}
\statement{
<span class="wims_warning">À faire sans calculatrice !</span><p>
  Classer les nombres suivants par ordre croissant&nbsp;:</p>
<div >\embed{reply1,\size}</div>
}
\answer{}{\liste;\liste}{type=clickfill}{option=shuffle}
#endif
