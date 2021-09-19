function [kp,r_sor, r_osz] =Gersgorin(A)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

[n,m]=size(A);
% ellenõrzés, hogy négyzetes-e a mátrix
if n ~= m ,
    display('Baj van')
else
    
%sugarak kinyerése
r_sor = zeros(1,n);
r_osz = zeros(1,n);
for i = 1:n,
    r_sor(i) = sum(A(i,:))-A(i,i);
    r_osz(i) = sum(A(:,i))-A(i,i);
end;



%körök kirajzolása
kp = diag(A);
ang=0:0.01:2*pi; 
figure
subplot(2,1,1);
for i = 1:n,
    xp=r_sor(i)*cos(ang);
    yp=r_sor(i)*sin(ang);
    fill(kp(i)+xp,0+yp,i);    
    hold on;
end;
subplot(2,1,2);
for i = 1:n,
    
    xp=r_osz(i)*cos(ang);
    yp=r_osz(i)*sin(ang);
    fill(kp(i)+xp,0+yp,i);    
    hold on;
end;
    
end


