hossz = 10000;

% a) Rossz megoldás a vektorok feltöltésére.%
tic;
T = [];
for j = 1:1:hossz
    T(j) = 1;
end   
ido1 = toc

% b) Jó megoldás a vektorok feltöltésére.%
tic;
T = zeros(1,hossz);
for j = 1:1:hossz
    T(j) = 1;
end
ido2=toc

% c) Legjobb megoldás a vektorok feltöltésére.%
tic;
T = [1:hossz];
ido3 = toc