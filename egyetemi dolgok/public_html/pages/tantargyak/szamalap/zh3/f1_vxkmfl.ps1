if ( $args.Length -eq 1 )
{
   	Write-Host (Get-ChildItem $args  -Directory | Measure-Object | %{$_.Count}) Könytár
    Write-Host (Get-ChildItem $args  -File | Measure-Object | %{$_.Count}) Fájl
}
ElseIf ( $args.Length -eq 0 )
{
Write-Host " Adja meg a mappa elérési útvonalát."
$a = Read-Host
   	Write-Host (Get-ChildItem $a  -Directory | Measure-Object | %{$_.Count}) Könytár
    Write-Host (Get-ChildItem $a  -File | Measure-Object | %{$_.Count}) Fájl
}
ElseIf ( $args.Length -gt 1 )
{

Write-Host " Túl sok paraméter"
}