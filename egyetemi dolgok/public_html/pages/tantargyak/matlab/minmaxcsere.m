A = rand(5)

[maxValue, linearIndexesOfMaxes] = max(A(:));
[minValue, linearIndexesOfMin] = min(A(:));

linearIndexesOfMaxes
linearIndexesOfMin
tmp = minValue;

A(linearIndexesOfMin) = maxValue;
A(linearIndexesOfMaxes) = tmp;

A
