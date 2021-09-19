function spl3term
%Irjon szkriptet spl3term.m n´even, mely a 2. feladatban megadott harmadfok´u term´eszetes interpol´aci´os spline-t elk´esz´?ti. A fel´?rt LER-t oldja meg a Matlab
%seg´?ts´eg´evel. K´esz´?tsen k´et rajzot egym´as al´a,
%• az els?on a spline ´es a f¨uggv´eny szerepeljen,
%• jel¨olje meg, melyik-melyik ´es adjon c´?met a rajznak.
%• A m´asodikon a hibaf¨uggv´enyt jelen´?tse meg c´?mmel.
%•
%´Irja ki a k¨ozel´?t´es hib´aj´at!


MATRIX = [-1,1,-1,1,0,0,0;
          0,0,0,1,0,0,0;
          1,1,1,1,1,0,0;
          8,4,2,1,8,1,0;
          27,9,3,1,27,8,1;
          -6,2,0,0,0,0,0;
          18,2,0,0,18,12,6];
      
b = [-1,1,1,1,3,0,0]';

bMegoldva = MATRIX \b;
xx = linspace(-1,3,101);

P1 = bMegoldva(1:4);
yyP1 = polyval(P1,xx);

P2 = [1,0,0,0];
yyP2 = polyval(P2,xx);
yyP2(1:25) = 0;

P3 = [1,-3,3,-1];
yyP3= polyval(P3,xx);
yyP3(1:50) = 0;

P4 = [1,-6,12,-8];
yyP4= polyval(P4,xx);
yyP4(1:75) = 0;

yy = yyP1+bMegoldva(5)*yyP2+bMegoldva(6)*yyP3+bMegoldva(7)*yyP4;


eredetiertek = cos(xx*pi/2) +xx;


subplot(2,1,1);
plot(xx,eredetiertek,'blue')

hold on;
plot(xx,yy,'black');
legend('eredeti fv','splineos');    


subplot(2,1,2);

plot(xx,yy-eredetiertek,'red');
legend('hibafv');

max(abs(yy-eredetiertek))


end