target=eqtgte1 eqtgte2 nbderiv txvarh
#if defined TARGET_eqtgte1
#define NUM 1
#endif
#if defined TARGET_eqtgte2
# define NUM 2
#endif
#if defined TARGET_eqtgte2 || TARGET_eqtgte1
\title{Nombre dérivé et équation de la tangente NUM}
\keywords{derivative,tangent}
#endif
#if defined TARGET_nbderiv
\title{Nombre dérivé}
\keywords{derivative}
#endif
#if defined TARGET_txvarh
\title{Calcul taux de variation entre a et a+h}
#endif
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{a=randint(1..5)*randitem(-1,1)}
\integer{b=randint(1..5)}
\integer{c=randint(1..5)}

\text{flist=x^2, \a*x^2, \a/x, \a/(x-\b),\a/(x+\b),\a*x^2 + \b*x,\a*x^2 - \b*x, \a*x^2 + \b*x + \c,\a*x^2 - \b*x + \c, \a*x^2 +\b*x -\c, \a*x^2 -\b*x -\c,\a*x+\c,\a*x -\c}
\text{deflist=\(\,\RR), \(\,\RR), \(\,\RR^*), \(\RR \setminus \left\lbrace \b \right\rbrace\),\(\RR \setminus\left\lbrace -\b\right\rbrace\),\(\,\RR) ,\(\,\RR),\(\,\RR),\(\,\RR),\(\,\RR), \(\,\RR),\(\,\RR), \(\,\RR)}
\integer{nbf=items(\flist)}
\integer{n=randint(1..\nbf)}
\function{f=item(\n,\flist)}
\text{defdom=\deflist[\n]}
\text{ft=item(\n,x^2, \a x^2, \frac{\a}{x}, \frac{\a}{x-\b},\frac{\a}{x+\b},\a x^2 + \b x,\a x^2 - \b x,\a x^2 + \b x + \c,\a x^2 - \b x + \c,\a x^2 + \b x - \c,\a x^2 - \b x - \c,\a x+\c, \a x - \c)}
\integer{x0=random(-3..3)}
\if{\n=3 and \x0=0}{\integer{x0=randint(1..3)*randitem(1,-1)}}
\if{\n=4 and \x0=\b}{\integer{x0=\x0+1}}
\if{\n=5 and \x0=-\b}{\integer{x0=\x0+1}}

\function{fp=diff(\f,x)}
\rational{nder=evalue(\fp,x=\x0)}

\function{y0=wims(mathsubst x=(\x0) in \f)}
\function{y0=simplify(\y0)}
\function{y0h=wims(mathsubst x=(\x0+h) in \f)}
\function{y0h=pari(\y0h)}
\function{y1=(\y0h - (\y0))/h}
\function{y1=simplify(\y1)}
## tangente
\text{eqtgte=simplify(y= \nder*(x-(\x0))+(\y0))}

%%%% solution %%%%%%%%%%%%
\text{fx00=texmath(\f)}
\if{\x0>=0}
 {\text{fx00=wims(replace internal x by \x0 in \fx00)}}
 {\if{\n isin 345}
  {\text{fx00=wims(replace internal x by \x0 in \fx00)}}
  {\text{fx00=wims(replace internal x by (\x0) in \fx00)}}
 }
\text{fx0=wims(replace internal x by (\x0) in \f)}
\text{fx0h=wims(replace internal x by (\x0+h) in \f)}
\text{fx0hb=pari(\fx0h)}
\text{fx0hbsol=texmath(pari(\fx0h))}
\text{fpx0=wims(replace internal x by (\x0)  in \fp)}
\text{y1sol=pari(\y1)}
\text{y1sol=texmath(\y1)}
\text{y0sol=texmath(\y0)}
\text{fx0sol=texmath(\fx0)}
\text{y0hsol=texmath(\y0h)}
\text{ndersol=texmath(\nder)}
\text{xmoinsx0=pari(x-(\x0))}
\text{eqtgtesol=pari(\eqtgte)}
\text{eqtgtesol=texmath(\eqtgtesol)}
\text{fp=texmath(\fp)}
%%%%%%%%%%%%%%%%%%%%%%%%%%

\statement{
Soit la fonction \(f) définie sur <span class="nowrap">\defdom</span> d'expression algébrique
<span class="nowrap">\(f(x)=)\(\ft).</span>

#if defined TARGET_txvarh
<p>On veut calculer le taux de variation de \(f) entre les points de la courbe
d'abscisse \(x=\x0) et <span class="nowrap">\(x=\x0+h),</span> \(h) étant un réel non nul.</p>
<div class="wims_question"><ol>
<li>Calculer <span class="nowrap">\(f(\x0)\) :</span>
<div class="unbreakable"><label for="reply1">\(f(\x0)={})</label>\embed{reply1,10}</div>
</li>
<li>Exprimer \(f(\x0+h)) en fonction de <span class="nowrap">\(h)&nbsp;:</span>
<div class="unbreakable"><label for="reply2">\(f(\x0+h)={})</label> \embed{reply2,10}</div>
</li>
<li>Exprimer le rapport \(\frac{f(\x0+h)-f(\x0)}{h}) en fonction de <span class="nowrap">\(h)&nbsp;:</span>
<div class="unbreakable"><label for="reply3">\(\frac{f(\x0+h)-f(\x0)}{h}={}\)</label>\embed{reply3,10}</div></li>
</ol>
</div>
#endif

#if defined TARGET_eqtgte1 || TARGET_nbderiv
<p>On veut calculer le nombre dérivé de \(f) en <span class="nowrap">\(x=\x0).</span></p>
<div class="wims_question"><ol>
<li>Calculer <span class="nowrap">\(f(\x0)\) :</span>
<div class="unbreakable"><label for="reply1">\(f(\x0)={})</label>\embed{reply1,10}</div>
</li>
<li>Pour \(h\) un réel non nul, exprimer \(f(\x0+h)) en fonction de <span class="nowrap">\(h)&nbsp;:</span>
<div class="unbreakable"><label for="reply2">\(f(\x0+h)={})</label> \embed{reply2,10}</div></li>
<li>Exprimer le rapport \(\frac{f(\x0+h)-f(\x0)}{h}) en fonction de <span class="nowrap">\(h)&nbsp;:</span>
<div class="unbreakable"><label for="reply3">\(\frac{f(\x0+h)-f(\x0)}{h}={}\)</label>\embed{reply3,10}</div></li>
<li>En déduire la valeur du nombre dérivé de \(f) en <span class="nowrap">\(x=\x0).</span>
<div class="unbreakable"><label for="reply4">\(f^{\prime}(\x0)=\)</label> \embed{reply4,10}</div>
</li>
#endif
#if defined TARGET_nbderiv
</ol></div>
#endif
#if defined TARGET_eqtgte1
<li><label for="reply5">Déterminer l'équation de la tangente à la courbe représentative de \(f)
au point d'abscisse <span class="nowrap">\(\x0)&nbsp;:</span></label>
<div class="unbreakable">Votre réponse&nbsp;: \embed{reply5}</div></li>
</ol></div>
#endif
#if defined TARGET_eqtgte2
<div class="wims_question"><ol>
<li>Calculer <span class="nowrap"><label for="reply1">\(f^'(\x0)=)</label>\embed{reply1,8}</span></li>
<li>Déterminer l'équation de la tangente à la courbe représentative
  \(f) au point d'abscisse <span class="nowrap">\(\x0)&nbsp;:</span>
<div class="unbreakable"><label for="reply2">Votre réponse&nbsp;:</label>\embed{reply2,16}</div></li>
</ol></div>
#endif
}
#if defined TARGET_eqtgte1 || TARGET_nbderiv || TARGET_txvarh
\answer{}{\y0}{type = numexp}{option=noreduction}
\answer{}{\y0h}{type = formal}
\answer{}{\y1}{type = formal}
#endif
#if defined TARGET_eqtgte1 || TARGET_eqtgte2
\answer{}{\nder}{type = numexp}{option=noreduction}
\answer{}{\eqtgte,x,y}{type = equation}
#endif
#if defined TARGET_nbderiv
\answer{}{\nder}{type = numexp}{option=noreduction}
#endif

\solution{
Rappel : la fonction \(f) est définie sur <span class="nowrap">\defdom</span> par
<span class="nowrap">\(f(x)=)\(\ft).</span>
<ol>
#if defined TARGET_eqtgte1 ||TARGET_nbderiv || TARGET_txvarh
<li>L'image de \(\x0\) par \(f\) se calcule ainsi&nbsp;:
  <div class="unbreakable">
  \(f(\x0)=\fx00\)
  \if{\fx00 issametext \y0sol}
    {}
    {<br>\(\phantom{f(\x0)}=\y0sol\)}
  </div>
</li>
<li>Pour \(h\) réel non nul, l'image de \(\x0+h\) par \(f\) se calcule ainsi&nbsp;:
  <div class="unbreakable">
  \(f(\x0+h)=\fx0h\)
  <br>\(\phantom{f(\x0+h)}=\fx0hbsol\)
  \if{\fx0hb issametext \y0h}
    {}
    {<br>\(\phantom{f(\x0+h)}=\y0hsol\)}
  </div>
</li>
<li>De même, pour \(h\) réel non nul&nbsp;:
  <div class="unbreakable">
  \if{\y0>=0}
   {\(\frac{f(\x0+h)-f(\x0)}{h}=\frac{\y0hsol-\y0sol}{h}\)}
   {\(\frac{f(\x0+h)-f(\x0)}{h}=\frac{\y0hsol-\left(\y0sol\right)}{h}\)}
  <br>\(\phantom{\frac{f(\x0+h)-f(\x0)}{h}}=\y1sol\)
  </div>
</li>
#endif
#if defined TARGET_eqtgte1 ||TARGET_nbderiv
<li>Ainsi en passant à la limite lorsque \(h\) tend vers <span class="nowrap">\(0\),</span> \(h \neq 0\) on obtient&nbsp;:
 <br>\(\displaystyle{\lim_{h \to 0} \; \left(\y1sol\right)} = \ndersol\)
 <br>Donc : \(f^{\prime}(\x0)=\ndersol\)
</li>
#endif
#if defined TARGET_eqtgte2
<li>On calcule la fonction dérivée de <span class="nowrap">\(f\)&nbsp;:</span><br>
Pour tout <span class="nowrap">\(x \in \)\defdom,</span> <span class="nowrap">\(f^{\prime}(x)=\fp\).</span><br>
Et ainsi \(f^{\prime}(\x0)=\ndersol\)</li>
#endif
#if defined TARGET_eqtgte1 ||TARGET_eqtgte2
<li>Pour l'équation de la tangente à la courbe représentative de \(f) au point d'abscisse
<span class="nowrap">\(\x0),</span> on sait qu'elle est de la forme&nbsp;: \(y= f^{\prime}(\x0)(\xmoinsx0)+f(\x0)\)
 #if defined TARGET_eqtgte2
  <br class="spacer">On calcule <span class="nowrap">\(f(\x0)\)&nbsp;:</span>
  <div class="unbreakable">
  \(f(\x0)=\fx00\)
  \if{\fx00 issametext \y0sol}
    {}
    {<br>\(\phantom{f(\x0)}=\y0sol\)}
  </div>
 #endif
 <br>Donc ici, en utilisant les résultats précédents&nbsp;:
\if{\y0>=0}
  {\(y= \ndersol (\xmoinsx0)+\y0sol\)}
  {\(y= \ndersol (\xmoinsx0) \y0sol\)}
<br>L'équation de la tangente est donc&nbsp;: \(y=\eqtgtesol\).</li>
#endif
</ol>
}
