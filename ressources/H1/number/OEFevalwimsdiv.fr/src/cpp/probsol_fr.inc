#if defined TARGET_oefmachprob1
\if{\ch=1}{\text{name_sol=\(\v1 \minus \v2=\tvres\)<p>Il lui reste <span class="nowrap">\(\tres\) €</span> à payer.</p>}
           \text{name_ans=Il lui reste à payer}
          }
\if{\ch=2}{\text{name_sol=\(\v1 \times \v2=\tvres\)<p>Il y a \(\tres\) cartons.</p>}
           \text{name_ans=Il y a}
          }
\if{\ch=3}{\text{name_sol=\(\v2 \div \v1=\tvres\)<p>Chacun aura <span class="nowrap">\(\tres\) €</span>.</p>}
           \text{name_ans=Chacun aura}
          }
\if{\ch=4}{\text{name_sol=\(\v2 \div \v1=\tvres\)<p>Chaque bouquet sera composé de \(\tres\) roses.</p>}
          \text{name_ans=Chaque bouquet est composé de}
          }
#endif
#if defined TARGET_oefmachprob2 || defined TARGET_oefmachprob3
\if{\ch=5}{\text{name_sol=\(\v1 \plus \v2=\tvres\)<p>Je dois payer <span class="nowrap">\(\tres\) €</span>.</p>}
           \text{name_ans=Je dois payer}
          }
\if{\ch=6}{\text{name_sol=\(\v1 \plus \v2=\tvres\)<p>Il a dépensé <span class="nowrap">\(\tres\) €</span>.</p>}
           \text{name_ans=Il a dépensé}
          }
\if{\ch=7}{\text{name_sol=\(\v2 \plus \v1=\tvres\)<p>\nom1 mesure \(\tres \ \mathrm{m}\).</p>}
            \text{name_ans=\nom1 mesure}
          }
\if{\ch=8}{\text{name_sol=\(\v1 \minus \v2=\tvres\)<p>Il me reste <span class="nowrap">\(\tres\) €</span>.</p>}
            \text{name_ans=Il me reste}
          }
\if{\ch=9}{\text{name_sol=\(\v2 \minus \v1=\tvres\)<p>\ar1 a économisé <span class="nowrap">\(\tres\) €</span>.</p>}
            \text{name_ans=\art1 a économisé}
          }
\if{\ch=10}{\text{name_sol=\(\v2 \times \v1=\tvres\)<p>Son salaire par jour est de <span class="nowrap">\(\tres\) €</span>.</p>}
            \text{name_ans=Son salaire par jour est}
           }
\if{\ch=11}{\text{name_sol=\(\v2 \times \v1=\tvres\)<p>La dépense du collège est de <span class="nowrap">\(\tres\) €</span>.</p>}
            \text{name_ans=La dépense du collège est de}
           }
\if{\ch=12}{\text{name_sol=\(\v2 \div \v1=\tvres\)<p>Un mètre de fil électrique coûte <span class="nowrap">\(\tres\) €</span>.</p>}
          \text{name_ans=Un mètre de fil électrique coûte}
           }
\if{\ch=13}{\text{name_sol=\(\v2 \div \v1=\tvres\)<p>Il obtient \(\tres\) étagères.</p>}
          \text{name_ans=Il obtient}
           }
#endif
#if defined TARGET_oefmachprob4
\if{\ch=14}{\text{name_sol=\(A=(\v1 \plus \v2) \minus \v3\)<p>\(A=\temp \minus \v3\)</p>\(A=\tvres\)<p>\ar1 a obtenu \(\tvres \mathrm{kg}\) de confiture.</p>}
            \text{name_ans=\art1 a obtenu}     
            }
\if{\ch=15}{\text{name_sol=\(A=(\v1 \plus \v2) \minus \v3\)<p>\(A=\temp \minus \v3\)</p>\(A=\tvres\)<p>\nom3 possède <span class="nowrap">\(\tres\) €</span>.</p>}
             \text{name_ans=\nom3 possède}
            }
\if{\ch=16}{\text{name_sol=\(A=(\v1 \times \v2) \minus \v3\)<p>\(A=\temp \minus \v3\)</p>\(A=\tvres\)<p>Le coût de la randonnée est <span class="nowrap">\(\tres\) €</span>.</p>}
             \text{name_ans= Le coût de la randonnée}
            }
\if{\ch=17}{\text{name_sol=\(A=(\v2 \times \v1) \times \v3\)<p>\(A=\temp \times \v3\)</p>\(A=\tvres\)<p>La recette de la vente des billets est <span class="nowrap">\(\tres\) €</span>.</p>}
             \text{name_ans=La recette de la vente de billets est} 
              }
\if{\ch=18}{\text{name_sol=\(A=\v1 \minus (\v2 \times \v3)\)<p>\(A=\v1 \minus \temp\)</p>\(A=\tvres\)<p>\nom1 économise \(\tvres \ \mathrm{L}\) d'eau en prenant une douche.</p>}
             \text{name_ans=\nom1 économise}  
            }
\if{\ch=19}{\text{name_sol=\(A=(\v1 \plus \v3) \minus \v2\)<p>\(A=\temp \minus \v2\)</p>\(A=\tvres\)<p>\nom1 mesure \(\tvres \mathrm{m}\).</p>}
             \text{name_ans=\nom1 mesure}
            }
\if{\ch=20}{\text{name_sol=On calcule le nombre de timbres de \nom2.<p>\(\v1 \div \v2 = \temp\)</p>\nom2 a \(\temp\) timbres.<p>On calcule le nombre de timbres de \nom3.</p>\(\v3 \minus \temp=\tvres\)<p>\nom3 a \(\tvres\) timbres.</p>}
            \text{name_ans=\nom3 possède}
           }
\if{\ch=21}{\text{name_sol=On calcule le prix de la montre et du nouveau bracelet.<p>\(\v1 \plus \v2 = \temp\)</p>La montre et le nouveau bracelet coûtent ensemble <span class="nowrap">\(\temp\) €</span>.<p>On retire le prix de la montre seule.
</p>\(\temp \minus \v3=\tvres\)<p>Le nouveau bracelet coûte <span class="nowrap">\(\tvres\) €</span></p>.}
                       \text{name_ans=Le nouveau bracelet coûte}  
            }
#endif
#if defined TARGET_oefmachprob5
\if{\ch=22}{\text{name_sol=On calcule d'abord la somme d'argent dont dispose \nom1.
<p>\(B=(\tvv1 \times \tvv2) \plus \tvv3\)</p>
\(B=\tvtemp1  \plus \tvv3\)
<p>\(B=\tvres1\)</p>
Le budget total est de <span class="nowrap">\(\tres1\) €.</span>
<p>On calcule la somme dépensée.</p>
\(\tvv1 \times \tvv4 = \tvres2\)
<p>On calcule l'argent qu'il lui reste.</p>
\(\tvres1 - \tvres2 = \tvres\)
<p>Il lui restera <span class="nowrap">\(\tres\) €.</span></p>}
\text{name_ans=Il lui restera}          
          }
\if{\ch=23}{\real{test=abs(\r1)}
            \if{\r1>0} 
              {\if{\r1=1}{\text{nbrerose=rose}}{\text{nbrerose=roses}}
              \if{\temp2=1}{\text{nbrerose2=rose}}{\text{nbrerose2=roses}}
              \text{name_sol1=On cherche le nombre de roses par bouquet.
              <p>On effectue la division euclidienne de \(\v2\) par \(\v1\).</p>
              \(\v2 = (\temp1 \times \v1) + \r1\)
              <p>Il pourra mettre \(\temp1\) roses par bouquet et il restera \(\r1\) \nbrerose.</p>
              On cherche le nombre de roses qu'il manque pour en ajouter une dans chaque bouquet.
              <p>\(\v1 \minus \r1=\temp2\)</p>
              Il manque \(\temp2\) \nbrerose2 pour pouvoir ajouter une rose dans chaque bouquet.} 
              }            
              {\text{name_sol1=On cherche le nombre de roses par bouquet.
              <p>On effectue la division euclidienne de \(\v2\) par \(\v1\).</p>
              \(\v2 =\temp1 \times \v1\)
              <p>Il pourra mettre \(\temp1\) roses par bouquet et il ne manque pas de rose.</p>}
              }
              \real{test=abs(\r2)}
             \if{\r2>0}
             {\if{\r2=1}{\text{nbretulipe=tulipe}}{\text{nbretulipe=tulipes}}
              \if{\temp4=1}{\text{nbretulipe2=tulipe}}{\text{nbretulipe2=tulipes}}
              \text{name_sol2=On cherche le nombre de tulipes par bouquet.
              <p>On effectue la division euclidienne de \(\v3\) par \(\v1\).</p>
              <p>\(\v3 = (\temp3 \times \v1) + \r2\)</p>
              Il pourra mettre \(\temp3\) tulipes par bouquet et il restera \(\r2\) \nbretulipe.
              <p>On cherche le nombre de tulipes qu'il manque pour en ajouter une dans chaque bouquet.</p>
              \(\v1 \minus \r2 = \temp4\)
              <p>Il manque \(\temp4\) \nbretulipe2 pour pouvoir ajouter une tulipe dans chaque bouquet.</p>}
              }
              {\text{name_sol2=On cherche le nombre de tulipes par bouquet.
              <p>On effectue la division euclidienne de \(\v3\) par \(\v1\).</p>
              <p>\(\v3 =\temp3 \times \v1\)</p>
              Il pourra mettre \(\temp3\) tulipes par bouquet et il ne manque pas de tulipe.}
              }
              \if{\tvres=1}{\text{flower=fleur}}{\text{flower=fleurs}}
              \if{\temp4=1}{\text{flower2=fleur}}{\text{flower2=fleurs}}
              \if{\temp2=1}{\text{flower3=fleur}}{\text{flower3=fleurs}}
              \real{test1=abs(\r1)}
              \real{test2=abs(\r2)}                
          \if{\test1>0 and \test2>0}{\text{name_sol3=On ajoute les fleurs manquantes&nbsp;:
              <p>\(\temp2 \plus \temp4 = \tvres\)</p>
              Il manque \(\tvres\) \flower pour faire des bouquets identiques.}
              }
          \if{\r1=0 and \test2>0}{\text{name_sol3=Conclusion&nbsp;: 
              <p>Il manque \(\temp4\) \flower2 pour faire des bouquets identiques.}
                               }
          \if{\test1>0 and \r2=0}{\text{name_sol3=Conclusion&nbsp;: 
              <p>Il manque \(\temp2\) \flower3 pour faire des bouquets identiques.}
                               }
          \if{\r1=0 and \r2=0}{\text{name_sol3=Conclusion&nbsp;: 
              <p>Il ne manque pas de fleur pour faire des bouquets identiques.}
                              }
          \text{name_ans=Il manque}
}        
\if{\ch=24}{\text{name_sol=On calcule le coût pour un élève sans participation du foyer.
<p>\(\tvv2 \plus \tvv3=\tvtemp1\)</p>
On calcule le coût pour les \v1 élèves sans participation du foyer.
<p>\(\v1 \times \tvtemp1=\tvtemp2\)</p>
On prend en compte la participation du foyer.
<p>\(\tvtemp2 \minus \v4 = \tvres\)</p>
Le coût total du voyage est <span class="nowrap">\(\tres\) €.</span>}
          \text{name_ans=Le coût total du voyage est}
}
#endif
#if defined TARGET_oefmachdiv4 || defined TARGET_oefmachdiv5
\text{name_sol=On cherche dans \(\nb1\), combien de fois a-t-on \(\nb2\)&nbsp;?
<p>\(\nb2 \times \tq = \temp1\) et \(\nb2 \times \plusq = \temp2\)</p>
Il y va \(\tq\) fois.
<p>On calcule le reste de la division euclidienne de \(\nb1\) par \(\nb2\).</p>
<p>\(\nb1 \minus \temp1= \res\)</p>
Le reste vaut \(\res\).
}
\text{name_ans=Le reste vaut}
#endif