% Facts
male(muralidhar).
male(namdev).
male(shivaji).
male(punjaram).
male(omkar).
male(madhukar).
male(aakash).
male(sandip).
male(shivansh).
male(ganesh).

female(rohini).
female(aarti).
female(sangita).
female(jyoti).
female(meera).
female(kaveri).
female(suvarna).
female(snehal).
female(pari).

parent(muralidhar, namdev).
parent(namdev, shivaji).
parent(namdev, madhukar).
parent(namdev, punjaram).
parent(shivaji, omkar).
parent(shivaji, aarti).
parent(punjaram, ganesh).
parent(punjaram, jyoti).
parent(madhukar, aakash).
parent(madhukar, sandip).
parent(madhukar, kaveri).
parent(madhukar, suvarna).
parent(rohini, omkar).
parent(rohini, aarti).
parent(sangita, ganesh).
parent(sangita, jyoti).
parent(meera, aakash).
parent(meera, sandip).
parent(meera, kaveri).
parent(meera, suvarna).

parent(ganesh, pari).
parent(snehal, pari).
parent(sandip, shivansh).
parent(sonali, shivansh).




married(shivaji, rohini).
married(namdev, jijabai).
married(punjaram, sangita).
married(ganesh, snehal).

married(madhukar, meera).
married(sandip, sonali).


father(X, Y) :- male(X), parent(X, Y).
mother(X, Y) :- female(X), parent(X, Y).
child(X, Y) :- parent(Y, X).
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
brother(X, Y) :- sibling(X, Y), male(X).
sister(X, Y) :- sibling(X, Y), female(X).
grandparent(X, Z) :- parent(X, Y), parent(Y, Z).
grandchild(Z, X) :- grandparent(X, Z).
uncle(X, Y) :- brother(X, Z), parent(Z, Y).


cousin(X, Y) :- parent(P1, X), parent(P2, Y), sibling(P1, P2), X \= Y.
nephew(X, Y) :- male(X), parent(P, X), cousin(P, Y).
niece(X, Y) :- female(X), parent(P, X), cousin(P, Y).
great_grandparent(X, Z) :- grandparent(X, Y), parent(Y, Z).
great_grandchild(Z, X) :- great_grandparent(X, Z).


