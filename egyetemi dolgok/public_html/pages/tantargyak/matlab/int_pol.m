function [hiba1,hiba2] = int_pol(n)
%int_pol feldatban emgadott fv-t interpolalja egyenletes es random
%felosztason


%egyenletes felosztas
xxequal = linspace(-8,8,n+1);
%veletlen felosztas -8,8 kozott
xxrandom = rand(1,n+1)*16-8;

%fv ertekek kiszamolasa

yyequal = sin(sqrt(xxequal.^2+4)+1);
yyrandom = sin(sqrt(xxrandom.^2+4)+1);

% interpoláció elvégzése
fequal = polyfit(xxequal,yyequal,n);
frandom = polyfit(xxrandom,yyrandom,n);


%sûrû felosztás
xx = linspace(-8,8,100);
yyreal = sin(sqrt(xx.^2+4)+1);
% fv-ek kirajzolasa
subplot(2,1,1)

ylabel('veletlen')
plot(xx,yyreal,'red',xxequal,yyequal,'black*')
hold on;
plot(xx,polyval(fequal,xx),'blue')

title('egyenletes felosztas')
%masodik abra
subplot(2,1,2)
text(0,1,'veletlen')
plot(xx,yyreal,'red',xxrandom,yyrandom,'black*')
hold on;
plot(xx,polyval(frandom,xx),'blue')

title('veletlen felosztas')


%vegtelen norma
hiba1= max(abs(polyval(fequal,xx)-yyreal));
hiba2= max(abs(polyval(frandom,xx)-yyreal));


%A fuggvenyt n = 8 ra ugy hivom meg h int_pol(8)
end

