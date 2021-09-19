function osztottdiff(P,V)
%kiszamolja az oszottt difet
if length(P) ~= length(V),
    error 'nem egyenlo hosszuak'
end;


N = length(P);

M = zeros(N,N);
M(:,1) = V;


for i = 2:N,
    for j = i:N,
        M(j,i) = (M(j,i-1)-M(j-1,i-1))/ (P(j)-P(j-i+1)); 
    end;
end;

M



end