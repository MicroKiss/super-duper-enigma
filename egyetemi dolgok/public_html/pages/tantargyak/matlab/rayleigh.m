function [minimum,maximum] = rayleigh(A)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

random = rand(1000,2)*10-5;


hanyadosok = zeros(1000,1);

for i = 1:1000,
    x = random(i,:)';

    hanyadosok(i) = dot(A*x,x)/dot(x,x);
end

minimum = min(hanyadosok)
maximum = max(hanyadosok)
end

