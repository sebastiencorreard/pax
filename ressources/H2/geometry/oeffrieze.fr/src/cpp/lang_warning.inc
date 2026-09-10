\text{wims_version=slib(oef/env wims_version)}
\text{wims_version=wims(char 1 to 4 of \wims_version)}
\if{\wims_version > 4.08}{
 \text{warning=Cliquer sur le bouton pour changer de couleur.}
 \if{\lang=en}{
  \text{warning=Click on the button to change the colour}
 }
 \if{\lang=nl}{
  \text{warning=Klik op de knop om van kleur te veranderen.}
 }
 \if{\lang=it}{
  \text{warning=Cliccare sul pulsante per cambiare il colore dei quadretti}
  }
 \if{\lang=es}{
  \text{warning=Clicar sobre el botón para cambiar el color}
 }
 \if{\lang=ca}{
  \text{warning=Clicar sobre el botó per canviar el color}
 }
}
{
 \text{warning=\wims_version Utilisez le click droit pour changer de couleur.}
 \if{\lang=en}{
  \text{warning=The right mouse click changes the colour.}
 }
 \if{\lang=nl}{
  \text{warning=De rechter muisknop gebruiken om de kleur te veranderen.}
 }
 \if{\lang=it}{
  \text{warning=Utilizzare il tasto destro del mouse per cambiare il
colore dei quadretti.}
 }
\if{\lang=es}{
  \text{warning=El clic derecho del mouse cambia el color.}
 }
\if{\lang=ca}{
  \text{warning=El clic dret del ratolí canvia el color.}
 }
}
