\integer{graine=randint(1..2)}
\matrix{M=wims(record 0 of data/\graine.data)}
\text{MM=\M[\tnf;]}
\matrix{MMM=pari(dat=\MM;
MN=0;
for(i=1,\ntt,if(dat[i]==\nnf,MN=MN+1));)}
\integer{MMN=pari(print(MN);)}

\text{zz=}
\text{zzz=}

\text{code=\code
from \ppp import seed
seed(\graine)\#pas touche à ma graine !\#
\#Entrer les variables\#
vi=??
vf=??
nt=??
n=0
\#################
for i in range(nt):
  issue = rand\pp(vi,vf)
  print(issue)
  if issue==?? :
    n=n+1
print('Nombre de \nnf :'+str(n))
}

\text{sscr=<script>
function graph(){n=Sk.ffi.remapToJs(Sk.globals["n"]);}
execidtest2.addEventListener('click',graph);
</script>}


\text{variable=[vi,1],[vf,\nf],[nt,\ntt]}

\text{instruction3=<li>Déterminer la condition à remplir pour compter le nombre
d'apparitions de la face \nnf.</li>}
