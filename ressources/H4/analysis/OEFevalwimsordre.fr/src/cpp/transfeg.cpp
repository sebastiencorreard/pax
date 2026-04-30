target=transfeg1 transfeg2 transfeg3 transfeg4 transfeg5

\author{Régine, Mangeard;Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
#define TITRE Transformation d'une égalité
#if defined TARGET_transfeg1
\title{TITRE 1}
\integer{a=randint(2..8)*randint(1,-1)}
\integer{b=randint(2..8)*randint(1,-1)}
\integer{c=randint(2..8)*randint(1,-1)}
\integer{d=randint(2..8)*randint(1,-1)}
\integer{e=randint(2..8)*randint(1,-1)}
\integer{f=randint(2..8)*randint(1,-1)}
\integer{g=randint(2..8)*randint(1,-1)}
\integer{h=randint(2..8)*randint(1,-1)}
\integer{i=randint(2..8)*randint(1,-1)}
\integer{j=randint(2..8)*randint(1,-1)}
\integer{k=randint(2..8)*randint(1,-1)}
\integer{p=randint(2..8)*randint(1,-1)}
\text{eqa=\(texmath(\a*x+\b-3*\b)\)}
\integer{bb=\b-3*\b}
\text{eqfa=\a*x+\bb}

\text{eqb=\(texmath(\c*x+\d*x+\a)\)}
\integer{cc=\c+\d}
\text{eqfb=\cc*x+\a}

\text{eqc=\(texmath(\e*x+\f*y+\b)\)}
\text{eqfc=\e*x+\f*y+\b}

\text{eqd=\(texmath(\g*x^2+\h*x+\h*x^2)\)}
\integer{gg=\g+\h}
\text{eqfd=\gg*x^2+\h*x}

\text{eqe=\(texmath(\i*x^2+\j*x^2+\k)\)}
\integer{ii=\i+\j}
\text{eqfe=\ii*x^2+\k}

\text{eqf=\(texmath(\k*x+\p / x + \a*x +\b)\)}
\integer{kk=\k+\a}
\text{eqff=\kk*x+ \p / x + \b}

\statement{
  Réduire, quand c'est possible, les expressions suivantes&nbsp;: <br>
(<i>c'est-à-dire effectuer les sommes des quantités que l'on peut sommer.</i>)

<ol>
<li>A=\eqa<br><label for="reply1">A=</label>\embed{reply1}</li>
<li>B=\eqb<br><label for="reply2">B=</label>\embed{reply2}</li>
<li>C=\eqc<br><label for="reply3">C=</label>\embed{reply3}</li>
<li>D=\eqd<br><label for="reply4">D=</label>\embed{reply4}</li>
<li>E=\eqe<br><label for="reply5">E=</label>\embed{reply5}</li>
<li>F=\eqf<br><label for="reply6">F=</label>\embed{reply6}</li>
</ol>
}
\answer{A}{\eqfa}{type=algexp}
\answer{B}{\eqfb}{type=algexp}
\answer{C}{\eqfc}{type=algexp}
\answer{D}{\eqfd}{type=algexp}
\answer{E}{\eqfe}{type=algexp}
\answer{F}{\eqff}{type=algexp}
#else
# if defined TARGET_transfeg2
\title{TITRE 2}
\integer{a=randint(2..8)*randint(1,-1)}
\integer{b=randint(2..8)*randint(1,-1)}
\integer{c=randint(2..8)*randint(1,-1)}
\integer{d=randint(2..8)*randint(1,-1)}
\integer{e=\a+randint(2..5)}
\integer{e=\e=0?2}
\integer{f=\b-randint(2..5)}
\integer{f=\f=0?1}
\text{equat=\(texmath(\a*x+\b=\e*x+\f))}
\integer{a1=\e-\a}
\integer{b1=\f-\b}
\text{eq1d=\a1*x+\b1}
\integer{a2=-\a1}
\text{sa=\a>0?:-}
\text{se=\e>0?:-}
\integer{ap=\a>0?\a:-\a}
\integer{am=-\a}
\integer{ep=\e>0?\e:-\e}
\text{eq2g=\e>0?\a x - \e x: \a x +\ep x}
\text{eq2b1g=\e>0?\a x + \e x:\a x - \ep x}
\text{eq2b2g=\e>0?\am x - \e x: \am x +\ep x}
\text{eq2b3g=\e>0?\am x + \e x:\am x - \ep x}
\text{lst2g=\eq2g,\eq2b1g,\eq2b2g,\eq2b3g}
\text{sb=\b>0?:-}
\integer{bp=\b>0?\b:-\b}
\integer{bm=\b>0?-\b:\b}
\text{eq2d=\b>0?\f-\bp:\f +\bp}
\text{eq2b1d=\b>0?\f +\bp:\f-\bp}
\text{lst2d=\eq2d,\eq2b1d}
\text{eq3g=\a2*x}
\text{eq3d=\b1}
\integer{b2=-\b1}
\text{eq4g=\b2}
\text{eq4d=\a1*x}
\text{debut=<i>Rappel&nbsp;: une équation est une écriture qui comporte un signe égal
  situé entre des expressions à gauche et à droite, que l'on désigne par&nbsp;:
"le membre de gauche de l'équation", et "le membre de droite de l'équation".
 Ces expressions peuvent comporter des nombres et une ou plusieurs
  lettres qui représentent des quantités "inconnues".</i>}
\text{oldenonce=<ol>
<li> Transformez l'équation suivante de manière à ce que le membre
  de gauche soit zéro, et réduisez le membre de droite si c'est possible.
<div class="wimscenter">\equat équivaut à \(0=\)\embed{reply1,7}</div></li>
}
\statement{
  Ceci est une équation dont l'inconnue est \(x\)&nbsp;:
<div class="wimscenter">\equat</div>
<ol>
<li> Transformez cette équation de manière à ce que les termes en "\(x\) "
  soient tous du côté gauche, et seulement ces termes.<p>
\embed{reply1}=\embed{reply2}</p></li>
<li> Réduisez chaque membre de l'équation&nbsp;:<p>
\embed{reply3,7}=\embed{reply4,7}</p></li>
<li> Transformez à nouveau cette nouvelle équation, réduite, de manière que le terme en "\(x\) "
  soit du côté droit de l'équation&nbsp;:<p>
\embed{reply5,3}=\embed{reply6,3} \(x\)
</p></li>
</ol>
}
answer{équation 1 droite}{\eq1d}{type=algexp}
\answer{équation 2 gauche}{1;\lst2g}{type=menu}{option=shuffle}
\answer{équation 2 droite}{1;\lst2d}{type=menu}{option=shuffle}
\answer{équation 3 gauche}{\eq3g}{type=algexp}
\answer{équation 3 droite}{\eq3d}{type=algexp}
\answer{équation 4 gauche}{\rep3}{type=numeric}
\answer{équation 4 droite}{\rep4}{type=numeric}
\condition{(\reply6=\a1 and \reply5=\b2) or (\reply6=-\a1 and \reply5=-\b2)}
#endif
#if defined TARGET_transfeg3
\title{TITRE 3}
\integer{a=randint(2..8)*randint(1,-1)}
\integer{b=randint(2..8)*randint(1,-1)}
\text{equat=\(texmath(\a*x+\a*x^2=\a*\b+1)\)}
\text{eq1d=\b+1/\a}
\text{lstrep=Si \(k \not = 0\), Si \(k \le 0\), Si \(k \ge 0\)}
\text{equat2=\(k\times x+ k\times x^2= \b \times k +1\)}
\statement{
<ol>
<li><div class="wimscenter">\equat</div>
  Transformez cette équation de manière à ce que le membre de gauche soit devenu \(x+x^2\),
  et qu'il n'y ait plus de termes comportant "\(x\) " à droite.<p>
<label for="reply1">\(x+x^2=\)</label>\embed{reply1}</p></li>
<li> À quelle condition sur le nombre \(k\) pouvez-vous faire de même ici&nbsp;:
<div class="wimscenter">\equat2</div>
\embed{reply2}</li>
</ol>
}
\answer{équation 1 droite}{\eq1d}{type=algexp}
\answer{}{1;\lstrep}{type=radio}
#endif
#if defined TARGET_transfeg4
\title{TITRE 4}
\integer{a=randint(-5,-4,-3,-2,1,2,3,4,5)}
\text{equat=\(texmath(\a+1=1/x)\)}
\text{eq1d=1/(\a+1)}
\statement{
 Transformez l'équation suivante de manière que l'inconnue "\(x\) " ne soit plus
 sous une barre de dénominateur et qu'il soit le membre de gauche.
<div class="wimscenter">\equat</div>
<label for="reply1">\(x=\)</label>\embed{reply1,7}
}
\answer{membre de droite}{\eq1d}{type=algexp}
#endif
#if defined TARGET_transfeg5
\title{TITRE 5}
\computeanswer{yes}
\integer{a=randint(2,3,5,6,7,8)}
\text{eq1g=\a^2+\a-1+2*\a*sqrt(\a)}
\text{equat=\(texmath(\a+sqrt(\a)=sqrt(x+1))\)}
\statement{
  Dans cette équation, on suppose que \(x \ge -1\), pour que le membre de droite ait un sens.<p>
  Transformez cette équation de manière à ce que le membre de droite soit <span class="nowrap">"\(x\) " :</span>
</p>
<div class="wimscenter"><label for="reply1">\equat équivaut à</label> \embed{reply1,10}=\(x\)</div>
<div class="wims_instruction"> Taper <span class="tt">sqrt(a)</span> pour \(sqrt(a)\).</div>
}
\answer{membre de gauche}{\eq1g}{type=algexp}
# endif
#endif
