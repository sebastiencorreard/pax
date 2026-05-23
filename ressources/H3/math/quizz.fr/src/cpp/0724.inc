\title{Question 0724 Mesurer un angle avec un rapporteur}
\keywords{angles}

\integer{angle=randint(11..13)*10}
\integer{k0=180-\angle+10}
\integer{k1=\k0-10}
\text{graduations=linewidth 3
segment 6,0,7,0,black
linewidth 1}
\for{k=1 to 19}{
  \integer{temp=\k*10}
  \if{(\temp=100) or (\temp=190)}{
    \text{graduations=\graduations
    linewidth 3}
    }
  \text{graduations=\graduations
  rotation \temp
  segment 6,0,7,0,black}
  \if{(\temp=100) or (\temp=190)}{
    \text{graduations=\graduations
    linewidth 1}
    }
  }
 
  
\text{rapporteur=
rotation 10
polyline black,7,0,8,0,8,-1,-8,-1,-8,0,-7,0
arc 0,0,14,14,10,190,black
arc 0,0,3,3,\k0,180,black
text black,-1,2.5,giant,?
segment 6,0,7,0,black
text black,-0.5,6,medium,90°
text black,5,0.5,medium,0°
text black,-5.5,0.5,medium,180°
halfline 0,0,-10,0,black
\graduations
killrotation
rotation \k0
halfline 0,0,10,0,black
killrotation

}

\text{dessin=draw(300,225
xrange -10,10
yrange -5,10
\rapporteur
)}

\text{fig24=<img src="\dessin" alt="image">}
\real{rep=\angle}
\text{enonce= <div class="wimscenter">\fig24</div> Donne la mesure de l'angle. <br> &#63;\({}={}\)}
\text{enonceb=°}
\text{feedback=Une graduation vaut 10°. L'angle va de la graduation 180° à la graduation \k1 °. L'angle mesure donc 180°-\k1 °=\angle ° }
