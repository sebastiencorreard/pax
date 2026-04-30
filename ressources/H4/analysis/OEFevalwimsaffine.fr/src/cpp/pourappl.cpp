target=pourappl1,pourappl2,pourappl3,pourappl4,pourappl5
#include "author.inc"
\precision{100}
#if defined TARGET_pourappl1
# define NUM 1
#endif
#if defined TARGET_pourappl2
# define NUM 2
#endif
#if defined TARGET_pourappl3
# define NUM 3
#endif
#if defined TARGET_pourappl4
# define NUM 4
#endif
#if defined TARGET_pourappl5
# define NUM 5
#endif
#include "lang_titles.inc"
#if defined TARGET_pourappl1
 \text{name=slib(lang/fname boy,fr)}
 \text{objet=slib(life/frcommodity 100,1000)}
 \integer{price=randint(100..1000)}
 \integer{remise=randint(11..19)}
 \text{art=item(1,\objet)}
 \text{objet=item(2,\objet)}
 \text{enonce=\name voit \art \objet à \price euros dans un magasin. Le vendeur lui propose une remise de \(\remise \%). Quel prix va-t-il payer}
 \text{reponse=\name payera}
 \text{compreponse=euros.<div class="wims_instruction">Arrondir votre résultat aux centimes d'euro.</div>}
 \real{rep=\price*(100-\remise)/100}
#endif
#if defined TARGET_pourappl2
 \text{name=slib(lang/fname girl,fr)}
 \integer{salaire=randint(1000..2000)}
 \integer{remise=randint(20..50)/10}
 \text{enonce=\name gagne \(\salaire) par mois. Son patron lui propose une augmentation de \(\remise \%). Combien gagnera-t-elle après cette augmentation}
 \integer{rep=\salaire*(100+\remise)}
 \real{rep=\rep/100}
 \text{compreponse=euros.<div class="wims_instruction">Arrondir votre résultat aux centimes d'euro.</div>}
 \text{reponse=\name gagnera}
#endif
#if defined TARGET_pourappl3
 \text{name=slib(lang/fname girl,fr)}
 \real{p=randint(12..45)/10}
 \real{prix=randint(21..39)/10}
 \integer{pour=randitem(2,3,4,5)}
 \text{produit=randitem(pommes de terre,carottes,courgettes,pommes,poires,oranges,citrons,clémentines)}
 \text{enonce=\name achète \p Kg de \produit à \prix euro/Kg. Comme elle possède une carte de fidélité, le vendeur lui fait une remise de \pour % en caisse.<br>Quel est le montant de son économie}
 \text{compreponse=euros.<div class="wims_instruction">Arrondir votre résultat aux centimes d'euro.</div>}
 \integer{rep=\p*\prix*\pour}
 \real{rep=\rep/100}
 \text{reponse=Elle économisera}
#endif
#if defined TARGET_pourappl4
 \real{prix=randint(50..500)}
 \text{v=wims(values v for v=5 to 15)}
 \text{v=shuffle(\v)}
 \integer{pour1=item(1,\v)}
 \integer{pour2=item(2,\v)}
 \integer{ch=randitem(1,2)}
 \text{type=baisse,augmentation}
 \text{type=item(\ch,\type)}
 \text{sg=-,+}
 \text{sg=item(\ch,\sg)}
 \text{enonce=Dans un magasin, le prix d'un article était de \prix euros. Il subit une \type de \pour1 % suivie d'une \type de \pour2 %. Quel est le prix de cet article après la deuxième \type}
 \text{compreponse=euros.<div class="wims_instruction">Arrondir votre résultat aux centimes d'euro.</div>}
 \integer{rep=\prix*(1\sg\pour1/100)*(1\sg\pour2/100)*100}
 \real{rep=\rep/100}
 \text{reponse=Le nouveau prix est de}
#endif
#if defined TARGET_pourappl5
 \real{pour=randitem(20,30,40,50,60,70,75,80,90)}
 \text{enonce=Un commerçant souhaite vendre les articles de son magasin \pour % plus cher que le prix où il les achète. Par quel nombre doit-il multiplier le prix d'achat pour obtenir le prix de vente aux clients}
 \text{compreponse=<div class="wims_instruction">Arrondir votre résultat au centième.</div>}
 \real{rep=1+\pour/100}
 \text{reponse=Il doit multiplier le prix d'achat par}
#endif
\statement{
\enonce ?
<p><b>Votre réponse :</b></p>

<label for="reply1">\reponse</label> : \embed{r1} \compreponse

}

\reply{réponse}{\rep}{type=numexp}
