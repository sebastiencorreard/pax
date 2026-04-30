target=grandeur1 grandeur2 grandeur3 grandeur4 grandeur5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard; Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
\computeanswer{yes}
\format{html}
\precision{10000}
#define TITRE Ordre de grandeur
#if (defined TARGET_grandeur1 || defined TARGET_grandeur2 )
#if defined TARGET_grandeur1
 \title{TITRE I}
#endif
#if defined TARGET_grandeur2
 \title{TITRE II}
#endif
\integer{n1=randint(1..9)}
\integer{n2=randint(0..9)}
\integer{n3=randint(0..9)}
\integer{p=randint(2..5)}
\integer{k=randint(1,2)}
 \integer{o1=\n2>=5?\n1+1:\n1}
\integer{z=0}
\integer{mp=-\p-1}
\if{\k=1}
 {
 \text{nombre=0,}
 \for{i=1 to \p}
  {\text{nombre=\nombre\z}}
 \text{nombre=\nombre\n1\n2\n3}
 \integer{o2=-\p-1}
 }
 {
 \text{nombre=\n1\n2\n3}
 \for{i=1 to \p}
  {\text{nombre=\nombre\z}}
 \integer{o2=\p+2}
 }
\if{\o1>9}
 {
 \integer{o2=\o2+1}
 \integer{o1=1}
 }
%%%% préparation des réponses multiples
\text{goodrep=\o1=1?\(10^{\o2}):\(\o1 \times 10^{\o2})}
\text{bad1=\o1}
\text{bad2=\(10^{\o2})}
\text{bad3=\k=1?\(\n1\z\z \times 10^{\mp}):\(\n1\z\z \times 10^{\p})}
\text{bad4=\k=1?\(\n1\n2\n3 \times 10^{\mp}):\(\n1\n2\n3 \times 10^{\p})}
\integer{mo2=-\o2}
\text{bad5=\o1=1?\(10^{\mo2}):\(\o1 \times 10^{\mo2})}
\integer{rep=1}
\text{lstrep=\goodrep,\bad1,\bad3,\bad4,\bad5}
\text{lstrep=\o1=1?\lstrep:\lstrep,\bad2}

\statement{
<p>
  Quel est l'ordre de grandeur du nombre \nombre ?
</p>
#if defined TARGET_grandeur1
<div class="wimscenter">\embed{reply1}
</div>
}
\answer{matice}{\rep;\lstrep}{type=radio}{option=shuffle}
#else
<div class="wimscenter">\embed{reply1,2}\times 10<sup>\embed{reply2,3}</sup></div>
}
\answer{matice}{\o1}{type=numeric}
\answer{exposant}{\o2}{type=numeric}
#endif
#endif

#if defined TARGET_grandeur3
 \title{ TITRE III}
\integer{a=randint(2..9)}
\integer{b=randint(2..9)}
\integer{c=randint(2..9)}
\integer{n1=\a*\c}
\integer{n2=\b}
\integer{n3=\c*randint(2,4,5)}
\text{nl=shuffle(\n1,\n2)}
\integer{n1=\nl[1]}
\integer{n2=\nl[2]}
\integer{p1=randint(2..4)*randint(1,-1)}
\integer{p2=randint(2..4)*randint(1,-1)}
\integer{p3=randint(2..4)*randint(1,-1)}
\integer{k=randint(1,2)}
\if{\k=1}
 {
 \real{x1=\n1*10^(\p1)}
 \real{x2=\n2*10^(\p2)}
 \real{x3=\n3*10^(\p3)}
 \text{x1=\x1}
 \text{x2=\x2}
 \text{x3=\x3}
 }
 {
 \text{x1=\n1 \times 10^{\p1}}
 \text{x2=\n2 \times 10^{\p2}}
 \text{x3=\n3 \times 10^{\p3}}
 }
%%%% détermination de la réponse
\rational{x=\n1*\n2/ \n3}
\integer{offp=\x>9?1:0}
\rational{x=\x>9?\x/10}
\integer{o1=\x}
\integer{o2=\p1+\p2-\p3+\offp}
\integer{o2=\o1>9?\o2+1}
\integer{o1=\o1>9?1}

 \statement{
<p>
  Déterminer l'ordre de grandeur de la fraction \(\frac{\x1 \times \x2}{\x3}):
</p>
<div class="wimscenter">\embed{reply1,2} \times 10 <sup>\embed{reply2,3}</sup></div>

}
\answer{matice}{\o1}{type=numeric}
\answer{exposant}{\o2}{type=numeric}
#endif

#if defined TARGET_grandeur5
 \title{TITRE V}
 \integer{d=randint(15..85)}
 \integer{r=100*\d}
 \integer{t=randint(1..30)}
 \real{q=\t / 10}
 \real{xV=4.086*\d^3}
 \real{xM=\q*\xV}
 \integer{rM=\xM}
 \integer{rV=\xV}
 \integer{iV=15}
 \for{n=1 to 6}
  {
   \integer{iV=\rV>9?\iV+1}
   \integer{rV=\rV>9?\rV /10}
  }
 \integer{iM=15}
 \for{n=1 to 7}
  {
   \integer{iM=\rM>9?\iM+1}
   \integer{rM=\rM>9?\rM /10}
  }
\statement{
  On a observé une nouvelle planète tournant autour d'une étoile lointaine.<br>
  Elle présente la forme d'une sphère de rayon \r kilomètres, et les savants pensent que sa densité moyenne est voisine de \q kilos par litre.
  Donnez l'ordre de grandeur V de son volume, en mètres cubes, puis M, celui de sa masse, en tonnes,
 sachant que le volume d'une sphère est donné par la formule \(V = \frac{4}{3} \times \pi \times R^3).
<ul><li>
Volume : V = \(\frac{4}{3}\times\pi\times(\r \times 10^3)^3) =
 \embed{reply1,2}\times 10<sup>\embed{reply2,3}</sup></li>
<li>Masse : M = \(\q\times V)=\embed{reply3,2} \times 10<sup>\embed{reply4,3}</sup>
</li></ul>
}
\answer{Volume}{\rV}{type=numeric}
\answer{Volume}{\iV}{type=numeric}
\answer{Masse}{\rM}{type=numeric}
\answer{Masse}{\iM}{type=numeric}
#endif

#if defined TARGET_grandeur4
 \title{ TITRE IV}
 \integer{j=randint(-7..-5)}
 \integer{h=randint(2..5)}
 \integer{p=10*\h}
 \integer{ip=24*\h+\j}
\statement{
  L'effectif d'une certaine population de bactéries est multiplié par 10 toutes les 10 heures.<br>
  Chacune de ces bactéries pèse \(10^{\j}) grammes.<br>
 Si elles se multipliaient ainsi durant \p jours, à partir d'une seule bactérie,
  quel serait l'ordre de grandeur de la masse bactérienne ?
<div class="wimscenter">Ordre de grandeur de la masse: 10<sup>\embed{reply1,3}</sup></div>
}
\answer{}{\ip}{type=numeric}
#endif

#if defined TARGET_grandeur6
 \title{TITRE VI}
 \integer{p=randint(30..250)}
 \real{xp=315576*\p}
 \integer{rp=\xp}
 \integer{ip=2}
 \for{n=1 to 11}
  {
   \integer{ip=\rp>9?\ip+1}
   \integer{rp=\rp>9?\rp /10}
  }
\statement{
  Les tortues de l'île Tortoise peuvent vivre jusqu'à \p ans.<br>
  Quelle est l'ordre de grandeur de cette durée, en secondes ?
<div>
Durée : d = \embed{reply1,2}\times 10^<sup>\embed{reply2,3}</sup>
</div>
}
\answer{}{\rp}{type=numeric}
\answer{}{\ip}{type=numeric}
#endif

#if defined TARGET_grandeur7
 \title{TITRE VII}
 \integer{k=randint(20..80)}
 \integer{a=\k*100}
 \integer{m=randint(2..8)}
 \integer{b=10*\m}
 \integer{f=randint(2..8)}
 \integer{c=5*\f}
 \integer{rp=\a*\b*\c}
 \integer{ip=9}
 \for{n=1 to 9}
  {
   \integer{ip=\rp>9?\ip+1}
   \integer{rp=\rp>9?\rp /10}
  }
\statement{
  Une plage du Gondwana est longue de \a mètres, large de \b mètres et le sable, d'une ravissante couleur mauve, y est profond d'un mètre en moyenne.
  Sachant qu'un millimètre cube de ce sable contient en moyenne \c grains,
  quel est l'ordre de grandeur du nombre des grains de sable de cette plage ?
<div class="wims_center">
 Nombre de grains : \(n\) = \embed{reply1,2}\times 10^<sup>\embed{reply2,3}</sup>
</div>

}
\answer{}{\rp}{type=numeric}
\answer{}{\ip}{type=numeric}
#endif


#if defined TARGET_grandeur8
 \title{TITRE VIII}
 \integer{k=randint(15..25)}
 \real{p=randint(4..6)}
 \real{c=\k*9.47}
 \integer{rp=\c}
 \integer{ip=12-\p}
 \for{n=1 to 5}
  {
   \integer{ip=\rp>9?\ip+1}
   \integer{rp=\rp>9?\rp /10}
  }
\statement{
  L'équipage de Jack Swift, sur sa fusée Quick Flash, vole à la vitesse de 10^\p kilomètres heures.<p>
 Quel est l'ordre de grandeur du nombre d'heures qu'il lui faudra pour atteindre le système stellaire de Yellow Ring,
 situé à une distance de \k années lumières ?</p>
  On admettra que la lumière parcourt 300 000 kilomètres par seconde et qu'une année dure 365.25 jours.
<div class="wimscenter">
  Nombre d'heures : \(n\)=\embed{reply1,2}\times 10^<sup>\embed{reply2,3}</sup>
</div>
}
\answer{}{\rp}{type=numeric}
\answer{}{\ip}{type=numeric}
#endif

\hint{Si \(N=a \times 10^p) est un nombre réel écrit sous la forme scientifique,
 l'ordre de grandeur de \(N) est simplement \(a' \times 10^p), où
\(a') est l'entier <u>arrondi</u> du décimal \(a).<br>
  L'entier \(a') est inférieur au décimal \(a) si la première décimale de ce dernier est 0,1,2,3 ou 4,
  et supérieur si c'est 5,6,7,8 ou 9.
}
