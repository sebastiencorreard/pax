====
Liste d'objets sur lequel on va travailler pris dans la catégorie \category
====
Création de la liste des  images
\text{images=}
\for{i=1..\cnt}{
 \text{image =wims(lookup \objs[\i] in descriptif)}
 \text{image = \image[\imag]}
 \text{image = wims(translate | to , in  \image)}
 \text{image=\objs[\i]/randitem(\image)}
 \text{images=wims(append item \image to \images)}
 }
\text{imglist=wims(makelist imgrename(\imagedir/ttt
        width=\width) for ttt in \images)}
