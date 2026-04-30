target=soleq1 soleq2 soleq3 soleq4 soleq5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{100}
#define TITRE Solution d'une équation
#if (defined TARGET_soleq1 || defined TARGET_soleq2 || defined TARGET_soleq3 || defined TARGET_soleq4 )
#if defined TARGET_soleq1
\title{TITRE 1}
\integer{a=randint(2..9)}
\text{equat=\a x =0}
\integer{x1=-\a}
\text{x2=\(\frac{1}{\a}\)}
\integer{x3=0}
\text{txl=shuffle(\x1,\x2,\x3)}
\text{x1=\txl[1]}
\text{x2=\txl[2]}
\text{x3=\txl[3]}
\if{\x1=0}{
  \text{rep=1,2,2}
}{
  \if{\x2=0}{
    \text{rep=2,1,2}
  }{
    \text{rep=2,2,1}
  }
}
\text{ind=1,2,3}
#else
\integer{a=randint(2..9)}
\integer{b=\a+randint(2..9)}
\text{signe=+,-}
\integer{ia=randint(1,2)}
\integer{ib=randint(1,2)}
\text{sa=\ia=2?-}
\text{sb=\ib=2?-}
\integer{ix=\ia*\ib}
\text{sx=\ix=2?-}
#if defined TARGET_soleq2
\title{TITRE 2}
\text{equat=\sa \a x =\sb \b}
#endif
#if defined TARGET_soleq3
\title{TITRE 3}
\text{equat=texmath(\sa \a*x - \sb\b)=0}
#endif
#if defined TARGET_soleq4
\title{TITRE 4}
\integer{c=randint(2..8)*randint(1,-1)}
\integer{e=\sa \a+\c}
\integer{d=randint(2..8)*randint(1,-1)}
\integer{f=-(\sb \b)+\d}

\text{equat=texmath(\c*x +\d)=texmath(\e*x+\f)}
#endif
\text{tx1=\(\sx\frac{\b}{\a}\)}
\text{tx2=\(\sx\frac{\a}{\b}\)}
\integer{x3=\sb \b - \sa \a}
\text{tx3=\x3}
\text{txl=\tx1,\tx2,\tx3}
\text{ind=shuffle(3)}
\integer{ind1=position(1,\ind)}
\if{\ind1=1}{
  \text{rep=1,2,2}
}{
    \if{\ind1=2}{\text{rep=2,1,2}}{\text{rep=2,2,1}}
}
#endif
\statement{
  Dire si les valeurs suivantes sont solutions de l'équation <span class="nowrap">\(\equat\).</span>
<ul>
<li>\txl[\ind[1]] est solution: \embed{reply1}</li>
<li>\txl[\ind[2]] est solution: \embed{reply2}</li>
<li>\txl[\ind[3]] est solution: \embed{reply3}</li>
</ul>
}
\answer{\txl[1]}{\rep[1];Oui,Non}{type=radio}
\answer{\txl[2]}{\rep[2];Oui,Non}{type=radio}
\answer{\txl[3]}{\rep[3];Oui,Non}{type=radio}
#endif
#if defined TARGET_soleq5
\title{TITRE 5}
\integer{a1=randint(2..6)*randint(1,-1)}
\integer{a2=randint(2..6)*randint(1,-1)}
\integer{b1=randint(2..6)*randint(1,-1)}
\integer{b2=randint(2..6)*randint(1,-1)}
\integer{c1=randint(2..6)*randint(1,-1)}
\integer{c2=randint(2..6)*randint(1,-1)}
\integer{d1=randint(2..6)*randint(1,-1)}
\integer{d2=randint(2..6)*randint(1,-1)}
\integer{colin=\c1*\d2-\c2*\d1}
\text{numequat1=texmath(\a1*x+\b1)}
\text{denequat1=texmath(\c1*x+\d1)}
\text{numequat2=texmath(\a2*x+\b2)}
\text{denequat2=texmath(\c2*x+\d2)}
\text{equat1=\(\frac{\numequat1}{\denequat1}=\frac{\numequat2}{\denequat2})}
\text{equat2=\((\numequat1)(\denequat2)=(\numequat2)(\denequat1))}
\rational{x1=simplify(-\d1 / \c1)}
\rational{x2=simplify(-\d2 / \c2)}
\text{tx1=texmath(\x1)}
\text{tx2=texmath(\x2)}
\rational{y1=simplify(-\b1 / \a1)}
\rational{y2=simplify(-\b2 / \a2)}
\integer{coliny=\a1*\b2-\a2*\b1}
\text{ty1=texmath(\y1)}
\text{ty2=texmath(\y2)}
\if{\colin<>0 and \coliny<>0}{
  \integer{rep=4}
  \text{lstrep=toutes valeurs de \(x\), pour tout \(x \not= \tx1\), pour tout \(x \not= \tx2\), pour tout \(x \not= \tx1\) et \(x \not= \tx2\),
  pour tout \(x \not= \ty1\), pour tout \(x \not= \ty2\), pour tout \(x \not= \ty1\) et \(x \not= \ty2\)}
}
\if{\colin=0 and \coliny<>0}{
  \integer{rep=2}
  \text{lstrep=toutes valeurs de \(x), pour tout \(x \not= \tx1\),
  pour tout \(x \not= \ty1\), pour tout \(x \not= \ty2\), pour tout \(x \not= \ty1\) et \(x \not= \ty2\)}
}
\if{\colin<>0 and \coliny=0}{
  \integer{rep=2}
  \text{lstrep=toutes valeurs de \(x\), pour tout \(x \not= \tx1\), pour tout \(x \not= \tx2\), pour tout \(x \not= \tx1\) et \(x \not= \tx2\),
  pour tout \(x \not= \ty1\)}
}
\if{\colin=0 and \coliny=0}{
  \integer{rep=2}
  \text{lstrep=toutes valeurs de \(x\), pour tout \(x \not= \tx1\),
  pour tout \(x \not= \ty1\)}
}
\integer{nbsol=items(\lstrep)}
\statement{
  Pour quelles valeurs de \(x\), les équations suivantes sont-elles équivalentes&nbsp;?
<div class="wimscenter">\equat1</div>
  et <div class="wimscenter"> \equat2</div>
  Les équations sont équivalentes pour&nbsp;:
<div class="wimscenter">\embed{reply1,1},\embed{reply1,2},\embed{reply1,3}<br>
\if{\nbsol>3}
 {
\embed{reply1,4},\embed{reply1,5}<br>
 \if{\nbsol>5}
 {
\embed{reply1,6},\embed{reply1,7}<br>
 }
}
</div>
}
\answer{condition}{\rep;\lstrep}{type=radio}{option=shuffle}
#endif
