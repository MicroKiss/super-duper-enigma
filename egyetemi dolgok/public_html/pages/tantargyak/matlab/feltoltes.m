hossz = 10000;

% a) Rossz megold�s a vektorok felt�lt�s�re.%
tic;
T = [];
for j = 1:1:hossz
    T(j) = 1;
end   
ido1 = toc

% b) J� megold�s a vektorok felt�lt�s�re.%
tic;
T = zeros(1,hossz);
for j = 1:1:hossz
    T(j) = 1;
end
ido2=toc

% c) Legjobb megold�s a vektorok felt�lt�s�re.%
tic;
T = [1:hossz];
ido3 = toc