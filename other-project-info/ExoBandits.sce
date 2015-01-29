clear;

exec("./ExoBandits.sci");

//A=[0,0,0,0,0,0,0,0]
//PGain=rand(A)
//N=length(PGain)
//for i=1:floor(N/2)
//    PGain(i)=0
//end

PGain=[0,1]
N=length(PGain)

T=5000;
nbruns=10;

for i=1:N
    Proba(i)=1/N
end

for method=1:5 

for run=1:nbruns 
//initialisation
for i=1:N
    Actions(i)=0
end
for i=1:N
    R(i)=0
end
// début des itérations
for i=1:T
    select method 
    case 1 then action=select_greedy(R),
    case 2 then action=select_egreedy(R,0.05),
    case 3 then action=UCB1(R,i,Actions),
    case 4 then [action,Proba]=adaptive_pursuit(R,Proba,0.01,0.8),
    case 5 then [action,Proba]=roulette_adaptative(R,Proba,0.01),
    end    
    //comptage de l'action choisie
    Actions(action)=Actions(action)+1;
    if (rand()<=PGain(action)) then 
        R(action)=(((Actions(action)-1)*R(action))+1)/Actions(action)
        if  (i>1) then
           //Gain(run,i)=(((i-1)*Gain(run,(i-1))+1))/i
           Gain(run,i)=Gain(run,(i-1))+1
        else 
           Gain(run,1)=1
        end
    else
        R(action)=((Actions(action)-1)*R(action))/Actions(action)
        if  (i>1) then
           //Gain(run,i)=((i-1)*Gain(run,(i-1)))/i
           Gain(run,i)=Gain(run,(i-1))
        else 
           Gain(run,1)=0
        end 
    end
end

//range_g=1:T;
//plot(range_g,Gain(range_g),'b');

end //run


for i=1:T
   somme=0
   for run=1:nbruns
    somme=somme+Gain(run,i)
   end
   Gain_moy(i)=somme/nbruns
end

range_g=1:T;

select method 
    case 1 then plot(range_g,Gain_moy(range_g),'y'),
    case 2 then plot(range_g,Gain_moy(range_g),'b'),
    case 3 then plot(range_g,Gain_moy(range_g),'r'),
    case 4 then plot(range_g,Gain_moy(range_g),'g'),
    case 5 then plot(range_g,Gain_moy(range_g),'c'),
    end 

end //method
