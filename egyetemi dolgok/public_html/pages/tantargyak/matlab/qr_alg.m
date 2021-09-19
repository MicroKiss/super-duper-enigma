function [ se, hiba ] = qr_alg(A,N)
%qr_alg this function calculates the N-th step of the qr alg.
%   The function returns the centres of the Gersgorin circles
% and their radiuses

%Check if the A matrix is symmetric
if(min(A ==A')== 0)
    error('az A matrix nem szimmetrikus!')
end;

%preallocating memory for the q and r matrixes
q = zeros(length(A));
r = zeros(length(A));

% the QR alg
for i = 1:N,
   [q,r] = qr(A);
   A = r*q;
end;
% diag(A) is the centres of the Gersgorin circles
se = diag(A);

% hiba contains all of the orher elements summarised for each row which is
% the radius
hiba = zeros(length(A),1);
for i = 1:length(A),
    hiba(i) =sum(abs(A(i,:)))-abs(se(i));
end 


end

