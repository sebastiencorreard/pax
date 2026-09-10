!set methods=v1+r/a1,Bereken I bij gegeven V en R\
v1+a1/r,Bereken R gegeven V en I\
a1+r/v1,Bereken V gegeven I en R\
a1+r/a2,Bereken I's bij gegeven I totaal\
v1+r/v2,Bereken de spanningsdeling\
a2+r/a1,Bereken I totaal bij een gegeven I's\
v2+r/v1,Bereken V totaal bij een gegeven V's\
v1+r/a2,Bereken gedeelte I bij gegeven V en R\
a1+r/v2,Bereken gedeelte V bij gegeven I en R\
v2+r/a1,Bereken I bij gegeven R en V's\
a2+r/v1,Bereken V bij gegeven R en I's\
v2+a1/r,Bereken R bij gegeven I en V's\
v1+a2/r,Bereken R bij gegeven V en I's

!set methlist=!column 1 of $methods
!set promptlist=!column 2 of $methods

