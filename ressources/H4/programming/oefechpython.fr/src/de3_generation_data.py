#Importation des méthodes#
from random import randint
from random import seed
seed(1)#pas touche à ma graine!\#

resultat=[]
resultatf=[]
for i in [3,4,6,8,10,12,16,20,24,30]:
  for k in range(30):
    issue = randint(1,i)
    resultat.append(issue)
  resultatf.append(resultat)
  resultat=[]
  seed(1) #impératif pour réinitialiser la graine à chaque tirage.
  
for i in range(30):
  print(resultatf[i])
  
  
#Importation des méthodes#
from random import randint
from random import seed
seed(1)\#pas touche à ma graine!\#

resultat=[]
resultatf=[]
i=0
for i in [10]:
  for k in range(30):
    issue = randint(1,i)
    resultat.append(issue)
  resultatf.append(resultat)
  resultat=[]

for i in range(1):
  print(resultatf[i])
