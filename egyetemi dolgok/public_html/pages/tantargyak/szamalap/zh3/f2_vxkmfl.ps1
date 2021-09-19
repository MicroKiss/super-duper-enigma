Write-Host " "
Write-Host " x		sin(x)			cos(x)"
Write-Host " "
Write-Host "--------------------------------------------------"
0..10 | Foreach-Object { write-host  $($_/10)"	|	" ([math]::Round(([math]::sin($_/10)),4)) "	|	" ([math]::Round(([math]::cos($_/10)),4)) }