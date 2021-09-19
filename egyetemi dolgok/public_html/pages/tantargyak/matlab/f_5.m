A = conv2(eye(5),[-1 2 -1],'same') %tridiag
sort(eig(A))
B=A+1/1000*(rand(5,5)-1/2 )
sort(eig(B))

norm(sort(eig(A))-sort(eig(B)),'inf')