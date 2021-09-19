f = polyfit([1,2,3,4,5],[1,2,1,2,1],4); %polinomot illeszt a pontokra
xx = linspace(0,6,100); % 0-6 ig 100 cucc
yy = polyval(f,xx); % f et kiértékeli xx helyeken

f2 = polyfit([2,3,4],[-5,-7,-5],2);
xx2 = linspace(2,4,30);
yy2 = polyval(f2,xx2);

plot(xx,yy,'b-',[2,4],[-3,-3],'black*');
hold on;
plot(xx2,yy2,'red--');