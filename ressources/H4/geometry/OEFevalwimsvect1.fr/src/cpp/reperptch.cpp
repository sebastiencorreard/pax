target=reperptch1 reperptch2 reperptch3 reperptch4 reperptch5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITLE Repérage et relation de Chasles

#if defined TARGET_reperptch1
 \title{TITLE I}
\text{pt=A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V}
\integer{i1=randint(1..22)}
\integer{i2=randint(1..22)}
\integer{i3=randint(1..22)}
\integer{i4=randint(1..22)}
 on ne veut pas le vecteur nul
\integer{i4=\i4=\i1?\i4+1:\i4}
\integer{i4=\i4>22?1}
\text{vlist=}
\integer{s=random(1..2)}
\text{v=\s=1?+\overrightarrow{\pt[\i1] \pt[\i2]}:-\overrightarrow{\pt[\i2] \pt[\i1]}}
\text{vlist= wims( append item \v to \vlist)}
\integer{s=random(1..2)}
\text{v=\s=1?+\overrightarrow{\pt[\i2] \pt[\i3]}:-\overrightarrow{\pt[\i3] \pt[\i2]}}
\text{vlist= wims( append item \v to \vlist)}
\integer{s=random(1..2)}
\text{v=\s=1?+\overrightarrow{\pt[\i3] \pt[\i4]}:-\overrightarrow{\pt[\i4] \pt[\i3]}}
\text{vlist= wims( append item \v to \vlist)}
\text{ind=shuffle(3)}
\text{rel=\vlist[\ind[1]] \vlist[\ind[2]] \vlist[\ind[3]]}
\text{deb=wims(text copy \rel mask 10-)}
\if{+ issametext \deb}
  {\text{rel=wims(text copy \rel mask 01+)}
  }
\text{ori=\pt[\i1]}
\text{dest=\pt[\i4]}
\statement{
Simplifiez au maximum la relation suivante

\special{mathmlinput [\rel =\overrightarrow{reply1 reply2}],2,noanswer
reply 1
reply 2
}
<div class="wims_instruction">Entrez séparément l'origine et la destination du vecteur.</div>
}

\answer{origine}{\ori}{type=nocase}
\answer{dest}{\dest}{type=nocase}

#endif

#if defined TARGET_reperptch2
 \title{TITLE II}
# include "lstcaract.inc"
 \text{listx=}
 \text{listpt=}
 \text{listquest=}
 \text{listrep=}
%% Liste des caratérisations
 \text{listecar=\(C\) est le milieu du segment \([A B]\) , \(C\) est le symétrique de \(A\)
  par rapport à \(B\), \(A B C D\) est un parallèlogramme}

 \text{listquest=}
 \integer{indquest=random(1..3)}
 \if {\indquest<3}{
  \text{indlst=shuffle(items(\listmil))}
  \text{listquest=wims(append item \listmil[\indlst[1]] to \listquest)}
  \text{listquest=wims(append item \listmil[\indlst[2]] to \listquest)}
  \text{indlst=shuffle(items(\listsym))}
  \text{listquest=wims(append item \listsym[\indlst[1]] to \listquest)}
  \text{listquest=wims(append item \listsym[\indlst[2]] to \listquest)}
  \text{listquest=wims(append item randomitem(\listpar) to \listquest)}
  \text{listquest=wims(append item randomitem(\listbadpar) to \listquest)}
  \if{\indquest=1}
   {\text{goodrep=1,2}}
   {\text{goodrep=3,4}}
  }{
  \text{listquest=wims(append item randomitem(\listmil) to \listquest)}
  \text{listquest=wims(append item randomitem(\listsym) to \listquest)}
  \text{indlst=shuffle(items(\listpar))}
  \text{listquest=wims(append item \listpar[\indlst[1]] to \listquest)}
  \text{listquest=wims(append item \listpar[\indlst[2]] to \listquest)}
  \text{indlst=shuffle(items(\listbadpar))}
  \text{listquest=wims(append item \listbadpar[\indlst[1]] to \listquest)}
  \text{listquest=wims(append item \listbadpar[\indlst[2]] to \listquest)}
  \text{goodrep=3,4}
  }
\statement{ Cocher la ou les égalités vectorielles permettant de conclure que:
<p class="wimscenter bold">
\listecar[\indquest].
</p>
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
<li>\embed{reply1,6}</li>
</ul>
}
\answer{Solution:}{\goodrep;\listquest}{type=checkbox}{option=shuffle}
#endif

#if (defined TARGET_reperptch5 || defined TARGET_reperptch4)
#if defined TARGET_reperptch4
 \title{TITLE IV}
 \integer{choix=1}
#endif
#if defined TARGET_reperptch5
 \title{TITLE V}
 \integer{choix=2}
#endif
 \integer{a=randint(2..7)*randint(1,-1)}
 \integer{b=randint(2..7)*randint(1,-1)}
 \integer{c=randint(2..7)*randint(1,-1)}
 \integer{d=random(2,3,5)}
 \integer{e=\choix=1?\a:\a*\d}
%% on ne veut pas \a+\b=0
 \integer{b=\e+\b=0?-1*(\b):\b}
%% on ne veut pas \a+\b=0
 \integer{c=\b+\c=0?-1*(\c):\c}
 \text{s1=\b<0?-:+}
 \integer{b=\b<0?-1*(\b)}
 \rational{bb= simplify(\b / \d)}
 \rational{cc= simplify(\c / \d)}
 \text{tbb=\bb=1? :texmath(\bb)}
 \text{tcc=\cc=1? :texmath(\cc)}
 \text{tcc=\cc=-1?-:\tcc}

 \text{rel=\choix=1? \(\a \overrightarrow{A P} \s1 \b \overrightarrow{B P} = \c \overrightarrow{A B}):\(\a \overrightarrow{A P} \s1 \tbb \overrightarrow{B P} = \tcc \overrightarrow{A B})}
 \rational{sol=\choix=1? ((\c)\s1(\b))/((\a)\s1(\b)):((\c)\s1(\b))/((\a)*\d \s1 (\b))}
 \text{relsol=\choix=1? \a \overrightarrow{A P} \s1 \b \overrightarrow{B A} \s1 \b \overrightarrow{A P} = \c \overrightarrow{A B}:\a \overrightarrow{A P} \s1 \frac{\b}{\d} \overrightarrow{B A} \s1 \frac{\b}{\d} \overrightarrow{A P} = \frac{\c}{\d} \overrightarrow{A B}}
 \text{relsol2=\choix=1? (\a \s1 \b) \overrightarrow{A P} = (\c \s1 \b) \overrightarrow{A B}:(\a \s1 \frac{\b}{\d}) \overrightarrow{A P} = (\frac{\c}{\d} \s1 \frac{\b}{\d}) \overrightarrow{A B}}
 \integer{solnum= ((\c)\s1(\b))}
 \integer{solden=\choix=1?((\a)\s1(\b)):((\a)*\d \s1 (\b))}
 \text{coefsol=simplify(\solnum / (\solden))}
 \text{coefsol=wims(replace internal / by , in \coefsol)}
 \text{coefsol=items(\coefsol)>1?\frac{\coefsol[1]}{\coefsol[2]}}

\text{relsol3= \overrightarrow{A P}= \coefsol \overrightarrow{A B}}
\statement{
 <p>
  Transformer la relation
  </p><p class="wimscenter">
 \rel
  </p>
  afin d'obtenir une égalité vectorielle de la forme
  <p class="wimscenter">
  \(\overrightarrow{A P} = k \overrightarrow{A B})
  </p>

<div class="wimscenter">
<b>Égalité vectorielle</b> :
<label for="reply1">\(\overrightarrow{A P})=</label>\embed{r1,4}\(\overrightarrow{A B})
</div>
 }

\answer{coeff}{\sol}{type=numeric}
\hint{Décomposer le vecteur \(\overrightarrow{B P}) à l'aide de la relation
  de Chasles.<br>
  Quel point semble le plus judicieux pour cette décomposition?
}
\solution{On commence par décomposer \(\overrightarrow{B P}) en \(\overrightarrow{B A}+\overrightarrow{A P})<br>
  On obtient: \(\relsol) <br>
  Puis: \(\relsol2)<br />
  et enfin : \(\relsol3). }
#endif


#if defined TARGET_reperptch3
 \title{TITLE III}
%%choix parametre entier ou rationnel
\integer{choix=random(1,2)}
\integer{b=random(1..5)}
\rational{c=\choix=1?random(-1,-2,2):random(-1,-2,-3,2,3)/\b}
on ne veut pas c=1
\rational{c=\c=1?2}
\rational{ca=1-\c}
\text{s1=\c>0?+:-}
\text{ss1=\c<0?+:-}
\rational{mc=-1*(\c)}
\text{tc=\c>0?\c:\mc}
\text{tc=wims(replace internal / by , in \tc)}
\text{tc=items(\tc)>1?\frac{\tc[1]}{\tc[2]}}
\text{tc=\tc=1? }
\text{tca=\ca}
\text{tca=wims(replace internal / by , in \tca)}
\text{tca=items(\tca)>1?\frac{\tca[1]}{\tca[2]}}
\text{tca=\tca=-1?-}

\integer{fx=\c*(\b)}
\integer{fy=0}
\integer{Ox=403}
\integer{ex=31}
\integer{\fxx=\Ox+\ex*\fx}
\integer{\fxxm=\fxx-0.3*\ex}
\integer{\fxxp=\fxx+0.3*\ex}
\text{image= draw(806,64
  xrange -13,13
  yrange -1,3
  hline 0,0,red
  parallel -12,-0.2,-12,0.2,1,0,2,blue
  parallel -10,-0.4,-10,0.4,5,0,5,blue
  parallel -9,-0.2,-9,0.2,1,0,4,blue
  parallel -4,-0.2,-4,0.2,1,0,4,blue
  parallel 1,-0.2,1,0.2,1,0,4,blue
  parallel 6,-0.2,6,0.2,1,0,4,blue
  parallel 11,-0.2,11,0.2,1,0,2,blue
  text red,-0.1,1.5,medium,A
  text red,\b-0.1,1.5,medium,B
  segment 0,-0.2,\a,0.2,red
  segment \b,-0.2,\b,0.2,red)
  }
\text{repimage=xrange -13,13
  yrange -1.5,3
  hline 0,0,red
  parallel -12,-0.2,-12,0.2,1,0,2,blue
  parallel -10,-0.4,-10,0.4,5,0,5,blue
  parallel -9,-0.2,-9,0.2,1,0,4,blue
  parallel -4,-0.2,-4,0.2,1,0,4,blue
  parallel 1,-0.2,1,0.2,1,0,4,blue
  parallel 6,-0.2,6,0.2,1,0,4,blue
  parallel 11,-0.2,11,0.2,1,0,2,blue
  text red,-0.1,1.5,medium,A
  text red,\b-0.1,1.5,medium,B
  text red,\fx-0.1,-0.5,medium,M
  segment 0,-0.2,\a,0.2,red
  segment \b,-0.2,\b,0.2,red
  segment \fx,-0.2,\fx,0.2,red
  }

\statement{
  Placer le point \(M\) défini par :
<p class="wimscenter">
 \(\tca \overrightarrow{A M} = \ss1 \tc \overrightarrow{B M})
</p>
  Pour cela, transformer la relation précédente afin d'obtenir une égalité vectorielle de la forme
 <p class="wimscenter">
\(\overrightarrow{A M} = k \overrightarrow{A B})
</p>
<div class="wimscenter">
\embed{r1}
<br>
  <label for="reply2">Valeur de \(k\):</label>\embed{r2,4}
</div>
<div class="wims_instruction">
 Saisir d'abord la valeur de \(k\), puis cliquer à l'emplacement du point \(M\).
</div>

 }

\answer{f(\X)}{\image;rectangle,\fxxm,0,\fxxp,64}{type=coord}
\answer{coeff}{\c}{type=numeric}
\hint{Transformer l'écriture \(\tca \overrightarrow{A M} \s1 \tc \overrightarrow{B M}=\vec{0}) pour obtenir une expression de la forme:
<p class="wimscenter">
 \(\overrightarrow{A M}=k \overrightarrow{A B})
</p>}
\solution{On commence par transformer l'écriture \(\tca \overrightarrow{A M}\s1 \tc \overrightarrow{B M}=\vec{0})
  pour obtenir une expression de la forme:
<p class="wimscenter">
 \(\overrightarrow{A M}=k \overrightarrow{A B})
</p>
  On trouve \(\overrightarrow{A M}= \s1 \tc \overrightarrow{A B})
<p>
  On peut alors facilement placer le point \(M\):

<div class="wimscenter">
\draw{800,64}{\repimage}
</div>
}
#endif
