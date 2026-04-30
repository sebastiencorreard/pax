\text{pol=slib(geo3D/polyhedra \poly[1;1],300,300,show=[S,A,F] color=[black,green,yellow,blue] width=[6,2] id=0)}
\text{nom=wims(lookup \poly[1;1] in data/polyedre_off/index.\lang)}
\text{nom=\nom[1]}
\feedback{1=1}{
  \name_nom <strong>\nom</strong>.
  <div>\pol</div>
}
