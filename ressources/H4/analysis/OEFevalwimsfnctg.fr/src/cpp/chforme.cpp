target=chforme1 chforme2 chforme3 chforme4 chforme5
\author{Régine, Mangeard}
\email{regine@mangeard}
\format{html}
#define TITRE Différentes écritures
#if defined TARGET_chforme1
# define NUM 1
#endif
#if defined TARGET_chforme3
# define NUM 3
#endif
#if defined TARGET_chforme4
# define NUM 4
#endif
#if defined TARGET_chforme2
# define NUM 2
#endif
#if defined TARGET_chforme5
# define NUM 5
#endif
\title{TITRE NUM}
#if (defined TARGET_chforme2 || defined TARGET_chforme5 )
%%%% Choix de l'équation à résoudre
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)*randint(1,-1)}
\integer{d=randint(1..9)*randint(1,-1)}
\rational{sing=-\d / \c}
\text{fdev=texmath((\a*x+\b) / (\c*x+\d))}
\rational{e=simplify(\a/\c)}
\rational{b1=simplify(\b-\e*\d)}
\text{fcan=texmath(\e+\b1/(\c*x+\d))}
\rational{b2=simplify(\b+\e*\d)}
\text{fbad1=texmath(\e+\b2/(\c*x+\d))}
\integer{a3=\a-\c}
\integer{b3=\b-\d}
\integer{b4=\b+\d}
\text{ffun=texmath(1+(\a3*x+\b3) / (\c*x+\d))}
\text{fbad2=texmath(1+(\a3*x+\b4) / (\c*x+\d))}
\text{listexp=\(\ffun),\(\fcan),\(\fbad1),\(\fbad2)}
\integer{nlist=items(\listexp)}
\text{listexpeq=\(\fdev),\(\ffun),\(\fcan)}
\text{mix=shuffle(\nlist)}
\text{listexp=\listexp[\mix]}
\integer{ind1=position(1,\mix)}
\integer{ind2=position(2,\mix)}
\text{indexp=\ind1,\ind2}
\text{borne=\b1>0?plus grand minorant:plus petit majorant}
\rational{eq1sol=-\b / \a}
\rational{eq2sol=-\b3 / \a3}
\rational{f0=\b / \d}
\integer{indeq1=1}
\integer{indeq2=2}
\integer{indf0=1}
\integer{indf01=3}
\text{eq1=f(x)=0}
\text{eq2=f(x)=1}
#else
%%%% Choix de l'équation à résoudre
\text{lstsing=wims(values x,-x for x = 1 to 10)}
\text{lstsing=shuffle(\lstsing)}
\rational{sing1=\lstsing[1]}
\integer{den1=random(1,2)}
\integer{num1=\sing1}
\rational{sing1=\sing1/\den1}

\rational{sing2=\lstsing[2]}
\rational{ms1=\sing1*(-1)}
\integer{den2=random(1,2)}
\integer{num2=\sing2}
\rational{sing2=\sing2/\den2}
\rational{sing2=\sing2=\ms1?11}
\if{\sing1=\sing2}{
  \integer{nbsol=1}
  \integer{indsol=2}
  \text{eq1sol=\sing1}
}{
  \text{eq1sol=\sing1,\sing2}
}
\integer{a=\den1*\den2}
\integer{b=-\a*((\sing1)+(\sing2))}
\text{s1=\b>0?+:-}
\integer{bb=\b<0?\b*(-1):\b}
\integer{c=\a*(\sing1)*(\sing2)}
\text{s2=\c>0?+:-}
\integer{cc=\c<0?\c*(-1):\c}

%%%% les différentes formes de f
\text{ta=\a=1? :\a}
\text{ta=\a=-1?-}
\text{fdev= \ta x^2 }
\if{\b !=0}{\text{fdev=\fdev \s1 \bb x }}
\if{\c !=0}{\text{fdev=\fdev \s2 \cc }}
\text{eq1=f(x)=0}
\text{eq2=f(x)=\c}
\integer{f0=\c}

\text{ss1=\sing1<0?+:-}
\rational{tsing1=\sing1<0?\sing1*(-1):\sing1}
\text{ss2=\sing2<0?+:-}
\rational{tsing2=\sing2<0?\sing2*(-1):\sing2}
\text{sb1=\sing1<0?-:+}
\text{sb2=\sing2<0?-:+}
\text{ffact=\a( x \ss1 \tsing1)( x \ss2 \tsing2)}

\text{ffact2=x (\a x \s1 \bb) \s2 \cc}

\rational{d=\b / (\a*2)}
\rational{dd=-\d}
\rational{e=\c - (\b)^2 / (4*\a)}
\text{ss1=\d>0?+:-}
\rational{td=\d>0?\d:\d*(-1)}
\text{ss2=\e>0?+:-}
\rational{te=\e>0?\e:\e*(-1)}
\text{fcan= \a(x \ss1 \td)^2 \ss2 \te}
\rational{borney=\e}
\rational{bornex=\d*(-1)}

\text{fbad1=\a(x \sb1 \tsing1)(x \sb2 \tsing2)}
\rational{e2=\c-(\b)^2/(2*\a)}
\text{ss2=\e2>0?+:-}
\rational{te2=\e2>0?\e2:\e2*(-1)}
\text{fbad2=\a (x \ss1 \td)^2 \ss2 \te2}

\text{borne=\a>0?minimum:maximum}
\rational{bc=-\b / \a}
\text{eq2sol=0,\bc}
\rational{bornesolx=\dd}
\integer{bornesoly=\d}

\text{listexp=shuffle(\(\ffact),\(\ffact2),\(\fcan),\(\fbad1),\(\fbad2))}
\text{listexp=\(\ffact),\(\ffact2),\(\fcan),\(\fbad1),\(\fbad2)}
\integer{nlist=items(\listexp)}
\text{mix=shuffle(\nlist)}
\text{listexp=\listexp[\mix]}
\integer{ind1=position(1,\mix)}
\integer{ind2=position(2,\mix)}
\integer{ind3=position(3,\mix)}
\text{indexp=\ind1,\ind2,\ind3}
\text{listexpeq=\(\fdev),\(\ffact),\(\ffact2),\(\fcan)}
\integer{indeq1=2}
\integer{indeq2=3}
\integer{indf0=1}
\integer{indf01=3}
\integer{indborne=4}
#endif

%%%%%%%%%%%% enoncé de l'exo %%%%%%%%%%%%
#if (defined TARGET_chforme1 || defined TARGET_chforme2 )
\statement{On considère une fonction \(f) donnée par son expression algébrique :
<div class="wimscenter"> \(f(x)=\fdev) </div>
  Parmi les expressions suivantes, cocher celles qui sont équivalentes à \(f(x)).
<ul>
 <li>\embed{reply 1,1}</li>
 <li>\embed{reply 1,2}</li>
 <li>\embed{reply 1,3}</li>
 <li>\embed{reply 1,4}</li>
# if defined TARGET_chforme1
 <li>\embed{reply 1,5}</li>
# endif
</ul>
}
\answer{expressions équivalentes}{\indexp;\listexp}{type=checkbox}
#endif
#if defined TARGET_chforme5
\statement{
 On considère une fonction \(f) pour laquelle on dispose
  de plusieurs expressions équivalentes:
<ul>
 <li>Forme A: \(f(x)=\fdev)</li>
 <li>Forme B: \(f(x)=\ffun)</li>
 <li>Forme C: \(f(x)=\fcan)</li>
</ul>
  Indiquer l'expression de \(f(x)) la plus adaptée :
<ol>
<li> pour calculer \(f(0)):
<table><tr><td>\embed{reply 1,1}</td><td>\embed{reply 1,2}</td><td>\embed{reply 1,3}</td></tr></table></li>
<li> pour résoudre \(\eq1):
<table><tr><td>\embed{reply 2,1}</td><td>\embed{reply 2,2}</td><td>\embed{reply 2,3}</td></tr></table></li>
<li> pour résoudre\(\eq2):
<table><tr><td>\embed{reply 3,1}</td><td>\embed{reply 3,2}</td><td>\embed{reply 3,3}</td></tr></table></li>
</ol>
  En utilisant la forme adaptée, calculer \(f(0))=\embed{reply4,5}<br>
  En utilisant la forme adaptée, déterminer les solutions de \(\eq1)?
  <div class="wimscenter"> \(S = )\embed{reply5,5}</div>
  En utilisant la forme adaptée, déterminer les solutions de \(\eq2)?
  <div class="wimscenter"> \(S = )\embed{reply6,5}</div>
}
\answer{expression pour \(f(0))}{1;\listexpeq}{type=radio}{option=shuffle}
\answer{expression pour \eq1}{1;\listexpeq}{type=radio}{option=shuffle}
\answer{expression pour \eq2}{2;\listexpeq}{type=radio}{option=shuffle}
\answer{\(f(0))}{\f0}{type=numeric}
\answer{solutions pour \eq1}{\eq1sol}{type=fset}
\answer{solutions pour \eq2}{\eq2sol}{type=fset}
#endif
#if (defined TARGET_chforme3 || defined TARGET_chforme4 )
\statement{On considère une fonction \(f) pour laquelle on dispose
  de plusieurs expressions équivalentes:
<ul>
 <li>Forme développée: \(f(x)=\fdev)</li>
 <li>Forme factorisée: \(f(x)=\ffact)</li>
 <li>Forme semi-factorisée: \(f(x)=\ffact2)</li>
 <li>Forme canonique: \(f(x)=\fcan)</li>
</ul>
  Indiquer l'expression de \(f(x)) la plus adaptée:
<ol>
# if defined TARGET_chforme4
 <li> pour résoudre \(\eq1):<table><tr><td>\embed{reply 1,1}</td><td>\embed{reply 1,2}</td><td>\embed{reply 1,3}</td><td>\embed{reply 1,4}</td></tr></table></li>
 <li> pour résoudre\(\eq2):<table><tr><td>\embed{reply 2,1}</td><td>\embed{reply 2,2}</td><td>\embed{reply 2,3}</td><td>\embed{reply 2,4}</td></tr></table></li>
</ol>
  En utilisant la forme adaptée, déterminer les solutions de \(\eq1)?
  <div class="wimscenter"> \(S = )\embed{reply3,5}</div>
  En utilisant la forme adaptée, déterminer les solutions de \(\eq2)?
  <div class="wimscenter"> \(S = )\embed{reply4,5}</div>
}
\answer{expression pour \eq1}{\indeq1;\listexpeq}{type=radio}{option=shuffle}
\answer{expression pour \eq2}{\indeq2;\listexpeq}{type=radio}{option=shuffle}
\answer{solutions pour \eq1}{\eq1sol}{type=fset}
\answer{solutions pour \eq2}{\eq2sol}{type=fset}
# else
<li> pour calculer \(f(0)):<table><tr><td>\embed{reply 1,1}</td><td>\embed{reply 1,2}</td><td>\embed{reply 1,3}</td><td>\embed{reply 1,4}</td></tr></table></li>
<li> pour déterminer le \borne de la fonction \(f):<table><tr><td>\embed{reply 2,1}</td><td>\embed{reply 2,2}</td><td>\embed{reply 2,3}</td><td>\embed{reply 2,4}</td></tr></table></li>
</ol>
  En utilisant la forme adaptée, calculer \(f(0))=\embed{reply3,5}<br>
  En utilisant la forme adaptée, calculer le \borne de \(f(x)):\embed{reply4,5}<br>
  Il est atteint en \(x = )\embed{reply5}
}
\answer{expression pour \(f(0))}{\indf00;\listexpeq}{type=radio}{option=shuffle}
\answer{expression pour le \borne}{\indborne;\listexpeq}{type=radio}{option=shuffle}
\answer{\(f(0))}{\f0}{type=numeric}
\answer{\borne}{\borney}{type=numeric}
\answer{abscisse du \borne}{\bornex}{type=numeric}
\condition{expression pour \(f(0))}{(\reply1 issametext \listexpeq[\indf0]) or (\reply1 issametext \listexpeq[\indf01])}
# endif
#endif
