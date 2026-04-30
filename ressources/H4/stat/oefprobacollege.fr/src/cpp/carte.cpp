target= oefcarte1 oefcarte2 oefcarte3

#if TARGET_oefcarte1
\title{Carte 1}
#endif
#if TARGET_oefcarte2
\title{Carte 2}
#endif
#if TARGET_oefcarte3
\title{Carte 3}
#endif
\language{fr}
\range{-5..5}
\author{Jean-Luc, Donadoni}
\email{jluc.donadoni@laposte.net}
\computeanswer{no}
\format{html}
\keywords{probability,events}
\precision{10000}

\text{couleur=coeur,pique,carreau,trèfle}
\text{valeur=un as,un roi,une dame,un valet,un dix,un neuf,un huit,un sept,un six,un cinq,un quatre,un trois,un deux}
\text{nomb=random(32,52)}
\integer{c=randint(1..4)}
\if{\nomb=32}{\integer{v=randint(1..8)}}{\integer{v=randint(1..13)}}
\integer{a=randint(1..3)}
\if{\a=1}{\text{enonc=un \couleur[\c]}
    \if{\nomb=32}{\integer{b=8}}{\integer{b=13}}}
\if{\a=2}{\text{enonc=\valeur[\v]}
    \integer{b=4}}
\if{\a=3}{\text{enonc=\valeur[\v] de \couleur[\c]}
    \integer{b=1}}

%%% MB
\integer{nbcolor=\nomb/4}
\text{valeurfeed=wims(replace internal une by in \valeur)}
\text{valeurfeed=wims(replace internal un by in \valeurfeed)}
\text{kk=shuffle(\nbcolor)}
\hint{Dans un jeu de \nomb cartes, il y a :
<ul><li> \nbcolor cartes de chaque couleur (cœur, pique, carreau, trèfle)</li>
<li> 4 \valeurfeed[\kk[1]]</li>
<li> 4 \valeurfeed[\kk[2]]</li>
<li> 4 \valeurfeed[\kk[3]]</li>
<li> 4 \valeurfeed[\kk[4]]</li>
<li> ...</li>
</ul>}
%%%
#if TARGET_oefcarte1
\text{rep=maxima((\b)/(\nomb))}
\text{typerep=(sous forme de fraction)}
#endif
#if TARGET_oefcarte2
\integer{rep=\b/\nomb*100}
\text{typerep=(sous forme d'un pourcentage arrondi à l'unité)}
#endif
#if TARGET_oefcarte3
\integer{rep=\b/\nomb*1000}
\real{rep=\rep/1000}
\text{typerep=(sous forme d'un nombre décimal arrondi au millième)}
#endif
%%% feedback MB

\text{feed1=\a=1? \couleur[\c]:\valeurfeed[\v]} %%% 1 ou 2
\text{feed1=\a=3?\valeurfeed[\v] de \couleur[\c]:\feed1}
#if TARGET_oefcarte2
\integer{rep0=\b/\nomb*10000}
\real{rep0=\rep0/10000}
\text{feed2=En faisant la division de \b par \nomb, on obtient environ \rep0. <br>Puis en arrondissant et enécrivant sous la forme d'un pourcentage \rep %}
#endif
#if TARGET_oefcarte3
\real{rep0=\b/\nomb}
\text{feed2=En faisant la division de \b par \nomb, on obtient environ \rep0. <br>Puis en arrondissant au millième \rep.}
#endif
%%%%

\statement{
Nous avons un jeu de \nomb cartes.
Nous tirons une carte au hasard.
<p>Quelle est la probabilité d'avoir \enonc ?</p>
<div class="spacer">
<label for="reply1">La probabilité \typerep =</label> \embed{r1,5} </div>
}
#if TARGET_oefcarte1
\answer{}{\rep}{type=numexp}{option=noreduction}
#endif
#if TARGET_oefcarte2
\answer{}{\rep}{type=numeric}{}
#endif
#if TARGET_oefcarte3
\answer{reponse}{\el1}{type=raw}
\text{el1=wims(translate , to . in \el1)}
\condition{Votre réponse}{\el1=\rep}
\solution{La bonne réponse est \rep}
#endif
\feedback{\sc_reply1<1}{
<div class="feedback">Il y a exactement \b \feed1 dans un jeu de \nomb cartes. <br>La probabilité est donc égale à \(\frac{\b}{\nomb}\)
<br>\feed2</div>}
