target=vocabfct1 vocabfct2 vocabfct3 vocabfct4 vocabfct5
\author{Régine, Mangeard}
#define TITRE Vocabulaire fonctions
#if defined TARGET_vocabfct1
# define NUM 1
#endif
#if defined TARGET_vocabfct3
# define NUM 3
#endif
#if defined TARGET_vocabfct4
# define NUM 4
#endif
#if defined TARGET_vocabfct2
# define NUM 2
# endif
#if defined TARGET_vocabfct5
# define NUM 5
#endif
\title{TITRE NUM}
#if defined TARGET_vocabfct1
\integer{a=randint(-9..9)}
\integer{b=randint(-9..9)}
\integer{b=\a=\b?\b+1}
\text{data=Si \(f(\a)=\b),(1,2),\(\b) est l'image de \(\a) par \(f), \(\a) est un antécédent de \(\b) par \(f),\(\a) est l'image de \(\b) par \(f), \(\b) est un antécédent de \(\a) par \(f)
  Si \(\b) est l'image de \(\a) par \(f),(1),\(f(\a)=\b),\(f(\b)=\a)
  Si \(\a) est un antécédent de \(\b) par \(\f),(1),\(f(\a)=\b),\(f(\b)=\a)
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\text{goodrep=wims(declosing \cedata[2])}
\integer{nbrep=items(\cedata)-2}
\text{lstrep=item(3..\nbrep+2,\cedata)}
\statement{
  Soit une fonction \(f) définie sur \(\,\RR).
<div class="wimscenter">\quest</div>
<ul>
\for{kk=1 to \nbrep}{
<li>\embed{reply1,\kk}</li>}
</ul>
}
\answer{Réponse}{\goodrep;\lstrep}{type=checkbox}{option=shuffle}
#endif
#if defined TARGET_vocabfct2
\integer{a=randint(-9..9)}
\text{data=pour tout \(x \in \mathcal{D})&#44; \(x) possède une unique image par \(f),1
  pour tout \(x \in \mathcal{D})&#44; \(x) possède au moins une image par \(f),2
  pour tout \(x \in \mathcal{D})&#44; \(x) possède plusieurs images par \(f),2
  pour tout \(x \in \mathcal{D})&#44; \(x) possède un unique antécédent par \(f),2
  pour tout \(x \in \RR)&#44; \(x) possède une unique image par \(f),2
  pour tout \(x \in \RR)&#44; \(f(x) \in \mathcal{D}),2
  si \(x \in \mathcal{D}) et \(f(x)=\a)&#44; \(\a) possède au moins un antécédent par \(f),1
  si \(x \in \mathcal{D}) et \(f(x)=\a)&#44; \(\a) possède un unique antécédent par \(f),2
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\text{rep=\cedata[2]}

\statement{
  Soit une fonction \(f : \mathcal{D} \rightarrow \RR).
<div class="wimscenter">\quest</div>
  Cocher la bonne réponse:
<div class="wimscenter">\embed{reply1}</div>
}
\answer{Réponse}{\rep;Vrai,Faux}{type=radio}
#endif
#if defined TARGET_vocabfct3
\integer{a=randint(-9..9)}
\integer{b=randint(-9..9)}
\integer{b=\a=\b?\b+1}
\text{data=est l'image de ,\b,\a
  est antécédent de ,\a,\b
  a pour image ,\a,\b
  a pour antécédent ,\b,\a
}
\text{ind=shuffle(4)}
\text{quest=}
\text{rep1=}
\text{rep2=}
\for{i=1 to 4}
 {
 \text{cedata=row(\ind[\i],\data)}
 \text{quest=wims(append item \cedata[1] to \quest)}
 \text{rep1=wims(append item \cedata[2] to \rep1)}
 \text{rep2=wims(append item \cedata[3] to \rep2)}
 }
\statement{
  Par une fonction \(f) on a :
<div class="wimscenter">\(\a \mapsto \b).</div>
  Compléter les phrases suivantes
<ul>
<li>\embed{reply1,3} \quest[1] \embed{reply2,3}</li>
<li>\embed{reply3,3} \quest[2] \embed{reply4,3}</li>
<li>\embed{reply5,3} \quest[3] \embed{reply6,3}</li>
<li>\embed{reply7,3} \quest[4] \embed{reply8,3}</li>
</ul>
}
\answer{}{\rep1[1]}{type=numeric}
\answer{}{\rep2[1]}{type=numeric}
\answer{}{\rep1[2]}{type=numeric}
\answer{}{\rep2[2]}{type=numeric}
\answer{}{\rep1[3]}{type=numeric}
\answer{}{\rep2[3]}{type=numeric}
\answer{}{\rep1[4]}{type=numeric}
\answer{}{\rep2[4]}{type=numeric}
#endif
#if defined TARGET_vocabfct4
\integer{a=randint(-9..9)}
\integer{b=randint(-9..9)}
\integer{b=\a=\b?\b+1}
\text{data=par la fonction \(f)&#44; \b est l'image de \a ,\a,\b
\a a pour image \b par la fonction \(f),\a,\b
  un antécédent de \b par la fonction \(f) est \a,\a,\b
  l'image par \(f) de \a est nulle,\a,0
  la courbe de la fonction \(f) passe par le point \(A(\a;\b)),\a,\b
  l'ordonnée du point d'abscisse \a de la courbe \(\mathcal{C}_f) vaut \b,\a,\b
  la représentation graphique de la fonction \(f) coupe l'axe des ordonnées au point d'ordonnée \b,0,\b
  la représentation graphique de la fonction \(f) coupe l'axe des abscisses au point d'abscisse \a,\a,0
  la représentation graphique de la fonction \(f) passe par l'origine du repère,0,0
}
 \text{cedata=randomrow(\data)}
 \text{quest=\cedata[1]}
 \text{x=\cedata[2]}
 \text{y=\cedata[3]}
\statement{
 Écrire symboliquement:
<div class="wimscenter">\quest</div>
<div class="wimscenter"><label for="reply1">\(f)</label>(\embed{reply1,3})
  <label for="reply2">=</label>\embed{reply2,3}</div>
}
\answer{x}{\x}{type=numeric}
\answer{y}{\y}{type=numeric}
#endif
#if defined TARGET_vocabfct5
\integer{a=randint(2..15)}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)}
\integer{c2=\c^2}
\text{data=\(texmath(x^2+\a*x+\b)),randint(-9..9),1
\(texmath(sqrt(x^2+\a))),randint(-9..-1),1
\(texmath(sqrt(x-\a))),randint(-5..\a-1),2
\(texmath(sqrt(x-\a))),randint(\a+1..\a+10),1
\(texmath(\b /(x-\a))),\a,2
\(texmath(\b /(x^2+\c2))),\c,1
\(texmath(\b /(x^2-\c2))),\c,2
}
 \text{cedata=randomrow(\data)}
 \text{f=\cedata[1]}
 \text{x=\cedata[2]}
 \text{rep=\cedata[3]}
\integer{k=randint(1,2)}
\text{quest=\k=1?Le réel \(\x) peut-il posséder une image par \(f):la fonction \(f) peut-elle être définie en \(\x)}
\statement{
  Soit une fonction \(f) d'expression algébrique:
<div class="wimscenter">\(f(x)=)\f.</div>
<div>\quest? \embed{reply1}</div>
}
\answer{Réponse}{\rep;Oui,Non}{type=radio}
#endif
