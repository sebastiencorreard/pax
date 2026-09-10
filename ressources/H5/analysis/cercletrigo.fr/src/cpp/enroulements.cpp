target= liresincos enroulement
#if defined TARGET_liresincos
\title{ Enroulement : Lire les valeurs de cos et sin sur le cercle }
#endif
#if defined TARGET_enroulement
\title{ Enroulement : Placer un point sur le cercle trigonométrique }
\keywords{trigonometric_circle,trigonometry,angles}
#endif
\language{ fr }
\author{ Bruno, Mifsud;Communauté,MutuWIMS }
\email{ bmifsud@ac-aix-marseille.fr;communaute.mutuwims@laposte.net }
\observation{L'angle est compris entre \(-pi) et \(pi)}
#if defined TARGET_liresincos

\keywords{trigonometric_circle,trigonometry,angles,sinus,cosinus}
#endif

\rational{ a = random(1/6,1/3,2/3,1/4,1/2,3/4,5/6,0/1) }
\integer{ r = 1 }
\integer{ b = 0.5*random(-1..1) }
\rational{ a = simplify(\a + \b) }
\text{ c = pari([numerator(\a) , denominator(\a)]) }
\function{ api = \c[1]*pi/\c[2] }
%%%%%pour solution %%%%%%%%%%%%%%%%%%                                        
\real{ pointx = (\r)*cos(\a*pi) }
\real{ pointy = (\r)*sin(\a*pi) }
\real{pointx1=1.1*\pointx}
\real{pointy1=1.1*\pointy}


%%%%%%%% angle bien écrit %%%%%%%%%%%
\text{angl=simplify(\api)}         
\text{anglfrac=\frac{\c[1] \pi}{\c[2]}}
\if{\c[2]=1 and \c[1]=1}{\text{anglfrac= \pi }}
\if{\c[2]=1 and \c[1]=-1}{\text{anglfrac=-\pi}}
\if{\c[1]=0 }{\text{anglfrac=0}}
\if{\c[2]=1 and (\c[1]>1 or \c[1]<-1)}{\text{anglfrac=\c[1]\pi}}
\if{\c[2]>1 and \c[1]=1 }{\text{anglfrac=\frac{\pi}{\c[2]}}}
\if{\c[2]>1 and \c[1]=-1 }{\text{anglfrac=\frac{-\pi}{\c[2]}}}


\text{repcos=simplify(cos(\angl))}
\text{repsin=simplify(sin(\angl))}
\real{ s = 1.3 }
\text{ dessin = }
 \for{ i = 1 to 5 }{  
  \text{ dessin = \dessin 
  
dline -2*\s*cos(\i*pi/6),-2*\s*sin(\i*pi/6),2*\s*cos(\i*pi/6),2*\s*sin(\i*pi/6),blue  
dline -2*\s*cos(\i*pi/4),-2*\s*sin(\i*pi/4), 2*\s*cos(\i*pi/4),2*\s*sin(\i*pi/4),green }}
 

\real{ taille = 400 }
\text{ preparation=
    linewidth 2
    xrange -\s, \s 
    yrange -\s, \s 
    hline 0,0,black 
    arrow 0,0,\s,0,6,black 
    arrow 0,0,0,\s,6,black 
    vline 0,0,black 
    vline 0.5,0,grey 
    vline -0.5,0,grey 
    hline 0,0.5,grey 
    hline 0,-0.5,grey 
    trange 0,2*pi 
    text black,0.1,0.1,medium,0
    text black,1.1,0.1,medium,1
    text black,0.1,1.1,medium,1 
    plot blue,cos(t),sin(t) 
  }

  
  \text{correction=
      crosshair \pointx,\pointy,10,blue
      text blue,\pointx1,\pointy1,large,M
#if defined TARGET_liresincos
    dline \pointx,0,\pointx,\pointy,red
    dline 0,\pointy,\pointx,\pointy,red  
    text black,0.5,0.1,medium,0.5 
    crosshair 0.5,0,10,black 
    text black,-0.5,0.1,medium,-0.5 
    crosshair -0.5,0,10,black 
    text black,0.1,0.5,medium,0.5 
    crosshair 0,0.5,10,black 
    text black,0.1,-0.5,medium,-0.5 
    crosshair 0,0.5,10,black 

    
#endif 
      
      }
#if defined TARGET_enroulement 
\text{ A = draw(\taille,\taille 
      \preparation
      \dessin
      ) }
\text{ PP = slib(draw/convpixel \pointx,\pointy,\taille,\taille,-\s,\s,-\s,\s,0,pixels) }
\real{ Px = \PP[1] }
\real{ Py = \PP[2] }  
#endif

#if defined TARGET_liresincos  
\integer{quest=random(1,2)}
\text{cas=\quest=1?cosinus:sinus}
\text{rep=\quest=1 ? \repcos : \repsin}
 
\statement{ Par lecture sur cercle trigonométrique, déterminer le \cas de \(\anglfrac \).
 
  <table>
  <tr>  <td><div class="wimscenter">    
     \draw{ \taille,\taille }{  
      \preparation
      \dessin
       }
       </td>
       <td>
     <div class="wims_question">
     
       Le \cas de \(\anglfrac \) vaut \embed{reply1,10} .
       
    </div> 
    </td></tr>
    </table>
    <div class="wims_instruction">Si la bonne réponse est \(\sqrt{3}) saisir : sqrt(3). Aucune calculatrice n'est autorisée.</div>
    } 

\answer{ \cas}{  \rep }{ type  =  algexp }

 
 
\solution{ Voici la réponse, le point \(M) associé à \(\anglfrac \) par enroulement 
de la droite réelle sur le cercle trigonométrique est le point bleu sur la figure ci-dessous.
    <div class="wimscenter">
     \draw{ \taille,\taille }{  
      \preparation
      \dessin
      \correction
    
 
      } </div>
      
<p>Rappel :</p>
<p>L'abscisse du point \(M) est la valeur du cosinus.</p>
<p>L'ordonnée du point \(M) est la valeur du sinus</p>
<div class="wimscenter">\img{\imagedir/cercletrigo.png}.</div>

  
} 
#endif

#if defined TARGET_enroulement 
\statement{<p>Cliquez sur le point \(M) du cercle associé à l'angle \(\anglfrac \) par enroulement
de la droite réelle sur le cercle trigonométrique tracé ci dessous..</p>
    <div class="wimsquestion wimscenter">
       \embed{ reply1 ,400x400}
    </div> } 

\answer{ }{\A; points,\Px,\Py }{type=jsxgraphcurve}{option=color1=black color2=green precision=8}
 
\feedback{ \sc_reply1 !=1}{
<p>Le cercle vert sur la figure précédente était la bonne réponse.</p>
      <p>Rappel :</p>
      <div class="wimscenter">\img{\imagedir/cercletrigo0.png}.</div>
 
}
#endif
