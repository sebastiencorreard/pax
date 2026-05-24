!set slib_header_patron=default(realprecision,3);\
normalise={v->1/sqrt(norml2(v))*v;};\
  /* calcule une image 2D isometrique des faces du polyedre*/\
wedge={(a,b)->[a[2]*b[3]-a[3]*b[2],a[3]*b[1]-a[1]*b[3],a[1]*b[2]-a[2]*b[1]]};\
depl_standard(f, xyz)={\
  my(res2D = vector(#f),no = vector(#f),t2,w);\
  for (k = 1, #f,\
    w=vector(f[k][1],i,xyz[f[k][i+1]+1,]);\
    my(t1=normalise(w[2]-w[1])~,n=normalise(wedge(t1,w[3]-w[1])),t2=wedge(n,t1)~);\
    no[k]=n;\
    res2D[k]=vector(#w,i,[w[i]*t1,w[i]*t2]));\
  [res2D,no];\
};\
deplacement_poly (a,b,f,i1,i2)={\
  /* rotation et translation de f qui envoie l'arête joignant les sommets\
    numero i1 et numero i2 sur (a,b).\
    On suppose (a,b) et (f[i1], f[i2]) de même longueur.*/\
  my(v1=f[i2]-f[i1],v2=b-a,v=normalise([v1*v2~,v1[1]*v2[2]-v1[2]*v2[1]]));\
  my(m1=[v[1],v[2];-v[2],v[1]]);\
  my(dec=a-f[i1]*m1);\
  vector(#f, i, if(i==i1,a,if(i==i2,b,f[i]*m1 + dec)));\
};\
a_gauche={(a,b,c)->(b[1]-a[1])*(c[2]-a[2])>(b[2]-a[2])*(c[1]-a[1]);}\
  /* 1 si le point c est à gauche (au sens strict) de la droite orientee ab*/\
tout_a_droite(a,b,poly)={\
  /* 1 si tous les sommets de poly sont à droite (au sens large)\
  de la droite orientee ab */\
   for (k=1,#poly,if(a_gauche(a,b,poly[k]),return(0)));\
   1;\
};\
interieur(pt,poly)={\
  /* 1 si le point pt est dans le polygone convexe ouvert dont le bord oriente\
   est donne par le vecteur de points poly*/\
  for (k=2,#poly,if(a_droite(poly[k-1],poly[k],pt),return(0)));\
  a_droite(poly[#poly],poly[1],pt)==0\
};\
intersecte(pol1, pol2)={\
  /* 1 si les deux polygones convexes ouverts ont une intersection non vide*/\
  for (k=2,#pol1,if(tout_a_droite(pol1[k-1],pol1[k],pol2),return(0)));\
  if (tout_a_droite(pol1[#pol1],pol1[1],pol2),return(0));\
  for (k=2,#pol2,if(tout_a_droite(pol2[k-1],pol2[k],pol1),return(0)));\
  tout_a_droite(pol2[#pol2],pol2[1],pol1)==0;\
};\
/* m est la matrice d'adjacence d'un graphe de sommets 1..#m,\
un arbre couvrant est une fonction de 1..#m dans lui-même qui 'aboutit' toujours à #m*/\
\
arbres_couvrants(m,but)={\
/* si but == 0, renvoie le nombre total d'arbres couvrants\
 sinon, renvoie le but-ieme arbre couvrant */\
  my(k=1,l=1,n,v=vector(#m,x,x),nb=0);\
  while(k,\
    if(m[k,l],\
      n=l;while(v[n]!=n,n=v[n]);if(n!=k,v[k]=l;if(k==#m-1,\
      nb+=1; if(nb==but, return(v)),k+=1;l=0)));\
    while(k>1&&l==#m,v[k]=k;k-=1;l=v[k]);if(l==#m,k-=1,v[k]=k;l+=1));\
    nb;\
};\
arbre_couvrant_aleatoire0(m)={arbres_couvrants(m,1+random(arbres_couvrants(m,0)));};\
arbre_couvrant_aleatoire1(m)={\
  my (n=#m, m1 = matrix(n,n),v=vector(n), reste=n, start=n, next1);\
  for (l = 1, n,\
    k = 0;\
    for (c = 1, n, if (m[l, c], k += 1; m1[l, k] = c)); /* calcul de nombre de voisins)*/\
    m1[l, n] = k;\
    );\
  v[n] = n;\
  while (reste > 1,\
    next1 = m1[start,1+random(m1[start,n])];\
    if (v[next1]==0, v[next1]=start; reste -=1);\
    start = next1;\
  );\
  v;\
};\
arbre_couvrant_aleatoire2(m)={\
/* Le même algo, implementation plus simple un peu moins efficace ?*/\
  my (n=#m, v=vector(n), reste=n, start=n, next1=n);\
  v[n] = n;\
  while (reste > 1,\
    until (m[start,next1], next1 = 1+random(n));\
    if (v[next1]==0, v[next1]=start; reste-=1);\
    start = next1;\
  );\
  v;\
};\
arbre_couvrant_aleatoire(m)={arbre_couvrant_aleatoire2(m);}\
{pred=(v,k)->v[if(k>2,k-1,#v)];}\
{succ=(v,k)->v[if(k<#v,k+1,2)];}\
\
/* retourne l'indice dans f1 et f2\
  des sommets communs à f1 et f2 s'ils existent et 0 sinon*/\
adj(f1,f2)={my(ns1=f1[1]+1,ns2=f2[1]+1);\
  for(i=2,ns1,for(j=2,ns2,\
    if(f1[i]==f2[j],\
      if(pred(f1,i)==succ(f2,j),return([if(i>2,i-1,ns1),if(j<ns2,j+1,2),i,j]));\
      if(succ(f1,i)==pred(f2,j),return([i,j,if(i<ns1,i+1,2),if(j>2,j-1,ns2)]));\
      return(0))));\
  0;\
};\
/* retourne les numéros des deux sommets communs à f1 et f2 s'ils existent et 0 sinon*/\
adj1(f1,f2)={my(ns1=f1[1]+1,ns2=f2[1]+1);\
  for(i=2,ns1,for(j=2,ns2,\
    if(f1[i]==f2[j],\
      if(pred(f1,i)==succ(f2,j),return([pred(f1,i),f1[i]]));\
      if(succ(f1,i)==pred(f2,j),return([f1[i],succ(f1,i)]));\
      return(0))));\
  0\
};\
adjacence={f->matrix(#f,#f,i,j,adj1(f[i],f[j]));};\
etale(v,f,f2,ns)={\
  /* v est un arbre couvrant du graphe des faces,\
  // f contient la liste des numeros des sommets des faces en 3D\
  // f2 contient les coordonnees 2D d'une projection\
  // ns est le nombre de sommets du polyedre\
  // le resultat est le polygone generalise (2D)\
  // si le deploiement associe est injectif\
  // 0 sinon. */\
  my(p,r,nbs,l,n1=f[#f][1],\
    pat=vector(#f),s2D=matrix(2*ns-2,3),f2D=vector(#f));\
  f2D[#f]=vector(n1+1,x,if(x==1,n1,x-2));\
  pat[#f]=r=f2[#f];\
  for(k=1,#f2[#f],s2D[k,1]=r[k][1];s2D[k,2]=r[k][2];s2D[k,3]=f[#f][k+1]);\
  nbs = n1;\
  for(kk=1,#f-1,\
    while(f2D[kk]==0,\
      l=kk; while(f2D[v[l]]==0,l=v[l]);\
      [i1,j1,i2,j2]=adj(f[l],f[v[l]]);\
      n1=f[l][1];\
      r=deplacement_poly(s2D[f2D[v[l]][j1]+1,1..2],s2D[f2D[v[l]][j2]+1,1..2],f2[l],i1-1,i2-1);\
      for (t=1,#f,if(pat[t] && intersecte(pat[t],r),print("pseudonet")));\
      pat[l]=r;\
      rr=vector(n1+1);\
      rr[1]=n1;\
      rr[i1]=f2D[v[l]][j1];\
      rr[i2]=f2D[v[l]][j2];\
      for(k=2,n1+1,if(k!=i1 && k!=i2,\
        rr[k]=nbs; nbs+=1; s2D[nbs,1]=r[k-1][1];s2D[nbs,2]=r[k-1][2];s2D[nbs,3]=f[l][k]));\
      f2D[l]=rr));\
  return([s2D,f2D,pat]);\
};\
/* v est un arbre couvrant du graphe de matrice d'adjacence m\
  ns est le nombre de sommets\
  renvoie l'arbre couvrant dual */\
dual(v,m,ns)={\
 my(m1=matrix(ns,ns),s1,s2);\
 for(i=1,#m,for(j=1,#m,\
   if(m[i,j],m1[m[i,j][1]+1,m[i,j][2]+1]=1)));\
   for(l=1,#m-1,[s1,s2]=m[l,v[l]];m1[s1+1,s2+1]=m1[s2+1,s1+1]=0);\
  /* m1 est maintenant la matrice d'adjacence de l'arbre cherché*/\
  arbre_couvrant_aleatoire1(m1);\
};\
/* renvoie l'indice de s dans la face f, s'il existe, 0 sinon*/\
cherche(f,s)={for(j=2,f[1]+1,if(f[j]==s,return(j)));0};\
/* dit si f contient le couple (s,t)*/\
cherche2(f,s,t)={for(j=2,f[1]+1,if(f[j]==s,return(succ(f,j)==t)));0};\
ffdual(ff,ns)={\
  my(res=vector(ns),s,t,u);\
  for(i=1,ns,s=i-1;\
    for(j=1,#ff,if(f=cherche(ff[j],s),\
      t=pred(ff[j],f);\
      u=succ(ff[j],f);\
      l=List([j-1]);\
      while(t!=u,for(k=1,#ff,if(cherche2(ff[k],s,t),\
        listput(l,k-1);t=pred(ff[k],cherche(ff[k],s));break)));\
      break));\
      res[i]=concat([#l],Vec(l)));\
 matconcat(res~)\
};
